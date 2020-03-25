#include "svggeometryelement.h"

namespace lunasvg {

SVGGeometryElement::SVGGeometryElement(ElementID elementId, SVGDocument* document) :
    SVGGraphicsElement(elementId, document)
{
}

void SVGGeometryElement::render(GraphicsContext &gc, RenderContext &context)
{
    if(style().isDisplayNone())
    {
        context.skipElement();
        return;
    }

    SVGGraphicsElement::render(gc, context);

    RenderState& state = context.state();
    if(state.style.isHidden())
        return;

    Path path = makePathAndBoundingBox(state);
    setupGc(gc, state);
    gc.drawPath(path);
}

} // namespace lunasvg
