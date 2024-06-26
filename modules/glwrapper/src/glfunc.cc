#include "glfunc.h"
#include "glcommon.h"

namespace glwrapper
{

    void set_clear_color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
    {
        GLCall(glClearColor(red, green, blue, alpha));
    }
    
    void set_viewport(GLint x, GLint y ,GLsizei width, GLsizei height)
    {
        GLCall(glViewport(x, y, width, height));
    }

    void clear(GLbitfield mask)
    {
        GLCall(glClear(mask));
    }

    void disable(GLenum cap)
    {
        GLCall(glDisable(cap));
    }
    
    void draw_arrays(GLenum mode, GLint count)
    {
        GLCall(glDrawArrays(mode, 0, count));
    }

    void enable(GLenum cap)
    {
        GLCall(glEnable(cap));
    }

    void draw_arrays(GLenum mode, const VertexArray &vao)
    {
        GLCall(glDrawArrays(mode, 0, vao.get_vertex_count()));
    }

    void draw_elements(GLenum mode, GLenum type, const VertexArray &vao)
    {
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
    
    void set_cull_face_mode(GLenum mode)
    {
        GLCall(glCullFace(mode));
    }
    
    void set_blend_func(GLenum sfactor, GLenum dfactor)
    {
        GLCall(glBlendFunc(sfactor, dfactor));
    }
    
    void set_polygon_offset(GLfloat factor, GLfloat units)
    {
        GLCall(glPolygonOffset(factor, units));
    }

    void set_polygon_mode(GLenum face, GLenum mode)
    {
        GLCall(glPolygonMode(face, mode));
    }
} // namespace glwrapper