#version 330 core

uniform sampler2D atlas;

in GS_OUT
{
    vec2 tex_coord;
} fs_in;

out vec4 colour;

const float width = 0.45;
const float edge = 0.1;
const vec3 text_colour = vec3 (0.2, 0.2, 0.2);

void main ()
{
    vec2 tex_size = vec2 (textureSize (atlas, 0));
    vec2 tex_coord = vec2 (fs_in.tex_coord.x / tex_size.x, fs_in.tex_coord.y / tex_size.y);

    float dst = 1.0 - texture (atlas, tex_coord).a;
    float alpha = 1.0 - smoothstep (width, width + edge, dst);

    colour = vec4 (text_colour, alpha);
}
