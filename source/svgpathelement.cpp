#include "svgpathelement.h"

namespace lunasvg {

SVGPathElement::SVGPathElement(SVGDocument *document) :
    SVGGeometryElement(EElementIdPath, document),
    m_d(EPropertyIdD)
{
    addToPropertyMap(m_d);
}

Path SVGPathElement::makePathAndBoundingBox(RenderState& state) const
{
    const Path& path = m_d.currentValue()->value();
    state.bbox = path.boundingBox();
    return path;
}

void SVGPathElement::render(GraphicsContext& gc, RenderContext& context)
{
    if(!m_d.isSpecified())
    {
        context.skipElement();
        return;
    }

    SVGGeometryElement::render(gc, context);
}

SVGElementImpl* SVGPathElement::clone(SVGDocument* document) const
{
    SVGPathElement* e = new SVGPathElement(document);
    baseClone(*e);
    return e;
}

} // namespace lunasvg
