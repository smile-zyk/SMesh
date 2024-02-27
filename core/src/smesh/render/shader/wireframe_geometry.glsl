// use SolidWireframe: https://developer.download.nvidia.cn/SDK/10/direct3d/Source/SolidWireframe/Doc/SolidWireframe.pdf
#version 460 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 vertex_normal[];
in vec3 vertex_position[];
in vec3 vertex_color[];

out noperspective vec3 edge_distance;
out vec3 frag_normal;
out vec3 frag_position;

uniform int viewport_x;
uniform int viewport_y;

void main()
{
    vec2 viewport_position[3];
    // clipspace to viewportspace
    for(int i = 0; i < 3; i++)
    {
        viewport_position[i] = vec2
        (
            ((gl_in[i].gl_Position.x / gl_in[i].gl_Position.w) + 1) / 2 * viewport_x,
            ((gl_in[i].gl_Position.y / gl_in[i].gl_Position.w) + 1) / 2 * viewport_y
        );
    }

    float s = 0.5 * abs(viewport_position[0].x * (viewport_position[1].y - viewport_position[2].y) +
                     viewport_position[1].x * (viewport_position[2].y - viewport_position[0].y) + 
                     viewport_position[2].x * (viewport_position[0].y - viewport_position[1].y));
    
    float edge_0 = length(viewport_position[2] - viewport_position[1]);
    float edge_1 = length(viewport_position[0] - viewport_position[2]);
    float edge_2 = length(viewport_position[1] - viewport_position[0]);

    vec3 dis = vec3(2 * s / edge_0, 2 * s / edge_1, 2 * s / edge_2);

    for(int i = 0; i < 3; i++)
    {
        gl_Position = gl_in[i].gl_Position;
        frag_normal = vertex_normal[i];
        frag_position = vertex_position[i];
        edge_distance = vec3(0,0,0);
        edge_distance[i] = dis[i];
        EmitVertex();
    }
    EndPrimitive();
}