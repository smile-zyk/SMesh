#include "frame_buffer.h"
#include "glcommon.h"

namespace glwrapper
{
    FrameBuffer::FrameBuffer()
    {
        GLCall(glCreateFramebuffers(1, &id));
    }
    
    void FrameBuffer::bind_texture(GLenum attachment, const Texture& texture, GLint level)
    {
        GLCall(glNamedFramebufferTexture(id, attachment, texture.get_id(), level));
    }
    
    void FrameBuffer::bind_render_buffer(GLenum attachment, const RenderBuffer& render_buffer)
    {
        GLCall(glNamedFramebufferRenderbuffer(id, attachment, GL_RENDERBUFFER, render_buffer.get_id()));
    }
    
    void FrameBuffer::bind()
    {
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, id));
    }
    
    void FrameBuffer::unbind()
    {
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }
    
    GLenum FrameBuffer::check_status()
    {
        GLenum res;
        GLCall(res = glCheckNamedFramebufferStatus(id, GL_FRAMEBUFFER));
        return res;
    }
    
    FrameBuffer::~FrameBuffer()
    {
        GLCall(glDeleteFramebuffers(1, &id));
    }
}