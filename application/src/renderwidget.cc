#include "renderwidget.h"
#include <imgui.h>
#include <QtImGui.h>
#include "log.h"
#include "renderer.h"

RenderWidget::RenderWidget(QWidget *parent): QOpenGLWidget(parent), tick_timer_(this)
{
    connect(&tick_timer_, &QTimer::timeout, this, [this](){update();});
    tick_timer_.start(16);
    smesh::Log::Init();
    SMESH_INFO("application init!");
    smesh::Renderer r;
}

void RenderWidget::initializeGL()
{
    if(glwrapper::GLLoad())
    {
        glclient_.set_clear_color(1.0, 0.0, 0.0, 1.0);
    }
    QtImGui::initialize(this);
}

void RenderWidget::resizeGL(int w, int h)
{

}

void RenderWidget::paintGL()
{
    QtImGui::newFrame();
    {
        static float f = 0.0f;
        ImGui::Text("Hello, world!");
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    }
    glViewport(0, 0, width(), height());
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui::Render();
    QtImGui::render();
}
