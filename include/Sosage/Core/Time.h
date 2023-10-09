/*
  [include/Sosage/Core/Time.h]
  Abstraction file for third party library handling time.

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

#ifndef SOSAGE_CORE_TIME_H
#define SOSAGE_CORE_TIME_H

#include <Sosage/Third_party/SDL_time.h>

#include <chrono>
#include <thread>

namespace Sosage::Core
{

#ifdef SOSAGE_SDL_TIME
using Time = Third_party::SDL_time;
#else
class Time
{
public:

  using Unit = std::chrono::steady_clock::time_point::rep;
  using Duration = std::chrono::steady_clock::duration::rep;

  static Unit now()
  {
    return std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::steady_clock::now().time_since_epoch()).count();
  }

  static void wait (const Duration& d)
  {
    std::this_thread::sleep_for
        (std::chrono::steady_clock::duration
         (std::chrono::milliseconds { d }));
  }
};
#endif
} // namespace Sosage::Core

#endif
