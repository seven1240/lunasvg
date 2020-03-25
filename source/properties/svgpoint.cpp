#include "svgpoint.h"

namespace lunasvg {

SVGPoint::SVGPoint() :
    SVGProperty(EPropertyTypePoint)
{
}

SVGProperty* SVGPoint::clone() const
{
    SVGPoint* property = new SVGPoint();
    property->m_value = m_value;

    return property;
}

bool SVGPoint::parse(const char*& ptr, SVGPoint& point)
{
    float x = 0;
    float y = 0;
    if(!(Utils::parseNumber(ptr, x)
            && Utils::skipWsComma(ptr)
            && Utils::parseNumber(ptr, y)))
        return false;

    point.setX(x);
    point.setY(y);
    return true;
}

bool SVGPoint::setValueAsString(const std::string& value)
{
    if(value.empty())
    {
        m_value = Point();
        return true;
    }

    const char* ptr = value.c_str();
    if(Utils::skipWs(ptr)
            && parse(ptr, *this)
            && !Utils::skipWs(ptr))
        return true;

    m_value = Point();
    return false;
}

std::string SVGPoint::valueAsString() const
{
    std::string out;
    out += Utils::toString(x());
    out += ' ';
    out += Utils::toString(y());

    return out;
}

} // namespace lunasvg
