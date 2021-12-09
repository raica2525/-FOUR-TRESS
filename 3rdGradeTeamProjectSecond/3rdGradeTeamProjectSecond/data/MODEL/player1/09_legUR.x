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
 38;
 -6.53520;9.14375;-3.26470;,
 -6.53520;9.14375;3.26450;,
 -3.27130;9.14375;-6.52840;,
 -3.27130;9.14375;6.52830;,
 3.25770;9.14375;-6.52840;,
 3.25770;9.14375;6.52830;,
 6.52160;9.14375;-3.26470;,
 6.52160;9.14375;3.26450;,
 -6.53520;9.14375;3.26450;,
 -6.53520;9.14375;-3.26470;,
 -6.53520;-53.44184;-3.26470;,
 -6.53520;-53.44184;3.26450;,
 -6.53520;-53.44184;3.26450;,
 -3.27130;-53.44184;6.52830;,
 3.25770;-53.44184;6.52830;,
 6.52160;-53.44184;3.26450;,
 6.52160;9.14375;-3.26470;,
 6.52160;9.14375;3.26450;,
 6.52160;-53.44184;3.26450;,
 6.52160;-53.44184;-3.26470;,
 3.25770;-53.44184;-6.52840;,
 -3.27130;-53.44184;-6.52840;,
 -0.82910;-60.27084;0.41120;,
 -0.82910;-60.27084;-0.41130;,
 -0.41800;-60.27084;0.82230;,
 -0.41800;-60.27084;-0.82240;,
 0.40440;-60.27084;0.82230;,
 0.40440;-60.27084;-0.82240;,
 0.81560;-60.27084;0.41120;,
 0.81560;-60.27084;-0.41130;,
 -5.61720;-58.06705;2.80540;,
 -2.81230;-58.06705;5.61040;,
 2.79870;-58.06705;5.61040;,
 5.60360;-58.06705;2.80540;,
 5.60360;-58.06705;-2.80550;,
 2.79870;-58.06705;-5.61060;,
 -2.81230;-58.06705;-5.61060;,
 -5.61720;-58.06705;-2.80550;;
 
 36;
 3;0,1,2;,
 3;1,3,2;,
 3;2,3,4;,
 3;3,5,4;,
 3;4,5,6;,
 3;6,5,7;,
 4;8,9,10,11;,
 4;1,12,13,3;,
 4;14,5,3,13;,
 4;5,14,15,7;,
 4;16,17,18,19;,
 4;20,4,16,19;,
 4;2,4,20,21;,
 4;10,9,2,21;,
 3;22,23,24;,
 3;23,25,24;,
 3;24,25,26;,
 3;25,27,26;,
 3;26,27,28;,
 3;28,27,29;,
 4;12,30,31,13;,
 4;13,31,32,14;,
 4;14,32,33,18;,
 4;18,33,34,19;,
 4;19,34,35,20;,
 4;20,35,36,21;,
 4;21,36,37,10;,
 4;10,37,30,12;,
 4;30,22,24,31;,
 4;31,24,26,32;,
 4;32,26,28,33;,
 4;33,28,29,34;,
 4;34,29,27,35;,
 4;35,27,25,36;,
 4;36,25,23,37;,
 4;37,23,22,30;;
 
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
  33;
  0.000000;1.000000;0.000000;,
  -0.918476;-0.108884;-0.380192;,
  -0.918477;-0.108884;0.380189;,
  -0.380182;-0.108878;0.918481;,
  0.380182;-0.108878;0.918481;,
  0.918477;-0.108884;0.380189;,
  0.918476;-0.108884;-0.380192;,
  0.380179;-0.108872;-0.918483;,
  -0.380179;-0.108872;-0.918483;,
  -0.698585;-0.655606;0.286636;,
  -0.286639;-0.655603;0.698587;,
  0.286632;-0.655602;0.698590;,
  0.698582;-0.655607;0.286640;,
  0.698583;-0.655607;-0.286639;,
  0.286634;-0.655601;-0.698591;,
  -0.286640;-0.655601;-0.698588;,
  -0.698585;-0.655606;-0.286634;,
  -0.239203;-0.966188;0.096242;,
  -0.057629;-0.988010;0.143229;,
  0.057625;-0.988010;0.143232;,
  0.179406;-0.981123;0.072188;,
  0.239199;-0.966189;-0.096245;,
  0.057625;-0.988010;-0.143230;,
  -0.057629;-0.988011;-0.143227;,
  -0.179410;-0.981123;-0.072183;,
  -0.923877;0.000000;0.382691;,
  -0.923874;0.000000;-0.382698;,
  -0.382676;0.000000;0.923882;,
  0.382676;0.000000;0.923882;,
  0.923877;0.000000;0.382691;,
  0.923874;0.000000;-0.382698;,
  0.382669;0.000000;-0.923885;,
  -0.382669;0.000000;-0.923885;;
  36;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;25,26,1,2;,
  4;25,2,3,27;,
  4;4,28,27,3;,
  4;28,4,5,29;,
  4;30,29,5,6;,
  4;7,31,30,6;,
  4;32,31,7,8;,
  4;1,26,32,8;,
  3;17,24,18;,
  3;24,23,18;,
  3;18,23,19;,
  3;23,22,19;,
  3;19,22,20;,
  3;20,22,21;,
  4;2,9,10,3;,
  4;3,10,11,4;,
  4;4,11,12,5;,
  4;5,12,13,6;,
  4;6,13,14,7;,
  4;7,14,15,8;,
  4;8,15,16,1;,
  4;1,16,9,2;,
  4;9,17,18,10;,
  4;10,18,19,11;,
  4;11,19,20,12;,
  4;12,20,21,13;,
  4;13,21,22,14;,
  4;14,22,23,15;,
  4;15,23,24,16;,
  4;16,24,17,9;;
 }
 MeshTextureCoords {
  38;
  0.375000;0.312490;,
  0.375000;0.437510;,
  0.437490;0.250000;,
  0.437490;0.500000;,
  0.562510;0.250000;,
  0.562510;0.500000;,
  0.625000;0.312490;,
  0.625000;0.437510;,
  0.187490;0.250000;,
  0.312510;0.250000;,
  0.312510;0.125000;,
  0.187490;0.125000;,
  0.375000;0.625000;,
  0.437490;0.625000;,
  0.562510;0.625000;,
  0.625000;0.625000;,
  0.687490;0.250000;,
  0.812510;0.250000;,
  0.812510;0.125000;,
  0.687490;0.125000;,
  0.562510;0.125000;,
  0.437490;0.125000;,
  0.375000;0.625000;,
  0.312510;0.125000;,
  0.437490;0.625000;,
  0.437490;0.125000;,
  0.562510;0.625000;,
  0.562510;0.125000;,
  0.812510;0.125000;,
  0.687490;0.125000;,
  0.375000;0.625000;,
  0.437490;0.625000;,
  0.562510;0.625000;,
  0.812510;0.125000;,
  0.687490;0.125000;,
  0.562510;0.125000;,
  0.437490;0.125000;,
  0.312510;0.125000;;
 }
}