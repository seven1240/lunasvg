#ifndef SVGROOTELEMENT_H
#define SVGROOTELEMENT_H

#include "svgsvgelement.h"

namespace lunasvg {

class SVGRootElement : public SVGSVGElement
{
public:
    SVGRootElement(SVGDocument* document);
    bool isSVGRootElement() const { return true; }
    SVGElementImpl* clone(SVGDocument* document) const;
};

} // namespace lunasvg

#endif // SVGROOTELEMENT_H
