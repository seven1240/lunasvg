#include "svgpolyelement.h"

namespace lunasvg {

SVGPolyElement::SVGPolyElement(ElementID elementId, SVGDocument* document) :
    SVGGeometryElement(elementId, document),
    m_points(EPropertyIdPoints)
{
    addToPropertyMap(m_points);
}

void SVGPolyElement::render(GraphicsContext& gc, RenderContext& context)
{
    if(!m_points.isSpecified())
    {
        context.skipElement();
        return;
    }

    SVGGeometryElement::render(gc, context);
}

} // namespace lunasvg
