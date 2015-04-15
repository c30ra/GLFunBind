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

#ifndef ORPHANENUMS
#define ORPHANENUMS

#include <QMultiMap>
#include <QString>

QMultiMap<QString/*enum name*/, QString /*enum group*/> orphanEnums
{
  //TextureUnit
  {"GL_TEXTURE0", "TextureUnit"},
  {"GL_TEXTURE0_ARB", "TextureUnit"},
  {"GL_TEXTURE1", "TextureUnit"},
  {"GL_TEXTURE10", "TextureUnit"},
  {"GL_TEXTURE10_ARB", "TextureUnit"},
  {"GL_TEXTURE11", "TextureUnit"},
  {"GL_TEXTURE11_ARB", "TextureUnit"},
  {"GL_TEXTURE12", "TextureUnit"},
  {"GL_TEXTURE12_ARB", "TextureUnit"},
  {"GL_TEXTURE13", "TextureUnit"},
  {"GL_TEXTURE13_ARB", "TextureUnit"},
  {"GL_TEXTURE14", "TextureUnit"},
  {"GL_TEXTURE14_ARB", "TextureUnit"},
  {"GL_TEXTURE15", "TextureUnit"},
  {"GL_TEXTURE15_ARB", "TextureUnit"},
  {"GL_TEXTURE16", "TextureUnit"},
  {"GL_TEXTURE16_ARB", "TextureUnit"},
  {"GL_TEXTURE17", "TextureUnit"},
  {"GL_TEXTURE17_ARB", "TextureUnit"},
  {"GL_TEXTURE18", "TextureUnit"},
  {"GL_TEXTURE18_ARB", "TextureUnit"},
  {"GL_TEXTURE19", "TextureUnit"},
  {"GL_TEXTURE19_ARB", "TextureUnit"},
  {"GL_TEXTURE1_ARB", "TextureUnit"},
  {"GL_TEXTURE2", "TextureUnit"},
  {"GL_TEXTURE20", "TextureUnit"},
  {"GL_TEXTURE20_ARB", "TextureUnit"},
  {"GL_TEXTURE21", "TextureUnit"},
  {"GL_TEXTURE21_ARB", "TextureUnit"},
  {"GL_TEXTURE22", "TextureUnit"},
  {"GL_TEXTURE22_ARB", "TextureUnit"},
  {"GL_TEXTURE23", "TextureUnit"},
  {"GL_TEXTURE23_ARB", "TextureUnit"},
  {"GL_TEXTURE24", "TextureUnit"},
  {"GL_TEXTURE24_ARB", "TextureUnit"},
  {"GL_TEXTURE25", "TextureUnit"},
  {"GL_TEXTURE25_ARB", "TextureUnit"},
  {"GL_TEXTURE26", "TextureUnit"},
  {"GL_TEXTURE26_ARB", "TextureUnit"},
  {"GL_TEXTURE27", "TextureUnit"},
  {"GL_TEXTURE27_ARB", "TextureUnit"},
  {"GL_TEXTURE28", "TextureUnit"},
  {"GL_TEXTURE28_ARB", "TextureUnit"},
  {"GL_TEXTURE29", "TextureUnit"},
  {"GL_TEXTURE29_ARB", "TextureUnit"},
  {"GL_TEXTURE2_ARB", "TextureUnit"},
  {"GL_TEXTURE3", "TextureUnit"},
  {"GL_TEXTURE30", "TextureUnit"},
  {"GL_TEXTURE30_ARB", "TextureUnit"},
  {"GL_TEXTURE31", "TextureUnit"},
  {"GL_TEXTURE31_ARB", "TextureUnit"},
  {"GL_TEXTURE3_ARB", "TextureUnit"},
  {"GL_TEXTURE4", "TextureUnit"},
  {"GL_TEXTURE4_ARB", "TextureUnit"},
  {"GL_TEXTURE5", "TextureUnit"},
  {"GL_TEXTURE5_ARB", "TextureUnit"},
  {"GL_TEXTURE6", "TextureUnit"},
  {"GL_TEXTURE6_ARB", "TextureUnit"},
  {"GL_TEXTURE7", "TextureUnit"},
  {"GL_TEXTURE7_ARB", "TextureUnit"},
  {"GL_TEXTURE8", "TextureUnit"},
  {"GL_TEXTURE8_ARB", "TextureUnit"},
  {"GL_TEXTURE9", "TextureUnit"},
  {"GL_TEXTURE9_ARB", "TextureUnit"},

  //BufferTargetARB
  {"GL_ARRAY_BUFFER", "BufferTargetARB"},
  {"GL_ARRAY_BUFFER_ARB", "BufferTargetARB"},
  {"GL_ATOMIC_COUNTER_BUFFER", "BufferTargetARB"},
  {"GL_COPY_READ_BUFFER Buffer", "BufferTargetARB"},
  {"GL_COPY_WRITE_BUFFER Buffer", "BufferTargetARB"},
  {"GL_DISPATCH_INDIRECT_BUFFER", "BufferTargetARB"},
  {"GL_DRAW_INDIRECT_BUFFER", "BufferTargetARB"},
  {"GL_ELEMENT_ARRAY_BUFFER", "BufferTargetARB"},
  {"GL_PIXEL_PACK_BUFFER Pixel", "BufferTargetARB"},
  {"GL_PIXEL_UNPACK_BUFFER", "BufferTargetARB"},
  {"GL_QUERY_BUFFER Query", "BufferTargetARB"},
  {"GL_SHADER_STORAGE_BUFFER", "BufferTargetARB"},
  {"GL_TEXTURE_BUFFER Texture", "BufferTargetARB"},
  {"GL_TRANSFORM_FEEDBACK_BUFFER", "BufferTargetARB"},
  {"GL_UNIFORM_BUFFER Uniform", "BufferTargetARB"},

  //TypeEnum
  {"GL_QUERY_WAIT", "TypeEnum"},
  {"GL_QUERY_WAIT_NV", "TypeEnum"},
  {"GL_QUERY_NO_WAIT", "TypeEnum"},
  {"GL_QUERY_NO_WAIT_NV", "TypeEnum"},
  {"GL_QUERY_BY_REGION_WAIT", "TypeEnum"},
  {"GL_QUERY_BY_REGION_WAIT_NV", "TypeEnum"},
  {"GL_QUERY_BY_REGION_NO_WAIT", "TypeEnum"},
  {"GL_QUERY_BY_REGION_NO_WAIT_NV", "TypeEnum"},
  {"GL_QUERY_WAIT_INVERTED", "TypeEnum"},
  {"GL_QUERY_NO_WAIT_INVERTED", "TypeEnum"},
  {"GL_QUERY_BY_REGION_WAIT_INVERTED", "TypeEnum"},
  {"GL_QUERY_BY_REGION_NO_WAIT_INVERTED", "TypeEnum"},

  //FramebufferTarget
  {"GL_READ_FRAMEBUFFER", "FramebufferTarget"},
  {"GL_DRAW_FRAMEBUFFER", "FramebufferTarget"},
  {"GL_FRAMEBUFFER", "FramebufferTarget"},

  //RenderbufferTarget
  {"GL_READ_FRAMEBUFFER", "RenderbufferTarget"},
  {"GL_DRAW_FRAMEBUFFER", "RenderbufferTarget"},
  {"GL_FRAMEBUFFER", "RenderbufferTarget"},

  //BlendEquationModeEXT
  {"GL_ALPHA_MAX_SGIX", "BlendEquationModeEXT"},
  {"GL_ALPHA_MIN_SGIX", "BlendEquationModeEXT"},
  {"GL_FUNC_ADD_EXT", "BlendEquationModeEXT"},
  {"GL_FUNC_REVERSE_SUBTRACT_EXT", "BlendEquationModeEXT"},
  {"GL_FUNC_SUBTRACT_EXT", "BlendEquationModeEXT"},
  {"GL_MAX_EXT", "BlendEquationModeEXT"},
  {"GL_MIN_EXT", "BlendEquationModeEXT"},
  {"GL_ALPHA_MAX", "BlendEquationModeEXT"},
  {"GL_ALPHA_MIN", "BlendEquationModeEXT"},
  {"GL_FUNC_ADD", "BlendEquationModeEXT"},
  {"GL_FUNC_REVERSE_SUBTRACT", "BlendEquationModeEXT"},
  {"GL_FUNC_SUBTRACT", "BlendEquationModeEXT"},
  {"GL_MAX", "BlendEquationModeEXT"},
  {"GL_MIN", "BlendEquationModeEXT"},

  //BlendEquationMode
  {"GL_ALPHA_MAX", "BlendEquationMode"},
  {"GL_ALPHA_MIN", "BlendEquationMode"},
  {"GL_FUNC_ADD", "BlendEquationMode"},
  {"GL_FUNC_REVERSE_SUBTRACT", "BlendEquationMode"},
  {"GL_FUNC_SUBTRACT", "BlendEquationMode"},
  {"GL_MAX", "BlendEquationMode"},
  {"GL_MIN", "BlendEquationMode"},

  //BlendFuncSeparateParameterEXT
  {"GL_ZERO", "BlendFuncSeparateParameterEXT"},
  {"GL_ONE", "BlendFuncSeparateParameterEXT"},
  {"GL_SRC_COLOR", "BlendFuncSeparateParameterEXT"},
  {"GL_ONE_MINUS_SRC_COLOR", "BlendFuncSeparateParameterEXT"},
  {"GL_DST_COLOR", "BlendFuncSeparateParameterEXT"},
  {"GL_ONE_MINUS_DST_COLOR", "BlendFuncSeparateParameterEXT"},
  {"GL_SRC_ALPHA", "BlendFuncSeparateParameterEXT"},
  {"GL_ONE_MINUS_SRC_ALPHA", "BlendFuncSeparateParameterEXT"},
  {"GL_DST_ALPHA", "BlendFuncSeparateParameterEXT"},
  {"GL_ONE_MINUS_DST_ALPHA", "BlendFuncSeparateParameterEXT"},
  {"GL_CONSTANT_COLOR", "BlendFuncSeparateParameterEXT"},
  {"GL_ONE_MINUS_CONSTANT_COLOR", "BlendFuncSeparateParameterEXT"},
  {"GL_CONSTANT_ALPHA", "BlendFuncSeparateParameterEXT"},
  {"GL_ONE_MINUS_CONSTANT_ALPHA", "BlendFuncSeparateParameterEXT"},
  {"GL_SRC_ALPHA_SATURATE", "BlendFuncSeparateParameterEXT"},
  {"GL_SRC1_COLOR", "BlendFuncSeparateParameterEXT"},
  {"GL_ONE_MINUS_SRC1_COLOR", "BlendFuncSeparateParameterEXT"},
  {"GL_SRC1_ALPHA", "BlendFuncSeparateParameterEXT"},
  {"GL_ONE_MINUS_SRC1_ALPHA", "BlendFuncSeparateParameterEXT"},

  //ClampColorTargetARB
  {"GL_CLAMP_VERTEX_COLOR", "ClampColorTargetARB"},
  {"GL_CLAMP_FRAGMENT_COLOR", "ClampColorTargetARB"},
  {"GL_CLAMP_READ_COLOR", "ClampColorTargetARB"},

  //PixelInternalFormat
  {"GL_STENCIL_INDEX", "PixelInternalFormat"},
  {"GL_RED", "PixelInternalFormat"},
  {"GL_DEPTH_COMPONENT", "PixelInternalFormat"},
  {"GL_DEPTH_STENCIL", "PixelInternalFormat"},
  {"GL_RG", "PixelInternalFormat"},
  {"GL_RGB", "PixelInternalFormat"},
  {"GL_RGBA", "PixelInternalFormat"},
  {"GL_COMPRESSED_RED", "PixelInternalFormat"},
  {"GL_COMPRESSED_RG", "PixelInternalFormat"},
  {"GL_COMPRESSED_RGB", "PixelInternalFormat"},
  {"GL_COMPRESSED_RGBA", "PixelInternalFormat"},
  {"GL_COMPRESSED_SRGB", "PixelInternalFormat"},
  {"GL_SRGB_ALPHA", "PixelInternalFormat"},
};
#endif // ORPHANENUMS

