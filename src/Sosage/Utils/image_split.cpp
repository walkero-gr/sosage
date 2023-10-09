/*
  [src/Sosage/Utils/image_split.cpp]
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

#include <Sosage/Utils/image_split.h>

#include <vector>
#include <iostream>

namespace Sosage::Splitter
{

Uint32 nb_sub (const Uint32& length)
{
  return 1 + (length / max_length);
}

SDL_Rect rect (const Uint32& width, const Uint32& height,
               const Uint32& x, const Uint32& y)
{
  Uint32 nb_x = nb_sub(width);
  Uint32 nb_y = nb_sub(height);
  Uint32 w = 1 + width / nb_x;
  Uint32 h = 1 + height / nb_y;

  SDL_Rect out;
  out.x = w * x;
  out.y = h * y;
  out.w = ((x == nb_x - 1) ? (width - out.x) : w);
  out.h = ((y == nb_y - 1) ? (height - out.y) : h);
  return out;
}

std::vector<SDL_Surface*> split_image (SDL_Surface* image)
{
  SDL_SetSurfaceBlendMode(image, SDL_BLENDMODE_NONE);
  std::vector<SDL_Surface*> out;
  for (Uint32 x = 0; x < nb_sub(image->w); ++ x)
  {
    for (Uint32 y = 0; y < nb_sub(image->h); ++ y)
    {
      SDL_Rect source = rect (image->w, image->h, x, y);
      SDL_Rect target;
      target.x = 0;
      target.y = 0;
      target.w = source.w;
      target.h = source.h;

      SDL_Surface* tile = SDL_CreateRGBSurfaceWithFormat
        (image->flags, source.w, source.h, 32, image->format->format);

      SDL_BlitSurface (image, &source, tile, &target);

      out.push_back(tile);
    }
  }
  return out;
}


} // namespace Sosage::Splitter
