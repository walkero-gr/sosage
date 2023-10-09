/*
  [include/Sosage/Utils/Gamepad_info.h]
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

#ifndef SOSAGE_UTILS_GAMEPAD_INFO_H
#define SOSAGE_UTILS_GAMEPAD_INFO_H

#include <Sosage/Utils/enum.h>

#include <string>

namespace Sosage
{

enum Gamepad_labels { NO_LABEL, NINTENDO, XBOX, PLAYSTATION };


struct Gamepad_info
{
  std::string id;
  std::string name;
  Gamepad_labels labels;
  bool ok_down;

  Gamepad_info (unsigned short vendor = 0, unsigned short product = 0,
                const std::string& name = "Default controller");
  Gamepad_info (const std::string& id, const Gamepad_labels& labels, const bool& ok_down);
};

std::string gamepad_label (const Gamepad_info& info, const Event_value& value);

}

#endif // SOSAGE_UTILS_GAMEPAD_INFO_H
