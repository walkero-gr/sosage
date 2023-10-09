/*
  [include/Sosage/Component/Image.h]
  Basis for all graphic items.

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

#ifndef SOSAGE_COMPONENT_IMAGE_H
#define SOSAGE_COMPONENT_IMAGE_H

#include <Sosage/Component/Base.h>
#include <Sosage/Component/Font.h>
#include <Sosage/Core/Graphic.h>
#include <Sosage/Utils/enum.h>
#include <Sosage/Utils/geometry.h>

namespace Sosage
{

namespace Config
{
constexpr int world_depth = 3240;
} // namespace Config

namespace Component
{

class Image : public Base
{
private:
  Core::Graphic::Image m_core;
  Point m_origin;
  int m_z;
  bool m_on;
  Collision_type m_collision;
  double m_scaling;
  unsigned char m_highlight_alpha;
  unsigned char m_alpha;

public:

  Image (const std::string& entity, const std::string& component,
         int w, int h, int r = 0, int g = 0, int b = 0, int a = 255);
  Image (const std::string& entity, const std::string& component, const std::string& file_name, int z = 0,
         const Collision_type& collision = UNCLICKABLE, bool with_highlight = false);
  Image (const std::string& entity, const std::string& component,
         Font_handle font, const std::string& color_str,
         const std::string& text, bool outlined = false);
  Image (const std::string& entity, const std::string& component, std::shared_ptr<Image> copy);
  void compose_with (const std::shared_ptr<Image>& other);
  void set_relative_origin (double ratio_x, double ratio_y);
  const Core::Graphic::Image& core() const;
  const Point& origin() const;
  Point& origin();
  const bool& on() const;
  bool& on();
  const Collision_type& collision() const;
  void set_collision(const Collision_type& collision);
  virtual int xmin() const;
  virtual int xmax() const;
  virtual int ymin() const;
  virtual int ymax() const;
  int width() const;
  int height() const;
  const int& z() const;
  int& z();
  double scale() const;
  void rescale (double z);
  void set_scale (double scale);
  void set_alpha (unsigned char alpha);
  unsigned char alpha() const;
  void set_highlight (unsigned char alpha);
  unsigned char highlight() const;
  bool is_target_inside (int x, int y) const;

  STR_NAME("Image");
  STR_VALUE(std::string(m_on ? "ON" : "OFF") + ", z=" + to_string(m_z)
            + ", scale=" + to_string(m_scaling)
            + ", alpha=" + to_string(m_alpha)
            + ", highlight=" + to_string(m_highlight_alpha));
};

using Image_handle = std::shared_ptr<Image>;

} // namespace Component

} // namespace Sosage

#endif // SOSAGE_COMPONENT_IMAGE_H
