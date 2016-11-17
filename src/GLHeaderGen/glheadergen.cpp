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
// GLHeaderGen
#include "glheadergen.h"
#include "orphanenums.h"
#include "utils.h"

//Qt
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>

using namespace GLHeaderGen;

static const char *registryTag{"registry"};
static const char *commentTag{"comment"};
static const char *typesTag{"types"};
static const char *groupsTag{"groups"};
static const char *enumsTag{"enums"};
static const char *commandsTag{"commands"};
static const char *featureTag{"feature"};
static const char *extensionsTag{"extensions"};

static const QString license
{
  "/*************************************************************************\n"
  "GLHeaderGen type safe header only OpenGL function binder.\n"
  "Copyright (C) 2015  Luca Carella\n"

  "This program is free software: you can redistribute it and/or modify\n"
  "it under the terms of the GNU General Public License as published by\n"
  "the Free Software Foundation, either version 3 of the License, or\n"
  "(at your option) any later version.\n"
  "\n"
  "This program is distributed in the hope that it will be useful,\n"
  "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
  "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
  "GNU General Public License for more details.\n"
  "\n"
  "You should have received a copy of the GNU General Public License\n"
  "along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"
  "*************************************************************************/\n"
};

static const QString tab = "  ";

Parser::Parser(QObject *parent)
  : QObject(parent),
    m_useEnumClass{false},
    m_useDefines{false}
{

}

Parser::~Parser()
{
}

void Parser::read(const char *buffer)
{
  tinyxml2::XMLDocument document;
  if(document.Parse(buffer) != tinyxml2::XMLError::XML_SUCCESS)
    qFatal("Error opening the file: ", document.GetErrorStr1());


  qDebug() << "Processing enum groups..";
  auto *element = document.FirstChildElement()->FirstChildElement(groupsTag);
  processGroups(element);

  qDebug() << "Processing enum values..";
  element = document.FirstChildElement()->FirstChildElement(enumsTag);
  processEnums(element);

  qDebug() << "Processing commands..";
  element = document.FirstChildElement()->FirstChildElement(commandsTag);
  processCommands(element);

  qDebug() << "Resolving data..";
  element = document.FirstChildElement()->FirstChildElement(featureTag);
  resolveData(element);

  qDebug() << "Writing enums header..";
  if(!m_useEnumClass)
    outputEnumsHeaders();
  else
    outputEnumsClassHeaders();

  qDebug() << "Writing functions header..";
  outputFunctionsHeaders();

  qDebug() << "Writing gl header..";
  outputGLHeaders();

  qDebug() << "Writing binds.h ..";
  outputBindingsHeaders();

  qDebug() << "Writing enum_undefs.h ..";
  outputEnumUndefs();

  qDebug() << "Done!";

}

void Parser::setUseEnumClass(bool useEnumClass)
{
  m_useEnumClass = useEnumClass;
}

void Parser::setUseDefines(bool useDefines)
{
  m_useDefines = useDefines;
}


void Parser::processGroups(tinyxml2::XMLElement *element)
{
  //Tag
  static const char *groupTag{"group"};
  static const char *enumTag{"enum"};

  //Attribute
  static const char *nameAttribute{"name"};

  auto groupChild = element->FirstChildElement(groupTag);
  while(groupChild != nullptr)
    {
      const char *groupAttrib = groupChild->Attribute(nameAttribute);
      //      if(groupAttrib)
      //        continue;
      auto enumChild = groupChild->FirstChildElement(enumTag);
      //      QVector<Enums> group;
      while(enumChild != nullptr)
        {
          const char *enumName = enumChild->Attribute(nameAttribute);
          if(enumName)
            {
              Enum enumData;
              enumData.setGroup(groupAttrib);
              enumData.setName(enumName);
              enumList.push_back(std::make_shared<Enum>(enumData));
            }
          enumChild = enumChild->NextSiblingElement(enumTag);
        }
      groupChild = groupChild->NextSiblingElement(groupTag);
    }
}

void Parser::processEnums(tinyxml2::XMLElement *element)
{
  //Tag
  static const char *enumTag{"enum"};

  //Attribute
  static const char *nameAttribute{"name"};
  static const char *valueAttribute{"value"};
  static const char *groupAttribute{"group"};

  QStringList orphans;
  std::vector<std::shared_ptr<Enum>> orphansVec;
  while(element != nullptr)
    {
      auto child = element->FirstChildElement(enumTag);
      const char *groupAttributeValue = element->Attribute(groupAttribute);

      while(child != nullptr)
        {
          auto *name = child->Attribute(nameAttribute);
          auto *value = child->Attribute(valueAttribute);
          if(name && value)
            {
              if(!findOrphans(enumList, name)) // trying to group ungrouped enus
                {
                  Enum enumData;
                  enumData.setName(name);
                  enumData.setValue(value);//Warning: name collision with gl.h

                  if(groupAttributeValue)
                    {
                      enumData.setGroup(groupAttributeValue);
                      orphansVec.push_back(std::make_unique<Enum>(enumData));
                    }
                  else // still ungrouped...
                    {
                      auto result = orphanEnums.find(name); //use "predefined" group

                      if(result==orphanEnums.end()) //still not found
                        {
                          enumData.setGroup("Ungrouped");
                          orphansVec.push_back(std::make_unique<Enum>(enumData));
                        }
                      else // found something
                        {
                          enumData.setGroup(result.value());
                          orphansVec.push_back(std::make_unique<Enum>(enumData));
                        }
                    }
                }
              for(auto &item : enumList)
                if(item->name() == name)
                  item->setValue(value); //Warning: name collision with gl.h
            }
          child = child->NextSiblingElement(enumTag);
        }
      element = element->NextSiblingElement(enumsTag);
    }

  for(auto &v : orphansVec)
    enumList.push_back(v);

#if 0
#ifdef DEBUG
    for(auto &v : enumList)
      if(v->group()== "Ungrouped")
        orphans << v->name();

    QFile file("orphans.txt");
    if(!file.open(QIODevice::WriteOnly| QIODevice::Truncate))
      qFatal(file.errorString().toStdString().c_str());
    QTextStream m_enumsOut{&file};
    orphans.removeDuplicates();
    orphans.sort();
    for(auto &value : orphans)
      m_enumsOut << value << endl;
    file.close();
#endif
#endif
  //  QFile file2("enums.txt");
  //  if(!file2.open(QIODevice::WriteOnly| QIODevice::Truncate))
  //    qFatal(file2.errorString().toStdString().c_str());
  //  QTextStream m_enumsOut2{&file2};
  //  for(auto &value : enumList)
  //    m_enumsOut2 << value->name << endl;
  //  file2.close();
}

void Parser::processCommands(tinyxml2::XMLElement *element)
{
  //Tag
  static const char *commandTag{"command"};
  static const char *protoTag{"proto"};
  static const char *nameTag{"name"};
  static const char *paramTag{"param"};
//  static const char *ptypeTag{"ptype"};

  //Attribute
  static const char *groupAttribute{"group"};

  auto commandChild = element->FirstChildElement(commandTag);
  while(commandChild != nullptr)
    {
      Function glFunction;
      std::vector<std::shared_ptr<Function::Param>> paramList;

      auto protoChild = commandChild->FirstChildElement(protoTag);
      auto protoReturnChild = protoChild->FirstChild();
      auto functioName = "";
      auto returnType = QString{};

      while(protoReturnChild)
        {
          auto textNode = protoReturnChild->ToText();
          if(textNode)
            returnType += QString{textNode->Value()}.trimmed();
          else
            {
              auto element = protoReturnChild->ToElement();
              if(strcmp(element->Value(), nameTag) != 0)
                returnType += QString{element->GetText()}.trimmed();
              else
                functioName = element->GetText();
            }

          protoReturnChild = protoReturnChild->NextSibling();

          if(protoReturnChild && !returnType.endsWith("*") ) //add space until last node
            returnType += " ";
        }
//      if(returnType.isEmpty() && paramTypeChild)
//        {
//          returnType = paramTypeChild->GetText();
//          returnType += " "; //Note: add extra space, because text don't have it
//        }
//      else if(paramTypeChild) //some proto also have ptype child instead of text..
//        returnType += paramTypeChild->GetText();

      auto paramChild = commandChild->FirstChildElement(paramTag);
      auto paramName = QString{};

      while(paramChild != nullptr)
        {
          Function::Param functionParam;         
          auto paramTypeChild = paramChild->FirstChild();
          auto paramType = QString{};
          while(paramTypeChild)
            {
              auto textNode = paramTypeChild->ToText();
              if(textNode)
                paramType += QString{textNode->Value()}.trimmed();
              else
                {
                  auto element = paramTypeChild->ToElement();
                  if(strcmp(element->Value(), nameTag) != 0)
                    paramType += QString{element->GetText()}.trimmed();
                  else
                    paramName = element->GetText();
                }

              paramTypeChild = paramTypeChild->NextSibling();

              if(paramTypeChild && !paramType.endsWith("*") ) //add space until last node
                paramType += " ";
            }


          auto paramGroup = "";
          if(!m_useEnumClass)
            {
              if(!paramType.isEmpty() && (paramType == "GLenum"))
                {
                  paramGroup = paramChild->Attribute(groupAttribute);
                  if(!paramGroup)
                    paramGroup = "Ungrouped";
                }
            }
          if(paramName == "far" || paramName == "near")
            paramName.prepend("_");

          functionParam.setGroup(paramGroup);
          functionParam.setName(paramName);
          functionParam.setType(paramType);

          paramList.push_back(std::make_unique<Function::Param>(functionParam));
          paramChild = paramChild->NextSiblingElement(paramTag);
        }
      glFunction.paramVector = paramList;
      glFunction.setName(functioName);
      glFunction.setReturnType(returnType);

      functionList.push_back(std::make_unique<Function>(glFunction));

      commandChild = commandChild->NextSiblingElement(commandTag);
    }
}

void Parser::resolveData(tinyxml2::XMLElement *feature)
{
  //Tag
  static const char *featureTag{"feature"};
  static const char *requireTag{"require"};
  static const char *removeTag{"remove"};
//  static const char *typeTag{"type"};
  static const char *commandTag{"command"};
  static const char *enumTag{"enum"};

  //Attribute
  static const char *commentAttribute{"comment"};
  static const char *apiAttribute{"api"};
  static const char *numberAttribute{"number"};
  static const char *nameAttribute{"name"};
  static const char *profileAttribute{"profile"};

  QMultiMap<QString, std::shared_ptr<Enum>> enumListCompatibility;
  QMultiMap<QString, std::shared_ptr<Enum>> enumListCore;
  QMultiMap<QString, std::shared_ptr<Function>> commandListCompatibility;
  QMultiMap<QString, std::shared_ptr<Function>> commandListCore;

  while(feature != nullptr)
    {
      const char *api  = feature->Attribute(apiAttribute);
      const char *name  = feature->Attribute(nameAttribute);

      float number;
      feature->QueryFloatAttribute(numberAttribute, &number);

      if(name && std::strcmp(name, "GL_VERSION_1_0") == 0)
        name = "GL_VERSION_1_1";

      auto apiNode = glTree.addNode(api);
      auto versionNode = apiNode->addNode(name);

      auto requireElement = feature->FirstChildElement(requireTag);
      auto removeElement = feature->FirstChildElement(removeTag);

      auto requireAttributeValue = requireElement->Attribute(profileAttribute);
      auto removeAttributeValue = "";
      if(removeElement)
        removeAttributeValue = removeElement->Attribute(profileAttribute);

      if(!requireAttributeValue){
          if(number > 3.1)
            {
              requireAttributeValue = "compatibility";
              if((qstrcmp(removeAttributeValue, "")== 0) && (!removeElement))
                removeAttributeValue = "core";
            }
          else
            requireAttributeValue = "";
        }
      auto profileNode = versionNode->addNode(requireAttributeValue);

      auto removeNode = strcmp(removeAttributeValue,"") == 0 ? 0 : versionNode->addNode(removeAttributeValue);
      if(!removeElement && number > 3.1)
        removeNode->setData(std::make_unique<BaseGL>(BaseGL{enumListCore, commandListCore}));

      while(requireElement != nullptr)
        {
          auto enumElement = requireElement->FirstChildElement(enumTag);
          auto commandElement = requireElement->FirstChildElement(commandTag);

          auto requireCommentValue = requireElement->Attribute(commentAttribute);
          Q_UNUSED(requireCommentValue);

          while(enumElement != nullptr)
            {
              auto enumName = enumElement->Attribute(nameAttribute);
              if(nameAttribute)
                {
                  for(auto &item : this->enumList)
                    {
                      if(enumName == item->name())
                        {
//                          if(item->group == "Ungrouped") // lot of ungrouped enums...
//                            {
//                              if(requireCommentValue) //no comment
//                                {
//                                  QRegExp exp("ARB_[a-zA-Z_]+");
//                                  QString str{requireCommentValue};
//                                  if(exp.indexIn(str) > -1)
//                                    {
//                                      auto groupName = exp.cap(0);
//                                      groupName.remove("ARB");
//                                      groupName = toCamelCase(groupName);
//                                      groupName.remove('_');
//                                           }
//                                }
//                            }
                          if(!m_useEnumClass)
                            {
                              enumListCompatibility.replace(item->name(), item);
                              enumListCore.replace(item->name(), item);
                            }
                          else
                            {
                              enumListCompatibility.insert(item->group(), item);
                              enumListCore.insert(item->group(), item);
                            }
                        }
                    }
                }
              enumElement = enumElement->NextSiblingElement(enumTag);
            }
          while(commandElement != nullptr)
            {
              auto commandName = commandElement->Attribute(nameAttribute);
              if(nameAttribute)
                {
                  for(auto &item : this->functionList)
                    {
                      if(commandName == item->name())
                        {
                            commandListCompatibility.replace(item->name(), item);
                            commandListCore.replace(item->name(), item);
                        }
                    }
                }
              commandElement = commandElement->NextSiblingElement(commandTag);
            }
          BaseGL glData;
          glData.commandList = commandListCompatibility;
          glData.enumList = enumListCompatibility;
          profileNode->setData(std::make_unique<BaseGL>(glData));
          requireElement = requireElement->NextSiblingElement(requireTag);
        }

//      if(enumListCore.isEmpty())
//        enumListCore = enumListCompatibility;
//      if(commandListCore.isEmpty())
//        commandListCore = commandListCompatibility;

      while(removeElement != nullptr)
        {
          auto enumElement = removeElement->FirstChildElement(enumTag);
          auto commandElement = removeElement->FirstChildElement(commandTag);
          while(enumElement != nullptr)
            {
              auto enumName = enumElement->Attribute(nameAttribute);
              if(nameAttribute)
                {
                  for(auto &item : this->enumList)
                    if(enumName == item->name())
                      {
                        if(!m_useEnumClass)
                          enumListCore.remove(item->name(), item);
                        else
                          enumListCore.remove(item->group(), item);
                      }

                }

              enumElement = enumElement->NextSiblingElement(enumTag);
            }

          while(commandElement != nullptr)
            {
              auto commandName = commandElement->Attribute(nameAttribute);
              if(nameAttribute)
                {
                  for(auto &item : this->functionList)
                    {
                      if(commandName == item->name())
                        {
                          commandListCore.remove(item->name(), item);
                        }
                    }
                }
              commandElement = commandElement->NextSiblingElement(commandTag);
            }
          BaseGL glData;
          glData.commandList = commandListCore;
          glData.enumList = enumListCore;

          removeNode->setData(std::make_unique<BaseGL>(glData));
          removeElement = removeElement->NextSiblingElement(removeTag);
        }
      feature = feature->NextSiblingElement(featureTag);
    }
}

void Parser::outputEnumUndefs()
{
  static const QString dir {"../include"};
  static const QString filePrefix {"enum_undefs"};
  static const QString fileExt {".h"};
  //  auto childs = glTree.childNodes();
  QDir outputDirectory{QDir::current()};
  if(!outputDirectory.mkdir(dir))
    if(!outputDirectory.exists(dir))
      qFatal("Colud not create directory:");

  auto dirName = dir + "/";
  if(!outputDirectory.mkdir(dirName))
    if(!outputDirectory.exists(dirName))
      qFatal("Colud not create directory: ");

  auto fileName = dir + '/' + filePrefix + fileExt;

  QFile file(fileName);
  if(!file.open(QIODevice::WriteOnly| QIODevice::Truncate))
    qFatal(file.errorString().toStdString().c_str());

  QTextStream enumUndefs_out{&file};
  enumUndefs_out << license;
  enumUndefs_out << "//! Place this file after any opengl include\n"
                    "//! if you have problem, example:\n"
                    "//! #include <gl.h> //\n"
                    "//! #include <enum_undefs.h>" << endl;

  enumUndefs_out << "#ifndef ENUM_UNDEFS" << endl;
  enumUndefs_out << "#define ENUM_UNDEFS" << endl;
  enumUndefs_out << "\n";
  enumUndefs_out << endl;

  for(auto &enumItem : enumList)
    {
      enumUndefs_out << "#undef " << enumItem->name() << endl;
    }

  enumUndefs_out << "#endif //ENUM_UNDEFS" << endl;
  file.close();
}

void Parser::outputEnumsHeaders()
{
  static const QString dir {"../include"};
  static const QString filePrefix {"enums"};
  static const QString fileExt {".h"};

  static const QString enumeratorType =
      m_useDefines ? "#define %1 %2" :
                     tab + tab + "static const GLenum %1 = %2";

  //  auto childs = glTree.childNodes();
  QDir outputDirectory{QDir::current()};
  if(!outputDirectory.mkdir(dir))
    if(!outputDirectory.exists(dir))
      qFatal("Could not create directory:");

  for(auto &api : glTree.nodes()) //API
    {
      auto apiValue = api->key();
      for(auto &version : api->nodes()) //Version
        {
          auto versionValue = version->key();
          for(auto &profile : version->nodes()) //Profile
            {
              auto profileValue = profile->key();
              auto dirName = dir + "/" + apiValue ;
              if(!outputDirectory.mkdir(dirName))
                if(!outputDirectory.exists(dirName))
                  qFatal("Could not create directory: ");

              auto profileStr = profileValue.isEmpty() ? "" : '_' + profileValue;
              auto fileName = dir + '/' + apiValue + '/' + filePrefix + "_"
                  + versionValue + profileStr + fileExt;

              QFile file(fileName);
              if(!file.open(QIODevice::WriteOnly| QIODevice::Truncate))
                qFatal(file.errorString().toStdString().c_str());

              QTextStream m_enumsOut{&file};
//              QTextStream m_enumsOut{stdout}; //for debug

              m_enumsOut << license;
              m_enumsOut << "#ifndef ENUMS_" + versionValue + profileStr
                         << endl;
              m_enumsOut << "#define ENUMS_" + versionValue + profileStr
                         << endl;
              m_enumsOut << "\n";
              m_enumsOut << "#include \"types.h\"" << endl;
              m_enumsOut << "\n";

              if(!m_useDefines)
                {
                  m_enumsOut << "namespace gl" << endl;
                  m_enumsOut << '{';
                }

              m_enumsOut << endl;

              for(auto &keys : profile->data()->enumList.uniqueKeys())
                {
                  auto values = profile->data()->enumList.values(keys);
                  std::sort(std::begin(values), std::end(values),
                            [](std::shared_ptr<Enum> &a, std::shared_ptr<Enum> &b)
                  {return a->value() < b->value();});

                  for(auto &items : values)
                    {
                      m_enumsOut << enumeratorType.arg(items->name())
                                    .arg(items->value());

                      m_enumsOut << ';' << endl;
                    }

                }
              if(!m_useDefines)
                m_enumsOut << "} //End of namespace gl" << endl;

              m_enumsOut << "#endif" << endl;
              file.close();
            }
        }
    }
}

void Parser::outputEnumsClassHeaders()
{
  static const QString dir {"../include"};
  static const QString filePrefix {"enums"};
  static const QString fileExt {".h"};
  //  auto childs = glTree.childNodes();
  QDir outputDirectory{QDir::current()};
  if(!outputDirectory.mkdir(dir))
    if(!outputDirectory.exists(dir))
      qFatal("Colud not create directory:");
  for(auto &api : glTree.nodes()) //API
    {
      auto apiValue = api->key();
      for(auto &version : api->nodes()) //Version
        {
          auto versionValue = version->key();
          for(auto &profile : version->nodes()) //Profile
            {
              auto profileValue = profile->key();
              auto dirName = dir + "/" + apiValue ;
              if(!outputDirectory.mkdir(dirName))
                if(!outputDirectory.exists(dirName))
                  qFatal("Colud not create directory: ");

              auto profileStr = profileValue.isEmpty() ? "" : '_' + profileValue;
              auto fileName = dir + '/' + apiValue + '/' + filePrefix + "_"
                  + versionValue + profileStr + fileExt;

              QFile file(fileName);
              if(!file.open(QIODevice::WriteOnly| QIODevice::Truncate))
                qFatal(file.errorString().toStdString().c_str());

              QTextStream m_enumsOut{&file};
              m_enumsOut << license;
              m_enumsOut << "#ifndef ENUMS_" + versionValue + profileStr
                         << endl;
              m_enumsOut << "#define ENUMS_" + versionValue + profileStr
                         << endl;
              m_enumsOut << "\n";
              m_enumsOut << "#include \"types.h\"" << endl;
              m_enumsOut << "\n";
              m_enumsOut << "namespace gl" << endl;
              m_enumsOut << '{' << endl;
              for(auto &keys : profile->data()->enumList.uniqueKeys())
                {
                  m_enumsOut << tab << "enum class " << keys << " : GLenum" << endl;
                  m_enumsOut << tab << "{" << endl;
                  auto values = profile->data()->enumList.values(keys);
                  std::sort(std::begin(values), std::end(values),
                            [](std::shared_ptr<Enum> &a, std::shared_ptr<Enum> &b)
                  {return a->value() < b->value();});
                  for(auto &items : values)
                    {
                      m_enumsOut << tab << tab << "" << items->name() << "=";
                      m_enumsOut << items->value();//Warnig name collision with gl.h
//                      m_enumsOut << items->name();
                      if(items != values.last())
                        m_enumsOut << ',';
                      m_enumsOut << endl;
                    }
                  m_enumsOut << tab << "};\n" << endl;

                }
              m_enumsOut << "} //End of namespace gl" << endl;
              m_enumsOut << "#endif" << endl;
              file.close();
            }
        }
    }
}

void Parser::outputFunctionsHeaders()
{
  static const QString dir {"../include"};
  static const QString filePrefix {"functions"};
  static const QString fileExt {".h"};
  //  auto childs = glTree.childNodes();
  QDir outputDirectory{QDir::current()};
  if(!outputDirectory.mkdir(dir))
    if(!outputDirectory.exists(dir))
      qFatal("Colud not create directory:");
  for(auto &api : glTree.nodes()) //API
    {
      auto apiValue = api->key();
      for(auto &version : api->nodes()) //Version
        {
          auto versionValue = version->key();
          for(auto &profile : version->nodes()) //Profile
            {
              auto profileValue = profile->key();
              auto dirName = dir + "/" + apiValue ;
              if(!outputDirectory.mkdir(dirName))
                if(!outputDirectory.exists(dirName))
                  qFatal("Colud not create directory: ");

              auto profileStr = profileValue.isEmpty() ? "" : '_' + profileValue;
              auto fileName = dir + '/' + apiValue + '/' + filePrefix + "_"
                  + versionValue + profileStr + fileExt;

              QFile file(fileName);
              if(!file.open(QIODevice::WriteOnly| QIODevice::Truncate))
                qFatal(file.errorString().toStdString().c_str());

              QTextStream functionOut{&file};
              functionOut << license;
              functionOut << "#ifndef FUNCTIONS_" << versionValue << profileStr
                          << endl;
              functionOut << "#define FUNCTIONS_" << versionValue << profileStr
                          << endl;
              functionOut << "\n";
              functionOut << "#include \"../binds.h\"" << endl;
              functionOut << "#include \"types.h\"" << endl;
              if(m_useEnumClass)
                functionOut << "#include \"enums_" << versionValue
                            << profileStr << fileExt << "\"" << endl;
              functionOut << "\n";
              functionOut << "namespace gl" << endl;
              functionOut << '{' << endl;

              for(auto &key : profile->data()->commandList.uniqueKeys())
                {
                  auto values = profile->data()->commandList.values(key);
                  //                  std::sort(std::begin(values), std::end(values),
                  //                            [](std::shared_ptr<Function> &a, std::shared_ptr<Function> &b)
                  //                  {return a->name < b->name;});

                  for(auto &item : values)
                    {
                      functionOut << tab << "inline " << item->returnType()
                                  << item->name() << "(";
                      auto glFunctionCall = item->name().remove(0, 2).prepend("_")
                          + "(";
                      if(!item->paramVector.empty())
                        for(auto param : item->paramVector)
                          {
                            auto paramType = QString{};
                            if(param->type() != "GLenum")
                              {
                                paramType = param->type();
                                glFunctionCall+= param->name();
                              }
                            else if(param->type() == "GLenum" && !m_useEnumClass)
                              {
                                paramType = param->type();
                                glFunctionCall+= param->name();
                              }
                            else if(param->type() == "GLenum" && m_useEnumClass)
                              {
                                paramType = param->group();
                                glFunctionCall+= "static_cast<GLenum>("
                                    + param->name() + ")";
                              }

                            functionOut << paramType << param->name();

                            if(item->paramVector.back() != param)
                              {
                                functionOut << ", ";
                                glFunctionCall+= ", ";
                              }
                            else
                              {
                                functionOut << ")" << endl;
                                glFunctionCall+= ");";
                              }
                          }
                      else
                        {
                          functionOut << ")" << endl;
                          glFunctionCall+= ");";
                        }
                      functionOut << tab << "{" << endl;
                      functionOut << tab << tab << "return " << glFunctionCall << endl;
                      functionOut << tab << "};\n" << endl;

                    }
                }
              functionOut << "}" << endl;
              functionOut << "#endif //FUNCTIONS_" + versionValue + profileStr
                          << endl;
              file.close();
            }
        }
    }
}

void Parser::outputGLHeaders()
{
  static const QString dir {"../include"};
  static const QString filePrefix {"gl"};
  static const QString fileExt {".h"};
  //  auto childs = glTree.childNodes();
  QDir outputDirectory{QDir::current()};
  if(!outputDirectory.mkdir(dir))
    if(!outputDirectory.exists(dir))
      qFatal("Colud not create directory:");
  for(auto &api : glTree.nodes()) //API
    {
      auto apiValue = api->key();
      for(auto &version : api->nodes()) //Version
        {
          auto versionValue = version->key();
          for(auto &profile : version->nodes()) //Profile
            {
              auto profileValue = profile->key();
              auto dirName = dir + "/" + apiValue ;
              if(!outputDirectory.mkdir(dirName))
                if(!outputDirectory.exists(dirName))
                  qFatal("Colud not create directory: ");

              auto profileStr = profileValue.isEmpty() ? "" : '_' + profileValue;
              auto fileName = dir + '/' + apiValue + '/' + filePrefix + "_"
                  + versionValue + profileStr + fileExt;

              QFile file(fileName);
              if(!file.open(QIODevice::WriteOnly| QIODevice::Truncate))
                qFatal(file.errorString().toStdString().c_str());

              QTextStream glOut{&file};
              glOut << license;
              glOut << "#ifndef GL_" << versionValue << profileStr
                          << endl;
              glOut << "#define GL_" << versionValue << profileStr
                          << endl;
              glOut << "\n";
              glOut << "#include \"types.h\"" << endl;
              glOut << "#include \"enums_" << versionValue
                                     << profileStr << fileExt << "\"" << endl;
              glOut << "#include \"functions_" << versionValue
                    << profileStr << fileExt << "\"" << endl;

              glOut << "#endif //GL_" + versionValue + "_" + profileStr
                          << endl;
              file.close();
            }
        }
    }
}

void Parser::outputBindingsHeaders()
{
  static const QString dir {"../include"};
  static const QString filePrefix {"binds"};
  static const QString fileExt {".h"};
  //  auto childs = glTree.childNodes();
  //  QDir outputDirectory{QDir::current()};
  //  if(!outputDirectory.mkdir(dir))
  //    if(!outputDirectory.exists(dir))
  //      qFatal("Colud not create directory:");

  auto fileName = dir + '/' + filePrefix + fileExt;

  QFile file(fileName);
  if(!file.open(QIODevice::WriteOnly| QIODevice::Truncate))
    qFatal(file.errorString().toStdString().c_str());

  QTextStream bindsOut{&file};

  bindsOut << license;
  bindsOut << "#ifndef BINDS" << endl;
  bindsOut << "#define BINDS" << endl;
  bindsOut << "\n";
  bindsOut << "#include <vector>" << endl;
  bindsOut << "#include \"function.h\"" << endl;
  bindsOut << "#include \"types.h\"" << endl;
  bindsOut << "\n";
  bindsOut << "namespace gl" << endl;
  bindsOut << '{' << endl;

  for(auto &function : functionList)
    {
      auto returnType = QString{};
      if(function->returnType().endsWith(" "))
        returnType = function->returnType().remove(-1,1);
      else
        returnType = function->returnType();

      bindsOut << tab << "static Function<" << returnType;

      if(!function->paramVector.empty())
        {
          bindsOut << ",";
          for(auto &param : function->paramVector)
            {
              bindsOut << " " << param->type();

              if(function->paramVector.back() != param)
                bindsOut << ",";
              else
                bindsOut << "> ";
            }
        }
      else
        bindsOut << "> ";

      bindsOut << function->name().remove(0, 2).prepend("_") << "(\"" << function->name()
               << "\");" << endl;
    }
  bindsOut << tab << "static std::vector<AbstractFunction *> functions" << endl;
  bindsOut << tab << "{" << endl;

  for(auto &function : functionList)
    {
      bindsOut << tab << tab << "&" << function->name().remove(0, 2).prepend("_");

      if(functionList.back() != function)
        bindsOut << "," << endl;
      else
        bindsOut << endl;
    }
  bindsOut << tab << "};" << endl;
  bindsOut << "} //namespace gl" << endl; //end namespace
  bindsOut << "#endif //BINDS" << endl;
  file.close();

}
