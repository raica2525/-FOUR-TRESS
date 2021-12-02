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
 43.33054;8.16399;85.14745;,
 0.76363;8.16399;0.93605;,
 0.76363;-9.68136;0.93605;,
 43.33054;-9.68136;85.14745;,
 22.28554;8.16399;-90.93535;,
 22.28554;-9.68136;-90.93517;,
 97.82584;8.16399;-147.47783;,
 97.82584;-9.68136;-147.47783;,
 192.03854;8.16399;-142.23685;,
 192.03854;-9.68136;-142.23685;,
 260.84079;8.16399;-77.66306;,
 260.84079;-9.68136;-77.66287;,
 272.03851;8.16399;16.02852;,
 272.03851;-9.68136;16.02852;,
 220.39284;8.16399;94.99825;,
 220.39284;-9.68136;94.99825;,
 130.06856;8.16399;122.29536;,
 130.06845;-9.68136;122.29536;,
 137.73146;8.16399;-15.43451;,
 137.73146;-9.68136;-15.43451;;
 
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
  -0.684349;0.000001;0.729155;,
  -0.992933;-0.000001;0.118673;,
  -0.836911;-0.000003;-0.547339;,
  -0.289292;-0.000002;-0.957241;,
  0.393687;-0.000002;-0.919245;,
  0.892463;-0.000002;-0.451121;,
  0.973641;-0.000000;0.228087;,
  0.599240;-0.000000;0.800569;,
  -0.055551;0.000000;0.998456;,
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
  0.074263;0.283347;,
  0.495320;0.496182;,
  0.495320;0.496182;,
  0.074263;0.283347;,
  0.954677;0.388572;,
  0.954676;0.388572;,
  1.237389;0.010871;,
  1.237389;0.010871;,
  1.211184;-0.460193;,
  1.211184;-0.460193;,
  0.888315;-0.804204;,
  0.888314;-0.804204;,
  0.419857;-0.860193;,
  0.419857;-0.860193;,
  0.025009;-0.601964;,
  0.025009;-0.601964;,
  -0.111477;-0.150343;,
  -0.111477;-0.150342;,
  0.577173;-0.188657;,
  0.577173;-0.188657;;
 }
}
