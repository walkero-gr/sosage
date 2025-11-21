/*
  [src/Sosage/Utils/locale.cpp]
  Accessing locale info on all platforms.

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

#include <Sosage/Config/platform.h>
#if !defined(__amigaos4__) && !defined(__morphos__)
#include <Sosage/Third_party/Steam.h>
#endif
#include <Sosage/Utils/locale.h>

#include <SDL_locale.h>


namespace Sosage
{

std::vector<std::string> get_locales()
{
#ifdef SOSAGE_LINKED_WITH_STEAMSDK
  return { Steam::game_language() };
#endif

  SDL_Locale* locale = SDL_GetPreferredLocales();
  std::vector<std::string> out;
  while (locale->language != nullptr)
  {
    std::string language = locale->language;
    if (locale->country != nullptr)
      language += "_" + std::string(locale->country);
    out.push_back (language);
    ++ locale;
  }
  return out;
}

} // namespace Sosage
