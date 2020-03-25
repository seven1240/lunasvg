#ifndef SVGLENGTHLIST_H
#define SVGLENGTHLIST_H

#include "svglistproperty.h"
#include "svglength.h"

namespace lunasvg {

class SVGLengthList : public SVGListProperty<SVGLength>
{
public:
    SVGLengthList();

    std::vector<float> values(const RenderState& state, LengthMode mode) const;
    bool setValueAsString(const std::string& value);
    SVGProperty* clone() const;
    static PropertyType classType() { return EPropertyTypeLengthList; }
};

typedef SVGAnimatedProperty<SVGLengthList> SVGAnimatedLengthList;

} // namespace lunasvg

#endif // SVGLENGTHLIST_H
