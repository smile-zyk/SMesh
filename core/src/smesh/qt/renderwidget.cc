// glad must include at first
#include <glad/glad.h>

#include "renderwidget.h"

#include "smesh/log/log.h"

#include <glclient.h>
#include <imgui.h>
#include <QtImGui.h>
#include <memory>


RenderWidget::RenderWidget(QWidget *parent): QOpenGLWidget(parent), tick_timer_(this)
{
    glclient_ = std::make_unique<glwrapper::GLClient>();
    connect(&tick_timer_, &QTimer::timeout, this, [this](){update();});
    tick_timer_.start(16);
    smesh::Log::Init();
    SMESH_INFO("application init!");
}

RenderWidget::~RenderWidget()
{
}

void RenderWidget::initializeGL()
{
    if(glwrapper::GLLoad())
    {
        glclient_->set_clear_color(1.0, 0.0, 0.0, 1.0);
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
    glclient_->clear(GL_COLOR_BUFFER_BIT);
    ImGui::Render();
    QtImGui::render();
}
