#ifndef SVGLINEARGRADIENTELEMENT_H
#define SVGLINEARGRADIENTELEMENT_H

#include "svggradientelement.h"
#include "svglength.h"

namespace lunasvg {

class LinearGradientAttributes : public GradientAttributes
{
public:
    const SVGLength* x1;
    const SVGLength* y1;
    const SVGLength* x2;
    const SVGLength* y2;

    inline LinearGradientAttributes()
    {
        x1 = NULL;
        y1 = NULL;
        x2 = NULL;
        y2 = NULL;
    }
};

class SVGLinearGradientElement : public SVGGradientElement
{
public:
    SVGLinearGradientElement(SVGDocument* document);
    const SVGAnimatedLength& x1() const { return m_x1; }
    const SVGAnimatedLength& y1() const { return m_y1; }
    const SVGAnimatedLength& x2() const { return m_x2; }
    const SVGAnimatedLength& y2() const { return m_y2; }
    void collectGradientAttributes(LinearGradientAttributes& attributes) const;
    Paint getPaint(const RenderState& state) const;
    SVGElementImpl* clone(SVGDocument* document) const;

private:
    SVGAnimatedLength m_x1;
    SVGAnimatedLength m_y1;
    SVGAnimatedLength m_x2;
    SVGAnimatedLength m_y2;
};

} // namespace lunasvg

#endif // SVGLINEARGRADIENTELEMENT_H
