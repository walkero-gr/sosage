/*
  [src/Sosage/Component/Status.cpp]
  The game current status (and pending ones).

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

#include <Sosage/Component/Status.h>

namespace Sosage::Component
{

Status::Status (const std::string& entity, const std::string& component)
  : Base(entity, component)
{
  reset();
}

void Status::reset()
{
  while (!m_value.empty())
    m_value.pop();
  m_value.push(IDLE);
  m_value.push(LOCKED); // start game locked
}

void Status::push (const Sosage::Status& v)
{
  m_value.push(v);
}

void Status::pop ()
{
  m_value.pop();
}

Sosage::Status Status::value() const
{
 return m_value.top();
}

Sosage::Status Status::next_value() const
{
  if (m_value.size() == 1)
    return value();
  Sosage::Status saved = m_value.top();
  m_value.pop();
  Sosage::Status out = m_value.top();
  m_value.push(saved);
  return out;
}

bool Status::is (const Sosage::Status& s)
{
  return (value() == s);
}

bool Status::is (const Sosage::Status& s1, const Sosage::Status& s2)
{
  return (value() == s1) || (value() == s2);
}

bool Status::is (const Sosage::Status& s1, const Sosage::Status& s2, const Sosage::Status& s3)
{
  return (value() == s1) || (value() == s2) || (value() == s3);
}

bool Status::was (const Sosage::Status& s)
{
  return (next_value() == s);
}

} // namespace Sosage::Component
