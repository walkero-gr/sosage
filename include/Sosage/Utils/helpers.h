/*
  [include/Sosage/Utils/helpers.h]
  Useful macros.

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

#ifndef SOSAGE_UTILS_HELPERS_H
#define SOSAGE_UTILS_HELPERS_H

#include <Sosage/Config/platform.h>

#ifdef SOSAGE_WINDOWS // Windows is shit at constexpr
#define constexpr_auto static const auto
#else
#define constexpr_auto constexpr auto
#endif

#define is_looking_right(x) \
  (get<C::Animation>(x + "_head", "image")->frames().front().y == 0)

#define is_walking_right(x) \
  (get<C::Animation>(x + "_body", "image")->frames().front().y != 2)

#define is_character(id) \
  request<C::String>((id), "color")

#define get_ground_map(id) \
  (value<C::Boolean>(id, "uses_2nd_map", false) ? \
  request<C::Ground_map>("background", "2nd_ground_map") : \
  request<C::Ground_map>("background", "ground_map"))

#endif // SOSAGE_UTILS_HELPERS_H
