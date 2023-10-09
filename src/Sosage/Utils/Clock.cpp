/*
  [src/Sosage/Utils/Clock.cpp]
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

#include <Sosage/Config/config.h>
#include <Sosage/Utils/Clock.h>
#include <Sosage/Utils/error.h>
#include <Sosage/Utils/profiling.h>

#include <cmath>

namespace Sosage
{

Clock::Clock (const Clock&)
{ }

Clock::Clock()
  : m_mean(0), m_nb(0), m_time(0)
{
  m_start = Time::now();
  m_latest = m_start;
}

double Clock::get() const
{
  return Time::now();
}

void Clock::set (double time)
{
  // After a speedup, resync time with nexw origin
  m_start = m_latest - std::lround(time * 1000.);
}

void Clock::update(bool verbose)
{
  Time::Unit now = Time::now();
  if (verbose)
  {
    m_mean += (now - m_latest);
    ++ m_nb;
    if (m_nb == 60)
    {
      m_fps = 1000. / (m_mean / m_nb);
      m_mean = 0.;
      m_nb = 0;
    }
  }
  m_latest = now;
  m_time = (m_latest - m_start) / 1000.;
}

void Clock::sleep (double time)
{
  Time::wait (time * 1000.);
  m_time = (Time::now() - m_start) / 1000.;
}

double Clock::fps() const
{
  return m_fps;
}

double Clock::time() const
{
  return m_time;
}

std::size_t frame_id (const double& time)
{
  return std::size_t(time * Config::animation_fps);
}

double frame_time (const double& time)
{
  return frame_id(time) / double(Config::animation_fps);
}

} // namespace Sosage
