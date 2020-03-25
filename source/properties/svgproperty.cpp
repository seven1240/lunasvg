#include "svgproperty.h"

namespace lunasvg {

SVGProperty::~SVGProperty()
{
}

SVGAnimatedPropertyBase::~SVGAnimatedPropertyBase()
{
}

bool SVGAnimatedPropertyBase::isSpecified() const
{
    return isAnimating() || isBaseSpecified();
}

} // namespace lunasvg
