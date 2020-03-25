#ifndef SVGNUMBER_H
#define SVGNUMBER_H

#include "svgproperty.h"

namespace lunasvg {

class SVGNumber : public SVGProperty
{
public:
    SVGNumber();

    void setValue(float value) { m_value = value; }
    float value() const { return  m_value; }

    std::string valueAsString() const;
    virtual bool setValueAsString(const std::string& value);
    virtual SVGProperty* clone() const;
    static PropertyType classType() { return EPropertyTypeNumber; }

protected:
    float m_value;
};

class SVGNumberPercentage : public SVGNumber
{
public:
    SVGNumberPercentage();

    static bool parse(const char*& ptr, float& number);
    bool setValueAsString(const std::string& value);
    SVGProperty* clone() const;
};

typedef SVGAnimatedProperty<SVGNumber> SVGAnimatedNumber;
typedef SVGAnimatedProperty<SVGNumberPercentage> SVGAnimatedNumberPercentage;

} // namespace lunasvg

#endif // SVGNUMBER_H
