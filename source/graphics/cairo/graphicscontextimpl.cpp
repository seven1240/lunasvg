#include "graphicscontextimpl.h"
#include "surface.h"
#include "surfaceimpl.h"
#include "rgb.h"
#include "rect.h"
#include "pathiterator.h"

namespace lunasvg {

static void set_path_on_context(cairo_t* cr, const Path& path);
static void set_paint_on_context(cairo_t* cr, const Paint& paint);
static void set_wind_rule_on_context(cairo_t* cr, WindRule windRule);
static void set_strokedata_on_context(cairo_t* cr, const StrokeData& strokeData);

GraphicsContextImpl::~GraphicsContextImpl()
{
    cairo_destroy(m_cr);
}

GraphicsContextImpl::GraphicsContextImpl(SurfaceImpl* surface) :
    m_cr(cairo_create(surface->surface()))
{
}

void GraphicsContextImpl::rotate(float radians)
{
    cairo_rotate(m_cr, radians);
}

void GraphicsContextImpl::scale(float x, float y)
{
    cairo_scale(m_cr, x, y);
}

void GraphicsContextImpl::translate(float x, float y)
{
    cairo_translate(m_cr, x, y);
}

void GraphicsContextImpl::concatenate(const AffineTransform& matrix)
{
    const float* m = matrix.getMatrix();
    cairo_matrix_t tr;
    cairo_matrix_init(&tr, m[0], m[1], m[2], m[3], m[4], m[5]);
    cairo_transform(m_cr, &tr);
}

void GraphicsContextImpl::setMatrix(const AffineTransform& matrix)
{
    const float* m = matrix.getMatrix();
    cairo_matrix_t tr;
    cairo_matrix_init(&tr, m[0], m[1], m[2], m[3], m[4], m[5]);
    cairo_set_matrix(m_cr, &tr);
}

AffineTransform GraphicsContextImpl::getMatrix() const
{
    cairo_matrix_t m;
    cairo_get_matrix(m_cr, &m);

    return AffineTransform(m.xx, m.yx, m.xy, m.yy, m.x0, m.y0);
}

void GraphicsContextImpl::clearPath(const Path &path, WindRule fillRule, const Paint &fillPaint)
{
    cairo_save(m_cr);
    set_paint_on_context(m_cr, fillPaint);
    cairo_set_fill_rule(m_cr, static_cast<cairo_fill_rule_t>(fillRule));
    set_path_on_context(m_cr, path);
    cairo_fill(m_cr);
    cairo_restore(m_cr);
}

void GraphicsContextImpl::drawPath(const Path& path, WindRule fillRule, const Paint& fillPaint, const Paint& strokePaint, const StrokeData& strokeData)
{
    if(fillPaint.isNone()&&strokePaint.isNone())
        return;

    cairo_save(m_cr);
    set_path_on_context(m_cr, path);
    set_wind_rule_on_context(m_cr, fillRule);

    if(!fillPaint.isNone())
    {
        set_paint_on_context(m_cr, fillPaint);
        cairo_fill_preserve(m_cr);
    }

    if(!strokePaint.isNone()&&strokeData.width>0.f)
    {
        set_strokedata_on_context(m_cr, strokeData);
        set_paint_on_context(m_cr, strokePaint);
        cairo_stroke_preserve(m_cr);
    }

    cairo_new_path(m_cr);
    cairo_restore(m_cr);
}

void GraphicsContextImpl::pushClip(const Path&, WindRule)
{
}

void GraphicsContextImpl::popClip()
{
}

void GraphicsContextImpl::pushLayer()
{
    cairo_push_group(m_cr);
}

void GraphicsContextImpl::popLayer(float opacity)
{
    cairo_pop_group_to_source(m_cr);
    cairo_paint_with_alpha(m_cr, static_cast<double>(opacity));
}

SurfaceImpl* GraphicsContextImpl::currentLayer() const
{
    return new SurfaceImpl(cairo_get_group_target(m_cr));
}

SurfaceImpl* GraphicsContextImpl::rootLayer() const
{
    return new SurfaceImpl(cairo_get_target(m_cr));
}

void set_path_on_context(cairo_t* cr, const Path& path)
{
    PathIterator it(path);
    float c[6];
    while(!it.isDone())
    {
        switch(it.currentSegment(c))
        {
        case Path::ESegMoveTo:
            cairo_move_to(cr, c[0], c[1]);
            break;
        case Path::ESegLineTo:
            cairo_line_to(cr, c[0], c[1]);
            break;
        case Path::ESegCubicTo:
            cairo_curve_to(cr, c[0], c[1], c[2], c[3], c[4], c[5]);
            break;
        case Path::ESegClose:
            cairo_close_path(cr);
            break;
        case Path::ESegQuadTo:
        {
            double x0, y0;
            cairo_get_current_point(cr, &x0, &y0);
            cairo_curve_to(cr,
                    2.0 / 3.0 * c[0] + 1.0 / 3.0 * x0,
                    2.0 / 3.0 * c[1] + 1.0 / 3.0 * y0,
                    2.0 / 3.0 * c[0] + 1.0 / 3.0 * c[2],
                    2.0 / 3.0 * c[1] + 1.0 / 3.0 * c[3],
                    c[2], c[3]);
            break;
        }
        }
        it.next();
    }
}

void set_paint_on_context(cairo_t* cr, const Paint& paint)
{
    if(paint.type() == EPaintTypeColor)
    {
        const Rgb* c = paint.color();
        cairo_set_source_rgba(cr, c->r/255.0, c->g/255.0, c->b/255.0, (c->a/255.0)*paint.opacity());
    }
    else if(paint.type() == EPaintTypeGradient)
    {
        const Gradient* g = paint.gradient();
        cairo_pattern_t* pattern;
        if(g->type==EGradientTypeLinear)
            pattern = cairo_pattern_create_linear(g->linear.x1, g->linear.y1, g->linear.x2, g->linear.y2);
        else
            pattern = cairo_pattern_create_radial(g->radial.fx, g->radial.fy, 0, g->radial.cx, g->radial.cy, g->radial.r);

        switch(g->spread)
        {
        case ESpreadMethodPad:
            cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
            break;
        case ESpreadMethodReflect:
            cairo_pattern_set_extend(pattern, CAIRO_EXTEND_REFLECT);
            break;
        case ESpreadMethodRepeat:
            cairo_pattern_set_extend(pattern, CAIRO_EXTEND_REPEAT);
            break;
        }

        for(unsigned i=0;i<g->stops.size();i++)
        {
            float offset = g->stops[i].first;
            const Rgb& c = g->stops[i].second;
            cairo_pattern_add_color_stop_rgba(pattern, offset, c.r/255.0, c.g/255.0, c.b/255.0, (c.a/255.0)*paint.opacity());
        }

        const float* m = g->matrix.getMatrix();
        cairo_matrix_t matrix;
        cairo_matrix_init(&matrix, m[0], m[1], m[2], m[3], m[4], m[5]);
        if(cairo_matrix_invert(&matrix) == CAIRO_STATUS_SUCCESS)
            cairo_pattern_set_matrix(pattern, &matrix);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
    }
    else
    {
        cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.0);
    }
}

void set_wind_rule_on_context(cairo_t* cr, WindRule windRule)
{
    switch(windRule)
    {
    case EWindRuleNonZero:
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        break;
    case EWindRuleEvenOdd:
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_EVEN_ODD);
        break;
    }
}

void set_strokedata_on_context(cairo_t* cr, const StrokeData& strokeData)
{
    cairo_set_line_width(cr, static_cast<double>(strokeData.width));
    cairo_set_miter_limit(cr, static_cast<double>(strokeData.miterLimit));

    std::vector<double> dashes(strokeData.dashes.begin(), strokeData.dashes.end());
    cairo_set_dash(cr, &dashes[0], int(dashes.size()), static_cast<double>(strokeData.dashOffset));

    switch(strokeData.cap)
    {
    case ELineCapButt:
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
        break;
    case ELineCapRound:
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
        break;
    case ELineCapSquare:
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
        break;
    }

    switch(strokeData.join)
    {
    case ELineJoinMiter:
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
        break;
    case ELineJoinRound:
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
        break;
    case ELineJoinBevel:
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_BEVEL);
        break;
    }
}

} // namespace lunasvg
