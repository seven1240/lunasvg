#ifndef SVGLINEELEMENT_H
#define SVGLINEELEMENT_H

#include "svggeometryelement.h"
#include "svglength.h"

namespace lunasvg {

class SVGLineElement : public SVGGeometryElement
{
public:
    SVGLineElement(SVGDocument* document);
    const SVGAnimatedLength& x1() const { return m_x1; }
    const SVGAnimatedLength& y1() const { return m_y1; }
    const SVGAnimatedLength& x2() const { return m_x2; }
    const SVGAnimatedLength& y2() const { return m_y2; }
    Path makePathAndBoundingBox(RenderState& state) const;
    void render(GraphicsContext& gc, RenderContext& context);
    SVGElementImpl* clone(SVGDocument* document) const;

private:
    SVGAnimatedLength m_x1;
    SVGAnimatedLength m_y1;
    SVGAnimatedLength m_x2;
    SVGAnimatedLength m_y2;
};

} // namespace lunasvg

#endif // SVGLINEELEMENT_H
