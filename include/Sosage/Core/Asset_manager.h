/*
  [include/Sosage/Core/Asset_manager.h]
  Select packaged or unpackaged assets.

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

#ifndef SOSAGE_CORE_ASSET_MANAGER_H
#define SOSAGE_CORE_ASSET_MANAGER_H

#ifdef SOSAGE_PACKAGED
#include <Sosage/Utils/Packaged_asset_manager.h>
#else
#include <Sosage/Utils/Unpackaged_asset_manager.h>
#endif

namespace Sosage
{
#ifdef SOSAGE_PACKAGED
using Asset = Packaged_asset;
using Asset_manager = Packaged_asset_manager;
#else
using Asset = Unpackaged_asset;
using Asset_manager = Unpackaged_asset_manager;
#endif
}

#endif // SOSAGE_CORE_ASSET_MANAGER_H
