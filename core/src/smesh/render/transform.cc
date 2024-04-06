#include "transform.h"
#include "smesh/render/rotation.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <memory>

namespace smesh
{
    Transform::Transform()
    {
        rotate_ = std::make_unique<Rotation>();
        set_matrix(glm::mat4{1.0});
    }

    void Transform::set_matrix(glm::mat4 matrix)
    {
	    glm::quat quaternion;
	    glm::vec3 skew;
	    glm::vec4 perspective;

	    glm::decompose(matrix, scale_, quaternion, translate_, skew, perspective);
        rotate_->set_quaternion(quaternion);
    }

    glm::mat4 Transform::matrix()
    {
        glm::mat4 res{1.0};
        res = glm::translate(res, translate_);
        res = res * rotate_->matrix();
        res = glm::scale(res, scale_);
        return res;
    }
}