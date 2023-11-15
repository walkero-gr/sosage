/*
  [src/Sosage/Third_party/SDL_file.cpp]
  Wrapper for SDL library (file system).

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

#include <Sosage/Config/options.h>
#include <Sosage/Third_party/SDL_file.h>
#include <Sosage/Utils/error.h>

namespace Sosage::Third_party::SDL_file
{

Asset::operator bool() const
{
  return (buffer != nullptr);
}

Asset open (const std::string& filename, bool write)
{
  Asset out;
  out.buffer = SDL_RWFromFile(filename.c_str(), write ? "w" : "r");
  if (out.buffer != nullptr)
    out.size = std::size_t(SDL_RWsize (out.buffer));
  else if (write)
      check(false, "Can't open " + filename + ", " + std::string(SDL_GetError()));
  return out;
}

Asset open (const void* memory, std::size_t size)
{
  Asset out;
  out.buffer = SDL_RWFromConstMem(memory, int(size));
  if (out.buffer != nullptr)
    out.size = std::size_t(SDL_RWsize (out.buffer));
  return out;
}

std::size_t read (Asset asset, void* ptr, std::size_t max_num)
{
  return std::size_t(SDL_RWread(asset.buffer, ptr, 1, max_num));
}

void write (Asset asset, const char* str)
{
  SDL_RWwrite (asset.buffer, str, 1, SDL_strlen(str));
}

std::size_t tell (Asset asset)
{
  return std::size_t(SDL_RWtell(asset.buffer));
}

void seek (Asset asset, std::size_t pos)
{
  SDL_RWseek (asset.buffer, Sint64(pos), RW_SEEK_SET);
}

void close (Asset asset)
{
  int ret = SDL_RWclose (asset.buffer);
  check(ret == 0, "Can't close file, " + std::string(SDL_GetError()));
}

std::string base_path()
{
  char* bp = SDL_GetBasePath();
  std::string out = bp;
  SDL_free(bp);
  return out;
}

std::string pref_path()
{
  char* pp = SDL_GetPrefPath(SOSAGE_PREF_PATH, SOSAGE_PREF_SUBPATH);
  std::string out = pp;
  SDL_free(pp);
  return out;
}

} // namespace Sosage::Third_party::SDL_file
