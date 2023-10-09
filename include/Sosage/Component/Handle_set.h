/*
  [include/Sosage/Component/Handle_set.h]
  Set of component handles and component map.

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

#ifndef SOSAGE_COMPONENT_HANDLE_SET_H
#define SOSAGE_COMPONENT_HANDLE_SET_H

#include <Sosage/Component/Base.h>

#include <unordered_map>
#include <vector>

namespace Sosage::Component
{

struct Id_hash
{
  std::size_t operator() (const Id& id) const
  {
    return std::hash<std::string>()(id.first) ^ std::hash<std::string>()(id.second);
  }
};

using Handle_map = std::unordered_map<Id, Handle, Id_hash>;
using Component_map = std::vector<Handle_map>;

class Handle_set
{
  Handle_map& m_map;

public:

  class iterator
  {
    using Base = Handle_map::iterator;
    Base m_base;

  public:

    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = Handle;
    using pointer           = value_type*;
    using reference         = value_type&;

    iterator (Base base = Base()) : m_base(base) { }

    reference operator*() const { return m_base->second; }
    pointer operator->() { return &m_base->second; }
    iterator& operator++() { m_base++; return *this; }
    iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
    friend bool operator== (const iterator& a, const iterator& b) { return a.m_base == b.m_base; };
    friend bool operator!= (const iterator& a, const iterator& b) { return a.m_base != b.m_base; };
  };

  using const_iterator = iterator;

  Handle_set (Handle_map& map) : m_map (map) { }
  void clear() { m_map.clear(); }
  iterator begin() { return iterator(m_map.begin()); }
  iterator end() { return iterator(m_map.end()); }
  const_iterator begin() const { return iterator(m_map.begin()); }
  const_iterator end() const { return iterator(m_map.end()); }
  const_iterator find (const Id& id) const { return m_map.find(id); }
};

} // namespace Sosage::Component

#endif // SOSAGE_COMPONENT_HANDLE_SET_H
