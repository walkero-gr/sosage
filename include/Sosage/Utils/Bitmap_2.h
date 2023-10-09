/*
  [include/Sosage/Utils/Bitmap_2.h]
  Bitmap image mask.

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

#ifndef SOSAGE_UTILS_BITMAP_2_H
#define SOSAGE_UTILS_BITMAP_2_H

#include <vector>

namespace Sosage
{

class Bitmap_2
{
private:
  std::vector<unsigned char> m_data;
  std::size_t m_width;

public:

  Bitmap_2 ();
  Bitmap_2 (const std::size_t& width, const std::size_t& height, const bool& value = true);
  bool empty() const;
  std::size_t width() const;
  std::size_t height() const;
  std::size_t size() const;
  bool operator() (const std::size_t& x, const std::size_t& y) const;
  void set (const std::size_t& x, const std::size_t& y, bool value);

  unsigned char* data();
};

}

#endif // SOSAGE_UTILS_BITMAP_2_H
