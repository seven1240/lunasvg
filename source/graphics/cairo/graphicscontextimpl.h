#ifndef GRAPHICSCONTEXTIMPL_H
#define GRAPHICSCONTEXTIMPL_H

#include <cairo/cairo.h>

#include "graphicscontext.h"

namespace lunasvg {

class SurfaceImpl;

class GraphicsContextImpl
{
public:
    ~GraphicsContextImpl();
    GraphicsContextImpl(SurfaceImpl* surface);

    void rotate(float radians);
    void scale(float x, float y);
    void translate(float x, float y);
    void concatenate(const AffineTransform& matrix);
    void setMatrix(const AffineTransform& matrix);
    AffineTransform getMatrix() const;

    void clearPath(const Path& path, WindRule fillRule, const Paint& fillPaint);
    void drawPath(const Path& path, WindRule fillRule, const Paint& fillPaint, const Paint& strokePaint, const StrokeData& strokeData);

    void pushClip(const Path&, WindRule);
    void popClip();

    void pushLayer();
    void popLayer(float opacity);
    SurfaceImpl* currentLayer() const;
    SurfaceImpl* rootLayer() const;

private:
    cairo_t* m_cr;
};

} // namespace lunasvg

#endif // GRAPHICSCONTEXTIMPL_H
