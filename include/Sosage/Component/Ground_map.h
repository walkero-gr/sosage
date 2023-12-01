/*
  [include/Sosage/Component/Ground_map.h]
  Ground limits, local depth and path finding.

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

#ifndef SOSAGE_COMPONENT_GROUND_MAP_H
#define SOSAGE_COMPONENT_GROUND_MAP_H

#include <Sosage/Component/Base.h>
#include <Sosage/Core/Graphic.h>
#include <Sosage/Utils/geometry.h>
#include <Sosage/Utils/graph.h>

#include <map>

namespace Sosage
{

namespace Config
{
constexpr double boundary_precision = 2.0;
} // namespace Config

namespace Component
{

class Ground_map : public Base
{
  struct Vertex
  {
    Point point;
    unsigned char red = 0;
    double dist = 0;
  };

  struct Edge
  {
    bool border = true;
  };

  using Graph = Sosage::Graph<Vertex, Edge, false>;
  using GVertex = typename Graph::Vertex;
  using GEdge = typename Graph::Edge;
  using Edge_condition = std::function<bool(const GEdge&)>;

  double deviation(GVertex v) const;

  struct Neighbor_query
  {
    GVertex vertex = Graph::null_vertex();
    GEdge edge = Graph::null_edge();
    double dist = std::numeric_limits<double>::max();
    Point point;
    operator bool() const;
  };

  struct Compare_ordered_pair
  {
    template <typename Pair>
    Pair ordered (const Pair& p) const
    {
      if (p.first > p.second)
        return Pair(p.second, p.first);
      return p;
    }
    template <typename Pair>
    bool operator() (const Pair& a, const Pair& b) const
    {
      return ordered(a) < ordered(b);
    }
  };

  const double snapping_dist = 5.;
  Core::Graphic::Surface m_image;
  int m_radius;
  int m_front_z;
  int m_back_z;
  Graph m_graph;
  Graph m_latest_graph;

  GVertex add_vertex (std::map<Point, GVertex>& map_p2v,
                      const Point& p, const unsigned char& red);
  void build_graph (const std::function<void()>& callback);

public:

  Ground_map (const std::string& entity, const std::string& component,
              const std::string& file_name, int front_z, int back_z,
              const std::function<void()>& callback);
#ifdef SOSAGE_SCAP
  void write (const std::string& filename);
#endif
#ifdef SOSAGE_PACKAGED
  void read (const std::string& filename);
#endif

  template <typename Functor>
  void for_each_vertex (const Functor& functor) const
  {
    for (GVertex v : m_latest_graph.vertices())
      functor (m_latest_graph[v].point);
  }

  template <typename Functor>
  void for_each_edge (const Functor& functor) const
  {
    for (GEdge e : m_latest_graph.edges())
    {
      const Point& s = m_latest_graph[m_latest_graph.source(e)].point;
      const Point& t = m_latest_graph[m_latest_graph.target(e)].point;
      functor (s, t, m_latest_graph[e].border);
    }
  }

  void find_path (Point origin, Point target, std::vector<Point>& out);
  void find_path (Point origin, Sosage::Vector direction, std::vector<Point>& out);
  double z_at_point (const Point& p) const;

  bool is_ground_point (const Point& p) const;
  Neighbor_query closest_simplex (const Point& p) const;

  void shortest_path (GVertex vorigin, GVertex vtarget,
                      std::vector<Point>& out);

  bool intersects_border (const Graph& g,
                          const Segment& seg,
                          const Edge_condition& condition) const;

  Neighbor_query closest_intersected_edge (const Point& p, const Sosage::Vector& direction,
                                           const Edge_condition& condition) const;

  STR_NAME("Ground_map");
};

using Ground_map_handle = std::shared_ptr<Ground_map>;

} // namespace Component

} // namespace Sosage

#endif // SOSAGE_COMPONENT_GROUND_MAP_H
