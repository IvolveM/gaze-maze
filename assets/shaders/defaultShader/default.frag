#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 CameraPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;


uniform Material material;

uniform sampler2D texture0;

void main()
{
    // ambient
    vec3 ambient = light.ambient * material.ambient;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    // specular
    vec3 viewDir = normalize(CameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128.0);
    vec3 specular = light.specular * (spec * material.specular);

    vec4 textureColor = texture(texture0, TexCoord);
    vec3 result = (ambient + diffuse + specular) * textureColor.xyz;
    FragColor = vec4(result, 1.0f);
}