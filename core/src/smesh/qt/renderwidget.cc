// glad must include at first
#include "smesh/render/renderer.h"
#include "renderwidget.h"

#include "smesh/log/log.h"

#include <QtImGui.h>
#include <gl/gl.h>
#include <glfunc.h>
#include <imgui.h>
#include <memory>


namespace smesh
{
    RenderWidget::RenderWidget(QWidget *parent) : QOpenGLWidget(parent), tick_timer_(this)
    {
        connect(&tick_timer_, &QTimer::timeout, this, [this]()
                { update(); });
        tick_timer_.start(16);
        smesh::Log::Init();
        SMESH_INFO("application init!");
    }

    RenderWidget::~RenderWidget()
    {
    }

    void RenderWidget::LoadModelObject(QString path)
    {
        object_list_.push_back(std::make_unique<smesh::ModelObject>(path.toStdString(), path.toStdString()));
    }

    void RenderWidget::initializeGL()
    {
        if (!glwrapper::GLLoad())
        {
            SMESH_ERROR("OpenGL Init Failed!");
            return;
        }
        SMESH_INFO("OpenGL Init Successed");
        glwrapper::set_clear_color(0.3f, 0.3f, 0.3f, 1.0f);
        renderer_ = std::make_unique<smesh::Renderer>(smesh::Size(width(), height()));
        QtImGui::initialize(this);
    }

    void RenderWidget::resizeGL(int w, int h)
    {
        glViewport(0, 0, width(), height());
    }

    void RenderWidget::paintGL()
    {
        QtImGui::newFrame();
        {
            static float f = 0.0f;
            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        }
        glwrapper::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (auto &object : object_list_)
        {
            renderer_->draw(object.get());
        }
        ImGui::Render();
        QtImGui::render();
    }
} // namespace smesh