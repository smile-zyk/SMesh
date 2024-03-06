// glad must include at first
#include "renderwidget.h"
#include "smesh/log/log.h"
#include "smesh/render/utils.h"

#include <QPoint>
#include <QSurfaceFormat>
#include <QtImGui.h>
#include <imgui.h>

#include <memory>
#include <qnamespace.h>
#include <qpoint.h>

namespace smesh
{
    RenderWidget::RenderWidget(QWidget *parent) : QOpenGLWidget(parent), tick_timer_(this)
    {
        QSurfaceFormat format;
        format.setSamples(4);
        setFormat(format);

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
        renderer_->AddModelObject(std::make_unique<smesh::ModelObject>(path.toStdString(), path.toStdString()));
    }
    
    void RenderWidget::Tick()
    {
        renderer_->Update();
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
        renderer_ = std::make_unique<smesh::Renderer>();
        renderer_->Init();
        QtImGui::initialize(this);
    }

    void RenderWidget::resizeGL(int w, int h)
    {
        renderer_->Resize(w, h);
    }

    void RenderWidget::paintGL()
    {
        QtImGui::newFrame();
        renderer_->Draw();
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
                glm::vec2 last_pos = smesh::utils::Screen2Ndc({last_mouse_position.x(), last_mouse_position.y()}, {width(), height()});
                glm::vec2 cur_pos = smesh::utils::Screen2Ndc({current_mouse_position.x(), current_mouse_position.y()}, {width(), height()});
                renderer_->camera()->TrackBallRotate(last_pos, cur_pos);
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
} // namespace smesh