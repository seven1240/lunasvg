#ifndef SVGDOCUMENTIMPL_H
#define SVGDOCUMENTIMPL_H

#include "svgdocument.h"

#include <map>

namespace lunasvg {

class SVGElementImpl;
class SVGRootElement;
class SVGElementHead;
class SVGParser;

class SVGDocumentImpl
{
public:
    SVGDocumentImpl(SVGDocument* document);
    ~SVGDocumentImpl();

    void dimensions(int& width, int& height, float dpi = 96.f) const;
    void render(Bitmap& bitmap, float dpi = 96.f, unsigned int bgColor = 0x00000000, const std::string& viewId = std::string());

    bool loadFromFile(const std::string& filename);
    bool loadFromData(const std::string& content);
    void updateIdCache(const std::string &oldValue, const std::string &newValue, SVGElementHead* element);
    SVGElementImpl* resolveIRI(const std::string& href) const;
    SVGElementImpl* insertContent(const std::string& content, SVGElementImpl* target, InsertPosition position);
    SVGElementImpl* copyElement(const SVGElementImpl* element, SVGElementImpl* target, InsertPosition);
    SVGElementImpl* moveElement(SVGElementImpl* element, SVGElementImpl* target, InsertPosition);
    void clearContent(SVGElementImpl* element);
    void removeElement(SVGElementImpl* element);
    void insertElement(SVGElementImpl* head, SVGElementImpl* tail, SVGElementImpl* target, InsertPosition position);
    void freeElement(SVGElementImpl* head, SVGElementImpl* tail);
    SVGRootElement* rootElement() const { return m_rootElement; }

private:
    void dispatchElementRemoveEvent(SVGElementImpl*, SVGElementImpl*) {}
    void dispatchElementInsertEvent(SVGElementImpl*, SVGElementImpl*) {}

private:
    SVGRootElement* m_rootElement;
    SVGParser* m_svgParser;
    std::multimap<std::string, SVGElementImpl*> m_idCache;
};

} // namespace lunasvg

#endif // SVGDOCUMENTIMPL_H
