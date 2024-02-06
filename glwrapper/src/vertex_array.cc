#include "vertex_array.h"
#include <iostream>

glwrapper::VertexArray::VertexArray()
{
    GLCall(glCreateVertexArrays(1, &id));
}

glwrapper::VertexArray::~VertexArray()
{
    std::cout << "~VertexArray()" << std::endl;
    GLCall(glDeleteVertexArrays(1, &id));
}

void glwrapper::VertexArray::bind_vertex_buffer(GLuint bindingindex, const Buffer &buffer, GLintptr offset, GLsizei stride)
{
    vertex_count = buffer.size / stride;
    GLCall(glVertexArrayVertexBuffer(id, bindingindex, buffer.id, offset, stride));
}

void glwrapper::VertexArray::bind_element_buffer(const Buffer &buffer)
{
    element_size = buffer.size;
    GLCall(glVertexArrayElementBuffer(id, buffer.id));
}

void glwrapper::VertexArray::enable_attrib(GLuint attribindex)
{
    GLCall(glEnableVertexArrayAttrib(id, attribindex));
}

void glwrapper::VertexArray::disable_attrib(GLuint attribindex)
{
    GLCall(glDisableVertexArrayAttrib(id, attribindex));
}

void glwrapper::VertexArray::bind_attrib(GLuint attribindex, GLuint bindingindex)
{
    GLCall(glVertexArrayAttribBinding(id, attribindex, bindingindex));
}

void glwrapper::VertexArray::set_attrib(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
{
    GLCall(glVertexArrayAttribFormat(id, attribindex, size, type, normalized, relativeoffset));
}

void glwrapper::VertexArray::bind() const
{
    GLCall(glBindVertexArray(id));
}

void glwrapper::VertexArray::unbind() const
{
    GLCall(glBindVertexArray(0));
}