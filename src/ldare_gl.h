#ifndef __LDARE_GL__
#define __LDARE_GL__

#include "../GL/glcorearb.h"
#include "../GL/wglext.h"

extern "C"
{
	// OpenGL function pointers
	 PFNGLENABLEPROC glEnable;
	 PFNGLDISABLEPROC glDisable;
	 PFNGLCLEARPROC glClear;
	 PFNGLCLEARCOLORPROC glClearColor;
	 PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
	 PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
	 PFNGLGENBUFFERSPROC glGenBuffers;
	 PFNGLBINDBUFFERPROC glBindBuffer;
	 PFNGLDELETEBUFFERSPROC glDeleteBuffers;
	 PFNGLBUFFERSUBDATAPROC glBufferSubData;
	 PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
	 PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
	 PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
	 PFNGLGETERRORPROC glGetError;
	 PFNGLGETPROGRAMIVPROC glGetProgramiv;
	 PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
	 PFNGLGETSHADERIVPROC glGetShaderiv;
	 PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
	 PFNGLCREATESHADERPROC glCreateShader;
	 PFNGLSHADERSOURCEPROC glShaderSource;
	 PFNGLCOMPILESHADERPROC glCompileShader;
	 PFNGLCREATEPROGRAMPROC glCreateProgram;
	 PFNGLATTACHSHADERPROC glAttachShader;
	 PFNGLLINKPROGRAMPROC glLinkProgram;
	 PFNGLDELETESHADERPROC glDeleteShader;
	 PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
	 PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
	 PFNGLBUFFERDATAPROC glBufferData;
	 PFNGLMAPBUFFERPROC glMapBuffer;
	 PFNGLUNMAPBUFFERPROC glUnmapBuffer;
	 PFNGLDRAWELEMENTSPROC glDrawElements;
	 PFNGLUSEPROGRAMPROC glUseProgram;
	 PFNGLFLUSHPROC glFlush;
	 PFNGLVIEWPORTPROC glViewport;
	 PFNGLGENTEXTURESPROC glGenTextures;
	 PFNGLBINDTEXTUREPROC glBindTexture;
	 PFNGLTEXPARAMETERFPROC glTexParameteri;
	 PFNGLTEXIMAGE2DPROC glTexImage2D;
	 PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
	 PFNGLBINDBUFFERBASEPROC glBindBufferBase;
	 PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex;
	 PFNGLSCISSORPROC glScissor;
	 PFNGLDEPTHFUNCPROC glDepthFunc;

}
#endif // _LDARE_GL__
