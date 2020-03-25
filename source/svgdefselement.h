#ifndef SVGDEFSELEMENT_H
#define SVGDEFSELEMENT_H

#include "svggraphicselement.h"

namespace lunasvg {

class SVGDefsElement : public SVGGraphicsElement
{
public:
    SVGDefsElement(SVGDocument* document);
    void render(GraphicsContext&, RenderContext& context);
    void renderTail(GraphicsContext&, RenderContext&);
    SVGElementImpl* clone(SVGDocument* document) const;
};

} // namespace lunasvg

#endif // SVGDEFSELEMENT_H
