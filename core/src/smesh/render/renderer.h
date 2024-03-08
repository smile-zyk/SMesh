#pragma once
#include <chrono>
#include <memory>
#include <vector>
#include <map>

#include "shader_program.h"
#include "smesh/core.h"
#include "camera.h"
#include "modelobject.h"

namespace smesh
{
    class SMESH_API Renderer
    {
      public:
        Renderer();
        ~Renderer() {}
        void AddModelObject(std::unique_ptr<ModelObject> object);
        void Init();
        void Update();
        void Draw();
        void Resize(int w, int h);
        ModelObject* GetObject(size_t idx);
        size_t GetObjectCount() { return object_list_.size(); }
        Camera *camera() { return camera_.get(); }
      private:
        void UpdateTime();
        void DrawScene();
        void DrawObject(ModelObject *object);
        void DrawImgui();
      private:
        enum State
        {
          // Object Mode
          kObject = 0,
          // Edit Mode
          kEdit = 1<<0,
        };
        typedef int States;
        States state_ = State::kObject;
        std::unique_ptr<Camera> camera_;
        std::map<std::string, std::unique_ptr<glwrapper::ShaderProgram>> shader_program_map_;
        std::vector<std::unique_ptr<ModelObject>> object_list_;
        std::chrono::high_resolution_clock::duration current_frame_time_;
        int width_ {};
        int height_{};
    };
} // namespace smesh