/*
  [include/Sosage/System/Graphic.h]
  Renders the content of the game at each frame.

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

#ifndef SOSAGE_SYSTEM_GRAPHIC_H
#define SOSAGE_SYSTEM_GRAPHIC_H

#include <Sosage/Component/Image.h>
#include <Sosage/Core/Graphic.h>
#include <Sosage/Content.h>
#include <Sosage/System/Base.h>
#include <Sosage/Utils/Clock.h>

#include <vector>

namespace Sosage::System
{

class Graphic : public Base
{
private:

  Core::Graphic m_core;
  Clock m_clock;
  double m_start;
  double m_loop;

public:

  Graphic (Content& content);

  virtual void init();

  virtual void run();

  void run_loading();

  void display_error (const std::string& error) { m_core.display_error(error); }

};

} // namespace Sosage::System

#endif // SOSAGE_SYSTEM_GRAPHIC_H
