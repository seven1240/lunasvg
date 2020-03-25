#ifndef SVGGELEMENT_H
#define SVGGELEMENT_H


#include "svggraphicselement.h"

namespace lunasvg {

class SVGGElement : public SVGGraphicsElement
{
public:
    SVGGElement(SVGDocument* document);
    void render(GraphicsContext &gc, RenderContext& context);
    SVGElementImpl* clone(SVGDocument* document) const;
};

} // namespace lunasvg

#endif // SVGGELEMENT_H
