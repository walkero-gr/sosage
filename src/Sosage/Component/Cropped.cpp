/*
  [src/Sosage/Component/Cropped.cpp]
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

#include <Sosage/Component/Cropped.h>
#include <Sosage/Core/Graphic.h>

namespace Sosage::Component
{

Cropped::Cropped (const std::string& entity, const std::string& component, const std::string& file_name, int z)
  : Image(entity, component, file_name, z)
  , m_xmin (0)
  , m_xmax (Core::Graphic::width(core()))
  , m_ymin (0)
  , m_ymax (Core::Graphic::height(core()))
{
}

void Cropped::crop (int xmin, int xmax, int ymin, int ymax)
{
  m_xmin = xmin;
  m_xmax = xmax;
  m_ymin = ymin;
  m_ymax = ymax;
}

int Cropped::xmin() const
{
  return m_xmin;
}

int Cropped::xmax() const
{
  return m_xmax;
}

int Cropped::ymin() const
{
  return m_ymin;
}

int Cropped::ymax() const
{
  return m_ymax;
}

} // namespace Sosage::Component
