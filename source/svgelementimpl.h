#ifndef SVGELEMENTIMPL_H
#define SVGELEMENTIMPL_H

#include "svgelement.h"
#include "svgelementutils.h"
#include "svgstring.h"

namespace lunasvg {

class SVGElementHead;
class GraphicsContext;
class RenderContext;

template<typename T>
inline T* to(SVGElement* element)
{
    return static_cast<T*>(element);
}

template<typename T>
inline const T* to(const SVGElement* element)
{
    return static_cast<const T*>(element);
}

class SVGElementImpl : public SVGElement
{
public:
    virtual ~SVGElementImpl();
    virtual void setAttribute(const std::string&, const std::string&) {}
    virtual std::string getAttribute(const std::string&) const { return std::string(); }
    virtual bool hasAttribute(const std::string&) const { return false; }
    virtual void removeAttribute(const std::string&) {}
    virtual const std::string& tagName() const { return KEmptyString; }
    virtual const std::string& id() const { return KEmptyString; }
    virtual ElementID elementId() const { return EElementIdUnknown; }
    virtual void render(GraphicsContext& gc, RenderContext& context) = 0;
    virtual SVGElementImpl* clone(SVGDocument* document) const = 0;

    SVGElementHead* parent;
    SVGElementImpl* next;
    SVGElementImpl* prev;

    virtual bool isSVGElementHead() const { return false; }
    virtual bool isSVGElementTail() const { return false; }
    virtual bool isSVGPresentationElement() const { return false; }
    virtual bool isSVGRootElement() const { return false; }
    virtual bool isSVGGraphicsElement() const { return false; }
    virtual bool isSVGGeometryElement() const { return false; }
    virtual bool isSVGPaintElement() const { return false; }
    virtual bool isSVGGradientElement() const { return false; }
    virtual bool isSVGPolyElement() const { return false; }
    virtual bool isSVGAnimationElement() const { return false; }

protected:
    SVGElementImpl(SVGDocument* document);
};

} // namespace lunasvg

#endif // SVGELEMENTIMPL_H
