#ifndef SVGGRAPHICSELEMENT_H
#define SVGGRAPHICSELEMENT_H

#include "svgelementhead.h"
#include "svgtransformlist.h"
#include "rendercontext.h"

namespace lunasvg {

class RenderState;

class SVGGraphicsElement : public SVGElementHead
{
public:
    virtual ~SVGGraphicsElement();
    bool isSVGGraphicsElement() const { return true; }
    const SVGAnimatedTransformList& transform() const { return m_transform; }
    AffineTransform* animateMotionMatrix();
    void setupGc(GraphicsContext& gc, const RenderState& state);
    virtual void render(GraphicsContext& gc, RenderContext& context);
    virtual void renderTail(GraphicsContext& gc, RenderContext& context);

protected:
    SVGGraphicsElement(ElementID elementId, SVGDocument* document);

private:
    SVGAnimatedTransformList m_transform;
    AffineTransform* m_animateMotionMatrix;
};

} // namespace lunasvg

#endif // SVGGRAPHICSELEMENT_H
