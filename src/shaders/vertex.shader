#version 330 core

layout (location=0) in vec3 position;
layout (location=1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perProj;

out vec3 fNormal;
out vec3 FragPos;

void main()
{
    gl_Position = perProj * view * model * vec4(position, 1.0);

    // world-space position
    FragPos = vec3(model * vec4(position, 1.0));

    // world-space normal
    fNormal = mat3(transpose(inverse(model))) * normal;
}
