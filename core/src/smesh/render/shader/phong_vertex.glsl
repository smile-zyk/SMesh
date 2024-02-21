#version 460 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

out vec3 frag_normal;
out vec3 frag_position;
out vec3 color;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main() 
{
    frag_normal = mat3(transpose(inverse(model_matrix))) * normal;
    frag_position = vec3(model_matrix * vec4(position, 1.0));
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1.0);
}
