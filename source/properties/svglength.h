#ifndef SVGLENGTH_H
#define SVGLENGTH_H

#include "svgproperty.h"

namespace lunasvg {

enum LengthUnit
{
    ELengthUnitUnknown,
    ELengthUnitNumber,
    ELengthUnitPx,
    ELengthUnitPt,
    ELengthUnitPc,
    ELengthUnitIn,
    ELengthUnitCm,
    ELengthUnitMm,
    ELengthUnitEx,
    ELengthUnitEm,
    ELengthUnitPercent
};

enum LengthMode
{
    ELengthModeWidth,
    ELengthModeHeight,
    ELengthModeBoth
};

enum LengthNegativeValuesMode {
    EAllowNegativeLengths,
    EForbidNegativeLengths
};

class RenderState;
class SVGLength;

const SVGLength& hundredPercent();
const SVGLength& fiftyPercent();

class SVGLength : public SVGProperty
{
public:
    SVGLength();
    SVGLength(float value, LengthUnit unit);

    void setUnit(LengthUnit unit) { m_unit = unit; }
    LengthUnit unit() const { return m_unit; }
    bool isRelative() const;
    void setValue(float value) { m_value = value; }
    float value() const { return m_value; }
    float value(float dpi) const;
    float value(const RenderState& state, LengthMode mode = ELengthModeBoth) const;
    float valueX(const RenderState& state) const;
    float valueY(const RenderState& state) const;

    static bool parse(const char*& ptr, SVGLength& length);
    bool setValueAsString(const std::string& value);
    std::string valueAsString() const;
    SVGProperty* clone() const;
    static PropertyType classType() { return EPropertyTypeLength; }

private:
    float m_value;
    LengthUnit m_unit;
};

class SVGAnimatedLength : public SVGAnimatedProperty<SVGLength>
{
public:
    SVGAnimatedLength(PropertyID propertyId, LengthMode mode, LengthNegativeValuesMode negativeValuesMode);
    bool setBaseValueAsString(const std::string &value);
    void setDefaultValue(const SVGLength& value);

    const SVGLength* defaultValue() const { return m_defaultValue; }
    LengthMode mode() const { return m_mode; }
    LengthNegativeValuesMode negativeValuesMode() const { return m_negativeValuesMode; }
    float value(const RenderState& state) const;
    bool isZero() const;

private:
    LengthMode m_mode;
    LengthNegativeValuesMode m_negativeValuesMode;
    const SVGLength* m_defaultValue;
};

} // namespace lunasvg

#endif // SVGLENGTH_H
