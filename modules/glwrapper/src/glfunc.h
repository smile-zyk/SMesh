#pragma once
#include "glcommon.h"
#include "vertex_array.h"

namespace glwrapper
{
	void set_clear_color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	void clear(GLbitfield mask);
	void enable(GLenum cap);

	void draw_arrays(GLenum mode, const VertexArray& vao);
	void draw_elements(GLenum mode, GLenum type, const VertexArray& vao);

	void set_polygon_mode(GLenum face, GLenum mode);
}