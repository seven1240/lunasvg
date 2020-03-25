#ifndef SVGELEMENT_H
#define SVGELEMENT_H

#include <string>

namespace lunasvg {

enum InsertPosition
{
    EBeforeBegin,
    EAfterBegin,
    EBeforeEnd,
    EAfterEnd
};

class SVGDocument;

class SVGElement
{
protected:
    virtual ~SVGElement();

public:
    virtual void setAttribute(const std::string& name, const std::string& value) = 0;
    virtual std::string getAttribute(const std::string& name) const = 0;
    virtual bool hasAttribute(const std::string& name) const = 0;
    virtual void removeAttribute(const std::string& name) = 0;
    virtual const std::string& tagName() const = 0;
    virtual const std::string& id() const = 0;

    SVGElement* getElementById(const std::string& id, int index = 0) const;
    SVGElement* getElementByTag(const std::string& tagName, int index = 0) const;
    SVGElement* insertElement(const SVGElement* element, InsertPosition position);
    SVGElement* appendElement(const SVGElement* element);
    SVGElement* insertContent(const std::string& content, InsertPosition position);
    SVGElement* appendContent(const std::string& content);
    void clearContent();
    void removeElement();

    SVGDocument* owner() const;
    SVGElement* parentElement() const;

protected:
    SVGElement(SVGDocument* document);

private:
    SVGDocument* m_owner;
};

inline SVGDocument* SVGElement::owner() const
{
    return m_owner;
}

} // namespace lunasvg

#endif // SVGELEMENT_H
