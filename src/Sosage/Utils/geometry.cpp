/*
  [src/Sosage/Utils/geometry.cpp]
  Basic geometric objects and functions (points, distances, etc.).

  ===========================================================================

  This file is part of SOSAGE, released under the MIT License.
  Copyright (c) 2019-present Simon Giraudot

  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.

  ===========================================================================

  Author(s): Simon Giraudot <sosage@ptilouk.net>
*/

#include <Sosage/Utils/geometry.h>

namespace Sosage
{

int round (const double& x)
{
  return int(std::lround(x));
}

double distance (double xa, double ya, double xb, double yb)
{
  return std::sqrt (square(xa - xb) + square(ya - yb));
}

double angle (double x, double y)
{
  return std::atan2 (y, x);
}

Point::Point (const double& x, const double& y)
  : m_x (x), m_y (y)
{ }

Point::Point (const std::pair<double, double>& coord)
  : Point (coord.first, coord.second)
{ }

double Point::x() const
{
  return m_x;
}

double Point::y() const
{
  return m_y;
}

int Point::X() const
{
  return round(m_x);
}

int Point::Y() const
{
  return round(m_y);
}

Box Point::box() const
{
  return {m_x, m_y, m_x, m_y};
}

bool Point::is_invalid() const
{
  return std::isnan(m_x);
}

Point Point::invalid()
{
  return Point (std::numeric_limits<double>::quiet_NaN(),
                std::numeric_limits<double>::quiet_NaN());
}

Point Point::right()
{
  return Point (1e10, 0);
}

Point Point::left()
{
  return Point (-1e10, 0);
}

Point Point::center (const Box& box)
{
  return Point ((box.xmin + box.xmax) / 2, (box.ymin + box.ymax) / 2);
}

Vector::Vector (double x, double y)
  : Point (x, y)
{ }

Vector::Vector (const Point& a, const Point& b)
  : Point (b.x() - a.x(), b.y() - a.y())
{ }

Vector::Vector (const Point& p)
  : Point (p.x(), p.y())
{ }

double Vector::length() const
{
  return std::sqrt(square (x()) + square (y()));
}

void Vector::normalize()
{
  double l = length();
  *this = Vector(x() / l, y() / l);
}

Vector Vector::perpendicular() const
{
  return Vector(y(), -x());
}


Line::Line (const Point& a, const Point& b)
  : m_reference (a),
    m_direction (a, b)
{
  m_direction.normalize();
}

Point Line::projection (const Point& p) const
{
  Vector ref (m_reference, p);
  double length = ref * m_direction;
  return m_reference + length * m_direction;
}

const Vector& Line::direction() const
{
  return m_direction;
}

Segment::Segment (const Point& source, const Point& target)
  : m_source (source), m_target (target)
{ }

Vector Segment::to_vector() const
{
  return Vector(m_source, m_target);
}

Line Segment::to_line() const
{
  return Line(m_source, m_target);
}

Box Segment::box() const
{
  return m_source.box() + m_target.box();
}

double Segment::length() const
{
  return distance (m_source.x(), m_source.y(), m_target.x(), m_target.y());
}

double Segment::projected_coordinate (const Point& p) const
{
  Line l = to_line();
  Point proj = l.projection(p);
  return distance (m_source, proj);
}

std::pair<Point, bool> Segment::projection (const Point& p) const
{
  Line l = to_line();
  Point proj = l.projection(p);
  Vector vproj (m_source, proj);
  return std::make_pair (proj,
                         (vproj * l.direction() > 0
                          && distance (m_source, proj) < length()));
}

} // namespace Sosage
