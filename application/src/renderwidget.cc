#include "renderwidget.h"

RenderWidget::RenderWidget(QWidget *parent): QOpenGLWidget(parent)
{
}

void RenderWidget::initializeGL()
{
    if(glwrapper::GLLoad())
    {
        gl_client_.set_clear_color(1.0, 0.0, 0.0, 1.0);
    }
}

void RenderWidget::resizeGL(int w, int h)
{
    
}

void RenderWidget::paintGL()
{
}
