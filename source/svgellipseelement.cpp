#include "svgellipseelement.h"

namespace lunasvg {

SVGEllipseElement::SVGEllipseElement(SVGDocument* document) :
    SVGGeometryElement(EElementIdEllipse, document),
    m_cx(EPropertyIdCx, ELengthModeWidth, EAllowNegativeLengths),
    m_cy(EPropertyIdCy, ELengthModeHeight, EAllowNegativeLengths),
    m_rx(EPropertyIdRx, ELengthModeWidth, EForbidNegativeLengths),
    m_ry(EPropertyIdRy, ELengthModeHeight, EForbidNegativeLengths)
{
    addToPropertyMap(m_cx);
    addToPropertyMap(m_cy);
    addToPropertyMap(m_rx);
    addToPropertyMap(m_ry);
}

Path SVGEllipseElement::makePathAndBoundingBox(RenderState& state) const
{
    float _cx = m_cx.value(state);
    float _cy = m_cy.value(state);
    float _rx = m_rx.value(state);
    float _ry = m_ry.value(state);

    Path path;
    state.bbox = Rect(_cx-_rx, _cy-_ry, _rx+_rx, _ry+_ry);
    path.addEllipse(state.bbox);
    return path;
}

void SVGEllipseElement::render(GraphicsContext &gc, RenderContext &context)
{
    if(m_rx.isZero() || m_ry.isZero())
    {
        context.skipElement();
        return;
    }

    SVGGeometryElement::render(gc, context);
}

SVGElementImpl* SVGEllipseElement::clone(SVGDocument* document) const
{
    SVGEllipseElement* e = new SVGEllipseElement(document);
    baseClone(*e);
    return  e;
}

} // namespace lunasvg
