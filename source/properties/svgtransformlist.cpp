#include "svgtransformlist.h"

namespace lunasvg {

SVGTransformList::SVGTransformList() :
    SVGListProperty<SVGTransform>(EPropertyTypeTransformList)
{
}

AffineTransform SVGTransformList::consolidate() const
{
    AffineTransform matrix;
    for(unsigned i = 0;i < length(); i++)
        matrix.concatenate(at(i)->matrix());
    return matrix;
}

SVGProperty* SVGTransformList::clone() const
{
    SVGTransformList* property = new SVGTransformList();
    baseClone(property);

    return property;
}

bool SVGTransformList::setValueAsString(const std::string& value)
{
    clear();
    if(value.empty())
        return true;

    const char* ptr = value.c_str();
    Utils::skipWs(ptr);
    SVGTransform item;
    while(*ptr)
    {
        if(!SVGTransform::parse(ptr, item))
            return false;
        appendItem(to<SVGTransform>(item.clone()));
        Utils::skipWsComma(ptr);
    }

    return true;
}

} // namespace lunasvg
