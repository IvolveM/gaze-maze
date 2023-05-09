#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout(location = 5) in ivec4 aBoneIds; 
layout(location = 6) in vec4 aWeights;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
    vec3 viewPos;
};

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

out vec3 ViewPos;
out vec3 Normal;
out vec2 TexCoord;
out vec3 FragPos;

uniform mat4 model;

void main()
{

    vec4 totalPosition = vec4(0.0f);
    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    {
        if(aBoneIds[i] == -1) 
            continue;
        if(aBoneIds[i] >=MAX_BONES) 
        {
            totalPosition = vec4(aPos,1.0f);
            break;
        }
        vec4 localPosition = finalBonesMatrices[aBoneIds[i]] * vec4(aPos,1.0f);
        totalPosition += localPosition * aWeights[i];
        vec3 localNormal = mat3(finalBonesMatrices[aBoneIds[i]]) * aNormal;
    }

    ViewPos = viewPos;
    TexCoord = aTexCoord;
    Normal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));

    gl_Position = projection * view * model * totalPosition;
}