#ifndef SVGSYMBOLELEMENT_H
#define SVGSYMBOLELEMENT_H

#include "svgelementhead.h"
#include "svgfittoviewbox.h"

namespace lunasvg {

class SVGSymbolElement : public SVGElementHead,
                         public SVGFitToViewBox
{
public:
    SVGSymbolElement(SVGDocument* document);
    void render(GraphicsContext& gc, RenderContext& context);
    void renderTail(GraphicsContext& gc, RenderContext& context);
    SVGElementImpl* clone(SVGDocument* document) const;
};

} // namespace lunasvg

#endif // SVGSYMBOLELEMENT_H
