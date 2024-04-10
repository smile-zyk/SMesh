#pragma once
#include "glcommon.h"

namespace glwrapper
{
    class RenderBuffer
    {
      public:
        RenderBuffer();
        ~RenderBuffer();
        RenderBuffer(const RenderBuffer &) = delete;
        RenderBuffer(RenderBuffer &&) = delete;
        void storage(GLenum internalformat, GLsizei width, GLsizei height);
        void storage_multisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);

        GLuint get_id() const { return id; }
      private:
        GLuint id;
    };
} // namespace glwrapper