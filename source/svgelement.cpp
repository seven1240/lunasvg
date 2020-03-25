#include "svgelementimpl.h"
#include "svgelementhead.h"
#include "svgelementiter.h"
#include "svgdocumentimpl.h"

namespace lunasvg {

SVGElement::SVGElement(SVGDocument* document) :
    m_owner(document)
{
}

SVGElement::~SVGElement()
{
}

SVGElement* SVGElement::insertContent(const std::string& content, InsertPosition position)
{
    return owner()->impl()->insertContent(content, to<SVGElementImpl>(this), position);
}

SVGElement* SVGElement::appendContent(const std::string& content)
{
    return insertContent(content, EBeforeEnd);
}

void SVGElement::clearContent()
{
    owner()->impl()->clearContent(to<SVGElementImpl>(this));
}

void SVGElement::removeElement()
{
    owner()->impl()->removeElement(to<SVGElementImpl>(this));
}

SVGElement* SVGElement::insertElement(const SVGElement* element, InsertPosition position)
{
    return owner()->impl()->copyElement(to<SVGElementImpl>(element), to<SVGElementImpl>(this), position);
}

SVGElement* SVGElement::appendElement(const SVGElement* element)
{
    return insertElement(element, EBeforeEnd);
}

SVGElement* SVGElement::getElementById(const std::string& id, int index) const
{
    SVGElementIter it(this, id);
    while (it.next())
    {
        if(index-- == 0)
            return it.currentElement();
    }

    return NULL;
}

SVGElement* SVGElement::getElementByTag(const std::string& tagName, int index) const
{
    SVGElementIter it(this, "", tagName);
    while (it.next())
    {
        if(index-- == 0)
            return it.currentElement();
    }

    return NULL;
}

SVGElement* SVGElement::parentElement() const
{
    return to<SVGElementImpl>(this)->parent;
}

} // namespace lunasvg
