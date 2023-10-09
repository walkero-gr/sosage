/*
  [include/Sosage/Utils/error.h]
  Debug checks, errors, warnings, assertions, etc.

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

#ifndef SOSAGE_UTILS_ERROR_H
#define SOSAGE_UTILS_ERROR_H

#include <Sosage/Config/options.h>
#include <Sosage/Config/platform.h>

#include <utility>
#include <iostream>
#include <sstream>

#define SOSAGE_UPDATE_DBG_LOCATION(x) \
  static const char* location = x;    \
  dbg_location = const_cast<char*>(location);

namespace Sosage
{

extern char* dbg_location;

#if !defined(SOSAGE_DEBUG)
#define debug if(false) std::cerr
#elif defined(SOSAGE_ANDROID) || defined(SOSAGE_WINDOWS) || defined(SOSAGE_EMSCRIPTEN)
#define SOSAGE_DEBUG_BUFFER

class Debug_buffer : public std::stringbuf
{
public:
  virtual int sync();
};

extern Debug_buffer debug_buffer;
extern std::ostream debug;
#else
#define debug std::cerr
#endif

#define check(test, msg) if (!(test)) check_impl (__FILE__, __LINE__, msg)

#ifdef SOSAGE_DEBUG
#define dbg_check(test, msg) if (!(test)) check_impl (__FILE__, __LINE__, msg)
#else
#define dbg_check(test, msg) (static_cast<void>(0))
#endif

void check_impl (const char* file, int line, const std::string& str);

} // namespace Sosage

#endif // SOSAGE_UTILS_ERROR_H
