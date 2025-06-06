// File: shaders/lib/Materials.inc
// Terrain samplers are provided by the shader loader.
// Do not redeclare them here to avoid conflicts.
vec4 GetTerrainColor(vec2 uv){return texture(terrain,uv);}
