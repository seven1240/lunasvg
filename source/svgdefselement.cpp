#include "svgdefselement.h"
#include "rendercontext.h"

namespace lunasvg {

SVGDefsElement::SVGDefsElement(SVGDocument* document) :
    SVGGraphicsElement(EElementIdDefs, document)
{
}

void SVGDefsElement::render(GraphicsContext&, RenderContext& context)
{
    context.skipElement();
}

void SVGDefsElement::renderTail(GraphicsContext&, RenderContext&)
{
}

SVGElementImpl* SVGDefsElement::clone(SVGDocument* document) const
{
    SVGDefsElement* e = new SVGDefsElement(document);
    baseClone(*e);
    return  e;
}

} // namespace lunasvg
