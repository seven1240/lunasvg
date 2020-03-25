#ifndef PATHITERATOR_H
#define PATHITERATOR_H

#include <vector>

#include "path.h"

namespace lunasvg
{

class PathIterator
{
public:
   PathIterator(const Path& path);

   Path::SegType currentSegment(float* coords) const;
   bool isDone() const;
   void next();

private:
   mutable Point m_startPoint;
   const std::vector<Path::SegType>& m_pointSegs;
   const std::vector<float>& m_pointCoords;
   unsigned int m_segIndex;
   unsigned int m_coordIndex;
};

} //namespace lunasvg

#endif // PATHITERATOR_H
