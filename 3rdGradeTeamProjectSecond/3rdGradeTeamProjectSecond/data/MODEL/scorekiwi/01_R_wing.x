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
 79;
 -5.11441;11.93807;-25.98166;,
 -1.48941;-0.58714;-23.18866;,
 -6.33911;-3.90993;-26.13946;,
 -5.11441;11.93807;-25.98166;,
 0.29329;8.22396;-18.24126;,
 -5.11441;11.93807;-25.98166;,
 -2.03511;17.36168;-14.19496;,
 -5.11441;11.93807;-25.98166;,
 -7.11081;21.47316;-13.42036;,
 -5.11441;11.93807;-25.98166;,
 -11.96050;18.15026;-16.37116;,
 -5.11441;11.93807;-25.98166;,
 -13.74320;9.33928;-21.31866;,
 -5.11441;11.93807;-25.98166;,
 -11.41471;0.20156;-25.36476;,
 -5.11441;11.93807;-25.98166;,
 -6.33911;-3.90993;-26.13946;,
 -1.63740;-17.51864;-8.41687;,
 -10.59840;-23.65884;-13.86895;,
 1.65699;-1.23784;0.72483;,
 -2.64570;15.64638;8.20114;,
 -12.02441;23.24367;9.63223;,
 -20.98542;17.10338;4.18034;,
 -24.27959;0.82296;-4.96155;,
 -19.97712;-16.06145;-12.43785;,
 -10.59840;-23.65884;-13.86895;,
 -5.53550;-36.27875;16.08403;,
 -17.24372;-44.30115;8.96043;,
 -1.23150;-15.00674;28.02844;,
 -6.85301;7.05336;37.79653;,
 -19.10691;16.97966;39.66653;,
 -30.81531;8.95726;32.54293;,
 -35.11911;-12.31435;20.59863;,
 -29.49779;-34.37476;10.83044;,
 -17.24372;-44.30115;8.96043;,
 -12.59060;-54.01105;46.58464;,
 -25.26360;-62.69444;38.87404;,
 -7.93211;-30.98654;59.51302;,
 -14.01661;-7.10893;70.08595;,
 -27.28038;3.63527;72.10995;,
 -39.95319;-5.04802;64.39952;,
 -44.61179;-28.07245;51.47113;,
 -38.52719;-51.95035;40.89804;,
 -25.26360;-62.69444;38.87404;,
 -21.72880;-68.01645;78.44101;,
 -33.43701;-76.03896;71.31755;,
 -17.42490;-46.74475;90.38530;,
 -23.04619;-24.68423;100.15359;,
 -35.30029;-14.75793;102.02345;,
 -47.00853;-22.78045;94.90004;,
 -51.31252;-44.05225;82.95560;,
 -45.69101;-66.11255;73.18753;,
 -33.43701;-76.03896;71.31755;,
 -31.55859;-76.16264;106.80377;,
 -40.51950;-82.30264;101.35158;,
 -28.26418;-59.88194;115.94568;,
 -32.56689;-42.99774;123.42189;,
 -41.94559;-35.40036;124.85309;,
 -50.90660;-41.54056;119.40097;,
 -54.20082;-57.82115;110.25909;,
 -49.89830;-74.70534;102.78296;,
 -40.51950;-82.30264;101.35158;,
 -40.58340;-77.20924;127.35477;,
 -45.43311;-80.53224;124.40399;,
 -38.80060;-68.39813;132.30228;,
 -41.12921;-59.26045;136.34857;,
 -46.20482;-55.14874;137.12308;,
 -51.05461;-58.47176;134.17239;,
 -52.83711;-67.28285;129.22498;,
 -50.50893;-76.42065;125.17877;,
 -45.43311;-80.53224;124.40399;,
 -47.42961;-70.99713;136.96558;,
 -47.42961;-70.99713;136.96558;,
 -47.42961;-70.99713;136.96558;,
 -47.42961;-70.99713;136.96558;,
 -47.42961;-70.99713;136.96558;,
 -47.42961;-70.99713;136.96558;,
 -47.42961;-70.99713;136.96558;,
 -47.42961;-70.99713;136.96558;;
 
 64;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;36,35,44,45;,
 4;35,37,46,44;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;45,44,53,54;,
 4;44,46,55,53;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;54,53,62,63;,
 4;53,55,64,62;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 3;63,62,71;,
 3;62,64,72;,
 3;64,65,73;,
 3;65,66,74;,
 3;66,67,75;,
 3;67,68,76;,
 3;68,69,77;,
 3;69,70,78;;
 
 MeshMaterialList {
  4;
  64;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\scorekiwi\\color_kiwi_01.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\scorekiwi\\color_kiwi_02.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\scorekiwi\\color_kiwi_03.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\scorekiwi\\color_black.jpg";
   }
  }
 }
 MeshNormals {
  72;
  0.731833;0.322949;-0.600103;,
  0.185992;-0.267737;-0.945370;,
  0.819244;-0.140823;-0.555885;,
  0.950617;0.161657;-0.264943;,
  0.797662;0.568880;-0.200278;,
  0.149711;0.925701;-0.347367;,
  -0.546350;0.675668;-0.494949;,
  -0.718008;0.294238;-0.630784;,
  -0.524782;-0.034032;-0.850556;,
  0.675394;-0.567305;-0.471177;,
  0.878098;-0.385635;-0.283247;,
  0.999520;0.017608;0.025509;,
  0.851178;0.499766;0.160405;,
  0.635374;0.748886;0.188332;,
  -0.754765;0.627362;-0.191693;,
  -0.904370;0.168881;-0.391910;,
  -0.727846;-0.258034;-0.635342;,
  0.660910;-0.676998;-0.323839;,
  0.866821;-0.475909;-0.148765;,
  0.989724;-0.038860;0.137613;,
  0.838804;0.445509;0.312936;,
  0.619169;0.695782;0.364029;,
  -0.815279;0.576931;-0.049717;,
  -0.950716;0.115315;-0.287821;,
  -0.787263;-0.344486;-0.511416;,
  0.636857;-0.741288;-0.211909;,
  0.846137;-0.530585;-0.050320;,
  0.973870;-0.077378;0.213519;,
  0.817891;0.398373;0.415154;,
  0.594752;0.643435;0.481936;,
  -0.846136;0.530586;0.050321;,
  -0.973870;0.077378;-0.213518;,
  -0.817892;-0.398371;-0.415154;,
  0.601829;-0.792794;-0.096328;,
  0.815279;-0.576930;0.049717;,
  0.950716;-0.115315;0.287821;,
  0.787262;0.344488;0.511417;,
  0.560084;0.579990;0.591538;,
  -0.866821;0.475910;0.148765;,
  -0.989724;0.038861;-0.137612;,
  -0.838806;-0.445508;-0.312934;,
  0.535290;-0.841899;0.068335;,
  0.754763;-0.627365;0.191693;,
  0.904369;-0.168881;0.391912;,
  0.727843;0.258036;0.635345;,
  0.495272;0.474290;0.727843;,
  -0.878100;0.385630;0.283248;,
  -0.999520;-0.017609;-0.025505;,
  -0.851181;-0.499763;-0.160401;,
  0.048615;-0.882438;0.467910;,
  0.546356;-0.675667;0.494944;,
  0.718011;-0.294239;0.630780;,
  0.524778;0.034036;0.850558;,
  0.017066;0.155036;0.987761;,
  -0.819247;0.140823;0.555881;,
  -0.950621;-0.161650;0.264932;,
  -0.797668;-0.568872;0.200275;,
  0.358107;-0.409548;0.839065;,
  -0.358097;0.409551;-0.839068;,
  -0.535293;0.841898;-0.068334;,
  -0.495275;-0.474291;-0.727840;,
  -0.601828;0.792795;0.096329;,
  -0.560087;-0.579987;-0.591538;,
  -0.636855;0.741290;0.211909;,
  -0.594754;-0.643432;-0.481936;,
  -0.660910;0.676999;0.323838;,
  -0.619171;-0.695782;-0.364027;,
  -0.675394;0.567304;0.471179;,
  -0.635375;-0.748886;-0.188331;,
  -0.672880;0.489649;0.554506;,
  -0.634609;-0.769068;-0.076204;,
  -0.731842;-0.322942;0.600096;;
  64;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;58,6,5;,
  3;58,7,6;,
  3;58,8,7;,
  3;58,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,59;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,60,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;59,14,22,61;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,60,62,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;61,22,30,63;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,62,64,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;63,30,38,65;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,64,66,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;65,38,46,67;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,66,68,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;67,46,54,69;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,68,70,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,71;,
  3;54,55,71;,
  3;55,56,71;,
  3;56,49,71;;
 }
 MeshTextureCoords {
  79;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
