#ifndef PATHUTILS_H
#define PATHUTILS_H

#include "path.h"

namespace lunasvg
{

namespace Utils
{

void pathArcTo(Path& path, float rx, float ry, float xAxisRotation, bool largeArcFlag, bool sweepFlag, float x, float y, bool rel = false);

} // namespace Utils

} // namespace lunasvg

#endif // PATHUTILS_H
