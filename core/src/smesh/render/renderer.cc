#include "renderer.h"
#include "buffer.h"
#include "glfunc.h"
#include "shader_program.h"
#include "smesh/log/log.h"
#include "smesh/render/camera.h"
#include "vertex_array.h"
#include <QtImGui.h>
#include <imgui.h>
#include <memory>
#include <utility>

namespace smesh
{
    Renderer::Renderer()
    {
        SMESH_TRACE("Render Init Begin");
        auto object_mode_shader_program = std::make_unique<glwrapper::ShaderProgram>("D:/DEV/SMesh/core/src/smesh/render/shader/phong_vertex.glsl",
                                                                            "D:/DEV/SMesh/core/src/smesh/render/shader/phong_fragment.glsl");
        shader_pragram_map_.insert({"object_mode_shader", std::move(object_mode_shader_program)});
        camera_ = std::make_unique<Camera>();
    }
    
    void Renderer::AddModelObject(std::unique_ptr<ModelObject> object)
    {
        object_list_.push_back(std::move(object));
    }

    void Renderer::Init()
    {
        glwrapper::set_clear_color(0.3f, 0.3f, 0.3f, 1.0f);
        glwrapper::enable(GL_DEPTH_TEST);
    }

    void Renderer::Update()
    {
        // update frame time
        UpdateTime();
        // update other...
    }

    void Renderer::Draw()
    {
        // clear
        glwrapper::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // draw scene like axis, gird ...
        DrawScene();
        // draw each object
        for (auto &object : object_list_)
        {
            DrawObject(object.get());
        }
        // draw imgui
        DrawImgui();
    }
    
    void Renderer::Resize(int w, int h)
    {
        glwrapper::set_viewport(0, 0, w, h);
        camera_->set_aspect(static_cast<float>(w)/ h);
        width_ = w;
        height_ = h;
    }

    void Renderer::UpdateTime()
    {
        // SMESH_TRACE("State is: {}", (state_ == State::kObject)?"Object" : "Edit");
        static std::chrono::steady_clock::time_point last_frame_time;
        auto current_frame_time = std::chrono::steady_clock::now();
        current_frame_time_ = current_frame_time - last_frame_time;
        last_frame_time = current_frame_time;
    }

    void Renderer::DrawScene()
    {
        // TODO: create axis and grid
    }

    void Renderer::DrawImgui()
    {
        auto current_fps = std::chrono::seconds{1} / current_frame_time_;
        ImGui::Begin("Debug");
        ImGui::Text("FPS: %lld", current_fps);
        ImGui::RadioButton("Object Mode", &state_, State::kObject);
        ImGui::RadioButton("Edit Mode", &state_, State::kEdit);;
        ImGui::End();
    }

    void Renderer::DrawObject(ModelObject *object)
    {
        // TODO: use https://www.khronos.org/assets/uploads/developers/library/2014-gdc/Khronos-OpenGL-Efficiency-GDC-Mar14.pdf
        glwrapper::set_polygon_mode(GL_FRONT, GL_FILL);
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
        shader_pragram_map_.at("object_mode_shader")->use();
        shader_pragram_map_.at("object_mode_shader")->set_uniform_value("model_matrix", object->transform());
        shader_pragram_map_.at("object_mode_shader")->set_uniform_value("view_matrix", camera_->GetViewMatrix());
        shader_pragram_map_.at("object_mode_shader")->set_uniform_value("projection_matrix", camera_->GetProjectionMatrix());
        shader_pragram_map_.at("object_mode_shader")->set_uniform_value("view_position", camera_->eye());
        shader_pragram_map_.at("object_mode_shader")->set_uniform_value("is_line", 0);
        glwrapper::draw_elements(GL_TRIANGLES, GL_UNSIGNED_INT, vao);
        if(state_ == State::kEdit)
        {
            glwrapper::set_polygon_mode(GL_FRONT, GL_LINE);
            glwrapper::enable(GL_POLYGON_OFFSET_LINE);
            glwrapper::set_polygon_offset(-1.0f, -1.0f);
            shader_pragram_map_.at("object_mode_shader")->set_uniform_value("is_line", 1);
            glwrapper::draw_elements(GL_TRIANGLES, GL_UNSIGNED_INT, vao);
            glwrapper::disable(GL_POLYGON_OFFSET_LINE);
        }
    }
} // namespace smesh