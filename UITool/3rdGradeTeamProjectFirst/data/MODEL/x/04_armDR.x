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
 162;
 -50.14589;12.76752;5.59555;,
 -53.25035;12.76752;3.34005;,
 -56.56972;12.76752;5.75155;,
 -51.41359;12.76752;9.49765;,
 -46.30829;12.76752;5.59555;,
 -45.04049;12.76752;9.49765;,
 -43.20369;12.76752;3.34005;,
 -39.88439;12.76752;5.75155;,
 -42.01799;12.76752;-0.30965;,
 -37.91489;12.76752;-0.30965;,
 -43.20369;12.76752;-3.95925;,
 -39.88439;12.76752;-6.37095;,
 -46.30829;12.76752;-6.21495;,
 -45.04049;12.76752;-10.11705;,
 -50.14589;12.76752;-6.21495;,
 -51.41359;12.76752;-10.11705;,
 -53.25035;12.76752;-3.95925;,
 -56.56972;12.76752;-6.37095;,
 -54.43624;12.76752;-0.30965;,
 -58.53913;12.76752;-0.30965;,
 -60.19284;9.86771;-0.30965;,
 -57.90754;9.86771;6.72355;,
 -57.90754;9.86771;-7.34295;,
 -51.92468;9.86771;-11.68985;,
 -44.52939;9.86771;-11.68985;,
 -38.54648;9.86771;-7.34295;,
 -36.26130;9.86771;-0.30965;,
 -38.54648;9.86771;6.72355;,
 -44.52939;9.86771;11.07045;,
 -51.92468;9.86771;11.07045;,
 -56.56972;-12.81918;5.75155;,
 -51.41359;-12.81918;9.49765;,
 -51.92468;-9.91928;11.07045;,
 -57.90754;-9.91928;6.72355;,
 -45.04049;-12.81918;9.49765;,
 -44.52939;-9.91928;11.07045;,
 -39.88439;-12.81918;5.75155;,
 -38.54648;-9.91928;6.72355;,
 -37.91489;-12.81918;-0.30965;,
 -36.26130;-9.91928;-0.30965;,
 -39.88439;-12.81918;-6.37095;,
 -38.54648;-9.91928;-7.34295;,
 -45.04049;-12.81918;-10.11705;,
 -44.52939;-9.91928;-11.68985;,
 -51.41359;-12.81918;-10.11705;,
 -51.92468;-9.91928;-11.68985;,
 -56.56972;-12.81918;-6.37095;,
 -57.90754;-9.91928;-7.34295;,
 -58.53913;-12.81918;-0.30965;,
 -60.19284;-9.91928;-0.30965;,
 -59.12184;9.86771;-0.30965;,
 -57.04113;9.86771;6.09415;,
 -57.04113;9.86771;-6.71355;,
 -51.59378;9.86771;-10.67135;,
 -44.86039;9.86771;-10.67135;,
 -39.41309;9.86771;-6.71355;,
 -37.33219;9.86771;-0.30965;,
 -39.41309;9.86771;6.09415;,
 -44.86039;9.86771;10.05195;,
 -51.59378;9.86771;10.05195;,
 -52.39838;-12.81918;2.72095;,
 -49.82039;-12.81918;4.59405;,
 -51.59378;-9.91928;10.05195;,
 -57.04103;-9.91928;6.09415;,
 -46.63379;-12.81918;4.59405;,
 -44.86039;-9.91928;10.05195;,
 -44.05568;-12.81918;2.72095;,
 -39.41289;-9.91928;6.09415;,
 -43.07099;-12.81918;-0.30965;,
 -37.33219;-9.91928;-0.30965;,
 -44.05568;-12.81918;-3.34035;,
 -39.41289;-9.91928;-6.71355;,
 -46.63379;-12.81918;-5.21345;,
 -44.86039;-9.91928;-10.67135;,
 -49.82039;-12.81918;-5.21345;,
 -51.59378;-9.91928;-10.67135;,
 -52.39838;-12.81918;-3.34035;,
 -57.04103;-9.91928;-6.71355;,
 -53.38315;-12.81918;-0.30965;,
 -59.12184;-9.91928;-0.30965;,
 -56.34813;-1.01509;5.59065;,
 -56.34813;0.96341;5.59065;,
 -58.26524;0.96341;-0.30965;,
 -58.26524;-1.01509;-0.30965;,
 -51.32909;-1.01509;9.23725;,
 -51.32909;0.96341;9.23725;,
 -45.12510;-1.01509;9.23725;,
 -45.12510;0.96341;9.23725;,
 -40.10588;-1.01509;5.59065;,
 -40.10588;0.96341;5.59065;,
 -38.18879;-1.01509;-0.30965;,
 -38.18879;0.96341;-0.30965;,
 -40.10588;-1.01509;-6.21005;,
 -40.10588;0.96341;-6.21005;,
 -45.12510;-1.01509;-9.85665;,
 -45.12510;0.96341;-9.85665;,
 -51.32909;-1.01509;-9.85665;,
 -51.32909;0.96341;-9.85665;,
 -56.34813;-1.01509;-6.21005;,
 -56.34813;0.96341;-6.21005;,
 -57.04113;0.96341;6.09415;,
 -51.59378;0.96341;10.05195;,
 -44.86039;0.96341;10.05195;,
 -39.41289;0.96341;6.09415;,
 -37.33219;0.96341;-0.30965;,
 -39.41289;0.96341;-6.71355;,
 -44.86039;0.96341;-10.67135;,
 -51.59378;0.96341;-10.67135;,
 -57.04113;0.96341;-6.71355;,
 -59.12184;0.96341;-0.30965;,
 -51.59378;-1.01509;10.05195;,
 -57.04103;-1.01509;6.09415;,
 -44.86039;-1.01509;10.05195;,
 -39.41289;-1.01509;6.09415;,
 -37.33219;-1.01509;-0.30965;,
 -39.41289;-1.01509;-6.71355;,
 -44.86039;-1.01509;-10.67135;,
 -51.59378;-1.01509;-10.67135;,
 -57.04103;-1.01509;-6.71355;,
 -59.12184;-1.01509;-0.30965;,
 -48.22709;32.74603;-0.30965;,
 -48.22709;-20.38588;-0.30965;,
 0.00253;-8.70258;-14.28125;,
 -22.54420;-8.29279;-13.63535;,
 -22.54420;8.67252;-13.63535;,
 0.00253;9.08232;-14.28125;,
 -22.54420;8.67252;13.09695;,
 -22.54420;-8.29279;13.09695;,
 0.00253;-8.70258;13.74285;,
 0.00253;9.08232;13.74285;,
 0.00253;14.20181;-9.16155;,
 -22.54420;13.55611;-8.75175;,
 -22.54420;13.55611;8.21335;,
 0.00253;14.20181;8.62335;,
 0.00253;-13.82208;8.62335;,
 -22.54420;-13.17639;8.21335;,
 -22.54420;-13.17639;-8.75175;,
 0.00253;-13.82208;-9.16155;,
 -42.81699;6.02971;-8.61135;,
 -42.81699;-5.64989;-8.61135;,
 -42.81699;-5.64989;8.07315;,
 -42.81699;6.02971;8.07315;,
 -42.81699;-8.15239;-6.10895;,
 -42.81699;-8.15239;5.57065;,
 -42.81699;8.53212;-6.10895;,
 -42.81699;8.53212;5.57065;,
 -25.43789;-7.37468;-11.07515;,
 -25.43789;-10.61618;-7.83365;,
 -25.43789;7.75432;-11.07515;,
 -25.43789;10.99571;-7.83365;,
 -25.43789;10.99571;7.29535;,
 -25.43789;7.75432;10.53675;,
 -25.43789;-7.37468;10.53675;,
 -25.43789;-10.61618;7.29535;,
 0.00253;7.75432;-11.07515;,
 0.00253;-7.37469;-11.07515;,
 0.00253;-7.37469;10.53675;,
 0.00253;7.75432;10.53675;,
 0.00253;10.99571;7.29535;,
 0.00253;10.99571;-7.83365;,
 0.00253;-10.61618;-7.83365;,
 0.00253;-10.61618;7.29535;;
 
 165;
 4;0,1,2,3;,
 4;4,0,3,5;,
 4;6,4,5,7;,
 4;8,6,7,9;,
 4;10,8,9,11;,
 4;12,10,11,13;,
 4;14,12,13,15;,
 4;16,14,15,17;,
 4;18,16,17,19;,
 4;1,18,19,2;,
 4;20,21,2,19;,
 4;22,20,19,17;,
 4;23,22,17,15;,
 4;24,23,15,13;,
 4;25,24,13,11;,
 4;26,25,11,9;,
 4;27,26,9,7;,
 4;28,27,7,5;,
 4;29,28,5,3;,
 4;21,29,3,2;,
 4;30,31,32,33;,
 4;31,34,35,32;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,30,33,49;,
 4;50,51,21,20;,
 4;52,50,20,22;,
 4;53,52,22,23;,
 4;54,53,23,24;,
 4;55,54,24,25;,
 4;56,55,25,26;,
 4;57,56,26,27;,
 4;58,57,27,28;,
 4;59,58,28,29;,
 4;51,59,29,21;,
 4;60,61,31,30;,
 4;62,63,33,32;,
 4;61,64,34,31;,
 4;65,62,32,35;,
 4;64,66,36,34;,
 4;67,65,35,37;,
 4;66,68,38,36;,
 4;69,67,37,39;,
 4;68,70,40,38;,
 4;71,69,39,41;,
 4;70,72,42,40;,
 4;73,71,41,43;,
 4;72,74,44,42;,
 4;75,73,43,45;,
 4;74,76,46,44;,
 4;77,75,45,47;,
 4;76,78,48,46;,
 4;79,77,47,49;,
 4;78,60,30,48;,
 4;63,79,49,33;,
 4;80,81,82,83;,
 4;81,80,84,85;,
 4;85,84,86,87;,
 4;87,86,88,89;,
 4;89,88,90,91;,
 4;91,90,92,93;,
 4;93,92,94,95;,
 4;95,94,96,97;,
 4;97,96,98,99;,
 4;99,98,83,82;,
 4;59,51,100,101;,
 4;58,59,101,102;,
 4;57,58,102,103;,
 4;56,57,103,104;,
 4;55,56,104,105;,
 4;54,55,105,106;,
 4;53,54,106,107;,
 4;52,53,107,108;,
 4;50,52,108,109;,
 4;51,50,109,100;,
 4;110,111,63,62;,
 4;112,110,62,65;,
 4;113,112,65,67;,
 4;114,113,67,69;,
 4;115,114,69,71;,
 4;116,115,71,73;,
 4;117,116,73,75;,
 4;118,117,75,77;,
 4;119,118,77,79;,
 4;111,119,79,63;,
 4;100,109,82,81;,
 4;119,111,80,83;,
 4;111,110,84,80;,
 4;101,100,81,85;,
 4;110,112,86,84;,
 4;102,101,85,87;,
 4;112,113,88,86;,
 4;103,102,87,89;,
 4;113,114,90,88;,
 4;104,103,89,91;,
 4;114,115,92,90;,
 4;105,104,91,93;,
 4;115,116,94,92;,
 4;106,105,93,95;,
 4;116,117,96,94;,
 4;107,106,95,97;,
 4;117,118,98,96;,
 4;108,107,97,99;,
 4;118,119,83,98;,
 4;109,108,99,82;,
 3;6,8,120;,
 3;4,6,120;,
 3;0,4,120;,
 3;1,0,120;,
 3;18,1,120;,
 3;16,18,120;,
 3;14,16,120;,
 3;12,14,120;,
 3;10,12,120;,
 3;8,10,120;,
 3;72,70,121;,
 3;74,72,121;,
 3;76,74,121;,
 3;78,76,121;,
 3;60,78,121;,
 3;61,60,121;,
 3;64,61,121;,
 3;66,64,121;,
 3;68,66,121;,
 3;70,68,121;,
 4;122,123,124,125;,
 4;126,127,128,129;,
 4;130,131,132,133;,
 4;134,135,136,137;,
 4;136,123,122,137;,
 4;124,131,130,125;,
 4;134,128,127,135;,
 4;129,133,132,126;,
 4;138,139,140,141;,
 4;139,142,143,140;,
 4;144,138,141,145;,
 4;142,139,146,147;,
 4;148,146,139,138;,
 4;138,144,149,148;,
 4;150,149,144,145;,
 4;151,150,145,141;,
 4;140,152,151,141;,
 4;153,152,140,143;,
 4;147,153,143,142;,
 4;146,148,124,123;,
 4;154,155,122,125;,
 4;151,152,127,126;,
 4;156,157,129,128;,
 4;149,150,132,131;,
 4;158,159,130,133;,
 4;153,147,136,135;,
 4;160,161,134,137;,
 4;147,146,123,136;,
 4;155,160,137,122;,
 4;148,149,131,124;,
 4;159,154,125,130;,
 4;161,156,128,134;,
 4;152,153,135,127;,
 4;157,158,133,129;,
 4;150,151,126,132;;
 
 MeshMaterialList {
  6;
  165;
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5;;
  Material {
   0.401600;0.401600;0.401600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\x\\gray.jpg";
   }
  }
  Material {
   0.000000;0.608800;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\x\\blue.jpg";
   }
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\x\\red.jpg";
   }
  }
  Material {
   0.787200;0.800000;0.016000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\x\\yellow.jpg";
   }
  }
  Material {
   0.800000;0.633600;0.373600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\x\\hada.jpg";
   }
  }
  Material {
   0.184800;0.184800;0.184800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\x\\black.jpg";
   }
  }
 }
 MeshNormals {
  113;
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.702772;0.495382;0.510595;,
  -0.868676;0.495380;0.000002;,
  -0.702773;0.495383;-0.510593;,
  -0.268436;0.495391;-0.826154;,
  0.268434;0.495394;-0.826152;,
  0.702772;0.495386;-0.510591;,
  0.868678;0.495377;0.000002;,
  0.702772;0.495385;0.510593;,
  0.268434;0.495394;0.826152;,
  -0.268436;0.495391;0.826154;,
  -0.702777;-0.495372;0.510598;,
  -0.268437;-0.495380;0.826160;,
  0.268436;-0.495383;0.826159;,
  0.702777;-0.495374;0.510597;,
  0.868684;-0.495367;0.000002;,
  0.702778;-0.495375;-0.510595;,
  0.268436;-0.495383;-0.826158;,
  -0.268438;-0.495379;-0.826160;,
  -0.702779;-0.495371;-0.510597;,
  -0.868683;-0.495368;0.000002;,
  -0.809018;0.000000;0.587783;,
  -0.809020;0.000000;0.587781;,
  -0.309021;0.000000;0.951055;,
  -0.309025;0.000000;0.951054;,
  0.309019;0.000003;0.951056;,
  0.309015;0.000000;0.951057;,
  0.809015;0.000009;0.587788;,
  0.809016;0.000000;0.587786;,
  1.000000;0.000011;0.000002;,
  1.000000;0.000000;0.000002;,
  0.809016;0.000009;-0.587786;,
  0.809018;0.000000;-0.587784;,
  0.309019;0.000003;-0.951056;,
  0.309015;0.000000;-0.951057;,
  -0.309021;0.000000;-0.951055;,
  -0.309025;0.000000;-0.951054;,
  -0.809021;0.000000;-0.587780;,
  -0.809020;0.000000;-0.587782;,
  -1.000000;0.000000;0.000002;,
  -1.000000;0.000000;0.000002;,
  -0.809020;0.000000;0.587781;,
  -1.000000;0.000000;0.000002;,
  -0.309020;0.000000;0.951055;,
  0.309013;0.000000;0.951058;,
  0.809015;0.000000;0.587787;,
  1.000000;0.000000;0.000002;,
  0.809017;0.000000;-0.587785;,
  0.309013;0.000000;-0.951058;,
  -0.309020;0.000000;-0.951055;,
  -0.809021;0.000000;-0.587779;,
  0.556720;0.320806;0.766255;,
  0.371522;-0.888320;-0.269924;,
  0.141908;-0.888320;-0.436749;,
  -0.141913;-0.888320;-0.436747;,
  -0.371526;-0.888317;-0.269926;,
  -0.459227;-0.888319;0.000002;,
  -0.371527;-0.888316;0.269930;,
  -0.141914;-0.888318;0.436750;,
  0.141909;-0.888318;0.436753;,
  0.371523;-0.888319;0.269927;,
  0.459227;-0.888319;0.000002;,
  -0.236354;-0.644215;-0.727409;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -0.448976;-0.825172;-0.342800;,
  -0.448974;-0.342795;-0.825175;,
  -0.448979;0.342798;-0.825171;,
  -0.448984;0.825171;-0.342793;,
  -0.448981;0.825171;0.342795;,
  -0.448973;0.342799;0.825174;,
  -0.448968;-0.342795;0.825178;,
  -0.448973;-0.825173;0.342802;,
  -0.033401;-0.382448;-0.923373;,
  -0.389652;-0.353731;-0.850321;,
  -0.389657;0.353731;-0.850319;,
  -0.033402;0.382449;-0.923373;,
  -0.389655;0.353728;0.850321;,
  -0.389650;-0.353728;0.850323;,
  -0.033403;-0.382443;0.923375;,
  -0.033403;0.382444;0.923375;,
  -0.033397;0.923377;-0.382439;,
  -0.389663;0.850319;-0.353724;,
  -0.389662;0.850317;0.353728;,
  -0.033399;0.923375;0.382443;,
  -0.033398;-0.923375;0.382444;,
  -0.389648;-0.850322;0.353732;,
  -0.389649;-0.850324;-0.353727;,
  -0.033396;-0.923377;-0.382439;,
  0.772568;0.296792;0.561295;,
  0.954944;0.296786;-0.000004;,
  0.295082;0.296787;0.908209;,
  -0.295091;0.296787;0.908206;,
  -0.772562;0.296788;0.561306;,
  -0.900789;0.320804;0.292684;,
  -0.954943;0.296789;-0.000004;,
  -0.772572;0.296786;-0.561294;,
  -0.295110;0.296791;-0.908199;,
  -0.000006;0.320808;-0.947144;,
  0.295101;0.296791;-0.908202;,
  0.772578;0.296790;-0.561283;,
  0.912058;0.283457;-0.296314;,
  -0.236354;-0.644209;0.727414;,
  0.826381;-0.563112;0.000004;,
  -0.166561;-0.911313;-0.376519;,
  -0.166561;-0.376509;-0.911317;,
  -0.166558;0.376518;-0.911314;,
  -0.166551;0.911318;-0.376511;,
  -0.166549;0.911318;0.376511;,
  -0.166550;0.376519;0.911315;,
  -0.166553;-0.376511;0.911318;,
  -0.166559;-0.911314;0.376518;;
  165;
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;3,2,2,3;,
  4;4,3,3,4;,
  4;5,4,4,5;,
  4;6,5,5,6;,
  4;7,6,6,7;,
  4;8,7,7,8;,
  4;9,8,8,9;,
  4;10,9,9,10;,
  4;11,10,10,11;,
  4;2,11,11,2;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;21,12,12,21;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;58,59,0,0;,
  4;1,1,1,1;,
  4;59,60,0,0;,
  4;1,1,1,1;,
  4;60,61,0,0;,
  4;1,1,1,1;,
  4;61,62,0,0;,
  4;1,1,1,1;,
  4;62,53,0,0;,
  4;1,1,1,1;,
  4;53,54,0,0;,
  4;1,1,1,1;,
  4;54,55,0,0;,
  4;1,1,1,1;,
  4;55,56,0,0;,
  4;1,1,1,1;,
  4;56,57,0,0;,
  4;1,1,1,1;,
  4;57,58,0,0;,
  4;1,1,1,1;,
  4;42,42,43,43;,
  4;42,42,44,44;,
  4;44,44,45,45;,
  4;45,45,46,46;,
  4;46,46,47,47;,
  4;47,47,48,48;,
  4;48,48,49,49;,
  4;49,49,50,50;,
  4;50,50,51,51;,
  4;51,51,43,43;,
  4;24,23,23,24;,
  4;26,24,24,26;,
  4;28,26,26,28;,
  4;30,28,28,30;,
  4;32,30,30,32;,
  4;34,32,32,34;,
  4;36,34,34,36;,
  4;38,36,36,38;,
  4;40,38,38,40;,
  4;23,40,40,23;,
  4;25,22,22,25;,
  4;27,25,25,27;,
  4;29,27,27,29;,
  4;31,29,29,31;,
  4;33,31,31,33;,
  4;35,33,33,35;,
  4;37,35,35,37;,
  4;39,37,37,39;,
  4;41,39,39,41;,
  4;22,41,41,22;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  3;90,91,52;,
  3;92,90,52;,
  3;93,92,52;,
  3;94,93,95;,
  3;96,94,95;,
  3;97,96,95;,
  3;98,97,99;,
  3;100,98,99;,
  3;101,100,99;,
  3;91,101,102;,
  3;54,53,63;,
  3;55,54,63;,
  3;56,55,63;,
  3;57,56,63;,
  3;58,57,103;,
  3;59,58,103;,
  3;60,59,103;,
  3;61,60,103;,
  3;62,61,104;,
  3;53,62,104;,
  4;74,75,76,77;,
  4;78,79,80,81;,
  4;82,83,84,85;,
  4;86,87,88,89;,
  4;88,75,74,89;,
  4;76,83,82,77;,
  4;86,80,79,87;,
  4;81,85,84,78;,
  4;64,64,64,64;,
  4;64,64,64,64;,
  4;64,64,64,64;,
  4;105,106,67,66;,
  4;68,67,106,107;,
  4;107,108,69,68;,
  4;70,69,108,109;,
  4;71,70,109,110;,
  4;111,72,71,110;,
  4;73,72,111,112;,
  4;66,73,112,105;,
  4;67,68,76,75;,
  4;65,65,65,65;,
  4;71,72,79,78;,
  4;65,65,65,65;,
  4;69,70,84,83;,
  4;65,65,65,65;,
  4;73,66,88,87;,
  4;65,65,65,65;,
  4;66,67,75,88;,
  4;65,65,65,65;,
  4;68,69,83,76;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;72,73,87,79;,
  4;65,65,65,65;,
  4;70,71,78,84;;
 }
}
