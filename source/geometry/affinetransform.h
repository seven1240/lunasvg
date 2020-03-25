#ifndef AFFINETRANSFORM_H
#define AFFINETRANSFORM_H

namespace lunasvg
{

class Point;
class Rect;

class AffineTransform
{
public:
    AffineTransform();
    AffineTransform(const AffineTransform& transform);
    AffineTransform(float m00, float m10, float m01, float m11, float m02, float m12);

    void makeIdentity();
    void setMatrix(float m00, float m10, float m01, float m11, float m02, float m12);
    void concatenate(const AffineTransform& transform);
    void map(float x, float y, float& _x, float& _y) const;
    Point mapPoint(const Point& point) const;
    Rect mapRect(const Rect& rect) const;
    AffineTransform getInverse() const;

    void rotate(float radians);
    void rotate(float radians, float cx, float cy);
    void scale(float sx, float sy);
    void shear(float shx, float shy);
    void translate(float cx, float cy);

    static AffineTransform fromRotate(float radians);
    static AffineTransform fromRotate(float radians, float cx, float cy);
    static AffineTransform fromScale(float sx, float sy);
    static AffineTransform fromShear(float shx, float shy);
    static AffineTransform fromTranslate(float tx, float ty);

    bool isIdentity() const;
    float determinant() const;
    const float* getMatrix() const;

private:
    float m_matrix[2*3];
};

inline const float* AffineTransform::getMatrix() const
{
   return m_matrix;
}

} //namespace lunasvg

#endif //AFFINETRANSFORM_H
