#include "svgtransform.h"

namespace lunasvg {

SVGTransform::SVGTransform() :
    SVGProperty(EPropertyTypeTransform),
    m_transformType(ETransformTypeUnknown),
    m_angle(0)
{
}

void SVGTransform::setMatrix(const AffineTransform& matrix)
{
    m_transformType = ETransformTypeMatrix;
    m_angle = 0;
    m_center = Point();
    m_matrix = matrix;
}

void SVGTransform::setRotate(float angle, float cx, float cy)
{
    m_transformType = ETransformTypeRotate;
    m_angle = angle;
    m_center = Point(cx, cy);
    m_matrix = AffineTransform::fromRotate(angle*3.141592654f/180, cx, cy);
}

void SVGTransform::setScale(float sx, float sy)
{
    m_transformType = ETransformTypeScale;
    m_angle = 0;
    m_center = Point();
    m_matrix = AffineTransform::fromScale(sx, sy);
}

void SVGTransform::setSkewX(float angle)
{
    m_transformType = ETransformTypeSkewX;
    m_angle = angle;
    m_center = Point();
    m_matrix = AffineTransform::fromShear(angle*3.141592654f/180, 0);
}

void SVGTransform::setSkewY(float angle)
{
    m_transformType = ETransformTypeSkewY;
    m_angle = angle;
    m_center = Point();
    m_matrix = AffineTransform::fromShear(0, angle*3.141592654f/180);
}

void SVGTransform::setTranslate(float tx, float ty)
{
    m_transformType = ETransformTypeTranslate;
    m_angle = 0;
    m_center = Point();
    m_matrix = AffineTransform::fromTranslate(tx, ty);
}

bool SVGTransform::parse(const char*& ptr, SVGTransform& transform)
{
    TransformType type = ETransformTypeUnknown;
    int required = 0;
    int optional = 0;
    if(Utils::skipDesc(ptr, "matrix", 6))
    {
        type = ETransformTypeMatrix;
        required = 6;
        optional = 0;
    }
    else if(Utils::skipDesc(ptr, "rotate", 6))
    {
        type = ETransformTypeRotate;
        required = 1;
        optional = 2;
    }
    else if(Utils::skipDesc(ptr, "scale", 5))
    {
        type = ETransformTypeScale;
        required = 1;
        optional = 1;
    }
    else if(Utils::skipDesc(ptr, "skewX", 5))
    {
        type = ETransformTypeSkewX;
        required = 1;
        optional = 0;
    }
    else if(Utils::skipDesc(ptr, "skewY", 5))
    {
        type = ETransformTypeSkewY;
        required = 1;
        optional = 0;
    }
    else if(Utils::skipDesc(ptr, "translate", 9))
    {
        type = ETransformTypeTranslate;
        required = 1;
        optional = 1;
    }
    else
        return false;

    if(!Utils::skipWs(ptr) || *ptr!='(')
        return false;
    ++ptr;

    float values[] = {0, 0, 0, 0, 0, 0};
    int count = 0;
    int maxCount = required + optional;
    Utils::skipWs(ptr);
    while(count < maxCount)
    {
        if(!Utils::parseNumber(ptr, values[count]))
            break;
        ++count;
        Utils::skipWsComma(ptr);
    }

    if(!*ptr || *ptr!=')' || !(count==required || count==maxCount))
        return false;
    ++ptr;

    switch(type)
    {
    case ETransformTypeMatrix:
        transform.setMatrix(AffineTransform(values[0], values[1], values[2], values[3], values[4], values[5]));
        break;
    case ETransformTypeRotate:
        if(count == 1)
            transform.setRotate(values[0], 0, 0);
        else
            transform.setRotate(values[0], values[1], values[2]);
        break;
    case ETransformTypeScale:
        if(count == 1)
            transform.setScale(values[0], values[0]);
        else
            transform.setScale(values[0], values[1]);
        break;
    case ETransformTypeSkewX:
        transform.setSkewX(values[0]);
        break;
    case ETransformTypeSkewY:
        transform.setSkewY(values[0]);
        break;
    case ETransformTypeTranslate:
        if(count == 1)
            transform.setTranslate(values[0], 0);
        else
            transform.setTranslate(values[0], values[1]);
        break;
    default:
        break;
    }

    return true;
}

SVGProperty* SVGTransform::clone() const
{
    SVGTransform* property = new SVGTransform();
    property->m_transformType = m_transformType;
    property->m_angle = m_angle;
    property->m_center = m_center;
    property->m_matrix = m_matrix;

    return property;
}

bool SVGTransform::setValueAsString(const std::string& value)
{
    if(value.empty())
    {
        m_transformType = ETransformTypeMatrix;
        m_angle = 0;
        m_center = Point();
        m_matrix.makeIdentity();
        return true;
    }

    const char* ptr = value.c_str();
    if(Utils::skipWs(ptr)
            && parse(ptr, *this)
            && !Utils::skipWs(ptr))
        return true;

    m_transformType = ETransformTypeUnknown;
    m_angle = 0;
    m_center = Point();
    m_matrix.makeIdentity();
    return false;
}

std::string SVGTransform::valueAsString() const
{
    std::string out;

    const float* m = m_matrix.getMatrix();
    switch(m_transformType)
    {
    case ETransformTypeMatrix:
        out += "matrix(";
        out += Utils::toString(m[0]);
        out += ' ';
        out += Utils::toString(m[1]);
        out += ' ';
        out += Utils::toString(m[2]);
        out += ' ';
        out += Utils::toString(m[3]);
        out += ' ';
        out += Utils::toString(m[4]);
        out += ' ';
        out += Utils::toString(m[5]);
        out += ')';
        break;
    case ETransformTypeRotate:
        out += "rotate(";
        out += Utils::toString(m_angle);
        if(m_center.x!=0.f || m_center.y!=0.f)
        {
            out += ' ';
            out += Utils::toString(m_center.x);
            out += ' ';
            out += Utils::toString(m_center.y);
        }
        out += ')';
        break;
    case ETransformTypeScale:
        out += "scale(";
        out += Utils::toString(m[0]);
        out += ' ';
        out += Utils::toString(m[3]);
        out += ')';
        break;
    case ETransformTypeSkewX:
        out += "skewX(";
        out += Utils::toString(m_angle);
        out += ')';
        break;
    case ETransformTypeSkewY:
        out += "skewY(";
        out += Utils::toString(m_angle);
        out += ')';
        break;
    case ETransformTypeTranslate:
        out += "translate(";
        out += Utils::toString(m[4]);
        out += ' ';
        out += Utils::toString(m[5]);
        out += ')';
        break;
    default:
        break;
    }

    return  out;
}

} // namespace lunasvg
