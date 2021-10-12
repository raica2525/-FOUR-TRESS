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
 -14.08983;-9.95980;8.63288;,
 -8.46171;-9.95980;7.61578;,
 -8.46171;-0.98240;9.68498;,
 -14.08982;0.05440;9.68498;,
 -0.21933;-5.78240;7.21628;,
 -0.21933;-5.78240;-8.42002;,
 -0.21933;0.05441;-8.42002;,
 -0.21933;0.05441;7.21628;,
 -8.46171;-9.95980;-8.81962;,
 -14.08983;-9.95980;-9.83662;,
 -14.08982;0.05440;-10.88872;,
 -8.46171;-0.98240;-10.88872;,
 -24.59237;-9.95980;-4.96492;,
 -24.59237;-9.95980;3.76108;,
 -24.59235;0.05441;4.85978;,
 -24.59235;0.05441;-6.06352;,
 -12.80242;13.87812;7.97918;,
 -6.66860;17.30123;9.51938;,
 -6.66860;17.30123;-10.72312;,
 -12.80242;13.87812;-9.18292;,
 -19.71783;-9.95980;7.61578;,
 -19.71782;0.05440;9.68498;,
 -24.59236;10.61391;4.85978;,
 -19.71784;10.61391;8.37288;,
 -19.71784;10.61402;-9.57652;,
 -24.59236;10.61401;-6.06352;,
 -19.71783;-9.95980;-8.81962;,
 -19.71782;0.05440;-10.88872;,
 0.11477;9.70061;7.91888;,
 0.11477;9.70071;-9.12272;,
 -6.66860;0.05440;11.84488;,
 -12.80242;0.05440;10.60948;,
 0.11477;0.05441;-9.12272;,
 0.11477;0.05441;7.91888;,
 -6.66860;0.05440;-13.04882;,
 -12.80242;0.05440;-11.81322;,
 -14.08982;10.61401;-9.57652;,
 -14.08982;10.61391;8.37288;;
 
 36;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;9,8,1,0;,
 4;13,20,21,14;,
 4;22,23,24,25;,
 4;26,12,15,27;,
 4;12,26,20,13;,
 4;5,8,11,6;,
 4;17,28,29,18;,
 4;1,4,7,2;,
 4;8,5,4,1;,
 4;30,17,16,31;,
 4;32,29,28,33;,
 4;19,18,34,35;,
 4;14,22,25,15;,
 4;21,23,22,14;,
 4;15,25,24,27;,
 4;34,18,29,32;,
 4;33,28,17,30;,
 4;27,24,36,10;,
 4;9,26,27,10;,
 4;26,9,0,20;,
 4;20,0,3,21;,
 4;37,23,21,3;,
 4;23,37,36,24;,
 4;37,16,19,36;,
 4;2,30,31,3;,
 4;3,31,16,37;,
 4;6,32,33,7;,
 4;36,19,35,10;,
 4;10,35,34,11;,
 4;11,34,32,6;,
 4;7,33,30,2;;
 
 MeshMaterialList {
  10;
  36;
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
    "data\\TEXTURE\\icarus\\gray.jpg";
   }
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\icarus\\red2.jpg";
   }
  }
  Material {
   0.009600;0.009600;0.009600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\icarus\\black.jpg";
   }
  }
  Material {
   0.000000;0.367200;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\icarus\\blue2.jpg";
   }
  }
  Material {
   0.031200;0.800000;0.455200;0.700000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\icarus\\green.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\icarus\\white.jpg";
   }
  }
  Material {
   0.150400;0.156800;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\icarus\\blue.jpg";
   }
  }
  Material {
   0.800000;0.536800;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\icarus\\yellow.jpg";
   }
  }
  Material {
   0.800000;0.166400;0.068800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\icarus\\red.jpg";
   }
  }
  Material {
   0.094400;0.094400;0.094400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\icarus\\black.jpg";
   }
  }
 }
 MeshNormals {
  49;
  -0.910581;-0.063553;0.408416;,
  -0.000001;1.000000;0.000008;,
  1.000000;0.000000;0.000000;,
  -0.910581;-0.063549;-0.408416;,
  -0.392303;-0.141157;0.908941;,
  0.000000;1.000000;0.000007;,
  -0.392300;-0.141151;-0.908943;,
  0.151673;-0.138267;-0.978712;,
  0.151675;-0.138272;0.978711;,
  -0.909692;-0.019711;0.414816;,
  -0.909691;-0.019708;-0.414818;,
  -0.370778;-0.026896;0.928332;,
  -0.370775;-0.026890;-0.928333;,
  -0.196588;0.137356;-0.970818;,
  -0.101607;-0.012133;-0.994751;,
  -0.005007;-0.158811;-0.987296;,
  -0.005007;-0.158815;0.987296;,
  -0.101600;-0.012138;0.994751;,
  -0.196574;0.137350;0.970821;,
  -0.752646;0.658426;0.000001;,
  -0.487321;0.873223;0.000000;,
  0.934365;0.356317;0.000001;,
  -0.319225;0.151163;0.935545;,
  0.096038;0.116310;0.988559;,
  1.000000;-0.000000;-0.000000;,
  -0.319247;0.151166;-0.935537;,
  0.096031;0.116315;-0.988559;,
  0.000000;-1.000000;-0.000000;,
  0.232400;-0.972620;-0.000000;,
  -0.000001;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000000;,
  0.224820;-0.111786;-0.967967;,
  0.746076;0.665860;0.000002;,
  0.224816;-0.111791;0.967967;,
  0.452074;-0.891981;-0.000000;,
  -0.907002;0.024343;0.420422;,
  -0.907001;0.024345;-0.420425;,
  -0.343727;0.089203;0.934823;,
  -0.343724;0.089209;-0.934824;,
  0.431660;0.062698;-0.899855;,
  0.431657;0.062693;0.899857;,
  0.000001;1.000000;0.000006;,
  -0.930261;0.366899;0.000001;,
  -0.018466;-0.964699;0.262705;,
  -0.139230;-0.916753;0.374405;,
  0.051627;-0.996073;-0.071923;,
  0.051629;-0.996073;0.071928;,
  -0.139235;-0.916758;-0.374390;,
  -0.018470;-0.964703;-0.262692;;
  36;
  4;16,8,8,17;,
  4;2,2,2,2;,
  4;7,15,14,7;,
  4;3,0,9,10;,
  4;19,20,20,19;,
  4;27,28,28,27;,
  4;0,4,11,9;,
  4;1,5,5,1;,
  4;6,3,10,12;,
  4;29,30,30,29;,
  4;31,7,7,31;,
  4;32,21,21,32;,
  4;8,33,33,8;,
  4;28,34,34,28;,
  4;23,23,22,22;,
  4;24,21,21,24;,
  4;25,26,26,25;,
  4;9,35,36,10;,
  4;11,37,35,9;,
  4;10,36,38,12;,
  4;26,26,39,39;,
  4;40,40,23,23;,
  4;12,38,13,14;,
  4;15,6,12,14;,
  4;30,27,27,30;,
  4;4,16,17,11;,
  4;18,37,11,17;,
  4;5,41,41,5;,
  4;42,19,19,42;,
  4;43,43,44,44;,
  4;17,22,22,18;,
  4;45,45,46,46;,
  4;13,25,25,14;,
  4;47,47,48,48;,
  4;48,48,45,45;,
  4;46,46,43,43;;
 }
}
