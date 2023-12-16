/*
  [include/Sosage/Component/Base.h]
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

#ifndef SOSAGE_COMPONENT_BASE_H
#define SOSAGE_COMPONENT_BASE_H

#include <memory>
#include <string>
#include <iostream>

#define STR_NAME(x) virtual std::string str_name() const { return x; }
#define STR_VALUE(x) virtual std::string str_value() const { return x; }
#define STR_SUB(x) virtual std::string str_sub(const std::size_t& indent) const { x }

namespace Sosage::Component
{

struct Id
{
  std::string first;
  std::string second;
  std::size_t hash;

  Id (const std::string& first = "", const std::string& second = "")
    : first(first), second(second)
  {
    hash = std::hash<std::string>()(first) ^ std::hash<std::string>()(second);
  }

  bool operator== (const Id& other) const
  {
    return (first == other.first && second == other.second);
  }
};

class Base
{
  Id m_id;
  bool m_altered;

public:
  Base (const std::string& entity, const std::string& component);
  virtual ~Base();
  bool is_system() const;
  void mark_as_altered();
  void mark_as_unaltered();
  bool was_altered() const;
  const Id& id() const;
  const std::string& entity() const;
  std::string character_entity() const;
  std::string target_entity() const;
  const std::string& component() const;
  std::string str() const;

  STR_NAME("Base");
  STR_VALUE("");
  virtual std::string str_sub(const std::size_t&) const { return ""; }
};

using Handle = std::shared_ptr<Base>;

std::string component_str(Handle handle, const std::size_t& indent, const std::string& prefix = "");

template <typename T>
class Value : public Base
{
public:
  Value(const std::string& entity, const std::string& component)
    : Base(entity, component) { }
  virtual T value() const = 0;
};

template <typename T>
using Value_handle = std::shared_ptr<Value<T> >;

template <typename T, typename ... Args>
std::shared_ptr<T> make_handle (Args ... args)
{
  return std::make_shared<T>(args...);
}

} // namespace Sosage::Component

#endif // SOSAGE_COMPONENT_BASE_H
