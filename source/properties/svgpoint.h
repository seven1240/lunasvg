#ifndef SVGPOINT_H
#define SVGPOINT_H

#include "svgproperty.h"
#include "point.h"

namespace lunasvg {

class SVGPoint : public SVGProperty
{
public:
    SVGPoint();

    float x() const { return m_value.x; }
    float y() const { return m_value.y; }
    void setX(float x) { m_value.x = x; }
    void setY(float y) { m_value.y = y; }

    void setValue(const Point& value) { m_value = value; }
    const Point& value() const { return  m_value; }

    static bool parse(const char*& ptr, SVGPoint& point);
    bool setValueAsString(const std::string& value);
    std::string valueAsString() const;
    SVGProperty* clone() const;
    static PropertyType classType() { return EPropertyTypePoint; }

private:
    Point m_value;
};

} // namespace lunasvg

#endif // SVGPOINT_H
