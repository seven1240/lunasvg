#include "surface.h"

#ifdef LUNA_SVG_ENABLE_CAIRO
#    include "cairo/surfaceimpl.h"
#endif

namespace lunasvg {

Surface::~Surface()
{
}

Surface::Surface() :
    m_impl(NULL)
{
}

Surface::Surface(unsigned int width, unsigned height) :
    m_impl(new SurfaceImpl(width, height))
{
}

Surface::Surface(const Surface& surface) :
    m_impl(surface.m_impl)
{
}

Surface::Surface(const RefPtr<SurfaceImpl>& impl) :
    m_impl(impl)
{
}

Surface::Surface(SurfaceImpl* impl) :
    m_impl(impl)
{
}

void Surface::copyToBitmap(Bitmap &bitmap) const
{
    m_impl->copyToBitmap(bitmap);
}

unsigned int Surface::width() const
{
    return m_impl->width();
}

unsigned int Surface::height() const
{
    return m_impl->height();
}

} // namespace lunasvg
