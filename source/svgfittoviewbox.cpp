#include "svgfittoviewbox.h"
#include "svgelementhead.h"

namespace lunasvg {

SVGFitToViewBox::SVGFitToViewBox(SVGElementHead* owner) :
    m_viewBox(EPropertyIdViewBox),
    m_preserveAspectRatio(EPropertyIdPreserveAspectRatio)
{
    owner->addToPropertyMap(m_viewBox);
    owner->addToPropertyMap(m_preserveAspectRatio);
}

} // namespace lunasvg
