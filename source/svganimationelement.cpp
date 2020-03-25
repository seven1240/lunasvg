#include "svganimationelement.h"

namespace lunasvg {

SVGAnimationElement::SVGAnimationElement(ElementID elementId, SVGDocument* document) :
    SVGElementHead(elementId, document),
    m_animationValid(false),
    m_animationInitialised(false),
    m_targetElement(NULL)
{
}

bool SVGAnimationElement::setProperty(PropertyID, const std::string&)
{
    return false;
}

void SVGAnimationElement::initialiseAnimation()
{
}

void SVGAnimationElement::resetAnimation()
{
}

void SVGAnimationElement::applyAnimation()
{
}

} // namespace lunasvg
