/*
  [include/Sosage/System/Animation.h]
  Generate animations and handle frame-by-frame image selection.

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

#ifndef SOSAGE_SYSTEM_ANIMATION_H
#define SOSAGE_SYSTEM_ANIMATION_H

#include <Sosage/Component/Animation.h>
#include <Sosage/Component/Path.h>
#include <Sosage/Config/config.h>
#include <Sosage/Content.h>
#include <Sosage/System/Base.h>

namespace Sosage
{

namespace Config
{
constexpr int camera_limit_left = world_width / 4;
constexpr int camera_limit_right = (3 * world_width) / 4;
constexpr int character_speed = 34;
} // namespace Config

namespace System
{

class Animation : public Base
{
private:

  std::size_t m_frame_id;
  std::vector<Component::Handle> m_to_remove;

  std::unordered_set<std::string> m_just_started;

public:

  Animation (Content& content);

  virtual void run();

  bool run_loading();

  void place_and_scale_character (const std::string& id);
  void generate_random_idle_animation (const std::string& id, bool looking_right);
  void generate_random_idle_head_animation (const std::string& id, bool looking_right);
  void generate_random_idle_body_animation  (const std::string& id, bool looking_right);

private:

  void run_gui_frame();
  void run_animation_frame();

  void handle_character_lookat (bool in_new_room);
  void handle_animation_stops();
  bool handle_moves();
  void handle_animation_starts();
  void handle_state_changes();
  void handle_characters_headmove (Component::Animation_handle anim);
  void trigger_step_sounds (Component::Animation_handle anim);

  bool compute_movement_from_path (Component::Path_handle path);
  void set_move_animation (const std::string& id, const Vector& direction);

  void generate_random_mouth_animation (const std::string& id);
  void generate_animation (const std::string& id, const std::string& anim);

  bool fade (double begin_time, double end_time, bool fadein);

  void update_camera_target();
};

} // namespace System

} // namespace Sosage

#endif // SOSAGE_SYSTEM_GRAPHIC_H
