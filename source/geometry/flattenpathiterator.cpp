#include "flattenpathiterator.h"

namespace lunasvg
{

FlattenPathIterator::FlattenPathIterator(const Path& path, unsigned int limit) :
    m_pathIterator(path),
    m_segType(Path::ESegClose),
    m_recursionLimit(limit),
    m_coordIndex(0)
{
   next();
}

Path::SegType FlattenPathIterator::currentSegment(float* coords) const
{
    if(m_coordIndex < m_pointCoords.size())
    {
        coords[0] = m_pointCoords[m_coordIndex];
        coords[1] = m_pointCoords[m_coordIndex + 1];
    }

    return m_segType;
}

bool FlattenPathIterator::isDone() const
{
    return (m_coordIndex >= m_pointCoords.size()) && m_pathIterator.isDone();
}

void FlattenPathIterator::next()
{
    m_coordIndex += 2;

    if(m_coordIndex >= m_pointCoords.size())
    {
        m_pointCoords.clear();
        m_coordIndex = 0;

        if(!m_pathIterator.isDone())
        {
            float coords[6];

            m_segType = m_pathIterator.currentSegment(coords);
            switch(m_segType)
            {
                case Path::ESegMoveTo:
                    m_pointCoords.push_back(coords[0]);
                    m_pointCoords.push_back(coords[1]);
                    m_lastPoint.x = coords[0];
                    m_lastPoint.y = coords[1];
                    break;
                case Path::ESegLineTo:
                    m_pointCoords.push_back(coords[0]);
                    m_pointCoords.push_back(coords[1]);
                    m_lastPoint.x = coords[0];
                    m_lastPoint.y = coords[1];
                    break;
                case Path::ESegQuadTo:
                    m_pointCoords.push_back(m_lastPoint.x);
                    m_pointCoords.push_back(m_lastPoint.y);
                    m_pointCoords.push_back(coords[0]);
                    m_pointCoords.push_back(coords[1]);
                    m_pointCoords.push_back(coords[2]);
                    m_pointCoords.push_back(coords[3]);

                    for(unsigned i = 0; i < m_recursionLimit; i++)
                        flattenCurveQuadTo(m_pointCoords);

                    m_coordIndex = 2;
                    m_lastPoint.x = coords[2];
                    m_lastPoint.y = coords[3];
                    m_segType = Path::ESegLineTo;
                    break;
                case Path::ESegCubicTo:
                    m_pointCoords.push_back(m_lastPoint.x);
                    m_pointCoords.push_back(m_lastPoint.y);
                    m_pointCoords.push_back(coords[0]);
                    m_pointCoords.push_back(coords[1]);
                    m_pointCoords.push_back(coords[2]);
                    m_pointCoords.push_back(coords[3]);
                    m_pointCoords.push_back(coords[4]);
                    m_pointCoords.push_back(coords[5]);

                    for(unsigned i = 0; i < m_recursionLimit; i++)
                        flattenCurveCubicTo(m_pointCoords);

                    m_coordIndex = 2;
                    m_lastPoint.x = coords[4];
                    m_lastPoint.y = coords[5];
                    m_segType = Path::ESegLineTo;
                    break;
                case Path::ESegClose:
                    m_pointCoords.push_back(m_lastPoint.x);
                    m_pointCoords.push_back(m_lastPoint.y);
                    break;
            }
            m_pathIterator.next();
        }
    }
}

void FlattenPathIterator::flattenCurveQuadTo(std::vector<float>& coords) const
{
    unsigned count, i = 0;
    float p[6];

    while (i + 5 < coords.size())
    {
        count = i;
        p[0] = coords[count++];
        p[1] = coords[count++];
        p[2] = coords[count++];
        p[3] = coords[count++];
        p[4] = coords[count++];
        p[5] = coords[count++];

        p[0] = (p[0] + p[2]) * .5f;
        p[1] = (p[1] + p[3]) * .5f;
        p[4] = (p[2] + p[4]) * .5f;
        p[5] = (p[3] + p[5]) * .5f;
        p[2] = (p[0] + p[4]) * .5f;
        p[3] = (p[1] + p[5]) * .5f;

        count = i + 2;

        coords[count] = p[2];
        coords[count + 1] = p[3];

        coords.insert(coords.begin() + count++, p[0]);
        coords.insert(coords.begin() + count, p[1]);
        coords.insert(coords.begin() + (i + 6), p[5]);
        coords.insert(coords.begin() + (i + 7), p[4]);

        i += 8;
    }
}

void FlattenPathIterator::flattenCurveCubicTo(std::vector<float>& coords) const
{
    unsigned count, i = 0;
    float p[10];

    while (i + 7 < coords.size())
    {
        count = i;
        p[0] = coords[count++];
        p[1] = coords[count++];
        p[2] = coords[count++];
        p[3] = coords[count++];
        p[4] = coords[count++];
        p[5] = coords[count++];
        p[6] = coords[count++];
        p[7] = coords[count++];

        p[0] = (p[0] + p[2]) * .5f;
        p[1] = (p[1] + p[3]) * .5f;
        p[6] = (p[4] + p[6]) * .5f;
        p[7] = (p[5] + p[7]) * .5f;
        p[8] = (p[2] + p[4]) * .5f;
        p[9] = (p[3] + p[5]) * .5f;
        p[2] = (p[0] + p[8]) * .5f;
        p[3] = (p[1] + p[9]) * .5f;
        p[4] = (p[6] + p[8]) * .5f;
        p[5] = (p[7] + p[9]) * .5f;
        p[8] = (p[2] + p[4]) * .5f;
        p[9] = (p[3] + p[5]) * .5f;

        count = i + 2;

        coords[count++] = p[0];
        coords[count++] = p[1];
        coords[count++] = p[2];
        coords[count++] = p[3];

        coords.insert(coords.begin() + count, p[7]);
        coords.insert(coords.begin() + count, p[6]);
        coords.insert(coords.begin() + count, p[5]);
        coords.insert(coords.begin() + count, p[4]);
        coords.insert(coords.begin() + count, p[9]);
        coords.insert(coords.begin() + count, p[8]);

        i += 12;
    }
}

} //namespace lunasvg
