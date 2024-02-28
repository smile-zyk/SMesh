#version 460 core
out vec4 frag_color;

in vec3 frag_position;

uniform vec3 view_position;

float get_alpha(float v)
{
    float frac_part = fract(abs(v));
    if(frac_part < 0.005)
    {
        return 1 - smoothstep(0.f, 0.005f, frac_part) ;
    }
    else if(frac_part > 0.995)
    {
        return smoothstep(0.995f, 1.0f, frac_part);
    }
    else
    {
        return 0;
    }
}

float get_position_alpha(vec3 pos)
{
    float alpha_x = get_alpha(pos.x);
    float alpha_y = get_alpha(pos.y);
    return clamp(max(alpha_x, alpha_y), 0, 1);
}

void main()
{
    float alpha = get_position_alpha(frag_position);
    if(alpha == 0) discard;
    frag_color = vec4(0.6, 0.6, 0.6, 0.8 * alpha);
}
