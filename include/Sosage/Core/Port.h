/*
  [include/Sosage/Core/Port.h]
  Abstraction file for third party port.

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

#ifndef SOSAGE_CORE_PORT_H
#define SOSAGE_CORE_PORT_H

#include <Sosage/Config/platform.h>
#ifdef SOSAGE_PORT
#include <Sosage/Third_party/Port.h>
#else
#include <Sosage/Third_party/SDL_events.h>
#define SOSAGE_PORT_MAIN 
namespace Sosage::Core::Port
{
	inline void init() { }
	inline void notify_data_change() { }
  inline bool init_gamepad(const std::string&, Gamepad_labels&, bool&) { return false;  }
  inline Event window_event(const SDL_Event&) { return Event(); }
  inline Event gamepad_event(const Event_type&, const SDL_Event&) { return Event(); }
} // namespace Sosage::Core::Port
#endif

#endif
