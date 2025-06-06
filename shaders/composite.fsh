// File: shaders/composite.fsh
#version 330 compatibility

in vec4 texcoord;
flat in vec3 colorSkyUp;
#include "lib/Settings.inc"
#include "lib/Uniforms.inc"
#include "lib/Common.inc"
#include "lib/Materials.inc"
#include "lib/GBufferData.inc"
layout(location = 0) out vec3 FragColor0;
layout(location = 1) out vec3 FragColor1;
layout(location = 2) out vec3 FragColor2;
layout(location = 3) out vec3 FragColor3;
vec4 sampleDepth(vec2 uv){return texture(depthtex1, uv);}
#include "program/composite.fsh.glsl"
