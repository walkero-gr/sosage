/*
  [include/Sosage/Component/Menu.h]
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

#ifndef SOSAGE_COMPONENT_MENU_H
#define SOSAGE_COMPONENT_MENU_H

#include <Sosage/Component/Base.h>
#include <Sosage/Component/Image.h>
#include <Sosage/Component/Position.h>
#include <Sosage/Utils/enum.h>
#include <Sosage/Utils/graph.h>

namespace Sosage::Component
{

class Menu : public Base
{

  struct Vertex
  {
    Split_direction direction;
    std::vector<Image_handle> image;
    Position_handle position;
    std::size_t current = 0;
  };

  struct Edge {};

  using Tree = Graph<Vertex, Edge, true>;
  using GVertex = Tree::Vertex;
  using GEdge = Tree::Edge;

  class Vertex_wrapper
  {
  private:
    Tree& tree;
    GVertex vertex;
  public:
    Vertex_wrapper (Tree& tree, GVertex vertex);
    Split_direction direction() const;
    bool has_image();
    Image_handle image() const;
    Position_handle position() const;
    void init (Image_handle image, Position_handle position);
    void add (Image_handle image);
    std::string change_setting (const std::string& setting, int diff);
    Vertex_wrapper operator[] (const std::size_t idx) const;
    void split (Split_direction direction, std::size_t nb_children);
    std::size_t nb_children() const;
    void hide();
    void apply (const std::function<void(Image_handle)>& func);
    void update_setting (const std::string& setting, const std::string& value);
  };

  Tree m_tree;
  GVertex m_root;

public:

  using Node = Vertex_wrapper;

  Menu (const std::string& entity, const std::string& component);
  Node operator[] (const std::size_t idx);
  void split (Split_direction direction, std::size_t nb_children);
  std::size_t nb_children() const;
  void hide();
  void apply (const std::function<void(Image_handle)>& func);
  void update_setting (const std::string& setting, const std::string& value);
  std::string increment (const std::string& setting);
  std::string decrement (const std::string& setting);
  Node root() const;

  STR_NAME("Menu");
};

using Menu_handle = std::shared_ptr<Menu>;

} // namespace Sosage::Component

#endif // SOSAGE_COMPONENT_MENU_H
