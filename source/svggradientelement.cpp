#include "svggradientelement.h"
#include "svgelementiter.h"
#include "svgstopelement.h"
#include "svgelementtail.h"

namespace lunasvg {

template<> const EnumEntryList& getEnumEntryList<SpreadMethod>()
{
    static EnumEntryList entries;
    if(entries.empty())
    {
        entries.push_back(EnumEntry(ESpreadMethodPad, "pad"));
        entries.push_back(EnumEntry(ESpreadMethodReflect, "reflect"));
        entries.push_back(EnumEntry(ESpreadMethodRepeat, "repeat"));
    }

    return entries;
}

template<> const EnumEntryList& getEnumEntryList<GradientUnits>()
{
    static EnumEntryList entries;
    if(entries.empty())
    {
        entries.push_back(EnumEntry(EGradientUnitsObjectBoundingBox, "objectBoundingBox"));
        entries.push_back(EnumEntry(EGradientUnitsUserSpaceOnUse, "userSpaceOnUse"));
    }

    return entries;
}

SVGGradientElement::SVGGradientElement(ElementID elementId, SVGDocument* document) :
    SVGPaintElement(elementId, document),
    SVGURIReference (this),
    m_gradientTransform(EPropertyIdGradientTransform),
    m_spreadMethod(EPropertyIdSpreadMethod),
    m_gradientUnits(EPropertyIdGradientUnits)
{
    addToPropertyMap(m_gradientTransform);
    addToPropertyMap(m_spreadMethod);
    addToPropertyMap(m_gradientUnits);
}

void SVGGradientElement::setGradientAttributes(GradientAttributes& attributes) const
{
    if(!attributes.spreadMethod&&m_spreadMethod.isSpecified())
        attributes.spreadMethod = m_spreadMethod.currentValue();
    if(!attributes.gradientUnits&&m_gradientUnits.isSpecified())
        attributes.gradientUnits = m_gradientUnits.currentValue();
    if(!attributes.gradientTransform&&m_gradientTransform.isSpecified())
        attributes.gradientTransform = m_gradientTransform.currentValue();
    if(attributes.gradientStops.empty())
    {
        SVGElementImpl* e = next;
        while(e != tail)
        {
            if(e->elementId()==EElementIdStop)
                attributes.gradientStops.push_back(to<SVGStopElement>(e));
            e = e->next;
        }
    }
}

GradientStops SVGGradientElement::buildGradientStops(const std::vector<const SVGStopElement*>& gradientStops)
{
    GradientStops stops(gradientStops.size());

    float prevOffset = 0.f;
    for(unsigned i=0;i<gradientStops.size();i++)
    {
        const SVGStopElement* stop = gradientStops[i];
        float offset = std::min(std::max(prevOffset, stop->offsetValue()), 1.0f);
        prevOffset = offset;
        stops[i] = GradientStop(offset, stop->stopColorWithOpacity());
    }

    return stops;
}

} // namespace lunasvg
