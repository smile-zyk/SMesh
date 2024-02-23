// glad must include at first
#include "smesh/render/renderer.h"
#include "renderwidget.h"
#include "smesh/log/log.h"

#include <QPoint>
#include <QtImGui.h>
#include <glfunc.h>
#include <imgui.h>

#include <chrono>
#include <memory>
#include <qnamespace.h>
#include <qpoint.h>

namespace smesh
{
    RenderWidget::RenderWidget(QWidget *parent) : QOpenGLWidget(parent), tick_timer_(this)
    {
        connect(&tick_timer_, &QTimer::timeout, this, [this]()
                { Tick(); });
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

    void RenderWidget::UpdateTime()
    {
        static std::chrono::steady_clock::time_point last_frame_time;
        auto current_frame_time = std::chrono::steady_clock::now();
        current_frame_time_ = current_frame_time - last_frame_time;
        last_frame_time = current_frame_time;
    }

    void RenderWidget::DrawScene()
    {
        glwrapper::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (auto &object : object_list_)
        {
            renderer_->draw(object.get());
        }
    }

    void RenderWidget::Tick()
    {
        // update detla time
        UpdateTime();
        // call paintGL
        update();
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
        glwrapper::enable(GL_DEPTH_TEST);
        renderer_ = std::make_unique<smesh::Renderer>(smesh::Size(width(), height()));
        QtImGui::initialize(this);
    }

    void RenderWidget::resizeGL(int w, int h)
    {
        glViewport(0, 0, width(), height());
        if (renderer_ != nullptr)
        {
            renderer_->camera()->set_aspect(static_cast<float>(w) / h);
        }
    }

    void RenderWidget::paintGL()
    {
        QtImGui::newFrame();
        DrawScene();
        DrawImgui();
        ImGui::Render();
        QtImGui::render();
    }

    void RenderWidget::mousePressEvent(QMouseEvent *event)
    {
        if (interaction_state_ == InteractionState::kNormal)
        {
            if (event->button() == Qt::LeftButton)
            {
                interaction_state_ = InteractionState::kRotate | InteractionState::kStart;
            }
            else if (event->button() == Qt::RightButton)
            {
                interaction_state_ = InteractionState::kMove | InteractionState::kStart;
            }
        }
    }

    void RenderWidget::mouseReleaseEvent(QMouseEvent *event)
    {
        if (interaction_state_ != InteractionState::kNormal)
        {
            interaction_state_ = InteractionState::kNormal;
        }
    }

    void RenderWidget::mouseMoveEvent(QMouseEvent *event)
    {
        static QPoint last_mouse_position;
        QPoint current_mouse_position = event->pos();
        if (interaction_state_ & InteractionState::kRotate)
        {
            if (interaction_state_ & InteractionState::kStart)
            {
                interaction_state_ = interaction_state_ & ~InteractionState::kStart;
            }
            else
            {
                glm::vec2 motion = {static_cast<float>((current_mouse_position - last_mouse_position).x()) / width(),
                                    static_cast<float>((current_mouse_position - last_mouse_position).y()) / height()};
                renderer_->camera()->Rotate(motion);
            }
            last_mouse_position = current_mouse_position;
        }
        else if (interaction_state_ & InteractionState::kMove)
        {
            if (interaction_state_ & InteractionState::kStart)
            {
                interaction_state_ = interaction_state_ & ~InteractionState::kStart;
            }
            else
            {
                glm::vec2 motion = {static_cast<float>((current_mouse_position - last_mouse_position).x()) / width(),
                                    static_cast<float>((current_mouse_position - last_mouse_position).y()) / height()};
                renderer_->camera()->Move(motion);
            }
            last_mouse_position = current_mouse_position;
        }
    }

    void RenderWidget::wheelEvent(QWheelEvent *event)
    {
        if (interaction_state_ == InteractionState::kNormal)
        {
            QPoint detla = event->angleDelta() / 120.f;
            renderer_->camera()->Approach(detla.y());
        }
    }

    void RenderWidget::DrawImgui()
    {
        auto current_fps = std::chrono::seconds{1} / current_frame_time_;
        ImGui::Begin("Debug");
        ImGui::Text("FPS: %lld", current_fps);
        ImGui::End();
    }

} // namespace smesh