#pragma once
#include "glcommon.h"
#include "texture.h"
#include "render_buffer.h"

namespace glwrapper {
    class FrameBuffer
    {
    public:
        FrameBuffer();
		~FrameBuffer();
		FrameBuffer(const FrameBuffer&) = delete;
		FrameBuffer(FrameBuffer&&) = delete;
        void bind_texture(GLenum attachment, const Texture& texture, GLint level);
        void bind_render_buffer(GLenum attachment, const RenderBuffer& render_buffer);
        void bind();
        void unbind();
        GLenum check_status();
	private:
        GLuint id;
    };
}