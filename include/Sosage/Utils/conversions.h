/*
  [include/Sosage/Utils/conversions.h]
  Convert strings to int, double, bool.

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

#ifndef SOSAGE_UTILS_CONVERSIONS_H
#define SOSAGE_UTILS_CONVERSIONS_H

#include <algorithm>
#include <string>
#include <vector>

namespace Sosage
{

bool is_int (const std::string& str);
bool is_relative (const std::string& str);
int to_int (const std::string& str);
double to_double (const std::string& str);
bool to_bool (const std::string& str);

template <typename T>
inline std::string to_string (const T& t)
{
  return std::to_string(t);
}

const std::string& to_string (const std::string& str);
std::string to_string (const char* str);
std::string to_string (const bool& t);

template <typename T, typename ... Ts>
inline std::string to_string (const T& t, const Ts& ... ts)
{
  return to_string(t) + to_string(std::forward<const Ts>(ts)...);
}

void capitalize(std::string& str);

template <typename Set, typename T>
bool contains (const Set& set, const T& t)
{
  return (set.find(t) != set.end());
}

template <typename T>
bool contains (const std::vector<T>& vec, const T& t)
{
  return std::find (vec.begin(), vec.end(), t) != vec.end();
}

bool contains (const std::initializer_list<const char*>& list, const std::string& str);
bool contains (const std::string& str, const char* sub);
bool contains (const std::string& str, const std::string& sub);
bool startswith (const std::string& str, const std::string& sub);
bool endswith (const std::string& str, const std::string& sub);

int random_int (int min, int max);
double random_double (double min = 0., double max = 1.);
bool random_chance(double chance);

template <typename T>
typename T::value_type random_choice (const T& list)
{
  double accu = 0.;
  double rnd = rand() / double(RAND_MAX);
  for (const auto& p : list)
  {
    accu += 1. / double(list.size());
    if (accu > rnd)
      return p;
  }
  return *(list.end() - 1);
}

template <typename T>
T random_choice (const std::initializer_list<T>& list)
{
  return random_choice<std::initializer_list<T>> (list);
}

void random_do (const std::initializer_list<std::function<void(void)>>& list);

} // namespace Sosage

#endif // SOSAGE_UTILS_CONVERSIONS_H
