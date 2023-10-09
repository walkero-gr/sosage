/*
  [include/Sosage/Component/Action.h]
  The effects of a user-selected verb action ("open", "use", etc.).

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

#ifndef SOSAGE_COMPONENT_ACTION_H
#define SOSAGE_COMPONENT_ACTION_H

#include <Sosage/Component/Base.h>

#include <functional>
#include <set>
#include <vector>

namespace Sosage::Component
{

class Action : public Base
{
public:

  class Step
  {
  private:

    std::string m_function;
    std::vector<std::string> m_args;

  public:

    Step (const std::string& function, const std::vector<std::string>& args);
    const std::string& function() const;
    const std::vector<std::string>& args() const;
    std::string to_string() const;
  };

  using Timed_handle = std::pair<double, Handle>;

private:

  std::vector<Step> m_steps;
  std::set<Timed_handle> m_timed;
  std::size_t m_next_step;
  bool m_on;
  bool m_still_waiting; // for this world to stop hating

public:

  Action (const std::string& entity, const std::string& component);
  void clear();
  void add (const std::string& function, const std::vector<std::string>& args);
  void launch();
  void stop();
  bool on() const;
  std::size_t size() const;
  std::vector<Step>::const_iterator begin() const;
  std::vector<Step>::const_iterator end() const;
  const std::set<Timed_handle>& scheduled() const;
  void schedule (double time, Handle h);
  void reset_scheduled ();
  void update_scheduled (const std::function<bool(Timed_handle)>& predicate);
  bool ready() const;
  const Step& next_step();
  const Step& first_step();
  const Step& last_step();

  STR_NAME("Action");

  std::string str_value() const override
  {
    std::string out = "";
    for (const Step& s : m_steps)
      out += "\n * " + s.to_string();
    return out;
  }
};

using Action_handle = std::shared_ptr<Action>;

} // namespace Sosage::Component

#endif // SOSAGE_COMPONENT_ACTION_H
