/*
  [include/Sosage/Component/Status.h]
  The game current status (and pending ones).

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

#ifndef SOSAGE_COMPONENT_STATUS_H
#define SOSAGE_COMPONENT_STATUS_H

#include <Sosage/Component/Base.h>
#include <Sosage/Utils/enum.h>

#include <stack>

namespace Sosage::Component
{

class Status : public Value<Sosage::Status>
{
private:

  using Base = Value<Sosage::Status>;
  mutable std::stack<Sosage::Status> m_value;
  
public:

  Status (const std::string& entity, const std::string& component);
  void reset();
  void push (const Sosage::Status& v);
  void pop();
  virtual Sosage::Status value() const;
  Sosage::Status next_value() const;
  bool is (const Sosage::Status& s);
  bool is (const Sosage::Status& s1, const Sosage::Status& s2);
  bool is (const Sosage::Status& s1, const Sosage::Status& s2, const Sosage::Status& s3);
  bool was (const Sosage::Status& s);

  STR_NAME("Status");
  STR_VALUE([&]()
            {
              auto copy = m_value;
              std::string out = "";
              while (!copy.empty())
              {
                Sosage::Status s = copy.top();
                copy.pop();
                if (s == IDLE) out += " idle";
                else if (s == CUTSCENE) out += " cutscene";
                else if (s == PAUSED) out += " pause";
                else if (s == LOCKED) out += " locked";
                else if (s == ACTION_CHOICE) out += " action";
                else if (s == INVENTORY_ACTION_CHOICE) out += " inventory_action";
                else if (s == DIALOG_CHOICE) out += " dialog";
                else if (s == OBJECT_CHOICE) out += " object";
                else if (s == IN_INVENTORY) out += " in_inventory";
                else if (s == IN_MENU) out += " in_menu";
                else if (s == IN_WINDOW) out += " in_window";
                else if (s == IN_CODE) out += " in_code";
              }
              return out;
            }());

};

using Status_handle = std::shared_ptr<Status>;

} // namespace Sosage::Component

#endif // SOSAGE_COMPONENT_STATUS_H
