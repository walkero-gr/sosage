/*
  [include/Sosage/Config/config.h]
  Constant shared configuration values (world size, FPS, etc.).

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

#ifndef SOSAGE_CONFIG_CONFIG_H
#define SOSAGE_CONFIG_CONFIG_H

#include <Sosage/Utils/helpers.h>

#include <memory>
#include <limits>

namespace Sosage::Config
{

constexpr int world_width = 1920;
constexpr int world_height = 1080;

constexpr int inventory_height = 150;
constexpr int inventory_active_zone = 50;

constexpr int object_reach_x = 250;
constexpr int object_reach_y = 100;
constexpr int object_reach_hysteresis = 20;

constexpr double minimum_reaction_time = 0.25;

constexpr double camera_speed = 1.0;

constexpr int animation_fps = 12;

constexpr_auto possible_actions = { "look", "move", "take", "inventory", "use", "combine", "goto" };

constexpr_auto save_ids = { "auto", "1", "2", "3", "4", "5" };

constexpr double default_sound_fade_time = 0.2;

extern double interface_scale;

enum Depth
{
  interface_depth = 1000000,
  inventory_depth,
  label_depth,
  action_button_depth,
  dialog_depth,
  overlay_depth,
  menu_front_depth,
  menu_button_depth,
  menu_text_depth,
  cursor_depth,
  notification_depth,
  loading_depth
};

enum Dialog_speed
{
  SLOW = 18,
  MEDIUM_SPEED = 12,
  FAST = 9
};

enum Interface_scale
{
  TINY = 4,
  SMALL = 6,
  LARGE = 9,
  HUGE_ = 12
  /* Old dialog sizes =
  SMALL = 9,
  MEDIUM = 12,
  LARGE = 18,
  */
};

} // namespace Sosage::Config

#endif // SOSAGE_CONFIG_CONFIG_H
