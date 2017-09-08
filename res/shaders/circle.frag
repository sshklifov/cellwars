#version 330 core

uniform sampler2D circle;

in GS_OUT
{
    vec2 dst_vec;
    vec3 colour;
} fs_in;

const float width = 0.95;
const float edge = 0.017;

out vec4 colour;

void main ()
{
    float dst = length (fs_in.dst_vec);
    float alpha = 1.0 - smoothstep (width, width + edge, dst);

    colour = vec4 (fs_in.colour, alpha);
}
