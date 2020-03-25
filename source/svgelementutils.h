#ifndef SVGELEMENTUTILS_H
#define SVGELEMENTUTILS_H

#include <string>

namespace lunasvg {

enum ElementID
{
    EElementIdUnknown = 0,
    EElementIdA,
    EElementIdAnimate,
    EElementIdAnimateColor,
    EElementIdAnimateMotion,
    EElementIdAnimateTransform,
    EElementIdCircle,
    EElementIdClipPath,
    EElementIdDefs,
    EElementIdDesc,
    EElementIdEllipse,
    EElementIdG,
    EElementIdImage,
    EElementIdLine,
    EElementIdLinearGradient,
    EElementIdMarker,
    EElementIdMask,
    EElementIdMetadata,
    EElementIdMpath,
    EElementIdPath,
    EElementIdPattern,
    EElementIdPolygon,
    EElementIdPolyline,
    EElementIdRadialGradient,
    EElementIdRect,
    EElementIdSet,
    EElementIdStop,
    EElementIdStyle,
    EElementIdSvg,
    EElementIdSwitch,
    EElementIdSymbol,
    EElementIdText,
    EElementIdTextPath,
    EElementIdTitle,
    EElementIdTref,
    EElementIdTspan,
    EElementIdUse,
    EElementIdView,
    EElementLastId
};

class SVGElementHead;
class SVGDocument;

namespace Utils {

const std::string& elementName(ElementID nameId);
ElementID elementId(const std::string& name);
bool isElementPermitted(ElementID parentId, ElementID childId);
SVGElementHead* createElement(ElementID elementId, SVGDocument* document);

} // namespace Utils

} // namespace lunasvg

#endif // SVGELEMENTUTILS_H
