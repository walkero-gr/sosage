/*
  [include/Sosage/System/Interface.h]
  Game logic, actions, dialog generation, etc.

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

#ifndef SOSAGE_SYSTEM_LOGIC_H
#define SOSAGE_SYSTEM_LOGIC_H

#include <Sosage/Component/Action.h>
#include <Sosage/Component/Debug.h>
#include <Sosage/Component/Image.h>
#include <Sosage/Component/Position.h>
#include <Sosage/Component/Simple.h>
#include <Sosage/System/Base.h>

#include <queue>

namespace Sosage
{

namespace Config
{
constexpr int follow_factor = 1500;
constexpr double char_spoken_time = 0.05;
constexpr double min_reading_time = 1.5;
constexpr double button_click_duration = 0.1;
constexpr int goto_active_zone_x = 75;
constexpr int goto_active_zone_y = 30;
} // Config

namespace System
{

class Logic : public Base
{
private:

  double m_current_time;
  using Function = std::function<bool(const std::vector<std::string>&)>;
  std::unordered_map<std::string, Function> m_dispatcher;
  Component::Action_handle m_current_action;
  std::queue<Component::Action_handle> m_todo;

public:

  Logic (Content& content);

  virtual void run();

private:

  void clear_notifications(bool hardclear = false);
  void notify_end_achievements();
  void reset_all_actions();
  void cancel_action();
  void console_action (Component::String_handle str);
  void update_scheduled(Component::Action_handle a, bool skip_dialog);
  void update_character_path();
  void update_code();
  void update_follower();
  void update_action (Component::Action_handle triggered_action);
  bool skip_cutscene();
  void run_actions(bool skip);

  bool compute_path_from_target (Component::Position_handle target,
                                 std::string id = "");
  bool compute_path_from_direction (const Vector& direction);
  void follow (const std::string& follower);
  void update_debug_info (Component::Debug_handle debug_info);

  bool apply_next_step (Component::Action_handle action);
  void skip_step (const Component::Action::Step& step);

  bool subfunction_fade (bool fadein, double duration);
  bool subfunction_trigger_dialog (const std::vector<std::string>& args);
  void create_dialog (const std::string& character,
                      const std::string& text,
                      std::vector<Component::Image_handle>& dialog);
  std::string push_notification (const std::string& text, double duration);

  // Implemented in Logic__functions.cpp
  bool function_add (const std::vector<std::string>& args);
  bool function_camera (const std::vector<std::string>& args);
  bool function_control (const std::vector<std::string>& args);
  bool function_cutscene (const std::vector<std::string>& args);
  bool function_emit (const std::vector<std::string>& args);
  bool function_exit (const std::vector<std::string>& args);
  bool function_fadein (const std::vector<std::string>& args);
  bool function_fadeout (const std::vector<std::string>& args);
  bool function_goto (const std::vector<std::string>& args);
  bool function_hide (const std::vector<std::string>& args);
  bool function_load (const std::vector<std::string>& args);
  bool function_lock (const std::vector<std::string>& args);
  bool function_look (const std::vector<std::string>& args);
  bool function_loop (const std::vector<std::string>& args);
  bool function_message (const std::vector<std::string>& args);
  bool function_move (const std::vector<std::string>& args);
  bool function_move60fps (const std::vector<std::string>& args);
  bool function_notify (const std::vector<std::string>& args);
  bool function_pause (const std::vector<std::string>& args);
  bool function_play (const std::vector<std::string>& args);
  bool function_randomize (const std::vector<std::string>& args);
  bool function_receive (const std::vector<std::string>& args);
  bool function_remove (const std::vector<std::string>& args);
  bool function_rescale (const std::vector<std::string>& args);
  bool function_rescale60fps (const std::vector<std::string>& args);
  bool function_save (const std::vector<std::string>& args);
  bool function_set (const std::vector<std::string>& args);
  bool function_set12fps (const std::vector<std::string>& args);
  bool function_shake (const std::vector<std::string>& args);
  bool function_show (const std::vector<std::string>& args);
  bool function_stop (const std::vector<std::string>& args);
  bool function_talk (const std::vector<std::string>& args);
  bool function_timer (const std::vector<std::string>& args);
  bool function_trigger (const std::vector<std::string>& args);
  bool function_unlock (const std::vector<std::string>& args);
  bool function_wait (const std::vector<std::string>& args);
  bool function_zoom (const std::vector<std::string>& args);

};

} // namespace System

} // namespace Sosage

#endif // SOSAGE_SYSTEM_LOGIC_H
