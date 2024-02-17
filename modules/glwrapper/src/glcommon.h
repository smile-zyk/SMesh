#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <memory>
#include <spdlog/spdlog.h>

#define ASSERT(x)\
	if(!(x)) __debugbreak()
#define GLCall(x)\
	GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

namespace glwrapper
{
	extern std::shared_ptr<spdlog::logger> gl_logger;
	bool GLLoad();
	void GLClearError();
	bool GLLogCall(const char* function, const char* file, int line);
}


