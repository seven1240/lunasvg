#include "svgrootelement.h"

namespace lunasvg {

SVGRootElement::SVGRootElement(SVGDocument* document) :
    SVGSVGElement(document)
{
}

SVGElementImpl* SVGRootElement::clone(SVGDocument* document) const
{
    SVGRootElement* e = new SVGRootElement(document);
    baseClone(*e);
    return  e;
}

} // namespace lunasvg
