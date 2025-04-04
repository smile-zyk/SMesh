#include "glcommon.h"
#include <memory>
#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> glwrapper::gl_logger = spdlog::stdout_color_mt("OpenGL");

bool glwrapper::GLLoad()
{
	gl_logger->set_pattern("%^[%T] %n: %v%$");
	gl_logger->set_level(spdlog::level::trace);
	if(!gladLoadGL())
	{
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
		gl_logger->error("error code {} in func {}, file {}, line {}", error, function, file, line);
		return false;
	}
	return true;
}