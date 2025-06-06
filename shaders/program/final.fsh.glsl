// File: shaders/program/final.fsh.glsl
#extension GL_ARB_gpu_shader5 : enable
#include "../lib/Settings.inc"
#include "../lib/Uniforms.inc"
#include "../lib/Common.inc"
in vec4 texcoord;
vec3 ACESFilm(vec3 x) {
    float a = 2.51;
    float b = 0.03;
    float c = 2.43;
    float d = 0.59;
    float e = 0.14;
    return clamp((x*(a*x+b))/(x*(c*x+d)+e), 0.0, 1.0);
}
void main(){
 vec3 color = texture(colortex0, texcoord.xy).rgb;
 color = ACESFilm(color);
 gl_FragColor = vec4(color, 1.0);
}
