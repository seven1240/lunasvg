#include "svglineargradientelement.h"
#include "svgdocumentimpl.h"
#include "rendercontext.h"

namespace lunasvg {

SVGLinearGradientElement::SVGLinearGradientElement(SVGDocument* document) :
    SVGGradientElement(EElementIdLinearGradient, document),
    m_x1(EPropertyIdX1, ELengthModeWidth, EAllowNegativeLengths),
    m_y1(EPropertyIdY1, ELengthModeHeight, EAllowNegativeLengths),
    m_x2(EPropertyIdX2, ELengthModeWidth, EAllowNegativeLengths),
    m_y2(EPropertyIdY2, ELengthModeHeight, EAllowNegativeLengths)
{
    m_x2.setDefaultValue(hundredPercent());

    addToPropertyMap(m_x1);
    addToPropertyMap(m_y1);
    addToPropertyMap(m_x2);
    addToPropertyMap(m_y2);
}

void SVGLinearGradientElement::collectGradientAttributes(LinearGradientAttributes& attributes) const
{
    std::set<const SVGGradientElement*> processedGradients;
    const SVGGradientElement* current = this;

    while(current)
    {
        current->setGradientAttributes(attributes);
        if(current->elementId() == EElementIdLinearGradient)
        {
            const SVGLinearGradientElement* linear = to<SVGLinearGradientElement>(current);
            if(!attributes.x1&&linear->m_x1.isSpecified())
                attributes.x1 = linear->m_x1.currentValue();
            if(!attributes.y1&&linear->m_y1.isSpecified())
                attributes.y1 = linear->m_y1.currentValue();
            if(!attributes.x2&&linear->m_x2.isSpecified())
                attributes.x2 = linear->m_x2.currentValue();
            if(!attributes.y2&&linear->m_y2.isSpecified())
                attributes.y2 = linear->m_y2.currentValue();
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

Paint SVGLinearGradientElement::getPaint(const RenderState& state) const
{
    Gradient gradient;
    LinearGradientAttributes attributes;

    collectGradientAttributes(attributes);
    if(attributes.gradientStops.empty())
        return Paint();        

    gradient.type = EGradientTypeLinear;
    gradient.stops = buildGradientStops(attributes.gradientStops);

    GradientUnits userUnits = attributes.gradientUnits ? attributes.gradientUnits->enumValue() : EGradientUnitsObjectBoundingBox;

    RenderState newState(state);
    if(userUnits==EGradientUnitsObjectBoundingBox)
        newState.viewBox = Rect(0, 0, 1.f, 1.f);

    gradient.linear.x1 = attributes.x1 ? attributes.x1->valueX(newState) : 0.f;
    gradient.linear.y1 = attributes.y1 ? attributes.y1->valueY(newState) : 0.f;
    gradient.linear.x2 = attributes.x2 ? attributes.x2->valueX(newState) : m_x2.defaultValue()->value(newState);
    gradient.linear.y2 = attributes.y2 ? attributes.y2->valueY(newState) : 0.f;

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

SVGElementImpl* SVGLinearGradientElement::clone(SVGDocument* document) const
{
    SVGLinearGradientElement* e = new SVGLinearGradientElement(document);
    baseClone(*e);
    return  e;
}

} // namespace lunasvg
