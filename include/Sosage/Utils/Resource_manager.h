/*
  [include/Sosage/Utils/Resource_manager.h]
  Avoid loading the same file twice.

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

#ifndef SOSAGE_UTILS_RESOURCE_MANAGER_H
#define SOSAGE_UTILS_RESOURCE_MANAGER_H

#include <Sosage/Component/Condition.h>
#include <Sosage/Content.h>
#include <Sosage/Utils/Clock.h>

#include <functional>

namespace Sosage
{

template <typename Resource>
class Resource_manager
{
public:

  using Resource_handle = std::shared_ptr<Resource>;
  using Data = std::unordered_map<std::string, Resource_handle>;
  using iterator = typename Data::iterator;

private:

  Data m_data;
  std::function<void(Resource*)> m_deleter;

public:

  Resource_manager(const std::function<void(Resource*)>& deleter
                   = [](Resource* r) { delete r; })
    : m_deleter(deleter)
  { }

  void clear()
  {
    Data new_data;
    for (const auto& d : m_data)
      if (d.second.use_count() > 1)
        new_data.insert (d);
      else
      {
//        debug << "Remove " << typeid(Resource*).name() << " " << d.first << std::endl;
      }
    m_data.swap(new_data);
  }

  std::size_t size() const { return m_data.size(); }

  Resource_handle get (const std::string& key)
  {
    iterator out = m_data.find(key);
    check (out != m_data.end(), "Can't find resource " + key);
    return out->second;
  }

  Resource_handle make_single_base (const std::function<Resource*()>& f)
  {
    return Resource_handle(f(), m_deleter);
  }

  template <typename F, typename ... Args>
  Resource_handle make_single (F&& f, Args&& ... args)
  {
    std::function<Resource*()> func = std::bind (f, args...);
    return make_single_base (func);
  }

  template <typename F, typename ... Args>
  Resource_handle make_mapped (const std::string& key, F&& f, Args&& ... args)
  {
    typename Data::iterator iter;
    bool inserted;
    std::tie (iter, inserted) = m_data.insert (std::make_pair (key, Resource_handle()));
    if (inserted)
      iter->second = make_single(std::forward<F>(f), std::forward<Args>(args)...);

    return iter->second;
  }
};

} // namespace Sosage

#endif // SOSAGE_UTILS_RESOURCE_MANAGER_H
