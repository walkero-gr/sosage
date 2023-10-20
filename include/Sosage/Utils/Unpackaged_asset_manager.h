/*
  [include/Sosage/Utils/Unpackaged_asset_manager.h]
  Handle unpackaged assets.

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

#ifndef SOSAGE_UTILS_UNPACKAGED_ASSET_MANAGER_H
#define SOSAGE_UTILS_UNPACKAGED_ASSET_MANAGER_H

#ifndef SOSAGE_PACKAGED

#include <Sosage/Third_party/SDL_file.h>
#include <Sosage/Utils/binary_io.h>

#include <unordered_map>

namespace Sosage
{

namespace IO = Third_party::SDL_file;

class Unpackaged_asset_manager;

class Unpackaged_asset
{
  IO::Asset m_base;

  Unpackaged_asset (const std::string& filename, bool write = false);

  friend Unpackaged_asset_manager;
public:

  Unpackaged_asset();
  operator bool() const;
  void close();
  SDL_RWops* base();
  Buffer* buffer();
  std::size_t size() const;
  std::size_t read (void* ptr, std::size_t max_num);
  void write (const std::string& str);
  std::size_t tell();
  void seek (std::size_t pos);
  template <typename T>
  T binary_read ()
  {
    T t;
    IO::read (m_base, &t, sizeof(T));
    return t;
  }
  void binary_read (Buffer& b);
};


class Unpackaged_asset_manager
{
  static std::string folder_name;

public:

  static bool init (const std::string& folder, bool scap_mode = false);
  static Unpackaged_asset open_pref (const std::string& filename, bool write = false);
  static Unpackaged_asset open (const std::string& filename, bool file_is_package = false);
  static bool exists (const std::string& filename);

private:

  static std::string local_file_name (const std::string& filename);
};

} // namespace Sosage

#endif // not SOSAGE_PACKAGED

#endif // SOSAGE_UTILS_UNPACKAGED_ASSET_MANAGER_H
