#ifndef SVGPOINTLIST_H
#define SVGPOINTLIST_H

#include "svglistproperty.h"
#include "svgpoint.h"

namespace lunasvg {

class SVGPointList : public SVGListProperty<SVGPoint>
{
public:
    SVGPointList();

    std::vector<Point> values() const;
    bool setValueAsString(const std::string& value);
    SVGProperty* clone() const;
    static PropertyType classType() { return EPropertyTypePointList; }
};

typedef SVGAnimatedProperty<SVGPointList> SVGAnimatedPointList;

} // namespace lunasvg

#endif // SVGPOINTLIST_H
