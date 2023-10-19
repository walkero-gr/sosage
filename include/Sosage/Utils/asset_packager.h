/*
  [include/Sosage/Utils/asset_packager.h]
  Package (and depackage) assets.

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

#ifndef SOSAGE_UTILS_ASSET_PACKAGER_H
#define SOSAGE_UTILS_ASSET_PACKAGER_H

#include <Sosage/Core/Asset_manager.h>

#include <memory>

namespace Sosage::SCAP
{

constexpr unsigned int surface_format = SDL_PIXELFORMAT_ARGB8888;
constexpr unsigned int flat_surface_format = SDL_PIXELFORMAT_RGB888;

std::string package (const std::string& filename);

using Output_file = std::shared_ptr<std::ofstream>;
using Package_files = std::unordered_map<std::string, Output_file>;

Package_files open_packages (const std::string& root);
void write_file (std::ofstream& ofile, const std::string& filename);
void write_image (std::ofstream& ofile, const std::string& filename, bool is_object);
void compile_package (const std::string& input_folder, const std::string& output_folder);
void decompile_package (const std::string& filename, std::string folder);

} // namespace Sosage::SCAP

#endif // SOSAGE_UTILS_ASSET_PACKAGER_H
