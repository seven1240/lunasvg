#ifndef SVGDOCUMENT_H
#define SVGDOCUMENT_H

#include "svgelement.h"

namespace lunasvg {

struct Bitmap
{
    unsigned char* pixels;
    unsigned int width;
    unsigned int height;
};

class SVGDocumentImpl;

class SVGDocument
{
public:
    SVGDocument();
    ~SVGDocument();

    SVGElement* getElementById(const std::string& id, int index = 0) const;
    SVGElement* getElementByTag(const std::string& tagName, int index = 0) const;
    SVGElement* insertElement(const SVGElement* element, InsertPosition position);
    SVGElement* appendElement(const SVGElement* element);
    SVGElement* insertContent(const std::string& content, InsertPosition position);
    SVGElement* appendContent(const std::string& content);
    void clearContent();

    bool loadFromFile(const std::string& filename);
    bool loadFromData(const std::string& content);

    void dimensions(int& width, int& height, float dpi = 96.f) const;
    void render(Bitmap& bitmap, float dpi = 96.f, unsigned int bgColor = 0x00000000, const std::string& viewId = std::string());

    bool setCurrentTime(double time, bool seekToTime=false);
    double currentTime() const;

    SVGElement* rootElement() const;
    SVGDocumentImpl* impl() const;

private:
    SVGDocumentImpl* m_impl;
};

inline SVGDocumentImpl* SVGDocument::impl() const
{
    return m_impl;
}

} //namespace lunasvg

#endif // SVGDOCUMENT_H
