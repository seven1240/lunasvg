#include "svgpolygonelement.h"
#include "path.h"

namespace lunasvg {

SVGPolygonElement::SVGPolygonElement(SVGDocument* document) :
    SVGPolyElement(EElementIdPolygon, document)
{
}

Path SVGPolygonElement::makePathAndBoundingBox(RenderState& state) const
{
    Path path;
    path.addPoints(points().currentValue()->values());
    path.closePath();
    state.bbox = path.boundingBox();
    return path;
}

SVGElementImpl* SVGPolygonElement::clone(SVGDocument* document) const
{
    SVGPolygonElement* e = new SVGPolygonElement(document);
    baseClone(*e);
    return  e;
}

} // namespace lunasvg
