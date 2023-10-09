/*
  [src/Sosage/Component/Inventory.cpp]
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

#include <Sosage/Component/Inventory.h>
#include <Sosage/Config/config.h>

#include <iostream>

namespace Sosage::Component
{

Inventory::Inventory (const std::string& entity, const std::string& component)
  : Base (entity, component), m_position(0)
{ }

void Inventory::clear()
{
  m_data.clear();
  m_position = 0;
}

std::vector<std::string>::const_iterator Inventory::begin() const
{
  return m_data.begin();
}

std::vector<std::string>::const_iterator Inventory::end() const
{
  return m_data.end();
}

void Inventory::add (const std::string& entity)
{
  m_data.push_back (entity);
}

void Inventory::remove (const std::string& entity)
{
  for (typename std::vector<std::string>::iterator
         it = m_data.begin(); it != m_data.end(); ++ it)
    if (*it == entity)
    {
      m_data.erase(it);
      break;
    }
}

bool Inventory::next()
{
  if (m_position + Config::displayed_inventory_size < m_data.size())
  {
    ++ m_position;
    return true;
  }
  return false;
}

bool Inventory::prev()
{
  if (m_position != 0)
  {
    -- m_position;
    return true;
  }
  return false;
}

std::size_t Inventory::size() const
{
  return m_data.size();
}

std::size_t Inventory::position() const
{
  return m_position;
}
  

std::string Inventory::get (std::size_t i) const
{
  return m_data[i];
}

const std::vector<std::string>& Inventory::data() const
{
  return m_data;
}

} // namespace Sosage::Component
