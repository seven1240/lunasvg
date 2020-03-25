#include "svgenumeration.h"

namespace lunasvg {

void SVGEnumerationBase::setValue(unsigned short value)
{
    m_value = value;
}

bool SVGEnumerationBase::setValueAsString(const std::string& value)
{
    m_value = 0;
    if(value.empty())
        return true;

    for(unsigned i=0;i<m_entries.size();i++)
    {
        if(m_entries[i].second == value)
        {
            m_value = m_entries[i].first;
            return true;
        }
    }

    return false;
}

std::string SVGEnumerationBase::valueAsString() const
{
    for(unsigned i=0;i<m_entries.size();i++)
        if(m_entries[i].first == m_value)
            return m_entries[i].second;

    return std::string();
}

} //namespace lunasvg
