/*
  [src/Sosage/Utils/Event.cpp]
  Definitions of all possible events.

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

#include <Sosage/Utils/Event.h>

#include <sstream>

namespace Sosage
{

std::ostream& operator<< (std::ostream& os, const Event_type& type)
{
  if (type == EMPTY) os << "EMPTY";
  else if (type == UNUSED) os << "UNUSED";
  else if (type == WINDOW) os << "WINDOW";
  else if (type == MOUSE_DOWN) os << "MOUSE_DOWN";
  else if (type == MOUSE_MOVE) os << "MOUSE_MOVE";
  else if (type == MOUSE_UP) os << "MOUSE_UP";
  else if (type == TOUCH_DOWN) os << "TOUCH_DOWN";
  else if (type == TOUCH_MOVE) os << "TOUCH_MOVE";
  else if (type == TOUCH_UP) os << "TOUCH_UP";
  else if (type == KEY_DOWN) os << "KEY_DOWN";
  else if (type == KEY_UP) os << "KEY_UP";
  else if (type == NEW_GAMEPAD) os << "NEW_GAMEPAD";
  else if (type == BUTTON_DOWN) os << "BUTTON_DOWN";
  else if (type == BUTTON_UP) os << "BUTTON_UP";
  else if (type == STICK_MOVE) os << "STICK_MOVE";
  else os << "WTF";
  return os;
}


std::ostream& operator<< (std::ostream& os, const Event_value& value)
{
  if (value == NONE) os << "NONE";
  else if (value == EXIT) os << "EXIT";
  else if (value == RESIZED) os << "RESIZED";
  else if (value == LEFT) os << "LEFT";
  else if (value == RIGHT) os << "RIGHT";
  else if (value == ALT) os << "ALT";
  else if (value == CTRL) os << "CTRL";
  else if (value == SHIFT) os << "SHIFT";
  else if (value == TAB) os << "TAB";
  else if (value == ANDROID_BACK) os << "ANDROID_BACK";
  else if (value == ENTER) os << "ENTER";
  else if (value == ESCAPE) os << "ESCAPE";
  else if (value == SPACE) os << "SPACE";
  else if (value == UP_ARROW) os << "UP_ARROW";
  else if (value == LEFT_ARROW) os << "LEFT_ARROW";
  else if (value == RIGHT_ARROW) os << "RIGHT_ARROW";
  else if (value == DOWN_ARROW) os << "DOWN_ARROW";
  else if (value == NORTH) os << "NORTH";
  else if (value == EAST) os << "EAST";
  else if (value == WEST) os << "WEST";
  else if (value == SOUTH) os << "SOUTH";
  else if (value == LEFT_SHOULDER) os << "LEFT_SHOULDER";
  else if (value == RIGHT_SHOULDER) os << "RIGHT_SHOULDER";
  else if (value == START) os << "START";
  else if (value == SELECT) os << "SELECT";
  else if (A <= value && value <= Z) os << char('A' + (value - A));
  else if (F1 <= value && value <= F12) os << "F" << 1 + value - F1;
  else os << "WTF";
  return os;
}

Event::Event (const Type& type, const Value& value, const int& x, const int& y)
  : m_type (type), m_value (value), m_x (x), m_y (y)
{ }

const Event::Type& Event::type() const
{
  return m_type;
}

const Event::Value& Event::value() const
{
  return m_value;
}

const int& Event::x() const
{
  return m_x;
}

const int& Event::y() const
{
  return m_y;
}

bool Event::operator< (const Event& other) const
{
  if (m_type == other.m_type)
    return m_value < other.m_value;
  return m_type < other.m_type;
}

bool Event::operator== (const Event& other) const
{
  return (m_type == other.m_type &&
          m_value == other.m_value);
}

Event::operator bool() const
{
  return (m_type != EMPTY);
}

std::string Event::to_string() const
{
  std::ostringstream oss;
  oss << *this;
  return oss.str();
}

} // namespace Sosage
