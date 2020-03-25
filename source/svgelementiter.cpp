#include "svgelementiter.h"
#include "svgelementhead.h"
#include "svgelementtail.h"

namespace lunasvg {

SVGElementIter::SVGElementIter(const SVGElement* element, const std::string& id, const std::string& tagName)
{
    m_element = to<SVGElementImpl>(element);
    m_id.assign(id);
    m_elementId = tagName.empty() ? EElementLastId : Utils::elementId(tagName);
    m_currentElement = m_element->isSVGElementHead() ? const_cast<SVGElementImpl*>(m_element) : NULL;
}

bool SVGElementIter::next()
{
    if(!m_currentElement)
        return false;

    m_currentElement = m_currentElement->next;

    while(m_currentElement != to<SVGElementHead>(m_element)->tail)
    {
       if(m_currentElement->isSVGElementHead())
       {
           SVGElementHead* e = to<SVGElementHead>(m_currentElement);
           if((m_elementId==EElementLastId || m_elementId == e->elementId()) && (m_id.length()==0 || m_id == e->id()))
               return true;
       }

       m_currentElement = m_currentElement->next;
    }

    m_currentElement = NULL;
    return false;
}

SVGElement* SVGElementIter::currentElement() const
{
    return m_currentElement;
}

} // namespace lunasvg
