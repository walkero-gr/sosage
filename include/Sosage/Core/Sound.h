/*
  [include/Sosage/Core/Sound.h]
  Abstraction file for third party library handling sound.

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

#ifndef SOSAGE_CORE_SOUND_H
#define SOSAGE_CORE_SOUND_H

#include <Sosage/Config/platform.h>

#if defined(SOSAGE_LINKED_WITH_SDL_MIXER)

#include <Sosage/Third_party/SDL_mixer.h>
namespace Sosage::Core
{
using Sound = Third_party::SDL_mixer;
} // namespace Sosage::Core

#elif defined(SOSAGE_LINKED_WITH_SDL_MIXER_EXT)

#include <Sosage/Third_party/SDL_mixer_ext.h>
namespace Sosage::Core
{
using Sound = Third_party::SDL_mixer_ext;
} // namespace Sosage::Core

#else

#include <string>

namespace Sosage::Core
{

class No_sound
{
public:

  using Sound = int;
  using Music = int;

  No_sound() { }
  ~No_sound() { }

  static Music load_music (const std::string&) { return 0; }
  static Sound load_sound (const std::string&) { return 0; }

  static void delete_music (const Music&) { }
  static void delete_sound (const Sound&) { }

  void set_music_channels (std::size_t) { }
  void start_music (const Music&, int, double) {}
  void stop_music(const Music&, int) {}
  void fade (const Music&, int, double, bool, double = 0.) {}
  void set_volume (const Music&, int, double) {}
  void pause_music (const Music&, int) {}
  void resume_music (const Music&, int) {}
  void play_sound (const Sound&, double, double = 0.5) {}

  double position (const Music&) const { return 0.; }

};

using Sound = No_sound;

} // namespace Sosage::Core

#endif

#endif
