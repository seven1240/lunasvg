#include "paint.h"

namespace lunasvg {

struct ColorPaintData : public PaintData
{
    Rgb color;
};

struct GradientPaintData : public PaintData
{
    Gradient gradient;
};

Paint::~Paint()
{
}

Paint::Paint()
{
    initType(EPaintTypeNone);
}

Paint::Paint(PaintType type)
{
    initType(type);
}

Paint::Paint(const Rgb& color)
{
    initType(EPaintTypeColor);

    setColor(color);
}

Paint::Paint(const Gradient &gradient)
{
    initType(EPaintTypeGradient);

    setGradient(gradient);
}

Paint::Paint(const Paint &paint) :
    m_data(paint.m_data)
{
}

void Paint::setColor(const Rgb &color)
{
    setType(EPaintTypeColor);

    ColorPaintData* colorData = static_cast<ColorPaintData*>(m_data.get());
    colorData->color = color;
}

void Paint::setGradient(const Gradient& gradient)
{
    setType(EPaintTypeGradient);

    GradientPaintData* gradientData = static_cast<GradientPaintData*>(m_data.get());
    gradientData->gradient = gradient;
}

void Paint::setType(PaintType type)
{
     if(type == m_data->type)
         return;

     initType(type);
}

void Paint::setOpacity(float opacity)
{
    m_data->opacity = opacity;
}

void Paint::initType(PaintType type)
{
    switch(type)
    {
    case EPaintTypeNone:
        m_data = new PaintData();
        break;
    case EPaintTypeColor:
        m_data = new ColorPaintData();
        break;
    case EPaintTypeGradient:
        m_data = new GradientPaintData();
        break;
    }

    m_data->type = type;
    m_data->opacity = 1.f;
}

const Rgb* Paint::color() const
{
    return m_data->type == EPaintTypeColor ? &static_cast<const ColorPaintData*>(m_data.get())->color : NULL;
}

const Gradient* Paint::gradient() const
{
    return m_data->type == EPaintTypeGradient ? &static_cast<const GradientPaintData*>(m_data.get())->gradient : NULL;
}

bool Paint::isNone() const
{
    return m_data->type == EPaintTypeNone;
}

float Paint::opacity() const
{
    return m_data->opacity;
}

PaintType Paint::type() const
{
    return m_data->type;
}

} // namespace lunasvg
