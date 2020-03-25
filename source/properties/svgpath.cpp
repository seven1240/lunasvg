#include "svgpath.h"
#include "pathiterator.h"
#include "pathutils.h"

namespace lunasvg {

SVGPath::SVGPath() :
    SVGProperty(EPropertyTypePath)
{
}

bool SVGPath::parseArcFlag(const char *&ptr, bool &flag)
{
    if(*ptr && *ptr=='0')
        flag = false;
    else if(*ptr && *ptr=='1')
        flag = true;
    else
        return false;

    ++ptr;
    return true;
}

SVGProperty* SVGPath::clone() const
{
    SVGPath* property = new SVGPath();
    property->m_value = m_value;

    return property;
}

bool SVGPath::setValueAsString(const std::string& value)
{
    m_value.reset();
    if(value.empty())
        return true;

    const char* ptr = value.c_str();
    Utils::skipWs(ptr);
    if(!*ptr || !(*ptr=='M' || *ptr=='m'))
        return false;
    char pathCommand = *ptr++;
    float c[6];
    bool f[2];
    while(true)
    {
        Utils::skipWs(ptr);
        switch(pathCommand)
        {
        case 'M':
        case 'm':
            if(!(Utils::parseNumber(ptr, c[0])
                    && Utils::skipWsComma(ptr)
                    && Utils::parseNumber(ptr, c[1])))
                return false;
            m_value.moveTo(c[0], c[1], pathCommand == 'm');
            pathCommand = pathCommand == 'm' ? 'l' : 'L';
            break;
        case 'L':
        case 'l':
            if(!(Utils::parseNumber(ptr, c[0])
                    && Utils::skipWsComma(ptr)
                    && Utils::parseNumber(ptr, c[1])))
                return false;
            m_value.lineTo(c[0], c[1], pathCommand == 'l');
            break;
        case 'Q':
        case 'q':
            if(!(Utils::parseNumber(ptr, c[0])
                    && Utils::skipWsComma(ptr)
                    && Utils::parseNumber(ptr, c[1])
                    && Utils::skipWsComma(ptr)
                    && Utils::parseNumber(ptr, c[2])
                    && Utils::skipWsComma(ptr)
                    && Utils::parseNumber(ptr, c[3])))
                return false;
            m_value.quadTo(c[0], c[1], c[2], c[3], pathCommand == 'q');
            break;
        case 'C':
        case 'c':
            if(!(Utils::parseNumber(ptr, c[0])
                    && Utils::skipWsComma(ptr)
                    && Utils::parseNumber(ptr, c[1])
                    && Utils::skipWsComma(ptr)
                    && Utils::parseNumber(ptr, c[2])
                    && Utils::skipWsComma(ptr)
                    && Utils::parseNumber(ptr, c[3])
                    && Utils::skipWsComma(ptr)
                    && Utils::parseNumber(ptr, c[4])
                    && Utils::skipWsComma(ptr)
                    && Utils::parseNumber(ptr, c[5])))
                return false;
            m_value.cubicTo(c[0], c[1], c[2], c[3], c[4], c[5], pathCommand == 'c');
            break;
        case 'T':
        case 't':
            if(!(Utils::parseNumber(ptr, c[0])
                    && Utils::skipWsComma(ptr)
                    && Utils::parseNumber(ptr, c[1])))
                return false;
            m_value.smoothQuadTo(c[0], c[1], pathCommand == 't');
            break;
        case 'S':
        case 's':
            if(!(Utils::parseNumber(ptr, c[0])
                    && Utils::skipWsComma(ptr)
                    && Utils::parseNumber(ptr, c[1])
                    && Utils::skipWsComma(ptr)
                    && Utils::parseNumber(ptr, c[2])
                    && Utils::skipWsComma(ptr)
                    && Utils::parseNumber(ptr, c[3])))
                return false;
            m_value.smoothCubicTo(c[0], c[1], c[2], c[3], pathCommand == 's');
            break;
        case 'H':
        case 'h':
            if(!Utils::parseNumber(ptr, c[0]))
                return false;
            m_value.horizontalTo(c[0], pathCommand == 'h');
            break;
        case 'V':
        case 'v':
            if(!Utils::parseNumber(ptr, c[0]))
                return false;
            m_value.verticalTo(c[0], pathCommand == 'v');
            break;
        case 'A':
        case 'a':
            if(!(Utils::parseNumber(ptr, c[0])
                    && Utils::skipWsComma(ptr)
                    && Utils::parseNumber(ptr, c[1])
                    && Utils::skipWsComma(ptr)
                    && Utils::parseNumber(ptr, c[2])
                    && Utils::skipWsComma(ptr)
                    && parseArcFlag(ptr, f[0])
                    && Utils::skipWsComma(ptr)
                    && parseArcFlag(ptr, f[1])
                    && Utils::skipWsComma(ptr)
                    && Utils::parseNumber(ptr, c[3])
                    && Utils::skipWsComma(ptr)
                    && Utils::parseNumber(ptr, c[4])))
                return false;
            Utils::pathArcTo(m_value, c[0], c[1], c[2], f[0], f[1], c[3], c[4], pathCommand == 'a');
            break;
        case 'Z':
        case 'z':
            m_value.closePath();
            break;
        default:
            return false;
        }

        if(!Utils::skipWsComma(ptr))
            break;

        if(IS_ALPHA(*ptr))
            pathCommand = *ptr++;
    }

    return true;
}

std::string SVGPath::valueAsString() const
{
    std::string out;

    PathIterator it(m_value);
    float c[6];
    Path::SegType lastSeg = Path::ESegMoveTo;
    while(!it.isDone())
    {
        Path::SegType seg = it.currentSegment(c);
        if(seg!=lastSeg)
            out += ' ';
        switch(seg) {
        case Path::ESegMoveTo:
            out += 'M';
            out += Utils::toString(c[0]);
            out += ' ';
            out += Utils::toString(c[1]);
            break;
        case Path::ESegLineTo:
            out += (lastSeg == Path::ESegLineTo ? ' ' : 'L');
            out += Utils::toString(c[0]);
            out += ' ';
            out += Utils::toString(c[1]);
            break;
        case Path::ESegQuadTo:
            out += (lastSeg == Path::ESegQuadTo ? ' ' : 'Q');
            out += Utils::toString(c[0]);
            out += ' ';
            out += Utils::toString(c[1]);
            out += ' ';
            out += Utils::toString(c[2]);
            out += ' ';
            out += Utils::toString(c[3]);
            break;
        case Path::ESegCubicTo:
            out += (lastSeg == Path::ESegCubicTo ? ' ' : 'C');
            out += Utils::toString(c[0]);
            out += ' ';
            out += Utils::toString(c[1]);
            out += ' ';
            out += Utils::toString(c[2]);
            out += ' ';
            out += Utils::toString(c[3]);
            out += ' ';
            out += Utils::toString(c[4]);
            out += ' ';
            out += Utils::toString(c[5]);
            break;
        case Path::ESegClose:
            out += 'Z';
            break;
        }
        lastSeg = seg;
        it.next();
    }

    return  out;
}

} // namespace lunasvg
