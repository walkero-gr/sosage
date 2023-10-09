/*
  [src/Sosage/Component/Position.cpp]
  2D coordinates.

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

#include <Sosage/Component/cast.h>
#include <Sosage/Component/Position.h>

namespace Sosage::Component
{

Position::Position (const std::string& entity, const std::string& component)
  : Base(entity, component)
{ }

Absolute_position::Absolute_position (const std::string& entity, const std::string& component,
                                      const Point& point, bool is_interface)
  : Position(entity, component), m_pos (point), m_is_interface (is_interface)
{
  if (entity == "couloir" && component == "position")
  {
    check (point.X() == 187 && point.Y() == 840,
           "couloir moved to " + str());
  }
}

Point Absolute_position::value () const
{
  return m_pos;
}

void Absolute_position::set (const Point& p)
{
  m_pos = p;
  mark_as_altered();
}

bool Absolute_position::is_interface() const
{
  return m_is_interface;
}

bool& Absolute_position::is_interface()
{
  return m_is_interface;
}

Relative_position::Relative_position (const std::string& entity, const std::string& component,
                                      Position_handle ref,
                                      const Sosage::Vector& diff, double factor)
  : Position(entity, component), m_ref(ref), m_diff(diff), m_factor(factor)
{ }
  
Absolute_position_handle Relative_position::absolute_reference()
{
  if (auto r = cast<Absolute_position>(m_ref))
    return r;
  return cast<Relative_position>(m_ref)->absolute_reference();
}

Point Relative_position::value() const
{
  return m_factor * m_ref->value() + m_diff;
}

void Relative_position::set (const Point& p)
{
  m_diff = Sosage::Vector(m_factor * m_ref->value(), p);
  mark_as_altered();
}

void Relative_position::set (const Sosage::Vector& v)
{
  m_diff = v;
}

bool Relative_position::is_interface() const
{
  return m_ref->is_interface();
}

Double_relative_position::Double_relative_position (const std::string& entity,
                                                    const std::string& component,
                                                    Position_handle ref,
                                                    Position_handle diff,
                                                    double factor)
  : Position(entity, component), m_ref(ref), m_diff(diff), m_factor(factor)
{ }

Absolute_position_handle Double_relative_position::absolute_reference()
{
  if (auto r = cast<Absolute_position>(m_ref))
    return r;
  return cast<Relative_position>(m_ref)->absolute_reference();
}

Point Double_relative_position::value() const
{
  return m_factor * m_ref->value() + m_diff->value();
}

void Double_relative_position::set (const Point& p)
{
  m_diff->set(Sosage::Vector(m_factor * m_ref->value(), p));
  mark_as_altered();
}

void Double_relative_position::set (const Sosage::Vector& v)
{
  m_diff->set(v);
}

bool Double_relative_position::is_interface() const
{
  return m_ref->is_interface();
}

Functional_position::Functional_position (const std::string& entity, const std::string& component,
                                          const Function& function,
                                          const std::string& arg, bool is_interface)
  : Position(entity, component), m_function(function), m_arg(arg), m_is_interface(is_interface),
    m_tmp_point(Point::invalid())
{ }

Point Functional_position::value() const
{
  if (!m_tmp_point.is_invalid())
    return m_tmp_point;
  return m_function(m_arg);
}

const Functional_position::Function& Functional_position::function() const
{
  return m_function;
}

void Functional_position::set (const Point& p)
{
  m_tmp_point = p;
}

void Functional_position::set (const Function& function)
{
  m_function = function;
}

bool Functional_position::is_interface() const
{
  return m_is_interface;
}

} // namespace Sosage::Component
