#include "svgurireference.h"
#include "svgelementhead.h"

namespace lunasvg {

SVGURIReference::SVGURIReference(SVGElementHead *owner) :
    m_href(EPropertyIdHref)
{
    owner->addToPropertyMap(m_href);
}

const std::string& SVGURIReference::hrefValue() const
{
    return m_href.isSpecified() ? m_href.currentValue()->value() : KEmptyString;
}

} // namespace lunasvg
