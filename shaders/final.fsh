// File: shaders/final.fsh
#version 330 compatibility

in vec2 texCoordOut;
#include "lib/Uniforms.inc"
layout(location = 0) out vec4 fragColor;
#include "program/final.fsh.glsl"
