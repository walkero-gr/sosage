/*
  [include/Sosage/Utils/Packaged_asset_manager.h]
  Handle packaged assets.

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

#ifndef SOSAGE_UTILS_PACKAGED_ASSET_MANAGER_H
#define SOSAGE_UTILS_PACKAGED_ASSET_MANAGER_H

#if defined(SOSAGE_PACKAGED) || defined(SOSAGE_SCAP)

#include <Sosage/Config/platform.h>
#include <Sosage/Core/File_IO.h>
#include <Sosage/Utils/binary_io.h>
#include <Sosage/Utils/helpers.h>

#include <array>
#include <unordered_map>

namespace Sosage
{

constexpr_auto packages = { "general", "locale", "images", "images_animations", "images_scenery", "sounds" };

class Packaged_asset_manager;

class Packaged_asset
{
  Core::File_IO::Asset m_base;
  Buffer* m_buffer;

  Packaged_asset (const std::string& filename, bool write = false);
  Packaged_asset (Buffer* buffer);
  Packaged_asset (const void* memory, std::size_t size);

  friend Packaged_asset_manager;
public:

  Packaged_asset();
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
    Core::File_IO::read (m_base, &t, sizeof(T));
    return t;
  }
  void binary_read (Buffer& b);
};

struct Packaged_asset_info
{
  std::size_t buffer_id = 0;
  std::size_t position = 0;
  std::size_t compressed_size = 0;
  std::size_t size = 0;

  // Only used by images
  unsigned short width = 0;
  unsigned short height = 0;
  unsigned int format = 0;

  Buffer buffer;
};

using Package_asset_map = std::unordered_map<std::string, Packaged_asset_info>;

class Packaged_asset_manager
{
  static std::string folder_name;
  static std::vector<Buffer> buffers;
  static Package_asset_map package_asset_map;

public:

  static bool init (const std::string& folder, bool scap_mode = false);
  static Packaged_asset open_pref (const std::string& filename, bool write = false);
  static Packaged_asset open (const std::string& filename, bool file_is_package = false);
  static bool exists (const std::string& filename);
  static std::tuple<int, int, int> image_info (const std::string& filename);
  static void open (const std::string& filename, void* memory, Uint32 x = 0, Uint32 y = 0, bool highlight = false);

  static const Package_asset_map& asset_map();

private:

  static std::string local_file_name (const std::string& filename);
};

} // namespace Sosage

#endif // SOSAGE_PACKAGED

#endif // SOSAGE_UTILS_PACKAGED_ASSET_MANAGER_H
