/*
  [src/Sosage/Utils/color.cpp]
  Handle RGB colors with strings and hex values.

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

#include <Sosage/Utils/color.h>

#include <sstream>

namespace Sosage
{

RGB_color color_from_string (const std::string& str)
{
  std::stringstream ss(str);
  int num;
  ss >> std::hex >> num;
  return { (unsigned char)(num / 0x10000),
           (unsigned char)((num / 0x100) % 0x100),
           (unsigned char)(num % 0x100) };
}

bool is_transparent_black_or_white (const RGBA_color& color)
{
  if (color[3] != 0)
    return false;

  return (color[0] == 255 && color[1] == 255 && color[2] == 255)
      || (color[0] == 0 && color[1] == 0 && color[2] == 0);
}

} // namespace Sosage
