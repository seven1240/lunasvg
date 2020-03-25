#include "svgnumberlist.h"

namespace lunasvg {

SVGNumberList::SVGNumberList() :
    SVGListProperty<SVGNumber>(EPropertyTypeNumberList)
{
}

SVGProperty* SVGNumberList::clone() const
{
    SVGNumberList* property = new SVGNumberList();
    baseClone(property);

    return property;
}

bool SVGNumberList::setValueAsString(const std::string& value)
{
    clear();
    if(value.empty())
        return true;

    const char* ptr = value.c_str();
    Utils::skipWs(ptr);
    while(*ptr)
    {
        float number = 0;
        if(!Utils::parseNumber(ptr, number))
            return false;
        SVGNumber* item = new SVGNumber;
        item->setValue(number);
        appendItem(item);
        Utils::skipWsComma(ptr);
    }

    return true;
}

} // namespace lunasvg
