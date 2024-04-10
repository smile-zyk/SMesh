#include "render_buffer.h"
#include "glcommon.h"

namespace glwrapper
{
    RenderBuffer::RenderBuffer()
    {
        GLCall(glCreateRenderbuffers(1, &id));
    }

    RenderBuffer::~RenderBuffer()
    {
        GLCall(glDeleteRenderbuffers(1, &id));
    }

    void RenderBuffer::storage(GLenum internalformat, GLsizei width, GLsizei height)
    {
        GLCall(glNamedRenderbufferStorage(id, internalformat, width, height));
    }

    void RenderBuffer::storage_multisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
    {
        GLCall(glNamedRenderbufferStorageMultisample(id, samples, internalformat, width, height));
    }
}