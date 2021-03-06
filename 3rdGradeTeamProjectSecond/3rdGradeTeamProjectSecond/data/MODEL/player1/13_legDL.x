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
 40;
 3.22827;0.02710;-6.55329;,
 3.22827;-62.55910;-6.55329;,
 -3.30083;-62.55910;-6.55329;,
 -3.30083;0.02710;-6.55329;,
 -3.30083;-62.55910;6.50331;,
 3.22827;-62.55910;6.50331;,
 3.22827;0.02710;6.50331;,
 -3.30083;0.02710;6.50331;,
 6.49207;0.02710;3.23961;,
 6.49207;-62.55910;3.23961;,
 6.49207;-62.55910;-3.28959;,
 6.49207;0.02710;-3.28959;,
 -6.56483;0.02710;-3.28959;,
 -6.56483;-62.55910;-3.28959;,
 -6.56483;-62.55910;3.23961;,
 -6.56483;0.02710;3.23961;,
 -4.14013;-65.94160;2.02721;,
 -4.14013;-65.94160;-2.07719;,
 -2.08843;-65.94160;4.07881;,
 -2.08843;-65.94160;-4.12879;,
 2.01587;-65.94160;4.07881;,
 2.01587;-65.94160;-4.12879;,
 4.06758;-65.94160;2.02721;,
 4.06758;-65.94160;-2.07719;,
 -6.56483;0.02710;3.23961;,
 -6.56483;-62.55910;3.23961;,
 6.49207;-62.55910;3.23961;,
 6.49207;0.02710;3.23961;,
 -2.58542;5.81500;1.24971;,
 -1.31103;5.81500;2.52411;,
 -2.58542;5.81500;-1.29969;,
 -1.31103;5.81500;-2.57409;,
 1.23847;5.81500;-2.57409;,
 1.23847;5.81500;2.52411;,
 2.51288;5.81500;-1.29969;,
 2.51288;5.81500;1.24971;,
 6.49207;-62.55910;-3.28959;,
 3.22827;-62.55910;-6.55329;,
 -3.30083;-62.55910;-6.55329;,
 -6.56483;-62.55910;-3.28959;;
 
 36;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 3;16,17,18;,
 3;17,19,18;,
 3;18,19,20;,
 3;19,21,20;,
 3;20,21,22;,
 3;22,21,23;,
 4;13,12,3,2;,
 4;1,0,11,10;,
 4;24,25,4,7;,
 4;6,5,26,27;,
 3;28,29,30;,
 3;30,29,31;,
 3;31,29,32;,
 3;29,33,32;,
 3;32,33,34;,
 3;34,33,35;,
 4;3,31,32,0;,
 4;0,32,34,11;,
 4;11,34,35,27;,
 4;27,35,33,6;,
 4;6,33,29,7;,
 4;7,29,28,15;,
 4;15,28,30,12;,
 4;12,30,31,3;,
 4;25,16,18,4;,
 4;4,18,20,5;,
 4;5,20,22,26;,
 4;26,22,23,36;,
 4;36,23,21,37;,
 4;37,21,19,38;,
 4;38,19,17,39;,
 4;39,17,16,25;;
 
 MeshMaterialList {
  9;
  36;
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
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\player1\\white.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\player1\\black.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\player1\\yellow.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\player1\\blue2.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\player1\\blue.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\player1\\gray.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\player1\\red.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\player1\\red.jpg";
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
  32;
  -0.870977;-0.335612;-0.358836;,
  -0.358800;-0.335597;-0.870998;,
  0.870987;-0.335598;-0.358826;,
  0.358811;-0.335596;-0.870993;,
  -0.870977;-0.335613;0.358836;,
  -0.358800;-0.335598;0.870997;,
  0.870987;-0.335598;0.358826;,
  0.358811;-0.335596;0.870993;,
  0.360218;0.325651;-0.874182;,
  -0.360207;0.325652;-0.874187;,
  -0.874170;0.325662;-0.360237;,
  -0.874170;0.325662;0.360237;,
  -0.360207;0.325652;0.874187;,
  0.360218;0.325651;0.874182;,
  0.874178;0.325652;0.360228;,
  0.874178;0.325652;-0.360228;,
  0.129235;0.940038;-0.315637;,
  -0.163350;0.902297;-0.398969;,
  0.398966;0.902297;-0.163357;,
  0.530412;0.819450;0.217177;,
  0.129235;0.940038;0.315637;,
  -0.106355;0.959797;0.259764;,
  -0.530400;0.819457;0.217178;,
  -0.398957;0.902302;-0.163357;,
  -0.126664;-0.942401;0.309575;,
  -0.520088;-0.827173;0.212821;,
  0.126668;-0.942401;0.309575;,
  0.391111;-0.906322;0.160039;,
  0.520105;-0.827162;-0.212822;,
  0.126668;-0.942401;-0.309575;,
  -0.126664;-0.942401;-0.309575;,
  -0.391098;-0.906328;-0.160039;;
  36;
  4;8,3,1,9;,
  4;5,7,13,12;,
  4;14,6,2,15;,
  4;10,0,4,11;,
  3;25,31,24;,
  3;31,30,24;,
  3;24,30,26;,
  3;30,29,26;,
  3;26,29,27;,
  3;27,29,28;,
  4;0,10,9,1;,
  4;3,8,15,2;,
  4;11,4,5,12;,
  4;13,7,6,14;,
  3;22,21,23;,
  3;23,21,17;,
  3;17,21,16;,
  3;21,20,16;,
  3;16,20,18;,
  3;18,20,19;,
  4;9,17,16,8;,
  4;8,16,18,15;,
  4;15,18,19,14;,
  4;14,19,20,13;,
  4;13,20,21,12;,
  4;12,21,22,11;,
  4;11,22,23,10;,
  4;10,23,17,9;,
  4;4,25,24,5;,
  4;5,24,26,7;,
  4;7,26,27,6;,
  4;6,27,28,2;,
  4;2,28,29,3;,
  4;3,29,30,1;,
  4;1,30,31,0;,
  4;0,31,25,4;;
 }
 MeshTextureCoords {
  40;
  0.562510;0.125000;,
  0.562510;0.000000;,
  0.437490;0.000000;,
  0.437490;0.125000;,
  0.437490;0.750000;,
  0.562510;0.750000;,
  0.562510;0.625000;,
  0.437490;0.625000;,
  0.812510;0.125000;,
  0.812510;0.000000;,
  0.687490;0.000000;,
  0.687490;0.125000;,
  0.312510;0.125000;,
  0.312510;0.000000;,
  0.187490;0.000000;,
  0.187490;0.125000;,
  0.375000;0.812490;,
  0.375000;0.937510;,
  0.437490;0.750000;,
  0.437490;1.000000;,
  0.562510;0.750000;,
  0.562510;1.000000;,
  0.625000;0.812490;,
  0.625000;0.937510;,
  0.375000;0.625000;,
  0.375000;0.812490;,
  0.625000;0.812490;,
  0.625000;0.625000;,
  0.187490;0.125000;,
  0.437490;0.625000;,
  0.312510;0.125000;,
  0.437490;0.125000;,
  0.562510;0.125000;,
  0.562510;0.625000;,
  0.687490;0.125000;,
  0.625000;0.625000;,
  0.625000;0.937510;,
  0.562510;1.000000;,
  0.437490;1.000000;,
  0.375000;0.937510;;
 }
}
