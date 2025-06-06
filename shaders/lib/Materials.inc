// File: shaders/lib/Materials.inc
uniform sampler2D terrain;
uniform sampler2D terrain_n;
uniform sampler2D terrain_s;
vec4 GetTerrainColor(vec2 uv){return texture(terrain,uv);}
