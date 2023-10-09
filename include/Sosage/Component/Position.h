/*
  [include/Sosage/Component/Position.h]
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

#ifndef SOSAGE_COMPONENT_POSITION_H
#define SOSAGE_COMPONENT_POSITION_H

#include <Sosage/Component/Base.h>
#include <Sosage/Utils/geometry.h>
#include <Sosage/Utils/conversions.h>

#include <functional>

namespace Sosage::Component
{

class Position : public Base
{
public:

  using const_reference = Point;
  using value_type = Point;

  Position (const std::string& entity, const std::string& component);

  virtual void set (const Point& p) = 0;
  virtual Point value() const = 0;
  virtual bool is_interface() const = 0;
};

using Position_handle = std::shared_ptr<Position>;

class Absolute_position : public Position
{
  Point m_pos;
  bool m_is_interface;

public:

  Absolute_position (const std::string& entity, const std::string& component,
                     const Point& coord, bool is_interface = true);
  virtual Point value () const;
  virtual void set (const Point& p);
  bool is_interface() const;
  bool& is_interface();

  STR_NAME("Absolute_position");
  STR_VALUE("Point(" + to_string(m_pos.x()) + ";" + to_string(m_pos.y()) + ")");
};

using Absolute_position_handle = std::shared_ptr<Absolute_position>;


class Relative_position : public Position
{
  Position_handle m_ref;
  Sosage::Vector m_diff;
  double m_factor;

public:

  Relative_position (const std::string& entity, const std::string& component, Position_handle ref,
                     const Sosage::Vector& diff = Sosage::Vector(0,0),
                     double factor = 1.);
  Absolute_position_handle absolute_reference();
  virtual Point value() const;
  virtual void set (const Point& p);
  void set (const Sosage::Vector& v);
  bool is_interface() const;

  STR_NAME("Relative_position");
  STR_VALUE("Vector(" + to_string(m_diff.x()) + ";" + to_string(m_diff.y()) + ")");
  STR_SUB(return component_str(m_ref, indent+1, "Reference -> "););
};

using Relative_position_handle = std::shared_ptr<Relative_position>;

class Double_relative_position : public Position
{
  Position_handle m_ref;
  Position_handle m_diff;
  double m_factor;

public:

  Double_relative_position (const std::string& entity, const std::string& component,
                            Position_handle ref, Position_handle diff,
                            double factor = 1.);
  Absolute_position_handle absolute_reference();
  virtual Point value() const;
  virtual void set (const Point& p);
  void set (const Sosage::Vector& v);
  bool is_interface() const;

  STR_NAME("Double_relative_position");
  STR_SUB(return component_str(m_ref, indent+1, "Ref = ")
          + component_str(m_diff, indent+1, "Diff = "););
};

using Relative_position_handle = std::shared_ptr<Relative_position>;

class Functional_position : public Position
{
  using Function = std::function<Point(const std::string&)>;
  Function m_function;
  std::string m_arg;
  bool m_is_interface;
  mutable Point m_tmp_point;

public:

  Functional_position (const std::string& entity, const std::string& component,
                       const Function& function,
                       const std::string& arg,
                       bool is_interface = false);

  virtual Point value() const;
  const Function& function() const;
  virtual void set (const Point& p);
  void set (const Function& function);
  bool is_interface() const;

  STR_NAME("Functional_position");
  STR_VALUE("arg(" + m_arg + ")");
};

using Functional_position_handle = std::shared_ptr<Functional_position>;

} // namespace Sosage::Component

#endif // SOSAGE_COMPONENT_POSITION_H
