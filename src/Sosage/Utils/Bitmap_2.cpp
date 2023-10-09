/*
  [src/Sosage/Utils/Bitmap_2.cpp]
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

#include <Sosage/Utils/Bitmap_2.h>

namespace Sosage
{

Bitmap_2::Bitmap_2() : m_width(0) { }

Bitmap_2::Bitmap_2 (const std::size_t& width, const std::size_t& height, const bool& value)
  : m_data (1 + (width * height) / 8, (value ? 255 : 0)), m_width (width)
{ }

bool Bitmap_2::empty() const
{
  return m_data.empty();
}

std::size_t Bitmap_2::width() const
{
  return m_width;
}

std::size_t Bitmap_2::height() const
{
  return (m_data.size() * 8) / m_width;
}

std::size_t Bitmap_2::size() const
{
  return m_data.size();
}

bool Bitmap_2::operator() (const std::size_t& x, const std::size_t& y) const
{
  std::size_t idx = x + m_width * y;
  return bool((m_data[idx / 8] >> (idx % 8)) & 1);
}

void Bitmap_2::set (const std::size_t& x, const std::size_t& y, bool value)
{
  std::size_t idx = x + m_width * y;
  if (value)
    m_data[idx / 8] |= (1 << (idx % 8));
  else
    m_data[idx / 8] &= ~(1 << (idx % 8));
}

unsigned char* Bitmap_2::data()
{
  return m_data.data();
}

} // namespace Sosage
