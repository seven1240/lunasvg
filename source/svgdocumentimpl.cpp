#include "svgdocumentimpl.h"
#include "svgrootelement.h"
#include "svgelementtail.h"
#include "svgparser.h"

#include <fstream>

namespace lunasvg {

SVGDocumentImpl::SVGDocumentImpl(SVGDocument* document) :
    m_svgParser(new SVGParser(document))
{
    m_rootElement = new SVGRootElement(document);
    m_rootElement->tail = new SVGElementTail(document);
    m_rootElement->parent = m_rootElement;
    m_rootElement->tail->parent = m_rootElement;
    m_rootElement->prev = m_rootElement->tail;
    m_rootElement->next = m_rootElement->tail;
    m_rootElement->tail->prev = m_rootElement;
    m_rootElement->tail->next = m_rootElement;
}

SVGElementImpl* SVGDocumentImpl::insertContent(const std::string& content, SVGElementImpl* target, InsertPosition position)
{
    assert(target->isSVGElementHead());
    if(target->isSVGRootElement())
    {
        if(position == EBeforeBegin)
            position = EAfterBegin;
        else if(position == EAfterEnd)
            position = EBeforeEnd;
    }

    SVGElementHead* parent;
    if(position==EAfterBegin || position==EBeforeEnd)
        parent = to<SVGElementHead>(target);
    else
        parent = target->parent;

    SVGElementImpl* head = m_svgParser->parse(content, parent);
    if(!head)
        return NULL;

    SVGElementImpl* tail = head->prev;
    insertElement(head, tail, target, position);
    dispatchElementInsertEvent(head, tail);
    return head;
}

bool SVGDocumentImpl::loadFromFile(const std::string& filename)
{
    std::fstream fs;
    fs.open(filename.c_str());

    if(!fs.is_open())
        return false;

    std::string content;
    std::getline(fs, content, '\0');

    return loadFromData(content);
}

bool SVGDocumentImpl::loadFromData(const std::string& content)
{
    m_rootElement->clearContent();
    SVGElementImpl* head = m_svgParser->parse(content, NULL);
    if(!head)
        return false;

    SVGElementImpl* tail = head->prev;
    insertElement(head, tail, m_rootElement, EAfterBegin);
    dispatchElementInsertEvent(head, tail);
    return true;
}

void SVGDocumentImpl::updateIdCache(const std::string& oldValue, const std::string& newValue, SVGElementHead* element)
{
    if(!oldValue.empty())
    {
        typedef std::multimap<std::string, SVGElementImpl*>::iterator iterator;
        std::pair<iterator, iterator> range = m_idCache.equal_range(oldValue);
        for(iterator it = range.first;it!=range.second;++it)
        {
            if(it->second == element)
            {
                m_idCache.erase(it);
                break;
            }
        }
    }

    if(!newValue.empty())
        m_idCache.insert(std::pair<std::string, SVGElementHead*>(newValue, element));
}

SVGElementImpl* SVGDocumentImpl::resolveIRI(const std::string& href) const
{
    if(href.length()>1 && href[0]=='#')
    {
        std::multimap<std::string, SVGElementImpl*>::const_iterator it = m_idCache.find(href.substr(1));
        return it != m_idCache.end() ? it->second : NULL;
    }

    return NULL;
}

SVGElementImpl* SVGDocumentImpl::moveElement(SVGElementImpl *element, SVGElementImpl* target, InsertPosition position)
{
    assert(target->isSVGElementHead());
    assert(element->isSVGElementHead());
    if(element->isSVGRootElement())
        return NULL;

    if(target->isSVGRootElement())
    {
        if(position == EBeforeBegin)
            position = EAfterBegin;
        else if(position == EAfterEnd)
            position = EBeforeEnd;
    }

    SVGElementHead* parent;
    if(position==EAfterBegin || position==EBeforeEnd)
        parent = to<SVGElementHead>(target);
    else
        parent = target->parent;

    if(!Utils::isElementPermitted(parent->elementId(), element->elementId()))
        return NULL;

    SVGElementImpl* head = element;
    SVGElementImpl* tail = to<SVGElementHead>(element)->tail;
    dispatchElementRemoveEvent(head, tail);

    head->parent = parent;
    head->prev->next = tail->next;
    tail->next->prev = head->prev;

    insertElement(head, tail, target, position);
    dispatchElementInsertEvent(head, tail);
    return head;
}

SVGElementImpl* SVGDocumentImpl::copyElement(const SVGElementImpl* element, SVGElementImpl *target, InsertPosition position)
{
    assert(target->isSVGElementHead());
    assert(element->isSVGElementHead());
    if(element->isSVGRootElement())
        return NULL;

    if(target->isSVGRootElement())
    {
        if(position == EBeforeBegin)
            position = EAfterBegin;
        else if(position == EAfterEnd)
            position = EBeforeEnd;
    }

    SVGElementHead* parent;
    if(position==EAfterBegin || position==EBeforeEnd)
        parent = to<SVGElementHead>(target);
    else
        parent = target->parent;

    if(!Utils::isElementPermitted(parent->elementId(), element->elementId()))
        return NULL;

    SVGElementImpl* head = const_cast<SVGElementImpl*>(element);
    SVGElementImpl* tail = to<SVGElementHead>(element)->tail;

    std::stack<SVGElementHead*> blocks;
    SVGElementImpl* start = head->clone(parent->owner());
    start->parent = parent;
    blocks.push(to<SVGElementHead>(start));

    SVGElementImpl* current = start;
    while(head != tail)
    {
        head = head->next;
        SVGElementImpl* newElement = head->clone(parent->owner());
        newElement->parent = blocks.top();
        newElement->prev = current;
        current->next = newElement;
        current = newElement;
        if(newElement->isSVGElementHead())
            blocks.push(to<SVGElementHead>(newElement));
        else if(newElement->isSVGElementTail())
        {
            SVGElementHead* block = blocks.top();
            block->tail = to<SVGElementTail>(newElement);
            blocks.pop();
        }
    }

    insertElement(start, current, target, position);
    dispatchElementInsertEvent(start, current);
    return start;
}

void SVGDocumentImpl::clearContent(SVGElementImpl* element)
{
    assert(element->isSVGElementHead());
    SVGElementImpl* head = element;
    SVGElementImpl* tail = to<SVGElementHead>(element)->tail;
    if(head->next == tail)
        return;
    head = head->next;
    tail = tail->prev;
    dispatchElementRemoveEvent(head, tail);
    freeElement(head, tail);
}

void SVGDocumentImpl::removeElement(SVGElementImpl* element)
{
    assert(element->isSVGElementHead());
    if(element->isSVGRootElement())
        return;

    SVGElementImpl* head = element;
    SVGElementImpl* tail = to<SVGElementHead>(element)->tail;
    dispatchElementRemoveEvent(head, tail);
    freeElement(head, tail);
}

SVGDocumentImpl::~SVGDocumentImpl()
{
    m_idCache.clear();
    delete m_svgParser;
    freeElement(m_rootElement, m_rootElement->prev);
}

void SVGDocumentImpl::dimensions(int &width, int &height, float dpi) const
{
    const SVGAnimatedLength& _width = m_rootElement->width();
    const SVGAnimatedLength& _height = m_rootElement->height();
    const SVGAnimatedRect& viewBox = m_rootElement->viewBox();

    if(_width.isSpecified() && !_width.currentValue()->isRelative())
    {
        width = int(ceilf(_width.currentValue()->value(dpi)));
    }
    else if(viewBox.isSpecified() && viewBox.currentValue()->isValid())
    {
        width = int(ceilf(viewBox.currentValue()->width()));
    }
    else
    {
        width = -1;
    }

    if(_height.isSpecified() && !_height.currentValue()->isRelative())
    {
        height = int(ceilf(_height.currentValue()->value(dpi)));
    }
    else if(viewBox.isSpecified() && viewBox.currentValue()->isValid())
    {
        height = int(ceilf(_height.currentValue()->value(dpi)));
    }
    else
    {
        height = -1;
    }
}

void SVGDocumentImpl::render(Bitmap& bitmap, float dpi, unsigned int bgColor, const std::string&)
{
    Surface surface(bitmap.width, bitmap.height);
    GraphicsContext gc(surface);

    gc.clear(bgColor);

    RenderContext context;
    RenderState& state = context.state();

    state.element = m_rootElement;
    state.dpi = dpi;
    state.viewBox = Rect(0, 0, bitmap.width, bitmap.height);

    context.render(gc, m_rootElement, m_rootElement->tail);

    surface.copyToBitmap(bitmap);
}

void SVGDocumentImpl::insertElement(SVGElementImpl* head, SVGElementImpl* tail, SVGElementImpl* target, InsertPosition position)
{
    head->prev = tail;
    tail->next = head;

    switch(position)
    {
        case EBeforeBegin:
        {
            SVGElementImpl* targetPrev = target->prev;

            targetPrev->next = head;
            head->prev = targetPrev;

            target->prev = tail;
            tail->next = target;
            break;
        }
        case EAfterBegin:
        {
            SVGElementImpl* targetNext = target->next;

            target->next = head;
            head->prev = target;

            targetNext->prev = tail;
            tail->next = targetNext;
            break;
        }
        case EBeforeEnd:
        {
            if(target->isSVGElementHead())
            {
                target = to<SVGElementHead>(target)->tail;
                SVGElementImpl* targetPrev = target->prev;

                targetPrev->next = head;
                head->prev = targetPrev;

                target->prev = tail;
                tail->next = target;
            }
            break;
        }
        case EAfterEnd:
        {
            if(target->isSVGElementHead())
            {
                target = to<SVGElementHead>(target)->tail;
                SVGElementImpl* targetNext = target->next;

                target->next = head;
                head->prev = target;

                targetNext->prev = tail;
                tail->next = targetNext;
            }
            break;
        }
    }
}

void SVGDocumentImpl::freeElement(SVGElementImpl* head, SVGElementImpl* tail)
{
    head->prev->next = tail->next;
    tail->next->prev = head->prev;

    head->prev = tail;
    tail->next = head;

    SVGElementImpl* e = head, *n;
    do
    {
        n = e->next;
        delete e;
        e = n;
    } while(e != head);
}

} // namespace lunasvg
