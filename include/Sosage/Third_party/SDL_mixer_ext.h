/*
  [include/Sosage/Third_party/SDL_mixer_ext.h]
  Wrapper for SDL library (extended sound system).

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

#ifndef SOSAGE_THIRD_PARTY_SDL_MIXER_EXT_H
#define SOSAGE_THIRD_PARTY_SDL_MIXER_EXT_H

#include <Sosage/Config/platform.h>

#ifdef SOSAGE_LINKED_WITH_SDL_MIXER_EXT

#include <Sosage/Core/Asset_manager.h>

#include <SDL_mixer_ext.h>

#include <array>
#include <string>
#include <vector>

namespace Sosage
{

namespace Config
{
constexpr int max_music_volume = 64;
constexpr int max_sound_volume = 128;
constexpr int max_panning = 255;
constexpr int sound_channels = 16;
} // namespace Config

namespace Third_party
{

class SDL_mixer_ext
{
public:

  using Music = std::pair<Mix_Music*, Asset>;
  using Sound = Mix_Chunk*;

private:

  static std::array<bool, Config::sound_channels> m_available_channels;

public:

  SDL_mixer_ext ();
  ~SDL_mixer_ext ();

  static Music load_music (const std::string& file_name);
  static Sound load_sound (const std::string& file_name);

  static void delete_music (Music& music);
  static void delete_sound (Sound& sound);

  void set_music_channels (std::size_t nb);
  void start_music (const Music& music, int channel, double volume);
  void stop_music(const Music& music, int channel);
  void fade (const Music& music, int channel, double time, bool in, double position = 0.);
  void set_volume (const Music& music, int channel, double percentage);
  void pause_music (const Music& music, int channel);
  void resume_music (const Music& music, int channel);
  void play_sound (const Sound& sound, double volume, double panning = 0.5);

  double position (const Music& music) const;

private:

  int reserve_channel();
};

} // namespace Third_party

} // namespace Sosage

#endif

#endif // SOSAGE_THIRD_PARTY_SDL_MIXER_EXT_H
