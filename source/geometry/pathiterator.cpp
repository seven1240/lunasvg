#include "pathiterator.h"
#include "point.h"

namespace lunasvg
{

PathIterator::PathIterator(const Path& path) :
    m_pointSegs(path.getPointSegs()),
    m_pointCoords(path.getPointCoords()),
    m_segIndex(0),
    m_coordIndex(0)
{
}

Path::SegType PathIterator::currentSegment(float* coords) const
{
    Path::SegType segType = m_pointSegs[m_segIndex];

    switch(segType)
    {
        case Path::ESegMoveTo:
            coords[0] = m_pointCoords[m_coordIndex];
            coords[1] = m_pointCoords[m_coordIndex + 1];
            m_startPoint.x = coords[0];
            m_startPoint.y = coords[1];
            break;
        case Path::ESegLineTo:
            coords[0] = m_pointCoords[m_coordIndex];
            coords[1] = m_pointCoords[m_coordIndex + 1];
            break;
        case Path::ESegQuadTo:
            coords[0] = m_pointCoords[m_coordIndex];
            coords[1] = m_pointCoords[m_coordIndex + 1];
            coords[2] = m_pointCoords[m_coordIndex + 2];
            coords[3] = m_pointCoords[m_coordIndex + 3];
            break;
        case Path::ESegCubicTo:
            coords[0] = m_pointCoords[m_coordIndex];
            coords[1] = m_pointCoords[m_coordIndex + 1];
            coords[2] = m_pointCoords[m_coordIndex + 2];
            coords[3] = m_pointCoords[m_coordIndex + 3];
            coords[4] = m_pointCoords[m_coordIndex + 4];
            coords[5] = m_pointCoords[m_coordIndex + 5];
            break;
        case Path::ESegClose:
            coords[0] = m_startPoint.x;
            coords[1] = m_startPoint.y;
            break;
    }

    return segType;
}

bool PathIterator::isDone() const
{
    return (m_segIndex >= m_pointSegs.size());
}

void PathIterator::next()
{
    if(m_segIndex < m_pointSegs.size())
    {
        switch(m_pointSegs[m_segIndex])
        {
            case Path::ESegMoveTo:
                m_coordIndex += 2;
                break;
            case Path::ESegLineTo:
                m_coordIndex += 2;
                break;
            case Path::ESegQuadTo:
                m_coordIndex += 4;
                break;
            case Path::ESegCubicTo:
                m_coordIndex += 6;
                break;
            default:
                break;
        }
        m_segIndex += 1;
    }
}

} //namespace lunasvg
