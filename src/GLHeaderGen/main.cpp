/*******************************************************************************
/*******************************************************************************
GLFunBind type safe header only OpenGL function binder.
Copyright (C) 2016  Luca Carella

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
//Qt
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFile>
#include <QDebug>

//GLHeaderGen
#include "glheadergen.h"
#include "gltree.h"

#include <iostream>
using namespace GLHeaderGen;

void showLicense()
{
  static const auto smallLicense =
      "GLHeaderGen type safe header only OpenGL function binder.\n"
      "Copyright (C) 2016  Luca Carella\n\n"

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
      "along with this program.  If not, see <http://www.gnu.org/licenses/>.\n";
  std::cout << smallLicense << '\n';
}

void showAbouts()
{
  static const auto abouts = "This software make use of TinyXML2 and Qt5.7\n";
  std::cout << abouts << '\n';
}

int main(int argc, char *argv[])
{
 QCoreApplication a(argc, argv);
  std::cout << "GLHeaderGen Copyright (C) 2015  Luca Carella\n\n"
              "This program comes with ABSOLUTELY NO WARRANTY.\n"
              "This is free software, and you are welcome to redistribute it\n"
              "under certain conditions; for details type `--license'.\n\n"
                          << '\n';

  QCommandLineParser clParser;
  clParser.addHelpOption();
  clParser.addPositionalArgument("source", "Input file to parse");
  clParser.addPositionalArgument("destination", QString("Optional output directory, default: %1").arg(QDir::currentPath()));
  clParser.addOptions({{"use-defines", "Output enumrator as defines, instead of \"static const\"(default: off)"},
                      {"license","Show license notice"},
                      {"abouts", "Show software information"}});
  clParser.process(a);

  auto args = clParser.positionalArguments();

  if(clParser.isSet("license")) {
    showLicense();
    return a.exit();
  }
  else if(clParser.isSet("abouts")){
    showAbouts();
    return a.exit();
  }

  if(args.isEmpty()){
    std::cout << "error: No input file provided..." << '\n';
    return a.exit();
  }
  if(args.length() > 2){
    std::cout << "error: invalid argument options" << '\n';
    return a.exit();
  }
  auto source = args.first();
  auto destDir = QDir::currentPath();

  if(args.length() == 2){
      destDir = args.last();
  }

  auto useDefines = clParser.isSet("use-defines");

  Parser parser;
  parser.setUseEnumClass(false);

  QFile file(source);
  if(!file.open(QFile::ReadOnly)){
    std::cout << file.errorString().toStdString() << '\n';
    return a.exit();
  }
  auto buffer = file.readAll();
  file.close();

  parser.read(buffer);
  parser.write(destDir);

  return a.exit();
}
