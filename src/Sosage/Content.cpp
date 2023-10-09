/*
  [src/Sosage/Content.cpp]
  Stores and handles access to all variable game content (components).

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

#include <Sosage/Content.h>

namespace Sosage
{

Content::Content()
  : m_data ()
#ifdef SOSAGE_LOG_CONTENT
  , m_log ("content.log")
#endif
{
  // For some components, we want to quickly access to the whole
  // list, so we separate them in specific Handle sets
  auto reserved_components
      = { "action",
          "animation",
          "end_notification",
          "gamepad",
          "group",
          "image",
          "label",
          "lookat",
          "move",
          "move60fps",
          "notification",
          "name",
          "path",
          "pause",
          "play_sound",
          "position",
          "rescale",
          "rescale60fps",
          "resume_at",
          "set_state",
          "set_visible",
          "set_hidden",
          "signal",
          "start_animation",
          "start_talking",
          "state",
          "stop_animation",
          "stop_talking",
          "stop_walking",
          "value" };

  m_data.resize(reserved_components.size() + 1);
  std::size_t idx = 1;
  for (const auto& c : reserved_components)
    m_map_component.insert (std::make_pair(c, idx ++));
}

Content::~Content()
{
  display_access();
}

void Content::clear()
{
  for (std::size_t i = 0; i < NUMBER_OF_KEYS; ++ i)
    m_fast_access_components[i] = nullptr;
  m_data.clear();
}

void Content::clear (const std::function<bool(Component::Handle)>& filter)
{
  for (auto& hmap : m_data)
  {
    Component::Handle_map& old_map = hmap;
    Component::Handle_map new_map;
    for (const auto& c : old_map)
      if (!filter(c.second))
        new_map.insert(c);
    old_map.swap (new_map);
  }
}

std::size_t Content::size() const
{
  return m_data.size();
}

Component::Component_map::const_iterator Content::begin() const
{
  return m_data.begin();
}

Component::Component_map::const_iterator Content::end() const
{
  return m_data.end();
}

Component::Handle_set Content::components (const std::string& s)
{
  return Component::Handle_set(handle_map(s));
}

bool Content::remove (const std::string& entity, const std::string& component, bool optional)
{
  Component::Handle_map& hmap = handle_map(component);
  Component::Handle_map::iterator iter = hmap.find(Component::Id(entity, component));
  if (optional && iter == hmap.end())
    return false;
  
  check (iter != hmap.end(), "Id " + entity + ":" + component + " doesn't exist");
  hmap.erase(iter);
  return true;
}

bool Content::remove (Component::Handle handle, bool optional)
{
  return remove (handle->entity(), handle->component(), optional);
}

void Content::emit (const std::string& entity, const std::string& component)
{
  set<Component::Signal>(entity, component);
}

bool Content::receive (const std::string& entity, const std::string& component)
{
  count_access(entity, component);
  count_request();

  Component::Handle_map& hmap = handle_map(component);

  Component::Handle_map::iterator iter = hmap.find(Component::Id(entity, component));
  if (iter == hmap.end())
    return false;
  if (!Component::cast<Component::Signal>(iter->second))
    return false;
  hmap.erase (iter);
  return true;
}

bool Content::signal (const std::string& entity, const std::string& component)
{
  return bool(request<Component::Signal>(entity, component));
}

Component::Handle_map& Content::handle_map (const std::string& s)
{
  auto iter = m_map_component.find(s);
  if (iter == m_map_component.end())
  {
    SOSAGE_COUNT (Content__components_default);
    return m_data[0];
  }
  SOSAGE_COUNT (Content__components_special);
  return m_data[iter->second];
}



void Content::count_set_ptr()
{
  SOSAGE_COUNT (Content__set_ptr);
}

void Content::count_set_args()
{
  SOSAGE_COUNT (Content__set_args);
}

void Content::count_request()
{
  SOSAGE_COUNT (Content__request);
}

void Content::count_get()
{
  SOSAGE_COUNT (Content__get);
}

#ifdef SOSAGE_PROFILE

void Content::count_access (const std::string& entity, const std::string& component)
{
  auto inserted = m_access_count.insert (std::make_pair (entity + ":" + component, 1));
  if (!inserted.second)
    inserted.first->second ++;
}

void Content::display_access()
{
  std::vector<std::pair<std::string, std::size_t> > sorted;
  sorted.reserve (m_access_count.size());
  std::copy (m_access_count.begin(), m_access_count.end(),
             std::back_inserter (sorted));
  auto end = std::partition
             (sorted.begin(), sorted.end(),
              [](const auto& p) -> bool { return isupper(p.first[0]); });
  std::sort (sorted.begin(), end,
             [](const auto& a, const auto& b) -> bool
             {
               return a.second > b.second;
             });
  debug << "[Profiling system component access count (25 first)]" << std::endl;
  for (std::size_t i = 0; i < 25; ++ i)
    debug << " * " << sorted[i].first << " (accessed "
          << sorted[i].second << " times)" << std::endl;
}

#else

void Content::count_access (const std::string&, const std::string&) { }
void Content::display_access () { }

#endif

} // namespace Sosage
