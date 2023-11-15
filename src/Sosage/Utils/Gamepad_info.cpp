/*
  [src/Sosage/Utils/Gamepad_info.cpp]
  Handle different types of Gamepad.

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

#include <Sosage/Utils/conversions.h>
#include <Sosage/Utils/Gamepad_info.h>
#include <Sosage/Utils/error.h>

#ifdef SOSAGE_PORT
#include <Sosage/Third_party/Port.h>
#endif

#include <unordered_map>

namespace Sosage
{

Gamepad_info::Gamepad_info (unsigned short vendor, unsigned short product,
                            const std::string& name)
  : name (name)
{
  id = to_string (vendor) + ":" + to_string(product);
#ifdef SOSAGE_PORT
  if (Port::init_gamepad(name, labels, ok_down))
  { }
  else
#endif
  if (contains (name, "Xbox") ||
      contains (name, "Steam"))
  {
    labels = XBOX;
    ok_down = true;
  }
  else if (startswith(name, "Nintendo") ||
           startswith(name, "8BitDo"))
  {
    labels = NINTENDO;
    ok_down = false;
  }
  else if (contains(name, "PlayStation") ||
           contains(name, "PS2") ||
           contains(name, "PS3") ||
           contains(name, "PS4") ||
           contains(name, "PS5") ||
           contains(name, "PSX"))
  {
    labels = PLAYSTATION;
    ok_down = true;
  }
  else
  {
    labels = NO_LABEL;
    ok_down = true;
  }
}

Gamepad_info::Gamepad_info (const std::string& id, const Gamepad_labels& labels, const bool& ok_down)
  : id(id)
  , name ("Saved controller")
  , labels(labels)
  , ok_down(ok_down)
{

}

std::string gamepad_label (const Gamepad_info& info, const Event_value& value)
{
  static std::unordered_map<Event_value, std::string>
      nintendo = { {NORTH, "X"}, {EAST, "A"}, {SOUTH, "B"}, {WEST, "Y"} };
  static std::unordered_map<Event_value, std::string>
      xbox = { {NORTH, "Y"}, {EAST, "B"}, {SOUTH, "A"}, {WEST, "X"} };
  static std::unordered_map<Event_value, std::string>
      playstation = { {NORTH, "Playstation_triangle"},
                      {EAST, "Playstation_circle"},
                      {SOUTH, "Playstation_cross"},
                      {WEST, "Playstation_square"} };

  if (info.labels == NINTENDO)
    return nintendo[value];

  if (info.labels == XBOX)
    return xbox[value];

  if (info.labels == PLAYSTATION)
    return playstation[value];

  // no label
  return "";
}

} // namespace Sosage
