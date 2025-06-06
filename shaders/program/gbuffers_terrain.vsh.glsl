// File: shaders/program/gbuffers_terrain.vsh.glsl
#version 330 compatibility
layout(location = 0) in vec4 position;
layout(location = 8) in vec2 texCoord;
out vec4 gbufferCoord;
out vec3 gbufferNormal;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;
void main(){
 gl_Position = projectionMatrix * modelViewMatrix * position;
 gbufferCoord = gl_Position;
 gbufferNormal = normalize(normalMatrix * vec3(0.0, 0.0, 1.0));
}
