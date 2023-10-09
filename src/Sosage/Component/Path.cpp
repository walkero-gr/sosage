/*
  [src/Sosage/Component/Path.cpp]
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

#include <Sosage/Component/Path.h>

namespace Sosage::Component
{

Path::Path (const std::string& entity, const std::string& component, const Point& point)
  : Base(entity, component), m_steps (1, point), m_current(0)
{ }

Path::Path (const std::string& entity, const std::string& component, std::vector<Point>& steps)
  : Base(entity, component), m_current(0)
{
  m_steps.swap(steps);
}

std::size_t Path::size() const
{
  return m_steps.size();
}

const Point& Path::operator[] (const std::size_t& idx) const
{
  dbg_check(idx < m_steps.size(), "Accessing index " + std::to_string(idx) + " in path of size " + std::to_string(m_steps.size()));
  return m_steps[idx];
}

Point& Path::operator[] (const std::size_t& idx)
{
  dbg_check(idx < m_steps.size(), "Accessing index " + std::to_string(idx) + " in path of size " + std::to_string(m_steps.size()));
  return m_steps[idx];
}

const std::size_t& Path::current() const
{
  return m_current;
}

std::size_t& Path::current()
{
  return m_current;
}

} // namespace Sosage::Component
