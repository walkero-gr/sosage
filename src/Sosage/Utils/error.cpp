/*
  [src/Sosage/Utils/error.cpp]
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

#include <Sosage/Utils/error.h>

#ifdef SOSAGE_ANDROID
#include <android/log.h>
#endif

#if defined(SOSAGE_EMSCRIPTEN) || defined(SOSAGE_WINDOWS)
#include <SDL.h>
#endif

namespace Sosage
{

char* dbg_location = nullptr;

#ifdef SOSAGE_DEBUG_BUFFER
int Debug_buffer::sync()
{
#if defined(SOSAGE_ANDROID)
  __android_log_print (ANDROID_LOG_DEBUG, "Sosage", "%s", this->str().c_str());
#else
  SDL_Log("%s", this->str().c_str());
#endif
  this->str("");
  return 0;
}
#endif

void check_impl (const char* file, int line, const std::string& str)
{
#if defined(SOSAGE_DEBUG) && !defined(SOSAGE_ANDROID)
  throw std::runtime_error(std::string(dbg_location) + ": " + str + " [" + file + ":" + std::to_string(line) + "]" );
#else
  debug << "Error in " << dbg_location << ": "<< str << " [" << file << ":" << line << "]" << std::endl;
  exit(EXIT_FAILURE);
#endif
}

} // namespace Sosage
