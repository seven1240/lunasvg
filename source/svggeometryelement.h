#ifndef SVGGEOMETRYELEMENT_H
#define SVGGEOMETRYELEMENT_H

#include "svggraphicselement.h"

namespace lunasvg {

class RenderState;
class Path;

class SVGGeometryElement : public SVGGraphicsElement
{
public:
    SVGGeometryElement(ElementID elementId, SVGDocument* document);
    virtual Path makePathAndBoundingBox(RenderState& state) const = 0;
    bool isSVGGeometryElement() const { return true; }
    virtual void render(GraphicsContext &gc, RenderContext& context);
};

} // namespace lunasvg

#endif // SVGGEOMETRYELEMENT_H
