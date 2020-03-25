#include "svgradialgradientelement.h"
#include "svgdocumentimpl.h"
#include "rendercontext.h"

namespace lunasvg {

SVGRadialGradientElement::SVGRadialGradientElement(SVGDocument* document) :
    SVGGradientElement(EElementIdRadialGradient, document),
    m_cx(EPropertyIdCx, ELengthModeWidth, EAllowNegativeLengths),
    m_cy(EPropertyIdCy, ELengthModeHeight, EAllowNegativeLengths),
    m_r(EPropertyIdR, ELengthModeBoth, EForbidNegativeLengths),
    m_fx(EPropertyIdFx, ELengthModeWidth, EAllowNegativeLengths),
    m_fy(EPropertyIdFy, ELengthModeHeight, EAllowNegativeLengths)
{
    m_cx.setDefaultValue(fiftyPercent());
    m_cy.setDefaultValue(fiftyPercent());
    m_r.setDefaultValue(fiftyPercent());

    addToPropertyMap(m_cx);
    addToPropertyMap(m_cy);
    addToPropertyMap(m_r);
    addToPropertyMap(m_fx);
    addToPropertyMap(m_fy);
}

void SVGRadialGradientElement::collectGradientAttributes(RadialGradientAttributes& attributes) const
{
    std::set<const SVGGradientElement*> processedGradients;
    const SVGGradientElement* current = this;

    while(current)
    {
        current->setGradientAttributes(attributes);
        if(current->elementId() == EElementIdRadialGradient)
        {
            const SVGRadialGradientElement* radial = to<SVGRadialGradientElement>(current);
            if(!attributes.cx && radial->m_cx.isSpecified())
                attributes.cx = radial->m_cx.currentValue();
            if(!attributes.cy && radial->m_cy.isSpecified())
                attributes.cy = radial->m_cy.currentValue();
            if(!attributes.r && radial->m_r.isSpecified())
                attributes.r = radial->m_r.currentValue();
            if(!attributes.fx && radial->m_fx.isSpecified())
                attributes.fx = radial->m_fx.currentValue();
            if(!attributes.fy && radial->m_fy.isSpecified())
                attributes.fy = radial->m_fy.currentValue();
        }

        processedGradients.insert(current);
        SVGElementImpl* ref = owner()->impl()->resolveIRI(current->hrefValue());
        current = NULL;
        if(ref && ref->isSVGGradientElement())
        {
            current = to<SVGGradientElement>(ref);
            if(processedGradients.find(current)!=processedGradients.end())
                current = NULL;
        }
    }
}

Paint SVGRadialGradientElement::getPaint(const RenderState& state) const
{
    Gradient gradient;
    RadialGradientAttributes attributes;

    collectGradientAttributes(attributes);
    if(attributes.gradientStops.empty())
        return Paint();

    gradient.type = EGradientTypeRadial;
    gradient.stops = buildGradientStops(attributes.gradientStops);

    GradientUnits userUnits = attributes.gradientUnits ? attributes.gradientUnits->enumValue() : EGradientUnitsObjectBoundingBox;

    RenderState newState(state);
    if(userUnits==EGradientUnitsObjectBoundingBox)
        newState.viewBox = Rect(0, 0, 1.f, 1.f);

    gradient.radial.cx = attributes.cx ? attributes.cx->valueX(newState) : m_cx.defaultValue()->valueX(newState);
    gradient.radial.cy = attributes.cy ? attributes.cy->valueY(newState) : m_cy.defaultValue()->valueY(newState);
    gradient.radial.r = attributes.r ? attributes.r->value(newState) : m_r.defaultValue()->value(newState);
    gradient.radial.fx = attributes.fx ? attributes.fx->valueX(newState) : gradient.radial.cx;
    gradient.radial.fy = attributes.fy ? attributes.fy->valueY(newState) : gradient.radial.cy;

    gradient.spread = attributes.spreadMethod ? attributes.spreadMethod->enumValue() : ESpreadMethodPad;

    if(userUnits==EGradientUnitsObjectBoundingBox)
    {
        gradient.matrix.translate(state.bbox.x, state.bbox.y);
        gradient.matrix.scale(state.bbox.width, state.bbox.height);
    }

    if(attributes.gradientTransform)
        gradient.matrix.concatenate(attributes.gradientTransform->consolidate());

    return gradient;
}

SVGElementImpl* SVGRadialGradientElement::clone(SVGDocument* document) const
{
    SVGRadialGradientElement* e = new SVGRadialGradientElement(document);
    baseClone(*e);
    return  e;
}

} // namespace lunasvg
