#ifndef SVGPOLYELEMENT_H
#define SVGPOLYELEMENT_H

#include "svggeometryelement.h"
#include "svgpointlist.h"

namespace lunasvg {

class SVGPolyElement : public SVGGeometryElement
{
public:
    SVGPolyElement(ElementID elementId, SVGDocument* document);
    bool isSVGPolyElement() const { return true; }
    virtual void render(GraphicsContext& gc, RenderContext& context);
    const SVGAnimatedPointList& points() const { return m_points; }

private:
    SVGAnimatedPointList m_points;
};

} // namespace lunasvg

#endif // SVGPOLYELEMENT_H
