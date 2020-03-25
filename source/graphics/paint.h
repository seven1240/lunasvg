#ifndef PAINT_H
#define PAINT_H

#include "gradient.h"
#include "rgb.h"
#include "refptr.h"

namespace lunasvg {

enum PaintType
{
    EPaintTypeNone,
    EPaintTypeColor,
    EPaintTypeGradient
};

struct PaintData
{
    PaintType type;
    float opacity;
};

class Paint
{
public:
    ~Paint();
    Paint();
    Paint(PaintType type);
    Paint(const Rgb& color);
    Paint(const Gradient& gradient);
    Paint(const Paint& paint);

    void setColor(const Rgb& color);
    void setGradient(const Gradient& gradient);
    void setType(PaintType type);
    void setOpacity(float opacity);
    void initType(PaintType type);

    const Rgb* color() const;
    const Gradient* gradient() const;
    bool isNone() const;
    float opacity() const;
    PaintType type() const;

private:
    RefPtr<PaintData> m_data;
};

} // namespace lunasvg

#endif // PAINT_H
