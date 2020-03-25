#ifndef SVGELEMENTTAIL_H
#define SVGELEMENTTAIL_H

#include "svgelementimpl.h"

namespace lunasvg {

class SVGElementTail : public SVGElementImpl
{
public:
    SVGElementTail(SVGDocument* document);
    bool isSVGElementTail() const { return true; }
    void render(GraphicsContext &gc, RenderContext& context);
    SVGElementImpl* clone(SVGDocument* document) const;
};

} // namespace lunasvg

#endif // SVGELEMENTTAIL_H
