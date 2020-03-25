#include "svgpolylineelement.h"
#include "path.h"

namespace lunasvg {

SVGPolylineElement::SVGPolylineElement(SVGDocument* document) :
    SVGPolyElement(EElementIdPolyline, document)
{
}

Path SVGPolylineElement::makePathAndBoundingBox(RenderState& state) const
{
    Path path;
    path.addPoints(points().currentValue()->values());
    state.bbox = path.boundingBox();
    return path;
}

SVGElementImpl* SVGPolylineElement::clone(SVGDocument* document) const
{
    SVGPolylineElement* e = new SVGPolylineElement(document);
    baseClone(*e);
    return  e;
}

} // namespace lunasvg
