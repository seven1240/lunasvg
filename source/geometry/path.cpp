#include "path.h"
#include "pathiterator.h"
#include "affinetransform.h"

#include <iostream>

namespace lunasvg
{

#define BEZIER_ARC_FACTOR 0.5522847498f

void Path::moveTo(float x, float y, bool rel)
{
   if(rel)
   {
      Point p = currentPoint();
      x += p.x;
      y += p.y;
   }

   m_pointSegs.push_back(ESegMoveTo);
   m_pointCoords.push_back(x);
   m_pointCoords.push_back(y);

   m_startPoint = Point(x, y);
}

void Path::lineTo(float x, float y, bool rel)
{
   if(rel)
   {
      Point p = currentPoint();
      x += p.x;
      y += p.y;
   }

   m_pointSegs.push_back(ESegLineTo);
   m_pointCoords.push_back(x);
   m_pointCoords.push_back(y);
}

void Path::quadTo(float x1, float y1, float x2, float y2, bool rel)
{
   if(rel)
   {
      Point p = currentPoint();
      x1 += p.x;
      y1 += p.y;
      x2 += p.x;
      y2 += p.y;
   }

   m_pointSegs.push_back(ESegQuadTo);
   m_pointCoords.push_back(x1);
   m_pointCoords.push_back(y1);
   m_pointCoords.push_back(x2);
   m_pointCoords.push_back(y2);
}

void Path::cubicTo(float x1, float y1, float x2, float y2, float x3, float y3, bool rel)
{
   if(rel)
   {
      Point p = currentPoint();
      x1 += p.x;
      y1 += p.y;
      x2 += p.x;
      y2 += p.y;
      x3 += p.x;
      y3 += p.y;
   }

   m_pointSegs.push_back(ESegCubicTo);
   m_pointCoords.push_back(x1);
   m_pointCoords.push_back(y1);
   m_pointCoords.push_back(x2);
   m_pointCoords.push_back(y2);
   m_pointCoords.push_back(x3);
   m_pointCoords.push_back(y3);
}

void Path::smoothQuadTo(float x2, float y2, bool rel)
{
   if(rel)
   {
      Point p = currentPoint();
      x2 += p.x;
      y2 += p.y;
   }

   Point p1;
   std::size_t count = m_pointSegs.size();
   if(count > 0 && m_pointSegs[count - 1] == ESegQuadTo)
      p1 = controlPoint();
   else
      p1 = currentPoint();

   quadTo(p1.x, p1.y, x2, y2, false);
}

void Path::smoothCubicTo(float x2, float y2, float x3, float y3, bool rel)
{
   if(rel)
   {
      Point p = currentPoint();
      x2 += p.x;
      y2 += p.y;
      x3 += p.x;
      y3 += p.y;
   }

   Point p1;
   std::size_t count = m_pointSegs.size();
   if(count > 0 && m_pointSegs[count - 1] == ESegCubicTo)
      p1 = controlPoint();
   else
      p1 = currentPoint();

   cubicTo(p1.x, p1.y, x2, y2, x3, y3, false);
}

void Path::horizontalTo(float x, bool rel)
{
   Point p = currentPoint();

   if(rel)
      x += p.x;

   m_pointSegs.push_back(ESegLineTo);
   m_pointCoords.push_back(x);
   m_pointCoords.push_back(p.y);
}

void Path::verticalTo(float y, bool rel)
{
   Point p = currentPoint();

   if(rel)
      y += p.y;

   m_pointSegs.push_back(ESegLineTo);
   m_pointCoords.push_back(p.x);
   m_pointCoords.push_back(y);
}

void Path::closePath()
{
   std::size_t count = m_pointSegs.size();
   if(count > 0 && m_pointSegs[count - 1] != ESegClose)
       m_pointSegs.push_back(ESegClose);
}

Point Path::currentPoint() const
{
   if(m_pointCoords.size() < 2)
      return Point();

   if(m_pointSegs[m_pointSegs.size() - 1] == ESegClose)
      return m_startPoint;

   std::size_t count = m_pointCoords.size();
   float x = m_pointCoords[count - 2];
   float y = m_pointCoords[count - 1];

   return Point(x, y);
}

Point Path::controlPoint() const
{
   if(m_pointCoords.size() < 4)
      return Point();

   std::size_t count = m_pointCoords.size();
   float x0 = m_pointCoords[count - 4];
   float y0 = m_pointCoords[count - 3];
   float x1 = m_pointCoords[count - 2];
   float y1 = m_pointCoords[count - 1];

   return Point(x1 + x1 - x0, y1 + y1 - y0);
}

void Path::addPath(const Path& path)
{
   PathIterator it(path);
   float c[6];
   while(!it.isDone())
   {
      switch(it.currentSegment(c))
      {
         case ESegMoveTo:
            moveTo(c[0], c[1]);
            break;
         case ESegLineTo:
            lineTo(c[0], c[1]);
            break;
         case ESegQuadTo:
            quadTo(c[0], c[1], c[2], c[3]);
            break;
         case ESegCubicTo:
            cubicTo(c[0], c[1], c[2], c[3], c[4], c[5]);
            break;
         case ESegClose:
            closePath();
            break;
      }
      it.next();
   }
}

void Path::addRect(float x, float y, float w, float h, float rx, float ry)
{
    rx = std::min(rx, w/ 2);
    ry = std::min(ry, h/ 2);

    float right = x + w;
    float bottom = y + h;

    if(rx==0.f && ry==0.f)
    {
        moveTo(x, y);
        lineTo(right, y);
        lineTo(right, bottom);
        lineTo(x, bottom);
        lineTo(x, y);
    }
    else
    {
        float cpx = rx * BEZIER_ARC_FACTOR;
        float cpy = ry * BEZIER_ARC_FACTOR;
        moveTo(x, y+ry);
        cubicTo(x, y+ry-cpy, x+rx-cpx, y, x+rx, y);
        lineTo(right-rx, y);
        cubicTo(right-rx+cpx, y, right, y+ry-cpy, right, y+ry);
        lineTo(right, bottom-ry);
        cubicTo(right, bottom-ry+cpy, right-rx+cpx, bottom, right-rx, bottom);
        lineTo(x+rx, bottom);
        cubicTo(x+rx-cpx, bottom, x, bottom-ry+cpy, x, bottom-ry);
        lineTo(x, y+ry);
    }

    closePath();
}

void Path::addRect(const Rect& rect, float rx, float ry)
{
    addRect(rect.x, rect.y, rect.width, rect.height, rx, ry);
}

void Path::addPoints(const std::vector<Point>& points)
{
    if(points.empty())
        return;

    moveTo(points[0].x, points[0].y);
    for(unsigned i = 1;i < points.size(); i++)
        lineTo(points[i].x, points[i].y);
}

void Path::addEllipse(const Rect& bbox)
{
    float cx = bbox.x + (bbox.width * 0.5f);
    float cy = bbox.y + (bbox.height * 0.5f);
    float offx = bbox.width * 0.257f;
    float offy = bbox.height * 0.257f;

    float px[12];
    px[0] = px[1] = px[11] = bbox.x;
    px[2] = px[10] = cx - offx;
    px[3] = px[9] = cx;
    px[4] = px[8] = cx + offx;
    px[5] = px[6] = px[7] = bbox.x + bbox.width;

    float py[12];
    py[2] = py[3] = py[4] = bbox.y;
    py[1] = py[5] = cy - offy;
    py[0] = py[6] = cy;
    py[7] = py[11] = cy + offy;
    py[8] = py[9] = py[10] = bbox.y + bbox.height;

    moveTo(px[0], py[0]);
    cubicTo(px[1], py[1], px[2], py[2], px[3], py[3]);
    cubicTo(px[4], py[4], px[5], py[5], px[6], py[6]);
    cubicTo(px[7], py[7], px[8], py[8], px[9], py[9]);
    cubicTo(px[10], py[10], px[11], py[11], px[0], py[0]);
}

void Path::addEllipse(const Point &center, float rx, float ry)
{
    addEllipse(Rect(center.x - rx, center.y - ry, rx + rx, ry + ry));
}

Rect Path::boundingBox() const
{
    float xMin = std::numeric_limits<float>::max();
    float yMin = std::numeric_limits<float>::max();
    float xMax = std::numeric_limits<float>::min();
    float yMax = std::numeric_limits<float>::min();

    for(std::size_t i=0;i<m_pointCoords.size();i+=2)
    {
        float x = m_pointCoords[i];
        float y = m_pointCoords[i+1];
        if(x < xMin) xMin = x;
        if(x > xMax) xMax = x;
        if(y < yMin) yMin = y;
        if(y > yMax) yMax = y;
    }

    return Rect(xMin, yMin, xMax - xMin, yMax - yMin);
}

void Path::transform(const AffineTransform& matrix)
{
    for(std::size_t i=0;i<m_pointCoords.size();i+=2)
        matrix.map(m_pointCoords[i], m_pointCoords[i+1], m_pointCoords[i], m_pointCoords[i+1]);
}

void Path::reset()
{
   m_startPoint = Point();
   m_pointSegs.clear();
   m_pointCoords.clear();
}

} //namespace lunasvg
