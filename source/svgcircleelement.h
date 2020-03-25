#ifndef SVGCIRCLEELEMENT_H
#define SVGCIRCLEELEMENT_H

#include "svggeometryelement.h"
#include "svglength.h"

namespace lunasvg {

class SVGCircleElement : public SVGGeometryElement
{
public:
    SVGCircleElement(SVGDocument* document);
    const SVGAnimatedLength& cx() const { return m_cx; }
    const SVGAnimatedLength& cy() const { return m_cy; }
    const SVGAnimatedLength& r() const { return m_r; }
    Path makePathAndBoundingBox(RenderState& state) const;
    void render(GraphicsContext& gc, RenderContext& context);
    SVGElementImpl* clone(SVGDocument* document) const;

private:
    SVGAnimatedLength m_cx;
    SVGAnimatedLength m_cy;
    SVGAnimatedLength m_r;
};

} // namespace lunasvg

#endif // SVGCIRCLEELEMENT_H
