/*
  [src/Sosage/Utils/conversions.cpp]
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

#include <Sosage/Utils/conversions.h>

namespace Sosage
{

bool is_int (const std::string& str)
{
  for (const char& c : str)
    if (!std::isdigit(c))
      return false;
  return true;
}

bool is_relative (const std::string& str)
{
  return str[0] == '+' || str[0] == '-';
}

int to_int (const std::string& str)
{
  return std::atoi (str.c_str());
}

double to_double (const std::string& str)
{
  return std::atof (str.c_str());
}

bool  to_bool (const std::string& str)
{
  return (str == "true");
}

const std::string& to_string (const std::string& str)
{
  return str;
}

std::string to_string (const char* str)
{
  return std::string(str);
}

std::string to_string (const bool& t)
{
  return (t ? "true" : "false");
}

void capitalize (std::string& str)
{
  if (startswith(str, "é"))
  {
    str = "É" + std::string(str.begin() + std::string("é").size(), str.end());
  }
  else
    str[0] = toupper(str[0]);
}

bool contains (const std::initializer_list<const char*>& list, const std::string& str)
{
  for (const char* s : list)
    if (std::string(s) == str)
      return true;
  return false;
}

bool contains (const std::string& str, const char* sub)
{
  return str.find(sub) != std::string::npos;
}

bool contains (const std::string& str, const std::string& sub)
{
  return str.find(sub) != std::string::npos;
}

bool startswith (const std::string& str, const std::string& sub)
{
  if (str.size() < sub.size())
    return false;
  return (str.compare (0, sub.size(), sub) == 0);
}

bool endswith (const std::string& str, const std::string& sub)
{
  if (str.size() < sub.size())
    return false;
  return (str.compare (str.size() - sub.size(), sub.size(), sub) == 0);
}

int random_int (int min, int max)
{
  return min + (rand() % (max - min));
}

double random_double (double min, double max)
{
  return min + (max - min) * (rand() / double(RAND_MAX));
}

bool random_chance (double chance)
{
  return (rand() / double(RAND_MAX)) < chance;
}

void random_do (const std::initializer_list<std::function<void(void)>>& list)
{
  random_choice(list)();
}

} // namespace Sosage
