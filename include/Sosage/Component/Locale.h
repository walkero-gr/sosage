/*
  [include/Sosage/Component/Locale.h]
  Handle translations of text.

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

#ifndef SOSAGE_COMPONENT_LOCALE_H
#define SOSAGE_COMPONENT_LOCALE_H

#include <Sosage/Component/Base.h>

#include <unordered_map>

namespace Sosage::Component
{

class Locale : public Base
{
  using Dictionary = std::unordered_map<std::string, std::string>;
  Dictionary m_dict;

public:

  Locale (const std::string& entity, const std::string& component);
  void add (const std::string& line, const std::string& translation);
  const std::string& get (const std::string& line);

  STR_NAME("Locale");
};

using Locale_handle = std::shared_ptr<Locale>;

} // namespace Sosage::Component

#endif // SOSAGE_COMPONENT_LOCALE_H
