#ifndef SVGTRANSFORMLIST_H
#define SVGTRANSFORMLIST_H

#include "svglistproperty.h"
#include "svgtransform.h"

namespace lunasvg {

class SVGTransformList : public SVGListProperty<SVGTransform>
{
public:
    SVGTransformList();

    AffineTransform consolidate() const;
    bool setValueAsString(const std::string& value);
    SVGProperty* clone() const;
    static PropertyType classType() { return EPropertyTypeTransformList; }
};

typedef SVGAnimatedProperty<SVGTransformList> SVGAnimatedTransformList;

} // namespace lunasvg

#endif // SVGTRANSFORMLIST_H
