/*
  [src/Sosage/Component/Base.cpp]
  Virtual basis for all components.

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

#include <Sosage/Component/Base.h>
#include <Sosage/Utils/demangle.h>
#include <Sosage/Utils/profiling.h>

namespace Sosage::Component
{

Base::Base (const std::string& entity, const std::string& component)
  : m_id (entity, component), m_altered(false)
{ }

Base::~Base() { }

bool Base::is_system() const
{
  return isupper(entity()[0]);
}

void Base::mark_as_altered()
{
  m_altered = true;
}

void Base::mark_as_unaltered()
{
  m_altered = false;
}

bool Base::was_altered() const
{
  return m_altered;
}

const Id& Base::id() const
{
  return m_id;
}

const std::string& Base::entity() const
{
  return m_id.first;
}

// Special handling of entity for characters
std::string Base::character_entity() const
{
  for (const std::string& postfix : { "_body", "_head", "_mouth" })
  {
    std::size_t pos = entity().find(postfix);
    if (pos != std::string::npos)
      return std::string (entity().begin(), entity().begin() + pos);
  }
  return entity();
}

// Special handling of entity for binary actions
std::string Base::target_entity() const
{
  for (const std::string& prefix : { "_inventory_" })
  {
    std::size_t pos = entity().find(prefix);
    if (pos != std::string::npos)
      return std::string (entity().begin(), entity().begin() + pos);
  }
  std::size_t pos = entity().find_last_of('_');
  if (pos != std::string::npos)
    return std::string (entity().begin(), entity().begin() + pos);
  return std::string("");
}

const std::string& Base::component() const
{
  SOSAGE_COUNT(Component__component);
  return m_id.second;
}

std::string Base::str() const
{
  std::string out = str_name() + "(" + m_id.first + ":" + m_id.second + ")";
  std::string v = str_value();
  if (v != "")
    out += " = " + v;
  std::string sub = str_sub(0);
  if (sub != "")
    out += "\n" + sub;
  return out;
}

std::string component_str (Handle handle, const std::size_t& indent, const std::string& prefix)
{
  return std::string(indent*2, '-') + prefix + (handle ? handle->str() : "nullptr") + "\n"
      + (handle ? handle->str_sub(indent) : "");
}

} // namespace Sosage::Component
