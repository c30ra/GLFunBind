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

#ifndef GL_TEST
#define GL_TEST

#include <windows.h>
#include <stddef.h>
#include <inttypes.h>

//casa
namespace gl{
  using GLenum = unsigned int;
  using GLbitfield = unsigned int;
  using GLuint = unsigned int;
  using GLint = int;
  using GLsizei = int ;
  using GLboolean = unsigned char;
  using GLbyte = signed char;
  using GLshort = short;
  using GLubyte = unsigned char;
  using GLushort = unsigned short;
  using GLulong = unsigned long;
  using GLfloat = float;
  using GLclampf = float;
  using GLdouble = double;
  using GLclampd = double;
  using GLvoid = void;
  using GLfixed = GLint;
  using GLchar = char ;
  using GLsizeiptr = ptrdiff_t;
  using GLintptr = ptrdiff_t;
  using GLhalfARB = unsigned short;
  using GLhandleARB = unsigned int;
  using GLcharARB = char;
  using GLintptrARB = ptrdiff_t;
  using GLsizeiptrARB = ptrdiff_t;
  using GLint64EXT = int64_t;
  using GLuint64EXT = uint64_t;
  using GLsync = struct __GLsync *;
  using GLuint64 = uint64_t;
  using GLhalfNV = unsigned short;
  using GLDEBUGPROC = void *(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
  using GLDEBUGPROCARB = void *(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
  using GLDEBUGPROCAMD = void *(GLuint id,GLenum category,GLenum severity,GLsizei length,const GLchar *message,void *userParam);
  using GLDEBUGPROCKHR = void *(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
  
  using GLeglImageOES = void *;
  using GLint64 = int64_t;
  using GLclampx = int;
  using GLvdpauSurfaceNV = GLintptr;
};

#endif // GL_TEST

