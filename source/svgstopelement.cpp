#include "svgstopelement.h"
#include "rendercontext.h"
#include "svgcolor.h"

namespace lunasvg {

SVGStopElement::SVGStopElement(SVGDocument* document) :
    SVGElementHead(EElementIdStop, document),
    m_offset(EPropertyIdOffset)
{
    addToPropertyMap(m_offset);
}

float SVGStopElement::offsetValue() const
{
    return m_offset.isSpecified() ? m_offset.currentValue()->value() : 0.f;
}

Rgb SVGStopElement::stopColorWithOpacity() const
{
    RenderStyle computedStyle;
    computedStyle.add(parent->style());
    computedStyle.add(style());

    Rgb currentColor;
    float stopOpacity = 1.f;
    if(computedStyle.isSet(CSSPropertyIdColor))
        currentColor = to<SVGColor>(computedStyle.get(CSSPropertyIdColor))->value();
    if(computedStyle.isSet(CSSPropertyIdStop_Opacity))
        stopOpacity = to<SVGNumber>(computedStyle.get(CSSPropertyIdStop_Opacity))->value();

    Rgb color;
    if(computedStyle.isSet(CSSPropertyIdStop_Color))
    {
        const SVGColor* stopColor = to<SVGColor>(computedStyle.get(CSSPropertyIdStop_Color));
        color = stopColor->colorType() == EColorTypeCurrentColor ? currentColor : stopColor->value();
    }

    color.a = static_cast<unsigned char>(stopOpacity * 255.f);
    return color;
}

SVGElementImpl* SVGStopElement::clone(SVGDocument* document) const
{
    SVGStopElement* e = new SVGStopElement(document);
    baseClone(*e);
    return  e;
}

} // namespace lunasvg
