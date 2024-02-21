#pragma once
#include <memory>
#include <vector>

#include "shader_program.h"
#include "smesh/core.h"
#include "smesh/qt/modelobject.h"

#include "camera.h"
#include "smesh/render/camera.h"


namespace smesh
{
    typedef glm::vec<2, int> Size;
    
    class SMESH_API Renderer
    {
    public:
        Renderer(const Size& size);
        ~Renderer(){}
        void draw(ModelObject* object);
    private:
        std::unique_ptr<Camera> camera_;
        std::unique_ptr<glwrapper::ShaderProgram> object_shader_program_;
        Size size_;
    };
}