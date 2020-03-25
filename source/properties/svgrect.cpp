#include "svgrect.h"

namespace lunasvg {

SVGRect::SVGRect() :
    SVGProperty(EPropertyTypeRect),
    m_valid(true)
{
}

SVGProperty* SVGRect::clone() const
{
    SVGRect* property = new SVGRect();
    property->m_value = m_value;
    property->m_valid = m_valid;

    return property;
}

bool SVGRect::setValueAsString(const std::string& value)
{
    if(value.empty())
    {
        m_valid = true;
        m_value = Rect(0, 0, 0, 0);
        return true;
    }

    float x = 0;
    float y = 0;
    float w = 0;
    float h = 0;

    const char* ptr = value.c_str();
    m_valid = Utils::skipWs(ptr)
            && Utils::parseNumber(ptr, x)
            && Utils::skipWsComma(ptr)
            && Utils::parseNumber(ptr, y)
            && Utils::skipWsComma(ptr)
            && Utils::parseNumber(ptr, w)
            && Utils::skipWsComma(ptr)
            && Utils::parseNumber(ptr, h)
            && !Utils::skipWs(ptr);

    if(m_valid)
        m_value = Rect(x, y, w, h);
    else
        m_value = Rect(0, 0, 0, 0);

    return m_valid;
}

std::string SVGRect::valueAsString() const
{
    std::string out;
    out += Utils::toString(x());
    out += ' ';
    out += Utils::toString(y());
    out += ' ';
    out += Utils::toString(width());
    out += ' ';
    out += Utils::toString(height());

    return out;
}

SVGAnimatedViewBoxRect::SVGAnimatedViewBoxRect(PropertyID propertyId) :
    SVGAnimatedRect(propertyId)
{
}

bool SVGAnimatedViewBoxRect::setBaseValueAsString(const std::string &value)
{
    if(!ensureBaseValue()->setValueAsString(value))
        return false;

    if(baseValue()->width() < 0 || baseValue()->height() < 0)
    {
        baseValue()->setValue(Rect());
        baseValue()->setValid(false);
        return false;
    }

    return true;
}

} // namespace lunasvg
