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
 3.23958;0.01850;-6.55519;,
 3.23958;-62.56770;-6.55519;,
 -3.28942;-62.56770;-6.55519;,
 -3.28942;0.01850;-6.55519;,
 -3.28942;-62.56770;6.50141;,
 3.23958;-62.56770;6.50141;,
 3.23958;0.01850;6.50141;,
 -3.28942;0.01850;6.50141;,
 6.50348;0.01850;3.23771;,
 6.50348;-62.56770;3.23771;,
 6.50348;-62.56770;-3.29149;,
 6.50348;0.01850;-3.29149;,
 -6.55332;0.01850;-3.29149;,
 -6.55332;-62.56770;-3.29149;,
 -6.55332;-62.56770;3.23771;,
 -6.55332;0.01850;3.23771;,
 -4.12882;-65.95020;2.02531;,
 -4.12882;-65.95020;-2.07909;,
 -2.07702;-65.95020;4.07701;,
 -2.07702;-65.95020;-4.13069;,
 2.02738;-65.95020;4.07701;,
 2.02738;-65.95020;-4.13069;,
 4.07898;-65.95020;2.02531;,
 4.07898;-65.95020;-2.07909;,
 -6.55332;0.01850;3.23771;,
 -6.55332;-62.56770;3.23771;,
 6.50348;-62.56770;3.23771;,
 6.50348;0.01850;3.23771;,
 -2.57412;5.80640;1.24781;,
 -1.29952;5.80640;2.52221;,
 -2.57412;5.80640;-1.30159;,
 -1.29952;5.80640;-2.57599;,
 1.24978;5.80640;-2.57599;,
 1.24978;5.80640;2.52221;,
 2.52428;5.80640;-1.30159;,
 2.52428;5.80640;1.24781;,
 6.50348;-62.56770;-3.29149;,
 3.23958;-62.56770;-6.55519;,
 -3.28942;-62.56770;-6.55519;,
 -6.55332;-62.56770;-3.29149;;
 
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
  -0.870984;-0.335598;-0.358834;,
  -0.358804;-0.335594;-0.870997;,
  0.870986;-0.335594;-0.358831;,
  0.358810;-0.335591;-0.870996;,
  -0.870985;-0.335596;0.358832;,
  -0.358807;-0.335588;0.870999;,
  0.870987;-0.335594;0.358828;,
  0.358812;-0.335586;0.870997;,
  0.360209;0.325649;-0.874187;,
  -0.360204;0.325651;-0.874188;,
  -0.874171;0.325656;-0.360240;,
  -0.874171;0.325656;0.360240;,
  -0.360204;0.325651;0.874188;,
  0.360209;0.325649;0.874187;,
  0.874174;0.325653;0.360237;,
  0.874174;0.325653;-0.360237;,
  0.129231;0.940038;-0.315640;,
  -0.163345;0.902296;-0.398974;,
  0.398962;0.902298;-0.163361;,
  0.530407;0.819451;0.217184;,
  0.129231;0.940038;0.315640;,
  -0.106352;0.959797;0.259768;,
  -0.530402;0.819453;0.217187;,
  -0.398958;0.902300;-0.163364;,
  -0.126668;-0.942399;0.309580;,
  -0.520106;-0.827161;0.212825;,
  0.126672;-0.942399;0.309579;,
  0.391117;-0.906320;0.160038;,
  0.520110;-0.827159;-0.212824;,
  0.126670;-0.942400;-0.309577;,
  -0.126665;-0.942400;-0.309578;,
  -0.391109;-0.906322;-0.160042;;
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
