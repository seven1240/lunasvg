#ifndef STROKEDATA_H
#define STROKEDATA_H

#include <vector>

namespace lunasvg {

enum LineCap
{
    ELineCapButt,
    ELineCapRound,
    ELineCapSquare,
};

enum LineJoin
{
    ELineJoinMiter,
    ELineJoinRound,
    ELineJoinBevel
};

class StrokeData
{
public:
    inline StrokeData()
    {
        width = 0;
        miterLimit = 0;
        dashOffset = 0;
        cap = ELineCapButt;
        join = ELineJoinMiter;
    }

public:
    float width;
    float miterLimit;
    float dashOffset;
    std::vector<float> dashes;
    LineCap cap;
    LineJoin join;
};

} // namespace lunasvg

#endif // STROKEDATA_H
