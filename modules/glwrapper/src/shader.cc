#include "shader.h"
#include "glcommon.h"

#include <fstream>
#include <sstream>

using namespace glwrapper;

Shader::Shader(GLenum type, const char* path)
{
	std::string vertexCode;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		shaderFile.open(path);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		vertexCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		gl_logger->error("shader program file read fail, %s", e.what());
	}
	this->path = path;
	const char* shaderCodeStr = vertexCode.c_str();
	GLCall(id = glCreateShader(type));
	GLCall(glShaderSource(id, 1, &shaderCodeStr, NULL));
	GLCall(glCompileShader(id));
	// check for shader compile errors
	int success;
	char infoLog[512];
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		GLCall(glGetShaderInfoLog(id, 512, NULL, infoLog));
		gl_logger->error("%s shader compile failed, %s", path, infoLog);
	}
}

Shader::~Shader()
{
	GLCall(glDeleteShader(id));
}