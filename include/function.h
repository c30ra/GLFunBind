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

#ifndef FUNCTIONS
#define FUNCTIONS

#include <windows.h>

class AbstractFunction
{
public:
  using Adress = void(*)();
  AbstractFunction(const char *name)
    : m_name{name}
  {}

  void resolveFunction()
  {
    if(m_name)
      getProcAdress(m_name);
  }

  const char *name() const {return m_name;}
  //    const Adress adress() const {return m_adress;}

protected:
  Adress adress;


private:
  void getProcAdress(const char *name)
  {
    auto p = static_cast<void *>(wglGetProcAddress(name));
    if(p == 0 ||
       (p == reinterpret_cast<void *>(0x1)) ||
       (p == reinterpret_cast<void *>(0x2)) ||
       (p == reinterpret_cast<void *>(0x3)) ||
       (p == reinterpret_cast<void *>(-1)) )
      {
        HMODULE module = LoadLibraryA("opengl32.dll");
        p = static_cast<void *>(GetProcAddress(module, name));
      }
    adress = reinterpret_cast<Adress>(p);
  }
  const char *m_name;

};

template<typename ReturnType, typename... Args>
class Function : public AbstractFunction
{
public:

  using FunctionPointer =  ReturnType(*)(Args...);

  Function(const char *name)
    : AbstractFunction{name}
  {}

  ReturnType operator()(Args... arguments)
  {

    if(adress)
      return reinterpret_cast<FunctionPointer>(adress)(arguments...);
    else
      {
        resolveFunction();
        assert(adress);
        return reinterpret_cast<FunctionPointer>(adress)(arguments...);
      }
  }
};
#endif // FUNCTIONS

