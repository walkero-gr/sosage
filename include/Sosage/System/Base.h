/*
  [include/Sosage/System/Base.h]
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

#ifndef SOSAGE_SYSTEM_BASE_H
#define SOSAGE_SYSTEM_BASE_H

#include <Sosage/Component/Handle_set.h>
#include <Sosage/Component/Status.h>
#include <Sosage/Content.h>

#include <memory>
#include <string>

namespace Sosage::System
{

class Base
{
protected:

  Content& m_content;

#ifdef SOSAGE_PROFILE
  Time::Unit m_start;
#endif

public:

  Base (Content& content);
  virtual ~Base();
  virtual void init();
  virtual void run() = 0;

  Component::Handle_set components (const std::string& s);
  template <typename T>
  std::shared_ptr<T> get (const std::string& entity, const std::string& component)
  { return m_content.get<T>(entity, component); }
  template <typename T>
  std::shared_ptr<T> get (const Fast_access_component& fac) { return m_content.get<T>(fac); }
  template <typename T>
  std::shared_ptr<T> request (const std::string& entity, const std::string& component)
  { return m_content.request<T>(entity, component); }
  template <typename T>
  typename T::const_reference value (const Fast_access_component& fac) { return m_content.value<T>(fac); }
  template <typename T>
  typename T::const_reference value (const std::string& entity, const std::string& component)
  { return m_content.value<T>(entity, component); }
  template <typename T>
  typename T::value_type value (const std::string& entity, const std::string& component,
                                const typename T::value_type& default_value)
  { return m_content.value<T>(entity, component, default_value); }
  template <typename T, typename ... Args>
  std::shared_ptr<T> set (Args&& ... args) { return m_content.set<T>(std::forward<Args>(args)...); }
  template <typename T>
  void set (const std::shared_ptr<T>& t) { return m_content.set<T>(t); }
  template <typename T, typename ... Args>
  std::shared_ptr<T> get_or_set (const std::string& entity, const std::string& component, Args&& ... args)
  { return m_content.get_or_set<T>(entity, component, std::forward<Args>(args)...); }
  template <typename T, typename ... Args>
  std::shared_ptr<T> set_fac (const Fast_access_component& fac, Args&& ... args)
  { return m_content.set_fac<T>(fac, std::forward<Args>(args)...); }
  bool remove (const std::string& entity, const std::string& component, bool optional = false);
  bool remove (Component::Handle handle, bool optional = false);
  void emit (const std::string& entity, const std::string& component);
  bool receive (const std::string& entity, const std::string& component);
  bool signal (const std::string& entity, const std::string& component);
  Component::Status_handle status();
  const std::string& locale (const std::string& line);
  const std::string& locale_get (const std::string& entity, const std::string& component);
};

using Handle = std::shared_ptr<Base>;

template <typename T, typename ... Args>
std::shared_ptr<T> make_handle (Args& ... args)
{
  return std::make_shared<T>(args...);
}

} // namespace Sosage::Component

#endif // SOSAGE_COMPONENT_BASE_H
