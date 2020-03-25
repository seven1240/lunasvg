#ifndef SVGSTOPELEMENT_H
#define SVGSTOPELEMENT_H

#include "svgelementhead.h"
#include "svgnumber.h"

namespace lunasvg {

class Rgb;

class SVGStopElement : public SVGElementHead
{
public:
    SVGStopElement(SVGDocument* document);
    const SVGAnimatedNumberPercentage& offset() const { return m_offset; }
    Rgb stopColorWithOpacity() const;
    float offsetValue() const;
    SVGElementImpl* clone(SVGDocument* document) const;

private:
    SVGAnimatedNumberPercentage m_offset;
};

} // namespace lunasvg

#endif // SVGSTOPELEMENT_H
