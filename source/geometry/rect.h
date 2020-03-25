#ifndef RECT_H
#define RECT_H

#include <algorithm>

namespace lunasvg {

class Rect
{
public:
    Rect() : x(0), y(0), width(0), height(0) {}
    Rect(float _x, float _y, float _w, float _h) : x(_x), y(_y), width(_w), height(_h) {}

    float right() const { return x + width; }
    float bottom() const { return y + height; }

    void unite(const Rect& rect);

public:
    float x;
    float y;
    float width;
    float height;
};

inline void Rect::unite(const Rect &rect)
{
    float l = std::min(x, rect.x);
    float t = std::min(y, rect.y);
    float r = std::max(right(), rect.right());
    float b = std::max(bottom(), rect.bottom());

    x = l;
    y = t;
    width = r - l;
    height = b - t;
}

} // namespace lunasvg

#endif // RECT_H
