#version 330 core

layout (location = 0) in uvec2 tex_botleft;
layout (location = 1) in uint tex_width;
layout (location = 2) in uint tex_height;
layout (location = 3) in vec2 screen_botleft;
layout (location = 4) in float screen_width;
layout (location = 5) in float screen_height;

out VS_OUT
{
    uvec2 tex_botleft;
    uint tex_width;
    uint tex_height;
    vec2 screen_botleft;
    float screen_width;
    float screen_height;
} vs_out;

void main ()
{
    vs_out.tex_botleft = tex_botleft;
    vs_out.tex_width = tex_width;
    vs_out.tex_height = tex_height;

    vs_out.screen_botleft = screen_botleft;
    vs_out.screen_width = screen_width;
    vs_out.screen_height = screen_height;
}
