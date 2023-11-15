/*
  [src/Sosage/Utils/Packaged_asset_manager.cpp]
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

#ifdef SOSAGE_PACKAGED

#include <Sosage/Third_party/LZ4.h>
#include <Sosage/Utils/Packaged_asset_manager.h>
#include <Sosage/Utils/conversions.h>
#include <Sosage/Utils/error.h>
#include <Sosage/Utils/image_split.h>
#include <Sosage/Utils/profiling.h>

namespace Sosage
{

std::string Packaged_asset_manager::folder_name = "";
std::vector<Buffer> Packaged_asset_manager::buffers;
Package_asset_map Packaged_asset_manager::package_asset_map;


Packaged_asset::Packaged_asset (const std::string& filename, bool write)
  : m_buffer(nullptr)
{
  m_base = IO::open(filename, write);
}

Packaged_asset::Packaged_asset (Buffer* buffer)
  : m_buffer(buffer)
{
  m_base = IO::open(buffer->data(), buffer->size());
}

Packaged_asset::Packaged_asset (const void* memory, std::size_t size)
{
  m_base = IO::open(memory, size);
}

Packaged_asset::Packaged_asset() { }

Packaged_asset::operator bool() const
{
  return bool(m_base);
}

void Packaged_asset::close()
{
  IO::close(m_base);
  m_base.buffer = nullptr;
  if (m_buffer != nullptr)
  {
    delete m_buffer;
    m_buffer = nullptr;
  }
}

SDL_RWops* Packaged_asset::base()
{
  return m_base.buffer;
}

Buffer* Packaged_asset::buffer()
{
  return m_buffer;
}

std::size_t Packaged_asset::size() const
{
  return m_base.size;
}

std::size_t Packaged_asset::read (void* ptr, std::size_t max_num)
{
  return IO::read (m_base, ptr, max_num);
}

void Packaged_asset::write (const std::string& str)
{
  IO::write (m_base, str.c_str());
}

std::size_t Packaged_asset::tell()
{
  return IO::tell(m_base);
}

void Packaged_asset::seek (std::size_t pos)
{
  IO::seek(m_base, pos);
}

void Packaged_asset::binary_read (Buffer& b)
{
  IO::read (m_base, b.data(), b.size());
}

bool Packaged_asset_manager::init (const std::string& folder, bool scap_mode)
{
  folder_name = folder;
  if (scap_mode)
    return true;

  Packaged_asset asset (local_file_name("general.data"));
  if (asset)
  {
    asset.close();
    buffers.resize(packages.size());
  }
  else
    return false;

  SOSAGE_TIMER_START(Asset_manager__depackage);
  std::size_t buffer_id = 0;
  for (const std::string& package : packages)
  {
    Packaged_asset asset = open (package + ".data", true);

    std::size_t end = 0;
    while (true)
    {
      auto path_size = asset.binary_read<unsigned char>();
      if (path_size == 0)
        break;

      Buffer path (path_size);
      asset.binary_read(path);
      std::string fname = std::string (path.begin(), path.end());

      Packaged_asset_info passet;
      passet.buffer_id = buffer_id;

      auto ext = fname.find(".sdl_surface.lz4");
      if (ext != std::string::npos) // custom surface
      {
        fname.resize(ext);
        fname = fname + ".png";
        passet.width = asset.binary_read<unsigned short>();
        passet.height = asset.binary_read<unsigned short>();
        passet.format = asset.binary_read<unsigned int>();
        SDL_PixelFormat* pixel_format = SDL_AllocFormat(passet.format);
        unsigned int bpp = (unsigned int)(pixel_format->BytesPerPixel);
        SDL_FreeFormat(pixel_format);

        bool is_object = contains(fname, "images/objects") ||
                         contains(fname, "images/interface") ||
                         contains(fname, "images/inventory") ||
                         contains(fname, "images/masks");

        bool is_map = endswith (fname, "_map.png");

        Uint32 nb_x = 1;
        Uint32 nb_y = 1;
        if (!is_map)
        {
          nb_x = Splitter::nb_sub (passet.width);
          nb_y = Splitter::nb_sub (passet.height);
        }

        for (Uint32 x = 0; x < nb_x; ++ x)
        {
          for (Uint32 y = 0; y < nb_y; ++ y)
          {
            SDL_Rect rect;
            rect.x = 0; rect.y = 0; rect.w = passet.width; rect.h = passet.height;
            if (!is_map)
              rect = Splitter::rect (passet.width, passet.height, x, y);

            Packaged_asset_info lpasset;
            lpasset.buffer_id = buffer_id;
            lpasset.width = rect.w;
            lpasset.height = rect.h;
            lpasset.format = passet.format;
            lpasset.size = bpp * lpasset.width * lpasset.height;
            lpasset.compressed_size = asset.binary_read<unsigned int>();
            lpasset.position = asset.tell();
            end = lpasset.position + lpasset.compressed_size;
            asset.seek(end);

            std::string lfname = fname + "." + std::to_string(x)
                                 + "x" + std::to_string(y);
            package_asset_map.insert (std::make_pair (lfname, lpasset));

            if (is_object)
            {
              Packaged_asset_info lpasset;
              lpasset.buffer_id = buffer_id;
              lpasset.width = rect.w;
              lpasset.height = rect.h;
              lpasset.format = passet.format;
              lpasset.size = bpp * lpasset.width * lpasset.height;
              lpasset.compressed_size = asset.binary_read<unsigned int>();
              lpasset.position = asset.tell();
              end = lpasset.position + lpasset.compressed_size;
              asset.seek(end);

              std::string lfname = fname + "." + std::to_string(x)
                                   + "x" + std::to_string(y) + ".HL";
              package_asset_map.insert (std::make_pair (lfname, lpasset));
            }
          }
        }

        if (is_object)
        {
          Packaged_asset_info lpasset;
          lpasset.buffer_id = buffer_id;
          lpasset.size = asset.binary_read<unsigned int>();
          lpasset.compressed_size = asset.binary_read<unsigned int>();
          lpasset.position = asset.tell();
          end = lpasset.position + lpasset.compressed_size;
          asset.seek(end);
          std::string lfname = fname + ".mask";
          package_asset_map.insert (std::make_pair (lfname, lpasset));
        }
      }
      else if (!contains (fname, ".lz4")) // uncompressed file
      {
        passet.size = asset.binary_read<unsigned int>();
        passet.position = asset.tell();
        end = passet.position + passet.size;
        asset.seek(end);
      }
      else
      {
        passet.size = asset.binary_read<unsigned int>();
        passet.compressed_size = asset.binary_read<unsigned int>();
        passet.position = asset.tell();
        end = passet.position + passet.compressed_size;
        asset.seek(end);
        fname.resize(fname.size() - 4);
      }
      package_asset_map.insert (std::make_pair (fname, passet));
    }

    asset.seek(0);
    buffers[buffer_id].resize(end);
    asset.read(buffers[buffer_id].data(), end);
    asset.close();

    ++ buffer_id;
  }
#if 0
  for (const auto& p : package_asset_map)
  {
    std::cerr << p.first << " is in buffer " << p.second.buffer_id
              << " at position " << p.second.position << " with compressed size "
              << p.second.compressed_size << " and size " << p.second.size << std::endl;
  }
#endif
  SOSAGE_TIMER_STOP(Asset_manager__depackage);

  return true;
}

Packaged_asset Packaged_asset_manager::open_pref (const std::string& filename, bool write)
{
  return Packaged_asset (IO::pref_path() + filename, write);
}

Packaged_asset Packaged_asset_manager::open (const std::string& filename, bool file_is_package)
{
  if (!file_is_package)
  {
    auto iter = package_asset_map.find(filename);
    if (iter == package_asset_map.end())
    {
      debug << "Can't find asset " << filename << std::endl;
      return Packaged_asset();
    }
    Packaged_asset_info& asset = iter->second;
    if (asset.compressed_size == 0) // uncompressed file
      return Packaged_asset (buffers[asset.buffer_id].data() + asset.position, asset.size);
    // else
    Buffer* buffer = new Buffer(asset.size);
    lz4_decompress_buffer (buffers[asset.buffer_id].data() + asset.position, asset.compressed_size,
        buffer->data(), asset.size);
    return Packaged_asset (buffer);
  }
  // else
  return Packaged_asset (local_file_name(filename));
}

bool Packaged_asset_manager::exists (const std::string& filename)
{
  return package_asset_map.find(filename) != package_asset_map.end();
}

std::tuple<int, int, int> Packaged_asset_manager::image_info (const std::string& filename)
{
  auto iter = package_asset_map.find(filename);
  check (iter != package_asset_map.end(), "Packaged asset " + filename + " not found");
  Packaged_asset_info& asset = iter->second;
  return std::make_tuple(asset.width, asset.height, asset.format);
}

void Packaged_asset_manager::open (const std::string& filename, void* memory, Uint32 x, Uint32 y, bool highlight)
{
  std::string fname = filename + "." + std::to_string(x) + "x" + std::to_string(y);
  if (highlight)
    fname += ".HL";
  auto iter = package_asset_map.find(fname);
  check (iter != package_asset_map.end(), "Packaged asset " + fname + " not found");
  Packaged_asset_info& asset = iter->second;

  lz4_decompress_buffer (buffers[asset.buffer_id].data() + asset.position, asset.compressed_size,
      memory, asset.size);
}

const Package_asset_map& Packaged_asset_manager::asset_map()
{
  return Packaged_asset_manager::package_asset_map;
}

std::string Packaged_asset_manager::local_file_name (const std::string& filename)
{
  return folder_name + filename;
}

} // namespace Sosage

#endif // SOSAGE_PACKAGED
