#ifndef SVGNUMBERLIST_H
#define SVGNUMBERLIST_H

#include "svglistproperty.h"
#include "svgnumber.h"

namespace lunasvg {

class SVGNumberList : public SVGListProperty<SVGNumber>
{
public:
    SVGNumberList();

    bool setValueAsString(const std::string& value);
    SVGProperty* clone() const;
    static PropertyType classType() { return EPropertyTypeNumberList; }
};

typedef SVGAnimatedProperty<SVGNumberList> SVGAnimatedNumberList;

} // namespace lunasvg

#endif // SVGNUMBERLIST_H
