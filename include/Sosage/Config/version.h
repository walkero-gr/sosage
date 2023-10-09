/*
  [include/Sosage/Config/version.h]
  Version of SOSAGE.

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

#ifndef SOSAGE_CONFIG_VERSION_H
#define SOSAGE_CONFIG_VERSION_H

#include <string>

namespace Sosage
{

namespace Version
{

constexpr unsigned int major = SOSAGE_VERSION_MAJOR;
constexpr unsigned int minor = SOSAGE_VERSION_MINOR;
constexpr unsigned int patch = SOSAGE_VERSION_PATCH;
constexpr const char* name = SOSAGE_VERSION_NAME;

inline std::string str(bool include_name = true)
{
  return std::to_string(major) + "."
    + std::to_string(minor) + "."
    + std::to_string(patch) + (include_name ? (std::string("-") + name) : "");
}

inline unsigned int get()
{
  return major * 10000 + minor * 100 + patch;
}

inline unsigned int parse (const std::string& vstring)
{
  std::size_t pos = vstring.find('.');
  std::string vmajor (vstring.begin(), vstring.begin() + pos);
  std::size_t pos2 = vstring.find('.', pos+1);
  std::string vminor (vstring.begin() + pos+1, vstring.begin() + pos2);
  std::string vpatch (vstring.begin() + pos2+1, vstring.end());
  return (unsigned int)(std::atoi(vmajor.c_str()) * 10000
                        + std::atoi(vminor.c_str()) * 100
                        + std::atoi(vpatch.c_str()));
}

}

}

#endif // SOSAGE_CONFIG_VERSION_H
