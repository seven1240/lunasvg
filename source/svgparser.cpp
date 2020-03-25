#include "svgparser.h"
#include "svgelementhead.h"
#include "svgelementtail.h"
#include "svgdocumentimpl.h"

#include "svgparserutils.h"
#include "svgelementutils.h"
#include "svgsvgelement.h"

#define KTagUnknown 0
#define KTagOpen 1
#define KTagClose 2
#define KTagEmpty 3
#define KTagComment 4
#define KTagCData 5
#define KTagPCData 6
#define KTagInstruction 7
#define KTagDeclaration 8

namespace lunasvg {

SVGParser::SVGParser(SVGDocument *document) :
    m_document(document)
{
}

bool SVGParser::appendHead(ElementID elementId, const AttributeList& attributes)
{
    SVGElementHead* parent;
    if(m_blocks.empty())
        parent = m_current->parent;
    else
        parent = m_blocks.top();
    if(!Utils::isElementPermitted(parent->elementId(), elementId))
         return false;
    SVGElementHead* newElement = Utils::createElement(elementId, m_document);
    if(newElement==NULL)
        return false;

    appendElement(newElement);
    m_blocks.push(newElement);
    for(unsigned i=0;i<attributes.size();i++)
        newElement->setAttribute(attributes[i].first, attributes[i].second);

    return true;
}

bool SVGParser::appendTail(ElementID elementId)
{
    if(m_blocks.empty() || elementId!=m_blocks.top()->elementId())
        return false;

    appendElement(new SVGElementTail(m_document));
    SVGElementHead* head = m_blocks.top();
    head->tail = to<SVGElementTail>(m_current);
    m_blocks.pop();

    return true;
}

bool SVGParser::appendContent(const std::string&)
{
    return false;
}

void SVGParser::appendElement(SVGElementImpl* newElement)
{
    if(m_blocks.empty())
        newElement->parent = m_current->parent;
    else
        newElement->parent = m_blocks.top();
    m_current->next = newElement;
    newElement->prev = m_current;
    m_current = newElement;
}

SVGElementImpl* SVGParser::parse(const std::string& source, SVGElementHead* parent)
{
    SVGElementHead* head = new SVGSVGElement(m_document);
    head->parent = parent;
    m_current = head;

    std::stack<std::string> unsupported;
    const char* ptr = source.c_str();
    int tagType;
    std::string tagName, content;
    AttributeList attributes;
    while(enumTag(ptr, tagType, tagName, content, attributes))
    {
        ElementID elementId = Utils::elementId(tagName);
        if(tagType==KTagOpen || tagType==KTagEmpty)
        {
            if(!parent && m_blocks.empty())
            {
                if(elementId!=EElementIdSvg)
                    break;
                SVGElementHead* rootElement = to<SVGSVGElement>(m_document->rootElement());
                m_blocks.push(rootElement);
                for(unsigned i=0;i<attributes.size();i++)
                    rootElement->setAttribute(attributes[i].first, attributes[i].second);
            }
            else if(!unsupported.empty() || !elementId || !appendHead(elementId, attributes))
                unsupported.push(tagName);
        }
        if(tagType==KTagClose || tagType==KTagEmpty)
        {
            if(unsupported.empty())
            {
                if(m_blocks.empty())
                    break;

                if(!parent && m_blocks.top() == m_document->rootElement())
                {
                    if(elementId!=EElementIdSvg)
                        break;
                    m_blocks.pop();
                    break;
                }

                if(!appendTail(elementId))
                    break;
            }
            else
            {
                if(tagName!=unsupported.top())
                    break;
                unsupported.pop();
            }
        }
    }

    m_current->next = head;
    head->prev = m_current;

    if(!m_blocks.empty() || !unsupported.empty())
    {
        std::stack<SVGElementHead*>().swap(m_blocks);
        m_document->impl()->freeElement(head, head->prev);
        return NULL;
    }

    SVGElementImpl* start = head->next;
    SVGElementImpl* end = head->prev;
    delete head;
    if(start==head)
        return NULL;

    start->prev = end;
    end->next = start;

    return start;
}

bool SVGParser::enumTag(const char*& ptr, int& tagType, std::string& tagName, std::string& content, AttributeList& attributes)
{
    tagType = KTagUnknown;
    tagName.clear();
    content.clear();
    attributes.clear();
    Utils::skipWs(ptr);
    const char* start = ptr;
    while(*ptr && *ptr!='<')
        ++ptr;
    if(ptr!=start)
    {
        tagType = KTagPCData;
        content.assign(start, ptr);
        return true;
    }

    if(!*ptr || *ptr!='<')
        return false;
     ++ptr;

    if(*ptr == '/')
    {
        ++ptr;
        tagType = KTagClose;
    }
    else if(*ptr == '?')
    {
        ++ptr;
        tagType = KTagInstruction;
    }
    else if(*ptr == '!')
    {
        ++ptr;
        if(Utils::skipDesc(ptr, "--", 2))
        {
            const char* sub = strstr(ptr, "-->");
            if(!sub)
                return false;

            content.assign(ptr, sub);
            ptr += content.length() + 3;
            tagType = KTagComment;

            return true;
        }
        else if(Utils::skipDesc(ptr, "[CDATA[", 7))
        {
            const char* sub = strstr(ptr, "]]>");
            if(!sub)
                return false;

            content.assign(ptr, sub);
            ptr += content.length() + 3;
            tagType = KTagCData;

            return true;
        }

        return false;
    }

    if(!*ptr || !IS_ID(*ptr))
        return false;

    start = ptr;
    ++ptr;
    while(*ptr && IS_NAMECHAR(*ptr))
        ++ptr;
    tagName.assign(start, ptr);

    Utils::skipWs(ptr);
    if(tagType==KTagClose)
    {
        if(*ptr != '>')
            return false;
        ++ptr;
        return true;
    }

    while(*ptr && IS_ID(*ptr))
    {
        start = ptr;
        ++ptr;
        while(*ptr && IS_NAMECHAR(*ptr))
            ++ptr;
        Attribute attribute;
        attribute.first.assign(start, ptr);

        Utils::skipWs(ptr);
        if(*ptr!='=')
            return false;
        ++ptr;

        Utils::skipWs(ptr);
        if(*ptr!='"' && *ptr!='\'')
            return false;

        const char quote = *ptr;
        ++ptr;
        start = ptr;
        while(*ptr && *ptr!=quote)
            ++ptr;
        if(*ptr!=quote)
            return false;
        attribute.second.assign(start, ptr);
        attributes.push_back(attribute);
        ++ptr;
        Utils::skipWs(ptr);
    }

    if(*ptr && *ptr=='?')
    {
        if(tagType==KTagUnknown)
            return false;
        ++ptr;
        if(*ptr!='>')
            return false;
        ++ptr;
        return true;
    }

    if(*ptr && *ptr=='/')
    {
        if(tagType!=KTagUnknown)
            return false;
        ++ptr;
        if(*ptr!='>')
            return false;
        tagType = KTagEmpty;
        ++ptr;
        return true;
    }

    if(*ptr && *ptr=='>')
    {
        if(tagType!=KTagUnknown)
            return false;
        tagType = KTagOpen;
        ++ptr;
        return true;
    }

    return false;
}

} // namespace lunasvg
