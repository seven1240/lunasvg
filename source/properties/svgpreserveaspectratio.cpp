#include "svgpreserveaspectratio.h"
#include "affinetransform.h"
#include "rect.h"

namespace lunasvg {

SVGPreserveAspectRatio::SVGPreserveAspectRatio() :
    SVGProperty(EPropertyTypePreserveAspectRatio),
    m_align(EXMidYMid),
    m_scale(EMeet)
{
}

AffineTransform SVGPreserveAspectRatio::getMatrix(const Rect &viewPort, const Rect &viewBox) const
{
    AffineTransform matrix;

    matrix.translate(viewPort.x, viewPort.y);
    if(viewBox.height==0.f || viewBox.width==0.f)
        return matrix;

    float scaleX = viewPort.width  / viewBox.width;
    float scaleY = viewPort.height  / viewBox.height;

    if(scaleX== 0.f || scaleY==0.f)
        return matrix;

    float transX = -viewBox.x;
    float transY = -viewBox.y;

    if(m_align == ENone)
    {
        matrix.scale(scaleX, scaleY);
        matrix.translate(transX, transY);
        return matrix;
    }

    float scale = (m_scale == ESlice) ? std::max(scaleX, scaleY) : std::min(scaleX, scaleY);

    float viewH = viewPort.height / scale;
    float viewW = viewPort.width / scale;

    switch(m_align)
    {
    case EXMidYMin:
    case EXMidYMid:
    case EXMidYMax:
        transX -= (viewBox.width - viewW) * .5f;
        break;
    case EXMaxYMin:
    case EXMaxYMid:
    case EXMaxYMax:
        transX -= (viewBox.width - viewW);
        break;
    default:
        break;
    }

    switch(m_align)
    {
    case EXMinYMid:
    case EXMidYMid:
    case EXMaxYMid:
        transY -= (viewBox.height - viewH) * .5f;
        break;
    case EXMinYMax:
    case EXMidYMax:
    case EXMaxYMax:
        transY -= (viewBox.height - viewH);
        break;
    default:
        break;
    }

    matrix.scale(scale, scale);
    matrix.translate(transX, transY);

    return matrix;
}

const SVGPreserveAspectRatio &SVGPreserveAspectRatio::defaultValue()
{
    static SVGPreserveAspectRatio value;
    return value;
}

SVGProperty* SVGPreserveAspectRatio::clone() const
{
    SVGPreserveAspectRatio* property = new SVGPreserveAspectRatio();
    property->m_align = m_align;
    property->m_scale = m_scale;

    return property;
}

bool SVGPreserveAspectRatio::setValueAsString(const std::string& value)
{
    if(value.empty())
    {
        m_align = EXMidYMid;
        m_scale = EMeet;
        return true;
    }

    const char* ptr = value.c_str();
    if(Utils::skipWs(ptr))
    {
        if(Utils::skipDesc(ptr, "none", 4))
            m_align = ENone;
        else if(Utils::skipDesc(ptr, "xMinYMin", 8))
            m_align = EXMinYMin;
        else if(Utils::skipDesc(ptr, "xMidYMin", 8))
            m_align = EXMidYMin;
        else if(Utils::skipDesc(ptr, "xMaxYMin", 8))
            m_align = EXMaxYMin;
        else if(Utils::skipDesc(ptr, "xMinYMid", 8))
            m_align = EXMinYMid;
        else if(Utils::skipDesc(ptr, "xMidYMid", 8))
            m_align = EXMidYMid;
        else if(Utils::skipDesc(ptr, "xMaxYMid", 8))
            m_align = EXMaxYMid;
        else if(Utils::skipDesc(ptr, "xMinYMax", 8))
            m_align = EXMinYMax;
        else if(Utils::skipDesc(ptr, "xMidYMax", 8))
            m_align = EXMidYMax;
        else if(Utils::skipDesc(ptr, "xMaxYMax", 8))
            m_align = EXMaxYMax;
        else
            return false;

        if(Utils::skipWs(ptr))
        {
            if(Utils::skipDesc(ptr, "meet", 4))
                m_scale = EMeet;
            if(Utils::skipDesc(ptr, "slice", 5))
                m_scale = ESlice;
        }

        if(!Utils::skipWs(ptr))
        {
            if(m_align == ENone)
                m_scale = EMeet;
            return true;
        }
    }

    m_align = EXMidYMid;
    m_scale = EMeet;
    return false;
}

std::string SVGPreserveAspectRatio::valueAsString() const
{
    std::string out;

    switch(m_align)
    {
    case ENone:
        out += "none";
        break;
    case EXMinYMin:
        out += "xMinYMin";
        break;
    case EXMidYMin:
        out += "xMidYMin";
        break;
    case EXMaxYMin:
        out += "xMaxYMin";
        break;
    case EXMinYMid:
        out += "xMinYMid";
        break;
    case EXMidYMid:
        out += "xMidYMid";
        break;
    case EXMaxYMid:
        out += "xMaxYMid";
        break;
    case EXMinYMax:
        out += "xMinYMax";
        break;
    case EXMidYMax:
        out += "xMidYMax";
        break;
    case EXMaxYMax:
        out += "xMaxYMax";
        break;
    }

    if(m_align != ENone)
    {
        out += ' ';
        if(m_scale == EMeet)
            out += "meet";
        else
            out += "slice";
    }

    return  out;
}

} // namespace lunasvg
