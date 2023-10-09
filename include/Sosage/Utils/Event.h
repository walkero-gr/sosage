/*
  [include/Sosage/Utils/Event.h]
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

#ifndef SOSAGE_UTILS_EVENT_H
#define SOSAGE_UTILS_EVENT_H

#include <Sosage/Utils/enum.h>

#include <iostream>

namespace Sosage
{

std::ostream& operator<< (std::ostream& os, const Event_type& type);
std::ostream& operator<< (std::ostream& os, const Event_value& value);

class Event
{
public:

  using Type = Event_type;
  using Value = Event_value;

private:

  Type m_type;
  Value m_value;
  int m_x;
  int m_y;

public:

  Event (const Type& type = EMPTY,
         const Value& value = NONE,
         const int& x = -1,
         const int& y = -1);
  const Type& type() const;
  const Value& value() const;
  const int& x() const;
  const int& y() const;
  bool operator< (const Event& other) const;
  bool operator== (const Event& other) const;
  operator bool() const;
  std::string to_string() const;
  friend std::ostream& operator<< (std::ostream& os, const Event& ev)
  {
    if (ev == Event())
    {
      os << "Event(null)";
      return os;
    }
    os << "Event(" << ev.type() << ", " << ev.value()
       << ", " << ev.x() << ", " << ev.y() << ")";
    return os;
  }

};

} // namespace Sosage

#endif // SOSAGE_UTILS_EVENT_H
