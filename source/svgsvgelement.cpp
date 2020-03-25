#include "svgsvgelement.h"

namespace lunasvg {

SVGSVGElement::SVGSVGElement(SVGDocument* document) :
    SVGGraphicsElement(EElementIdSvg, document),
    SVGFitToViewBox(this),
    m_x(EPropertyIdX, ELengthModeWidth, EAllowNegativeLengths),
    m_y(EPropertyIdY, ELengthModeHeight, EAllowNegativeLengths),
    m_width(EPropertyIdWidth, ELengthModeWidth, EForbidNegativeLengths),
    m_height(EPropertyIdHeight, ELengthModeHeight, EForbidNegativeLengths)
{
    m_height.setDefaultValue(hundredPercent());
    m_width.setDefaultValue(hundredPercent());

    addToPropertyMap(m_x);
    addToPropertyMap(m_y);
    addToPropertyMap(m_width);
    addToPropertyMap(m_height);
}

void SVGSVGElement::render(GraphicsContext& gc, RenderContext& context)
{
    if(m_width.isZero() || m_height.isZero() || style().isDisplayNone())
    {
        context.skipElement();
        return;
    }

    RenderState& state = context.state();
    Rect viewPort;
    if(state.element->isSVGRootElement() || state.element->elementId()==EElementIdUse)
    {
        viewPort = state.viewBox;
    }
    else
    {
        viewPort.x = m_x.value(state);
        viewPort.y = m_y.value(state);
        viewPort.width = m_width.value(state);
        viewPort.height = m_height.value(state);
    }

    SVGGraphicsElement::render(gc, context);

    RenderState& newState = context.state();
    newState.viewBox = viewBox().isSpecified() && viewBox().currentValue()->isValid() ? viewBox().currentValue()->value() : viewPort;

    const SVGPreserveAspectRatio* positioning = preserveAspectRatio().isSpecified() ? preserveAspectRatio().currentValue() : &SVGPreserveAspectRatio::defaultValue();
    newState.matrix.concatenate(positioning->getMatrix(viewPort, newState.viewBox));
}

SVGElementImpl* SVGSVGElement::clone(SVGDocument* document) const
{
    SVGSVGElement* e = new SVGSVGElement(document);
    baseClone(*e);
    return  e;
}

} // namespace lunasvg
