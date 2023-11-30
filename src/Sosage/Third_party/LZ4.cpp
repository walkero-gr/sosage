/*
  [src/Sosage/Third_party/LZ4.cpp]
  Wrapper for LZ4 compression library.

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

#if defined(SOSAGE_PACKAGED) || defined(SOSAGE_SCAP)

#include <Sosage/Third_party/LZ4.h>
#include <Sosage/Utils/conversions.h>
#include <Sosage/Utils/error.h>
#include <Sosage/Config/platform.h>

#include <lz4.h>
#include <lz4hc.h>

//#define SOSAGE_FAST_COMPRESS

namespace Sosage
{

Buffer lz4_compress_buffer (void* data, std::size_t size)
{
  const char* cdata = reinterpret_cast<const char*>(data);
  unsigned int max_lz4_size = LZ4_compressBound(size);
  Buffer out (max_lz4_size);
#ifdef SOSAGE_FAST_COMPRESS
  unsigned int true_size = LZ4_compress_default(cdata, out.data(), size, max_lz4_size);
#else
  unsigned int true_size = LZ4_compress_HC(cdata, out.data(), size, max_lz4_size,
                                           LZ4HC_CLEVEL_MAX);
#endif
  out.resize(true_size);
  return out;
}

void lz4_decompress_buffer (void* data, std::size_t size, void* out, std::size_t output_size)
{
  const char* cdata = reinterpret_cast<const char*>(data);
  char* cout = reinterpret_cast<char*>(out);
  int decompressed_size = LZ4_decompress_safe (cdata, cout, size, output_size);

  check (std::size_t(decompressed_size) == output_size,
         "LZ4 decompressed size differs from expected ("
         + to_string(decompressed_size) + " != " + to_string(output_size) + ")");
}

} // namespace Sosage

#endif
