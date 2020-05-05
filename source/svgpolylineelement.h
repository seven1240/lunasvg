#ifndef SVGPOLYLINEELEMENT_H
#define SVGPOLYLINEELEMENT_H

#include "svgpolyelement.h"

namespace lunasvg {

class SVGPolylineElement : public SVGPolyElement
{
public:
    SVGPolylineElement(SVGDocument* document);
    Path makePathAndBoundingBox(RenderState& state) const;
    SVGElementImpl* clone(SVGDocument* document) const;
};

} // namespace lunasvg

#endif // SVGPOLYLINEELEMENT_H
