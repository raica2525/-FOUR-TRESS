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
 112;
 -6.56460;9.53060;8.33670;,
 -6.56460;3.64710;13.48660;,
 -3.43980;3.87850;14.34440;,
 -3.43980;10.13610;8.86680;,
 -6.56460;-3.62510;13.48660;,
 -3.43980;-3.85660;14.34440;,
 -6.56460;-9.50870;8.33670;,
 -3.43980;-10.11420;8.86680;,
 -6.56460;-11.75600;0.00390;,
 -3.43980;-12.50450;0.00390;,
 -6.56460;-9.50870;-8.32890;,
 -3.43980;-10.11420;-8.85900;,
 -6.56460;-3.62510;-13.47870;,
 -3.43980;-3.85660;-14.33630;,
 -6.56460;3.64710;-13.47870;,
 -3.43980;3.87850;-14.33630;,
 -6.56460;9.53060;-8.32890;,
 -3.43980;10.13610;-8.85900;,
 -6.56460;11.77790;0.00390;,
 -3.43980;12.52640;0.00390;,
 -0.08590;4.01500;14.85010;,
 -0.08590;10.49340;9.17950;,
 -0.08590;-3.99330;14.85010;,
 -0.08590;-10.47150;9.17950;,
 -0.08590;-12.94600;0.00390;,
 -0.08590;-10.47150;-9.17140;,
 -0.08590;-3.99330;-14.84230;,
 -0.08590;4.01500;-14.84230;,
 -0.08590;10.49340;-9.17140;,
 -0.08590;12.96780;0.00390;,
 3.26730;3.87850;14.34440;,
 3.26730;10.13610;8.86680;,
 3.26730;-3.85660;14.34440;,
 3.26730;-10.11420;8.86680;,
 3.26730;-12.50450;0.00390;,
 3.26730;-10.11420;-8.85900;,
 3.26730;-3.85660;-14.33630;,
 3.26730;3.87850;-14.33630;,
 3.26730;10.13610;-8.85900;,
 3.26730;12.52640;0.00390;,
 6.39260;3.47840;12.86110;,
 6.39260;9.08910;7.94990;,
 6.39260;-3.45650;12.86110;,
 6.39260;-9.06720;7.94990;,
 6.39260;-11.21010;0.00390;,
 6.39260;-9.06720;-7.94240;,
 6.39260;-3.45650;-12.85320;,
 6.39260;3.47840;-12.85320;,
 6.39260;9.08910;-7.94240;,
 6.39260;11.23200;0.00390;,
 9.07570;2.84210;10.50170;,
 9.07570;7.42320;6.49180;,
 9.07570;-2.82030;10.50170;,
 9.07570;-7.40130;6.49180;,
 9.07570;-9.15110;0.00390;,
 9.07570;-7.40130;-6.48430;,
 9.07570;-2.82030;-10.49390;,
 9.07570;2.84210;-10.49390;,
 9.07570;7.42320;-6.48430;,
 9.07570;9.17290;0.00390;,
 11.13470;2.01270;7.42720;,
 11.13470;5.25210;4.59160;,
 11.13470;-1.99110;7.42720;,
 11.13470;-5.23030;4.59160;,
 11.13470;-6.46740;0.00390;,
 11.13470;-5.23030;-4.58370;,
 11.13470;-1.99110;-7.41930;,
 11.13470;2.01270;-7.41930;,
 11.13470;5.25210;-4.58370;,
 11.13470;6.48950;0.00390;,
 12.42980;1.04730;3.84630;,
 12.42980;2.72420;2.37860;,
 12.42980;-1.02540;3.84630;,
 12.42980;-2.70230;2.37860;,
 12.42980;-3.34250;0.00390;,
 12.42980;-2.70200;-2.37080;,
 12.42980;-1.02540;-3.83850;,
 12.42980;1.04730;-3.83850;,
 12.42980;2.72420;-2.37080;,
 12.42980;3.36440;0.00390;,
 12.87100;0.01100;0.00390;,
 -24.67050;3.61230;12.40680;,
 -24.74560;9.14380;7.77350;,
 -45.85820;9.09830;7.36060;,
 -45.85820;3.90400;11.90750;,
 -24.67140;-3.07790;12.40740;,
 -45.85820;-2.51680;11.90750;,
 -24.74780;-8.60970;7.77430;,
 -45.85820;-7.71140;7.36060;,
 -24.80500;-10.82010;0.00390;,
 -45.85820;-9.69520;0.00390;,
 -24.74780;-8.60970;-7.76650;,
 -45.85820;-7.71140;-7.35310;,
 -24.67140;-3.07790;-12.39960;,
 -45.85820;-2.51680;-11.89970;,
 -24.67050;3.61230;-12.39900;,
 -45.85820;3.90400;-11.89970;,
 -24.70950;9.15180;-7.77260;,
 -45.82000;9.10900;-7.36030;,
 -24.80070;11.35730;-0.00240;,
 -45.88360;11.07780;0.00190;,
 -44.82010;8.47460;0.01000;,
 -44.77960;6.99710;5.52140;,
 -44.77240;6.99790;-5.51190;,
 -44.77960;3.10100;-8.92380;,
 -44.77960;-1.71420;-8.92380;,
 -44.77960;-5.61010;-5.51360;,
 -44.77960;-7.09810;0.00390;,
 -44.77960;-5.61010;5.52140;,
 -44.77960;-1.71420;8.93160;,
 -44.77960;3.10100;8.93160;,
 -44.78310;0.69260;0.00480;;
 
 120;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,0,3,19;,
 4;3,2,20,21;,
 4;2,5,22,20;,
 4;5,7,23,22;,
 4;7,9,24,23;,
 4;9,11,25,24;,
 4;11,13,26,25;,
 4;13,15,27,26;,
 4;15,17,28,27;,
 4;17,19,29,28;,
 4;19,3,21,29;,
 4;21,20,30,31;,
 4;20,22,32,30;,
 4;22,23,33,32;,
 4;23,24,34,33;,
 4;24,25,35,34;,
 4;25,26,36,35;,
 4;26,27,37,36;,
 4;27,28,38,37;,
 4;28,29,39,38;,
 4;29,21,31,39;,
 4;31,30,40,41;,
 4;30,32,42,40;,
 4;32,33,43,42;,
 4;33,34,44,43;,
 4;34,35,45,44;,
 4;35,36,46,45;,
 4;36,37,47,46;,
 4;37,38,48,47;,
 4;38,39,49,48;,
 4;39,31,41,49;,
 4;41,40,50,51;,
 4;40,42,52,50;,
 4;42,43,53,52;,
 4;43,44,54,53;,
 4;44,45,55,54;,
 4;45,46,56,55;,
 4;46,47,57,56;,
 4;47,48,58,57;,
 4;48,49,59,58;,
 4;49,41,51,59;,
 4;51,50,60,61;,
 4;50,52,62,60;,
 4;52,53,63,62;,
 4;53,54,64,63;,
 4;54,55,65,64;,
 4;55,56,66,65;,
 4;56,57,67,66;,
 4;57,58,68,67;,
 4;58,59,69,68;,
 4;59,51,61,69;,
 4;61,60,70,71;,
 4;60,62,72,70;,
 4;62,63,73,72;,
 4;63,64,74,73;,
 4;64,65,75,74;,
 4;65,66,76,75;,
 4;66,67,77,76;,
 4;67,68,78,77;,
 4;68,69,79,78;,
 4;69,61,71,79;,
 3;71,70,80;,
 3;70,72,80;,
 3;72,73,80;,
 3;73,74,80;,
 3;74,75,80;,
 3;75,76,80;,
 3;76,77,80;,
 3;77,78,80;,
 3;78,79,80;,
 3;79,71,80;,
 4;81,82,83,84;,
 4;85,81,84,86;,
 4;87,85,86,88;,
 4;89,87,88,90;,
 4;91,89,90,92;,
 4;93,91,92,94;,
 4;95,93,94,96;,
 4;97,95,96,98;,
 4;99,97,98,100;,
 4;82,99,100,83;,
 4;83,100,101,102;,
 4;100,98,103,101;,
 4;98,96,104,103;,
 4;96,94,105,104;,
 4;94,92,106,105;,
 4;92,90,107,106;,
 4;90,88,108,107;,
 4;88,86,109,108;,
 4;86,84,110,109;,
 4;84,83,102,110;,
 3;102,101,111;,
 3;101,103,111;,
 3;103,104,111;,
 3;104,105,111;,
 3;105,106,111;,
 3;106,107,111;,
 3;107,108,111;,
 3;108,109,111;,
 3;109,110,111;,
 3;110,102,111;,
 4;0,18,99,82;,
 4;18,16,97,99;,
 4;16,14,95,97;,
 4;14,12,93,95;,
 4;12,10,91,93;,
 4;10,8,89,91;,
 4;8,6,87,89;,
 4;6,4,85,87;,
 4;4,1,81,85;,
 4;1,0,82,81;;
 
 MeshMaterialList {
  5;
  120;
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
    "data\\TEXTURE\\ranger\\meisai.jpg";
   }
  }
  Material {
   0.690400;0.615200;0.480000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\ranger\\hada.jpg";
   }
  }
  Material {
   0.401600;0.401600;0.401600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\ranger\\green.jpg";
   }
  }
  Material {
   0.487080;0.487080;0.487080;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.177694;0.177694;0.177694;;
   TextureFilename {
    "data\\TEXTURE\\ranger\\white.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\ranger\\black.jpg";
   }
  }
 }
 MeshNormals {
  122;
  -0.141701;0.837791;0.527282;,
  -0.164263;0.344928;0.924144;,
  -0.169056;-0.344510;0.923435;,
  -0.153406;-0.836291;0.526388;,
  -0.144458;-0.989511;0.000000;,
  -0.153399;-0.836289;-0.526393;,
  -0.169032;-0.344506;-0.923441;,
  -0.164166;0.344781;-0.924216;,
  -0.141557;0.837766;-0.527361;,
  -0.130483;0.991450;0.000082;,
  -0.192681;0.832911;0.518781;,
  -0.213442;0.344241;0.914298;,
  -0.213450;-0.344240;0.914296;,
  -0.192693;-0.832908;0.518780;,
  -0.182013;-0.983296;-0.000001;,
  -0.192684;-0.832907;-0.518786;,
  -0.213450;-0.344236;-0.914298;,
  -0.213443;0.344237;-0.914299;,
  -0.192673;0.832909;-0.518787;,
  -0.182005;0.983298;-0.000001;,
  0.000014;0.848667;0.528927;,
  0.000016;0.352077;0.935971;,
  0.000016;-0.352080;0.935970;,
  0.000014;-0.848668;0.528926;,
  0.000013;-1.000000;-0.000002;,
  0.000015;-0.848667;-0.528928;,
  0.000016;-0.352082;-0.935969;,
  0.000016;0.352079;-0.935970;,
  0.000015;0.848666;-0.528929;,
  0.000014;1.000000;-0.000002;,
  0.273285;0.816848;0.508011;,
  0.300687;0.336674;0.892322;,
  0.300692;-0.336675;0.892320;,
  0.273294;-0.816846;0.508009;,
  0.259083;-0.965855;-0.000000;,
  0.273277;-0.816845;-0.508019;,
  0.300688;-0.336669;-0.892323;,
  0.300683;0.336668;-0.892325;,
  0.273269;0.816847;-0.508021;,
  0.259075;0.965857;-0.000000;,
  0.521979;0.725476;0.448579;,
  0.561938;0.294018;0.773162;,
  0.561936;-0.294020;0.773162;,
  0.521975;-0.725477;0.448581;,
  0.500441;-0.865771;0.000003;,
  0.521962;-0.725477;-0.448596;,
  0.561907;-0.294012;-0.773187;,
  0.561909;0.294010;-0.773186;,
  0.521967;0.725475;-0.448594;,
  0.500444;0.865769;0.000003;,
  0.727213;0.585080;0.358946;,
  0.761948;0.232199;0.604582;,
  0.761944;-0.232206;0.604584;,
  0.727208;-0.585087;0.358945;,
  0.707565;-0.706648;0.000003;,
  0.727218;-0.585076;-0.358944;,
  0.761947;-0.232193;-0.604585;,
  0.761949;0.232187;-0.604585;,
  0.727220;0.585071;-0.358947;,
  0.707565;0.706648;0.000003;,
  0.877914;0.408997;0.248974;,
  0.897658;0.159254;0.410912;,
  0.897657;-0.159260;0.410912;,
  0.877912;-0.409006;0.248967;,
  0.866249;-0.499612;-0.000003;,
  0.877921;-0.408990;-0.248962;,
  0.897663;-0.159254;-0.410902;,
  0.897660;0.159249;-0.410908;,
  0.877918;0.408991;-0.248972;,
  0.866248;0.499614;0.000000;,
  0.969403;0.210002;0.127112;,
  0.975008;0.080716;0.206990;,
  0.975008;-0.080716;0.206987;,
  0.969402;-0.210006;0.127108;,
  0.965991;-0.258575;-0.000009;,
  0.969402;-0.210003;-0.127112;,
  0.975008;-0.080721;-0.206985;,
  0.975007;0.080717;-0.206993;,
  0.969402;0.210003;-0.127114;,
  0.965991;0.258574;-0.000000;,
  1.000000;-0.000000;-0.000001;,
  -0.011903;0.843782;0.536554;,
  -0.019325;0.346691;0.937780;,
  -0.033214;-0.346305;0.937534;,
  -0.045723;-0.842770;0.536328;,
  -0.050563;-0.998721;0.000003;,
  -0.045719;-0.842768;-0.536333;,
  -0.033211;-0.346298;-0.937537;,
  -0.019306;0.345953;-0.938053;,
  -0.011887;0.843647;-0.536767;,
  -0.010458;0.999945;0.000534;,
  -0.982868;-0.159199;-0.092876;,
  -0.980691;-0.195561;-0.001471;,
  -0.983576;-0.155980;0.090820;,
  -0.986088;-0.058652;0.155536;,
  -0.985860;0.060816;0.156144;,
  -0.982739;0.158217;0.095875;,
  -0.980843;0.194800;-0.000001;,
  -0.982738;0.158222;-0.095878;,
  -0.985860;0.060820;-0.156146;,
  -0.985860;-0.060818;-0.156143;,
  -1.000000;-0.000891;-0.000089;,
  -0.023511;0.843561;0.536519;,
  -0.018340;0.999832;0.000349;,
  -0.023357;0.843456;-0.536691;,
  -0.036570;0.346031;-0.937510;,
  -0.048454;-0.346104;-0.936944;,
  -0.052260;-0.842521;-0.536122;,
  -0.052517;-0.998620;0.000001;,
  -0.052262;-0.842523;0.536119;,
  -0.048457;-0.346109;0.936942;,
  -0.036652;0.346546;0.937317;,
  -0.931733;-0.311677;-0.186361;,
  -0.924989;-0.379987;-0.002243;,
  -0.934208;-0.306288;0.182874;,
  -0.944174;-0.116974;0.307983;,
  -0.943274;0.120500;0.309377;,
  -0.930967;0.312249;0.189212;,
  -0.923528;0.383532;-0.000002;,
  -0.930963;0.312258;-0.189218;,
  -0.943271;0.120508;-0.309382;,
  -0.943274;-0.120504;-0.309376;;
  120;
  4;0,1,11,10;,
  4;1,2,12,11;,
  4;2,3,13,12;,
  4;3,4,14,13;,
  4;4,5,15,14;,
  4;5,6,16,15;,
  4;6,7,17,16;,
  4;7,8,18,17;,
  4;8,9,19,18;,
  4;9,0,10,19;,
  4;10,11,21,20;,
  4;11,12,22,21;,
  4;12,13,23,22;,
  4;13,14,24,23;,
  4;14,15,25,24;,
  4;15,16,26,25;,
  4;16,17,27,26;,
  4;17,18,28,27;,
  4;18,19,29,28;,
  4;19,10,20,29;,
  4;20,21,31,30;,
  4;21,22,32,31;,
  4;22,23,33,32;,
  4;23,24,34,33;,
  4;24,25,35,34;,
  4;25,26,36,35;,
  4;26,27,37,36;,
  4;27,28,38,37;,
  4;28,29,39,38;,
  4;29,20,30,39;,
  4;30,31,41,40;,
  4;31,32,42,41;,
  4;32,33,43,42;,
  4;33,34,44,43;,
  4;34,35,45,44;,
  4;35,36,46,45;,
  4;36,37,47,46;,
  4;37,38,48,47;,
  4;38,39,49,48;,
  4;39,30,40,49;,
  4;40,41,51,50;,
  4;41,42,52,51;,
  4;42,43,53,52;,
  4;43,44,54,53;,
  4;44,45,55,54;,
  4;45,46,56,55;,
  4;46,47,57,56;,
  4;47,48,58,57;,
  4;48,49,59,58;,
  4;49,40,50,59;,
  4;50,51,61,60;,
  4;51,52,62,61;,
  4;52,53,63,62;,
  4;53,54,64,63;,
  4;54,55,65,64;,
  4;55,56,66,65;,
  4;56,57,67,66;,
  4;57,58,68,67;,
  4;58,59,69,68;,
  4;59,50,60,69;,
  4;60,61,71,70;,
  4;61,62,72,71;,
  4;62,63,73,72;,
  4;63,64,74,73;,
  4;64,65,75,74;,
  4;65,66,76,75;,
  4;66,67,77,76;,
  4;67,68,78,77;,
  4;68,69,79,78;,
  4;69,60,70,79;,
  3;70,71,80;,
  3;71,72,80;,
  3;72,73,80;,
  3;73,74,80;,
  3;74,75,80;,
  3;75,76,80;,
  3;76,77,80;,
  3;77,78,80;,
  3;78,79,80;,
  3;79,70,80;,
  4;111,102,81,82;,
  4;110,111,82,83;,
  4;109,110,83,84;,
  4;108,109,84,85;,
  4;107,108,85,86;,
  4;106,107,86,87;,
  4;105,106,87,88;,
  4;104,105,88,89;,
  4;103,104,89,90;,
  4;102,103,90,81;,
  4;112,113,92,91;,
  4;113,114,93,92;,
  4;114,115,94,93;,
  4;115,116,95,94;,
  4;116,117,96,95;,
  4;117,118,97,96;,
  4;118,119,98,97;,
  4;119,120,99,98;,
  4;120,121,100,99;,
  4;121,112,91,100;,
  3;91,92,101;,
  3;92,93,101;,
  3;93,94,101;,
  3;94,95,101;,
  3;95,96,101;,
  3;96,97,101;,
  3;97,98,101;,
  3;98,99,101;,
  3;99,100,101;,
  3;100,91,101;,
  4;0,9,103,102;,
  4;9,8,104,103;,
  4;8,7,105,104;,
  4;7,6,106,105;,
  4;6,5,107,106;,
  4;5,4,108,107;,
  4;4,3,109,108;,
  4;3,2,110,109;,
  4;2,1,111,110;,
  4;1,0,102,111;;
 }
 MeshTextureCoords {
  112;
  0.467180;0.452350;,
  0.467180;0.481760;,
  0.482800;0.480610;,
  0.482800;0.449320;,
  0.467180;0.518130;,
  0.482800;0.519280;,
  0.467180;0.547540;,
  0.482800;0.550570;,
  0.467180;0.558780;,
  0.482800;0.562520;,
  0.467180;0.547540;,
  0.482800;0.550570;,
  0.467180;0.518130;,
  0.482800;0.519280;,
  0.467180;0.481760;,
  0.482800;0.480610;,
  0.467180;0.452350;,
  0.482800;0.449320;,
  0.467180;0.441110;,
  0.482800;0.437370;,
  0.499570;0.479930;,
  0.499570;0.447530;,
  0.499570;0.519970;,
  0.499570;0.552360;,
  0.499570;0.564730;,
  0.499570;0.552360;,
  0.499570;0.519970;,
  0.499570;0.479930;,
  0.499570;0.447530;,
  0.499570;0.435160;,
  0.516340;0.480610;,
  0.516340;0.449320;,
  0.516340;0.519280;,
  0.516340;0.550570;,
  0.516340;0.562520;,
  0.516340;0.550570;,
  0.516340;0.519280;,
  0.516340;0.480610;,
  0.516340;0.449320;,
  0.516340;0.437370;,
  0.531960;0.482610;,
  0.531960;0.454550;,
  0.531960;0.517280;,
  0.531960;0.545340;,
  0.531960;0.556050;,
  0.531960;0.545340;,
  0.531960;0.517280;,
  0.531960;0.482610;,
  0.531960;0.454550;,
  0.531960;0.443840;,
  0.545380;0.485790;,
  0.545380;0.462880;,
  0.545380;0.514100;,
  0.545380;0.537010;,
  0.545380;0.545760;,
  0.545380;0.537010;,
  0.545380;0.514100;,
  0.545380;0.485790;,
  0.545380;0.462880;,
  0.545380;0.454140;,
  0.555670;0.489940;,
  0.555670;0.473740;,
  0.555670;0.509960;,
  0.555670;0.526150;,
  0.555670;0.532340;,
  0.555670;0.526150;,
  0.555670;0.509960;,
  0.555670;0.489940;,
  0.555670;0.473740;,
  0.555670;0.467550;,
  0.562150;0.494760;,
  0.562150;0.486380;,
  0.562150;0.505130;,
  0.562150;0.513510;,
  0.562150;0.516710;,
  0.562150;0.513510;,
  0.562150;0.505130;,
  0.562150;0.494760;,
  0.562150;0.486380;,
  0.562150;0.483180;,
  0.564360;0.499950;,
  0.376650;0.481940;,
  0.376270;0.454280;,
  0.270710;0.454510;,
  0.270710;0.480480;,
  0.376640;0.515390;,
  0.270710;0.512580;,
  0.376260;0.543050;,
  0.270710;0.538560;,
  0.375980;0.554100;,
  0.270710;0.548480;,
  0.376260;0.543050;,
  0.270710;0.538560;,
  0.376640;0.515390;,
  0.270710;0.512580;,
  0.376650;0.481940;,
  0.270710;0.480480;,
  0.376450;0.454240;,
  0.270900;0.454450;,
  0.376000;0.443210;,
  0.270580;0.444610;,
  0.275900;0.457630;,
  0.276100;0.465010;,
  0.276140;0.465010;,
  0.276100;0.484500;,
  0.276100;0.508570;,
  0.276100;0.528050;,
  0.276100;0.535490;,
  0.276100;0.528050;,
  0.276100;0.508570;,
  0.276100;0.484500;,
  0.276080;0.496540;;
 }
}
