#ifndef SVGURIREFERENCE_H
#define SVGURIREFERENCE_H

#include "svgstring.h"

namespace lunasvg {

class SVGElementHead;

class SVGURIReference
{
public:
    const SVGAnimatedString& href() const { return m_href; }
    const std::string& hrefValue() const;

protected:
    SVGURIReference(SVGElementHead* owner);

private:
    SVGAnimatedString m_href;
};

} // namespace lunasvg

#endif // SVGURIREFERENCE_H
