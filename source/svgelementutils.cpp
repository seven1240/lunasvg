#include "svgelementutils.h"
#include "svgparserutils.h"

#include "svgsvgelement.h"
#include "svggelement.h"
#include "svgrectelement.h"
#include "svgcircleelement.h"
#include "svgellipseelement.h"
#include "svgpathelement.h"
#include "svglineelement.h"
#include "svgdefselement.h"
#include "svgpolygonelement.h"
#include "svgpolylineelement.h"
#include "svglineargradientelement.h"
#include "svgradialgradientelement.h"
#include "svgstopelement.h"
#include "svgsymbolelement.h"
#include "svguseelement.h"

namespace lunasvg {

namespace Utils {

#define KElementIdsAnimation \
    EElementIdAnimate, \
    EElementIdAnimateMotion, \
    EElementIdAnimateTransform, \
    EElementIdAnimateColor, \
    EElementIdSet

#define KElementIdsDescriptive \
    EElementIdDesc, \
    EElementIdTitle, \
    EElementIdMetadata

#define KElementIdsGradient \
    EElementIdLinearGradient, \
    EElementIdRadialGradient

#define KElementIdsStructural \
    EElementIdDefs, \
    EElementIdG, \
    EElementIdSvg, \
    EElementIdSymbol, \
    EElementIdUse

#define KElementIdsShape \
    EElementIdCircle, \
    EElementIdEllipse, \
    EElementIdLine, \
    EElementIdPath, \
    EElementIdPolygon, \
    EElementIdPolyline, \
    EElementIdRect

#define KElementIdsTextContentChild \
    EElementIdTextPath, \
    EElementIdTref, \
    EElementIdTspan

static const ElementID contentmodel_1[] = {
    KElementIdsAnimation,
    KElementIdsShape,
    KElementIdsDescriptive,
    KElementIdsStructural,
    KElementIdsGradient,
    EElementIdA,
    EElementIdClipPath,
    EElementIdImage,
    EElementIdMarker,
    EElementIdMask,
    EElementIdPattern,
    EElementIdStyle,
    EElementIdSwitch,
    EElementIdText,
    EElementIdView,
    EElementIdUnknown
};

static const ElementID contentmodel_2[] = {
    KElementIdsAnimation,
    KElementIdsDescriptive,
    EElementIdUnknown
};

static const ElementID contentmodel_3[] = {
    //KElementAllIds,
    EElementIdUnknown
};

static const ElementID contentmodel_4[] = {
    KElementIdsDescriptive,
    EElementIdUnknown
};

static const ElementID contentmodel_5[] = {
    KElementIdsAnimation,
    KElementIdsShape,
    KElementIdsDescriptive,
    EElementIdA,
    EElementIdG,
    EElementIdImage,
    EElementIdSvg,
    EElementIdSwitch,
    EElementIdText,
    EElementIdUse,
    EElementIdUnknown
};

static const ElementID contentmodel_6[] = {
    KElementIdsAnimation,
    KElementIdsDescriptive,
    KElementIdsTextContentChild,
    EElementIdA,
    EElementIdUnknown
};

static const ElementID contentmodel_7[] = {
    KElementIdsDescriptive,
    EElementIdA,
    EElementIdAnimate,
    EElementIdAnimateColor,
    EElementIdSet,
    EElementIdTref,
    EElementIdTspan,
    EElementIdUnknown
};

static const ElementID contentmodel_8[] = {
    KElementIdsDescriptive,
    EElementIdAnimate,
    EElementIdAnimateColor,
    EElementIdSet,
    EElementIdUnknown
};

static const ElementID contentmodel_11[] = {
    KElementIdsAnimation,
    KElementIdsShape,
    KElementIdsDescriptive,
    EElementIdUse,
    EElementIdText,
    EElementIdUnknown
};

static const ElementID contentmodel_12[] = {
    KElementIdsDescriptive,
    EElementIdAnimate,
    EElementIdAnimateTransform,
    EElementIdSet,
    EElementIdStop,
    EElementIdUnknown
};

static const ElementID contentmodel_13[] = {
    EElementIdAnimate,
    EElementIdAnimateColor,
    EElementIdSet,
    EElementIdUnknown
};

static const ElementID contentmodel_15[] = {
    EElementIdAnimate,
    EElementIdSet,
    EElementIdUnknown
};

static const ElementID contentmodel_23[] = {
    KElementIdsDescriptive,
    EElementIdMpath,
    EElementIdUnknown
};

static const ElementID contentmodel_24[] = {
    EElementIdAnimate,
    EElementIdAnimateTransform,
    EElementIdSet,
    EElementIdUnknown
};

static const ElementID contentmodel_25[] = {
    EElementIdUnknown
};

static const struct
{
    std::string name;
    ElementID id;
    const ElementID* content;
} elementmap[] = {
    {"", EElementIdUnknown, contentmodel_25},
    {"a", EElementIdA, contentmodel_1},
    {"animate", EElementIdAnimate, contentmodel_4},
    {"animateColor", EElementIdAnimateColor, contentmodel_4},
    {"animateMotion", EElementIdAnimateMotion, contentmodel_23},
    {"animateTransform", EElementIdAnimateTransform, contentmodel_4},
    {"circle", EElementIdCircle, contentmodel_2},
    {"clipPath", EElementIdClipPath, contentmodel_11},
    {"defs", EElementIdDefs, contentmodel_1},
    {"desc", EElementIdDesc, contentmodel_3},
    {"ellipse", EElementIdEllipse, contentmodel_2},
    {"g", EElementIdG, contentmodel_1},
    {"image", EElementIdImage, contentmodel_2},
    {"line", EElementIdLine, contentmodel_2},
    {"linearGradient", EElementIdLinearGradient, contentmodel_12},
    {"marker", EElementIdMarker, contentmodel_1},
    {"mask", EElementIdMask, contentmodel_1},
    {"metadata", EElementIdMetadata, contentmodel_3},
    {"mpath", EElementIdMpath, contentmodel_23},
    {"path", EElementIdPath, contentmodel_2},
    {"pattern", EElementIdPattern, contentmodel_1},
    {"polygon", EElementIdPolygon, contentmodel_2},
    {"polyline", EElementIdPolyline, contentmodel_2},
    {"radialGradient", EElementIdRadialGradient, contentmodel_12},
    {"rect", EElementIdRect, contentmodel_2},
    {"set", EElementIdSet, contentmodel_4},
    {"stop", EElementIdStop, contentmodel_13},
    {"style", EElementIdStyle, contentmodel_3},
    {"svg", EElementIdSvg, contentmodel_1},
    {"switch", EElementIdSwitch, contentmodel_5},
    {"symbol", EElementIdSymbol, contentmodel_1},
    {"text", EElementIdText, contentmodel_6},
    {"textPath", EElementIdTextPath, contentmodel_7},
    {"title", EElementIdTitle, contentmodel_3},
    {"tref", EElementIdTref, contentmodel_8},
    {"tspan", EElementIdTspan, contentmodel_7},
    {"use", EElementIdUse, contentmodel_2},
    {"view", EElementIdView, contentmodel_4},
    {"", EElementLastId, NULL}
};

bool isElementPermitted(ElementID parentId, ElementID childId)
{
    const ElementID* content = parentId<EElementLastId?elementmap[parentId].content:NULL;
    if(content!=NULL)
    {
        for(int i = 0;content[i]; i++)
            if(content[i] == childId)
                return true;
    }

    return false;
}

SVGElementHead* createElement(ElementID elementId, SVGDocument* document)
{
    switch(elementId)
    {
    case EElementIdSvg:
        return new SVGSVGElement(document);
    case EElementIdPath:
        return new SVGPathElement(document);
    case EElementIdG:
        return new SVGGElement(document);
    case EElementIdRect:
        return new SVGRectElement(document);
    case EElementIdCircle:
        return new SVGCircleElement(document);
    case EElementIdEllipse:
        return new SVGEllipseElement(document);
    case EElementIdLine:
        return new SVGLineElement(document);
    case EElementIdDefs:
        return new SVGDefsElement(document);
    case EElementIdPolygon:
        return new SVGPolygonElement(document);
    case EElementIdPolyline:
        return new SVGPolylineElement(document);
    case EElementIdStop:
        return new SVGStopElement(document);
    case EElementIdLinearGradient:
        return new SVGLinearGradientElement(document);
    case EElementIdRadialGradient:
        return new SVGRadialGradientElement(document);
    case EElementIdSymbol:
        return new SVGSymbolElement(document);
    case EElementIdUse:
        return new SVGUseElement(document);
    default:
        break;
    }

    return NULL;
}

const std::string& elementName(ElementID nameId)
{
    return nameId<EElementLastId ? elementmap[nameId].name : KEmptyString;
}

ElementID elementId(const std::string& name)
{
    const char* s = name.c_str();
    switch(s[0])
    {
    case 'a':
        if(s[1] == 0)
            return EElementIdA;
        if(strncmp(s+1, "nimate", 6) == 0)
        {
            if(s[7] == 0)
                return EElementIdAnimate;
            if(s[7] == 'C')
                return strcmp(s+8, "olor") == 0 ? EElementIdAnimateColor : EElementIdUnknown;
            if(s[7] == 'M')
                return strcmp(s+8, "otion") == 0 ? EElementIdAnimateMotion : EElementIdUnknown;
            return strcmp(s+7, "Transform") == 0 ? EElementIdAnimateTransform : EElementIdUnknown;
        }
        break;
    case 'c':
        if(s[1] == 'i')
            return strcmp(s+2, "rcle") == 0 ? EElementIdCircle : EElementIdUnknown;
        return strcmp(s+1, "lipPath") == 0 ? EElementIdClipPath : EElementIdUnknown;
    case 'd':
        if(s[1] == 'e')
        {
            if(s[2] == 'f')
                return (s[3]=='s'&&s[4]==0) ? EElementIdDefs : EElementIdUnknown;
            return strcmp(s+2, "sc") == 0 ? EElementIdDesc : EElementIdUnknown;
        }
        break;
    case 'e':
        return strcmp(s+1, "llipse") == 0 ? EElementIdEllipse : EElementIdUnknown;
    case 'g':
        return (s[1] == 0) ? EElementIdG : EElementIdUnknown;
    case 'i':
        return strcmp(s+1, "mage") == 0 ? EElementIdImage : EElementIdUnknown;
    case 'l':
        if(strncmp(s+1, "ine", 3) == 0)
        {
            if(s[4] == 0)
                return EElementIdLine;
            return strcmp(s+4, "arGradient") == 0 ? EElementIdLinearGradient : EElementIdUnknown;
        }
        break;
    case 'm':
        if(s[1] == 'a')
        {
            if(s[2] == 'r')
                return strcmp(s+3, "ker") == 0 ? EElementIdMarker : EElementIdUnknown;
            return strcmp(s+2, "sk") == 0 ? EElementIdMask : EElementIdUnknown;
        }
        if(s[1] == 'e')
            return strcmp(s+2, "tadata") == 0 ? EElementIdMetadata : EElementIdUnknown;
        return strcmp(s+1, "path") == 0 ? EElementIdMpath : EElementIdUnknown;
    case 'p':
        if(s[1] == 'a')
        {
            if(s[2] == 't')
            {
                if(s[3] == 'h')
                    return s[4] == 0 ? EElementIdPath : EElementIdUnknown;
                return strcmp(s+3, "tern") == 0 ? EElementIdPattern : EElementIdUnknown;
            }
            return EElementIdUnknown;
        }
        if(strncmp(s+1, "oly", 3) == 0)
        {
            if(s[4] == 'g')
                return strcmp(s+5, "on") == 0 ? EElementIdPolygon : EElementIdUnknown;
            return strcmp(s+4, "line") == 0 ? EElementIdPolyline : EElementIdUnknown;
        }
        break;
    case 'r':
        if(s[1] == 'a')
            return strcmp(s+2, "dialGradient") == 0 ? EElementIdRadialGradient : EElementIdUnknown;
        return strcmp(s+1, "ect") == 0 ? EElementIdRect : EElementIdUnknown;
    case 's':
        if(s[1] == 'e')
            return  (s[2]=='t'&&s[3]==0) ? EElementIdSet : EElementIdUnknown;
        if(s[1] == 't')
        {
            if(s[2] == 'o')
                return (s[3]=='p'&&s[4]==0) ? EElementIdStop : EElementIdUnknown;
            return strcmp(s+2, "yle") == 0 ? EElementIdStyle : EElementIdUnknown;
        }
        if(s[1] == 'v')
            return (s[2]=='g'&&s[3]==0) ? EElementIdSvg : EElementIdUnknown;
        if(s[1] == 'w')
            return strcmp(s+2, "itch") == 0 ? EElementIdSwitch : EElementIdUnknown;
        return strcmp(s+1, "ymbol") == 0 ? EElementIdSymbol : EElementIdUnknown;
    case 't':
        if(s[1] == 'e')
        {
            if(s[2]=='x'&&s[3]=='t')
            {
                if(s[4] == 0)
                    return EElementIdText;
                return strcmp(s+4, "Path") == 0 ? EElementIdTextPath : EElementIdUnknown;
            }
            return EElementIdUnknown;
        }
        if(s[1] == 'i')
            return strcmp(s+2, "tle") == 0 ? EElementIdTitle : EElementIdUnknown;
        if(s[1] == 'r')
            return strcmp(s+2, "ef") == 0 ? EElementIdTref : EElementIdUnknown;
        return strcmp(s+1, "span") == 0 ? EElementIdTspan : EElementIdUnknown;
    case 'u':
        return strcmp(s+1, "se") == 0 ? EElementIdUse : EElementIdUnknown;
    case 'v':
        return strcmp(s+1, "iew") == 0 ? EElementIdView : EElementIdUnknown;
    default:
        break;
    }

    return EElementIdUnknown;
}

} // namespace Utils

} // namespace lunasvg
