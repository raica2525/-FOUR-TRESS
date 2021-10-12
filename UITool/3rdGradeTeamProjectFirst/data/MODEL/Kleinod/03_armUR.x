xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 64;
 -7.73330;-1.02900;-8.32050;,
 -8.09090;-3.06260;-8.26660;,
 -12.48590;-2.77820;-7.86350;,
 -12.52540;-0.94870;-7.96330;,
 -13.30130;-4.47000;-6.53130;,
 -8.44620;-4.56470;-6.86240;,
 -7.07520;1.33160;-7.94100;,
 -12.46050;1.27180;-7.51920;,
 -6.93950;3.10060;-7.33780;,
 -12.39260;3.18930;-6.80390;,
 -7.37830;1.85410;7.19910;,
 -6.68450;4.25360;5.80520;,
 -12.33130;3.63490;5.67290;,
 -12.83230;1.26440;6.73540;,
 -7.83280;-0.72710;7.96310;,
 -13.01910;-0.79810;7.32550;,
 -6.13460;6.28170;2.69210;,
 -12.00350;5.72420;2.84430;,
 -13.26330;-3.44840;6.59370;,
 -13.52320;-5.47390;3.65090;,
 -8.75210;-5.53910;4.54190;,
 -8.40060;-3.96290;6.88170;,
 -6.20160;6.13510;-0.97430;,
 -12.10480;5.82990;-0.63170;,
 -13.33070;-5.92510;-0.45630;,
 -8.91990;-6.26350;0.19720;,
 -12.18560;5.46520;-3.60450;,
 -6.41030;5.79270;-3.97050;,
 -6.68200;4.61100;-6.09040;,
 -12.36610;4.23080;-5.49820;,
 -4.23690;-1.38260;-7.47780;,
 -4.77270;-3.22970;-7.54160;,
 -4.88980;-4.77500;-6.34840;,
 -3.91690;1.36350;-7.14010;,
 -4.04810;3.20680;-6.69650;,
 -4.44780;1.95640;6.70390;,
 -4.50230;4.85560;5.19160;,
 -4.32450;-0.67660;7.48170;,
 -4.69660;6.22570;2.19380;,
 -4.98570;-5.87530;4.48760;,
 -4.48670;-3.65230;6.44840;,
 -4.55570;6.04810;-1.01120;,
 -5.08070;-6.43380;0.59030;,
 -4.45220;5.54560;-3.76970;,
 -4.21440;4.72620;-5.69440;,
 -8.91990;-6.26350;0.19720;,
 -13.33070;-5.92510;-0.45630;,
 -5.08070;-6.43380;0.59030;,
 -2.54300;6.43310;2.48890;,
 -2.46580;6.30520;-1.21180;,
 -2.18660;5.85260;-4.58890;,
 -1.97640;4.73980;6.03060;,
 -1.67140;4.66060;-6.53750;,
 -1.06060;1.33130;8.08200;,
 -1.06320;2.94440;-7.59180;,
 -0.41080;-2.22560;8.78600;,
 -0.61500;0.89950;-8.17780;,
 0.23680;-5.13550;6.94530;,
 -0.47830;-2.46440;-8.75110;,
 0.06760;-8.91990;5.23710;,
 -0.26160;-4.57940;-8.97550;,
 -0.28630;-8.78520;0.80950;,
 -0.30950;-6.38730;-8.92730;,
 -0.28630;-8.78520;0.80950;;
 
 116;
 3;0,1,2;,
 3;2,3,0;,
 3;4,2,1;,
 3;1,5,4;,
 3;6,0,3;,
 3;3,7,6;,
 3;8,6,7;,
 3;7,9,8;,
 3;10,11,12;,
 3;12,13,10;,
 3;14,10,13;,
 3;13,15,14;,
 3;11,16,17;,
 3;17,12,11;,
 3;18,19,20;,
 3;20,21,18;,
 3;16,22,23;,
 3;23,17,16;,
 3;19,24,25;,
 3;25,20,19;,
 3;26,23,22;,
 3;22,27,26;,
 3;27,28,29;,
 3;29,26,27;,
 3;28,8,9;,
 3;9,29,28;,
 3;21,14,15;,
 3;15,18,21;,
 3;1,0,30;,
 3;30,31,1;,
 3;5,1,31;,
 3;31,32,5;,
 3;0,6,33;,
 3;33,30,0;,
 3;34,33,6;,
 3;6,8,34;,
 3;11,10,35;,
 3;35,36,11;,
 3;37,35,10;,
 3;10,14,37;,
 3;36,38,16;,
 3;16,11,36;,
 3;21,20,39;,
 3;39,40,21;,
 3;38,41,22;,
 3;22,16,38;,
 3;20,25,42;,
 3;42,39,20;,
 3;27,22,41;,
 3;41,43,27;,
 3;43,44,28;,
 3;28,27,43;,
 3;44,34,8;,
 3;8,28,44;,
 3;14,21,40;,
 3;40,37,14;,
 3;4,5,45;,
 3;45,46,4;,
 3;5,32,47;,
 3;47,45,5;,
 3;48,49,41;,
 3;41,38,48;,
 3;41,49,50;,
 3;50,43,41;,
 3;51,48,38;,
 3;38,36,51;,
 3;43,50,52;,
 3;52,44,43;,
 3;53,51,36;,
 3;36,35,53;,
 3;44,52,54;,
 3;54,34,44;,
 3;55,53,35;,
 3;35,37,55;,
 3;34,54,56;,
 3;56,33,34;,
 3;57,55,37;,
 3;37,40,57;,
 3;33,56,58;,
 3;58,30,33;,
 3;59,57,40;,
 3;40,39,59;,
 3;30,58,60;,
 3;60,31,30;,
 3;61,59,39;,
 3;39,42,61;,
 3;31,60,62;,
 3;62,32,31;,
 3;62,63,47;,
 3;47,32,62;,
 3;55,57,53;,
 3;53,57,51;,
 3;57,59,51;,
 3;51,59,48;,
 3;59,61,48;,
 3;48,61,49;,
 3;61,62,49;,
 3;49,62,50;,
 3;50,62,52;,
 3;52,62,54;,
 3;54,62,56;,
 3;56,62,58;,
 3;62,60,58;,
 3;15,13,18;,
 3;13,12,18;,
 3;18,12,19;,
 3;12,17,19;,
 3;19,17,46;,
 3;17,23,46;,
 3;46,23,4;,
 3;23,26,4;,
 3;26,29,4;,
 3;29,9,4;,
 3;4,9,2;,
 3;9,7,2;,
 3;7,3,2;;
 
 MeshMaterialList {
  12;
  116;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.417600;0.439200;0.489600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.009600;0.009600;0.009600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/00_Kleinod/Clothes.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/00_Kleinod/Sabre.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/00_Kleinod/Face.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/00_Kleinod/Hair.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/00_Kleinod/FaceBrow.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/00_Kleinod/FaceEyeline.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/00_Kleinod/FaceEyelash.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/00_Kleinod/EyeWhite.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/00_Kleinod/EyeIris.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/00_Kleinod/Weapon.png";
   }
  }
 }
 MeshNormals {
  90;
  0.080717;0.037850;-0.996018;,
  0.052378;-0.366598;-0.928904;,
  -0.096599;-0.224347;-0.969710;,
  -0.075193;0.107105;-0.991400;,
  -0.066031;-0.844566;-0.531364;,
  0.009909;-0.857366;-0.514612;,
  0.076065;0.225985;-0.971156;,
  -0.080771;0.292616;-0.952813;,
  0.038143;0.476793;-0.878188;,
  -0.091023;0.605058;-0.790961;,
  0.016317;0.381930;0.924047;,
  -0.013007;0.678726;0.734276;,
  -0.102687;0.597229;0.795470;,
  -0.119019;0.337729;0.933688;,
  0.007765;-0.021023;0.999749;,
  -0.109818;-0.094027;0.989494;,
  -0.016863;0.968753;0.247456;,
  -0.090387;0.912807;0.398264;,
  -0.113245;-0.663985;0.739121;,
  -0.086707;-0.953845;0.287509;,
  -0.084424;-0.924302;0.372207;,
  -0.020755;-0.562412;0.826597;,
  -0.008178;0.996774;-0.079839;,
  -0.068717;0.996749;-0.042064;,
  -0.066731;-0.995640;-0.065172;,
  -0.049380;-0.997748;-0.045381;,
  -0.069274;0.962600;-0.261920;,
  0.016501;0.945176;-0.326145;,
  -0.002577;0.800213;-0.599710;,
  -0.102232;0.832293;-0.544827;,
  -0.029313;0.056669;-0.997963;,
  -0.133619;-0.319260;-0.938200;,
  -0.256179;-0.809551;-0.528204;,
  -0.017291;0.160378;-0.986904;,
  -0.024255;0.354098;-0.934894;,
  -0.073729;0.351923;0.933121;,
  -0.074111;0.709293;0.701007;,
  -0.081593;-0.068846;0.994285;,
  -0.014085;0.981242;0.192266;,
  -0.257114;-0.869452;0.421836;,
  -0.077796;-0.447778;0.890754;,
  -0.043516;0.992984;-0.109954;,
  -0.220389;-0.973048;-0.067875;,
  -0.050153;0.925078;-0.376452;,
  -0.054508;0.696862;-0.715131;,
  -0.123368;0.985066;0.120103;,
  -0.130096;0.987423;-0.089834;,
  -0.217399;0.928655;-0.300562;,
  -0.177437;0.779190;0.601149;,
  -0.239898;0.736732;-0.632198;,
  -0.299390;0.339381;0.891732;,
  -0.249131;0.392910;-0.885187;,
  -0.366041;-0.057685;0.928809;,
  -0.269233;0.190042;-0.944139;,
  -0.293042;-0.424358;0.856765;,
  -0.286072;0.123275;-0.950245;,
  -0.434461;-0.665614;0.606796;,
  -0.293826;0.054832;-0.954285;,
  -0.465771;-0.884653;-0.021136;,
  -0.488819;-0.642991;-0.589592;,
  0.980939;0.188524;0.047085;,
  0.968333;0.189833;-0.162160;,
  0.979630;0.199898;-0.019118;,
  0.962641;0.176195;-0.205613;,
  0.966706;0.157243;-0.201876;,
  0.987431;0.150662;-0.047769;,
  0.988800;0.149023;-0.008178;,
  0.989360;0.140425;0.038039;,
  0.942728;0.052859;0.329347;,
  0.985065;0.101864;0.138820;,
  0.931526;0.036563;0.361831;,
  0.797856;-0.021779;0.602455;,
  0.930780;0.001421;0.365578;,
  0.929847;0.023518;0.367194;,
  0.717316;-0.000429;0.696748;,
  -0.995848;0.090990;0.002782;,
  -0.988247;0.094003;-0.120550;,
  -0.991030;0.106309;-0.080984;,
  -0.988868;0.120447;-0.087369;,
  -0.991007;0.131185;-0.026368;,
  -0.992348;0.122561;-0.014979;,
  -0.993614;0.112799;-0.002811;,
  -0.994203;0.105240;0.022020;,
  -0.990267;0.105968;-0.090237;,
  -0.994197;0.105601;0.020519;,
  -0.993744;0.109451;-0.022231;,
  -0.987892;0.069794;-0.138559;,
  -0.998498;0.027168;-0.047587;,
  -0.988909;-0.006412;0.148383;,
  -0.980595;-0.010493;0.195766;;
  116;
  3;0,1,2;,
  3;2,3,0;,
  3;4,2,1;,
  3;1,5,4;,
  3;6,0,3;,
  3;3,7,6;,
  3;8,6,7;,
  3;7,9,8;,
  3;10,11,12;,
  3;12,13,10;,
  3;14,10,13;,
  3;13,15,14;,
  3;11,16,17;,
  3;17,12,11;,
  3;18,19,20;,
  3;20,21,18;,
  3;16,22,23;,
  3;23,17,16;,
  3;19,24,25;,
  3;25,20,19;,
  3;26,23,22;,
  3;22,27,26;,
  3;27,28,29;,
  3;29,26,27;,
  3;28,8,9;,
  3;9,29,28;,
  3;21,14,15;,
  3;15,18,21;,
  3;1,0,30;,
  3;30,31,1;,
  3;5,1,31;,
  3;31,32,5;,
  3;0,6,33;,
  3;33,30,0;,
  3;34,33,6;,
  3;6,8,34;,
  3;11,10,35;,
  3;35,36,11;,
  3;37,35,10;,
  3;10,14,37;,
  3;36,38,16;,
  3;16,11,36;,
  3;21,20,39;,
  3;39,40,21;,
  3;38,41,22;,
  3;22,16,38;,
  3;20,25,42;,
  3;42,39,20;,
  3;27,22,41;,
  3;41,43,27;,
  3;43,44,28;,
  3;28,27,43;,
  3;44,34,8;,
  3;8,28,44;,
  3;14,21,40;,
  3;40,37,14;,
  3;4,5,25;,
  3;25,24,4;,
  3;5,32,42;,
  3;42,25,5;,
  3;45,46,41;,
  3;41,38,45;,
  3;41,46,47;,
  3;47,43,41;,
  3;48,45,38;,
  3;38,36,48;,
  3;43,47,49;,
  3;49,44,43;,
  3;50,48,36;,
  3;36,35,50;,
  3;44,49,51;,
  3;51,34,44;,
  3;52,50,35;,
  3;35,37,52;,
  3;34,51,53;,
  3;53,33,34;,
  3;54,52,37;,
  3;37,40,54;,
  3;33,53,55;,
  3;55,30,33;,
  3;56,54,40;,
  3;40,39,56;,
  3;30,55,57;,
  3;57,31,30;,
  3;58,56,39;,
  3;39,42,58;,
  3;31,57,59;,
  3;59,32,31;,
  3;59,58,42;,
  3;42,32,59;,
  3;60,61,62;,
  3;62,61,63;,
  3;61,64,63;,
  3;63,64,65;,
  3;64,66,65;,
  3;65,66,67;,
  3;66,68,67;,
  3;67,68,69;,
  3;69,68,70;,
  3;70,68,71;,
  3;71,68,72;,
  3;72,68,73;,
  3;68,74,73;,
  3;75,76,77;,
  3;76,78,77;,
  3;77,78,79;,
  3;78,80,79;,
  3;79,80,81;,
  3;80,82,81;,
  3;81,82,83;,
  3;82,84,83;,
  3;84,85,83;,
  3;85,86,83;,
  3;83,86,87;,
  3;86,88,87;,
  3;88,89,87;;
 }
 MeshTextureCoords {
  64;
  0.452170;0.046830;,
  0.446390;0.048770;,
  0.447210;0.059820;,
  0.452340;0.059150;,
  0.442190;0.060670;,
  0.439990;0.052680;,
  0.458020;0.045620;,
  0.457790;0.058960;,
  0.462960;0.045260;,
  0.462500;0.058790;,
  0.499140;0.046880;,
  0.494340;0.045660;,
  0.495750;0.059470;,
  0.499250;0.061190;,
  0.501990;0.047130;,
  0.501980;0.061920;,
  0.486620;0.044480;,
  0.487650;0.058540;,
  0.509800;0.061380;,
  0.518220;0.062620;,
  0.517890;0.051620;,
  0.510000;0.049490;,
  0.478940;0.044770;,
  0.479290;0.058540;,
  0.529020;0.063220;,
  0.528390;0.055280;,
  0.472050;0.058540;,
  0.472510;0.044950;,
  0.467540;0.045160;,
  0.466790;0.058860;,
  0.450990;0.041490;,
  0.444430;0.043670;,
  0.435980;0.048180;,
  0.459160;0.039280;,
  0.463750;0.038720;,
  0.498490;0.040630;,
  0.493320;0.039420;,
  0.503320;0.042850;,
  0.485620;0.038480;,
  0.519900;0.047230;,
  0.512800;0.044720;,
  0.478910;0.038520;,
  0.528900;0.051480;,
  0.473000;0.037880;,
  0.467750;0.038440;,
  0.426100;0.057470;,
  0.425850;0.063810;,
  0.424160;0.052500;,
  0.485720;0.033840;,
  0.478900;0.033770;,
  0.472460;0.033110;,
  0.494070;0.034690;,
  0.467370;0.033650;,
  0.501880;0.036670;,
  0.463390;0.034380;,
  0.504950;0.038590;,
  0.458610;0.035290;,
  0.515740;0.041640;,
  0.449860;0.037750;,
  0.523180;0.044250;,
  0.443980;0.038860;,
  0.529500;0.048340;,
  0.433590;0.044180;,
  0.423300;0.048720;;
 }
}
