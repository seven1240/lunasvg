#include "svgstring.h"

namespace lunasvg {

SVGString::SVGString() :
    SVGProperty(EPropertyTypeString)
{
}

SVGProperty* SVGString::clone() const
{
    SVGString* property = new SVGString();
    property->m_value = m_value;

    return property;
}

bool SVGString::setValueAsString(const std::string& value)
{
    m_value.assign(value);
    return true;
}

std::string SVGString::valueAsString() const
{
    return  m_value;
}

} // namespace lunasvg
