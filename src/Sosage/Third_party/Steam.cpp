/*
  [src/Sosage/Third_party/Steam.cpp]
  Wrapper for Steam SDK.

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

#if !defined(__amigaos4__) && !defined(__morphos__)
#include <Sosage/Third_party/Steam.h>
#include <Sosage/Utils/error.h>

#ifdef SOSAGE_LINKED_WITH_STEAMSDK
#include <steam/steam_api.h>
#endif

namespace Sosage::Steam
{

bool achievement_init = false;

void init()
{
#ifdef SOSAGE_LINKED_WITH_STEAMSDK
  if (SteamAPI_RestartAppIfNecessary (SOSAGE_STEAM_APP_ID)) // Remplacez par votre AppID
    exit(1);
  bool success = SteamAPI_Init();
  check(success, "Couldn't init Steam SDK.");

  if (SteamUser()->BLoggedOn())
  {
    SteamUserStats()->RequestCurrentStats();
    achievement_init = true;
  }
#endif
}

void run()
{
#ifdef SOSAGE_LINKED_WITH_STEAMSDK
  SteamAPI_RunCallbacks();
#endif
}

std::string game_language()
{
#ifdef SOSAGE_LINKED_WITH_STEAMSDK
  return SteamApps()->GetCurrentGameLanguage();
#else
  return "";
#endif
}

bool set_achievement (const std::string& id)
{
#ifdef SOSAGE_LINKED_WITH_STEAMSDK
  if (achievement_init)
  {
    bool out = SteamUserStats()->SetAchievement(id.c_str());
    SteamUserStats()->StoreStats();
    return out;
  }
#endif
  return false;
}

void shutdown()
{
#ifdef SOSAGE_LINKED_WITH_STEAMSDK
  SteamAPI_Shutdown();
#endif
}

} // namespace Sosage
#endif