#ifndef FLATTENPATHITERATOR_H
#define FLATTENPATHITERATOR_H

#include <vector>

#include "pathiterator.h"

namespace lunasvg
{

class FlattenPathIterator
{
public:
   FlattenPathIterator(const Path& path, unsigned int limit);

   Path::SegType currentSegment(float* coords) const;
   bool isDone() const;
   void next();

private:
   void flattenCurveQuadTo(std::vector<float>& coords) const;
   void flattenCurveCubicTo(std::vector<float>& coords) const;

private:
   PathIterator m_pathIterator;
   std::vector<float> m_pointCoords;
   Path::SegType m_segType;
   unsigned int m_recursionLimit;
   unsigned int m_coordIndex;
   Point m_lastPoint;
};

} // namespace lunasvg

#endif // FLATTENPATHITERATOR_H
