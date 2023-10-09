/*
  [src/Sosage/Component/Conditional.cpp]
  Access different components depending on a condition.

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

#include <Sosage/Component/Conditional.h>
#include <Sosage/Utils/conversions.h>
#include <Sosage/Utils/error.h>

namespace Sosage::Component
{

Conditional_base::Conditional_base (const std::string& entity, const std::string& component)
  : Base(entity, component)
{ }

Conditional::Conditional (const std::string& entity, const std::string& component,
                          Condition_handle condition,
                          Handle if_true,
                          Handle if_false)
  : Conditional_base(entity, component)
  , m_condition (condition)
  , m_if_true (if_true)
  , m_if_false (if_false)
{ }

Conditional::~Conditional()
{
  m_condition = Condition_handle();
  m_if_true = Handle();
  m_if_false = Handle();
}

Handle Conditional::get() const
{
  return (m_condition->value() ? m_if_true : m_if_false);
}

Functional_conditional::Functional_conditional
  (const std::string& entity, const std::string& component,
   const Function& function, const std::string& arg)
  : Conditional_base(entity, component)
  , m_function (function), m_arg (arg)
{ }

void Functional_conditional::add (Handle h)
{
  m_handles.emplace_back(h);
}

Handle Functional_conditional::get() const
{
  return m_handles[m_function(m_arg)];
}

Random_conditional::Random_conditional (const std::string& entity, const std::string& component)
  : Conditional_base(entity, component)
{ }

Random_conditional::~Random_conditional()
{
  m_handles.clear();
}

void Random_conditional::add (Handle h)
{
  m_handles.emplace_back(h);
}

Handle Random_conditional::get() const
{
  return random_choice(m_handles);
}


} // namespace Sosage::Component
