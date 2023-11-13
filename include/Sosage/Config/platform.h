/*
  [include/Sosage/Config/platform.h]
  Internal defines for platform handling.

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

#ifndef SOSAGE_CONFIG_PLATFORM_H
#define SOSAGE_CONFIG_PLATFORM_H

namespace Sosage
{

namespace Config
{

#if __has_include("Sosage/Third_party/Port.h")
#define SOSAGE_PORT
constexpr bool android = false;
constexpr bool mac = false;
constexpr bool windows = false;
constexpr bool gnunux = false;
constexpr bool emscripten = false;
constexpr bool port = true;

#elif defined(__ANDROID__) && !defined(SOSAGE_NATIVE_ANDROID)
#define SOSAGE_ANDROID
constexpr bool android = true;
constexpr bool mac = false;
constexpr bool windows = false;
constexpr bool gnunux = false;
constexpr bool emscripten = false;
constexpr bool port = false;

#elif defined(__APPLE__)
#define SOSAGE_MAC
constexpr bool android = false;
constexpr bool mac = true;
constexpr bool windows = false;
constexpr bool gnunux = false;
constexpr bool emscripten = false;
constexpr bool port = false;

#elif defined(_WIN32)
#define SOSAGE_WINDOWS
constexpr bool android = false;
constexpr bool mac = false;
constexpr bool windows = true;
constexpr bool gnunux = false;
constexpr bool emscripten = false;
constexpr bool port = false;

#elif defined(__linux__)
#define SOSAGE_GNUNUX
constexpr bool android = false;
constexpr bool mac = false;
constexpr bool windows = false;
constexpr bool gnunux = true;
constexpr bool emscripten = false;
constexpr bool port = false;

#elif defined(__EMSCRIPTEN__)
#define SOSAGE_EMSCRIPTEN
constexpr bool android = false;
constexpr bool mac = false;
constexpr bool windows = false;
constexpr bool gnunux = false;
constexpr bool emscripten = true;
constexpr bool port = false;

#endif

}

}

#endif // SOSAGE_CONFIG_PLATFORM_H
