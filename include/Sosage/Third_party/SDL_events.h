/*
  [include/Sosage/Third_party/SDL_events.h]
  Wrapper for SDL library (event handling).

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

#ifndef SOSAGE_THIRD_PARTY_SDL_EVENTS_H
#define SOSAGE_THIRD_PARTY_SDL_EVENTS_H

#include <SDL.h>
#include <Sosage/Utils/Event.h>
#include <Sosage/Utils/Gamepad_info.h>

#include <utility>
#include <unordered_map>
#include <vector>

namespace Sosage
{

namespace Config
{
constexpr int no_value = std::numeric_limits<int>::max();
constexpr int deadzone = 6000;
} // namespace Config

namespace Third_party
{

using Gamepad_ptr = SDL_GameController*;

class SDL_events
{
  std::unordered_map<SDL_EventType, Event_type> m_type_map;
  mutable bool m_gamepad_changed;
  mutable int m_latest_gamepad_used;

public:

  SDL_events();

  ~SDL_events();

  Event next_event();

  std::pair<Gamepad_ptr, int> open_gamepad (int idx) const;
  void close_gamepad (Gamepad_ptr ptr) const;
  void rumble_gamepad (Gamepad_ptr ptr, double intensity, double duration) const;

  Gamepad_info gamepad_info(Gamepad_ptr ptr) const;

private:

  Event mouse_event (const Event_type& type, const SDL_Event& ev) const;
  Event keyboard_event (const Event_type& type, const SDL_Event& ev) const;
  Event touch_event (const Event_type& type, const SDL_Event& ev) const;
  Event gamepad_event (const Event_type& type, const SDL_Event& ev) const;
};

} // namespace Third_party

} // namespace Sosage

#endif // SOSAGE_THIRD_PARTY_SDL_EVENTS_H
