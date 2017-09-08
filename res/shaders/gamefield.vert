#version 330 core

layout (location = 0) in vec2 pos;

layout(std140) uniform matrices
{
    mat4 scale;
    mat4 projection;
    mat4 translate;
    mat4 mvp;
};

void main ()
{
    gl_Position = mvp * vec4 (pos, 0.0, 1.0);
}
