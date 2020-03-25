#ifndef SVGRADIALGRADIENTELEMENT_H
#define SVGRADIALGRADIENTELEMENT_H

#include "svggradientelement.h"
#include "svglength.h"

namespace lunasvg {

class RadialGradientAttributes : public GradientAttributes
{
public:
    const SVGLength* cx;
    const SVGLength* cy;
    const SVGLength* r;
    const SVGLength* fx;
    const SVGLength* fy;

    inline RadialGradientAttributes()
    {
        cx = NULL;
        cy = NULL;
        r = NULL;
        fx = NULL;
        fy = NULL;
    }
};

class SVGRadialGradientElement : public SVGGradientElement
{
public:
    SVGRadialGradientElement(SVGDocument* document);
    const SVGAnimatedLength& cx() const { return m_cx; }
    const SVGAnimatedLength& cy() const { return m_cy; }
    const SVGAnimatedLength& r() const { return m_r; }
    const SVGAnimatedLength& fx() const { return m_fx; }
    const SVGAnimatedLength& fy() const { return m_fy; }
    void collectGradientAttributes(RadialGradientAttributes& attributes) const;
    Paint getPaint(const RenderState& state) const;
    SVGElementImpl* clone(SVGDocument* document) const;

private:
    SVGAnimatedLength m_cx;
    SVGAnimatedLength m_cy;
    SVGAnimatedLength m_r;
    SVGAnimatedLength m_fx;
    SVGAnimatedLength m_fy;
};

} // namespace lunasvg

#endif // SVGRADIALGRADIENTELEMENT_H
