#ifndef SVGUSEELEMENT_H
#define SVGUSEELEMENT_H

#include "svggraphicselement.h"
#include "svgurireference.h"
#include "svglength.h"

namespace lunasvg {

class SVGUseElement : public SVGGraphicsElement,
                      public SVGURIReference
{
public:
    SVGUseElement(SVGDocument* document);
    const SVGAnimatedLength& x() const { return m_x; }
    const SVGAnimatedLength& y() const { return m_y; }
    const SVGAnimatedLength& width() const { return m_width; }
    const SVGAnimatedLength& height() const { return m_height; }
    void render(GraphicsContext& gc, RenderContext& context);
    SVGElementImpl* clone(SVGDocument* document) const;

private:
    SVGAnimatedLength m_x;
    SVGAnimatedLength m_y;
    SVGAnimatedLength m_width;
    SVGAnimatedLength m_height;
};

} // namespace lunasvg

#endif // SVGUSEELEMENT_H
