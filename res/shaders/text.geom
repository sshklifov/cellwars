#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

layout(std140) uniform matrices
{
    mat4 scale;
    mat4 projection;
    mat4 translate;
    mat4 mvp;
};

in VS_OUT
{
    uvec2 tex_botleft;
    uint tex_width;
    uint tex_height;
    vec2 screen_botleft;
    float screen_width;
    float screen_height;
} gs_in[];

out GS_OUT
{
    vec2 tex_coord;
} gs_out;

void main ()
{
    vec2 screen_botleft = gs_in[0].screen_botleft;
    float screen_width = gs_in[0].screen_width;
    float screen_height = gs_in[0].screen_height;

    vec2 tex_botleft = vec2 (gs_in[0].tex_botleft);
    float tex_width = float (gs_in[0].tex_width);
    float tex_height = float (gs_in[0].tex_height);

    gl_Position = projection * vec4 (screen_botleft.x + screen_width, screen_botleft.y, 0.0, 1.0);
    gs_out.tex_coord = vec2 (tex_botleft.x + tex_width, tex_botleft.y);
    EmitVertex ();

    gl_Position = projection * vec4 (screen_botleft.x + screen_width, screen_botleft.y + screen_height, 0.0, 1.0);
    gs_out.tex_coord = vec2 (tex_botleft.x + tex_width, tex_botleft.y + tex_height);
    EmitVertex ();

    gl_Position = projection * vec4 (screen_botleft.x, screen_botleft.y, 0.0, 1.0);
    gs_out.tex_coord = vec2 (tex_botleft.x, tex_botleft.y);
    EmitVertex ();

    gl_Position = projection * vec4 (screen_botleft.x, screen_botleft.y + screen_height, 0.0, 1.0);
    gs_out.tex_coord = vec2 (tex_botleft.x, tex_botleft.y + screen_height);
    EmitVertex ();

    EndPrimitive ();
}
