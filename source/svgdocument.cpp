#include "svgdocument.h"
#include "svgdocumentimpl.h"
#include "svgrootelement.h"

namespace lunasvg {

SVGDocument::SVGDocument()
{
    m_impl = new SVGDocumentImpl(this);
}

SVGElement* SVGDocument::getElementById(const std::string& id, int index) const
{
    return m_impl->rootElement()->getElementById(id, index);
}

SVGElement* SVGDocument::getElementByTag(const std::string& tag, int index) const
{
    return m_impl->rootElement()->getElementByTag(tag, index);
}

SVGElement* SVGDocument::insertContent(const std::string& content, InsertPosition position)
{
    return m_impl->rootElement()->insertContent(content, position);
}

SVGElement* SVGDocument::appendContent(const std::string& content)
{
    return m_impl->rootElement()->appendContent(content);
}

void SVGDocument::clearContent()
{
    m_impl->rootElement()->clearContent();
}

bool SVGDocument::loadFromFile(const std::string& filename)
{
    return m_impl->loadFromFile(filename);
}

bool SVGDocument::loadFromData(const std::string& content)
{
    return m_impl->loadFromData(content);
}

void SVGDocument::dimensions(int &width, int &height, float dpi) const
{
    m_impl->dimensions(width, height, dpi);
}

void SVGDocument::render(Bitmap &bitmap, float dpi, unsigned int bgColor, const std::string &viewId)
{
    m_impl->render(bitmap, dpi, bgColor, viewId);
}

SVGElement* SVGDocument::insertElement(const SVGElement* element, InsertPosition position)
{
    return m_impl->rootElement()->insertElement(element, position);
}

SVGElement* SVGDocument::appendElement(const SVGElement* element)
{
    return m_impl->rootElement()->appendElement(element);
}

SVGElement* SVGDocument::rootElement() const
{
    return m_impl->rootElement();
}

SVGDocument::~SVGDocument()
{
    delete m_impl;
}

} // namespace lunasvg
