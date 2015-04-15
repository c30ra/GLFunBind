/*******************************************************************************
GLFunBind type safe header only OpenGL function binder.
Copyright (C) 2015  Luca Carella

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/

#ifndef UTILS
#define UTILS

//GLHeaderGen
#include "glheadergen_types.h"

//System
#include <memory>

//Qt
#include <QString>
#include <QRegExp>

namespace GLHeaderGen
{
inline bool findOrphans(const std::vector<std::shared_ptr<Enum>> &vector,
                 const QString &value )
{
  for(auto &i : vector)
      if(i->name() == value)
        return true;
  return false;
}

//! convert to camel string containing "_"
QString toCamelCase(const QString &str)
{
  QRegExp rx("_[a-z]");    // primitive floating point matching
  int pos = 0;
  auto newStr = str;
  while ((pos = rx.indexIn(str, pos)) != -1)
    {
      auto replaceStr = rx.cap(0);
      auto tmp = replaceStr;
      auto replaceChar = replaceStr.at(1).toUpper();
      tmp.replace(replaceStr.at(1), replaceChar);
      newStr.replace(replaceStr, tmp);
      pos += rx.matchedLength();
    }
  return newStr;
}
}
#endif // UTILS

