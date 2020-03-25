#include "svgsymbolelement.h"
#include "rendercontext.h"
#include "svgcolor.h"

namespace lunasvg {

SVGSymbolElement::SVGSymbolElement(SVGDocument* document) :
    SVGElementHead(EElementIdSymbol, document),
    SVGFitToViewBox(this)
{
}

void SVGSymbolElement::render(GraphicsContext& gc, RenderContext& context)
{
    if(context.state().element->elementId() != EElementIdUse || style().isDisplayNone())
    {
        context.skipElement();
        return;
    }

    context.push();
    RenderState& state = context.state();

    const Rect& viewPort = state.viewBox;
    state.viewBox = viewBox().isSpecified() && viewBox().currentValue()->isValid() ? viewBox().currentValue()->value() : viewPort;

    const SVGPreserveAspectRatio* positioning = preserveAspectRatio().isSpecified() ? preserveAspectRatio().currentValue() : &SVGPreserveAspectRatio::defaultValue();
    state.matrix.concatenate(positioning->getMatrix(viewPort, state.viewBox));

    state.style.add(style());
    if(state.style.isSet(CSSPropertyIdColor))
    {
        const SVGColor* color = to<SVGColor>(state.style.get(CSSPropertyIdColor));
        if(color->colorType() != EColorTypeCurrentColor)
            state.color = color->value();
    }

    if(state.style.isCompositing())
        gc.pushLayer();
}

void SVGSymbolElement::renderTail(GraphicsContext& gc, RenderContext& context)
{
    RenderState& state = context.state();
    if(state.style.isCompositing())
        gc.popLayer(state.style.opacity());

    context.pop();
}

SVGElementImpl* SVGSymbolElement::clone(SVGDocument* document) const
{
    SVGSymbolElement* e = new SVGSymbolElement(document);
    baseClone(*e);
    return  e;
}

} // namespace lunasvg
