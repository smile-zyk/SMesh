#version 460 core
layout(location = 0) in vec3 position;

out vec3 frag_position;

uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main() 
{
    frag_position = position;
    gl_Position = projection_matrix * view_matrix * vec4(position, 1.0);
}
