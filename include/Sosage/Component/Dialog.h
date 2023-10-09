/*
  [include/Sosage/Component/Dialog.h]
  A dialog stored as a graph.

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

#ifndef SOSAGE_COMPONENT_DIALOG_H
#define SOSAGE_COMPONENT_DIALOG_H

#include <Sosage/Component/Base.h>
#include <Sosage/Utils/graph.h>

namespace Sosage::Component
{

class Dialog : public Base
{
  struct Vertex
  {
    std::string character;
    std::string line;
    std::string signal;
  };

  struct Edge
  {
    std::string line;
    std::string condition;
    bool unless;
    bool displayed;
    bool enabled;
  };

  using Graph = Sosage::Graph<Vertex, Edge, true>;

public:

  using GVertex = typename Graph::Vertex;
  using GEdge = typename Graph::Edge;

private:

  Graph m_graph;
  GVertex m_vin;
  GVertex m_vout;
  GVertex m_current;

public:

  Dialog (const std::string& entity, const std::string& component, const std::string& end = "");
  GVertex add_vertex (const std::string& character = "",
                      const std::string& line = "",
                      const std::string& signal = "");
  GEdge add_edge (GVertex source, GVertex target, const std::string& line = "",
                  const std::string& condition = "", bool unless = false, bool displayed = true);
  bool has_incident_edges (GVertex v);
  GVertex current() const;
  GVertex vertex_in() const;
  GVertex vertex_out() const;
  void init(GVertex current = Graph::null_vertex());
  void next();
  std::string next (int choice);
  bool is_displayed (int choice);
  bool is_over() const;
  bool is_line() const;
  bool has_signal() const;
  std::pair<std::string, std::string> line() const;
  const std::string& signal() const;

  template <typename Container, typename Content>
  void get_choices (Container& choices, Content& content)
  {
    for (GEdge e : m_graph.incident_edges(m_current))
    {
      if (m_graph[e].condition != "")
      {
        std::string condition = (m_graph[e].condition == "said"
                                 ? entity() + std::to_string(std::size_t(e)) : m_graph[e].condition);
        m_graph[e].enabled = (content.signal(condition, "signal") != m_graph[e].unless);
      }

      if (!m_graph[e].enabled)
        continue;

      choices.push_back (m_graph[e].line);
    }
  }

  STR_NAME("Dialog");
};

using Dialog_handle = std::shared_ptr<Dialog>;

} // namespace Sosage::Component

#endif // SOSAGE_COMPONENT_DIALOG_H
