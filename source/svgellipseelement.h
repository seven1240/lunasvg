#ifndef SVGELLIPSEELEMENT_H
#define SVGELLIPSEELEMENT_H

#include "svggeometryelement.h"
#include "svglength.h"

namespace lunasvg {

class SVGEllipseElement : public SVGGeometryElement
{
public:
    SVGEllipseElement(SVGDocument* document);
    const SVGAnimatedLength& cx() const { return m_cx; }
    const SVGAnimatedLength& cy() const { return m_cy; }
    const SVGAnimatedLength& rx() const { return m_rx; }
    const SVGAnimatedLength& ry() const { return m_ry; }
    Path makePathAndBoundingBox(RenderState& state) const;
    void render(GraphicsContext& gc, RenderContext& context);
    SVGElementImpl* clone(SVGDocument* document) const;

private:
    SVGAnimatedLength m_cx;
    SVGAnimatedLength m_cy;
    SVGAnimatedLength m_rx;
    SVGAnimatedLength m_ry;
};

} // namespace lunasvg

#endif // SVGELLIPSEELEMENT_H
