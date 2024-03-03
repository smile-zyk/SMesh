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
uniform int viewport_x;
uniform int viewport_y;

vec3 CalculateDistance(vec4 a, vec4 b, vec4 c)
{
    vec2 viewport_position[3] = vec2[]
    (
        vec2(((a.x / a.w) + 1) / 2 * viewport_x,((a.y / a.w) + 1) / 2 * viewport_y),
        vec2(((b.x / b.w) + 1) / 2 * viewport_x,((b.y / b.w) + 1) / 2 * viewport_y),
        vec2(((c.x / c.w) + 1) / 2 * viewport_x,((c.y / c.w) + 1) / 2 * viewport_y)
    );
    float s = 0.5 * abs(viewport_position[0].x * (viewport_position[1].y - viewport_position[2].y) +
                     viewport_position[1].x * (viewport_position[2].y - viewport_position[0].y) + 
                     viewport_position[2].x * (viewport_position[0].y - viewport_position[1].y));
    
    float edge_0 = length(viewport_position[2] - viewport_position[1]);
    float edge_1 = length(viewport_position[0] - viewport_position[2]);
    float edge_2 = length(viewport_position[1] - viewport_position[0]);

    vec3 dis = vec3(2 * s / edge_0, 2 * s / edge_1, 2 * s / edge_2);

    return dis;
}

vec3 CalculateNormal(vec3 a, vec3 b, vec3 c)
{
    vec3 v0 = normalize(b - a);
    vec3 v1 = normalize(c - a);
    return normalize(cross(v0, v1));
}

void main()
{
    vec3 normal = CalculateNormal(vertex_position[0], vertex_position[1], vertex_position[2]);
    vec3 dis = vec3(0, 0, 0);

    if(is_wireframe)
        dis = CalculateDistance(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position);

    for(int i = 0; i < 3; i++)
    {
        gl_Position = gl_in[i].gl_Position;
        frag_normal = normal;
        frag_position = vertex_position[i];
        edge_distance = vec3(0,0,0);
        edge_distance[i] = dis[i];
        EmitVertex();
    }
    EndPrimitive();
}