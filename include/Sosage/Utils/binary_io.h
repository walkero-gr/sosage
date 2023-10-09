/*
  [include/Sosage/Utils/binary_io.h]
  Read and write variables in binary.

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

#ifndef SOSAGE_UTILS_BINARY_IO_H
#define SOSAGE_UTILS_BINARY_IO_H

#include <iostream>
#include <memory>
#include <vector>

namespace Sosage
{

using Buffer = std::vector<char>;
using Buffer_ptr = std::shared_ptr<Buffer>;

template <typename T>
void binary_write (std::ostream& os, const T& t)
{
  os.write (reinterpret_cast<const char*>(&t), sizeof(T));
}

void binary_write (std::ostream& os, const std::size_t& t);
void binary_write (std::ostream& os, const Buffer& b);
void binary_write (std::ostream& os, const std::string& str);

template <typename T>
T binary_read (std::istream& is)
{
  T t;
  is.read (reinterpret_cast<char*>(&t), sizeof(T));
  return t;
}

void binary_read (std::istream& is, Buffer& b);

} // namespace Sosage

#endif // SOSAGE_UTILS_BINARY_IO_H
