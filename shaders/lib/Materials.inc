// File: shaders/lib/Materials.inc
// Terrain samplers are defined in Uniforms.inc.
// Avoid redeclaration when this file is included after Uniforms.inc.
#ifndef LAZY_TERRAIN_SAMPLERS_DEFINED
#define LAZY_TERRAIN_SAMPLERS_DEFINED
uniform sampler2D terrain;
uniform sampler2D terrain_n;
uniform sampler2D terrain_s;
#endif
vec4 GetTerrainColor(vec2 uv){return texture(terrain,uv);}
