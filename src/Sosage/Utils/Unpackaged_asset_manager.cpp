/*
  [src/Sosage/Utils/Unpackaged_asset_manager.cpp]
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

#ifndef SOSAGE_PACKAGED

#include <Sosage/Third_party/LZ4.h>
#include <Sosage/Utils/Unpackaged_asset_manager.h>
#include <Sosage/Utils/conversions.h>
#include <Sosage/Utils/error.h>
#include <Sosage/Utils/image_split.h>
#include <Sosage/Utils/profiling.h>

namespace Sosage
{

std::string Unpackaged_asset_manager::folder_name = "";

Unpackaged_asset::Unpackaged_asset (const std::string& filename, bool write)
{
  m_base = Core::File_IO::open(filename, write);
}

Unpackaged_asset::Unpackaged_asset() { }

Unpackaged_asset::operator bool() const
{
  return bool(m_base);
}

void Unpackaged_asset::close()
{
  Core::File_IO::close(m_base);
}

SDL_RWops* Unpackaged_asset::base()
{
  return m_base.buffer;
}

Buffer* Unpackaged_asset::buffer()
{
  return nullptr;
}

std::size_t Unpackaged_asset::size() const
{
  return m_base.size;
}

std::size_t Unpackaged_asset::read (void* ptr, std::size_t max_num)
{
  return Core::File_IO::read (m_base, ptr, max_num);
}

void Unpackaged_asset::write (const std::string& str)
{
  Core::File_IO::write (m_base, str.c_str());
}

std::size_t Unpackaged_asset::tell()
{
  return Core::File_IO::tell(m_base);
}

void Unpackaged_asset::seek (std::size_t pos)
{
  Core::File_IO::seek(m_base, pos);
}

void Unpackaged_asset::binary_read (Buffer& b)
{
  Core::File_IO::read (m_base, b.data(), b.size());
}


bool Unpackaged_asset_manager::init (const std::string& folder, bool scap_mode)
{
  folder_name = folder;
  if (scap_mode)
    return true;

  if (!exists("data/init.yaml"))
    return false;

  return true;
}

Unpackaged_asset Unpackaged_asset_manager::open_pref (const std::string& filename, bool write)
{
  return Unpackaged_asset (Core::File_IO::pref_path() + filename, write);
}

Unpackaged_asset Unpackaged_asset_manager::open (const std::string& filename, bool)
{
  return Unpackaged_asset (local_file_name(filename));
}

bool Unpackaged_asset_manager::exists (const std::string& filename)
{
  Unpackaged_asset asset (local_file_name(filename));
  if (asset)
  {
    asset.close();
    return true;
  }
  return false;
}

std::string Unpackaged_asset_manager::local_file_name (const std::string& filename)
{
  return folder_name + filename;
}

} // namespace Sosage

#endif // not SOSAGE_PACKAGED
