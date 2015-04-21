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
//Qt
#include <QCoreApplication>
#include <QFile>
#include <QDebug>

//GLHeaderGen
#include "glheadergen.h"
#include "gltree.h"

#include <iostream>
using namespace GLHeaderGen;

void showHelp()
{
  static const auto help =
      "Usage: GLHeaderGen fileinput -[options]\n\n"
      "Options:\n"
      "\t-use-defines: output enumrator as defines \n\t\t"
      "instead of \"static const\"(default: off)\n"
      "\t-license: show license notice\n"
      "\t-abouts: show software information"
      "\t-help: show this help.\n";
  qDebug() << help;

}

void showLicense()
{
  static const auto smallLicense =
      "GLHeaderGen type safe header only OpenGL function binder.\n"
      "Copyright (C) 2015  Luca Carella\n\n"

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
  qDebug() << smallLicense;
}

void showAbouts()
{
  static const auto abouts = "This software make use of TinyXML2 and Qt5.4\n";
  qDebug() << abouts;
}

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  qDebug() << "GLHeaderGen Copyright (C) 2015  Luca Carella\n\n"
              "This program comes with ABSOLUTELY NO WARRANTY.\n"
              "This is free software, and you are welcome to redistribute it\n"
              "under certain conditions; for details type `-license'.\n\n";

  Parser parser;
  parser.setUseEnumClass(false);

  QFile file;
  auto wrongCommands = true;

  for(auto i = 0; i != argc; ++i)
    {
      if(strcmp("-help", argv[i]) == 0)
        {
          showHelp();
          return 0;
        }
      else if(strcmp("-abouts", argv[i]) == 0)
        {
          showAbouts();
          return 0;
        }
      else if(strcmp("-license", argv[i]) == 0)
        {
          showLicense();
          return 0;
        }
      else if(strcmp("-use-defines", argv[i]) == 0)
        {
          parser.setUseDefines(true);
        }
      else if(QString(argv[i]).contains(".xml"))
        {

          file.setFileName(argv[i]);
          if (!file.open(QFile::ReadOnly | QFile::Text))
            qCritical() << "Error opening the file";

          wrongCommands = false;
        }
    }

  if(wrongCommands)
    {
      qDebug() << "Invalid argument...\n";
      showHelp();
      return 0;
    }

  auto buffer = file.readAll();
  file.close();

  parser.read(buffer);

  return 0;
}
