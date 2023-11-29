/*
  [include/Sosage/System/Control.h]
  Handles how users control the interface.

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

#ifndef SOSAGE_SYSTEM_CONTROL_H
#define SOSAGE_SYSTEM_CONTROL_H

#include <Sosage/Component/Image.h>
#include <Sosage/Component/Position.h>
#include <Sosage/System/Base.h>

namespace Sosage
{

namespace Config
{
constexpr double key_repeat_delay = 5.;
} // namespace Config

namespace System
{

class Control : public Base
{
  Status m_status;
  Input_mode m_mode;
  double m_latest_exit;
  bool m_stick_on;

  using Function = std::function<void(void)>;
  using Status_input_pair = std::pair<Status, Input_mode>;

  struct Hash_status_mode_pair
  {
    std::size_t operator() (const Status_input_pair& p) const;
  };

  std::unordered_map<Status_input_pair, Function, Hash_status_mode_pair> m_dispatcher;

public:

  Control (Content& content);

  virtual void run();

  virtual void init();

private:

  void update_exit();

  void begin_status (const Status& s);
  void end_status (const Status& s);

  void set_action (const std::string& id, const std::string& default_id);

  // Implemented in Control__mouse.cpp
  void idle_mouse();
  void idle_touchscreen();
  void idle_sub_click (const std::string& target);
  void action_choice_mouse();
  void action_choice_touchscreen();
  void action_choice_sub_click (const std::string& id);
  void object_choice_mouse();
  void object_choice_touchscreen();
  void object_choice_sub_click (const std::string& id);
  void inventory_mouse();
  void inventory_touchscreen();
  void inventory_sub_click (const std::string& target);
  void window_mouse();
  void window_touchscreen();
  void code_mouse();
  void code_touchscreen();
  void code_sub_click(bool collision);
  void dialog_mouse();
  void dialog_touchscreen();
  void dialog_sub_click ();
  void menu_mouse();
  void menu_touchscreen();
  bool collides (Component::Position_handle cursor, Component::Image_handle img);
  std::string first_collision (Component::Position_handle cursor,
                               const std::function<bool(Component::Image_handle)>& filter);

  // Implemented in Control__gamepad.cpp
  void idle_gamepad();
  void idle_sub_update_active_objects();
  void idle_sub_switch_active_object (bool right);
  void action_choice_gamepad();
  void action_choice_sub_triggered (const std::string& key);
  void object_choice_gamepad();
  void object_choice_sub_triggered (const std::string& key);
  void inventory_gamepad();
  void inventory_sub_switch_active_object (bool right);
  void inventory_sub_triggered (const std::string& key);
  void window_gamepad();
  void code_gamepad();
  void dialog_gamepad();
  void dialog_sub_switch_active_object (bool right);
  void menu_gamepad();
  void menu_sub_triggered (const Event_value& key);
  void menu_sub_switch_active_item (bool right);
  void flush_gamepad_keys();
  std::vector<std::string> detect_active_objects();
  Event_value stick_left_right();
  Event_value stick_up_down();
  Event_value stick_left_right_up_down();
  Vector stick_direction();
  bool is_ok (const std::string& key);
  bool is_notok (const std::string& key);
  void click_and_rumble();
};

} // namespace System

} // namespace Sosage

#endif // SOSAGE_SYSTEM_CONTROL_H
