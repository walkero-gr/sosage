/*
  [src/Sosage/Utils/datetime.cpp]
  Useful date/time tools

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

#include <Sosage/Config/platform.h>
#include <Sosage/Utils/datetime.h>

#include <ctime>

#ifdef SOSAGE_WINDOWS
#pragma warning(disable : 4996)
#endif

namespace Sosage
{

std::string time_to_string (double time)
{
  int seconds = int(time);

  auto tts = [](int val) -> std::string
  { return (val < 10 ? "0" : "") + std::to_string(val); };

  return tts(seconds / 3600) + ":"
      + tts((seconds / 60) % 60);
}

std::string date_to_string (int date)
{
  std::time_t time = date;
  std::tm* tm = std::localtime(&time);

  char timeString[std::size("yyyy-mm-dd, hh:mm")];
  std::strftime(std::data(timeString), std::size(timeString), "%F, %R", tm);
  return std::string(timeString);
}


} // namespace Sosage
