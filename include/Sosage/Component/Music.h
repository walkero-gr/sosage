/*
  [include/Sosage/Component/Music.h]
  Background music played in loop.

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

#ifndef SOSAGE_COMPONENT_MUSIC_H
#define SOSAGE_COMPONENT_MUSIC_H

#include <Sosage/Component/Base.h>
#include <Sosage/Core/Sound.h>
#include <Sosage/Utils/geometry.h>

#include <unordered_map>
#include <vector>

namespace Sosage::Component
{

class Music : public Base
{
public:
  enum Source_status { FADING_IN, ON, FADING_OUT, OFF };

private:

  struct Source
  {
    Point position = Point::invalid();
    double small_radius = 0;
    double big_radius = 0;
    std::vector<double> mix;
    double fade_origin = 0.;
    double fade_duration = 0.;
    double fade_strength = 0.;
    Source_status status = ON;
  };

  std::vector<Core::Sound::Music> m_core;
  std::vector<double> m_mix;
  std::unordered_map<std::string, Source> m_sources;
  bool m_on;
  
public:

  Music (const std::string& entity, const std::string& component);
  virtual ~Music();
  void init();
  void add_track (const std::string& file_name);
  void add_source (const std::string& id, const std::vector<double>& mix,
                   double x = 0, double y = 0,
                   double small_radius = 0, double big_radius = 0);
  bool adjust_mix (const Point& position, const double& time);
  std::size_t tracks() const;
  const Core::Sound::Music& core (std::size_t i) const;
  double mix (std::size_t i) const;
  const bool& on() const;
  bool& on();
  void disable_source (const std::string& id, double time, double duration);
  void enable_source (const std::string& id, double time, double duration);
  const std::unordered_map<std::string, Source>& sources() const;

  STR_NAME("Music");
};

using Music_handle = std::shared_ptr<Music>;

} // namespace Sosage::Component

#endif // SOSAGE_COMPONENT_MUSIC_H
