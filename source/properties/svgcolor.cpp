#include "svgcolor.h"
#include "rendercontext.h"
#include "svgpaintelement.h"
#include "svgdocumentimpl.h"

namespace lunasvg {

static const struct
{
   std::string name;
   Rgb rgb;
} colormap[] = {
    {"aliceblue", Rgb(0xF0F8FFFF)},
    {"antiquewhite", Rgb(0xFAEBD7FF)},
    {"aqua", Rgb(0x00FFFFFF)},
    {"aquamarine", Rgb(0x7FFFD4FF)},
    {"azure", Rgb(0xF0FFFFFF)},
    {"beige", Rgb(0xF5F5DCFF)},
    {"bisque", Rgb(0xFFE4C4FF)},
    {"black", Rgb(0x000000FF)},
    {"blanchedalmond", Rgb(0xFFEBCDFF)},
    {"blue", Rgb(0x0000FFFF)},
    {"blueviolet", Rgb(0x8A2BE2FF)},
    {"brown", Rgb(0xA52A2AFF)},
    {"burlywood", Rgb(0xDEB887FF)},
    {"cadetblue", Rgb(0x5F9EA0FF)},
    {"chartreuse", Rgb(0x7FFF00FF)},
    {"chocolate", Rgb(0xD2691EFF)},
    {"coral", Rgb(0xFF7F50FF)},
    {"cornflowerblue", Rgb(0x6495EDFF)},
    {"cornsilk", Rgb(0xFFF8DCFF)},
    {"crimson", Rgb(0xDC143CFF)},
    {"cyan", Rgb(0x00FFFFFF)},
    {"darkblue", Rgb(0x00008BFF)},
    {"darkcyan", Rgb(0x008B8BFF)},
    {"darkgoldenrod", Rgb(0xB8860BFF)},
    {"darkgray", Rgb(0xA9A9A9FF)},
    {"darkgreen", Rgb(0x006400FF)},
    {"darkgrey", Rgb(0xA9A9A9FF)},
    {"darkkhaki", Rgb(0xBDB76BFF)},
    {"darkmagenta", Rgb(0x8B008BFF)},
    {"darkolivegreen", Rgb(0x556B2FFF)},
    {"darkorange", Rgb(0xFF8C00FF)},
    {"darkorchid", Rgb(0x9932CCFF)},
    {"darkred", Rgb(0x8B0000FF)},
    {"darksalmon", Rgb(0xE9967AFF)},
    {"darkseagreen", Rgb(0x8FBC8FFF)},
    {"darkslateblue", Rgb(0x483D8BFF)},
    {"darkslategray", Rgb(0x2F4F4FFF)},
    {"darkslategrey", Rgb(0x2F4F4FFF)},
    {"darkturquoise", Rgb(0x00CED1FF)},
    {"darkviolet", Rgb(0x9400D3FF)},
    {"deeppink", Rgb(0xFF1493FF)},
    {"deepskyblue", Rgb(0x00BFFFFF)},
    {"dimgray", Rgb(0x696969FF)},
    {"dimgrey", Rgb(0x696969FF)},
    {"dodgerblue", Rgb(0x1E90FFFF)},
    {"firebrick", Rgb(0xB22222FF)},
    {"floralwhite", Rgb(0xFFFAF0FF)},
    {"forestgreen", Rgb(0x228B22FF)},
    {"fuchsia", Rgb(0xFF00FFFF)},
    {"gainsboro", Rgb(0xDCDCDCFF)},
    {"ghostwhite", Rgb(0xF8F8FFFF)},
    {"gold", Rgb(0xFFD700FF)},
    {"goldenrod", Rgb(0xDAA520FF)},
    {"gray", Rgb(0x808080FF)},
    {"green", Rgb(0x008000FF)},
    {"greenyellow", Rgb(0xADFF2FFF)},
    {"grey", Rgb(0x808080FF)},
    {"honeydew", Rgb(0xF0FFF0FF)},
    {"hotpink", Rgb(0xFF69B4FF)},
    {"indianred", Rgb(0xCD5C5CFF)},
    {"indigo", Rgb(0x4B0082FF)},
    {"ivory", Rgb(0xFFFFF0FF)},
    {"khaki", Rgb(0xF0E68CFF)},
    {"lavender", Rgb(0xE6E6FAFF)},
    {"lavenderblush", Rgb(0xFFF0F5FF)},
    {"lawngreen", Rgb(0x7CFC00FF)},
    {"lemonchiffon", Rgb(0xFFFACDFF)},
    {"lightblue", Rgb(0xADD8E6FF)},
    {"lightcoral", Rgb(0xF08080FF)},
    {"lightcyan", Rgb(0xE0FFFFFF)},
    {"lightgoldenrodyellow", Rgb(0xFAFAD2FF)},
    {"lightgray", Rgb(0xD3D3D3FF)},
    {"lightgreen", Rgb(0x90EE90FF)},
    {"lightgrey", Rgb(0xD3D3D3FF)},
    {"lightpink", Rgb(0xFFB6C1FF)},
    {"lightsalmon", Rgb(0xFFA07AFF)},
    {"lightseagreen", Rgb(0x20B2AAFF)},
    {"lightskyblue", Rgb(0x87CEFAFF)},
    {"lightslategray", Rgb(0x778899FF)},
    {"lightslategrey", Rgb(0x778899FF)},
    {"lightsteelblue", Rgb(0xB0C4DEFF)},
    {"lightyellow", Rgb(0xFFFFE0FF)},
    {"lime", Rgb(0x00FF00FF)},
    {"limegreen", Rgb(0x32CD32FF)},
    {"linen", Rgb(0xFAF0E6FF)},
    {"magenta", Rgb(0xFF00FFFF)},
    {"maroon", Rgb(0x800000FF)},
    {"mediumaquamarine", Rgb(0x66CDAAFF)},
    {"mediumblue", Rgb(0x0000CDFF)},
    {"mediumorchid", Rgb(0xBA55D3FF)},
    {"mediumpurple", Rgb(0x9370DBFF)},
    {"mediumseagreen", Rgb(0x3CB371FF)},
    {"mediumslateblue", Rgb(0x7B68EEFF)},
    {"mediumspringgreen", Rgb(0x00FA9AFF)},
    {"mediumturquoise", Rgb(0x48D1CCFF)},
    {"mediumvioletred", Rgb(0xC71585FF)},
    {"midnightblue", Rgb(0x191970FF)},
    {"mintcream", Rgb(0xF5FFFAFF)},
    {"mistyrose", Rgb(0xFFE4E1FF)},
    {"moccasin", Rgb(0xFFE4B5FF)},
    {"navajowhite", Rgb(0xFFDEADFF)},
    {"navy", Rgb(0x000080FF)},
    {"oldlace", Rgb(0xFDF5E6FF)},
    {"olive", Rgb(0x808000FF)},
    {"olivedrab", Rgb(0x6B8E23FF)},
    {"orange", Rgb(0xFFA500FF)},
    {"orangered", Rgb(0xFF4500FF)},
    {"orchid", Rgb(0xDA70D6FF)},
    {"palegoldenrod", Rgb(0xEEE8AAFF)},
    {"palegreen", Rgb(0x98FB98FF)},
    {"paleturquoise", Rgb(0xAFEEEEFF)},
    {"palevioletred", Rgb(0xDB7093FF)},
    {"papayawhip", Rgb(0xFFEFD5FF)},
    {"peachpuff", Rgb(0xFFDAB9FF)},
    {"peru", Rgb(0xCD853FFF)},
    {"pink", Rgb(0xFFC0CBFF)},
    {"plum", Rgb(0xDDA0DDFF)},
    {"powderblue", Rgb(0xB0E0E6FF)},
    {"purple", Rgb(0x800080FF)},
    {"rebeccapurple", Rgb(0x663399FF)},
    {"red", Rgb(0xFF0000FF)},
    {"rosybrown", Rgb(0xBC8F8FFF)},
    {"royalblue", Rgb(0x4169E1FF)},
    {"saddlebrown", Rgb(0x8B4513FF)},
    {"salmon", Rgb(0xFA8072FF)},
    {"sandybrown", Rgb(0xF4A460FF)},
    {"seagreen", Rgb(0x2E8B57FF)},
    {"seashell", Rgb(0xFFF5EEFF)},
    {"sienna", Rgb(0xA0522DFF)},
    {"silver", Rgb(0xC0C0C0FF)},
    {"skyblue", Rgb(0x87CEEBFF)},
    {"slateblue", Rgb(0x6A5ACDFF)},
    {"slategray", Rgb(0x708090FF)},
    {"slategrey", Rgb(0x708090FF)},
    {"snow", Rgb(0xFFFAFAFF)},
    {"springgreen", Rgb(0x00FF7FFF)},
    {"steelblue", Rgb(0x4682B4FF)},
    {"tan", Rgb(0xD2B48CFF)},
    {"teal", Rgb(0x008080FF)},
    {"thistle", Rgb(0xD8BFD8FF)},
    {"tomato", Rgb(0xFF6347FF)},
    {"turquoise", Rgb(0x40E0D0FF)},
    {"violet", Rgb(0xEE82EEFF)},
    {"wheat", Rgb(0xF5DEB3FF)},
    {"white", Rgb(0xFFFFFFFF)},
    {"whitesmoke", Rgb(0xF5F5F5FF)},
    {"yellow", Rgb(0xFFFF00FF)},
    {"yellowgreen", Rgb(0x9ACD32FF)},
    {"", 0}
};

SVGColor::SVGColor() :
    SVGProperty(EPropertyTypeColor),
    m_colorType(EColorTypeRgb)
{
}

Paint SVGColor::getPaint(const RenderState& state) const
{
    switch(m_colorType)
    {
    case EColorTypeNone:
        return Paint();
    case EColorTypeCurrentColor:
        return  Paint(state.color);
    case EColorTypeRgb:
        return Paint(m_value);
    }

    return Paint();
}

SVGProperty* SVGColor::clone() const
{
    SVGColor* property = new SVGColor();
    property->m_colorType = m_colorType;
    property->m_value = m_value;

    return property;
}

bool SVGColor::setValueAsString(const std::string& value)
{
    m_colorType = EColorTypeRgb;
    m_value = Rgb(0, 0, 0, 255);
    if(value.empty())
        return true;

    const char* ptr = value.c_str();
    if(Utils::skipDesc(ptr, "#", 1))
    {
        const char* start = ptr;
        while(*ptr && Utils::isIntegralDigit(*ptr, 16))
            ++ptr;
        std::ptrdiff_t pos = ptr - start;
        unsigned int hex = 0;
        if(pos == 3)
        {
            std::string hex_str;
            hex_str.reserve(8);
            hex_str.append(2, start[0]);
            hex_str.append(2, start[1]);
            hex_str.append(2, start[2]);
            start = hex_str.c_str();
            Utils::parseInteger(start, hex, 16);
        }
        else if(pos == 6)
        {
            Utils::parseInteger(start, hex, 16);
        }
        else
        {
            return false;
        }

        m_value.r = (hex&0xff0000)>>16;
        m_value.g = (hex&0x00ff00)>>8;
        m_value.b = (hex&0x0000ff)>>0;
    }
    else if(Utils::skipDesc(ptr, "none", 4))
    {
        m_colorType = EColorTypeNone;
        m_value.a = 0;
    }
    else if(Utils::skipDesc(ptr, "currentColor", 12))
    {
        m_colorType = EColorTypeCurrentColor;
        m_value.a = 0;
    }
    else if(Utils::skipDesc(ptr, "rgb(", 4))
    {
        float r, g, b;
        Utils::skipWs(ptr);
        if(!Utils::parseNumber(ptr, r))
            return false;
        if(Utils::skipDesc(ptr, "%", 1))
            r *= 2.55f;
        Utils::skipWsComma(ptr);
        if(!Utils::parseNumber(ptr, g))
            return false;
        if(Utils::skipDesc(ptr, "%", 1))
            g *= 2.55f;
        Utils::skipWsComma(ptr);
        if(!Utils::parseNumber(ptr, b))
            return false;
        if(Utils::skipDesc(ptr, "%", 1))
            b *= 2.55f;
        Utils::skipWs(ptr);
        if(!Utils::skipDesc(ptr, ")", 1))
            return false;
        m_value.r = (static_cast<unsigned char>(r));
        m_value.g = (static_cast<unsigned char>(g));
        m_value.b = (static_cast<unsigned char>(b));
    }
    else
    {
        const char* start = ptr;
        while(*ptr && IS_ID(*ptr))
            ++ptr;
        std::string value(start, ptr);
        for(int i = 0;colormap[i].name.length();i++)
        {
            if(value == colormap[i].name)
            {
                m_value = colormap[i].rgb;
                break;
            }
        }
    }

    if(Utils::skipWs(ptr))
    {
        m_colorType = EColorTypeRgb;
        m_value = Rgb(0, 0, 0, 255);
        return false;
    }

    return true;
}

std::string SVGColor::valueAsString() const
{
    if(m_colorType == EColorTypeNone)
        return "none";
    if(m_colorType == EColorTypeCurrentColor)
        return  "currentColor";

    for(int i = 0;!colormap[i].name.empty();i++)
        if(m_value == colormap[i].rgb)
           return colormap[i].name;
    char buf[16];
    snprintf(buf, 16, "#%02x%02x%02x", int(m_value.r), int(m_value.g), int(m_value.b));
    return buf;
}

SVGPaint::~SVGPaint()
{
    delete m_fallbackColor;
}

SVGPaint::SVGPaint() :
    m_fallbackColor(NULL)
{
}

Paint SVGPaint::getPaint(const RenderState& state) const
{
    if(m_url.empty())
        return SVGColor::getPaint(state);

    SVGElementImpl* ref = state.element->owner()->impl()->resolveIRI(m_url);
    if(ref && ref->isSVGPaintElement())
        return to<SVGPaintElement>(ref)->getPaint(state);
    return m_fallbackColor ? m_fallbackColor->getPaint(state) : Paint();
}

bool SVGPaint::setValueAsString(const std::string &value)
{
    delete m_fallbackColor;
    m_fallbackColor = NULL;
    m_url.clear();
    if(value.empty())
        return true;

    const char* ptr = value.c_str();
    Utils::skipWs(ptr);
    if(Utils::skipDesc(ptr, "url(", 4))
    {
        const char* closeBracket = strstr(ptr, ")");
        if(!closeBracket)
            return false;

        m_url.assign(ptr, closeBracket);
        ptr += m_url.length() + 1;
        if(Utils::skipWs(ptr))
        {
            m_fallbackColor = new SVGColor();
            return m_fallbackColor->setValueAsString(ptr);
        }

        return true;
    }

    return SVGColor::setValueAsString(ptr);
}

std::string SVGPaint::valueAsString() const
{
    if(m_url.empty())
        return SVGColor::valueAsString();

    return "url(" + m_url + ")" + (m_fallbackColor ? m_fallbackColor->valueAsString() : KEmptyString);
}

SVGProperty *SVGPaint::clone() const
{
    SVGPaint* property = new SVGPaint();
    property->m_colorType = m_colorType;
    property->m_value = m_value;
    if(m_fallbackColor)
        property->m_fallbackColor = to<SVGColor>(m_fallbackColor->clone());

    return property;
}

} // namespace lunasvg
