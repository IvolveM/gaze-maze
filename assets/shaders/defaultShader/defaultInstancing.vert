#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormalCoord;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in mat4 aInstanceMatrix;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
    vec3 cameraPos;
};

out vec3 CameraPos;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    CameraPos = cameraPos;
    TexCoord = aTexCoord;
    Normal = mat3(transpose(inverse(aInstanceMatrix))) * aNormalCoord;
    FragPos = vec3(aInstanceMatrix * vec4(aPos, 1.0));

    gl_Position = projection * view * vec4(FragPos, 1.0f); 
}