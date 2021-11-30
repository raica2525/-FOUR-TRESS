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
 116;
 0.17253;0.04825;-8.44870;,
 142.34624;40.80016;-7.88780;,
 148.16045;20.51746;-8.00160;,
 5.98674;-20.23456;-8.56250;,
 142.34624;40.80016;-7.88780;,
 142.31264;40.70366;7.61180;,
 148.12694;20.42086;7.49800;,
 148.16045;20.51746;-8.00160;,
 142.31264;40.70366;7.61180;,
 0.13903;-0.04835;7.05100;,
 5.95324;-20.33106;6.93720;,
 148.12694;20.42086;7.49800;,
 0.13903;-0.04835;7.05100;,
 0.17253;0.04825;-8.44870;,
 5.98674;-20.23456;-8.56250;,
 5.95324;-20.33106;6.93720;,
 142.34624;40.80016;-7.88780;,
 0.17253;0.04825;-8.44870;,
 5.98674;-20.23456;-8.56250;,
 148.16045;20.51746;-8.00160;,
 99.48395;172.97055;-8.05710;,
 123.13144;179.74875;-7.96380;,
 162.34305;42.96007;-8.73120;,
 138.69545;36.18187;-8.82450;,
 123.13144;179.74875;-7.96380;,
 123.09424;179.64087;9.33580;,
 162.30565;42.85236;8.56840;,
 162.34305;42.96007;-8.73120;,
 123.09424;179.64087;9.33580;,
 99.44664;172.86276;9.24250;,
 138.65814;36.07407;8.47510;,
 162.30565;42.85236;8.56840;,
 99.44664;172.86276;9.24250;,
 99.48395;172.97055;-8.05710;,
 138.69545;36.18187;-8.82450;,
 138.65814;36.07407;8.47510;,
 123.13144;179.74875;-7.96380;,
 99.48395;172.97055;-8.05710;,
 138.69545;36.18187;-8.82450;,
 162.34305;42.96007;-8.73120;,
 87.79845;195.96005;-14.98930;,
 121.63554;205.65906;-14.85580;,
 130.26035;175.57126;-15.02460;,
 96.42325;165.87238;-15.15810;,
 121.63554;205.65906;-14.85580;,
 121.56764;205.46365;16.54350;,
 130.19264;175.37576;16.37470;,
 130.26035;175.57126;-15.02460;,
 121.56764;205.46365;16.54350;,
 87.73055;195.76456;16.41000;,
 96.35555;165.67685;16.24130;,
 130.19264;175.37576;16.37470;,
 87.73055;195.76456;16.41000;,
 87.79845;195.96005;-14.98930;,
 96.42325;165.87238;-15.15810;,
 96.35555;165.67685;16.24130;,
 121.63554;205.65906;-14.85580;,
 87.79845;195.96005;-14.98930;,
 96.42325;165.87238;-15.15810;,
 130.26035;175.57126;-15.02460;,
 130.51015;42.03706;-15.85590;,
 164.34714;51.73596;-15.72240;,
 172.97214;21.64826;-15.89120;,
 139.13495;11.94926;-16.02470;,
 164.34714;51.73596;-15.72240;,
 164.27934;51.54036;15.67700;,
 172.90436;21.45256;15.50820;,
 172.97214;21.64826;-15.89120;,
 164.27934;51.54036;15.67700;,
 130.44235;41.84146;15.54350;,
 139.06714;11.75366;15.37470;,
 172.90436;21.45256;15.50820;,
 130.44235;41.84146;15.54350;,
 130.51015;42.03706;-15.85590;,
 139.13495;11.94926;-16.02470;,
 139.06714;11.75366;15.37470;,
 164.34714;51.73596;-15.72240;,
 130.51015;42.03706;-15.85590;,
 139.13495;11.94926;-16.02470;,
 172.97214;21.64826;-15.89120;,
 121.92055;225.03555;0.05990;,
 127.38304;225.22607;7.59110;,
 80.66365;293.23148;4.51440;,
 78.83945;287.74487;-2.77720;,
 136.23155;224.85995;4.73470;,
 83.62535;301.43488;1.27070;,
 136.23795;224.44388;-4.56140;,
 83.63164;301.01895;-8.02540;,
 127.39305;224.55206;-7.45070;,
 80.67395;292.55807;-10.52710;,
 121.92055;225.03555;0.05990;,
 78.83945;287.74487;-2.77720;,
 1.48303;269.85626;5.50780;,
 5.82523;266.19016;-1.86110;,
 -5.53237;275.11377;2.38890;,
 -5.52617;274.69815;-6.90690;,
 1.49324;269.18268;-9.53400;,
 5.82523;266.19016;-1.86110;,
 -0.73377;187.40387;9.19830;,
 3.78113;190.15906;1.54190;,
 -8.02868;182.27228;6.54430;,
 -8.02237;181.85635;-2.75160;,
 -0.72367;186.73026;-5.84350;,
 3.78113;190.15906;1.54190;,
 77.07684;159.82047;10.48550;,
 75.53185;164.72446;2.72930;,
 79.58635;151.21367;7.99420;,
 79.59265;150.79747;-1.30220;,
 77.08694;159.14706;-4.55600;,
 75.53185;164.72446;2.72930;,
 127.38304;225.22607;7.59110;,
 121.92055;225.03555;0.05990;,
 136.23155;224.85995;4.73470;,
 136.23795;224.44388;-4.56140;,
 127.39305;224.55206;-7.45070;,
 121.92055;225.03555;0.05990;;
 
 49;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;72,65,76,77;,
 4;78,79,66,75;,
 4;80,81,82,83;,
 4;81,84,85,82;,
 4;84,86,87,85;,
 4;86,88,89,87;,
 4;88,90,91,89;,
 4;83,82,92,93;,
 4;82,85,94,92;,
 4;85,87,95,94;,
 4;87,89,96,95;,
 4;89,91,97,96;,
 4;93,92,98,99;,
 4;92,94,100,98;,
 4;94,95,101,100;,
 4;95,96,102,101;,
 4;96,97,103,102;,
 4;99,98,104,105;,
 4;98,100,106,104;,
 4;100,101,107,106;,
 4;101,102,108,107;,
 4;102,103,109,108;,
 4;105,104,110,111;,
 4;104,106,112,110;,
 4;106,107,113,112;,
 4;107,108,114,113;,
 4;108,109,115,114;;
 
 MeshMaterialList {
  6;
  49;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\kamikaze\\kamikaze_eye.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\kamikaze\\BIOS.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\kamikaze\\color_blue.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\kamikaze\\color_black.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\kamikaze\\color_white.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  49;
  0.002159;0.006230;-0.999978;,
  0.961282;0.275540;0.003797;,
  -0.002159;-0.006229;0.999978;,
  0.002160;0.006229;-0.999978;,
  0.961283;0.275538;0.003790;,
  -0.002160;-0.006229;0.999978;,
  0.002160;0.006229;-0.999978;,
  0.961283;0.275537;0.003791;,
  -0.002159;-0.006227;0.999978;,
  0.002160;0.006229;-0.999978;,
  0.961282;0.275541;0.003792;,
  -0.002160;-0.006229;0.999978;,
  -0.711151;-0.464689;0.527568;,
  0.308289;0.034262;0.950676;,
  0.824508;0.565310;-0.024735;,
  0.309553;-0.050821;-0.949523;,
  0.102716;0.333500;0.937138;,
  0.103989;0.248406;-0.963058;,
  0.243950;-0.803258;0.543382;,
  -0.245704;0.230644;0.941505;,
  -0.283371;0.958044;-0.043040;,
  -0.244413;0.145556;-0.958684;,
  0.861454;-0.000431;0.507835;,
  -0.255459;-0.132165;0.957744;,
  -0.999639;0.026794;-0.001871;,
  -0.254168;-0.217240;-0.942446;,
  0.287977;0.834312;0.470099;,
  0.086931;-0.253535;0.963412;,
  -0.334441;-0.941484;0.041911;,
  0.088206;-0.338604;-0.936785;,
  -0.961283;-0.275538;-0.003794;,
  -0.275555;0.961270;0.005391;,
  0.275555;-0.961270;-0.005393;,
  -0.961283;-0.275538;-0.003790;,
  -0.275553;0.961271;0.005399;,
  0.275556;-0.961270;-0.005393;,
  -0.961282;-0.275539;-0.003791;,
  -0.275559;0.961269;0.005388;,
  0.275555;-0.961270;-0.005391;,
  -0.961284;-0.275535;-0.003792;,
  -0.275556;0.961270;0.005393;,
  0.275556;-0.961270;-0.005395;,
  -0.710466;-0.510020;-0.484889;,
  0.244631;-0.848589;-0.469098;,
  0.862135;-0.045765;-0.504608;,
  0.288660;0.788982;-0.542386;,
  -0.683936;0.547393;0.482277;,
  0.792942;-0.608663;0.027788;,
  -0.683255;0.502062;-0.530185;;
  49;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;12,12,12,12;,
  4;13,13,16,16;,
  4;14,14,14,14;,
  4;15,15,17,17;,
  4;42,42,42,42;,
  4;18,18,18,18;,
  4;16,16,19,19;,
  4;20,20,20,20;,
  4;17,17,21,21;,
  4;43,43,43,43;,
  4;22,22,22,22;,
  4;19,19,23,23;,
  4;24,24,24,24;,
  4;21,21,25,25;,
  4;44,44,44,44;,
  4;26,26,26,26;,
  4;23,23,27,27;,
  4;28,28,28,28;,
  4;25,25,29,29;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;27,27,13,13;,
  4;47,47,47,47;,
  4;29,29,15,15;,
  4;48,48,48,48;;
 }
 MeshTextureCoords {
  116;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.200000;,
  0.200000;0.200000;,
  0.200000;0.000000;,
  0.000000;0.400000;,
  0.200000;0.400000;,
  0.000000;0.600000;,
  0.200000;0.600000;,
  0.000000;0.800000;,
  0.200000;0.800000;,
  0.000000;1.000000;,
  0.200000;1.000000;,
  0.400000;0.200000;,
  0.400000;0.000000;,
  0.400000;0.400000;,
  0.400000;0.600000;,
  0.400000;0.800000;,
  0.400000;1.000000;,
  0.600000;0.200000;,
  0.600000;0.000000;,
  0.600000;0.400000;,
  0.600000;0.600000;,
  0.600000;0.800000;,
  0.600000;1.000000;,
  0.800000;0.200000;,
  0.800000;0.000000;,
  0.800000;0.400000;,
  0.800000;0.600000;,
  0.800000;0.800000;,
  0.800000;1.000000;,
  1.000000;0.200000;,
  1.000000;0.000000;,
  1.000000;0.400000;,
  1.000000;0.600000;,
  1.000000;0.800000;,
  1.000000;1.000000;;
 }
}
