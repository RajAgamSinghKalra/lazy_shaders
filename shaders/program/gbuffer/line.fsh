// File: shaders/program/gbuffers_line.fsh.glsl
#version 330 compatibility
layout(location = 0) out vec4 lineOut;
void main() {
    lineOut = gl_Color;  // use the vertex color (set by the game)
}
