#include "renderer.h"
#include "buffer.h"
#include "glfunc.h"
#include "shader_program.h"
#include "smesh/log/log.h"
#include "smesh/render/camera.h"
#include "smesh/render/renderer.h"
#include "vertex_array.h"
#include <OpenMesh/Core/System/config.h>
#include <glm/fwd.hpp>
#include <memory>

namespace smesh
{
    Renderer::Renderer(const Size &size)
    {
        SMESH_TRACE("Render Init Begin");
        size_ = size;
        object_shader_program_ = std::make_unique<glwrapper::ShaderProgram>("D:/DEV/SMesh/core/src/smesh/render/shader/phong_vertex.glsl",
                                                                            "D:/DEV/SMesh/core/src/smesh/render/shader/phong_fragment.glsl");
        camera_ = std::make_unique<Camera>(60, 1.f, 1000.f, static_cast<float>(size_.x) / size_.y);
    }

    void Renderer::draw(ModelObject *object)
    {
        glwrapper::VertexArray vao;
        glwrapper::Buffer vbo;
        glwrapper::Buffer ebo;
        auto render_data = object->mesh()->render_data();
        vbo.allocate_storage(render_data->render_points.size() * sizeof(VertexRenderData), render_data->render_points.data(), GL_DYNAMIC_STORAGE_BIT);
        ebo.allocate_storage(render_data->render_indices.size() * sizeof(unsigned int), render_data->render_indices.data(), GL_DYNAMIC_STORAGE_BIT);
        vao.bind_vertex_buffer(0, vbo, offsetof(VertexRenderData, position), sizeof(VertexRenderData));
        vao.bind_vertex_buffer(1, vbo, offsetof(VertexRenderData, normal), sizeof(VertexRenderData));
        vao.bind_vertex_buffer(2, vbo, offsetof(VertexRenderData, color), sizeof(VertexRenderData));
        vao.set_attrib(0, 3, GL_FLOAT, false, 0);
	    vao.set_attrib(1, 3, GL_FLOAT, false, 0);
	    vao.set_attrib(2, 3, GL_FLOAT, false, 0);
        vao.bind_attrib(0, 0);
	    vao.bind_attrib(1, 1);
	    vao.bind_attrib(2, 2);
	    vao.enable_attrib(0);
	    vao.enable_attrib(1);
	    vao.enable_attrib(2);
        vao.bind_element_buffer(ebo);
        vao.bind();
        object_shader_program_->use();
        object_shader_program_->set_uniform_value("model_matrix", object->transform());
        object_shader_program_->set_uniform_value("view_matrix", camera_->GetViewMatrix());
        object_shader_program_->set_uniform_value("projection_matrix", camera_->GetProjectionMatrix());
        glwrapper::draw_elements(GL_TRIANGLES , GL_UNSIGNED_INT, vao);
    }
} // namespace smesh