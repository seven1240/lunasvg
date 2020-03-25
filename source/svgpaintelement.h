#ifndef SVGPAINTELEMENT_H
#define SVGPAINTELEMENT_H

#include "svgelementhead.h"

namespace lunasvg {

class RenderState;
class Paint;

class SVGPaintElement : public SVGElementHead
{
public:
    SVGPaintElement(ElementID elementId, SVGDocument* document);
    bool isSVGPaintElement() const { return true; }
    virtual Paint getPaint(const RenderState& state) const = 0;
};

} // namespace lunasvg

#endif // SVGPAINTELEMENT_H
