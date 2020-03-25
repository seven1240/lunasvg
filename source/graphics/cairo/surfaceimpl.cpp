#include "surfaceimpl.h"
#include "svgdocument.h"

#include <assert.h>

namespace lunasvg {

SurfaceImpl::SurfaceImpl(unsigned int width, unsigned height) :
    m_surface(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, int(width), int(height)))
{
}

SurfaceImpl::SurfaceImpl(cairo_surface_t* surface) :
    m_surface(cairo_surface_reference(surface))
{
}

void SurfaceImpl::copyToBitmap(Bitmap& bitmap) const
{
    assert(bitmap.width == width());
    assert(bitmap.height == height());

    unsigned char* data = cairo_image_surface_get_data(m_surface);
    unsigned char* ptr = bitmap.pixels;
    unsigned char* end = ptr + bitmap.height * bitmap.width * 4;
    while(ptr < end)
    {
        ptr[3] = data[3];
        if(data[3] != 0)
        {
            ptr[0] = (data[2] * 255) / data[3];
            ptr[1] = (data[1] * 255) / data[3];
            ptr[2] = (data[0] * 255) / data[3];
        }
        else
        {
            ptr[0] = 0;
            ptr[1] = 0;
            ptr[2] = 0;
        }

        ptr += 4;
        data += 4;
    }
}

unsigned int SurfaceImpl::width() const
{
    return cairo_image_surface_get_width(m_surface);
}

unsigned int SurfaceImpl::height() const
{
    return cairo_image_surface_get_height(m_surface);
}

SurfaceImpl::~SurfaceImpl()
{
    cairo_surface_destroy(m_surface);
}

} // namespace lunasvg
