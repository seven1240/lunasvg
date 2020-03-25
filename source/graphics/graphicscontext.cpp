#include "graphicscontext.h"
#include "surface.h"

#ifdef LUNA_SVG_ENABLE_CAIRO
#    include "cairo/graphicscontextimpl.h"
#    include "cairo/surfaceimpl.h"
#endif

#include <assert.h>

namespace lunasvg {

GraphicsContext::~GraphicsContext()
{
    delete m_impl;
}

GraphicsContext::GraphicsContext(Surface& surface) :
    m_impl(new GraphicsContextImpl(surface.impl()))
{
}

void GraphicsContext::rotate(float radians)
{
    m_impl->rotate(radians);
}

void GraphicsContext::scale(float x, float y)
{
    m_impl->scale(x, y);
}

void GraphicsContext::translate(float x, float y)
{
    m_impl->translate(x, y);
}

void GraphicsContext::concatenate(const AffineTransform& matrix)
{
    m_impl->concatenate(matrix);
}

void GraphicsContext::setMatrix(const AffineTransform &matrix)
{
    m_impl->setMatrix(matrix);
}

AffineTransform GraphicsContext::getMatrix() const
{
    return m_impl->getMatrix();
}

void GraphicsContext::pushClip(const Path& path, WindRule clipRule)
{
    m_impl->pushClip(path, clipRule);
}

void GraphicsContext::pushClip(const Rect &rect)
{
    Path path;
    path.addRect(rect);
    pushClip(path, EWindRuleNonZero);
}

void GraphicsContext::popClip()
{
    m_impl->popClip();
}

void GraphicsContext::clear(const Rgb& color)
{
    RefPtr<SurfaceImpl> layer = m_impl->currentLayer();
    Path path;
    path.addRect(0, 0, layer->width(), layer->height());
    clearPath(path, EWindRuleNonZero, Paint(color));
}

void GraphicsContext::clearPath(const Path& path, WindRule fillRule, const Paint& fillPaint)
{
    m_impl->clearPath(path, fillRule, fillPaint);
}

void GraphicsContext::drawPath(const Path &path)
{
    m_impl->drawPath(path, m_fillRule, m_fillPaint, m_strokePaint, m_strokeData);
}

void GraphicsContext::drawRect(const Rect& rect, float rx, float ry)
{
    Path path;
    path.addRect(rect, rx, ry);
    drawPath(path);
}

void GraphicsContext::drawLine(const Point &p1, const Point &p2)
{
    Path path;
    path.moveTo(p1);
    path.lineTo(p2);
    drawPath(path);
}

void GraphicsContext::pushLayer()
{
    m_impl->pushLayer();
}

void GraphicsContext::popLayer(float opacity)
{
    m_impl->popLayer(opacity);
}

Surface GraphicsContext::currentLayer() const
{
    return Surface(m_impl->currentLayer());
}

Surface GraphicsContext::rootLayer() const
{
    return Surface(m_impl->rootLayer());
}

} // namespace lunasvg
