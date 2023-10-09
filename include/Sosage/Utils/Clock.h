/*
  [include/Sosage/Utils/Clock.h]
  Clocks and timers.

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

#ifndef SOSAGE_UTILS_CLOCK_H
#define SOSAGE_UTILS_CLOCK_H

#include <Sosage/Core/Time.h>

namespace Sosage
{

using namespace Core;

class Clock
{
  Time::Unit m_latest;
  double m_mean;
  std::size_t m_nb;
  double m_fps;
  Time::Unit m_start;
  double m_time;

  Clock (const Clock&);

public:

  Clock();
  double get() const;
  void set (double time);
  void update(bool verbose = false);
  void sleep (double time);
  double fps() const;
  double time() const;

};

std::size_t frame_id (const double& time);
double frame_time (const double& time);

} // namespace Sosage

#endif // SOSAGE_UTILS_CLOCK_H
