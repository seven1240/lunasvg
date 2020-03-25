#ifndef SVGSTRING_H
#define SVGSTRING_H

#include "svgproperty.h"

namespace lunasvg {

const static std::string KEmptyString;

class SVGString : public SVGProperty
{
public:
    SVGString();

    void setValue(std::string value) { m_value = value; }
    const std::string& value() const { return  m_value; }

    bool setValueAsString(const std::string& value);
    std::string valueAsString() const;
    SVGProperty* clone() const;
    static PropertyType classType() { return EPropertyTypeString; }

private:
    std::string m_value;
};

typedef SVGAnimatedProperty<SVGString> SVGAnimatedString;

} // namespace lunasvg

#endif // SVGSTRING_H
