/*
  [include/Sosage/Utils/demangle.h]
  Display human-readable types.

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

#ifndef SOSAGE_UTILS_DEMANGLE_H
#define SOSAGE_UTILS_DEMANGLE_H

#include <Sosage/Config/platform.h>

#ifndef SOSAGE_WINDOWS // TODO: demangle on Visual Studio
#include <cxxabi.h>
#endif

#include <string>

namespace Sosage
{

inline std::string demangle (const char* name)
{
#ifdef SOSAGE_WINDOWS
	return name;
#else
  int status = 0;
  char* cout = abi::__cxa_demangle(name, nullptr, nullptr, &status);
  std::string out(cout);
  delete cout;
  return out;
#endif
}

} // namespace Sosage

#endif // SOSAGE_UTILS_DEMANGLE_H
