#ifndef SVGRECTELEMENT_H
#define SVGRECTELEMENT_H

#include "svggeometryelement.h"
#include "svglength.h"

namespace lunasvg {

class SVGRectElement : public SVGGeometryElement
{
public:
    SVGRectElement(SVGDocument* document);
    const SVGAnimatedLength& x() const { return m_x; }
    const SVGAnimatedLength& y() const { return m_y; }
    const SVGAnimatedLength& rx() const { return m_rx; }
    const SVGAnimatedLength& ry() const { return m_ry; }
    const SVGAnimatedLength& width() const { return m_width; }
    const SVGAnimatedLength& height() const { return m_heigth; }
    Path makePathAndBoundingBox(RenderState& state) const;
    void render(GraphicsContext& gc, RenderContext& context);
    SVGElementImpl* clone(SVGDocument* document) const;

private:
    SVGAnimatedLength m_x;
    SVGAnimatedLength m_y;
    SVGAnimatedLength m_rx;
    SVGAnimatedLength m_ry;
    SVGAnimatedLength m_width;
    SVGAnimatedLength m_heigth;
};

} // namespace lunasvg

#endif // SVGRECTELEMENT_H
