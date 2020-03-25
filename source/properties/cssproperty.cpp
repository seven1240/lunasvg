#include "cssproperty.h"
#include "svgcolor.h"
#include "svgnumber.h"
#include "svglengthlist.h"
#include "svgenumeration.h"
#include "svgstring.h"
#include "path.h"

namespace lunasvg {

template<> const EnumEntryList& getEnumEntryList<Display>()
{
    static EnumEntryList entries;
    if(entries.empty())
    {
        entries.push_back(EnumEntry(EDisplayInline, "inline"));
        entries.push_back(EnumEntry(EDisplayBlock, "block"));
        entries.push_back(EnumEntry(EDisplayNone, "none"));
    }

    return entries;
}

template<> const EnumEntryList& getEnumEntryList<Visibility>()
{
    static EnumEntryList entries;
    if(entries.empty())
    {
        entries.push_back(EnumEntry(EVisibilityVisible, "visible"));
        entries.push_back(EnumEntry(EVisibilityHidden, "hidden"));
        entries.push_back(EnumEntry(EVisibilityCollaspe, "collaspe"));
    }

    return entries;
}

template<> const EnumEntryList& getEnumEntryList<Overflow>()
{
    static EnumEntryList entries;
    if(entries.empty())
    {
        entries.push_back(EnumEntry(EOverflowVisible, "visible"));
        entries.push_back(EnumEntry(EOverflowHidden, "hidden"));
        entries.push_back(EnumEntry(EOverflowScroll, "scroll"));
        entries.push_back(EnumEntry(EOverflowAuto, "auto"));
    }

    return entries;
}

template<> const EnumEntryList& getEnumEntryList<LineCap>()
{
    static EnumEntryList entries;
    if(entries.empty())
    {
        entries.push_back(EnumEntry(ELineCapButt, "butt"));
        entries.push_back(EnumEntry(ELineCapRound, "round"));
        entries.push_back(EnumEntry(ELineCapSquare, "square"));
    }

    return entries;
}

template<> const EnumEntryList& getEnumEntryList<LineJoin>()
{
    static EnumEntryList entries;
    if(entries.empty())
    {
        entries.push_back(EnumEntry(ELineJoinMiter, "miter"));
        entries.push_back(EnumEntry(ELineJoinBevel, "bevel"));
        entries.push_back(EnumEntry(ELineJoinRound, "round"));
    }

    return entries;
}

template<> const EnumEntryList& getEnumEntryList<WindRule>()
{
    static EnumEntryList entries;
    if(entries.empty())
    {
        entries.push_back(EnumEntry(EWindRuleNonZero, "nonzero"));
        entries.push_back(EnumEntry(EWindRuleEvenOdd, "evenodd"));
    }

    return entries;
}

CSSProperty::~CSSProperty()
{
    delete m_value;
}

CSSProperty::CSSProperty(CSSPropertyID propertyId, SVGProperty* value, bool important, bool inherited) :
    SVGProperty(EPropertyTypeCSSProperty),
    m_propertyId(propertyId),
    m_value(value),
    m_important(important),
    m_inherited(inherited)
{
}

CSSProperty* CSSProperty::create(CSSPropertyID propertyId, bool important, bool inherited)
{
    switch(propertyId)
    {
    case CSSPropertyIdFill:
    case CSSPropertyIdStroke:
        return new CSSProperty(propertyId, new SVGPaint(), important, inherited);
    case CSSPropertyIdColor:
    case CSSPropertyIdStop_Color:
        return new CSSProperty(propertyId, new SVGColor(), important, inherited);
    case CSSPropertyIdFill_Opacity:
    case CSSPropertyIdStroke_Opacity:
    case CSSPropertyIdOpacity:
    case CSSPropertyIdStop_Opacity:
        return new CSSProperty(propertyId, new SVGNumberPercentage(), important, inherited);
    case CSSPropertyIdStroke_Miterlimit:
        return new CSSProperty(propertyId, new SVGNumber(), important, inherited);
    case CSSPropertyIdStroke_Width:
    case CSSPropertyIdStroke_Dashoffset:
        return new CSSProperty(propertyId, new SVGLength(), important, inherited);
    case CSSPropertyIdStroke_Dasharray:
        return new CSSProperty(propertyId, new SVGLengthList(), important, inherited);
    case CSSPropertyIdFill_Rule:
    case CSSPropertyIdClip_Rule:
        return new CSSProperty(propertyId, new SVGEnumeration<WindRule>(), important, inherited);
    case CSSPropertyIdStroke_Linecap:
        return new CSSProperty(propertyId, new SVGEnumeration<LineCap>(), important, inherited);
    case CSSPropertyIdStroke_Linejoin:
        return new CSSProperty(propertyId, new SVGEnumeration<LineJoin>(), important, inherited);
    case CSSPropertyIdDisplay:
        return new CSSProperty(propertyId, new SVGEnumeration<Display>(), important, inherited);
    case CSSPropertyIdVisibility:
        return new CSSProperty(propertyId, new SVGEnumeration<Visibility>(), important, inherited);
    case CSSPropertyIdOverflow:
        return new CSSProperty(propertyId, new SVGEnumeration<Overflow>(), important, inherited);
    case CSSPropertyIdClip_Path:
    case CSSPropertyIdMask:
    case CSSPropertyIdMarker_Start:
    case CSSPropertyIdMarker_Mid:
    case CSSPropertyIdMarker_End:
        return new CSSProperty(propertyId, new SVGString(), important, inherited);
    default:
        break;
    }

    return NULL;
}

void CSSProperty::setValue(const SVGProperty* value)
{
    assert(m_value->propertyType() == value->propertyType());

    delete m_value;
    m_value = value->clone();
}

SVGProperty* CSSProperty::clone() const
{
    return new CSSProperty(m_propertyId, m_value->clone(), m_important, m_inherited);
}

bool CSSProperty::setValueAsString(const std::string& value)
{
    if(value=="inherit")
    {
        m_inherited = true;
        return m_value->setValueAsString(KEmptyString);
    }

    return m_value->setValueAsString(value);
}

std::string CSSProperty::valueAsString() const
{
    return m_inherited ? "inherit" : m_value->valueAsString() + (m_important ? "!important" : "");
}

CSSPropertyList::CSSPropertyList() :
    SVGListProperty<CSSProperty> (EPropertyTypeCSSPropertyList)
{
}

CSSProperty* CSSPropertyList::findProperty(CSSPropertyID nameId) const
{
    for(unsigned i=0;i<length();i++)
        if(nameId==at(i)->propertyId())
            return const_cast<CSSProperty*>(at(i));

    return NULL;
}

void CSSPropertyList::addItem(CSSProperty* item)
{
    unsigned index = 0;
    for(;index<length();index++)
        if(at(index)->propertyId()==item->propertyId())
            break;
    if(index < length())
        replaceItem(item, index);
    else
        appendItem(item);
}

bool CSSPropertyList::setValueAsString(const std::string& value)
{
    clear();
    if(value.empty())
        return true;

    const char* ptr = value.c_str();
    Utils::skipWs(ptr);
    while(*ptr)
    {
        if(!IS_CSSID(*ptr))
            return false;
        const char* start = ptr;
        ++ptr;
        while(*ptr && IS_CSSNAMECHAR(*ptr))
            ++ptr;
        std::string name(start, ptr);
        Utils::skipWs(ptr);
        if(!*ptr || *ptr!=':')
            return false;
        ++ptr;
        Utils::skipWs(ptr);
        start = ptr;
        while(*ptr && *ptr!=';')
            ++ptr;
        std::string value(start, ptr);
        Utils::skipWsDelimiter(ptr, ';');
        if(CSSProperty* item = CSSProperty::create(Utils::cssPropertyId(name)))
        {
            item->setValueAsString(value);
            addItem(item);
        }
    }

    return true;
}

std::string CSSPropertyList::valueAsString() const
{
    std::string out;
    for(size_t i=0;i<length();i++)
    {
        out += Utils::cssPropertyName(at(i)->propertyId());
        out += ':';
        out += at(i)->valueAsString();
        out += ';';
    }

    return out;
}

SVGProperty* CSSPropertyList::clone() const
{
    CSSPropertyList*  property = new CSSPropertyList();
    baseClone(property);

    return property;
}

SVGAnimatedStyle::SVGAnimatedStyle(PropertyID propertyId) :
    SVGAnimatedProperty<CSSPropertyList>(propertyId)
{
}

bool SVGAnimatedStyle::setProperty(const std::string& name, const std::string& value)
{
    CSSPropertyID nameId = Utils::cssPropertyId(name);
    if(nameId==CSSPropertyIdUnknown)
        return false;

    CSSProperty* property = ensureBaseValue()->findProperty(nameId);
    if(property)
    {
        property->setValueAsString(value);
        return true;
    }

    CSSProperty* item = CSSProperty::create(nameId);
    if(item)
    {
        item->setValueAsString(value);
        baseValue()->appendItem(item);
        return true;
    }

    return false;
}

std::string SVGAnimatedStyle::getProperty(const std::string& name) const
{
    if(!isBaseSpecified())
        return KEmptyString;

    CSSPropertyID nameId = Utils::cssPropertyId(name);
    if(nameId==CSSPropertyIdUnknown)
        return KEmptyString;

    CSSProperty* property = baseValue()->findProperty(nameId);
    if(property)
        return property->valueAsString();

   return KEmptyString;
}

bool SVGAnimatedStyle::hasProperty(const std::string& name) const
{
    return isBaseSpecified() ? baseValue()->findProperty(Utils::cssPropertyId(name)) : NULL;
}

void SVGAnimatedStyle::removeProperty(const std::string& name)
{
    if(!isBaseSpecified())
        return;

    CSSPropertyID nameId = Utils::cssPropertyId(name);
    if(nameId==CSSPropertyIdUnknown)
        return;

    for(size_t i=0;i<baseValue()->length();i++)
        if(baseValue()->at(i)->propertyId()==nameId)
            baseValue()->removeItem(i);
}

bool SVGAnimatedStyle::isDisplayNone() const
{
    if(!isSpecified())
        return false;

    if(CSSProperty* property = currentValue()->findProperty(CSSPropertyIdDisplay))
    {
        SVGEnumeration<Display>* display = to<SVGEnumeration<Display>>(property->value());
        return display->enumValue() == EDisplayNone;
    }

    return false;
}

bool SVGAnimatedStyle::isHidden() const
{
    if(!isSpecified())
        return false;

    if(CSSProperty* property = currentValue()->findProperty(CSSPropertyIdVisibility))
    {
        SVGEnumeration<Visibility>* visibility = to<SVGEnumeration<Visibility>>(property->value());
        return visibility->enumValue() == EVisibilityHidden;
    }

    return false;
}

} // namespace lunasvg
