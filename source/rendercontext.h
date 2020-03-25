#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H

#include "cssproperty.h"
#include "affinetransform.h"
#include "rect.h"
#include "graphicscontext.h"

#include <stack>
#include <set>

namespace lunasvg {

class SVGElementImpl;

class RenderStyle
{
public:
    RenderStyle();
    void add(const CSSPropertyList* items);
    void add(const SVGAnimatedStyle& style);
    void add(const RenderStyle& style);
    void inheritFrom(const RenderStyle& style);
    void set(const CSSProperty* item);
    const SVGProperty* get(CSSPropertyID nameId) const;
    bool isSet(CSSPropertyID nameId) const;
    bool isEmpty() const;
    void clear(CSSPropertyID nameId);
    void clearAll();

    bool isCompositing() const;
    bool isDisplayNone() const;
    bool isHidden() const;
    float opacity() const;

private:
    std::vector<const SVGProperty*> m_properties;
};

class RenderState
{
public:
    SVGElementImpl* element;
    Rect bbox;
    Rect viewBox;
    RenderStyle style;
    AffineTransform matrix;
    Rgb color;
    float dpi;

    inline RenderState()
    {
        element = NULL;
        dpi = 96.f;
    }
};

class RenderBreaker
{
public:
    static void registerElement(const SVGElementImpl* element);
    static void unregisterElement(const SVGElementImpl* element);
    static bool hasElement(const SVGElementImpl* element);

private:
   static std::set<const SVGElementImpl*> elementSet;
};

class RenderContext
{
public:
    ~RenderContext();
    RenderContext();

    RenderState& state() const { return *m_state; }
    SVGElementImpl* current() const { return m_current; }
    void skipElement();
    void render(GraphicsContext& gc, SVGElementImpl* head, SVGElementImpl* tail);
    void push();
    void pop();

private:
    RenderState* m_state;
    std::stack<RenderState*> m_states;
    SVGElementImpl* m_current;
};

} // namespace lunasvg

#endif // RENDERCONTEXT_H
