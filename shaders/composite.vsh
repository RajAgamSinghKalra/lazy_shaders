// File: shaders/composite.vsh
#version 330 compatibility

#extension GL_ARB_explicit_attrib_location : enable
#include "lib/Uniforms.inc"
#include "lib/Common.inc"
layout(location = 0) in vec4 vertex;
layout(location = 2) in vec2 texCoordIn;
out vec2 texCoordOut;

void main() {
    texCoordOut = texCoordIn;
    gl_Position = vertex;
}
