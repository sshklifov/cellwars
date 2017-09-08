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
    vec3 colour;
    vec2 center;
    float rad;
} gs_in[];

out GS_OUT
{
    vec2 dst_vec;
    vec3 colour;
} gs_out;

void main ()
{
    vec3 colour = gs_in[0].colour;
    vec2 center = gs_in[0].center;
    float rad = gs_in[0].rad;
    
    gs_out.colour = colour;

    gl_Position = mvp * vec4 (center.x + rad, center.y - rad, 0.0, 1.0);
    gs_out.dst_vec = vec2 (1.0, -1.0);
    EmitVertex ();

    gl_Position = mvp * vec4 (center.x + rad, center.y + rad, 0.0, 1.0);
    gs_out.dst_vec = vec2 (1.0, 1.0);
    EmitVertex ();

    gl_Position = mvp * vec4 (center.x - rad, center.y - rad, 0.0, 1.0);
    gs_out.dst_vec = vec2 (-1.0, -1.0);
    EmitVertex ();

    gl_Position = mvp * vec4 (center.x - rad, center.y + rad, 0.0, 1.0);
    gs_out.dst_vec = vec2 (-1.0, 1.0);
    EmitVertex ();

    EndPrimitive ();
}
