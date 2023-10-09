/*
  [include/Sosage/System/Test_input.h]
  Automatic input generation for testing purposes.

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

#ifndef SOSAGE_SYSTEM_TEST_INPUT_H
#define SOSAGE_SYSTEM_TEST_INPUT_H

#ifdef SOSAGE_DEV

#include <Sosage/Core/Input.h>
#include <Sosage/System/Base.h>
#include <Sosage/Utils/geometry.h>

#include <random>

namespace Sosage::System
{

class Test_input : public Base
{
  Core::Input m_core;
  bool m_random_mode;
  std::function<void(void)> m_mode;
  std::mt19937 m_randgen;

public:

  Test_input (Content& content);
  void set_random_mode();

  virtual void run();

private:

  void run_mouse();
  void run_mouse_chaos();
  void run_touchscreen();
  void run_gamepad();
  void run_gamepad_chaos();

  Point cursor_target (const std::string& id);

  std::function<void(void)> new_mode();
  bool ready (const std::string& key, double time);
};

} // namespace Sosage::System

#endif // SOSAGE_DEV

#endif // SOSAGE_SYSTEM_TEST_INPUT_H
