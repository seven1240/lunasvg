#include "svggelement.h"
#include "rendercontext.h"

namespace lunasvg {

SVGGElement::SVGGElement(SVGDocument *document) :
    SVGGraphicsElement(EElementIdG, document)
{
}

void SVGGElement::render(GraphicsContext& gc, RenderContext& context)
{
    if(style().isDisplayNone())
    {
        context.skipElement();
        return;
    }

    SVGGraphicsElement::render(gc, context);
}

SVGElementImpl* SVGGElement::clone(SVGDocument *document) const
{
    SVGGElement* e = new SVGGElement(document);
    baseClone(*e);

    return e;
}

} // namespace lunasvg
