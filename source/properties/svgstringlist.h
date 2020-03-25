#ifndef SVGSTRINGLIST_H
#define SVGSTRINGLIST_H

#include "svglistproperty.h"
#include "svgstring.h"

namespace lunasvg {

class SVGStringList : public SVGListProperty<SVGString>
{
public:
    SVGStringList();

    bool setValueAsString(const std::string& value);
    SVGProperty* clone() const;
    static PropertyType classType() { return EPropertyTypeStringList; }
};

} // namespace lunasvg

#endif // SVGSTRINGLIST_H
