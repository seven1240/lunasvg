#include "svgnumber.h"

namespace lunasvg {

SVGNumber::SVGNumber() :
    SVGProperty(EPropertyTypeNumber),
    m_value(0)
{
}

SVGProperty* SVGNumber::clone() const
{
    SVGNumber* property = new SVGNumber();
    property->m_value = m_value;

    return property;
}

bool SVGNumber::setValueAsString(const std::string& value)
{
    m_value = 0;
    if(value.empty())
        return true;

    const char* ptr = value.c_str();
    if(Utils::skipWs(ptr)
            && Utils::parseNumber(ptr, m_value)
            && !Utils::skipWs(ptr))
        return true;

    m_value = 0;
    return false;
}

std::string SVGNumber::valueAsString() const
{
    return Utils::toString(m_value);
}

SVGNumberPercentage::SVGNumberPercentage()
{
}

bool SVGNumberPercentage::parse(const char*& ptr, float& number)
{
    if(Utils::parseNumber(ptr, number))
    {
        if(Utils::skipDesc(ptr, "%", 1))
            number /= 100.f;
        number = (number < 0.f) ? 0.f : (number > 1.f) ? 1.f : number;
        return true;
    }

    return false;
}

bool SVGNumberPercentage::setValueAsString(const std::string& value)
{
    m_value = 0;
    if(value.empty())
        return true;

    const char* ptr = value.c_str();
    if(Utils::skipWs(ptr)
            && parse(ptr, m_value)
            && !Utils::skipWs(ptr))
        return true;

    m_value = 0;
    return false;
}

SVGProperty* SVGNumberPercentage::clone() const
{
    SVGNumberPercentage* property = new SVGNumberPercentage();
    property->m_value = m_value;

    return property;
}

} // namespace lunasvg
