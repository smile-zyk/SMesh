// use SolidWireframe: https://developer.download.nvidia.cn/SDK/10/direct3d/Source/SolidWireframe/Doc/SolidWireframe.pdf
#version 460 core
out vec4 frag_color;

in vec3 frag_normal;
in vec3 frag_position;
in vec3 edge_distance;

uniform vec3 view_position;
uniform float line_width;

float min_distance(vec3 dis)
{
    return min(min(dis.x, dis.y), dis.z);
}

float smooth_func(float dis)
{
    return exp2(-2 * dis * dis);
}

void main()
{
    vec3 line_color = vec3(0.f, 0.f, 0.f);
    float min_dis = min_distance(edge_distance);
    vec3 diffuse_color = vec3(0.4f, 0.4f, 0.4f);
    vec3 specular_color = vec3(0.6f, 0.6f, 0.6f);
    vec3 ambient = vec3(0.4f, 0.4f, 0.4f);

    vec3 light_position = view_position;
    vec3 light_diffuse_color = vec3(0.5f, 0.5f, 0.5f);
    vec3 light_specular_color = vec3(0.6f, 0.6f, 0.6f);

    vec3 normal = normalize(frag_normal);
    vec3 light_direction = normalize(light_position - frag_position);
    float diff = max(dot(normal, light_direction), 0.0);
    vec3 diffuse = light_diffuse_color * (diff * diffuse_color);

    vec3 view_direction = normalize(view_position - frag_position);
    vec3 reflect_direction = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), 32.f);
    vec3 specular = light_specular_color * (spec * specular_color);

    vec3 result = ambient + diffuse + specular;
    if(min_dis > 0.5 * line_width + 1)
    {
        frag_color = vec4(result, 1.0);
    }
    else
    {
        float alpha = smooth_func(clamp(min_dis - (0.5 * line_width - 1), 0, 2));
        frag_color = vec4((result * (1 - alpha) + line_color * alpha).xyz, 1.0);
    }
}