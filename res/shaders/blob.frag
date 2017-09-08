#version 330 core

in GS_OUT
{
    vec3 colour;
} fs_in;

out vec4 colour;

void main()
{
    colour = vec4 (fs_in.colour, 1.0);
}
