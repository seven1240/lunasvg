#include "svglengthlist.h"

namespace lunasvg {

SVGLengthList::SVGLengthList() :
    SVGListProperty<SVGLength>(EPropertyTypeLengthList)
{
}

std::vector<float> SVGLengthList::values(const RenderState &state, LengthMode mode) const
{
    std::vector<float> v(length());
    for(size_t i = 0;i < length(); i++)
        v[i] = at(i)->value(state, mode);
    return v;
}

SVGProperty* SVGLengthList::clone() const
{
    SVGLengthList* property = new SVGLengthList();
    baseClone(property);

    return property;
}

bool SVGLengthList::setValueAsString(const std::string& value)
{
    clear();
    if(value.empty())
        return true;

    const char* ptr = value.c_str();
    Utils::skipWs(ptr);
    SVGLength item;
    while(*ptr)
    {
        if(!SVGLength::parse(ptr, item))
            return false;
        appendItem(to<SVGLength>(item.clone()));
        Utils::skipWsComma(ptr);
    }

    return true;
}

} // namespace lunasvg
