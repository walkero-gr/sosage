/*
  [include/Sosage/System/File_IO.h]
  Reads levels/savegames/configs, writes savegames/config.

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

#ifndef SOSAGE_SYSTEM_FILE_IO_H
#define SOSAGE_SYSTEM_FILE_IO_H

#include <Sosage/Component/Action.h>
#include <Sosage/Component/Font.h>
#include <Sosage/Component/Image.h>
#include <Sosage/Config/config.h>
#include <Sosage/Content.h>
#include <Sosage/Core/Parser.h>
#include <Sosage/System/Base.h>

#include <unordered_set>

namespace Sosage::System
{

class File_IO : public Base
{
private:

  using Function = std::function<void(const std::string&, const Core::Parser::Node&)>;
  std::unordered_map<std::string, Function> m_dispatcher;

public:

  File_IO (Content& content);

  virtual void run();

  void clean_content();

  void read_config();
  void write_config();

  void read_init ();
  void read_locale ();

  bool read_savefile(const std::string& save_id);
  void write_savefile();

private:

  void read_init_general (const Core::Parser& input);
  void read_init_achievement (const Core::Parser& input);
  void read_init_cursor (const Core::Parser& input);
  void read_init_inventory (const Core::Parser& input);
  void read_init_interface (const Core::Parser& input);
  void read_init_functions (const Core::Parser& input);
  void read_init_global_items (const Core::Parser& input);
  void read_init_text_defaults (const Core::Parser& input);

  void read_savefiles (const Core::Parser& input);

  void parse_function (const std::vector<std::string>& args,
                       Component::Action_handle action);
  void create_locale_dependent_text (const std::string& id, Component::Font_handle font,
                                     const std::string& color, const std::string& text, int z);
  Component::Handle load_locale_dependent_image (const std::string& entity,
                                                 const std::string& component,
                                    const std::string& filename,
                                    const std::function<Component::Image_handle(std::string)>& func,
                                                 bool insert_to_data = true);

  // Implemented in File_IO__read_room.cpp:
  void read_room (const std::string& file_name);

  void read_action (const std::string& id, const Core::Parser::Node& input);
  void read_animation (const std::string& id, const Core::Parser::Node& input);
  void read_character (const std::string& id, const Core::Parser::Node& input);
  void read_character_skin (const std::string& id, const Core::Parser::Node& input,
                            const std::string& default_state);
  void read_code (const std::string& id, const Core::Parser::Node& input);
  void read_dialog (const std::string& id, const Core::Parser::Node& input);
  void read_integer (const std::string& id, const Core::Parser::Node& input);
  void read_music (const std::string& id, const Core::Parser::Node& input);
  void read_object (const std::string& id, const Core::Parser::Node& input);
  std::pair<Component::Handle, Component::Handle>
  read_object_action (const std::string& id, const std::string& action,
                      const Core::Parser::Node& input);
  void read_scenery (const std::string& id, const Core::Parser::Node& input);
  void read_sound (const std::string& id, const Core::Parser::Node& input);
  void read_text (const std::string& id, const Core::Parser::Node& input);
  void read_window (const std::string& id, const Core::Parser::Node& input);

};

} // namespace Sosage::System

#endif // SOSAGE_SYSTEM_FILE_IO_H
