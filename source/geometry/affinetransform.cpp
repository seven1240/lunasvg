#include "affinetransform.h"
#include "point.h"
#include "rect.h"

#include <cmath>
#include <iostream>

namespace lunasvg
{

AffineTransform::AffineTransform()
{
   setMatrix(1, 0,
             0, 1,
             0, 0); //Identity
}

AffineTransform::AffineTransform(const AffineTransform& transform)
{
   const float* m = transform.m_matrix;
   setMatrix(m[0], m[1],
             m[2], m[3],
             m[4], m[5]);
}

AffineTransform::AffineTransform(float m00, float m10, float m01, float m11, float m02, float m12)
{
   setMatrix(m00, m10,
             m01, m11,
             m02, m12);
}

void AffineTransform::makeIdentity()
{
   setMatrix(1, 0,
             0, 1,
             0, 0);
}

bool AffineTransform::isIdentity() const
{
    return (m_matrix[0] == 1.f && m_matrix[0] == 0.f &&
            m_matrix[0] == 0.f && m_matrix[0] == 1.f &&
            m_matrix[0] == 0.f && m_matrix[0] == 0.f);
}

void AffineTransform::setMatrix(float m00, float m10, float m01, float m11, float m02, float m12)
{
    m_matrix[0] = m00; m_matrix[1] = m10;
    m_matrix[2] = m01; m_matrix[3] = m11;
    m_matrix[4] = m02; m_matrix[5] = m12;
}

void AffineTransform::concatenate(const AffineTransform& transform)
{
    const float* a = m_matrix;
    const float* b = transform.m_matrix;

    float m00 = a[0] * b[0] + a[2] * b[1];
    float m10 = a[1] * b[0] + a[3] * b[1];
    float m01 = a[0] * b[2] + a[2] * b[3];
    float m11 = a[1] * b[2] + a[3] * b[3];
    float m02 = a[0] * b[4] + a[2] * b[5] + a[4];
    float m12 = a[1] * b[4] + a[3] * b[5] + a[5];

    setMatrix(m00, m10,
              m01, m11,
              m02, m12);

}

AffineTransform AffineTransform::getInverse() const
{
    const float* m = m_matrix;
    float det = m[0] * m[3] - m[1] * m[2];

    if (det != 0.f)
    {
        float m00 = m[0] * (1.f / det);
        float m01 = m[1] * (1.f / det);
        float m10 = m[2] * (1.f / det);
        float m11 = m[3] * (1.f / det);
        float m02 = (m[2] *  m[5] - m[3] * m[4]) * (1.f / det);
        float m12 = (m[1] *  m[4] - m[0] * m[5]) * (1.f / det);

        return AffineTransform(m11, -m01,
                               -m10, m00,
                               m02, m12);
    }

    return AffineTransform();
}

AffineTransform AffineTransform::fromRotate(float radians)
{
    float c = std::cos(radians);
    float s = std::sin(radians);

    return AffineTransform(c, s,
                           -s, c,
                           0, 0);
}

AffineTransform AffineTransform::fromRotate(float radians, float cx, float cy)
{
    float c = std::cos(radians);
    float s = std::sin(radians);

    float x = cx * (1 - c) + cy * s;
    float y = cy * (1 - c) - cx * s;

    return AffineTransform(c, s,
                           -s, c,
                           x, y);
}

AffineTransform AffineTransform::fromScale(float sx, float sy)
{
    return AffineTransform(sx, 0,
                           0, sy,
                           0, 0);
}

AffineTransform AffineTransform::fromShear(float shx, float shy)
{
    float x = std::tan(shx);
    float y = std::tan(shy);

    return AffineTransform(1, y,
                           x, 1,
                           0, 0);
}

AffineTransform AffineTransform::fromTranslate(float tx, float ty)
{
    return AffineTransform(1, 0,
                           0, 1,
                           tx, ty);
}

void AffineTransform::rotate(float radians)
{
    concatenate(fromRotate(radians));
}

void AffineTransform::rotate(float radians, float cx, float cy)
{
    concatenate(fromRotate(radians, cx, cy));
}

void AffineTransform::scale(float sx, float sy)
{
    concatenate(fromScale(sx, sy));
}

void AffineTransform::shear(float shx, float shy)
{
    concatenate(fromShear(shx, shy));
}

void AffineTransform::translate(float cx, float cy)
{
    concatenate(fromTranslate(cx, cy));
}

void AffineTransform::map(float x, float y, float& _x, float& _y) const
{
    const float* m = m_matrix;
    _x = x * m[0] + y * m[2] + m[4];
    _y = x * m[1] + y * m[3] + m[5];
}

Point AffineTransform::mapPoint(const Point& point) const
{
    Point p;
    map(point.x, point.y, p.x, p.y);
    return p;
}

Rect AffineTransform::mapRect(const Rect& rect) const
{
    Point p[4];
    p[0].x = rect.x;
    p[0].y = rect.y;
    p[1].x = rect.x + rect.width;
    p[1].y = rect.y;
    p[2].x = rect.x + rect.width;
    p[2].y = rect.y + rect.height;
    p[3].x = rect.x;
    p[3].y = rect.y + rect.height;

    map(p[0].x, p[0].y, p[0].x, p[0].y);
    map(p[1].x, p[1].y, p[1].x, p[1].y);
    map(p[2].x, p[2].y, p[2].x, p[2].y);
    map(p[3].x, p[3].y, p[3].x, p[3].y);

    float xMin = std::numeric_limits<float>::max();
    float yMin = std::numeric_limits<float>::max();
    float xMax = std::numeric_limits<float>::min();
    float yMax = std::numeric_limits<float>::min();

    for(int i = 0;i < 4; i++)
    {
        if(p[i].x < xMin) xMin = p[i].x;
        if(p[i].x > xMax) xMax = p[i].x;
        if(p[i].y < yMin) yMin = p[i].y;
        if(p[i].y > yMax) yMax = p[i].y;
    }

    return Rect(xMin, yMin, xMax-xMin, yMax-yMin);
}

} //namespace lunasvg
