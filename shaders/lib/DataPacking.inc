// File: shaders/lib/DataPacking.inc
float UnpackHalf(int x){uint u=uint(x);uint e=(u>>10)&0x1F;uint m=u&0x3FF;int s=int(u>>15);float r;if(e==0){r=m*0.00000095367431640625; } else if(e!=31){r=(1.0+ m*0.0009765625)*exp2(int(e)-15); } else {r=m==0?1.0/0.0:0.0/0.0;}return s==1? -r:r;}
vec2 PackFloatToVec2i(float value){uint u=uint(floatBitsToInt(value));uint up=u&0xFFFFu;uint down=(u>>16)&0xFFFFu;return vec2(int(up),int(down));}
float UnpackVec2iToFloat(vec2 v){uint up=uint(v.x)&0xFFFFu;uint down=uint(v.y)&0xFFFFu;return intBitsToFloat(int((down<<16)|up));}
