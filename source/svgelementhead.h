#ifndef SVGELEMENTHEAD_H
#define SVGELEMENTHEAD_H

#include "svgelementimpl.h"
#include "cssproperty.h"

#include <vector>
#include <set>

namespace lunasvg {

class SVGElementTail;

class SVGElementHead : public SVGElementImpl
{
public:
    virtual ~SVGElementHead();
    virtual bool setProperty(PropertyID nameId, const std::string& value);
    virtual std::string getProperty(PropertyID nameId) const;
    virtual bool hasProperty(PropertyID nameId) const;
    virtual void removeProperty(PropertyID nameId);
    virtual void render(GraphicsContext&, RenderContext&);
    virtual void renderTail(GraphicsContext&, RenderContext&);
    void setAttribute(const std::string& name, const std::string& value);
    std::string getAttribute(const std::string& name) const;
    bool hasAttribute(const std::string& name) const;
    void removeAttribute(const std::string& name);
    const std::string& tagName() const;
    const std::string& id() const { return m_id; }
    ElementID elementId() const { return m_elementId; }
    const SVGAnimatedString& className() const { return m_className; }
    const SVGAnimatedStyle& style() const { return m_style; }
    bool isSVGElementHead() const { return true; }

    SVGElementTail* tail;

    SVGAnimatedPropertyBase* findAnimatedProperty(PropertyID nameId) const;
    void addToPropertyMap(SVGAnimatedPropertyBase& property);
    void updateId(const std::string& newValue);

protected:
    SVGElementHead(ElementID elementId, SVGDocument* document);
    void baseClone(SVGElementHead& e) const;

private:
    ElementID m_elementId;
    std::string m_id;
    SVGAnimatedString m_className;
    SVGAnimatedStyle m_style;
    std::vector<SVGAnimatedPropertyBase*> m_properties;
};

} // namespace lunasvg

#endif // SVGELEMENTHEAD_H
