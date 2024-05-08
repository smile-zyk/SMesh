// use SolidWireframe: https://developer.download.nvidia.cn/SDK/10/direct3d/Source/SolidWireframe/Doc/SolidWireframe.pdf
#version 460 core
out vec4 frag_color;

in vec3 frag_normal;
in vec3 frag_position;
in vec3 edge_distance;

uniform bool is_wireframe;
uniform vec3 view_position;
uniform float line_width;

struct Material
{
    vec3 diffuse_color;
    vec3 specular_color;
    float specular_shininess;
};

struct Light
{
    vec3 position;
    vec3 ambient_color;
    vec3 diffuse_color;
    vec3 specular_color;
};

Material material;
Light light;
vec3 line_color = vec3(0.f, 0.f, 0.f);

vec3 CalculateLightColor(Light light, Material material, vec3 frag_position, vec3 frag_normal, vec3 view_position)
{
    vec3 light_direction = normalize(light.position - frag_position);
    float diff = max(dot(frag_normal, light_direction), 0.0);
    vec3 diffuse = light.diffuse_color * (diff * material.diffuse_color);

    vec3 view_direction = normalize(view_position - frag_position);
    vec3 reflect_direction = reflect(-light_direction, frag_normal);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.specular_shininess);
    vec3 specular = light.specular_color * (spec * material.specular_color);

    vec3 result = light.ambient_color + diffuse + specular;
    return result;
}

void main()
{
    material.diffuse_color = vec3(0.4f, 0.4f, 0.4f);
    material.specular_color = vec3(0.4f, 0.4f, 0.4f);
    material.specular_shininess = 8.0f;
    light.position = view_position;
    light.ambient_color = vec3(0.4f, 0.4f, 0.4f);
    light.diffuse_color = vec3(0.4f, 0.4f, 0.4f);
    light.specular_color = vec3(0.4f, 0.4f, 0.4f);
    vec3 result_color = CalculateLightColor(light, material, frag_position, frag_normal, view_position);
    if(is_wireframe)
    {
        vec3 d = fwidth(edge_distance);
        vec3 a3 = smoothstep(vec3(0), d * line_width, edge_distance);
        float alpha = min(min(a3.x, a3.y), a3.z);
        vec3 color = mix(line_color, result_color, alpha);
        frag_color = vec4(color, 1.0);
        return;
    }
    frag_color = vec4(result_color, 1.0);
}