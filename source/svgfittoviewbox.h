#ifndef SVGFITTOVIEWBOX_H
#define SVGFITTOVIEWBOX_H

#include "svgpreserveaspectratio.h"
#include "svgrect.h"

namespace lunasvg {

class SVGElementHead;

class SVGFitToViewBox
{
public:
    const SVGAnimatedViewBoxRect& viewBox() const { return m_viewBox; }
    const SVGAnimatedPreserveAspectRatio& preserveAspectRatio() const { return m_preserveAspectRatio; }

protected:
    SVGFitToViewBox(SVGElementHead* owner);

private:
    SVGAnimatedViewBoxRect m_viewBox;
    SVGAnimatedPreserveAspectRatio m_preserveAspectRatio;
};

} // namespace lunasvg

#endif // SVGFITTOVIEWBOX_H
