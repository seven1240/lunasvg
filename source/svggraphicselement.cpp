#include "svggraphicselement.h"
#include "svgcolor.h"
#include "svgnumber.h"
#include "svgenumeration.h"
#include "svglengthlist.h"

namespace lunasvg {

SVGGraphicsElement::SVGGraphicsElement(ElementID elementId, SVGDocument* document) :
    SVGElementHead(elementId, document),
    m_transform(EPropertyIdTransform),
    m_animateMotionMatrix(NULL)
{
    addToPropertyMap(m_transform);
}

SVGGraphicsElement::~SVGGraphicsElement()
{
    delete m_animateMotionMatrix;
}

AffineTransform* SVGGraphicsElement::animateMotionMatrix()
{
    if(!m_animateMotionMatrix)
        m_animateMotionMatrix = new AffineTransform;
    return m_animateMotionMatrix;
}

void SVGGraphicsElement::render(GraphicsContext& gc, RenderContext& context)
{
    context.push();

    RenderState& state = context.state();
    state.style.add(style());
    if(state.style.isSet(CSSPropertyIdColor))
    {
        const SVGColor* color = to<SVGColor>(state.style.get(CSSPropertyIdColor));
        if(color->colorType() != EColorTypeCurrentColor)
            state.color = color->value();
    }

    if(m_transform.isSpecified())
        state.matrix.concatenate(m_transform.currentValue()->consolidate());
    if(m_animateMotionMatrix)
        state.matrix.concatenate(*m_animateMotionMatrix);

    if(state.style.isCompositing())
        gc.pushLayer();
}

void SVGGraphicsElement::renderTail(GraphicsContext& gc, RenderContext& context)
{
    RenderState& state = context.state();
    if(state.style.isCompositing())
        gc.popLayer(state.style.opacity());

    context.pop();
}

void SVGGraphicsElement::setupGc(GraphicsContext &gc, const RenderState &state)
{
    Paint fillPaint;
    Paint strokePaint;
    StrokeData strokeData;
    float strokeOpacity;
    float fillOpacity;
    WindRule fillRule;

    fillPaint.setColor(Rgb(0, 0, 0));
    strokeData.width = 1.f;
    strokeData.miterLimit = 4.f;
    fillOpacity = 1.f;
    strokeOpacity = 1.f;
    fillRule = EWindRuleNonZero;

    const RenderStyle& style = state.style;
    if(style.isSet(CSSPropertyIdFill))
        fillPaint = to<SVGColor>(style.get(CSSPropertyIdFill))->getPaint(state);
    if(style.isSet(CSSPropertyIdStroke))
        strokePaint = to<SVGColor>(style.get(CSSPropertyIdStroke))->getPaint(state);
    if(style.isSet(CSSPropertyIdFill_Opacity))
        fillOpacity = to<SVGNumber>(style.get(CSSPropertyIdFill_Opacity))->value();
    if(style.isSet(CSSPropertyIdStroke_Opacity))
        strokeOpacity = to<SVGNumber>(style.get(CSSPropertyIdStroke_Opacity))->value();
    if(style.isSet(CSSPropertyIdFill_Rule))
        fillRule = to<SVGEnumeration<WindRule>>(style.get(CSSPropertyIdFill_Rule))->enumValue();
    if(style.isSet(CSSPropertyIdStroke_Width))
        strokeData.width = to<SVGLength>(style.get(CSSPropertyIdStroke_Width))->value(state, ELengthModeBoth);
    if(style.isSet(CSSPropertyIdStroke_Linecap))
        strokeData.cap = to<SVGEnumeration<LineCap>>(style.get(CSSPropertyIdStroke_Linecap))->enumValue();
    if(style.isSet(CSSPropertyIdStroke_Linejoin))
        strokeData.join = to<SVGEnumeration<LineJoin>>(style.get(CSSPropertyIdStroke_Linejoin))->enumValue();
    if(style.isSet(CSSPropertyIdStroke_Opacity))
        strokeOpacity = to<SVGNumber>(style.get(CSSPropertyIdStroke_Opacity))->value();
    if(style.isSet(CSSPropertyIdStroke_Miterlimit))
        strokeData.miterLimit = to<SVGNumber>(style.get(CSSPropertyIdStroke_Miterlimit))->value();
    if(style.isSet(CSSPropertyIdStroke_Dasharray))
        strokeData.dashes = to<SVGLengthList>(style.get(CSSPropertyIdStroke_Dasharray))->values(state, ELengthModeBoth);
    if(style.isSet(CSSPropertyIdStroke_Dashoffset))
        strokeData.dashOffset = to<SVGLength>(style.get(CSSPropertyIdStroke_Dashoffset))->value(state, ELengthModeBoth);

    fillPaint.setOpacity(fillOpacity);
    strokePaint.setOpacity(strokeOpacity);

    gc.setMatrix(state.matrix);
    gc.setStrokeData(strokeData);
    gc.setFillPaint(fillPaint);
    gc.setStrokePaint(strokePaint);
    gc.setFillRule(fillRule);
}

} // namespace lunasvg
