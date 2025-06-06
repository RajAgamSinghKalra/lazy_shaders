// File: shaders/program/gbuffers_terrain.gsh.glsl
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
in vec4 gbufferCoordIn[];
in vec3 gbufferNormalIn[];
out vec4 gbufferCoord;
out vec3 gbufferNormal;
void main(){
 for(int i=0;i<gl_in.length();i++){
  gl_Position=gl_in[i].gl_Position;
  gbufferCoord=gl_in[i].gl_Position;
  gbufferNormal=normalize(mat3(gbufferModelViewInverse)*gl_in[i].gl_Position.xyz);
  EmitVertex();
 }
 EndPrimitive();
}
