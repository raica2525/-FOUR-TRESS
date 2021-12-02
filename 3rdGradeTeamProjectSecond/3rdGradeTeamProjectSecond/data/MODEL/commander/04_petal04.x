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
 20;
 -228.65601;27.90678;66.99036;,
 -271.22308;27.90678;-17.22127;,
 -271.22308;10.06160;-17.22127;,
 -228.65601;10.06160;66.99036;,
 -249.70102;27.90678;-109.09127;,
 -249.70102;10.06160;-109.09127;,
 -174.16127;27.90678;-165.63419;,
 -174.16127;10.06160;-165.63419;,
 -79.94942;27.90678;-160.39310;,
 -79.94942;10.06160;-160.39310;,
 -11.14744;27.90678;-95.81964;,
 -11.14744;10.06160;-95.81964;,
 0.05045;27.90678;-2.12797;,
 0.05045;10.06160;-2.12797;,
 -51.59545;27.90678;76.84159;,
 -51.59545;10.06160;76.84159;,
 -141.91864;27.90678;104.13855;,
 -141.91864;10.06160;104.13855;,
 -134.25607;27.90678;-33.59117;,
 -134.25607;10.06160;-33.59117;;
 
 27;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,0,3,17;,
 3;18,1,0;,
 3;18,4,1;,
 3;18,6,4;,
 3;18,8,6;,
 3;18,10,8;,
 3;18,12,10;,
 3;18,14,12;,
 3;18,16,14;,
 3;18,0,16;,
 3;19,3,2;,
 3;19,2,5;,
 3;19,5,7;,
 3;19,7,9;,
 3;19,9,11;,
 3;19,11,13;,
 3;19,13,15;,
 3;19,15,17;,
 3;19,17,3;;
 
 MeshMaterialList {
  4;
  27;
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
    "data\\TEXTURE\\commander\\rafflesia.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\commander\\color_cm_001.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\commander\\red.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\commander\\color_cm_002.jpg";
   }
  }
 }
 MeshNormals {
  11;
  0.000000;1.000000;0.000000;,
  -0.684350;0.000000;0.729153;,
  -0.992934;0.000000;0.118671;,
  -0.836912;0.000000;-0.547338;,
  -0.289294;0.000000;-0.957240;,
  0.393687;0.000000;-0.919245;,
  0.892462;0.000000;-0.451123;,
  0.973641;0.000000;0.228088;,
  0.599240;0.000000;0.800569;,
  -0.055552;0.000000;0.998456;,
  0.000000;-1.000000;-0.000000;;
  27;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,1,1,9;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;;
 }
 MeshTextureCoords {
  20;
  0.165048;1.643280;,
  0.586106;1.856115;,
  0.586106;1.856115;,
  0.165048;1.643280;,
  1.045456;1.748505;,
  1.045456;1.748505;,
  1.328171;1.370806;,
  1.328171;1.370806;,
  1.301965;0.899747;,
  1.301965;0.899747;,
  0.979098;0.555737;,
  0.979098;0.555737;,
  0.510640;0.499748;,
  0.510640;0.499748;,
  0.115792;0.757977;,
  0.115792;0.757977;,
  -0.020693;1.209593;,
  -0.020693;1.209593;,
  0.667956;1.171280;,
  0.667956;1.171280;;
 }
}
