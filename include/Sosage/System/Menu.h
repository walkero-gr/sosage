/*
  [include/Sosage/System/Menu.h]
  Handles menus.

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

#ifndef SOSAGE_SYSTEM_MENU_H
#define SOSAGE_SYSTEM_MENU_H

#include <Sosage/Component/Menu.h>
#include <Sosage/Content.h>
#include <Sosage/System/Base.h>
#include <Sosage/Utils/helpers.h>

namespace Sosage
{

namespace Config
{
constexpr_auto exit_menu_items
= {  "Phone", "Settings", "Controls", "New_game"
     #ifndef SOSAGE_EMSCRIPTEN
     , "Load", "Save"
     #endif
     #if !defined(SOSAGE_EMSCRIPTEN) && !defined(SOSAGE_PORT)
     , "Quit"
     #endif
  };
constexpr_auto settings_menu_items
= { "Language",
#if !defined (SOSAGE_ANDROID) && !defined(SOSAGE_EMSCRIPTEN) && !defined(SOSAGE_PORT)
    "Fullscreen",
#endif
    "Interface_scale", "Text_speed", "Music_volume", "Sound_volume" 
  };
constexpr_auto menus
= {  "Exit", "Phone", "Settings", "Controls"
     #ifndef SOSAGE_EMSCRIPTEN
     , "Load", "Save"
     #endif
  };

constexpr int menu_margin = 90;
constexpr int menu_small_margin = 35;
constexpr int menu_oknotok_y = 858;
constexpr int menu_ok_x = 120;
constexpr int menu_notok_x = 360;
constexpr int exit_menu_logo = 130;
constexpr int exit_menu_start = 220;
constexpr int exit_menu_text = menu_margin + 60;
constexpr int settings_menu_margin = 15;
constexpr int settings_menu_start = 135;
constexpr int settings_menu_height = 100;
constexpr int settings_menu_in_margin = 20;
constexpr int settings_menu_value_margin = 75;
constexpr int settings_menu_larrow_x = settings_menu_margin + 370;
constexpr int settings_menu_rarrow_x = settings_menu_margin + 420;
} // namespace Config

namespace System
{

class Menu : public Base
{
private:

  using Button_id = Component::Id;
  using Callback = std::function<void(const std::string& menu,
                                      const std::string& effect)>;
  std::unordered_map<Button_id, Callback, Component::Id_hash> m_callbacks;

public:

  Menu (Content& content);

  virtual void run();

  virtual void init();

private:

  void update_menu();
  void update_exit();
  void show_menu (const std::string& id);
  void hide_menu (const std::string& id);
  void delete_menu (const std::string& id);
  void menu_clicked ();
  void apply_setting (const std::string& setting, const std::string& value);
  void update_phone_menu();
  void update_end_menu();

  // Implemented in Menu__creation.cpp
  void init_menus();
  void init_loadsave_menus();
  void init_controls_menu();
  void create_callback (const std::string& menu, const std::string& button,
                        const Callback& callback);
  void make_oknotok_item (Component::Menu::Node node, bool only_ok);
  void make_exit_menu_item (Component::Menu::Node node, const std::string& id, int y);
  void make_text_menu_title (Component::Menu::Node node, const std::string& id);
  void make_text_menu_text (Component::Menu::Node node, const std::string& id);
  void make_settings_item (Component::Menu::Node node, const std::string& id, int y);

  std::pair<Component::Image_handle, Component::Position_handle>
  make_settings_button (const std::string& id, int y);
  std::pair<Component::Image_handle, Component::Position_handle>
  make_settings_title (const std::string& id, const std::string& suffix, int y,
                       const std::string& text);
  std::pair<Component::Image_handle, Component::Position_handle>
  make_settings_subtitle (const std::string& id, const std::string& suffix, int y,
                          const std::string& text);
};

} // namespace System

} // namespace Sosage

#endif // SOSAGE_SYSTEM_MENU_H
