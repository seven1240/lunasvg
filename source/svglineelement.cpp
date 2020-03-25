#include "svglineelement.h"

namespace lunasvg {

SVGLineElement::SVGLineElement(SVGDocument* document) :
    SVGGeometryElement(EElementIdLine, document),
    m_x1(EPropertyIdX1, ELengthModeWidth, EAllowNegativeLengths),
    m_y1(EPropertyIdY1, ELengthModeHeight, EAllowNegativeLengths),
    m_x2(EPropertyIdX2, ELengthModeWidth, EAllowNegativeLengths),
    m_y2(EPropertyIdY2, ELengthModeHeight, EAllowNegativeLengths)
{
    addToPropertyMap(m_x1);
    addToPropertyMap(m_y1);
    addToPropertyMap(m_x2);
    addToPropertyMap(m_y2);
}

Path SVGLineElement::makePathAndBoundingBox(RenderState& state) const
{
    float _x1 = m_x1.value(state);
    float _y1 = m_y1.value(state);
    float _x2 = m_x2.value(state);
    float _y2 = m_y2.value(state);

    Path path;
    path.moveTo(_x1, _y1);
    path.lineTo(_x2, _y2);

    state.bbox.x = std::min(_x1, _x2);
    state.bbox.y = std::min(_y1, _y2);
    state.bbox.width = std::abs(_x2 - _x1);
    state.bbox.height = std::abs(_y2 - _y1);

    return path;
}

void SVGLineElement::render(GraphicsContext &gc, RenderContext &context)
{
    SVGGeometryElement::render(gc, context);
}

SVGElementImpl* SVGLineElement::clone(SVGDocument* document) const
{
    SVGLineElement* e = new SVGLineElement(document);
    baseClone(*e);
    return  e;
}

} // namespace lunasvg
