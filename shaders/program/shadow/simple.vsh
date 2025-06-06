// File: shaders/program/shadow.vsh.glsl
layout(location = 0) in vec4 position;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
void main(){
 gl_Position=projectionMatrix * modelViewMatrix * position;
}
