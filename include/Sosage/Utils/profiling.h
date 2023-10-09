/*
  [include/Sosage/Utils/profiling.h]
  Tools for profiling code.

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

#ifndef SOSAGE_UTILS_PROFILING_H
#define SOSAGE_UTILS_PROFILING_H

#include <Sosage/Config/options.h>
#include <Sosage/Core/Time.h>


#ifdef SOSAGE_PROFILE
#  define SOSAGE_TIMER_START(x) static Timer x(#x); x.start()
#  define SOSAGE_TIMER_RESTART(x) x.start()
#  define SOSAGE_TIMER_STOP(x) x.stop()
#  define SOSAGE_COUNT(x) static Counter x(#x); x.increment()
#else
#  define SOSAGE_TIMER_START(x)
#  define SOSAGE_TIMER_RESTART(x)
#  define SOSAGE_TIMER_STOP(x)
#  define SOSAGE_COUNT(x)
#endif

#ifdef SOSAGE_PROFILE_FINELY
#include <fstream>
#include <vector>
#endif

namespace Sosage
{
using namespace Core;

class Timer
{
  std::string m_id;
  Time::Unit m_start;

#ifdef SOSAGE_PROFILE_FINELY
  std::vector<Time::Duration> m_duration;
#else
  Time::Duration m_duration;
  unsigned int m_nb = 0;
#endif

  bool m_master;

public:

  Timer (const std::string& id, bool master = true);
  ~Timer();
  void start();
  void stop();
  void display();
#ifndef SOSAGE_PROFILE_FINELY
  double mean_duration() const;
#endif
  std::string to_string (double d) const;
};

class Counter
{
  std::string m_id;
  unsigned int m_nb;

public:

  Counter (const std::string& id);
  ~Counter ();
  void increment();
};

}

#endif // SOSAGE_UTILS_PROFILING_H


