/*
  [src/Sosage/Component/Menu.cpp]
  Menu and information boxes, windows, etc.

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

#include <Sosage/Component/Menu.h>

namespace Sosage::Component
{

Menu::Vertex_wrapper::Vertex_wrapper (Tree& tree, GVertex vertex)
  : tree(tree), vertex(vertex) {}

Split_direction Menu::Vertex_wrapper::direction() const
{
  return tree[vertex].direction;
}

bool Menu::Vertex_wrapper::has_image()
{
  return !tree[vertex].image.empty();
}

Image_handle Menu::Vertex_wrapper::image() const
{
  return tree[vertex].image[tree[vertex].current];
}

Position_handle Menu::Vertex_wrapper::position() const
{
  return tree[vertex].position;
}

void Menu::Vertex_wrapper::init (Image_handle image, Position_handle position)
{
  tree[vertex].image.emplace_back(image);
  tree[vertex].position = position;
}

void Menu::Vertex_wrapper::add (Image_handle image)
{
  tree[vertex].image.emplace_back(image);
}

std::string Menu::Vertex_wrapper::change_setting (const std::string& setting, int diff)
{
  if (nb_children() == 0)
  {
    if (tree[vertex].image.size() > 1 &&
        position()->entity() == setting)
    {
      image()->on() = false;
      if (diff == 1)
      {
        ++ tree[vertex].current;
        if (tree[vertex].current == tree[vertex].image.size())
          tree[vertex].current = 0;
      }
      else
      {
        if (tree[vertex].current == 0)
          tree[vertex].current = tree[vertex].image.size();
        -- tree[vertex].current;
      }

      image()->on() = true;
      std::string entity = image()->entity();
      return std::string (entity.begin() + setting.size() + 1, entity.end());
    }
  }
  else
    for (std::size_t i = 0; i < nb_children(); ++ i)
    {
      std::string out = (*this)[i].change_setting (setting, diff);
      if (out != "")
        return out;
    }
  return "";
}

Menu::Vertex_wrapper Menu::Vertex_wrapper::operator[] (const std::size_t idx) const
{
  return Vertex_wrapper (tree, tree.incident_vertex(vertex, idx));
}

void Menu::Vertex_wrapper::split (Split_direction direction, std::size_t nb_children)
{
  check(tree[vertex].direction == NO_SPLIT, "Trying to split already splitted vertex");
  tree[vertex].direction = direction;
  for (std::size_t i = 0; i < nb_children; ++ i)
  {
    GVertex v = tree.add_vertex();
    tree.add_edge(vertex, v);
  }
}

std::size_t Menu::Vertex_wrapper::nb_children() const
{
  return tree.incident_edges(vertex).size();
}

void Menu::Vertex_wrapper::hide()
{
  if (has_image())
    image()->on() = false;
  for (std::size_t i = 0; i < nb_children(); ++ i)
    (*this)[i].hide();
}

void Menu::Vertex_wrapper::apply (const std::function<void(Image_handle)>& func)
{
  if (nb_children() < 2)
    func(image());
  for (std::size_t i = 0; i < nb_children(); ++ i)
    (*this)[i].apply(func);
}

void Menu::Vertex_wrapper::update_setting (const std::string& setting, const std::string& value)
{
  if (nb_children() == 0)
  {
    if (tree[vertex].image.size() > 1 &&
        position()->entity() == setting)
    {
      for (std::size_t i = 0; i < tree[vertex].image.size(); ++ i)
      {
        std::string entity = tree[vertex].image[i]->entity();
        std::string v (entity.begin() + setting.size() + 1, entity.end());
        if (v == value)
        {
          tree[vertex].current = i;
          return;
        }
      }
      check (false, "Value " + value + " not found in setting " + setting);
    }
  }
  else
    for (std::size_t i = 0; i < nb_children(); ++ i)
      (*this)[i].update_setting (setting, value);
}

Menu::Menu (const std::string& entity, const std::string& component)
  : Base(entity, component)
{
  m_root = m_tree.add_vertex();
}

Menu::Node Menu::operator[] (const std::size_t idx)
{
  return root()[idx];
}

void Menu::split (Split_direction direction, std::size_t nb_children)
{
  root().split(direction, nb_children);
}

std::size_t Menu::nb_children() const
{
  return root().nb_children();
}

void Menu::hide()
{
  root().hide();
}

void Menu::apply (const std::function<void(Image_handle)>& func)
{
  root().apply(func);
}

void Menu::update_setting (const std::string& setting, const std::string& value)
{
  root().update_setting (setting, value);
}

std::string Menu::increment (const std::string& setting)
{
  return root().change_setting (setting, 1);
}

std::string Menu::decrement (const std::string& setting)
{
  return root().change_setting (setting, -1);
}

Menu::Node Menu::root() const
{
  return Node(const_cast<Tree&>(m_tree), m_root);
}

} // namespace Sosage::Component
