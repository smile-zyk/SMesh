//infinite grid: see https://asliceofrendering.com/scene%20helper/2020/01/05/InfiniteGrid/
#version 460 core
in vec3 near_point;
in vec3 far_point;

out vec4 frag_color;

uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform vec3 view_position;

float max_fade_depth = abs((view_matrix * vec4(far_point, 1.0)).z);

float ComputeDepth(vec3 pos)
{
    vec4 clip_space_pos = projection_matrix * view_matrix * vec4(pos.xyz, 1.0);
    float ndc_z = clip_space_pos.z / clip_space_pos.w;
    return ndc_z * 0.5 + 0.5;
}

float ComputeFade(vec3 pos, float depth)
{
    depth = min(depth, max_fade_depth);
    vec3 eye2pos = pos - view_position;
    float depth_asp = length(eye2pos) / depth;
    float depth_fade = clamp(1 - depth_asp, 0, 1);
    float lookat_fade = 1;
    float cos_view_axisz = abs(dot(normalize(eye2pos), vec3(0,0,1)));
    if(cos_view_axisz < 0.2)
        lookat_fade = cos_view_axisz * 5;
    return depth_fade * lookat_fade;
}

void SetGridColor(vec3 frag_pos, float scale, float depth) 
{
    vec2 coord = frag_pos.xy / scale; // use the scale variable to set the distance between the lines
    vec2 derivative = fwidth(coord);
    vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
    float line = min(grid.x, grid.y);
    float minimumy = min(derivative.y, 1);
    float minimumx = min(derivative.x, 1);
    vec4 color = vec4(0.3, 0.3, 0.3, 1.0 - min(line, 1.0)); 
    color.a *= ComputeFade(frag_pos, depth);
    if(frag_pos.x < derivative.x * scale && frag_pos.x > -derivative.x * scale)
        color.y = 0.6;
    if(frag_pos.y < derivative.y * scale && frag_pos.y > -derivative.y * scale)
        color.x = 0.6;
    if(color.a != 0) frag_color = color;
}

void main()
{
    float t = -near_point.z / (far_point.z - near_point.z);
    vec3 frag_pos = near_point + t * (far_point - near_point);
    if(t > 0)
    {
        gl_FragDepth = ComputeDepth(frag_pos);
        // float fading = clamp(1 - ComputeFade(frag_pos), 0, 1);
        SetGridColor(frag_pos, 0.1, 20);
        SetGridColor(frag_pos, 1, 200);
        SetGridColor(frag_pos, 10, 450);
        SetGridColor(frag_pos, 100, 500);
        // frag_color.a *= fading;
        if(frag_color.a == 0) discard;
    }
    else
    {
        discard;
    }
}
