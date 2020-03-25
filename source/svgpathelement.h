#ifndef SVGPATHELEMENT_H
#define SVGPATHELEMENT_H

#include "svggeometryelement.h"
#include "svgpath.h"

namespace lunasvg {

class SVGPathElement : public SVGGeometryElement
{
public:
    SVGPathElement(SVGDocument* document);
    const SVGAnimatedPath& d() const { return m_d; }
    Path makePathAndBoundingBox(RenderState& state) const;
    void render(GraphicsContext &gc, RenderContext& context);
    SVGElementImpl* clone(SVGDocument* document) const;

private:
    SVGAnimatedPath m_d;
};

} // namespace lunasvg

#endif // SVGPATHELEMENT_H
