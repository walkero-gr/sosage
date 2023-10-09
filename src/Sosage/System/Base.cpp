/*
  [src/Sosage/System/Base.cpp]
  Virtual basis for all systems.

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

#include <Sosage/Component/Locale.h>
#include <Sosage/System/Base.h>

namespace Sosage::System
{

Base::Base (Content& content)
  : m_content (content)
{ }

Base::~Base() { }

void Base::init() { }

Component::Handle_set Base::components (const std::string& s)
{
  return m_content.components(s);
}

bool Base::remove (const std::string& entity, const std::string& component, bool optional)
{
  return m_content.remove(entity, component, optional);
}

bool Base::remove (Component::Handle handle, bool optional)
{
  return m_content.remove(handle, optional);
}

void Base::emit (const std::string& entity, const std::string& component)
{
  m_content.emit (entity, component);
}

bool Base::receive (const std::string& entity, const std::string& component)
{
  return m_content.receive(entity, component);
}

bool Base::signal (const std::string& entity, const std::string& component)
{
  return m_content.signal(entity, component);
}

Component::Status_handle Base::status()
{
  return get<Component::Status>(GAME__STATUS);
}

const std::string& Base::locale (const std::string& line)
{
  if (auto l = request<Component::Locale>("Game", "locale"))
    return l->get(line);
  // else
  return line;
}

const std::string& Base::locale_get (const std::string& entity, const std::string& component)
{
  return locale (value<Component::String>(entity, component));
}

} // namespace Sosage::System
