#ifndef SVGANIMATEDSTYLE_H
#define SVGANIMATEDSTYLE_H

#include "svglistproperty.h"
#include "strokedata.h"

namespace lunasvg {

enum Display
{
    EDisplayInline,
    EDisplayBlock,
    EDisplayNone,
};

enum Visibility
{
   EVisibilityHidden,
   EVisibilityVisible,
   EVisibilityCollaspe
};

enum Overflow
{
    EOverflowVisible,
    EOverflowHidden,
    EOverflowScroll,
    EOverflowAuto
};

class CSSProperty : public SVGProperty
{
public:
    ~CSSProperty();
    static CSSProperty* create(CSSPropertyID propertyId, bool important=false, bool inherited=false);
    void setValue(const SVGProperty* value);
    SVGProperty* value() const { return m_value; }
    void setImportant(bool important) { m_important = important; }
    void setInherited(bool inherited) { m_inherited = inherited; }
    bool isImportant() const { return m_important; }
    bool isInherited() const { return m_inherited; }
    CSSPropertyID propertyId() const { return m_propertyId; }

    bool setValueAsString(const std::string& value);
    std::string valueAsString() const;
    SVGProperty* clone() const;
    static PropertyType classType() { return EPropertyTypeCSSProperty; }

private:
    CSSProperty(CSSPropertyID propertyID, SVGProperty* value, bool important, bool inherited);

private:
    CSSPropertyID m_propertyId;
    SVGProperty* m_value;
    bool m_important;
    bool m_inherited;
};

class CSSPropertyList : public SVGListProperty<CSSProperty>
{
public:
    CSSPropertyList();

    CSSProperty* findProperty(CSSPropertyID nameId) const;
    void addItem(CSSProperty* item);

    bool setValueAsString(const std::string& value);
    std::string valueAsString() const;
    SVGProperty* clone() const;
    static PropertyType classType() { return EPropertyTypeCSSPropertyList; }
};

class SVGAnimatedStyle : public SVGAnimatedProperty<CSSPropertyList>
{
public:
    SVGAnimatedStyle(PropertyID propertyId);

    bool setProperty(const std::string& name, const std::string& value);
    std::string getProperty(const std::string& name) const;
    bool hasProperty(const std::string& name) const;
    void removeProperty(const std::string& name);

    bool isDisplayNone() const;
    bool isHidden() const;
};

} // namespace lunasvg

#endif // SVGANIMATEDSTYLE_H
