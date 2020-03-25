#ifndef POINT_H
#define POINT_H

namespace lunasvg {

class Point
{
public:
    Point() : x(0), y(0) {}
    Point(float _x, float _y) : x(_x), y(_y) {}

public:
    float x;
    float y;
};

} // namespace lunasvg

#endif // POINT_H
