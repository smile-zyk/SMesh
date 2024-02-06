#include "Buffer.h"
#include <iostream>

glwrapper::Buffer::Buffer()
{
	GLCall(glCreateBuffers(1, &id));
}

glwrapper::Buffer::~Buffer()
{
	std::cout << "~Buffer()" << std::endl;
	GLCall(glDeleteBuffers(1, &id));
}

void glwrapper::Buffer::allocate_storage(GLsizeiptr size, const void* data, GLbitfield flags)
{
	this->size = static_cast<GLsizei>(size);
	GLCall(glNamedBufferStorage(id, size, data, flags));
}

void glwrapper::Buffer::allocate_data(GLsizeiptr size, const void* data, GLenum usage)
{
	this->size = static_cast<GLsizei>(size);
	GLCall(glNamedBufferData(id, size, data, usage));
}

void glwrapper::Buffer::allocate_sub_data(GLintptr offset, GLsizeiptr size, const void* data)
{
	GLCall(glNamedBufferSubData(id, offset, size, data));
}

void* glwrapper::Buffer::map_memory(GLenum access)
{
	GLCall(void* ret = glMapNamedBuffer(id, access));
	return ret;
}

void* glwrapper::Buffer::map_memory_range(GLintptr offset, GLsizeiptr length, GLbitfield access)
{
	GLCall(void* ret = glMapNamedBufferRange(id, offset, length, access));
	return ret;
}

void glwrapper::Buffer::unmap_memory()
{
	GLCall(glUnmapNamedBuffer(id));
}