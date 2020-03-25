#include "svglength.h"
#include "rendercontext.h"

namespace lunasvg {

const SVGLength& hundredPercent()
{
    static SVGLength value(100.f, ELengthUnitPercent);
    return value;
}

const SVGLength& fiftyPercent()
{
    static SVGLength value(50.f, ELengthUnitPercent);
    return value;
}

SVGLength::SVGLength() :
    SVGProperty(EPropertyTypeLength),
    m_value(0),
    m_unit(ELengthUnitNumber)
{
}

SVGLength::SVGLength(float value, LengthUnit unit) :
    SVGProperty(EPropertyTypeLength),
    m_value(value),
    m_unit(unit)
{
}

bool SVGLength::isRelative() const
{
    return m_unit == ELengthUnitPercent
            || m_unit == ELengthUnitEm
            || m_unit == ELengthUnitEx;
}

float SVGLength::value(float dpi) const
{
    switch(m_unit)
    {
    case ELengthUnitNumber:
    case ELengthUnitPx:
        return m_value;
    case ELengthUnitIn:
        return m_value * dpi;
    case ELengthUnitCm:
        return m_value * dpi / 2.54f;
    case ELengthUnitMm:
        return m_value * dpi / 25.4f;
    case ELengthUnitPt:
        return m_value * dpi / 72.f;
    case ELengthUnitPc:
        return m_value * dpi / 6.f;
    default:
        break;
    }

    return 0.f;
}

float SVGLength::value(const RenderState& state, LengthMode mode) const
{
    if(m_unit == ELengthUnitPercent)
    {
        float w = state.viewBox.width;
        float h = state.viewBox.height;
        float max = (mode == ELengthModeWidth) ? w : (mode == ELengthModeHeight) ? h : sqrtf(w*w+h*h) / sqrtf(2);
        return m_value * max / 100.f;
    }

    return value(state.dpi);
}

float SVGLength::valueX(const RenderState &state) const
{
    return value(state, ELengthModeWidth);
}

float SVGLength::valueY(const RenderState &state) const
{
    return value(state, ELengthModeHeight);
}

SVGProperty* SVGLength::clone() const
{
    SVGLength* property = new SVGLength();
    property->m_value = m_value;
    property->m_unit = m_unit;

    return property;
}

bool SVGLength::parse(const char *&ptr, SVGLength &length)
{
    float value = 0;
    LengthUnit unit = ELengthUnitUnknown;
    if(Utils::parseNumber(ptr, value))
    {
        if(Utils::skipDesc(ptr, "%", 1))
            unit = ELengthUnitPercent;
        else if(Utils::skipDesc(ptr, "px", 2))
            unit = ELengthUnitPx;
        else if(Utils::skipDesc(ptr, "pc", 2))
            unit = ELengthUnitPc;
        else if(Utils::skipDesc(ptr, "pt", 2))
            unit = ELengthUnitPt;
        else if(Utils::skipDesc(ptr, "in", 2))
            unit = ELengthUnitIn;
        else if(Utils::skipDesc(ptr, "cm", 2))
            unit = ELengthUnitCm;
        else if(Utils::skipDesc(ptr, "mm", 2))
            unit = ELengthUnitMm;
        else if(Utils::skipDesc(ptr, "em", 2))
            unit = ELengthUnitEm;
        else if(Utils::skipDesc(ptr, "ex", 2))
            unit = ELengthUnitEx;
        else
            unit = ELengthUnitNumber;

        length.m_value = value;
        length.m_unit = unit;
        return true;
    }

    return false;
}

bool SVGLength::setValueAsString(const std::string& value)
{
    m_value = 0;
    m_unit = ELengthUnitNumber;
    if(value.empty())
        return true;

    const char* ptr = value.c_str();
    if(Utils::skipWs(ptr)
            && parse(ptr, *this)
            && !Utils::skipWs(ptr))
        return true;

    m_value = 0;
    m_unit = ELengthUnitUnknown;
    return false;
}

std::string SVGLength::valueAsString() const
{
    std::string out;

    out += Utils::toString(m_value);
    switch(m_unit)
    {
    case ELengthUnitPx:
        out += "px";
        break;
    case ELengthUnitPc:
        out += "pc";
        break;
    case ELengthUnitPt:
        out += "pt";
        break;
    case ELengthUnitIn:
        out += "in";
        break;
    case ELengthUnitCm:
        out += "cm";
        break;
    case ELengthUnitMm:
        out += "mm";
        break;
    case ELengthUnitEm:
        out += "em";
        break;
    case ELengthUnitEx:
        out += "ex";
        break;
    case ELengthUnitPercent:
        out += "%";
        break;
    default:
        break;
    }

    return  out;
}

SVGAnimatedLength::SVGAnimatedLength(PropertyID propertyId, LengthMode mode, LengthNegativeValuesMode negativeValuesMode) :
    SVGAnimatedProperty<SVGLength>(propertyId),
    m_mode(mode),
    m_negativeValuesMode(negativeValuesMode),
    m_defaultValue(NULL)
{
}

bool SVGAnimatedLength::setBaseValueAsString(const std::string &value)
{
    if(ensureBaseValue()->setValueAsString(value) && !(negativeValuesMode()==EForbidNegativeLengths&&baseValue()->value()<0))
        return true;

    baseValue()->setValue(0);
    baseValue()->setUnit(ELengthUnitNumber);
    return false;
}

void SVGAnimatedLength::setDefaultValue(const SVGLength &value)
{
    m_defaultValue = &value;
}

float SVGAnimatedLength::value(const RenderState& state) const
{
    return isSpecified() ? currentValue()->value(state, m_mode) : m_defaultValue ? m_defaultValue->value(state, m_mode) : 0.f;
}

bool SVGAnimatedLength::isZero() const
{
    return isSpecified() ? currentValue()->value() == 0.f : m_defaultValue ? m_defaultValue->value() == 0.f : true;
}

} // namespace lunasvg
