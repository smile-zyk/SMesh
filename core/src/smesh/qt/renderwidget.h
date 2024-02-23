#pragma once

#include "smesh/core.h"

#include <chrono>
#include <memory>

#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWheelEvent>

namespace smesh
{
    class Renderer;
    class ModelObject;
    class SMESH_API RenderWidget : public QOpenGLWidget
    {
        Q_OBJECT
      public:
        RenderWidget(QWidget *parent = nullptr);
        ~RenderWidget();
        void LoadModelObject(QString path);
        void Tick();

      protected:
        virtual void initializeGL() Q_DECL_OVERRIDE;
        virtual void resizeGL(int w, int h) Q_DECL_OVERRIDE;
        virtual void paintGL() Q_DECL_OVERRIDE;

        // qt event
        void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
        void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
        void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
        void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

        virtual void UpdateTime();

        virtual void DrawImgui();
        virtual void DrawScene();

      private:
        enum InteractionState
        {
            kNormal = 0,
            kStart = 1 << 0,
            kRotate = 1 << 1,
            kMove = 1 << 2,
        };
        typedef int InteractionStates;
        InteractionStates interaction_state_ = InteractionState::kNormal;
        QTimer tick_timer_;
        std::vector<std::unique_ptr<smesh::ModelObject>> object_list_;
        std::unique_ptr<smesh::Renderer> renderer_;
        std::chrono::steady_clock::duration current_frame_time_;
    };
} // namespace smesh