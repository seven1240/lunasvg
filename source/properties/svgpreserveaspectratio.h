#ifndef SVGPRESERVEASPECTRATIO_H
#define SVGPRESERVEASPECTRATIO_H

#include "svgproperty.h"

namespace lunasvg {

class AffineTransform;
class Rect;

class SVGPreserveAspectRatio : public SVGProperty
{
public:
    SVGPreserveAspectRatio();

    enum Alignment
    {
        ENone,
        EXMinYMin,
        EXMidYMin,
        EXMaxYMin,
        EXMinYMid,
        EXMidYMid,
        EXMaxYMid,
        EXMinYMax,
        EXMidYMax,
        EXMaxYMax
    };

    enum Scale
    {
        EMeet,
        ESlice
    };

    void setAlign(Alignment align) { m_align = align; }
    void setScale(Scale scale) { m_scale = scale; }
    Alignment align() const { return  m_align; }
    Scale scale() const { return  m_scale; }
    AffineTransform getMatrix(const Rect& viewPort, const Rect& viewBox) const;

    static const SVGPreserveAspectRatio& defaultValue();
    bool setValueAsString(const std::string& value);
    std::string valueAsString() const;
    SVGProperty* clone() const;
    static PropertyType classType() { return EPropertyTypePreserveAspectRatio; }

private:
    Alignment m_align;
    Scale m_scale;
};

typedef SVGAnimatedProperty<SVGPreserveAspectRatio> SVGAnimatedPreserveAspectRatio;

} // namespace lunasvg

#endif // SVGPRESERVEASPECTRATIO_H
