#ifndef SVGTRANSFORM_H
#define SVGTRANSFORM_H

#include "svgproperty.h"
#include "affinetransform.h"
#include "point.h"

namespace lunasvg {

enum TransformType
{
    ETransformTypeUnknown,
    ETransformTypeMatrix,
    ETransformTypeRotate,
    ETransformTypeScale,
    ETransformTypeSkewX,
    ETransformTypeSkewY,
    ETransformTypeTranslate
};

class SVGTransform : public SVGProperty
{
public:
    SVGTransform();

    void setMatrix(const AffineTransform& matrix);
    void setRotate(float angle, float cx, float cy);
    void setScale(float sx, float sy);
    void setSkewX(float angle);
    void setSkewY(float angle);
    void setTranslate(float tx, float ty);

    TransformType transformType() const { return m_transformType; }
    float angle() const { return m_angle; }
    const Point& center() const { return m_center; }
    const AffineTransform& matrix() const { return  m_matrix; }

    static bool parse(const char*& ptr, SVGTransform& transform);
    bool setValueAsString(const std::string&value);
    std::string valueAsString() const;
    SVGProperty* clone() const;
    static PropertyType classType() { return EPropertyTypeTransform; }

private:
    TransformType m_transformType;
    float m_angle;
    Point m_center;
    AffineTransform m_matrix;
};

} // namespace lunasvg

#endif // SVGTRANSFORM_H
