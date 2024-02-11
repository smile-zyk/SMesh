#pragma once
#include "gl_client.h"
#include <QOpenGLWidget>

class RenderWidget : public QOpenGLWidget
{
    Q_OBJECT
  public:
    RenderWidget(QWidget *parent = nullptr);
    ~RenderWidget() {}
  protected:
    virtual void initializeGL() Q_DECL_OVERRIDE;
    virtual void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    virtual void paintGL() Q_DECL_OVERRIDE;
  private:
    glwrapper::GLClient gl_client_;
};