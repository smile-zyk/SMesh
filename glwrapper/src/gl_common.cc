#include "gl_common.h"
#include <iostream>

bool glwrapper::GLLoad()
{
	if(!gladLoadGL())
	{
		std::cout << "gl init fail!" << std::endl;
		return false;
	}
	return true;
}

void glwrapper::GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool glwrapper::GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}