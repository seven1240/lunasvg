#ifndef SVGGRADIENTELEMENT_H
#define SVGGRADIENTELEMENT_H

#include "svgpaintelement.h"
#include "svgurireference.h"
#include "svgenumeration.h"
#include "svgtransformlist.h"
#include "gradient.h"

namespace lunasvg {

template<> const EnumEntryList& getEnumEntryList<SpreadMethod>();
template<> const EnumEntryList& getEnumEntryList<GradientUnits>();

class SVGStopElement;

class GradientAttributes
{
public:
    const SVGEnumeration<GradientUnits>* gradientUnits;
    const SVGEnumeration<SpreadMethod>* spreadMethod;
    const SVGTransformList* gradientTransform;
    std::vector<const SVGStopElement*> gradientStops;

    inline GradientAttributes()
    {
        gradientUnits = NULL;
        spreadMethod = NULL;
        gradientTransform = NULL;
    }
};

class SVGGradientElement : public SVGPaintElement,
                           public SVGURIReference
{
public:
    SVGGradientElement(ElementID elementId, SVGDocument* document);
    bool isSVGGradientElement() const { return true; }
    const SVGAnimatedTransformList& gradientTransform() const { return m_gradientTransform; }
    const SVGAnimatedEnumeration<SpreadMethod>& spreadMethod() const { return m_spreadMethod; }
    const SVGAnimatedEnumeration<GradientUnits>& gradientUnits() const { return m_gradientUnits; }
    void setGradientAttributes(GradientAttributes& attributes) const;
    static GradientStops buildGradientStops(const std::vector<const SVGStopElement*>& gradientStops);

private:
    SVGAnimatedTransformList m_gradientTransform;
    SVGAnimatedEnumeration<SpreadMethod> m_spreadMethod;
    SVGAnimatedEnumeration<GradientUnits> m_gradientUnits;
};

} // namespace lunasvg

#endif // SVGGRADIENTELEMENT_H
