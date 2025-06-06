// File: shaders/composite.fsh
#version 330 compatibility

in vec2 texCoordOut;
flat in vec3 colorSkyUp;
#include "lib/Settings.inc"
#include "lib/Uniforms.inc"
#include "lib/Common.inc"
#include "lib/GBufferData.inc"
vec4 sampleDepth(vec2 uv){return texture(depthtex1, uv);}
#include "program/composite.fsh.glsl"
