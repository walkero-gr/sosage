/*
  [include/Sosage/Component/Path.h]
  List of coordinates that the character should follow.

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

#ifndef SOSAGE_COMPONENT_PATH_H
#define SOSAGE_COMPONENT_PATH_H

#include <Sosage/Component/Base.h>
#include <Sosage/Utils/geometry.h>

#include <vector>

namespace Sosage::Component
{

class Path : public Base
{
  std::vector<Point> m_steps;
  std::size_t m_current;

public:

  Path (const std::string& entity, const std::string& component, const Point& coord);
  Path (const std::string& entity, const std::string& component, std::vector<Point>& steps);
  std::size_t size() const;
  const Point& operator[] (const std::size_t& idx) const;
  Point& operator[] (const std::size_t& idx);
  const std::size_t& current() const;
  std::size_t& current();

  STR_NAME("Path");
};

using Path_handle = std::shared_ptr<Path>;

} // namespace Sosage::Component

#endif // SOSAGE_COMPONENT_PATH_H
