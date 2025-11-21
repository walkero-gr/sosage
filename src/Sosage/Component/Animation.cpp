/*
  [src/Sosage/Component/Animation.cpp]
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

#include <Sosage/Component/Animation.h>

namespace Sosage::Component
{

Animation::Animation (const std::string& entity, const std::string& component,
                      const std::string& file_name, int z,
                      int width_subdiv, int height_subdiv, bool loop,
                      const Collision_type& collision, bool with_highlight)
  : Image(entity, component, file_name, z, collision, with_highlight)
  , m_width_subdiv (width_subdiv)
  , m_height_subdiv (height_subdiv)
  , m_current(0)
  , m_loop(loop)
  , m_playing(true)
{
  reset();
}

int Animation::width_subdiv() const
{
  return m_width_subdiv;
}

int Animation::height_subdiv() const
{
  return m_height_subdiv;
}

const std::vector<Animation::Frame>& Animation::frames() const
{
  return m_frames;
}

std::vector<Animation::Frame>& Animation::frames()
{
  return m_frames;
}

bool Animation::loop() const
{
  return m_loop;
}

bool Animation::animated() const
{
  return m_frames.size() > 1;
}

const bool& Animation::playing() const
{
  return m_playing;
}

bool& Animation::playing()
{
  return m_playing;
}

int Animation::reset (bool all_frames, int duration)
{
  int out = 0;
  
  m_frames.clear();
  if (all_frames)
    for (int i = 0; i < m_height_subdiv; ++ i)
      for (int j = 0; j < m_width_subdiv; ++ j)
      {
        m_frames.push_back ({j,i,duration});
        out += 1;
      }
  else
  {
    m_frames.push_back ({0,0,duration});
    out = 1;
  }
  m_current = 0;

  return out;
}

int Animation::xmin() const
{
  int width = Core::Graphic::width(this->core());
  int w = width / m_width_subdiv;
  return w * m_frames[m_current].x;
}

int Animation::xmax() const
{
  int width = Core::Graphic::width(this->core());
  int w = width / m_width_subdiv;
  return w * (m_frames[m_current].x + 1);
}

int Animation::ymin() const
{
  int height = Core::Graphic::height(this->core());
  int h = height / m_height_subdiv;
  return h * m_frames[m_current].y;
}

int Animation::ymax() const
{
  int height = Core::Graphic::height(this->core());
  int h = height / m_height_subdiv;
  return h * (m_frames[m_current].y + 1);
}

std::size_t Animation::current() const
{
  return m_current;
}

const Animation::Frame& Animation::current_frame() const
{
 return m_frames[m_current];
}

bool Animation::next_frame()
{
  if (++ m_frames[m_current].ellapsed == m_frames[m_current].duration)
  {
    m_frames[m_current].ellapsed = 0;
    if (++ m_current >= m_frames.size())
    {
      m_current = 0;
      if (!m_loop)
        return false;
    }
  }
  return true;
}

bool Animation::is_last_frame() const
{
  if (m_frames.empty() || m_current >= m_frames.size())
    return false;
    
  // Check if we're on the last frame
  if (m_current != m_frames.size() - 1)
    return false;
  
  const auto& last_frame = m_frames[m_current];
  
  // We're on the last frame - check if we're about to complete
  // For duration=1, ellapsed should be 0 (will complete on next call)
  // For duration>1, ellapsed should be duration-1 (will complete on next call)
  return (last_frame.ellapsed == last_frame.duration - 1);
}

} // namespace Sosage::Component
