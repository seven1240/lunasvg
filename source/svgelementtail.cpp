#include "svgelementtail.h"
#include "svgelementhead.h"

namespace lunasvg {

SVGElementTail::SVGElementTail(SVGDocument* document) :
    SVGElementImpl(document)
{
}

void SVGElementTail::render(GraphicsContext& gc, RenderContext& context)
{
    parent->renderTail(gc, context);
}

SVGElementImpl* SVGElementTail::clone(SVGDocument* document) const
{
    return new SVGElementTail(document);
}

} // namespace lunasvg
