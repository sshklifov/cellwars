#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 10) out;

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
    vec3 colour;
} gs_out;

void main ()
{
    vec3 colour = gs_in[0].colour;
    vec2 center = gs_in[0].center;
    float rad = gs_in[0].rad;

    gs_out.colour = colour;

    float segment = 2.0 * 3.1415926 / 6.0;
    vec2 vertex = vec2 (rad, 0.0);

    for (int i = 1; i < 6; i += 3)
    {
        float theta1 = segment * (i + 0);
        float theta2 = segment * (i + 1);
        float theta3 = segment * (i + 2);

        gl_Position = mvp * vec4 (center + vertex, 0.0, 1.0);
        EmitVertex ();

        vertex = vec2 (cos (theta1) * rad, sin (theta1) * rad);
        gl_Position = mvp * vec4 (center + vertex, 0.0, 1.0);
        EmitVertex ();

        gl_Position = mvp * vec4 (center, 0.0, 1.0);
        EmitVertex ();

        vertex = vec2 (cos (theta2) * rad, sin (theta2) * rad);
        gl_Position = mvp * vec4 (center + vertex, 0.0, 1.0);
        EmitVertex ();

        vertex = vec2 (cos (theta3) * rad, sin (theta3) * rad);
        gl_Position = mvp * vec4 (center + vertex, 0.0, 1.0);
        EmitVertex ();

        EndPrimitive ();
    }
}
