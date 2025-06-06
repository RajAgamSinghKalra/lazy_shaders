#define FN__textureGrad textureGrad
#define FN__textureLod textureLod
#define FN__textureProj textureProj
#define H_(X,Y) X##Y
#define FNL(vec4) value=H_(value, vec4).a;
#define FNH(sampler, coord) texture(sampler, fract(coord)*vTexCoordAM.pq+vTexCoordAM.st)
const float FEXHLIYFGIBHWXVCEYIELQVVTJ=1.0;
const float FEXHLIYFGIBHWXVCEYIELQVVTJ_inversed=1.0;
uniform mat4 NrpXplUyhGQ;
uniform mat4 NrpXplUyhGQ_inversed;
uniform vec4 vTexCoordAM;
uniform float uvPixelSize;
float ZhQcMnz(float d, float i){return 1.0-exp(-d*i);}
vec4 CTMtexLod(sampler2D texture, vec2 coord, float lod){return FN__textureLod(texture, fract(coord)*vTexCoordAM.pq+vTexCoordAM.st, lod);}
