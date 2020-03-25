#ifndef SVGPROPERTYUTILS_H
#define SVGPROPERTYUTILS_H

#include <string>

namespace lunasvg {

enum PropertyID
{
    EPropertyIdUnknown = 0,
    EPropertyIdAccumulate,
    EPropertyIdAdditive,
    EPropertyIdAttributeName,
    EPropertyIdAttributeType,
    EPropertyIdBaseProfile,
    EPropertyIdBegin,
    EPropertyIdBy,
    EPropertyIdCalcMode,
    EPropertyIdClass,
    EPropertyIdClipPathUnits,
    EPropertyIdCx,
    EPropertyIdCy,
    EPropertyIdD,
    EPropertyIdDur,
    EPropertyIdDx,
    EPropertyIdDy,
    EPropertyIdEnd,
    EPropertyIdFill,
    EPropertyIdFrom,
    EPropertyIdFx,
    EPropertyIdFy,
    EPropertyIdFr,
    EPropertyIdGradientTransform,
    EPropertyIdGradientUnits,
    EPropertyIdHeight,
    EPropertyIdHref,
    EPropertyIdId,
    EPropertyIdKeyPoints,
    EPropertyIdKeySplines,
    EPropertyIdKeyTimes,
    EPropertyIdLang,
    EPropertyIdMarkerHeight,
    EPropertyIdMarkerUnits,
    EPropertyIdMarkerWidth,
    EPropertyIdMaskContentUnits,
    EPropertyIdMaskUnits,
    EPropertyIdMax,
    EPropertyIdMedia,
    EPropertyIdMin,
    EPropertyIdOffset,
    EPropertyIdOrient,
    EPropertyIdOrigin,
    EPropertyIdPath,
    EPropertyIdPatternContentUnits,
    EPropertyIdPatternTransform,
    EPropertyIdPatternUnits,
    EPropertyIdPoints,
    EPropertyIdPreserveAspectRatio,
    EPropertyIdR,
    EPropertyIdRefX,
    EPropertyIdRefY,
    EPropertyIdRepeatCount,
    EPropertyIdRepeatDur,
    EPropertyIdRequiredExtensions,
    EPropertyIdRestart,
    EPropertyIdRotate,
    EPropertyIdRx,
    EPropertyIdRy,
    EPropertyIdSpreadMethod,
    EPropertyIdStartOffset,
    EPropertyIdStyle,
    EPropertyIdSystemLanguage,
    EPropertyIdTitle,
    EPropertyIdTo,
    EPropertyIdTransform,
    EPropertyIdType,
    EPropertyIdValues,
    EPropertyIdVersion,
    EPropertyIdViewBox,
    EPropertyIdWidth,
    EPropertyIdX,
    EPropertyIdX1,
    EPropertyIdX2,
    EPropertyIdY,
    EPropertyIdY1,
    EPropertyIdY2,
    EPropertyIdZoomAndPan,
    EPropertyLastId
};

enum CSSPropertyID
{
    CSSPropertyIdUnknown,
    CSSPropertyIdClip,
    CSSPropertyIdClip_Path,
    CSSPropertyIdClip_Rule,
    CSSPropertyIdColor,
    CSSPropertyIdDirection,
    CSSPropertyIdDisplay,
    CSSPropertyIdFill,
    CSSPropertyIdFill_Opacity,
    CSSPropertyIdFill_Rule,
    CSSPropertyIdFont_Family,
    CSSPropertyIdFont_Size,
    CSSPropertyIdFont_Size_Adjust,
    CSSPropertyIdFont_Stretch,
    CSSPropertyIdFont_Style,
    CSSPropertyIdFont_Variant,
    CSSPropertyIdFont_Weight,
    CSSPropertyIdMarker_End,
    CSSPropertyIdMarker_Mid,
    CSSPropertyIdMarker_Start,
    CSSPropertyIdMask,
    CSSPropertyIdOpacity,
    CSSPropertyIdOverflow,
    CSSPropertyIdStop_Color,
    CSSPropertyIdStop_Opacity,
    CSSPropertyIdStroke,
    CSSPropertyIdStroke_Dasharray,
    CSSPropertyIdStroke_Dashoffset,
    CSSPropertyIdStroke_Linecap,
    CSSPropertyIdStroke_Linejoin,
    CSSPropertyIdStroke_Miterlimit,
    CSSPropertyIdStroke_Opacity,
    CSSPropertyIdStroke_Width,
    CSSPropertyIdText_Anchor,
    CSSPropertyIdText_Decoration,
    CSSPropertyIdVisibility,
    CSSPropertyLastId
};

namespace Utils {

const std::string& propertyName(PropertyID nameId);
PropertyID propertyId(const std::string& name);
const std::string& cssPropertyName(CSSPropertyID nameId);
CSSPropertyID cssPropertyId(const std::string& name);

} // namespace Utils

} // namespace lunasvg

#endif // SVGPROPERTYUTILS_H
