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
 76;
 -8.18994;1.12992;15.77647;,
 -8.18994;34.33422;15.77647;,
 -10.58807;26.67819;15.21687;,
 -10.58804;7.11071;15.21687;,
 -10.58807;26.67819;-17.20403;,
 -10.58804;7.11071;-17.20403;,
 12.42527;5.55710;-17.20403;,
 12.42526;29.90689;-17.20403;,
 12.42526;29.90689;15.21687;,
 12.42527;5.55710;15.21687;,
 -8.18996;34.33412;-17.20403;,
 -8.18994;1.12992;-17.20403;,
 6.91805;1.12993;15.77647;,
 6.91805;34.33422;15.77647;,
 3.55825;34.33423;16.00027;,
 3.55824;1.12992;16.00027;,
 6.91806;34.33413;-17.20403;,
 3.55825;34.33412;-17.20403;,
 0.76166;6.89620;-18.87563;,
 -0.27845;6.89620;-18.87563;,
 1.43255;9.48732;-18.87563;,
 -0.71475;10.39661;-18.87563;,
 1.43256;23.73827;-18.87563;,
 -0.71474;21.84865;-18.87563;,
 0.07636;26.32937;-18.87563;,
 0.40707;26.32937;-18.87563;,
 6.91805;1.12993;-17.20403;,
 3.55824;1.12992;-17.20403;,
 -4.61283;93.08221;11.53217;,
 -4.61283;93.08221;-1.27072;,
 -5.58426;93.08221;-1.27072;,
 -5.58426;93.08221;11.53217;,
 -3.63454;34.33421;16.00027;,
 -3.63454;1.12991;16.00027;,
 -3.63454;1.12991;-17.20403;,
 -3.63455;34.33413;-17.20403;,
 1.33236;31.03569;-17.92803;,
 -1.50765;31.03570;-17.92803;,
 10.13898;27.48798;-17.92803;,
 10.13897;7.97601;-17.92803;,
 4.37986;4.42842;-17.92803;,
 -4.55505;4.42841;-17.92803;,
 -8.30203;9.22100;-17.92803;,
 -8.30205;24.90077;-17.92803;,
 1.31095;30.34229;-18.49363;,
 -1.38124;30.34229;-18.49363;,
 9.65847;26.97946;-18.49363;,
 9.65847;8.48449;-18.49363;,
 4.19947;5.12171;-18.49363;,
 -4.26985;5.12171;-18.49363;,
 -7.82124;9.66453;-18.49363;,
 -7.82124;24.52717;-18.49363;,
 0.57495;26.32936;-18.49363;,
 -0.90804;26.32938;-18.49363;,
 5.17417;23.73826;-18.49363;,
 5.17417;9.48730;-18.49363;,
 2.16667;6.89618;-18.49363;,
 -2.49974;6.89619;-18.49363;,
 -4.45635;10.39661;-18.49363;,
 -4.45634;21.84867;-18.49363;,
 0.57495;26.32936;-14.63543;,
 -0.90804;26.32938;-14.63543;,
 5.17417;23.73826;-14.63543;,
 5.17417;9.48730;-14.63543;,
 2.16667;6.89618;-14.63543;,
 -2.49974;6.89619;-14.63543;,
 -4.45635;10.39661;-14.63543;,
 -4.45634;21.84867;-14.63543;,
 0.44255;26.32937;-14.63543;,
 -0.13234;26.32936;-14.63543;,
 2.22517;23.73826;-14.63543;,
 2.22516;9.48730;-14.63543;,
 1.05945;6.89620;-14.63543;,
 -0.74905;6.89619;-14.63543;,
 -1.50734;10.39659;-14.63543;,
 -1.50734;21.84867;-14.63543;;
 
 79;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;6,7,8,9;,
 4;1,10,4,2;,
 4;11,0,3,5;,
 4;12,13,14,15;,
 4;13,16,17,14;,
 3;18,19,20;,
 3;19,21,20;,
 3;20,21,22;,
 3;21,23,22;,
 3;23,24,22;,
 3;24,25,22;,
 4;26,12,15,27;,
 4;9,8,13,12;,
 4;8,7,16,13;,
 4;6,9,12,26;,
 4;28,29,30,31;,
 4;15,14,32,33;,
 4;27,15,33,34;,
 4;32,35,10,1;,
 4;33,32,1,0;,
 4;34,33,0,11;,
 4;35,17,36,37;,
 3;17,16,36;,
 4;16,7,38,36;,
 4;7,6,39,38;,
 4;6,26,40,39;,
 3;26,27,40;,
 4;27,34,41,40;,
 3;34,11,41;,
 4;11,5,42,41;,
 4;5,4,43,42;,
 4;4,10,37,43;,
 3;10,35,37;,
 4;37,36,44,45;,
 4;36,38,46,44;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,41,49,48;,
 4;41,42,50,49;,
 4;42,43,51,50;,
 4;43,37,45,51;,
 4;45,44,52,53;,
 4;44,46,54,52;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,49,57,56;,
 4;49,50,58,57;,
 4;50,51,59,58;,
 4;51,45,53,59;,
 4;53,52,60,61;,
 4;52,54,62,60;,
 4;54,55,63,62;,
 4;55,56,64,63;,
 4;56,57,65,64;,
 4;57,58,66,65;,
 4;58,59,67,66;,
 4;59,53,61,67;,
 4;61,60,68,69;,
 4;60,62,70,68;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;64,65,73,72;,
 4;65,66,74,73;,
 4;66,67,75,74;,
 4;67,61,69,75;,
 4;69,68,25,24;,
 4;68,70,22,25;,
 4;70,71,20,22;,
 4;71,72,18,20;,
 4;72,73,19,18;,
 4;73,74,21,19;,
 4;74,75,23,21;,
 4;75,69,24,23;,
 4;14,17,29,28;,
 4;17,35,30,29;,
 4;35,32,31,30;,
 4;32,14,28,31;;
 
 MeshMaterialList {
  10;
  79;
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  7,
  7,
  7,
  7,
  7,
  9,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  0,
  9,
  9,
  9,
  9,
  0,
  0,
  0,
  0,
  9,
  9,
  9,
  0,
  9,
  9,
  9,
  0,
  7,
  7,
  7,
  0,
  7,
  7,
  7,
  6,
  6,
  6,
  6;;
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
  76;
  0.901815;-0.432123;-0.000000;,
  0.901818;0.432116;-0.000001;,
  -0.227245;-0.000000;0.973838;,
  -0.981877;-0.189517;0.000000;,
  -0.988504;0.151194;-0.000000;,
  -0.138720;-0.000000;0.990332;,
  -0.954280;0.298914;-0.000000;,
  -0.928167;-0.372164;0.000000;,
  0.083791;-0.000000;0.996483;,
  0.332128;0.943234;-0.000002;,
  0.332123;-0.943236;-0.000000;,
  -0.000002;1.000000;-0.000003;,
  0.022180;0.025307;0.999434;,
  0.033251;-0.000000;0.999447;,
  0.000002;-1.000000;-0.000000;,
  0.000000;1.000000;-0.000003;,
  -0.016371;0.025302;0.999546;,
  -0.024542;-0.000000;0.999699;,
  -0.000001;-1.000000;0.000000;,
  -0.123239;0.350459;-0.928434;,
  0.069893;0.375779;-0.924070;,
  0.378829;0.204306;-0.902634;,
  0.403386;-0.186634;-0.895795;,
  0.092247;-0.363958;-0.926836;,
  -0.141890;-0.327141;-0.934262;,
  -0.458580;-0.132336;-0.878744;,
  -0.440374;0.163990;-0.882711;,
  -0.123898;0.307486;-0.943452;,
  0.065351;0.330798;-0.941436;,
  0.279752;0.168950;-0.945090;,
  0.301895;-0.149324;-0.941574;,
  0.089051;-0.313125;-0.945528;,
  -0.138983;-0.278814;-0.950235;,
  -0.349488;-0.110366;-0.930418;,
  -0.337028;0.140500;-0.930952;,
  0.000000;0.000000;-1.000000;,
  0.435417;-0.900229;-0.000000;,
  -0.253728;-0.967276;0.000000;,
  -0.490844;-0.871248;0.000000;,
  -0.909042;0.416705;0.000000;,
  -0.348134;0.937445;0.000000;,
  0.000002;1.000000;0.000000;,
  0.967701;0.252100;0.000000;,
  0.944445;-0.328668;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000008;1.000000;0.000000;,
  0.101091;0.000000;0.994877;,
  -0.000003;-1.000000;0.000000;,
  0.000000;0.230243;-0.973133;,
  0.000000;0.230243;-0.973133;,
  0.046532;0.181416;-0.982305;,
  0.199066;0.074543;-0.977147;,
  0.208553;-0.078842;-0.974828;,
  0.056112;-0.185801;-0.980984;,
  0.000000;-0.214390;-0.976748;,
  -0.000000;-0.214390;-0.976748;,
  -0.081335;-0.157500;-0.984164;,
  -0.232778;-0.049713;-0.971259;,
  -0.216927;0.053457;-0.974723;,
  -0.065052;0.160948;-0.984817;,
  -1.000000;-0.000000;0.000000;,
  0.872891;0.487915;0.000000;,
  -0.000007;1.000000;0.000001;,
  0.879889;0.468274;-0.080716;,
  0.960765;0.241510;-0.136395;,
  0.973990;-0.166827;-0.153338;,
  0.936920;-0.328842;-0.118509;,
  -0.000001;-1.000000;-0.000002;,
  -0.975455;-0.165873;-0.144825;,
  -0.982794;-0.083239;-0.164884;,
  -0.981855;0.116939;-0.149282;,
  -0.966143;0.232139;-0.112604;,
  0.990466;0.137761;-0.000000;,
  0.000001;0.261758;-0.965134;,
  -0.999450;-0.033169;0.000000;,
  0.000000;0.075836;0.997120;;
  79;
  4;5,5,2,2;,
  4;3,4,4,3;,
  4;0,1,1,0;,
  4;6,6,4,4;,
  4;7,7,3,3;,
  4;8,8,12,13;,
  4;9,9,11,11;,
  3;44,35,35;,
  3;35,35,35;,
  3;35,35,35;,
  3;35,35,35;,
  3;35,35,35;,
  3;35,44,35;,
  4;10,10,14,14;,
  4;46,46,8,8;,
  4;1,1,9,9;,
  4;0,0,10,10;,
  4;45,45,45,45;,
  4;13,12,16,17;,
  4;14,14,18,18;,
  4;15,15,15,15;,
  4;17,16,5,5;,
  4;18,18,47,47;,
  4;48,49,20,19;,
  3;49,50,20;,
  4;50,51,21,20;,
  4;51,52,22,21;,
  4;52,53,23,22;,
  3;53,54,23;,
  4;54,55,24,23;,
  3;55,56,24;,
  4;56,57,25,24;,
  4;57,58,26,25;,
  4;58,59,19,26;,
  3;59,48,19;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,19,27,34;,
  4;27,28,35,35;,
  4;28,29,35,35;,
  4;29,30,35,35;,
  4;30,31,35,35;,
  4;31,32,35,35;,
  4;32,33,35,35;,
  4;33,34,35,35;,
  4;34,27,35,35;,
  4;36,37,37,36;,
  4;37,38,38,37;,
  4;60,39,39,60;,
  4;39,40,40,39;,
  4;40,41,41,40;,
  4;61,42,42,61;,
  4;42,43,43,42;,
  4;43,36,36,43;,
  4;35,35,35,35;,
  4;35,35,35,35;,
  4;35,35,35,35;,
  4;35,35,35,35;,
  4;35,35,35,35;,
  4;35,35,35,35;,
  4;35,35,35,35;,
  4;35,35,35,35;,
  4;62,62,62,62;,
  4;63,64,64,63;,
  4;64,65,65,64;,
  4;65,66,66,65;,
  4;67,67,67,67;,
  4;68,69,69,68;,
  4;69,70,70,69;,
  4;70,71,71,70;,
  4;72,72,72,72;,
  4;49,48,73,73;,
  4;74,74,74,74;,
  4;16,12,75,75;;
 }
}
