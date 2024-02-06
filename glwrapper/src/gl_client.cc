#include "gl_client.h"

using namespace glwrapper;

void GLClient::set_clear_color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	GLCall(glClearColor(red, green, blue, alpha));
}

void GLClient::clear(GLbitfield mask)
{
	GLCall(glClear(mask));
}

void GLClient::enable(GLenum cap)
{
	GLCall(glEnable(cap));
}

void GLClient::draw_arrays(GLenum mode, const VertexArray& vao, const ShaderProgram& program)
{
	vao.bind();
	program.use();
	GLCall(glDrawArrays(mode, 0, vao.get_vertex_count()));
}

void GLClient::draw_elements(GLenum mode, GLenum type, const VertexArray& vao, const ShaderProgram& program)
{
	vao.bind();
	program.use();
	GLsizei count = 0;
	switch (type)
	{
	case GL_UNSIGNED_BYTE:
		count = vao.get_element_size() / sizeof(unsigned char);
		break;
	case GL_UNSIGNED_SHORT:
		count = vao.get_element_size() / sizeof(unsigned short);
		break;
	case GL_UNSIGNED_INT:
		count = vao.get_element_size() / sizeof(unsigned int);
		break;
	default:
		break;
	}
	GLCall(glDrawElements(mode, count, type, 0));
}

void GLClient::set_polygon_mode(GLenum face, GLenum mode)
{
	GLCall(glPolygonMode(face, mode));
}
