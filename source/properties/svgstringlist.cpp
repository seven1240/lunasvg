#include "svgstringlist.h"

namespace lunasvg {

SVGStringList::SVGStringList() :
    SVGListProperty<SVGString>(EPropertyTypeStringList)
{
}

SVGProperty* SVGStringList::clone() const
{
    SVGStringList* property = new SVGStringList();
    baseClone(property);

    return property;
}

bool SVGStringList::setValueAsString(const std::string& value)
{
    clear();
    if(value.empty())
        return true;

    const char* ptr = value.c_str();
    const char delimiter = ' ';
    Utils::skipWs(ptr);
    while(*ptr)
    {
        const char* start = ptr;
        while(*ptr && *ptr!=delimiter)
            ++ptr;
        SVGString* item = new SVGString;
        item->setValue(std::string(start, ptr));
        appendItem(item);
        Utils::skipWsDelimiter(ptr, delimiter);
    }

    return true;
}

} // namespace lunasvg
