/*
  [include/Sosage/Component/Font.h]
  Font container for text generation.

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

#ifndef SOSAGE_COMPONENT_FONT_H
#define SOSAGE_COMPONENT_FONT_H

#include <Sosage/Component/Base.h>
#include <Sosage/Core/Graphic.h>

namespace Sosage::Component
{

class Font : public Base
{
private:
  Core::Graphic::Font m_core;
  
public:

  Font (const std::string& entity, const std::string& component, const std::string& file_name, int size);
  virtual ~Font();
  const Core::Graphic::Font& core() const;

  STR_NAME("Font");
};

using Font_handle = std::shared_ptr<Font>;

} // namespace Sosage::Component

#endif // SOSAGE_COMPONENT_FONT_H
