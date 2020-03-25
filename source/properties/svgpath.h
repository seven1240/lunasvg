#ifndef SVGPATH_H
#define SVGPATH_H

#include "svgproperty.h"
#include "path.h"

namespace lunasvg {

class SVGPath : public SVGProperty
{
public:
    SVGPath();

    void setValue(const Path& value) { m_value = value; }
    const Path& value() const { return  m_value; }

    static bool parseArcFlag(const char*& ptr, bool& flag);
    bool setValueAsString(const std::string& value);
    std::string valueAsString() const;
    SVGProperty* clone() const;
    static PropertyType classType() { return EPropertyTypePath; }

private:
    Path m_value;
};

typedef SVGAnimatedProperty<SVGPath> SVGAnimatedPath;

} // namespace lunasvg

#endif // SVGPATH_H
