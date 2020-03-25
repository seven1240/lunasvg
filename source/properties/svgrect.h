#ifndef SVGRECT_H
#define SVGRECT_H

#include "rect.h"
#include "svgproperty.h"

namespace lunasvg {

class SVGRect : public SVGProperty
{
public:
    SVGRect();

    float x() const { return m_value.x; }
    float y() const { return m_value.y; }
    float width() const { return m_value.width; }
    float height() const { return m_value.height; }

    void setX(float x) { m_value.x = x; }
    void setY(float y) { m_value.y = y; }
    void setWidth(float w) { m_value.width = w; }
    void setHeight(float h) { m_value.height = h; }

    void setValue(const Rect& value) { m_value = value; }
    void setValid(bool valid) { m_valid = valid; }
    const Rect& value() const { return  m_value; }
    bool isValid() const { return  m_valid; }

    bool setValueAsString(const std::string&);
    std::string valueAsString() const;
    SVGProperty* clone() const;
    static PropertyType classType() { return EPropertyTypeRect; }

private:
    Rect m_value;
    bool m_valid;
};

typedef SVGAnimatedProperty<SVGRect> SVGAnimatedRect;

class SVGAnimatedViewBoxRect : public SVGAnimatedRect
{
public:
    SVGAnimatedViewBoxRect(PropertyID propertyId);
    bool setBaseValueAsString(const std::string &value);
};

} // namespace lunasvg

#endif // SVGRECT_H
