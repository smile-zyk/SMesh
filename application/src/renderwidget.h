#pragma once
#include "glclient.h"
#include <QOpenGLWidget>
#include <QTimer>

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
    glwrapper::GLClient glclient_;
    QTimer tick_timer_;
};