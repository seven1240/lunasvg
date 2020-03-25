#ifndef SURFACE_H
#define SURFACE_H

#include "refptr.h"

namespace lunasvg {

class SurfaceImpl;
class Bitmap;

class Surface
{
public:
    ~Surface();
    Surface();
    Surface(unsigned int width, unsigned height);
    Surface(const Surface& surface);
    Surface(const RefPtr<SurfaceImpl>& impl);
    Surface(SurfaceImpl* impl);

    void copyToBitmap(Bitmap& bitmap) const;
    unsigned int width() const;
    unsigned int height() const;
    SurfaceImpl* impl() const { return m_impl.get(); }

private:
    RefPtr<SurfaceImpl> m_impl;
};

} // namespace lunasvg

#endif // SURFACE_H
