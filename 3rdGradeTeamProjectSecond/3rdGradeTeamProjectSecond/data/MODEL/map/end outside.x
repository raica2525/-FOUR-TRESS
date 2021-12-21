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
 153;
 4.24988;3.79357;3.79384;,
 4.24988;3.79357;4.23127;,
 0.31302;3.79357;4.23127;,
 0.31302;3.79357;3.79384;,
 -3.62383;3.79357;4.23127;,
 -3.62383;3.79357;3.79384;,
 -4.06125;12.10468;4.23127;,
 -4.06125;12.10468;3.79384;,
 -4.06125;8.16784;3.79384;,
 -4.06125;8.16784;4.23127;,
 0.31302;12.54211;4.23127;,
 0.31302;12.54211;3.79384;,
 -3.62383;12.54211;3.79384;,
 -3.62383;12.54211;4.23127;,
 4.24988;12.54211;4.23127;,
 4.24988;12.54211;3.79384;,
 4.68730;8.16784;4.23127;,
 4.68730;8.16784;3.79384;,
 4.68730;12.10468;3.79384;,
 4.68730;12.10468;4.23127;,
 4.24988;12.54211;-4.07986;,
 4.24988;12.54211;-4.51730;,
 0.31302;12.54211;-4.51730;,
 0.31302;12.54211;-4.07987;,
 -3.62383;12.54211;-4.51730;,
 -3.62383;12.54211;-4.07987;,
 -4.06125;8.16784;-4.51730;,
 -4.06125;8.16784;-4.07987;,
 -4.06125;12.10468;-4.07986;,
 -4.06125;12.10468;-4.51730;,
 0.31302;3.79357;-4.51730;,
 0.31302;3.79357;-4.07987;,
 -3.62383;3.79357;-4.07986;,
 -3.62383;3.79357;-4.51730;,
 4.24988;3.79357;-4.51730;,
 4.24988;3.79357;-4.07987;,
 4.68730;12.10468;-4.51730;,
 4.68730;12.10468;-4.07987;,
 4.68730;8.16784;-4.07987;,
 4.68730;8.16784;-4.51730;,
 4.68730;3.79357;-4.07987;,
 4.68730;3.79357;-4.51730;,
 4.68730;3.79357;-0.14304;,
 4.24988;3.79357;-0.14304;,
 4.68730;3.79357;3.79384;,
 4.68730;3.79357;4.23127;,
 4.68730;12.10468;4.23127;,
 4.24988;12.10468;4.23127;,
 4.24988;8.16784;4.23127;,
 4.68730;8.16784;4.23127;,
 4.68730;12.54211;3.79384;,
 4.68730;12.54211;4.23127;,
 4.68730;12.54211;-0.14304;,
 4.24988;12.54211;-0.14304;,
 4.68730;12.54211;-4.07987;,
 4.68730;12.54211;-4.51730;,
 4.24988;8.16784;-4.51730;,
 4.24988;12.10468;-4.51730;,
 -4.06125;3.79357;-4.07987;,
 -3.62383;3.79357;-0.14304;,
 -4.06125;3.79357;-0.14304;,
 -4.06125;3.79357;-4.51730;,
 -3.62383;12.10468;-4.51730;,
 -3.62383;8.16784;-4.51730;,
 -4.06125;12.54211;-4.07987;,
 -4.06125;12.54211;-4.51730;,
 -3.62383;12.54211;-0.14304;,
 -4.06125;12.54211;-0.14304;,
 -4.06125;12.54211;3.79384;,
 -4.06125;12.54211;4.23127;,
 -4.06125;8.16784;4.23127;,
 -3.62383;8.16784;4.23127;,
 -3.62383;12.10468;4.23127;,
 -4.06125;12.10468;4.23127;,
 -4.06125;3.79357;3.79384;,
 -4.06125;3.79357;4.23127;,
 4.68730;4.23099;-4.51730;,
 4.24988;4.23099;-4.51730;,
 -3.62383;4.23099;-4.51730;,
 -4.06125;4.23099;-4.51730;,
 -4.06125;4.23099;-4.07987;,
 -4.06125;4.23099;3.79384;,
 -4.06125;4.23099;4.23127;,
 -4.06125;4.23099;4.23127;,
 -3.62383;4.23099;4.23127;,
 4.24988;4.23099;4.23127;,
 4.68730;4.23099;4.23127;,
 4.68730;4.23099;4.23127;,
 4.68730;4.23099;3.79384;,
 4.68730;4.23099;-4.07986;,
 4.68730;3.79357;-4.51730;,
 4.24988;3.79357;-4.51730;,
 0.31302;4.23099;-4.51730;,
 0.31302;3.79357;-4.51730;,
 -3.62383;3.79357;-4.51730;,
 -4.06125;3.79357;-4.51730;,
 -4.06125;3.79357;-4.07987;,
 -4.06125;4.23099;-0.14304;,
 -4.06125;3.79357;-0.14304;,
 -4.06125;3.79357;3.79384;,
 -4.06125;3.79357;4.23127;,
 0.31302;4.23099;4.23127;,
 4.68730;3.79357;4.23127;,
 4.68730;3.79357;3.79384;,
 4.68730;4.23099;-0.14304;,
 4.68730;3.79357;-0.14304;,
 4.68730;3.79357;-4.07987;,
 0.31302;12.10468;4.23127;,
 -4.06125;12.54211;3.79384;,
 -4.06125;12.54211;4.23127;,
 -4.06125;12.54211;-0.14304;,
 -4.06125;12.10468;-0.14304;,
 -4.06125;12.54211;-4.07987;,
 0.31302;12.10468;-4.51730;,
 4.68730;12.54211;-4.07987;,
 4.68730;12.54211;-0.14304;,
 4.68730;12.10468;-0.14304;,
 4.68730;12.54211;3.79384;,
 4.68730;12.54211;4.23127;,
 0.31302;12.10468;-4.07987;,
 4.24988;12.10468;-4.07986;,
 -3.62383;12.10468;-4.07987;,
 0.31302;4.23099;-4.07987;,
 -3.62383;4.23099;-4.07986;,
 4.24988;4.23099;-4.07987;,
 -3.62383;8.16784;-4.07986;,
 4.24988;8.16784;-4.07986;,
 0.31302;4.23099;3.79384;,
 4.24988;4.23099;3.79384;,
 -3.62383;4.23099;3.79384;,
 0.31302;12.10468;3.79384;,
 -3.62383;12.10468;3.79384;,
 4.24988;12.10468;3.79384;,
 4.24988;8.16784;3.79384;,
 -3.62383;8.16784;3.79384;,
 -3.62383;12.10468;-0.14304;,
 4.24988;12.10468;-0.14304;,
 -3.62383;4.23099;-0.14304;,
 4.24988;4.23099;-0.14304;,
 5.39678;0.25823;-4.92650;,
 -4.77074;0.25823;-4.92650;,
 -4.77074;1.82408;-4.92650;,
 5.39678;1.82408;-4.92650;,
 -4.77074;1.82408;4.94326;,
 5.39678;1.82408;4.94326;,
 -4.77074;0.25823;4.94326;,
 5.39678;0.25823;4.94326;,
 -4.77074;0.25823;-4.92650;,
 5.39678;0.25823;-4.92650;,
 -4.77074;0.25823;4.94326;,
 -4.77074;1.82408;4.94326;,
 5.39678;0.25823;4.94326;,
 5.39678;1.82408;4.94326;;
 
 126;
 4;0,1,2,3;,
 4;4,5,3,2;,
 4;6,7,8,9;,
 4;10,11,12,13;,
 4;14,15,11,10;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,23,22;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;34,35,31,30;,
 4;36,37,38,39;,
 4;40,35,34,41;,
 4;42,43,35,40;,
 4;44,0,43,42;,
 4;45,1,0,44;,
 4;46,47,48,49;,
 4;50,15,14,51;,
 4;52,53,15,50;,
 4;54,20,53,52;,
 4;55,21,20,54;,
 4;39,56,57,36;,
 4;58,32,59,60;,
 4;33,32,58,61;,
 4;29,62,63,26;,
 4;64,25,24,65;,
 4;66,25,64,67;,
 4;68,12,66,67;,
 4;13,12,68,69;,
 4;70,71,72,73;,
 4;74,5,4,75;,
 4;59,5,74,60;,
 4;76,77,56,39;,
 4;26,63,78,79;,
 4;79,80,27,26;,
 4;9,8,81,82;,
 4;83,84,71,70;,
 4;49,48,85,86;,
 4;87,88,17,16;,
 4;39,38,89,76;,
 4;90,91,77,76;,
 4;92,77,91,93;,
 4;78,92,93,94;,
 4;79,78,94,95;,
 4;95,96,80,79;,
 4;97,80,96,98;,
 4;81,97,98,99;,
 4;82,81,99,100;,
 4;4,84,83,75;,
 4;2,101,84,4;,
 4;1,85,101,2;,
 4;86,85,1,45;,
 4;102,103,88,87;,
 4;104,88,103,105;,
 4;89,104,105,106;,
 4;76,89,106,90;,
 4;51,14,47,46;,
 4;107,47,14,10;,
 4;72,107,10,13;,
 4;73,72,13,69;,
 4;108,7,6,109;,
 4;110,111,7,108;,
 4;112,28,111,110;,
 4;29,28,112,65;,
 4;24,62,29,65;,
 4;22,113,62,24;,
 4;21,57,113,22;,
 4;36,57,21,55;,
 4;114,37,36,55;,
 4;115,116,37,114;,
 4;117,18,116,115;,
 4;19,18,117,118;,
 4;20,23,119,120;,
 4;23,25,121,119;,
 4;122,123,32,31;,
 4;124,122,31,35;,
 4;77,92,122,124;,
 4;92,78,123,122;,
 4;62,113,119,121;,
 4;113,57,120,119;,
 4;123,78,63,125;,
 4;56,126,120,57;,
 4;125,63,62,121;,
 4;77,124,126,56;,
 4;28,27,125,121;,
 4;27,80,123,125;,
 4;89,38,126,124;,
 4;38,37,120,126;,
 4;0,3,127,128;,
 4;3,5,129,127;,
 4;130,131,12,11;,
 4;132,130,11,15;,
 4;47,107,130,132;,
 4;107,72,131,130;,
 4;84,101,127,129;,
 4;101,85,128,127;,
 4;48,133,128,85;,
 4;131,72,71,134;,
 4;47,132,133,48;,
 4;134,71,84,129;,
 4;81,8,134,129;,
 4;8,7,131,134;,
 4;18,17,133,132;,
 4;17,88,128,133;,
 4;28,121,135,111;,
 4;66,135,121,25;,
 4;120,37,116,136;,
 4;53,20,120,136;,
 4;59,137,129,5;,
 4;97,81,129,137;,
 4;89,124,138,104;,
 4;43,138,124,35;,
 4;136,116,18,132;,
 4;53,136,132,15;,
 4;66,12,131,135;,
 4;111,135,131,7;,
 4;43,0,128,138;,
 4;104,138,128,88;,
 4;32,123,137,59;,
 4;97,137,123,80;,
 4;139,140,141,142;,
 4;142,141,143,144;,
 4;144,143,145,146;,
 4;146,145,147,148;,
 4;140,149,150,141;,
 4;151,139,142,152;;
 
 MeshMaterialList {
  4;
  126;
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
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
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
    "data\\TEXTURE\\end portal\\murasaki.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\end portal\\midori.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\end portal\\kuro.png";
   }
  }
 }
 MeshNormals {
  16;
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.000001;0.000000;1.000000;,
  0.000012;0.000000;1.000000;,
  -0.000012;0.000000;1.000000;,
  0.000001;0.000000;1.000000;,
  -0.000003;0.000000;1.000000;,
  0.000003;0.000000;1.000000;,
  -0.000013;0.000000;1.000000;,
  -0.000027;0.000000;1.000000;,
  0.000013;0.000000;1.000000;,
  0.000027;0.000000;1.000000;;
  126;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;10,6,6,7;,
  4;6,5,5,6;,
  4;9,8,11,9;,
  4;5,9,9,5;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;5,12,12,5;,
  4;12,13,8,12;,
  4;5,14,14,5;,
  4;14,15,7,14;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;2,2,2,2;;
 }
 MeshTextureCoords {
  153;
  0.387500;0.762500;,
  0.387500;0.750000;,
  0.500000;0.750000;,
  0.500000;0.762500;,
  0.612500;0.750000;,
  0.612500;0.762500;,
  0.875000;0.237500;,
  0.862500;0.237500;,
  0.862500;0.125000;,
  0.875000;0.125000;,
  0.500000;0.500000;,
  0.500000;0.487500;,
  0.612500;0.487500;,
  0.612500;0.500000;,
  0.387500;0.500000;,
  0.387500;0.487500;,
  0.125000;0.125000;,
  0.137500;0.125000;,
  0.137500;0.237500;,
  0.125000;0.237500;,
  0.387500;0.262500;,
  0.387500;0.250000;,
  0.500000;0.250000;,
  0.500000;0.262500;,
  0.612500;0.250000;,
  0.612500;0.262500;,
  0.625000;0.125000;,
  0.637500;0.125000;,
  0.637500;0.237500;,
  0.625000;0.237500;,
  0.500000;1.000000;,
  0.500000;0.987500;,
  0.612500;0.987500;,
  0.612500;1.000000;,
  0.387500;1.000000;,
  0.387500;0.987500;,
  0.375000;0.237500;,
  0.362500;0.237500;,
  0.362500;0.125000;,
  0.375000;0.125000;,
  0.375000;0.987500;,
  0.375000;1.000000;,
  0.375000;0.875000;,
  0.387500;0.875000;,
  0.375000;0.762500;,
  0.375000;0.750000;,
  0.375000;0.512500;,
  0.387500;0.512500;,
  0.387500;0.625000;,
  0.375000;0.625000;,
  0.375000;0.487500;,
  0.375000;0.500000;,
  0.375000;0.375000;,
  0.387500;0.375000;,
  0.375000;0.262500;,
  0.375000;0.250000;,
  0.387500;0.125000;,
  0.387500;0.237500;,
  0.625000;0.987500;,
  0.612500;0.875000;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.612500;0.237500;,
  0.612500;0.125000;,
  0.625000;0.262500;,
  0.625000;0.250000;,
  0.612500;0.375000;,
  0.625000;0.375000;,
  0.625000;0.487500;,
  0.625000;0.500000;,
  0.625000;0.625000;,
  0.612500;0.625000;,
  0.612500;0.512500;,
  0.625000;0.512500;,
  0.625000;0.762500;,
  0.625000;0.750000;,
  0.375000;0.012500;,
  0.387500;0.012500;,
  0.612500;0.012500;,
  0.625000;0.012500;,
  0.637500;0.012500;,
  0.862500;0.012500;,
  0.875000;0.012500;,
  0.625000;0.737500;,
  0.612500;0.737500;,
  0.387500;0.737500;,
  0.375000;0.737500;,
  0.125000;0.012500;,
  0.137500;0.012500;,
  0.362500;0.012500;,
  0.375000;0.000000;,
  0.387500;0.000000;,
  0.500000;0.012500;,
  0.500000;0.000000;,
  0.612500;0.000000;,
  0.625000;0.000000;,
  0.637500;0.000000;,
  0.750000;0.012500;,
  0.750000;0.000000;,
  0.862500;0.000000;,
  0.875000;0.000000;,
  0.500000;0.737500;,
  0.125000;0.000000;,
  0.137500;0.000000;,
  0.250000;0.012500;,
  0.250000;0.000000;,
  0.362500;0.000000;,
  0.500000;0.512500;,
  0.862500;0.250000;,
  0.875000;0.250000;,
  0.750000;0.250000;,
  0.750000;0.237500;,
  0.637500;0.250000;,
  0.500000;0.237500;,
  0.362500;0.250000;,
  0.250000;0.250000;,
  0.250000;0.237500;,
  0.137500;0.250000;,
  0.125000;0.250000;,
  0.500000;0.298750;,
  0.387500;0.298750;,
  0.612500;0.298750;,
  0.500000;0.951250;,
  0.612500;0.951250;,
  0.387500;0.951250;,
  0.612500;0.625000;,
  0.387500;0.625000;,
  0.500000;0.748750;,
  0.387500;0.748750;,
  0.612500;0.748750;,
  0.500000;0.501250;,
  0.612500;0.501250;,
  0.387500;0.501250;,
  0.387500;0.625000;,
  0.612500;0.625000;,
  0.612500;0.400000;,
  0.387500;0.400000;,
  0.612500;0.850000;,
  0.387500;0.850000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;;
 }
}
