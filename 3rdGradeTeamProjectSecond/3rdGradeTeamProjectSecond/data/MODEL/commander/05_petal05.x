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
 -232.55135;8.16336;95.14081;,
 -275.11853;8.16336;10.92962;,
 -275.11832;-9.68181;10.92962;,
 -232.55135;-9.68181;95.14081;,
 -253.59583;8.16336;-80.94123;,
 -253.59583;-9.68181;-80.94123;,
 -178.05646;8.16336;-137.48450;,
 -178.05646;-9.68181;-137.48450;,
 -83.84444;8.16336;-132.24249;,
 -83.84444;-9.68181;-132.24249;,
 -15.04296;8.16336;-67.66877;,
 -15.04296;-9.68181;-67.66877;,
 -3.84528;8.16336;26.02232;,
 -3.84528;-9.68181;26.02232;,
 -55.49034;8.16336;104.99161;,
 -55.49034;-9.68181;104.99161;,
 -145.81305;8.16336;132.28851;,
 -145.81305;-9.68181;132.28851;,
 -138.15056;8.16336;-5.44057;,
 -138.15056;-9.68181;-5.44057;;
 
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
  -0.684347;-0.000003;0.729157;,
  -0.992934;-0.000006;0.118671;,
  -0.836912;-0.000003;-0.547337;,
  -0.289292;0.000000;-0.957241;,
  0.393694;0.000000;-0.919241;,
  0.892464;0.000000;-0.451119;,
  0.973641;0.000000;0.228085;,
  0.599243;0.000000;0.800567;,
  -0.055547;0.000000;0.998456;,
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
  0.024296;1.662757;,
  0.445352;1.875593;,
  0.445352;1.875592;,
  0.024296;1.662757;,
  0.904706;1.767979;,
  0.904706;1.767979;,
  1.187423;1.390282;,
  1.187423;1.390282;,
  1.161212;0.919222;,
  1.161212;0.919222;,
  0.838344;0.575215;,
  0.838344;0.575215;,
  0.369888;0.519226;,
  0.369888;0.519226;,
  -0.024958;0.777452;,
  -0.024958;0.777452;,
  -0.161443;1.229065;,
  -0.161443;1.229065;,
  0.527203;1.190753;,
  0.527203;1.190753;;
 }
}
