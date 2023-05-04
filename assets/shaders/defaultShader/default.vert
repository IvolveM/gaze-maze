#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 texCoord;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
    vec3 cameraPos;
};

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec3 CameraPos;

uniform mat4 model;

void main()
{
    CameraPos = cameraPos;
    TexCoord = texCoord;
    Normal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model * vec4(pos, 1.0));

    gl_Position = projection * view * model * vec4(pos, 1.0);
}