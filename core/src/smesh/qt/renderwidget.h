#pragma once

#include "smesh/core.h"

#include <memory>

#include <QOpenGLWidget>
#include <QTimer>

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

      protected:
        virtual void initializeGL() Q_DECL_OVERRIDE;
        virtual void resizeGL(int w, int h) Q_DECL_OVERRIDE;
        virtual void paintGL() Q_DECL_OVERRIDE;

      private:
        QTimer tick_timer_;
        std::vector<std::unique_ptr<smesh::ModelObject>> object_list_;
        std::unique_ptr<smesh::Renderer> renderer_;
    };
} // namespace smesh