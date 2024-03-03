#include "renderer.h"
#include "buffer.h"
#include "glfunc.h"
#include "shader_program.h"
#include "smesh/log/log.h"
#include "smesh/render/camera.h"
#include "vertex_array.h"
#include <QtImGui.h>
#include <glm/fwd.hpp>
#include <imgui.h>
#include <memory>
#include <utility>

namespace smesh
{
    Renderer::Renderer()
    {
        SMESH_TRACE("Render Init Begin");
        auto object_shader_program = std::make_unique<glwrapper::ShaderProgram>("D:/DEV/SMesh/core/src/smesh/render/shader/object_vertex.glsl",
                                                                                   "D:/DEV/SMesh/core/src/smesh/render/shader/object_fragment.glsl",
                                                                                   "D:/DEV/SMesh/core/src/smesh/render/shader/object_geometry.glsl");

        auto grid_shader_program = std::make_unique<glwrapper::ShaderProgram>("D:/DEV/SMesh/core/src/smesh/render/shader/grid_vertex.glsl",
                                                                              "D:/DEV/SMesh/core/src/smesh/render/shader/grid_fragment.glsl");

        shader_program_map_.insert({"object_shader", std::move(object_shader_program)});
        shader_program_map_.insert({"grid_shader", std::move(grid_shader_program)});
        camera_ = std::make_unique<Camera>();
        SMESH_TRACE("Render Init End");
    }

    void Renderer::AddModelObject(std::unique_ptr<ModelObject> object)
    {
        object_list_.push_back(std::move(object));
    }

    void Renderer::Init()
    {
        glwrapper::set_clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        glwrapper::enable(GL_DEPTH_TEST);
        glwrapper::enable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
        // draw each object
        for (auto &object : object_list_)
        {
            DrawObject(object.get());
        }
        // draw scene like axis, gird ...
        // cause scene has opacity object, so we should draw it last;
        DrawScene();
        // draw imgui
        DrawImgui();
    }

    void Renderer::Resize(int w, int h)
    {
        glwrapper::set_viewport(0, 0, w, h);
        camera_->set_aspect(static_cast<float>(w) / h);
        width_ = w;
        height_ = h;
    }

    void Renderer::UpdateTime()
    {
        // SMESH_TRACE("State is: {}", (state_ == State::kObject)?"Object" : "Edit");
        static std::chrono::high_resolution_clock::time_point last_frame_time = std::chrono::high_resolution_clock::now();
        auto current_frame_time = std::chrono::high_resolution_clock::now();
        current_frame_time_ = current_frame_time - last_frame_time;
        last_frame_time = current_frame_time;
    }

    void Renderer::DrawScene()
    {
        // TODO: create axis and grid
        auto& grid_shader = shader_program_map_.at("grid_shader");
        grid_shader->use();
        grid_shader->set_uniform_value("view_matrix", camera_->GetViewMatrix());
        grid_shader->set_uniform_value("projection_matrix", camera_->GetProjectionMatrix());
        grid_shader->set_uniform_value("view_position", camera_->eye());
        glwrapper::draw_arrays(GL_TRIANGLES, 6);
    }

    static float line_width = 1.5;

    void Renderer::DrawImgui()
    {
        static long long current_fps = 0;
        // Must check whether current_frame_time is 0
        // Otherwise the program in Release mode maybe fail the first time it starts
        // update: This problem is resolved by changing steady_clock to high_resolution_clock, but it is recommended to determine whether current_frame_time_ is 0, so leave the if
        if (current_frame_time_.count() != 0)
        {
            current_fps = std::chrono::seconds{1} / current_frame_time_;
        }
        ImGui::Begin("Debug");
        ImGui::Text("FPS: %lld", current_fps);
        ImGui::RadioButton("Object Mode", &state_, State::kObject);
        ImGui::RadioButton("Edit Mode", &state_, State::kEdit);
        if (state_ == State::kEdit)
        {
            ImGui::SliderFloat("LineWidth", &line_width, 0, 5);
        }
        ImGui::End();
    }

    void Renderer::DrawObject(ModelObject *object)
    {
        // TODO: use https://www.khronos.org/assets/uploads/developers/library/2014-gdc/Khronos-OpenGL-Efficiency-GDC-Mar14.pdf
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
        auto& object_shader = shader_program_map_.at("object_shader");
        object_shader->use();
        object_shader->set_uniform_value("model_matrix", object->transform());
        object_shader->set_uniform_value("view_matrix", camera_->GetViewMatrix());
        object_shader->set_uniform_value("projection_matrix", camera_->GetProjectionMatrix());
        object_shader->set_uniform_value("view_position", camera_->eye());
        object_shader->set_uniform_value("viewport_x", width_);
        object_shader->set_uniform_value("viewport_y", height_);
        object_shader->set_uniform_value("line_width", line_width);
        bool is_wireframe = state_ == State::kEdit ? true : false;
        object_shader->set_uniform_value("is_wireframe", is_wireframe);
        glwrapper::draw_elements(GL_TRIANGLES, GL_UNSIGNED_INT, vao);
    }
} // namespace smesh