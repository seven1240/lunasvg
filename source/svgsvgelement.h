#ifndef SVGSVGELEMENT_H
#define SVGSVGELEMENT_H

#include "svggraphicselement.h"
#include "svgfittoviewbox.h"
#include "svglength.h"

namespace lunasvg {

class SVGSVGElement : public SVGGraphicsElement,
                      public SVGFitToViewBox
{
public:
    SVGSVGElement(SVGDocument* document);
    const SVGAnimatedLength& x() const { return m_x; }
    const SVGAnimatedLength& y() const { return m_y; }
    const SVGAnimatedLength& width() const { return m_width; }
    const SVGAnimatedLength& height() const { return m_height; }
    virtual void render(GraphicsContext& gc, RenderContext& context);
    SVGElementImpl* clone(SVGDocument* document) const;

private:
    SVGAnimatedLength m_x;
    SVGAnimatedLength m_y;
    SVGAnimatedLength m_width;
    SVGAnimatedLength m_height;
};

} // namespace lunasvg

#endif // SVGSVGELEMENT_H
