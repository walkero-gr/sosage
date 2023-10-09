/*
  [include/Sosage/Config/options.h]
  Compile-time options passed by CMake.

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

#ifndef SOSAGE_CONFIG_OPTIONS_H
#define SOSAGE_CONFIG_OPTIONS_H

#if !defined(NDEBUG) || defined(SOSAGE_CFG_DISPLAY_DEBUG_INFO)
#define SOSAGE_DEBUG
#endif

#ifdef SOSAGE_CFG_PROFILE
#define SOSAGE_PROFILE
#define SOSAGE_PROFILE_FINELY
#define SOSAGE_PROFILE_TO_FILE
#endif

#ifdef SOSAGE_CFG_GUILESS
#define SOSAGE_GUILESS
#endif

#ifdef SOSAGE_CFG_USE_SDL_TIME
#define SOSAGE_SDL_TIME
#endif

#ifndef SOSAGE_PREF_PATH
#define SOSAGE_PREF_PATH "ptilouk"
#endif

#ifndef SOSAGE_PREF_SUBPATH
#define SOSAGE_PREF_SUBPATH "sosage"
#endif

#endif // SOSAGE_CONFIG_OPTIONS_H
