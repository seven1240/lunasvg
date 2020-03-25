#ifndef SVGENUMERATION_H
#define SVGENUMERATION_H

#include "svgproperty.h"

#include <vector>

namespace lunasvg {

typedef std::pair<unsigned short, std::string> EnumEntry;
typedef std::vector<EnumEntry> EnumEntryList;

class SVGEnumerationBase : public SVGProperty
{
public:
    void setValue(unsigned short value);
    unsigned short value() const { return m_value; }

    bool setValueAsString(const std::string& value);
    std::string valueAsString() const;
    static PropertyType classType() { return EPropertyTypeEnumeration; }

protected:
    SVGEnumerationBase(const EnumEntryList& entries) :
        SVGProperty(EPropertyTypeEnumeration),
        m_value(0),
        m_entries(entries)
    {}

protected:
    unsigned short m_value;
    const EnumEntryList& m_entries;
};

template<typename Enum> const EnumEntryList& getEnumEntryList();

template<typename T>
class SVGEnumeration : public SVGEnumerationBase
{
public:
    SVGEnumeration() :
        SVGEnumerationBase(getEnumEntryList<T>())
    {}

    T enumValue() const
    {
        return static_cast<T>(m_value);
    }

    void setEnumValue(T value)
    {
        m_value = value;
    }

    SVGProperty* clone() const
    {
        SVGEnumeration<T>* property = new SVGEnumeration<T>();
        property->m_value = m_value;

        return property;
    }
};

template<typename T>
class SVGAnimatedEnumeration : public SVGAnimatedProperty<SVGEnumeration<T>>
{
public:
    SVGAnimatedEnumeration(PropertyID propertyId) :
        SVGAnimatedProperty<SVGEnumeration<T>>(propertyId)
    {}
};

} // namespace lunasvg

#endif // SVGENUMERATION_H
