#ifndef SURFACEIMPL_H
#define SURFACEIMPL_H

#include <cairo/cairo.h>

namespace lunasvg {

class Bitmap;

class SurfaceImpl
{
public:
    ~SurfaceImpl();
    SurfaceImpl(unsigned int width, unsigned height);
    SurfaceImpl(cairo_surface_t* surface);

    void copyToBitmap(Bitmap& bitmap) const;
    unsigned int width() const;
    unsigned int height() const;
    cairo_surface_t* surface() const { return m_surface; }

private:
    cairo_surface_t* m_surface;
};

} // namespace lunasvg

#endif // SURFACECAIROIMPL_H
