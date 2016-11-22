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

#ifndef GLHeaderGen_H
#define GLHeaderGen_H

//Qt
#include <QObject>
#include <QString>
#include <QDir>
#include <QMultiMap>

//tinyxml2
#include <tinyxml2.h>

//system
#include <memory>

//GLHeaderGen
#include "gltree.h"
#include "glheadergen_types.h"

class QTextStream;
namespace GLHeaderGen
{
  class Parser : public QObject
  {
    Q_OBJECT
  public:
    explicit Parser(QObject *parent = 0);
    ~Parser();

    void setUseEnumClass(bool useEnumClass);
    void setUseDefines(bool useDefines);

  public:
    //  void read(QIODevice *device);
    void read(const char *buffer);//dom version
    void write(const QString &where);
  private://options
    bool m_useEnumClass;
    bool m_useDefines;

  private:
    void processGroups(tinyxml2::XMLElement *element);
    void processEnums(tinyxml2::XMLElement *element);
    void processCommands(tinyxml2::XMLElement *element);

    void resolveData(tinyxml2::XMLElement *feature);

    void outputEnumUndefs(const QString &where);
    void outputEnumsHeaders(const QString &where);
    void outputEnumsClassHeaders(const QString &where);
    void outputFunctionsHeaders(const QString &where);
    void outputGLHeaders(const QString &where);
    void outputBindingsHeaders(const QString &where);

  private:
    GLHeaderGen::GLTree<BaseGL> glTree;
    std::vector<std::shared_ptr<Enum>> enumList;
    std::vector<std::shared_ptr<Function>> functionList;

  };
}
#endif // GLHeaderGen_H
