#ifndef GRADIENT_H
#define GRADIENT_H

#include <utility>
#include <vector>

#include "affinetransform.h"
#include "rgb.h"

namespace lunasvg {

enum SpreadMethod
{
    ESpreadMethodPad,
    ESpreadMethodReflect,
    ESpreadMethodRepeat
};

enum GradientUnits
{
    EGradientUnitsObjectBoundingBox,
    EGradientUnitsUserSpaceOnUse
};

enum GradientType
{
   EGradientTypeLinear,
   EGradientTypeRadial
};

typedef std::pair<float, Rgb> GradientStop;
typedef std::vector<GradientStop> GradientStops;

class Gradient
{
public:
   struct Linear
   {
       float x1, x2, y1, y2;
   };

   struct Radial
   {
       float cx, cy, r, fx, fy;
   };

public:
   GradientType type;
   AffineTransform matrix;
   SpreadMethod spread;
   GradientStops stops;
   union
   {
       Linear linear;
       Radial radial;
   };
};

} // namespace lunasvg

#endif // GRADIENT_H
