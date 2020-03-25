#include "svguseelement.h"
#include "svgdocumentimpl.h"
#include "svgelementtail.h"

namespace lunasvg {

SVGUseElement::SVGUseElement(SVGDocument* document) :
    SVGGraphicsElement(EElementIdUse, document),
    SVGURIReference(this),
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

void SVGUseElement::render(GraphicsContext& gc, RenderContext& context)
{
    if(m_width.isZero() || m_height.isZero() || style().isDisplayNone() || RenderBreaker::hasElement(this))
    {
        context.skipElement();
        return;
    }

    SVGElementImpl* ref = owner()->impl()->resolveIRI(hrefValue());
    if(!ref)
    {
        context.skipElement();
        return;
    }

    SVGGraphicsElement::render(gc, context);

    RenderState& state = context.state();
    float _x = m_x.value(state);
    float _y = m_y.value(state);

    state.matrix.translate(_x, _y);

    RenderContext newContext;
    RenderState& newState = newContext.state();
    newState.element = state.element;
    newState.bbox = Rect(0, 0, 0, 0);
    newState.viewBox = state.viewBox;
    newState.style.inheritFrom(state.style);
    newState.matrix = state.matrix;
    newState.color = state.color;
    newState.dpi = state.dpi;

    if(ref->elementId()==EElementIdSvg || ref->elementId()==EElementIdSymbol)
    {
        float _w = m_width.value(state);
        float _h = m_height.value(state);
        newState.viewBox = Rect(0, 0, _w, _h);
    }

    RenderBreaker::registerElement(this);
    newContext.render(gc, ref, to<SVGElementHead>(ref)->tail);
    RenderBreaker::unregisterElement(this);

    state.bbox.unite(newState.bbox);
}

SVGElementImpl* SVGUseElement::clone(SVGDocument* document) const
{
    SVGUseElement* e = new SVGUseElement(document);
    baseClone(*e);
    return  e;
}

} // namespace lunasvg
