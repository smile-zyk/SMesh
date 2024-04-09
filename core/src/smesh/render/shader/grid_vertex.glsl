//infinite grid: see https://asliceofrendering.com/scene%20helper/2020/01/05/InfiniteGrid/
#version 460 core

out vec3 near_point;
out vec3 far_point;

uniform mat4 view_matrix;
uniform mat4 projection_matrix;

// opengl ndc space near plane is -1
vec3 grid_plane[6] = vec3[]
(
    vec3(1, 1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
    vec3(-1, -1, -1), vec3(1, 1, -1), vec3(1, -1, -1)
);

vec3 NDC2World(vec3 p_ndc, mat4 view, mat4 proj)
{
    mat4 view_inv = inverse(view);
    mat4 proj_inv = inverse(proj);
    vec4 p_world = view_inv * proj_inv * vec4(p_ndc, 1.0);
    return p_world.xyz / p_world.w;
}

void main() 
{
    vec3 p = grid_plane[gl_VertexID];
    near_point = NDC2World(vec3(p.xy, -1.0), view_matrix, projection_matrix);
    far_point = NDC2World(vec3(p.xy, 1.0), view_matrix, projection_matrix);
    gl_Position = vec4(p, 1.0);
}
