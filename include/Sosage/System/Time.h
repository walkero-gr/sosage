/*
  [include/Sosage/System/Time.h]
  Time handling (framerate, sleep, etc.).

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

#ifndef SOSAGE_SYSTEM_TIME_H
#define SOSAGE_SYSTEM_TIME_H

#include <Sosage/Content.h>
#include <Sosage/System/Base.h>
#include <Sosage/Utils/Clock.h>

namespace Sosage
{

namespace Config
{
constexpr double speedup_factor = 2.;
}

namespace System
{

class Time : public Base
{
  Clock m_clock;
  bool m_loading;

public:

  Time (Content& content);

  virtual void run();
  void signal_loading() { m_loading = true; }

private:

  void limit_fps();
};

} // namespace System
} // namespace Sosage


#endif // SOSAGE_SYSTEM_TIME_H
