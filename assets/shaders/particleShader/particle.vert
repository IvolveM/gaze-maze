#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;


layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
    vec3 viewPos;
};

out vec2 TexCoord;
out vec4 ParticleColor;

uniform mat4 model;

void main()
{
    // make the particle face the player
    mat3 invViewRot = inverse(mat3(view));
    vec3 pos = invViewRot * aPos;
    TexCoord = aTexCoord;
    gl_Position = projection * view * model * vec4(pos, 1.0);
}