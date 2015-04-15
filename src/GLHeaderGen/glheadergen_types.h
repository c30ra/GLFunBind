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

#ifndef PARSERTYPES
#define PARSERTYPES

#include <QString>
#include <QMultiMap>

struct Types
{
  QString name; //the name oof the type
  QString requires;// the name of the type recquired
  QString api;// the api where it appear
  QString apientry;// the api where it appear
};

class Enum
{
public:
  Enum(){}

  QString group() const{return m_group;}
  void setGroup(const QString &group){m_group = group;}

  QString name() const{return m_name;}
  void setName(const QString &name){m_name = name;}

  QString value() const{return m_value;}
  void setValue(const QString &value){m_value = value;}

private:
  QString m_group;
  QString m_name;
  QString m_value;
};

class Function
{
public:
  Function(){}

  QString name() const{return m_name;}
  void setName(const QString &name){m_name = name;}

  QString returnType() const{return m_returnType;}
  void setReturnType(const QString &type){m_returnType = type;}

  class Param
  {
  public:
    Param(){}

    QString group() const{return m_group;}
    void setGroup(const QString &group){m_group = group;}

    QString name() const{return m_name;}
    void setName(const QString &name){m_name = name;}

    QString type() const{return m_type;}
    void setType(const QString &type){m_type = type;}

  private:
    QString m_group;
    QString m_type;
    QString m_name;
  };

  std::vector<std::shared_ptr<Param>> paramVector;

private:
  QString m_name;
  QString m_returnType;
};

struct BaseGL
{
  QMultiMap<QString, std::shared_ptr<Enum>> enumList;
  QMultiMap<QString, std::shared_ptr<Function>> commandList;
};

#endif // PARSERTYPES

