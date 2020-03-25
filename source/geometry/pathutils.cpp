#include "pathutils.h"
#include <cmath>

namespace lunasvg
{

namespace Utils
{

static void path_arc_segment(Path& path, float xc, float yc, float th0, float th1, float rx, float ry, float xAxisRotation)
{
    float sinTh, cosTh;
    float a00, a01, a10, a11;
    float x1, y1, x2, y2, x3, y3;
    float t;
    float thHalf;

    sinTh = sinf(xAxisRotation * float(M_PI / 180.0));
    cosTh = cosf(xAxisRotation * float(M_PI / 180.0));

    a00 =  cosTh * rx;
    a01 = -sinTh * ry;
    a10 =  sinTh * rx;
    a11 =  cosTh * ry;

    thHalf = 0.5f * (th1 - th0);
    t = (8.f / 3.f) * sinf(thHalf * 0.5f) * sinf(thHalf * 0.5f) / sinf(thHalf);
    x1 = xc + cosf(th0) - t * sinf(th0);
    y1 = yc + sinf(th0) + t * cosf(th0);
    x3 = xc + cosf(th1);
    y3 = yc + sinf(th1);
    x2 = x3 + t * sinf(th1);
    y2 = y3 - t * cosf(th1);

    path.cubicTo(a00 * x1 + a01 * y1,
        a10 * x1 + a11 * y1,
        a00 * x2 + a01 * y2,
        a10 * x2 + a11 * y2,
        a00 * x3 + a01 * y3,
        a10 * x3 + a11 * y3);
}

void pathArcTo(Path& path, float rx, float ry, float xAxisRotation, bool largeArcFlag, bool sweepFlag, float x, float y, bool rel)
{
    Point cp = path.currentPoint();
    if(rel)
    {
        x += cp.x;
        y += cp.y;
    }

    float sin_th, cos_th;
    float a00, a01, a10, a11;
    float x0, y0, x1, y1, xc, yc;
    float d, sfactor, sfactor_sq;
    float th0, th1, th_arc;
    int i, n_segs;
    float dx, dy, dx1, dy1, Pr1, Pr2, Px, Py, check;

    rx = fabsf(rx);
    ry = fabsf(ry);

    sin_th = sinf(xAxisRotation * float(M_PI / 180.0));
    cos_th = cosf(xAxisRotation * float(M_PI / 180.0));

    dx = (cp.x - x) / 2.f;
    dy = (cp.y - y) / 2.f;
    dx1 =  cos_th * dx + sin_th * dy;
    dy1 = -sin_th * dx + cos_th * dy;
    Pr1 = rx * rx;
    Pr2 = ry * ry;
    Px = dx1 * dx1;
    Py = dy1 * dy1;
    /* Spec : check if radii are large enough */
    check = Px / Pr1 + Py / Pr2;
    if (check > 1) {
        rx = rx * sqrtf(check);
        ry = ry * sqrtf(check);
    }

    a00 =  cos_th / rx;
    a01 =  sin_th / rx;
    a10 = -sin_th / ry;
    a11 =  cos_th / ry;
    x0 = a00 * cp.x + a01 * cp.y;
    y0 = a10 * cp.x + a11 * cp.y;
    x1 = a00 * x + a01 * y;
    y1 = a10 * x + a11 * y;
    /* (x0, y0) is current point in transformed coordinate space.
       (x1, y1) is new point in transformed coordinate space.

       The arc fits a unit-radius circle in this space.
    */
    d = (x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0);
    sfactor_sq = 1.f / d - 0.25f;
    if (sfactor_sq < 0) sfactor_sq = 0;
    sfactor = sqrtf(sfactor_sq);
    if (sweepFlag == largeArcFlag) sfactor = -sfactor;
    xc = 0.5f * (x0 + x1) - sfactor * (y1 - y0);
    yc = 0.5f * (y0 + y1) + sfactor * (x1 - x0);
    /* (xc, yc) is center of the circle. */

    th0 = atan2f(y0 - yc, x0 - xc);
    th1 = atan2f(y1 - yc, x1 - xc);

    th_arc = th1 - th0;
    if (th_arc < 0 && sweepFlag)
        th_arc += float(2 * M_PI);
    else if (th_arc > 0 && !sweepFlag)
        th_arc -= float(2 * M_PI);

    n_segs = int(ceilf(fabsf(th_arc / float(M_PI * 0.5 + 0.001))));
    for (i = 0; i < n_segs; i++) {
        path_arc_segment(path, xc, yc,
            th0 + i * th_arc / n_segs,
            th0 + (i + 1) * th_arc / n_segs,
            rx, ry, xAxisRotation);
    }

    path.lineTo(x, y);
}

} // namespace Utils

} // namespace lunasvg
