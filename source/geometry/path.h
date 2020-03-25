#ifndef PATH_H
#define PATH_H

#include <vector>
#include <string>

#include "point.h"
#include "rect.h"

namespace lunasvg
{

enum WindRule
{
    EWindRuleNonZero,
    EWindRuleEvenOdd
};

class AffineTransform;

class Path
{
public:
   enum SegType
   {
      ESegMoveTo,
      ESegLineTo,
      ESegQuadTo,
      ESegCubicTo,
      ESegClose
   };

   enum PathOp
   {
      EUnion,
      EIntersect,
      EXnor,
      EDifference
   };

   const std::vector<SegType>& getPointSegs() const;
   const std::vector<float>& getPointCoords() const;

   bool isEmpty() const;
   void reset();

   void transform(const AffineTransform& matrix);
   void combine(const Path& path, PathOp op);

   Point currentPoint() const;
   Point controlPoint() const;

   void moveTo(float x1, float y1, bool rel = false);
   void lineTo(float x1, float y1, bool rel = false);
   void quadTo(float x1, float y1, float x2, float y2, bool rel = false);
   void cubicTo(float x1, float y1, float x2, float y2, float x3, float y3, bool rel = false);
   void smoothQuadTo(float x2, float y2, bool rel = false);
   void smoothCubicTo(float x2, float y2, float x3, float y3, bool rel = false);
   void horizontalTo(float x, bool rel = false);
   void verticalTo(float y, bool rel = false);
   void closePath();

   void moveTo(const Point& p1, bool rel = false);
   void lineTo(const Point& p1, bool rel = false);
   void quadTo(const Point& p1, const Point& p2, bool rel = false);
   void cubicTo(const Point& p1, const Point& p2, const Point& p3, bool rel = false);
   void smoothQuadTo(const Point& p2, bool rel = false);
   void smoothCubicTo(const Point& p2, const Point& p3, bool rel = false);

   void addPath(const Path& path);
   void addRect(float x, float y, float w, float h, float rx = 0, float ry = 0);
   void addRect(const Rect& rect, float rx = 0, float ry = 0);
   void addPoints(const std::vector<Point>& points);
   void addEllipse(const Point& center, float rx, float ry);
   void addEllipse(const Rect& bbox);

   Rect boundingBox() const;

private:
   Point m_startPoint;
   std::vector<SegType> m_pointSegs;
   std::vector<float> m_pointCoords;
};

inline const std::vector<Path::SegType>& Path::getPointSegs() const
{
   return m_pointSegs;
}

inline const std::vector<float>& Path::getPointCoords() const
{
   return m_pointCoords;
}

inline bool Path::isEmpty() const
{
   return m_pointCoords.empty();
}

inline void Path::moveTo(const Point& p1, bool rel)
{
   moveTo(p1.x, p1.y, rel);
}

inline void Path::lineTo(const Point& p1, bool rel)
{
   lineTo(p1.x, p1.y, rel);
}

inline void Path::quadTo(const Point& p1, const Point& p2, bool rel)
{
   quadTo(p1.x, p1.y, p2.x, p2.y, rel);
}

inline void Path::cubicTo(const Point& p1, const Point& p2, const Point& p3, bool rel)
{
   cubicTo(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, rel);
}

inline void Path::smoothQuadTo(const Point& p2, bool rel)
{
   smoothQuadTo(p2.x, p2.y, rel);
}

inline void Path::smoothCubicTo(const Point& p2, const Point& p3, bool rel)
{
   smoothCubicTo(p2.x, p2.y, p3.x, p3.y, rel);
}

} // namespace lunasvg

#endif //PATH_H
