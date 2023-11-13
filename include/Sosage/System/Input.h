/*
  [include/Sosage/System/Input.h]
  Reads and interprets user input (keyboard, mouse, touchscreen).

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

#ifndef SOSAGE_SYSTEM_INPUT_H
#define SOSAGE_SYSTEM_INPUT_H

#include <Sosage/Content.h>
#include <Sosage/Core/Input.h>
#include <Sosage/System/Base.h>

#include <random>

namespace Sosage
{

namespace Config
{
constexpr double stick_max = 32767.5;
} // namespace Config

namespace System
{

class Input : public Base
{
  Core::Input m_core;
  std::vector<Event> m_current_events;
  std::vector<bool> m_keys_on;
  double m_x;
  double m_y;

#ifdef SOSAGE_DEV
  bool m_fake_touchscreen;
#endif

  // For demo mode
#if defined(SOSAGE_DEV) || defined(SOSAGE_DEMO)
  bool m_demo_mode;
  std::mt19937 m_randgen;
#endif

public:

  Input (Content& content);

  virtual void run ();

private:

  void update_mode();
  void update_keys_on (const Event& ev);
  void handle_exit_pause_speed(const Event& ev);
  void handle_debug_tools(const Event& ev);
  void update_window(const Event& ev);
  void update_active_gamepad(const Event& ev);
  void update_mouse(const Event& ev);
  void update_touchscreen(const Event& ev);
  bool update_gamepad(const Event& ev);
  void finalize_gamepad (bool arrow_released);
  void rumble_gamepad (double intensity, double duration);

  typename std::vector<bool>::reference key_on(const Event_value& value);
#if defined(SOSAGE_DEV) || defined(SOSAGE_DEMO)
  void run_demo_mode();
  Point cursor_target (const std::string& id);
#endif
};

} // namespace System

} // namespace Sosage

#endif // SOSAGE_SYSTEM_INPUT_H
