#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 5) in mat4 aInstanceMatrix;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
    vec3 viewPos;
};

out vec3 ViewPos;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    ViewPos = viewPos;
    TexCoord = aTexCoord;
    Normal = mat3(transpose(inverse(aInstanceMatrix))) * aNormal;
    FragPos = vec3(aInstanceMatrix * vec4(aPos, 1.0));

    gl_Position = projection * view * vec4(FragPos, 1.0f); 
}