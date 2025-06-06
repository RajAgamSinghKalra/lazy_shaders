// File: shaders/program/gbuffers_terrain.fsh.glsl
layout(location = 0) out vec4 terrainOut;
in vec4 gbufferCoord;
in vec3 gbufferNormal;
void main(){
 vec2 uv = gl_TexCoord[0].xy;
 float height = texture(terrain_n, uv).a;
 vec3 normSample = texture(terrain_n, uv).rgb * 2.0 - 1.0;
 vec3 normal = normalize(gbufferNormal * normSample);
 vec3 albedo = texture(terrain, uv).rgb;
 float ao = texture(terrain_s, uv).r;
 albedo *= ao;
 terrainOut = vec4(albedo, 1.0);
}
