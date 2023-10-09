/*
  [include/Sosage/Component/Code.h]
  Code-based enigmas.

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

#ifndef SOSAGE_COMPONENT_CODE_H
#define SOSAGE_COMPONENT_CODE_H

#include <Sosage/Component/Base.h>

#include <vector>

namespace Sosage::Component
{

class Code : public Base
{

  struct Button
  {
    std::string value;
    int x;
    int y;
    int w;
    int h;
    std::size_t x_index = 0;
    std::size_t y_index = 0;
  };

  std::vector<Button> m_buttons;
  std::vector<std::string> m_answer;
  std::vector<std::size_t> m_proposal;
  std::size_t m_hover;
  std::vector<std::vector<std::size_t>> m_indices;
  
public:

  Code (const std::string& entity, const std::string& component);
  void add_button (const std::string& value, int x, int y, int w, int h);
  void add_answer_item (const std::string& value);
  bool hover (int x = -1, int y = -1);
  void move (double x, double y);
  bool click (int x = -1, int y = -1);
  void reset();
  bool failure();
  bool success();
  int xmin();
  int xmax();
  int ymin();
  int ymax();

  STR_NAME("Code");
};

using Code_handle = std::shared_ptr<Code>;

} // namespace Sosage::Component

#endif // SOSAGE_COMPONENT_CODE_H
