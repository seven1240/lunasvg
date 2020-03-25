#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

#include <stack>

#include "strokedata.h"
#include "paint.h"
#include "path.h"
#include "surface.h"

namespace lunasvg {

class Bitmap;
class AffineTransform;
class Rect;
class Surface;
class Rgb;
class GraphicsContextImpl;
class Point;

class GraphicsContext
{
public:
    ~GraphicsContext();
    GraphicsContext(Surface& surface);

    void rotate(float radians);
    void scale(float x, float y);
    void translate(float x, float y);
    void concatenate(const AffineTransform& matrix);
    void setMatrix(const AffineTransform& matrix);
    AffineTransform getMatrix() const;

    void pushClip(const Path& path, WindRule clipRule);
    void pushClip(const Rect& rect);
    void popClip();

    void clear(const Rgb& color);
    void clearPath(const Path& path, WindRule fillRule, const Paint& fillPaint);

    void setFillRule(WindRule fillRule) { m_fillRule = fillRule; }
    void setFillPaint(const Paint& fillPaint) { m_fillPaint = fillPaint; }
    void setStrokePaint(const Paint& strokePaint) { m_strokePaint = strokePaint; }
    void setStrokeData(const StrokeData& strokeData) { m_strokeData = strokeData; }

    WindRule fillRule() const { return m_fillRule; }
    const Paint& fillPaint() const { return m_fillPaint; }
    const Paint& strokePaint() const { return m_strokePaint; }
    const StrokeData& strokeData() const { return m_strokeData; }

    void drawPath(const Path& path);
    void drawRect(const Rect& rect, float rx = 0, float ry = 0);
    void drawLine(const Point& p1, const Point& p2);
    void drawEllipse(const Rect& bbox);
    void drawBitmap(const Bitmap& bitmap);

    void pushLayer();
    void popLayer(float opacity);
    Surface currentLayer() const;
    Surface rootLayer() const;
    GraphicsContextImpl* impl() const { return m_impl; }

private:
    GraphicsContextImpl* m_impl;
    Paint m_fillPaint;
    WindRule m_fillRule;
    Paint m_strokePaint;
    StrokeData m_strokeData;
};

} // namespace

#endif // GRAPHICSCONTEXT_H
