/*
  [include/Sosage/Component/Cropped.h]
  Specialization of Image for cropped objects.

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

#ifndef SOSAGE_COMPONENT_CROPPED_H
#define SOSAGE_COMPONENT_CROPPED_H

#include <Sosage/Component/Image.h>

namespace Sosage::Component
{

class Cropped : public Image
{
public:

  int m_xmin;
  int m_xmax;
  int m_ymin;
  int m_ymax;

public:

  Cropped (const std::string& entity, const std::string& component, const std::string& file_name, int z);
  void crop (int xmin, int xmax, int ymin, int ymax);
  virtual int xmin() const;
  virtual int xmax() const;
  virtual int ymin() const;
  virtual int ymax() const;

  STR_NAME("Cropped");
};

using Cropped_handle = std::shared_ptr<Cropped>;

} // namespace Sosage::Component

#endif // SOSAGE_COMPONENT_CROPPED_H
