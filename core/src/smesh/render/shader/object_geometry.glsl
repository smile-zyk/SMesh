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

uniform bool is_wireframe;
uniform bool is_smooth;
uniform int viewport_x;
uniform int viewport_y;

vec3 CalculateNormal(vec3 a, vec3 b, vec3 c)
{
    vec3 v0 = normalize(b - a);
    vec3 v1 = normalize(c - a);
    return normalize(cross(v0, v1));
}

void main()
{
    vec3 normal = CalculateNormal(vertex_position[0], vertex_position[1], vertex_position[2]);
    for(int i = 0; i < 3; i++)
    {
        gl_Position = gl_in[i].gl_Position;
        if(is_smooth)
            frag_normal = vertex_normal[i];
        else
            frag_normal = normal;
        frag_position = vertex_position[i];
        edge_distance = vec3(0,0,0);
        if(is_wireframe)
        {
            edge_distance[i] = 1;
        }
        EmitVertex();
    }
    EndPrimitive();
}