#include "svgcircleelement.h"

namespace lunasvg {

SVGCircleElement::SVGCircleElement(SVGDocument* document) :
    SVGGeometryElement(EElementIdCircle, document),
    m_cx(EPropertyIdCx, ELengthModeWidth, EAllowNegativeLengths),
    m_cy(EPropertyIdCy, ELengthModeHeight, EAllowNegativeLengths),
    m_r(EPropertyIdR, ELengthModeBoth, EForbidNegativeLengths)
{
    addToPropertyMap(m_cx);
    addToPropertyMap(m_cy);
    addToPropertyMap(m_r);
}

Path SVGCircleElement::makePathAndBoundingBox(RenderState& state) const
{
    float _cx = m_cx.value(state);
    float _cy = m_cy.value(state);
    float _r = m_r.value(state);

    Path path;
    state.bbox = Rect(_cx-_r, _cy-_r, _r+_r, _r+_r);
    path.addEllipse(state.bbox);
    return path;
}

void SVGCircleElement::render(GraphicsContext &gc, RenderContext &context)
{
    if(m_r.isZero())
    {
        context.skipElement();
        return;
    }

    SVGGeometryElement::render(gc, context);
}

SVGElementImpl* SVGCircleElement::clone(SVGDocument* document) const
{
    SVGCircleElement* e = new SVGCircleElement(document);
    baseClone(*e);
    return  e;
}

} // namespace lunasvg
