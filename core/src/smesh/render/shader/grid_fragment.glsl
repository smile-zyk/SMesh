//infinite grid: see https://asliceofrendering.com/scene%20helper/2020/01/05/InfiniteGrid/
#version 460 core
in vec3 near_point;
in vec3 far_point;

out vec4 frag_color;

uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform vec3 view_position;

vec4 GetGridColor(vec3 frag_pos, float scale) {
    vec2 coord = frag_pos.xy * scale; // use the scale variable to set the distance between the lines
    vec2 derivative = fwidth(coord);
    vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
    float line = min(grid.x, grid.y);
    float minimumy = min(derivative.y, 1);
    float minimumx = min(derivative.x, 1);
    vec4 color = vec4(0.3, 0.3, 0.3, 1.0 - min(line, 1.0));
    // x axis
    if(frag_pos.x > - minimumx / scale && frag_pos.x < minimumx / scale)
        color.x = 1.0;
    // y axis
    if(frag_pos.y > -minimumy / scale && frag_pos.y < minimumy / scale)
        color.y = 1.0;
    return color;
}

float ComputeDepth(vec3 pos)
{
    vec4 clip_space_pos = projection_matrix * view_matrix * vec4(pos.xyz, 1.0);
    float ndc_z = clip_space_pos.z / clip_space_pos.w;
    return ndc_z * 0.5 + 0.5;
}

float ComputeFade(vec3 pos)
{
    vec4 near_view_pos = view_matrix * vec4(near_point, 1.0);
    vec4 far_view_pos = view_matrix * vec4(far_point, 1.0);
    vec4 cur_view_pos = view_matrix * vec4(pos, 1.0);
    return length(cur_view_pos.xyz - view_position) / abs(far_view_pos.z) ; 
}

void main()
{
    float t = -near_point.z / (far_point.z - near_point.z);
    vec3 frag_pos = near_point + t * (far_point - near_point);
    if(t > 0)
    {
        gl_FragDepth = ComputeDepth(frag_pos);
        float fading = clamp(1 - ComputeFade(frag_pos), 0, 1);
        frag_color = GetGridColor(frag_pos, 0.1);
        frag_color.a *= fading;
        if(frag_color.a == 0) discard;
    }
    else
    {
        discard;
    }
}
