#include "svgpropertyutils.h"
#include "svgparserutils.h"
#include "svgstring.h"

namespace lunasvg {

namespace Utils {

static const struct
{
    std::string name;
    PropertyID id;
} propertymap[] = {
    {"", EPropertyIdUnknown},
    {"accumulate", EPropertyIdAccumulate},
    {"additive", EPropertyIdAdditive},
    {"attributeName", EPropertyIdAttributeName},
    {"attributeType", EPropertyIdAttributeType},
    {"baseProfile", EPropertyIdBaseProfile},
    {"begin", EPropertyIdBegin},
    {"by", EPropertyIdBy},
    {"calcMode", EPropertyIdCalcMode},
    {"class", EPropertyIdClass},
    {"clipPathUnits", EPropertyIdClipPathUnits},
    {"cx", EPropertyIdCx},
    {"cy", EPropertyIdCy},
    {"d", EPropertyIdD},
    {"dur", EPropertyIdDur},
    {"dx", EPropertyIdDx},
    {"dy", EPropertyIdDy},
    {"end", EPropertyIdEnd},
    {"fill", EPropertyIdFill},
    {"from", EPropertyIdFrom},
    {"fx", EPropertyIdFx},
    {"fy", EPropertyIdFy},
    {"fr", EPropertyIdFr},
    {"gradientTransform", EPropertyIdGradientTransform},
    {"gradientUnits", EPropertyIdGradientUnits},
    {"height", EPropertyIdHeight},
    {"href", EPropertyIdHref},
    {"id", EPropertyIdId},
    {"keyPoints", EPropertyIdKeyPoints},
    {"keySplines", EPropertyIdKeySplines},
    {"keyTimes", EPropertyIdKeyTimes},
    {"lang", EPropertyIdLang},
    {"markerHeight", EPropertyIdMarkerHeight},
    {"markerUnits", EPropertyIdMarkerUnits},
    {"markerWidth", EPropertyIdMarkerWidth},
    {"maskContentUnits", EPropertyIdMaskContentUnits},
    {"maskUnits", EPropertyIdMaskUnits},
    {"max", EPropertyIdMax},
    {"media", EPropertyIdMedia},
    {"min", EPropertyIdMin},
    {"offset", EPropertyIdOffset},
    {"orient", EPropertyIdOrient},
    {"origin", EPropertyIdOrigin},
    {"path", EPropertyIdPath},
    {"patternContentUnits", EPropertyIdPatternContentUnits},
    {"patternTransform", EPropertyIdPatternTransform},
    {"patternUnits", EPropertyIdPatternUnits},
    {"points", EPropertyIdPoints},
    {"preserveAspectRatio", EPropertyIdPreserveAspectRatio},
    {"r", EPropertyIdR},
    {"refX", EPropertyIdRefX},
    {"refY", EPropertyIdRefY},
    {"repeatCount", EPropertyIdRepeatCount},
    {"repeatDur", EPropertyIdRepeatDur},
    {"requiredExtensions", EPropertyIdRequiredExtensions},
    {"restart", EPropertyIdRestart},
    {"rotate", EPropertyIdRotate},
    {"rx", EPropertyIdRx},
    {"ry", EPropertyIdRy},
    {"spreadMethod", EPropertyIdSpreadMethod},
    {"startOffset", EPropertyIdStartOffset},
    {"style", EPropertyIdStyle},
    {"systemLanguage", EPropertyIdSystemLanguage},
    {"title", EPropertyIdTitle},
    {"to", EPropertyIdTo},
    {"transform", EPropertyIdTransform},
    {"type", EPropertyIdType},
    {"values", EPropertyIdValues},
    {"version", EPropertyIdVersion},
    {"viewBox", EPropertyIdViewBox},
    {"width", EPropertyIdWidth},
    {"x", EPropertyIdX},
    {"x1", EPropertyIdX1},
    {"x2", EPropertyIdX2},
    {"y", EPropertyIdY},
    {"y1", EPropertyIdY1},
    {"y2", EPropertyIdY2},
    {"zoomAndPan", EPropertyIdZoomAndPan},
    {"", EPropertyLastId}
};

static const struct
{
    std::string name;
    CSSPropertyID id;
} csspropertymap[] = {
    {"", CSSPropertyIdUnknown},
    {"clip", CSSPropertyIdClip},
    {"clip-path", CSSPropertyIdClip_Path},
    {"clip-rule", CSSPropertyIdClip_Rule},
    {"color", CSSPropertyIdColor},
    {"direction", CSSPropertyIdDirection},
    {"display", CSSPropertyIdDisplay},
    {"fill", CSSPropertyIdFill},
    {"fill-opacity", CSSPropertyIdFill_Opacity},
    {"fill-rule", CSSPropertyIdFill_Rule},
    {"font-family", CSSPropertyIdFont_Family},
    {"font-size", CSSPropertyIdFont_Size},
    {"font-size-adjust", CSSPropertyIdFont_Size_Adjust},
    {"font-stretch", CSSPropertyIdFont_Stretch},
    {"font-style", CSSPropertyIdFont_Style},
    {"font-variant", CSSPropertyIdFont_Variant},
    {"font-weight", CSSPropertyIdFont_Weight},
    {"marker-end", CSSPropertyIdMarker_End},
    {"marker-mid", CSSPropertyIdMarker_Mid},
    {"marker-start", CSSPropertyIdMarker_Start},
    {"mask", CSSPropertyIdMask},
    {"opacity", CSSPropertyIdOpacity},
    {"overflow", CSSPropertyIdOverflow},
    {"stop-color", CSSPropertyIdStop_Color},
    {"stop-opacity", CSSPropertyIdStop_Opacity},
    {"stroke", CSSPropertyIdStroke},
    {"stroke-dasharray", CSSPropertyIdStroke_Dasharray},
    {"stroke-dashoffset", CSSPropertyIdStroke_Dashoffset},
    {"stroke-linecap", CSSPropertyIdStroke_Linecap},
    {"stroke-linejoin", CSSPropertyIdStroke_Linejoin},
    {"stroke-miterlimit", CSSPropertyIdStroke_Miterlimit},
    {"stroke-opacity", CSSPropertyIdStroke_Opacity},
    {"stroke-width", CSSPropertyIdStroke_Width},
    {"text-anchor", CSSPropertyIdText_Anchor},
    {"text-decoration", CSSPropertyIdText_Decoration},
    {"visibility", CSSPropertyIdVisibility},
    {"", CSSPropertyLastId}
};

const std::string& propertyName(PropertyID nameId)
{
    return nameId<EPropertyLastId ? propertymap[nameId].name : KEmptyString;
}

PropertyID propertyId(const std::string& name)
{
    const char* s = name.c_str();
    switch(s[0])
    {
    case 'a':
        if(s[1] == 'c')
            return strcmp(s+2, "cumulate") == 0 ? EPropertyIdAccumulate : EPropertyIdUnknown;
        if(s[1] == 'd')
            return strcmp(s+2, "ditive") == 0 ? EPropertyIdAdditive : EPropertyIdUnknown;
        if(strncmp(s+1, "ttribute", 7) == 0)
        {
           if(s[9] == 'N')
                return strcmp(s+10, "ame") == 0 ? EPropertyIdAttributeName : EPropertyIdUnknown;
           return strcmp(s+9, "Type") == 0 ? EPropertyIdAttributeType : EPropertyIdUnknown;
        }
        break;
    case 'b':
        if(s[1] == 'a')
            return strcmp(s+2, "seProfile") == 0 ? EPropertyIdBaseProfile : EPropertyIdUnknown;
        if(s[1] == 'e')
            return strcmp(s+2, "gin") == 0 ? EPropertyIdBegin : EPropertyIdUnknown;
        return (s[1]=='y'&&s[2]==0) ? EPropertyIdBy : EPropertyIdUnknown;
    case 'c':
        if(s[1] == 'a')
            return strcmp(s+2, "lcMode") == 0 ? EPropertyIdCalcMode : EPropertyIdUnknown;
        if(s[1] == 'l')
        {
            if(s[2] == 'a')
                return strcmp(s+3, "ss") == 0 ? EPropertyIdClass : EPropertyIdUnknown;
            return strcmp(s+2, "ipPathUnits") == 0 ? EPropertyIdClipPathUnits : EPropertyIdUnknown;
        }
        if(s[1] == 'x')
           return (s[2]==0) ? EPropertyIdCx : EPropertyIdUnknown;
        return (s[1]=='y'&&s[2]==0) ? EPropertyIdCy : EPropertyIdUnknown;
    case 'd':
        if(s[1] == 0)
            return EPropertyIdD;
        if(s[1] == 'u')
            return (s[2]=='r'&&s[3]==0) ? EPropertyIdDur : EPropertyIdUnknown;
        if(s[1] == 'x')
            return (s[2]==0) ? EPropertyIdDx : EPropertyIdUnknown;
        return (s[1]=='y'&&s[2]==0) ? EPropertyIdDy : EPropertyIdUnknown;
    case 'e':
        return strcmp(s+1, "nd") == 0 ? EPropertyIdEnd : EPropertyIdUnknown;
    case 'f':
        if(s[1] == 'i')
            return strcmp(s+2, "ll") == 0 ? EPropertyIdFill : EPropertyIdUnknown;
        if(s[1] == 'r')
        {
            if(s[2] == 0)
                return EPropertyIdFr;
            return strcmp(s+2, "om") == 0 ? EPropertyIdFrom : EPropertyIdUnknown;
        }
        if(s[1] == 'x')
            return (s[2]==0) ? EPropertyIdFx : EPropertyIdUnknown;
        return (s[1]=='y'&&s[2]==0) ? EPropertyIdFy : EPropertyIdUnknown;
    case 'g':
        if(strncmp(s+1, "radient", 7) == 0)
        {
            if(s[8] == 'T')
                return strcmp(s+9, "ransform") == 0 ? EPropertyIdGradientTransform : EPropertyIdUnknown;
            return strcmp(s+8, "Units") == 0 ? EPropertyIdGradientUnits : EPropertyIdUnknown;
        }
        break;
    case 'h':
        if(s[1] == 'e')
            return strcmp(s+1, "eight") == 0 ? EPropertyIdHeight : EPropertyIdUnknown;
        return strcmp(s+1, "ref") == 0 ? EPropertyIdHref : EPropertyIdUnknown;
    case 'i':
        return (s[1]=='d'&&s[2]==0) ? EPropertyIdId : EPropertyIdUnknown;
    case 'k':
        if(s[1] == 'e' && s[2] == 'y')
        {
            if(s[3] == 'P')
                return strcmp(s+4, "oints") == 0 ? EPropertyIdKeyPoints : EPropertyIdUnknown;
            if(s[3] == 'S')
                return strcmp(s+4, "plines") == 0 ? EPropertyIdKeySplines : EPropertyIdUnknown;
            return strcmp(s+3, "Times") == 0 ? EPropertyIdKeyTimes : EPropertyIdUnknown;
        }
        break;
    case 'l':
        return strcmp(s+1, "ang") == 0 ? EPropertyIdLang : EPropertyIdUnknown;
    case 'm':
        if(s[1] == 'a')
        {
            if(s[2] == 'r')
            {
                if(s[3]=='k'&&s[4]=='e'&&s[5]=='r')
                {
                    if(s[6] == 'H')
                        return strcmp(s+7, "eight") == 0 ? EPropertyIdMarkerHeight : EPropertyIdUnknown;
                    if(s[6] == 'U')
                        return strcmp(s+7, "nits") == 0 ? EPropertyIdMarkerUnits : EPropertyIdUnknown;
                    return strcmp(s+6, "Width") == 0 ? EPropertyIdMarkerWidth : EPropertyIdUnknown;
                }
                return EPropertyIdUnknown;
            }
            if(s[2] == 's' && s[3] == 'k')
            {
                if(s[4] == 'C')
                    return strcmp(s+5, "ontentUnits") == 0 ? EPropertyIdMaskContentUnits : EPropertyIdUnknown;
                return strcmp(s+4, "Units") == 0 ? EPropertyIdMaskUnits : EPropertyIdUnknown;
            }
            return (s[2]=='x'&&s[3]==0) ? EPropertyIdMax : EPropertyIdUnknown;
        }
        if(s[1] == 'e')
            return strcmp(s+2, "dia") == 0 ? EPropertyIdMedia : EPropertyIdUnknown;
        return strcmp(s+1, "in") == 0 ? EPropertyIdMin : EPropertyIdUnknown;
    case 'o':
        if(s[1] == 'f')
            return strcmp(s+2, "fset") == 0 ? EPropertyIdOffset : EPropertyIdUnknown;
        if(s[1] == 'r' && s[2] == 'i')
        {
            if(s[3] == 'e')
                return strcmp(s+4, "nt") == 0 ? EPropertyIdOrient : EPropertyIdUnknown;
            return strcmp(s+3, "gin") == 0 ? EPropertyIdOrigin : EPropertyIdUnknown;
        }
        break;
    case 'p':
        if(s[1] == 'a')
        {
            if(s[2] == 't')
            {
                if(s[3] == 'h')
                    return (s[4]==0) ? EPropertyIdPath : EPropertyIdUnknown;
                if(strncmp(s+3, "tern", 4) == 0)
                {
                    if(s[7] == 'C')
                        return strcmp(s+8, "ontentUnits") == 0 ? EPropertyIdPatternContentUnits : EPropertyIdUnknown;
                    if(s[7] == 'T')
                        return strcmp(s+8, "ransform") == 0 ? EPropertyIdPatternTransform : EPropertyIdUnknown;
                    return strcmp(s+7, "Units") == 0 ? EPropertyIdPatternUnits : EPropertyIdUnknown;
                }
            }
            return EPropertyIdUnknown;
        }
        if(s[1] == 'o')
            return strcmp(s+2, "ints") == 0 ? EPropertyIdPoints : EPropertyIdUnknown;
        return strcmp(s+1, "reserveAspectRatio") == 0 ? EPropertyIdPreserveAspectRatio : EPropertyIdUnknown;
    case 'r':
        if(s[1] == 0)
            return EPropertyIdR;
        if(s[1] == 'e')
        {
            if(s[2] == 'f')
            {
                if(s[3] == 'X')
                    return s[4]==0 ? EPropertyIdRefX : EPropertyIdUnknown;
                return (s[3]=='Y'&&s[4]==0) ? EPropertyIdRefY : EPropertyIdUnknown;
            }
            if(s[2] == 'p')
            {
                if(s[3]=='e'&&s[4]=='a'&&s[5]=='t')
                {
                    if(s[6] == 'C')
                        return strcmp(s+7, "ount") == 0 ? EPropertyIdRepeatCount : EPropertyIdUnknown;
                    return strcmp(s+6, "Dur") == 0 ? EPropertyIdRepeatDur : EPropertyIdUnknown;
                }
                return EPropertyIdUnknown;
            }
            if(s[2] == 'q')
                return strcmp(s+3, "uiredExtensions") == 0 ? EPropertyIdRequiredExtensions : EPropertyIdUnknown;
            return strcmp(s+2, "start") == 0 ? EPropertyIdRestart : EPropertyIdUnknown;
        }
        if(s[1] == 'o')
            return strcmp(s+2, "tate") == 0 ? EPropertyIdRotate : EPropertyIdUnknown;
        if(s[1] == 'x')
            return s[2]==0 ? EPropertyIdRx : EPropertyIdUnknown;
        return (s[1]=='y'&&s[2]==0) ? EPropertyIdRy : EPropertyIdUnknown;
    case 's':
        if(s[1] == 'p')
            return strcmp(s+2, "readMethod") == 0 ? EPropertyIdSpreadMethod : EPropertyIdUnknown;
        if(s[1] == 't')
        {
            if(s[2] == 'a')
                return strcmp(s+3, "rtOffset") == 0 ? EPropertyIdStartOffset : EPropertyIdUnknown;
            return strcmp(s+2, "yle") == 0 ? EPropertyIdStyle : EPropertyIdUnknown;
        }
        return strcmp(s+1, "ystemLanguage") == 0 ? EPropertyIdSystemLanguage : EPropertyIdUnknown;
    case 't':
        if(s[1] == 'i')
            return strcmp(s+2, "tle") == 0 ? EPropertyIdTitle : EPropertyIdUnknown;
        if(s[1] == 'o')
            return (s[2] == 0) ? EPropertyIdTo : EPropertyIdUnknown;
        if(s[1] == 'r')
            return strcmp(s+2, "ansform") == 0 ? EPropertyIdTransform : EPropertyIdUnknown;
        return strcmp(s+1, "ype") == 0 ? EPropertyIdType : EPropertyIdUnknown;
    case 'v':
        if(s[1] == 'a')
            return strcmp(s+2, "lues") == 0 ? EPropertyIdValues : EPropertyIdUnknown;
        if(s[1] == 'e')
            return strcmp(s+2, "rsion") == 0 ? EPropertyIdVersion : EPropertyIdUnknown;
        return strcmp(s+1, "iewBox") == 0 ? EPropertyIdViewBox : EPropertyIdUnknown;
    case 'w':
        return strcmp(s+1, "idth") == 0 ? EPropertyIdWidth : EPropertyIdUnknown;
    case 'x':
        if(s[1] == 0)
            return EPropertyIdX;
        if(s[1] == '1')
            return s[2] == 0 ? EPropertyIdX1 : EPropertyIdUnknown;
        if(s[1] == '2')
            return s[2] == 0 ? EPropertyIdX2 : EPropertyIdUnknown;
        if(strncmp(s+1, "link:", 5) == 0)
        {
            if(s[6] == 'h')
                return strcmp(s+7, "ref") == 0? EPropertyIdHref : EPropertyIdUnknown;
            return strcmp(s+6, "title") == 0 ? EPropertyIdTitle : EPropertyIdUnknown;
        }
        break;
    case 'y':
        if(s[1] == 0)
            return EPropertyIdY;
        if(s[1] == '1')
            return s[2] == 0 ? EPropertyIdY1 : EPropertyIdUnknown;
        return (s[1]=='2'&& s[2]==0) ? EPropertyIdY2 : EPropertyIdUnknown;
    case 'z':
        return strcmp(s+1, "oomAndPan") == 0 ? EPropertyIdZoomAndPan : EPropertyIdUnknown;
    default:
        break;
    }

    return EPropertyIdUnknown;
}

const std::string& cssPropertyName(CSSPropertyID nameId)
{
    return nameId<CSSPropertyLastId ? csspropertymap[nameId].name : KEmptyString;
}

CSSPropertyID cssPropertyId(const std::string& name)
{
    const char* s = name.c_str();
    switch(s[0])
    {
    case 'c':
        if(s[1] == 'l')
        {
            if(s[2]=='i'&&s[3]=='p')
            {
                if(s[4] == 0)
                    return CSSPropertyIdClip;
                if(s[4] == '-')
                {
                    if(s[5] == 'p')
                        return strcmp(s+6, "ath") == 0 ? CSSPropertyIdClip_Path : CSSPropertyIdUnknown;
                    return strcmp(s+5, "rule") == 0 ? CSSPropertyIdClip_Rule : CSSPropertyIdUnknown;
                }
            }
            return CSSPropertyIdUnknown;
        }
        return strcmp(s+1, "olor") == 0 ? CSSPropertyIdColor : CSSPropertyIdUnknown;
    case 'd':
        if(s[1] == 'i')
        {
            if(s[2] == 'r')
                return strcmp(s+3, "ection") == 0 ? CSSPropertyIdDirection : CSSPropertyIdUnknown;
            return strcmp(s+2, "splay") == 0 ? CSSPropertyIdDisplay : CSSPropertyIdUnknown;
        }
        break;
    case 'f':
        if(s[1] == 'i')
        {
            if(s[2] == 'l' && s[3] == 'l')
            {
                if(s[4] == 0)
                    return CSSPropertyIdFill;
                if(s[4] == '-')
                {
                    if(s[5] == 'o')
                        return strcmp(s+6, "pacity") == 0 ? CSSPropertyIdFill_Opacity : CSSPropertyIdUnknown;
                    return strcmp(s+5, "rule") == 0 ? CSSPropertyIdFill_Rule : CSSPropertyIdUnknown;
                }
            }
            return CSSPropertyIdUnknown;
        }
        if(s[1]=='o'&&s[2]=='n'&&s[3]=='t'&&s[4]=='-')
        {
            if(s[5] == 'f')
                return strcmp(s+6, "amily") == 0 ? CSSPropertyIdFont_Family : CSSPropertyIdUnknown;
            if(s[5] == 's')
            {
               if(s[6]=='i')
                {
                    if(s[7]=='z'&&s[8]=='e')
                    {
                        if(s[9] == 0)
                            return CSSPropertyIdFont_Size;
                        return strcmp(s+9, "-adjust") == 0 ? CSSPropertyIdFont_Size_Adjust : CSSPropertyIdUnknown;
                    }
                    return CSSPropertyIdUnknown;
                }
                if(s[6]=='t')
                {
                    if(s[7]=='r')
                        return strcmp(s+8, "etch") == 0 ? CSSPropertyIdFont_Stretch : CSSPropertyIdUnknown;
                    return strcmp(s+7, "yle") == 0 ? CSSPropertyIdFont_Style : CSSPropertyIdUnknown;
                }
                return CSSPropertyIdUnknown;
            }
            if(s[5] == 'v')
                return strcmp(s+6, "ariant") == 0 ? CSSPropertyIdFont_Variant : CSSPropertyIdUnknown;
            return strcmp(s+5, "weight") == 0 ? CSSPropertyIdFont_Weight : CSSPropertyIdUnknown;
        }
        break;
    case 'm':
        if(s[1] == 'a')
        {
            if(s[2] == 'r')
            {
                if(s[3]=='k'&&s[4]=='e'&&s[5]=='r'&&s[6]=='-')
                {
                    if(s[7] == 'e')
                        return strcmp(s+8, "nd") == 0 ? CSSPropertyIdMarker_End : CSSPropertyIdUnknown;
                    if(s[7] == 'm')
                        return strcmp(s+8, "id") == 0 ? CSSPropertyIdMarker_Mid : CSSPropertyIdUnknown;
                    return strcmp(s+7, "start") == 0 ? CSSPropertyIdMarker_Start : CSSPropertyIdUnknown;
                }
                return CSSPropertyIdUnknown;
            }
            return strcmp(s+2, "sk") == 0 ? CSSPropertyIdMask : CSSPropertyIdUnknown;
        }
        break;
    case 'o':
       if(s[1] == 'p')
            return strcmp(s+2, "acity") == 0 ? CSSPropertyIdOpacity : CSSPropertyIdUnknown;
        return strcmp(s+1, "verflow") == 0 ? CSSPropertyIdOverflow : CSSPropertyIdUnknown;
    case 's':
        if(s[1] == 't')
        {
            if(s[2] == 'o')
            {
                if(s[3]=='p'&&s[4]=='-')
                {
                    if(s[5] == 'c')
                        return strcmp(s+6, "olor") == 0 ? CSSPropertyIdStop_Color : CSSPropertyIdUnknown;
                    return strcmp(s+5, "opacity") == 0 ? CSSPropertyIdStop_Opacity : CSSPropertyIdUnknown;
                }
                return CSSPropertyIdUnknown;
            }
            if(s[2] == 'r')
            {
                if(s[3]=='o'&&s[4]=='k'&&s[5]=='e')
                {
                    if(s[6] == 0)
                        return CSSPropertyIdStroke;
                    if(s[6] == '-')
                    {
                        if(s[7] == 'd')
                        {
                            if(s[8]=='a'&&s[9]=='s'&&s[10]=='h')
                            {
                                if(s[11] == 'a')
                                    return strcmp(s+12, "rray") == 0 ? CSSPropertyIdStroke_Dasharray : CSSPropertyIdUnknown;
                                return strcmp(s+11, "offset") == 0 ? CSSPropertyIdStroke_Dashoffset : CSSPropertyIdUnknown;
                            }
                            return CSSPropertyIdUnknown;
                        }
                        if(s[7] == 'l')
                        {
                            if(s[8]=='i'&&s[9]=='n'&&s[10]=='e')
                            {
                                if(s[11] == 'c')
                                    return strcmp(s+12, "ap") == 0 ? CSSPropertyIdStroke_Linecap : CSSPropertyIdUnknown;
                                return strcmp(s+11, "join") == 0 ? CSSPropertyIdStroke_Linejoin : CSSPropertyIdUnknown;
                            }
                            return CSSPropertyIdUnknown;
                        }
                        if(s[7] == 'm')
                            return strcmp(s+8, "iterlimit") == 0 ? CSSPropertyIdStroke_Miterlimit : CSSPropertyIdUnknown;
                        if(s[7] == 'o')
                            return strcmp(s+8, "pacity") == 0 ? CSSPropertyIdStroke_Opacity : CSSPropertyIdUnknown;
                        return strcmp(s+7, "width") == 0 ? CSSPropertyIdStroke_Width : CSSPropertyIdUnknown;
                    }
                }
            }
        }
        break;
    case 't':
        if(s[1]=='e'&&s[2]=='x'&&s[3]=='t'&&s[4]=='-')
        {
            if(s[5] == 'a')
                return strcmp(s+6, "nchor") == 0 ? CSSPropertyIdText_Anchor : CSSPropertyIdUnknown;
            return strcmp(s+5, "decoration") == 0 ? CSSPropertyIdText_Decoration : CSSPropertyIdUnknown;
        }
        break;
    case 'v':
        return strcmp(s+1, "isibility") == 0 ? CSSPropertyIdVisibility : CSSPropertyIdUnknown;
    default:
        break;
    }

    return CSSPropertyIdUnknown;
}

} // namespace Utils

} // namespace lunasvg
