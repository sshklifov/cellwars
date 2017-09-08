#version 330 core

layout(location = 0) in vec3 colour;
layout(location = 1) in vec2 center;
layout(location = 2) in float rad;

out VS_OUT
{
    vec3 colour;
    vec2 center;
    float rad;
} vs_out;

void main()
{
    vs_out.colour = colour;
    vs_out.center = center;
    vs_out.rad = rad;
}

