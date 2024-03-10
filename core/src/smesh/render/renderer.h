#pragma once
#include <chrono>
#include <map>
#include <memory>
#include <vector>


#include "camera.h"
#include "modelobject.h"
#include "shader_program.h"
#include "smesh/common.h"
#include "smesh/core.h"


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
        ModelObject *GetObject(size_t idx);
        size_t GetObjectCount() { return object_list_.size(); }
        Camera *camera() { return camera_.get(); }
        void set_selected_object_idx(const std::vector<int> &idx) { selected_object_idx_ = idx; }
        std::vector<int> &selected_object_idx() { return selected_object_idx_; }
        void set_gizmo_mode(GizmoMode mode) { gizmo_mode_ = mode; }
        GizmoMode gizmo_mode() { return gizmo_mode_; }

      private:
        void UpdateTime();
        void DrawScene();
        void DrawObject(ModelObject *object);
        void DrawImgui();

      private:
        RenderMode render_mode_ = RenderMode::kObject;
        GizmoMode gizmo_mode_ = GizmoMode::kTranslate;
        std::unique_ptr<Camera> camera_;
        std::map<std::string, std::unique_ptr<glwrapper::ShaderProgram>> shader_program_map_;
        std::vector<std::unique_ptr<ModelObject>> object_list_;
        std::chrono::high_resolution_clock::duration current_frame_time_;
        std::vector<int> selected_object_idx_;
        int width_{};
        int height_{};
    };
} // namespace smesh