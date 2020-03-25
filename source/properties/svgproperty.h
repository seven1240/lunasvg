#ifndef SVGPROPERTY_H
#define SVGPROPERTY_H

#include "svgpropertyutils.h"
#include "svgparserutils.h"

#include <assert.h>

namespace lunasvg {

enum PropertyType
{
    EPropertyTypeAngle,
    EPropertyTypeColor,
    EPropertyTypeCSSProperty,
    EPropertyTypeCSSPropertyList,
    EPropertyTypeEnumeration,
    EPropertyTypeLength,
    EPropertyTypeLengthList,
    EPropertyTypeNumber,
    EPropertyTypeNumberList,
    EPropertyTypePath,
    EPropertyTypePoint,
    EPropertyTypePointList,
    EPropertyTypePreserveAspectRatio,
    EPropertyTypeRect,
    EPropertyTypeString,
    EPropertyTypeStringList,
    EPropertyTypeTransform,
    EPropertyTypeTransformList,
};

class SVGProperty;

template<typename T>
inline T* to(SVGProperty* property)
{
    return static_cast<T*>(property);
}

template<typename T>
inline const T* to(const SVGProperty* property)
{
    return static_cast<const T*>(property);
}

class SVGProperty
{
public:
    virtual ~SVGProperty();
    virtual bool setValueAsString(const std::string& value) = 0;
    virtual std::string valueAsString() const = 0;
    virtual SVGProperty* clone() const = 0;

    PropertyType propertyType() const { return m_propertyType; }

protected:
    SVGProperty(PropertyType propertyType) : m_propertyType(propertyType) {}

private:
    PropertyType m_propertyType;
};

class SVGAnimatedPropertyBase
{
public:
    virtual ~SVGAnimatedPropertyBase();
    virtual SVGProperty* currentValueBase() const = 0;
    virtual SVGProperty* baseValueBase() const = 0;
    virtual bool setBaseValueAsString(const std::string& value) = 0;
    virtual std::string baseValueAsString() const = 0;
    virtual void setBaseValue(const SVGProperty* value) = 0;
    virtual void setAnimatedValue(const SVGProperty* value) = 0;
    virtual void resetAnimatedValue() = 0;
    virtual void resetBaseValue() = 0;
    virtual bool isBaseSpecified() const = 0;
    virtual bool isAnimating() const = 0;
    virtual void clone(const SVGAnimatedPropertyBase* property) = 0;

    PropertyID propertyId() const { return m_propertyId; }
    PropertyType propertyType() const { return m_propertyType; }
    bool isSpecified() const;

protected:
    SVGAnimatedPropertyBase(PropertyID propertyId, PropertyType propertyType) :
        m_propertyId(propertyId), m_propertyType(propertyType)
    {}

private:
    PropertyID m_propertyId;
    PropertyType m_propertyType;
};

template<typename T>
class SVGAnimatedProperty : public SVGAnimatedPropertyBase
{
public:
    SVGAnimatedProperty(PropertyID propertyId)
        : SVGAnimatedPropertyBase(propertyId, T::classType()),
          m_baseValue(NULL), m_animValue(NULL)
    {
    }

    T* baseValue() const { return m_baseValue; }
    T* currentValue() const { return m_animValue ? m_animValue : m_baseValue; }
    SVGProperty* baseValueBase() const { return baseValue(); }
    SVGProperty* currentValueBase() const { return currentValue(); }
    bool isBaseSpecified() const { return m_baseValue; }
    bool isAnimating() const { return m_animValue; }

    T* ensureBaseValue()
    {
        if(!m_baseValue)
            m_baseValue = new T();
        return m_baseValue;
    }

    void setBaseValue(const SVGProperty* value)
    {
        assert(propertyType() == value->propertyType());
        delete m_baseValue;
        m_baseValue = to<T>(value->clone());
    }

    void setAnimatedValue(const SVGProperty* value)
    {
        assert(propertyType() == value->propertyType());
        delete m_animValue;
        m_animValue = to<T>(value->clone());
    }

    void resetBaseValue()
    {
        delete m_baseValue;
        m_baseValue = NULL;
    }

    void resetAnimatedValue()
    {
        delete m_animValue;
        m_animValue = NULL;
    }

    void clone(const SVGAnimatedPropertyBase* property)
    {
        assert(propertyId() == property->propertyId());
        assert(m_baseValue == NULL);
        assert(m_animValue == NULL);
        if(property->isBaseSpecified())
            m_baseValue = to<T>(property->baseValueBase()->clone());
    }

    virtual std::string baseValueAsString() const
    {
        return m_baseValue ? m_baseValue->valueAsString() : std::string();
    }

    virtual bool setBaseValueAsString(const std::string& value)
    {
        return ensureBaseValue()->setValueAsString(value);
    }

    virtual ~SVGAnimatedProperty()
    {
        delete m_baseValue;
        delete m_animValue;
    }

private:
    T* m_baseValue;
    T* m_animValue;
};

} //namespace lunasvg

#endif // SVGPROPERTY_H
