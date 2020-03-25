#ifndef SVGCOLOR_H
#define SVGCOLOR_H

#include "svgproperty.h"
#include "rgb.h"

namespace lunasvg {

enum ColorType
{
    EColorTypeNone,
    EColorTypeCurrentColor,
    EColorTypeRgb
};

class RenderState;
class Paint;

class SVGColor : public SVGProperty
{
public:
    SVGColor();

    void setValue(const Rgb& value) { m_value = value; }
    void setColorType(ColorType type) { m_colorType = type; }
    const Rgb& value() const { return m_value; }
    ColorType colorType() const { return m_colorType; }

    virtual Paint getPaint(const RenderState& state) const;
    virtual bool setValueAsString(const std::string& value);
    virtual std::string valueAsString() const;
    virtual SVGProperty* clone() const;
    static PropertyType classType() { return EPropertyTypeColor; }

protected:
    ColorType m_colorType;
    Rgb m_value;
};

class SVGPaint : public SVGColor
{
public:
    ~SVGPaint();
    SVGPaint();

    void setUrl(const std::string& href) { m_url = href; }
    const std::string& url() { return  m_url; }

    Paint getPaint(const RenderState& state) const;
    bool setValueAsString(const std::string& value);
    std::string valueAsString() const;
    SVGProperty* clone() const;

private:
    std::string m_url;
    SVGColor* m_fallbackColor;
};

} // namespace lunasvg

#endif // SVGCOLOR_H
