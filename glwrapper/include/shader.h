#pragma once
#include <string>
#include "gl_common.h"

namespace glwrapper
{
	class Shader
	{
	public:
		Shader(GLenum type, const char* path);
		~Shader();
		Shader(const Shader&) = delete;
		Shader(Shader&&) = delete;
	private:
		std::string path;
	protected:
		GLuint id;
		friend class ShaderProgram;
	};
}