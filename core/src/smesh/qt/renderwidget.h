#pragma once

#include "smesh/core.h"

#include <memory>

#include <QOpenGLWidget>
#include <QTimer>

namespace glwrapper {
  class GLClient;
}

class SMESH_API RenderWidget : public QOpenGLWidget
{
    Q_OBJECT
  public:
    RenderWidget(QWidget *parent = nullptr);
    ~RenderWidget();
  protected:
    virtual void initializeGL() Q_DECL_OVERRIDE;
    virtual void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    virtual void paintGL() Q_DECL_OVERRIDE;
  private:
    std::unique_ptr<glwrapper::GLClient> glclient_{};
    QTimer tick_timer_;
};