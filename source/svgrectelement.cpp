#include "svgrectelement.h"

namespace lunasvg {

SVGRectElement::SVGRectElement(SVGDocument* document) :
    SVGGeometryElement(EElementIdRect, document),
    m_x(EPropertyIdX, ELengthModeWidth, EAllowNegativeLengths),
    m_y(EPropertyIdY, ELengthModeHeight, EAllowNegativeLengths),
    m_rx(EPropertyIdRx, ELengthModeWidth, EForbidNegativeLengths),
    m_ry(EPropertyIdRy, ELengthModeHeight, EForbidNegativeLengths),
    m_width(EPropertyIdWidth, ELengthModeWidth, EForbidNegativeLengths),
    m_heigth(EPropertyIdHeight, ELengthModeHeight, EForbidNegativeLengths)
{
    addToPropertyMap(m_x);
    addToPropertyMap(m_y);
    addToPropertyMap(m_rx);
    addToPropertyMap(m_ry);
    addToPropertyMap(m_width);
    addToPropertyMap(m_heigth);
}

Path SVGRectElement::makePathAndBoundingBox(RenderState& state) const
{
    float _x = m_x.value(state);
    float _y = m_y.value(state);
    float _w = m_width.value(state);
    float _h = m_heigth.value(state);

    float _rx, _ry;
    if(m_rx.isSpecified() && m_ry.isSpecified())
    {
        _rx = m_rx.value(state);
        _ry = m_ry.value(state);
    }
    else if(m_rx.isSpecified())
    {
        _rx = _ry = m_rx.value(state);
    }
    else if(m_ry.isSpecified())
    {
        _rx = _ry = m_ry.value(state);
    }
    else
    {
        _rx = _ry = 0.f;
    }

    Path path;
    path.addRect(_x, _y, _w, _h, _rx, _ry);
    state.bbox = Rect(_x, _y, _w, _h);
    return path;
}

void SVGRectElement::render(GraphicsContext &gc, RenderContext &context)
{
    if(m_width.isZero() || m_heigth.isZero())
    {
        context.skipElement();
        return;
    }

    SVGGeometryElement::render(gc, context);
}

SVGElementImpl* SVGRectElement::clone(SVGDocument* document) const
{
    SVGRectElement* e = new SVGRectElement(document);
    baseClone(*e);
    return  e;
}

} // namespace lunasvg
