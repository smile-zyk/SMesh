#pragma once
#include "smesh/render/renderer.h"
#include "smesh/core.h"

#include <memory>

#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWheelEvent>

namespace smesh
{
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
        std::unique_ptr<smesh::Renderer> renderer_;
    };
} // namespace smesh