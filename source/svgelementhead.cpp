#include "svgelementhead.h"
#include "svgelementtail.h"
#include "svgdocumentimpl.h"
#include "rendercontext.h"

namespace lunasvg {

SVGElementHead::SVGElementHead(ElementID elementId, SVGDocument* document) :
    SVGElementImpl(document),
    m_elementId(elementId),
    m_className(EPropertyIdClass),
    m_style(EPropertyIdStyle)
{
    addToPropertyMap(m_className);
    addToPropertyMap(m_style);
}

SVGElementHead::~SVGElementHead()
{
    owner()->impl()->updateIdCache(m_id, KEmptyString, this);
}

const std::string& SVGElementHead::tagName() const
{
    return Utils::elementName(m_elementId);
}

void SVGElementHead::setAttribute(const std::string& name, const std::string& value)
{
    PropertyID nameId = Utils::propertyId(name);
    if(nameId!=EPropertyIdUnknown)
        setProperty(nameId, value);

    m_style.setProperty(name, value);
}

std::string SVGElementHead::getAttribute(const std::string& name) const
{
    PropertyID nameId = Utils::propertyId(name);
    if(nameId!=EPropertyIdUnknown)
        return getProperty(nameId);

    return m_style.getProperty(name);
}

bool SVGElementHead::hasAttribute(const std::string& name) const
{
    PropertyID nameId = Utils::propertyId(name);
    if(nameId!=EPropertyIdUnknown)
        return hasProperty(nameId);

    return m_style.hasProperty(name);
}

void SVGElementHead::removeAttribute(const std::string& name)
{
    PropertyID nameId = Utils::propertyId(name);
    if(nameId!=EPropertyIdUnknown)
        removeProperty(nameId);

    m_style.removeProperty(name);
}

std::string SVGElementHead::getProperty(PropertyID nameId) const
{
    if(nameId==EPropertyIdId)
        return m_id;

    for(unsigned i=0;i<m_properties.size();i++)
        if(nameId==m_properties[i]->propertyId())
            return m_properties[i]->baseValueAsString();

    return KEmptyString;
}

bool SVGElementHead::hasProperty(PropertyID nameId) const
{
    for(unsigned i=0;i<m_properties.size();i++)
        if(nameId==m_properties[i]->propertyId())
            return m_properties[i]->isBaseSpecified();

    return false;
}

bool SVGElementHead::setProperty(PropertyID nameId, const std::string& value)
{
    if(nameId==EPropertyIdId)
    {
        updateId(value);
        return true;
    }

    for(unsigned i=0;i<m_properties.size();i++)
        if(nameId==m_properties[i]->propertyId())
            return m_properties[i]->setBaseValueAsString(value);

    return false;
}

void SVGElementHead::removeProperty(PropertyID nameId)
{
    if(nameId==EPropertyIdId)
    {
        updateId(KEmptyString);
        return;
    }

    for(unsigned i=0;i<m_properties.size();i++)
        if(nameId==m_properties[i]->propertyId())
            return m_properties[i]->resetBaseValue();
}

void SVGElementHead::render(GraphicsContext&, RenderContext& context)
{
    context.skipElement();
}

void SVGElementHead::renderTail(GraphicsContext&, RenderContext&)
{
}

SVGAnimatedPropertyBase* SVGElementHead::findAnimatedProperty(PropertyID nameId) const
{
    for(unsigned i=0;i<m_properties.size();i++)
        if(nameId==m_properties[i]->propertyId())
            return m_properties[i];

    return NULL;
}

void SVGElementHead::addToPropertyMap(SVGAnimatedPropertyBase& property)
{
    m_properties.push_back(&property);
}

void SVGElementHead::updateId(const std::string &newValue)
{
    SVGDocumentImpl* impl = owner()->impl();
    impl->updateIdCache(m_id, newValue, this);
    m_id.assign(newValue);
}

void SVGElementHead::baseClone(SVGElementHead& e) const
{
    e.updateId(e.m_id);
    for(unsigned i=0;i<m_properties.size();i++)
        e.m_properties[i]->clone(m_properties[i]);
}

} // namespace lunasvg
