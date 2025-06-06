// File: shaders/lib/Common.inc
#include "DataPacking.inc"
#include "TAA.inc"

#define SKYLIGHT_BRIGHTNESS 1.0
#define MOON_BRIGHTNESS 1.0
#define SUNLIGHT_RED 1.15
#define SUNLIGHT_GREEN 1.0
#define SUNLIGHT_BLUE 0.85
#define NIGHT_RED 0.44
#define NIGHT_GREEN 0.47
#define NIGHT_BLUE 0.5
#define UNDERWATER_BLUE 1.2
#define UNDERWATER_GREEN 1.1
#define TORCH_RED 1.0
#define TORCH_GREEN 0.85
#define TORCH_BLUE 0.6
#define TORCH_FLAME_SIZE 6.0

#define CUMULUS_CLOUD_DENSITY 1.0
#define CUMULUS_CLOUD_COLOR 1.0
#define CUMULUS_CLOUD_BRIGHTNESS 1.0
#define CIRRUS_CLOUD_DENSITY 1.0
#define CIRRUS_CLOUD_COLOR 1.0
#define CLOUD_HEIGHT 128.0

#define RAIN_STRENGTH_MIN 0.3
#define RAIN_STRENGTH_MAX 0.6
#define RAIN_NIGHT_FACTOR 0.5
#define RAIN_LIGHT_RED 1.0
#define RAIN_LIGHT_GREEN 1.0
#define RAIN_LIGHT_BLUE 1.0

#define DOF_FAR_BLUR_CURVE 1.0

#define WAVING_HAND_STRENGTH 1.0

#define WHITE_FOG_DISTANCE 100000.0

const vec3 LUMINANCE_VECTOR=vec3(0.2126,0.7152,0.0722);

#include "GBuffersCommon.inc"
#include "Materials.inc"
#include "PhysicsOcean.inc"

vec3 g_Glow;
vec3 g_HandLight;
vec3 g_Ambient;
vec3 g_LocalDiffuse;
vec3 g_LocalSpecular;

float g_rainStrength;

vec2 g_NoiseCoords;
vec2 g_NoiseCoords2;

vec2 s(vec3 v){ivec2 m=ivec2(viewWidth,viewHeight);vec3 i=floor(v.xzy+1e-05);i.x+=i.z*altRTDiameter;vec2 r;r.x=mod(i.x,m.x);r.y=i.y+floor(i.x/m.x)*altRTDiameter;r+=.5;r/=m;return r;}
vec2 d(vec3 v){v=clamp(v,vec3(0.),vec3(RAY_TRACING_DIAMETER-1.0));v.x+=v.y*RAY_TRACING_DIAMETER;v.y=v.z+floor(v.x/RAY_TRACING_RESOLUTION)*RAY_TRACING_DIAMETER;v.x=mod(v.x,RAY_TRACING_RESOLUTION);return v.xy/vec2(RAY_TRACING_RESOLUTION,float(altRTDiameter*altRTDiameter));}

float CloudShadow(vec3 worldPos, vec3 lightDir)
{
 vec3 pos=lightDir*(940.0-cameraPosition.y+worldPos.y)/(lightDir.y+1e-5)+worldPos+cameraPosition;
 float cloudDist=length(pos.xz)*0.0016;
 float c=texture2D(noise2D, pos.xz*0.0015625).r;
 return mix(1.0, 0.6, smoothstep(0.0,1.0,c+cloudDist));
}

vec4 CloudColorCirrus(vec3 pos, vec3 worldDir, vec3 worldLightVector, vec3 colorSkyUp, vec3 atmosphere, bool detail, float LdotV, float LdotV2, float dist)
{
 #ifndef CIRRUS_CLOUDS
 return vec4(0.0);
 #endif
 float cloudDensity=CIRRUS_CLOUD_DENSITY;
 float cloudFade=max((1.0-abs(worldDir.y))*1.25-0.25,0.0);
 vec4 result=vec4(0.0);
 result.rgb=cloudFade*colorSkyUp*cloudDensity;
 result.a=cloudFade*cloudDensity;
 return result;
}

vec4 CloudColor(vec3 pos, vec3 worldDir, vec3 worldLightVector, vec3 colorSkyUp,
 vec3 atmosphere, bool detail, float LdotV, float LdotV2, float dist)
{
 #ifndef CUMULUS_CLOUDS
 return vec4(0.0);
 #endif
 float perturbNoise=2.0;
 if(detail){
  vec3 ppos=worldDir+texture(noise2D, worldDir.xz*0.05).r*0.02-vec3(frameTimeCounter*0.0075,0,0);
  perturbNoise=(1.0-texture(noise2D, ppos.xz*0.25).r)*2.0/(1.0+dist*0.0002);
  perturbNoise+=(1.0-texture(noise2D, ppos.xz*0.5).r)/(1.0+dist*0.00001);
  perturbNoise+=(1.0-texture(noise2D, ppos.xz*1.0).r)*0.5/(1.0+dist*0.00005);
  perturbNoise+=(1.0-texture(noise2D, ppos.xz*2.0).r)*0.25/(1.0+dist*0.000025);
 }
 perturbNoise*=dist*0.0018+1.2;
 float cloudDensity=CUMULUS_CLOUD_DENSITY;
 float baseHeight=texture(noise2D, pos.xz*0.0015625).r;
 float height=pos.y*0.002;
 float fade=max((1.0-abs(worldDir.y))*1.25-0.25,0.0);
 float cloudAmount=cloudDensity*smoothstep(-0.025,0.025,baseHeight-height*perturbNoise);
 vec3 cloudColor=vec3(1.0)*CUMULUS_CLOUD_COLOR;
 float light=dot(worldLightVector,worldDir)*0.5+0.5;
 vec3 c=cloudColor*mix(colorSkyUp,vec3(1.0),0.25+0.75*light);
 return vec4(c*cloudAmount*fade,cloudAmount*fade);
}

void CloudPlane(inout vec3 color, vec3 positionOffset, vec3 worldVector, vec3 worldLightVector, vec3 worldSunVector, vec3 colorSunlight,
 vec3 colorSkyUp, vec3 atmosphere, float timeMidnight, bool detail)
{
 vec3 worldVectorNormalized=normalize(worldVector);
 Ray viewRay=MakeRay(positionOffset, worldVectorNormalized);
 Intersection i=RayPlaneIntersectionWorld(viewRay);
 if(i.angle<0.0){
  float LdotV=dot(worldLightVector,-worldVector);
  float LdotV2=LdotV*LdotV+1.0;
  float dist=length(i.pos.xz-cameraPosition.xz);
  vec4 cirrusCloud=CloudColorCirrus(i.pos.xyz, worldVector, worldLightVector, colorSkyUp, atmosphere, detail, LdotV, LdotV2, dist);
  vec4 cloudSample=CloudColor(i.pos.xyz, worldVector, worldLightVector, colorSkyUp, atmosphere, detail, LdotV, LdotV2, dist);
  float atmosphereDist=i.dist*0.0075*CUMULUS_CLOUD_BRIGHTNESS;
  worldVector=-worldVector;
  worldVectorNormalized=-worldVectorNormalized;
  vec3 absorb=AtmosphereAbsorption(worldVector, atmosphereDist);
  cloudSample.rgb*=absorb;
  cirrusCloud.rgb*=absorb;
  vec3 atmos=vec3(0.0);
  if(detail){
   float atmosphereLdotV=dot(worldVectorNormalized, worldSunVector);
   float atmosphereLdotV2=atmosphereLdotV*atmosphereLdotV+1.0;
   atmos=Atmosphere(worldVectorNormalized, worldSunVector,0.25, atmosphereDist, atmosphereLdotV, atmosphereLdotV2);
   atmos+=Atmosphere(worldVectorNormalized, -worldSunVector,0.25, atmosphereDist, -atmosphereLdotV, atmosphereLdotV2)*nightBrightness;
  } else {
   atmos=atmosphere*(1.0-pow(saturate(worldVector.y)+0.001,0.4))+Rayleigh*0.5*SUNLIGHT_BRIGHTNESS*colorSunlight*(1.0-wetness);
  }
  cirrusCloud.rgb+=atmos;
  cloudSample.rgb+=atmos;
  cloudSample.rgb=DoNightEyeAtNight(cloudSample.rgb,timeMidnight);
  cirrusCloud.rgb=DoNightEyeAtNight(cirrusCloud.rgb,timeMidnight);
  color.rgb=mix(color.rgb, cirrusCloud.rgb, cirrusCloud.a);
  color.rgb=mix(color.rgb, cloudSample.rgb, cloudSample.a);
 }
}
