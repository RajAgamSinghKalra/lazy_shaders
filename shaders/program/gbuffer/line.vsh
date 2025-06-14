// File: shaders/program/gbuffers_line.vsh.glsl
void main() {
    // Transform the fixed-function vertex (gl_Vertex) by the modelview and projection matrices
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
}
