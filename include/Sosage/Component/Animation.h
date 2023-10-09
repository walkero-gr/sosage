/*
  [include/Sosage/Component/Animation.h]
  Specialization of Image for animated objects.

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

#ifndef SOSAGE_COMPONENT_ANIMATION_H
#define SOSAGE_COMPONENT_ANIMATION_H

#include <Sosage/Component/Image.h>

#include <vector>

namespace Sosage::Component
{

class Animation : public Image
{
public:

  struct Frame
  {
    int x;
    int y;
    int duration;
    int ellapsed = 0;
  };

private:
  
  const int m_width_subdiv;
  const int m_height_subdiv;
  std::vector<Frame> m_frames;
  std::size_t m_current;
  bool m_loop;
  bool m_playing;

public:

  Animation (const std::string& entity, const std::string& component,
             const std::string& file_name, int z,
             int width_subdiv, int height_subdiv, bool loop,
             const Collision_type& collision = BOX, bool with_highlight = false);
  int width_subdiv() const;
  int height_subdiv() const;
  const std::vector<Frame>& frames() const;
  std::vector<Frame>& frames();
  bool loop() const;
  bool animated() const;
  const bool& playing() const;
  bool& playing();
  int reset(bool all_frames = true, int duration = 1);
  virtual int xmin() const;
  virtual int xmax() const;
  virtual int ymin() const;
  virtual int ymax() const;
  std::size_t current() const;
  const Frame& current_frame() const;
  bool next_frame();
  bool is_last_frame() const;

  STR_NAME("Animation");
};

using Animation_handle = std::shared_ptr<Animation>;

} // namespace Sosage::Component

#endif // SOSAGE_COMPONENT_ANIMATION_H
