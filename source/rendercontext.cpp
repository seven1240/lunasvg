#include "rendercontext.h"
#include "svgelementhead.h"
#include "svgelementtail.h"
#include "svgnumber.h"
#include "svgenumeration.h"

namespace lunasvg {

#define MAX_STYLE CSSPropertyLastId

RenderStyle::RenderStyle() :
    m_properties(MAX_STYLE, NULL)
{
}

void RenderStyle::add(const CSSPropertyList* items)
{
    for(unsigned i=0;i<items->length();i++)
        set(items->at(i));
}

void RenderStyle::add(const SVGAnimatedStyle& style)
{
    if(style.isBaseSpecified())
        add(style.baseValue());
    if(style.isAnimating())
        add(style.currentValue());
}

void RenderStyle::add(const RenderStyle& style)
{
    for(unsigned i = 0; i < MAX_STYLE; i++)
        if(style.m_properties[i])
            m_properties[i] = style.m_properties[i];
}

void RenderStyle::inheritFrom(const RenderStyle& style)
{
    for(unsigned i = 0; i < MAX_STYLE; i++)
    {
        if(style.m_properties[i]==NULL)
            continue;

        switch(i)
        {
        case CSSPropertyIdDisplay:
        case CSSPropertyIdClip:
        case CSSPropertyIdClip_Path:
        case CSSPropertyIdOverflow:
        case CSSPropertyIdStop_Color:
        case CSSPropertyIdStop_Opacity:
        case CSSPropertyIdOpacity:
        case CSSPropertyIdMask:
            break;
        default:
            m_properties[i] = style.m_properties[i];
            break;
        }
    }
}

void RenderStyle::set(const CSSProperty* item)
{
    if(!item->isInherited())
        m_properties[item->propertyId()] = item->value();
}

bool RenderStyle::isSet(CSSPropertyID nameId) const
{
    return m_properties[nameId];
}

bool RenderStyle::isEmpty() const
{
    return m_properties.empty();
}

void RenderStyle::clear(CSSPropertyID nameId)
{
    m_properties[nameId] = NULL;
}

void RenderStyle::clearAll()
{
    m_properties.assign(MAX_STYLE, NULL);
}

float RenderStyle::opacity() const
{
    return isSet(CSSPropertyIdOpacity) ? to<SVGNumber>(get(CSSPropertyIdOpacity))->value() : 1.f;
}

bool RenderStyle::isCompositing() const
{
    return opacity() < 1.f;
}

bool RenderStyle::isDisplayNone() const
{
    return isSet(CSSPropertyIdDisplay) ? to<SVGEnumeration<Display>>(get(CSSPropertyIdDisplay))->enumValue() == EDisplayNone : false;
}

bool RenderStyle::isHidden() const
{
    return isSet(CSSPropertyIdVisibility) ? to<SVGEnumeration<Visibility>>(get(CSSPropertyIdVisibility))->enumValue() == EVisibilityHidden : false;
}

const SVGProperty* RenderStyle::get(CSSPropertyID nameId) const
{
    return m_properties[nameId];
}

std::set<const SVGElementImpl*> RenderBreaker::elementSet;

void RenderBreaker::registerElement(const SVGElementImpl* element)
{
    elementSet.insert(element);
}

void RenderBreaker::unregisterElement(const SVGElementImpl* element)
{
    elementSet.erase(element);
}

bool RenderBreaker::hasElement(const SVGElementImpl* element)
{
    return elementSet.find(element) != elementSet.end();
}

RenderContext::~RenderContext()
{
    delete m_state;
}

RenderContext::RenderContext() :
    m_state(new RenderState()),
    m_current(NULL)
{
}

void RenderContext::push()
{
    RenderState* parent = m_state;
    RenderState* child = new RenderState();
    child->element = m_current;
    child->bbox = Rect(0, 0, 0, 0);
    child->viewBox = parent->viewBox;
    child->style.inheritFrom(parent->style);
    child->matrix = parent->matrix;
    child->dpi = parent->dpi;

    m_state = child;
    m_states.push(parent);
}

void RenderContext::pop()
{
    RenderState* child = m_state;
    RenderState* parent = m_states.top();
    parent->bbox.unite(child->matrix.mapRect(child->bbox));

    delete child;
    m_state = parent;
    m_states.pop();
}

void RenderContext::skipElement()
{
    assert(m_current->isSVGElementHead());
    m_current = to<SVGElementHead>(m_current)->tail;
}

void RenderContext::render(GraphicsContext& gc, SVGElementImpl* head, SVGElementImpl* tail)
{
    m_current = head;
    m_current->render(gc, *this);
    while(m_current != tail)
    {
        m_current = m_current->next;
        m_current->render(gc, *this);
    }
}

} // namespace lunasvg
