#ifndef _LDK_GL_H_
#define _LDK_GL_H_

#include "../GL/glcorearb.h"
#include "../GL/wglext.h"

#ifdef LDK_EXTERN_GL_FUNCTIONS
#define GLFUNCPTR extern
#else
#define GLFUNCPTR
#endif //LDK_EXTERN_GL_FUNCTIONS

	// OpenGL function pointers
	 GLFUNCPTR PFNGLENABLEPROC glEnable;
	 GLFUNCPTR PFNGLDISABLEPROC glDisable;
	 GLFUNCPTR PFNGLCLEARPROC glClear;
	 GLFUNCPTR PFNGLCLEARCOLORPROC glClearColor;
	 GLFUNCPTR PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
	 GLFUNCPTR PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
	 GLFUNCPTR PFNGLGENBUFFERSPROC glGenBuffers;
	 GLFUNCPTR PFNGLBINDBUFFERPROC glBindBuffer;
	 GLFUNCPTR PFNGLDELETEBUFFERSPROC glDeleteBuffers;
	 GLFUNCPTR PFNGLBUFFERSUBDATAPROC glBufferSubData;
	 GLFUNCPTR PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
	 GLFUNCPTR PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
	 GLFUNCPTR PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
	 GLFUNCPTR PFNGLGETERRORPROC glGetError;
	 GLFUNCPTR PFNGLGETPROGRAMIVPROC glGetProgramiv;
	 GLFUNCPTR PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
	 GLFUNCPTR PFNGLGETSHADERIVPROC glGetShaderiv;
	 GLFUNCPTR PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
	 GLFUNCPTR PFNGLCREATESHADERPROC glCreateShader;
	 GLFUNCPTR PFNGLSHADERSOURCEPROC glShaderSource;
	 GLFUNCPTR PFNGLCOMPILESHADERPROC glCompileShader;
	 GLFUNCPTR PFNGLCREATEPROGRAMPROC glCreateProgram;
	 GLFUNCPTR PFNGLATTACHSHADERPROC glAttachShader;
	 GLFUNCPTR PFNGLLINKPROGRAMPROC glLinkProgram;
	 GLFUNCPTR PFNGLDELETESHADERPROC glDeleteShader;
	 GLFUNCPTR PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
	 GLFUNCPTR PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
	 GLFUNCPTR PFNGLBUFFERDATAPROC glBufferData;
	 GLFUNCPTR PFNGLMAPBUFFERPROC glMapBuffer;
	 GLFUNCPTR PFNGLUNMAPBUFFERPROC glUnmapBuffer;
	 GLFUNCPTR PFNGLDRAWELEMENTSPROC glDrawElements;
	 GLFUNCPTR PFNGLUSEPROGRAMPROC glUseProgram;
	 GLFUNCPTR PFNGLFLUSHPROC glFlush;
	 GLFUNCPTR PFNGLVIEWPORTPROC glViewport;
	 GLFUNCPTR PFNGLGENTEXTURESPROC glGenTextures;
	 GLFUNCPTR PFNGLBINDTEXTUREPROC glBindTexture;
	 GLFUNCPTR PFNGLTEXPARAMETERFPROC glTexParameteri;
	 GLFUNCPTR PFNGLTEXIMAGE2DPROC glTexImage2D;
	 GLFUNCPTR PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
	 GLFUNCPTR PFNGLBINDBUFFERBASEPROC glBindBufferBase;
	 GLFUNCPTR PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex;
	 GLFUNCPTR PFNGLSCISSORPROC glScissor;
	 GLFUNCPTR PFNGLDEPTHFUNCPROC glDepthFunc;
	 GLFUNCPTR PFNGLBLENDFUNCPROC glBlendFunc;
	 GLFUNCPTR PFNGLDEPTHMASKPROC glDepthMask;
	 GLFUNCPTR PFNGLPOLYGONMODEPROC glPolygonMode;
	 GLFUNCPTR PFNGLPOLYGONOFFSETPROC glPolygonOffset;
	 GLFUNCPTR PFNGLLINEWIDTHPROC glLineWidth;
#endif // _LDK_GL_H_
