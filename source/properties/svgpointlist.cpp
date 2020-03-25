#include "svgpointlist.h"

namespace lunasvg {

SVGPointList::SVGPointList() :
    SVGListProperty<SVGPoint>(EPropertyTypePointList)
{
}

std::vector<Point> SVGPointList::values() const
{
    std::vector<Point> v(length());
    for(std::size_t i = 0;i < v.size();i++)
        v[i] = at(i)->value();

    return v;
}

SVGProperty* SVGPointList::clone() const
{
    SVGPointList* property = new SVGPointList();
    baseClone(property);

    return property;
}

bool SVGPointList::setValueAsString(const std::string& value)
{
    clear();
    if(value.empty())
        return true;

    const char* ptr = value.c_str();
    Utils::skipWs(ptr);
    SVGPoint item;
    while(*ptr)
    {
        if(!SVGPoint::parse(ptr, item))
            return false;
        appendItem(to<SVGPoint>(item.clone()));
        Utils::skipWsComma(ptr);
    }

    return true;
}

} // namespace lunasvg
