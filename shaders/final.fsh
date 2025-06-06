// File: shaders/final.fsh
#version 330 compatibility

in vec4 texcoord;
#include "lib/Uniforms.inc"
#include "lib/Common.inc"
layout(location = 0) out vec4 fragColor;
#include "program/final.fsh.glsl"
