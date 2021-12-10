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
 69;
 0.00000;414.29263;-69.96262;,
 0.00000;25.37543;-69.96262;,
 184.15932;25.37543;-69.96262;,
 184.15932;414.29263;-69.96262;,
 0.00000;430.34360;-81.66317;,
 0.00000;430.34360;-65.96786;,
 190.52330;430.34360;-65.96786;,
 190.52330;430.34360;-81.66317;,
 0.00000;24.42685;-73.19442;,
 0.00000;415.24094;-73.19442;,
 185.90852;415.24094;-73.19442;,
 185.90852;24.42685;-73.19442;,
 0.00000;9.32404;-65.96786;,
 0.00000;9.32404;-81.66317;,
 190.52330;9.32404;-81.66317;,
 190.52330;9.32404;-65.96786;,
 317.53928;9.32404;70.39957;,
 317.53928;9.32404;54.70393;,
 317.53928;430.34360;54.70393;,
 317.53928;430.34360;70.39957;,
 -317.53928;9.32404;54.70393;,
 -317.53928;9.32404;70.39957;,
 -317.53928;430.34360;70.39957;,
 -317.53928;430.34360;54.70393;,
 -190.52330;9.32404;-65.96786;,
 -190.52330;9.32404;-81.66317;,
 -185.90852;24.42685;-73.19442;,
 -185.90852;415.24094;-73.19442;,
 -190.52330;430.34360;-81.66317;,
 -190.52330;430.34360;-65.96786;,
 -184.15932;414.29263;-69.96262;,
 -184.15932;25.37543;-69.96262;,
 -317.53928;9.32404;54.70393;,
 -317.53928;9.32404;70.39957;,
 -309.84750;415.24094;63.17272;,
 -309.84750;24.42685;63.17272;,
 -317.53928;430.34360;54.70393;,
 -306.93188;25.37543;66.40453;,
 -306.93188;414.29263;66.40453;,
 306.93188;25.37543;66.40453;,
 306.93188;414.29263;66.40453;,
 317.53928;430.34360;54.70393;,
 309.84750;415.24094;63.17272;,
 309.84750;24.42685;63.17272;,
 317.53928;9.32404;54.70393;,
 317.53928;9.32404;70.39957;,
 0.00000;9.32404;-65.96786;,
 190.52330;9.32404;-65.96786;,
 184.15932;25.37543;-65.96786;,
 0.00000;25.37543;-65.96786;,
 0.00000;414.29263;-65.96786;,
 184.15932;414.29263;-65.96786;,
 -190.52330;9.32404;-65.96786;,
 -184.15932;25.37543;-65.96786;,
 -184.15932;414.29263;-65.96786;,
 -306.93188;25.37543;70.39957;,
 -306.93188;414.29263;70.39957;,
 306.93188;25.37543;70.39957;,
 306.93188;414.29263;70.39957;,
 185.90825;415.24094;-81.66317;,
 0.00000;415.24094;-81.66317;,
 0.00000;24.42685;-81.66317;,
 185.90825;24.42685;-81.66317;,
 -185.90852;415.24094;-81.66317;,
 -185.90852;24.42685;-81.66317;,
 -309.84750;415.24094;54.70393;,
 -309.84750;24.42685;54.70393;,
 309.84750;415.24094;54.70393;,
 309.84750;24.42685;54.70393;;
 
 58;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,13,12;,
 4;26,27,9,8;,
 4;28,29,5,4;,
 4;30,31,1,0;,
 4;32,25,24,33;,
 4;34,27,26,35;,
 4;22,29,28,36;,
 4;37,31,30,38;,
 4;3,2,39,40;,
 4;7,6,19,41;,
 4;11,10,42,43;,
 4;15,14,44,45;,
 4;46,47,48,49;,
 4;6,5,50,51;,
 4;52,46,49,53;,
 4;5,29,54,50;,
 4;21,52,53,55;,
 4;29,22,56,54;,
 4;22,21,55,56;,
 4;47,16,57,48;,
 4;16,19,58,57;,
 4;19,6,51,58;,
 4;49,48,2,1;,
 4;51,50,0,3;,
 4;53,49,1,31;,
 4;50,54,30,0;,
 4;55,53,31,37;,
 4;54,56,38,30;,
 4;56,55,37,38;,
 4;48,57,39,2;,
 4;57,58,40,39;,
 4;58,51,3,40;,
 4;4,7,59,60;,
 4;14,13,61,62;,
 4;28,4,60,63;,
 4;13,25,64,61;,
 4;36,28,63,65;,
 4;25,32,66,64;,
 4;32,36,65,66;,
 4;7,41,67,59;,
 4;41,44,68,67;,
 4;44,14,62,68;,
 4;60,59,10,9;,
 4;62,61,8,11;,
 4;63,60,9,27;,
 4;61,64,26,8;,
 4;65,63,27,34;,
 4;64,66,35,26;,
 4;66,65,34,35;,
 4;59,67,42,10;,
 4;67,68,43,42;,
 4;68,62,11,43;;
 
 MeshMaterialList {
  3;
  58;
  2,
  1,
  2,
  1,
  1,
  1,
  1,
  2,
  1,
  2,
  1,
  2,
  1,
  2,
  2,
  1,
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
   0.400000;0.400000;0.400000;1.000000;;
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
    "data\\TEXTURE\\lightwall\\gaisou.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\lightwall\\naisou.png";
   }
  }
 }
 MeshNormals {
  26;
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -0.923402;-0.154610;-0.351317;,
  0.923402;-0.154613;-0.351317;,
  -0.923403;0.154608;-0.351317;,
  0.923402;0.154612;-0.351317;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.381153;-0.199512;0.902728;,
  -0.381152;0.199517;0.902727;,
  0.381152;0.199517;0.902727;,
  0.381153;-0.199512;0.902728;,
  -0.406761;0.000000;0.913535;,
  0.406761;0.000000;0.913535;,
  0.933590;0.000000;0.358343;,
  -0.933590;0.000000;0.358343;,
  0.000000;0.000000;-1.000000;,
  0.388418;-0.157241;-0.907968;,
  0.388418;0.157240;-0.907969;,
  -0.388419;0.157236;-0.907969;,
  -0.388419;-0.157238;-0.907969;,
  0.404611;0.000000;-0.914489;,
  -0.404611;0.000000;-0.914489;,
  -0.740024;0.000000;-0.672580;,
  0.740024;0.000000;-0.672580;;
  58;
  4;8,8,13,13;,
  4;7,7,7,7;,
  4;17,17,22,22;,
  4;6,6,6,6;,
  4;1,5,3,1;,
  4;4,0,0,2;,
  4;6,6,6,6;,
  4;23,23,17,17;,
  4;7,7,7,7;,
  4;14,14,8,8;,
  4;6,6,6,6;,
  4;24,23,23,24;,
  4;7,7,7,7;,
  4;15,14,14,15;,
  4;13,13,16,16;,
  4;7,7,7,7;,
  4;22,22,25,25;,
  4;6,6,6,6;,
  4;8,9,9,8;,
  4;10,8,8,10;,
  4;12,8,8,12;,
  4;8,11,11,8;,
  4;12,12,12,12;,
  4;11,11,11,11;,
  4;11,12,12,11;,
  4;9,9,9,9;,
  4;9,10,10,9;,
  4;10,10,10,10;,
  4;7,7,7,7;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;6,6,6,6;,
  4;1,1,15,15;,
  4;7,7,7,7;,
  4;0,0,16,16;,
  4;6,6,6,6;,
  4;17,18,18,17;,
  4;19,17,17,19;,
  4;21,17,17,21;,
  4;17,20,20,17;,
  4;2,21,21,21;,
  4;20,4,20,20;,
  4;17,17,21,20;,
  4;18,3,18,18;,
  4;17,17,19,18;,
  4;5,19,19,19;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;1,1,1,1;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;7,7,7,7;;
 }
 MeshTextureCoords {
  69;
  0.500000;0.250000;,
  0.500000;0.000000;,
  0.575000;0.000000;,
  0.575000;0.250000;,
  0.500000;0.500000;,
  0.500000;0.250000;,
  0.575000;0.250000;,
  0.575000;0.500000;,
  0.500000;0.750000;,
  0.500000;0.500000;,
  0.575000;0.500000;,
  0.575000;0.750000;,
  0.500000;1.000000;,
  0.500000;0.750000;,
  0.575000;0.750000;,
  0.575000;1.000000;,
  0.625000;0.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.625000;0.250000;,
  0.125000;0.000000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.125000;0.250000;,
  0.425000;1.000000;,
  0.425000;0.750000;,
  0.425000;0.750000;,
  0.425000;0.500000;,
  0.425000;0.500000;,
  0.425000;0.250000;,
  0.425000;0.250000;,
  0.425000;0.000000;,
  0.375000;0.750000;,
  0.375000;1.000000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.375000;0.500000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.500000;,
  0.625000;0.500000;,
  0.625000;0.750000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.500000;0.000000;,
  0.575000;0.000000;,
  0.575000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.575000;0.250000;,
  0.425000;0.000000;,
  0.425000;0.000000;,
  0.425000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.575000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.750000;,
  0.575000;0.750000;,
  0.425000;0.500000;,
  0.425000;0.750000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.500000;,
  0.625000;0.750000;;
 }
}
