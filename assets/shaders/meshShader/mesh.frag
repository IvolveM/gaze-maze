#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 CameraPos;

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_diffuse3;
    sampler2D texture_specular1;
    sampler2D texture_specular2;
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

void main()
{
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoord));

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoord));

    // specular
    vec3 viewDir = normalize(CameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128.0);
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoord));

    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0f);
}