// use SolidWireframe: https://developer.download.nvidia.cn/SDK/10/direct3d/Source/SolidWireframe/Doc/SolidWireframe.pdf
#version 460 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 vertex_normal;
out vec3 vertex_position;

uniform float outline_offset;
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main()
{
    vertex_normal = mat3(transpose(inverse(model_matrix))) * normal;
    vertex_position = vec3(model_matrix * vec4(position, 1.0));
    vertex_position = vertex_position + vertex_normal * outline_offset;
    gl_Position = projection_matrix * view_matrix * vertex_position;
}