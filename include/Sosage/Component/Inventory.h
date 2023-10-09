/*
  [include/Sosage/Component/Inventory.h]
  List of items carried by the player.

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

#ifndef SOSAGE_COMPONENT_INVENTORY_H
#define SOSAGE_COMPONENT_INVENTORY_H

#include <Sosage/Component/Base.h>

#include <vector>

namespace Sosage
{

namespace Config
{
constexpr int displayed_inventory_size = 9;
} // namespace Config

namespace Component
{

class Inventory : public Base
{
  std::vector<std::string> m_data;
  std::size_t m_position;
  
public:

  Inventory (const std::string& entity, const std::string& component);
  void clear();
  std::vector<std::string>::const_iterator begin() const;
  std::vector<std::string>::const_iterator end() const;
  void add (const std::string& entity);
  void remove (const std::string& entity);
  bool next();
  bool prev();
  std::size_t size() const;
  std::size_t position() const;
  std::string get (std::size_t i) const;
  const std::vector<std::string>& data() const;

  STR_NAME("Inventory");
};

using Inventory_handle = std::shared_ptr<Inventory>;

} // namespace Component

} // namespace Sosage

#endif // SOSAGE_COMPONENT_INVENTORY_H
