/*
  [include/Sosage/Utils/image_split.h]
  Handle splitting and recomposing images.

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

#ifndef SOSAGE_UTILS_IMAGE_SPLIT_H
#define SOSAGE_UTILS_IMAGE_SPLIT_H

#include <SDL.h>

#include <vector>
#include <iostream>

namespace Sosage::Splitter
{

constexpr Uint32 max_length = 512;
Uint32 nb_sub (const Uint32& length);
SDL_Rect rect (const Uint32& width, const Uint32& height,
               const Uint32& x, const Uint32& y);
std::vector<SDL_Surface*> split_image (SDL_Surface* image);

} // namespace Sosage::Splitter

#endif // SOSAGE_UTILS_IMAGE_SPLIT_H
