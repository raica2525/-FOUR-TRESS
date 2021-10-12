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
 144;
 14.08597;-30.05849;-9.86000;,
 13.56097;-36.64098;-9.27210;,
 8.80957;-37.20168;-13.60590;,
 9.12217;-30.58669;-14.42510;,
 8.95237;-24.29309;-14.56650;,
 13.98577;-23.81698;-9.90290;,
 -4.40273;-31.67579;-14.42180;,
 -3.44603;-38.13828;-13.60650;,
 -8.18823;-38.61288;-9.24240;,
 -9.36043;-32.14529;-9.83840;,
 -10.02533;-25.97338;-9.89130;,
 -4.99493;-25.53468;-14.56040;,
 13.43307;-17.42369;4.93740;,
 12.53877;-10.87858;5.26410;,
 7.66057;-11.47589;9.92830;,
 8.43797;-17.95549;9.61930;,
 8.95447;-24.25159;9.23940;,
 13.98467;-23.81358;4.56970;,
 -5.33123;-19.32408;9.61000;,
 -5.45473;-12.92639;9.92220;,
 -10.35983;-13.30758;5.25670;,
 -10.33993;-19.71869;4.92630;,
 -10.03143;-25.93858;4.55970;,
 -4.99233;-25.53349;9.22650;,
 13.44347;-17.51098;-9.63420;,
 8.43967;-17.98009;-14.31750;,
 7.66307;-11.49658;-13.87080;,
 12.55607;-11.00068;-9.20360;,
 -5.33583;-19.33229;-14.31650;,
 -10.33913;-19.72367;-9.62880;,
 -10.36083;-13.30648;-9.20330;,
 -5.46413;-12.92268;-13.87550;,
 -9.37783;-32.03098;4.07230;,
 -8.21273;-38.44649;3.30870;,
 -3.44083;-38.20229;7.64250;,
 -4.39883;-31.71259;8.63880;,
 9.12747;-30.47939;8.65560;,
 8.81437;-37.04999;7.66000;,
 13.55877;-36.78928;3.29280;,
 14.08567;-30.15359;4.06680;,
 -8.67953;-38.56258;-2.96400;,
 -9.84803;-32.12369;-2.88140;,
 -10.50663;-25.99348;-2.66550;,
 14.03737;-36.67368;-2.99300;,
 14.56357;-30.06499;-2.89890;,
 14.46287;-23.77179;-2.66720;,
 -10.81793;-19.75108;-2.35100;,
 -10.83923;-13.33308;-1.97250;,
 13.91537;-17.41969;-2.34840;,
 13.02367;-10.88618;-1.96970;,
 5.82587;0.62192;10.45960;,
 5.28017;2.72642;10.13710;,
 -4.97693;1.30892;10.16220;,
 -5.22533;-0.85047;10.46400;,
 4.18237;8.95981;5.60080;,
 -5.45853;7.65671;5.57170;,
 9.36577;3.30042;5.83590;,
 8.65927;5.90012;2.91880;,
 10.27567;1.23932;5.89540;,
 -9.12453;0.75632;5.83300;,
 -9.72753;-1.39468;5.88700;,
 -9.01923;3.44912;2.80810;,
 9.79027;3.36391;-1.10060;,
 8.76937;3.74572;-0.85980;,
 10.73827;1.29822;-1.22970;,
 10.27887;1.23221;-8.35610;,
 9.37507;3.31061;-8.03970;,
 8.97367;5.42402;-6.57860;,
 -9.56533;0.70212;-1.11770;,
 -10.19913;-1.44319;-1.24250;,
 -8.63483;1.20632;-1.09370;,
 -9.47173;3.49172;-6.32720;,
 -9.14693;0.76232;-8.06240;,
 -9.73543;-1.38198;-8.36900;,
 -5.00063;1.32952;-12.36000;,
 -5.24773;-0.81748;-12.92900;,
 -5.44323;5.44562;-9.80150;,
 5.28287;2.74921;-12.35340;,
 5.81997;0.65043;-12.92520;,
 4.37407;6.63532;-10.11600;,
 -5.87313;9.70421;0.77100;,
 3.90087;10.99212;0.86920;,
 4.91297;3.19832;-1.03950;,
 -4.70193;1.85442;-1.12770;,
 3.95197;8.38712;-7.18820;,
 -5.84233;7.23142;-6.50120;,
 11.40977;-4.07218;5.64420;,
 6.70457;-4.69789;10.29910;,
 -5.40193;-6.18208;10.29540;,
 -10.14743;-6.64108;5.63590;,
 -5.41843;-6.15959;-13.42370;,
 -10.14983;-6.63207;-8.76630;,
 11.42017;-4.14558;-8.76080;,
 6.70167;-4.69229;-13.41890;,
 -10.62853;-6.67608;-1.56530;,
 11.89027;-4.04939;-1.55820;,
 -9.18083;6.35592;0.18580;,
 -8.63633;1.20762;-1.13610;,
 -9.16713;4.86461;-4.13720;,
 7.96147;6.86793;-5.33330;,
 7.91967;8.66681;0.38140;,
 6.87487;-50.28059;-9.99140;,
 6.36547;-52.46838;-9.03450;,
 -0.05273;-53.15619;-9.03110;,
 -0.68543;-51.02608;-9.98780;,
 6.16867;-52.75398;-7.18800;,
 0.16397;-53.40659;-7.19040;,
 9.91537;-52.08269;-5.89700;,
 9.28937;-52.34549;-5.18730;,
 10.78137;-49.84789;-6.52610;,
 -3.58433;-53.53039;-5.87190;,
 -4.57823;-51.42949;-6.49910;,
 -2.93543;-53.66898;-5.17770;,
 10.36197;-52.03288;-2.70000;,
 9.50607;-52.38959;-2.69180;,
 11.25127;-49.80919;-2.75490;,
 10.78507;-49.86839;1.01590;,
 9.93007;-52.07838;0.49630;,
 9.30107;-52.34299;-0.20010;,
 -4.00553;-53.57309;-2.70830;,
 -5.04183;-51.45828;-2.75190;,
 -3.12113;-53.76179;-2.70720;,
 -2.91503;-53.66508;-0.23820;,
 -3.56003;-53.52389;0.45420;,
 -4.57603;-51.39568;0.99300;,
 -0.04453;-53.14909;3.60870;,
 -0.68333;-51.02789;4.46890;,
 0.17517;-53.40388;1.77600;,
 6.36307;-52.46159;3.62790;,
 6.86727;-50.24638;4.47790;,
 6.17187;-52.75188;1.80300;,
 6.10557;-52.84879;-2.68890;,
 0.24227;-53.48939;-2.70600;,
 12.22787;-43.96909;-7.90610;,
 7.87507;-44.47909;-11.82150;,
 -2.01173;-45.30418;-11.82080;,
 -6.35343;-45.74879;-7.87590;,
 -6.36953;-45.63559;2.11330;,
 -2.00883;-45.34319;6.03300;,
 7.87247;-44.37408;6.04470;,
 12.22657;-44.06659;2.11180;,
 -6.83873;-45.73109;-2.87900;,
 12.70477;-43.97218;-2.89880;,
 -4.70403;1.88062;-1.06430;;
 
 146;
 4;0,1,2,3;,
 4;0,3,4,5;,
 4;6,7,8,9;,
 4;6,9,10,11;,
 4;12,13,14,15;,
 4;12,15,16,17;,
 4;18,19,20,21;,
 4;18,21,22,23;,
 4;24,5,4,25;,
 4;24,25,26,27;,
 4;28,11,10,29;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,35,23,22;,
 4;36,37,38,39;,
 4;36,39,17,16;,
 4;3,2,7,6;,
 4;3,6,11,4;,
 4;36,16,23,35;,
 4;36,35,34,37;,
 4;8,40,41,9;,
 4;40,33,32,41;,
 4;41,32,22,42;,
 4;9,41,42,10;,
 4;38,43,44,39;,
 4;43,1,0,44;,
 4;44,0,5,45;,
 4;39,44,45,17;,
 4;15,14,19,18;,
 4;15,18,23,16;,
 4;10,42,46,29;,
 4;42,22,21,46;,
 4;46,21,20,47;,
 4;29,46,47,30;,
 4;25,4,11,28;,
 4;25,28,31,26;,
 4;17,45,48,12;,
 4;45,5,24,48;,
 4;48,24,27,49;,
 4;12,48,49,13;,
 4;50,51,52,53;,
 4;51,54,55,52;,
 4;54,51,56,57;,
 4;51,50,58,56;,
 4;53,52,59,60;,
 4;52,55,61,59;,
 4;57,56,62,63;,
 4;56,58,64,62;,
 4;62,64,65,66;,
 4;63,62,66,67;,
 4;60,59,68,69;,
 4;59,61,70,68;,
 4;68,70,71,72;,
 4;69,68,72,73;,
 4;73,72,74,75;,
 4;72,71,76,74;,
 4;75,74,77,78;,
 4;74,76,79,77;,
 4;78,77,66,65;,
 4;77,79,67,66;,
 4;80,81,82,83;,
 4;82,84,85,83;,
 4;86,58,50,87;,
 4;86,87,14,13;,
 4;88,53,60,89;,
 4;88,89,20,19;,
 4;90,31,30,91;,
 4;90,91,73,75;,
 4;92,27,26,93;,
 4;92,93,78,65;,
 4;19,14,87,88;,
 4;87,50,53,88;,
 4;30,47,94,91;,
 4;47,20,89,94;,
 4;94,89,60,69;,
 4;91,94,69,73;,
 4;93,26,31,90;,
 4;93,90,75,78;,
 4;13,49,95,86;,
 4;49,27,92,95;,
 4;95,92,65,64;,
 4;86,95,64,58;,
 4;96,80,83,97;,
 4;83,85,98,97;,
 4;63,99,84,82;,
 4;63,82,81,100;,
 4;101,102,103,104;,
 4;102,105,106,103;,
 4;105,102,107,108;,
 4;102,101,109,107;,
 4;104,103,110,111;,
 4;103,106,112,110;,
 4;108,107,113,114;,
 4;107,109,115,113;,
 4;113,115,116,117;,
 4;114,113,117,118;,
 4;111,110,119,120;,
 4;110,112,121,119;,
 4;119,121,122,123;,
 4;120,119,123,124;,
 4;124,123,125,126;,
 4;123,122,127,125;,
 4;126,125,128,129;,
 4;125,127,130,128;,
 4;129,128,117,116;,
 4;128,130,118,117;,
 4;106,105,131,132;,
 4;131,130,127,132;,
 4;133,109,101,134;,
 4;133,134,2,1;,
 4;135,104,111,136;,
 4;135,136,8,7;,
 4;137,124,126,138;,
 4;137,138,34,33;,
 4;139,129,116,140;,
 4;139,140,38,37;,
 4;7,2,134,135;,
 4;134,101,104,135;,
 4;8,136,141,40;,
 4;136,111,120,141;,
 4;141,120,124,137;,
 4;40,141,137,33;,
 4;139,37,34,138;,
 4;139,138,126,129;,
 4;38,140,142,43;,
 4;140,116,115,142;,
 4;142,115,109,133;,
 4;43,142,133,1;,
 4;114,118,130,131;,
 4;114,131,105,108;,
 4;112,106,132,121;,
 4;132,127,122,121;,
 3;82,83,143;,
 4;76,85,84,79;,
 4;143,83,97,70;,
 4;70,97,98,71;,
 4;71,98,85,76;,
 4;79,84,99,67;,
 3;67,99,63;,
 3;143,83,82;,
 4;54,81,80,55;,
 4;61,96,97,70;,
 4;70,97,83,143;,
 4;55,80,96,61;,
 3;63,100,57;,
 4;57,100,81,54;;
 
 MeshMaterialList {
  6;
  146;
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
   0.401600;0.401600;0.401600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\x\\gray.jpg";
   }
  }
  Material {
   0.000000;0.608800;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\x\\blue.jpg";
   }
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\x\\red.jpg";
   }
  }
  Material {
   0.787200;0.800000;0.016000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\x\\yellow.jpg";
   }
  }
  Material {
   0.800000;0.633600;0.373600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\x\\hada.jpg";
   }
  }
  Material {
   0.184800;0.184800;0.184800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\x\\black.jpg";
   }
  }
 }
 MeshNormals {
  158;
  0.367746;-0.197786;-0.908649;,
  0.888925;-0.172333;-0.424398;,
  -0.335784;-0.228153;-0.913890;,
  -0.867317;-0.248595;-0.431232;,
  0.373051;0.004301;0.927801;,
  0.898964;0.109893;0.424014;,
  -0.368259;-0.046703;0.928550;,
  -0.905383;-0.013429;0.424384;,
  0.362761;0.028729;-0.931439;,
  0.900702;0.052751;-0.431223;,
  -0.900151;-0.064324;-0.430802;,
  -0.364681;-0.018699;-0.930945;,
  -0.867177;-0.249055;0.431249;,
  -0.335687;-0.229964;0.913472;,
  0.366565;-0.199564;0.908738;,
  0.888391;-0.173534;0.425026;,
  0.369128;-0.050548;0.928003;,
  0.902895;0.016190;0.429557;,
  -0.896807;-0.100949;0.430751;,
  -0.357002;-0.098138;0.928934;,
  -0.906308;0.036968;-0.420998;,
  -0.376679;0.063392;-0.924172;,
  0.360461;0.113291;-0.925869;,
  0.892079;0.159035;-0.422970;,
  0.368007;0.139585;0.919286;,
  0.279090;0.765994;0.579104;,
  -0.391103;0.087355;0.916192;,
  -0.473106;0.664449;0.578513;,
  0.793994;0.569798;0.211906;,
  0.872191;0.271982;0.406582;,
  -0.912844;0.368326;0.176212;,
  -0.903288;0.149795;0.402035;,
  -0.815411;0.504494;-0.283885;,
  -0.898455;0.195212;-0.393282;,
  -0.395811;0.194165;-0.897571;,
  -0.431772;0.631003;-0.644521;,
  0.348821;0.244833;-0.904644;,
  0.243745;0.717599;-0.652411;,
  0.741869;0.639861;-0.200522;,
  0.860024;0.315578;-0.400961;,
  0.356343;-0.386983;-0.850449;,
  0.143894;-0.986147;-0.082516;,
  -0.290886;-0.408740;-0.865053;,
  0.067691;-0.994031;-0.085556;,
  0.244137;-0.967234;-0.069684;,
  0.834379;-0.365555;-0.412530;,
  -0.045236;-0.996194;-0.074503;,
  -0.797773;-0.422768;-0.429913;,
  -0.046246;-0.995981;0.076703;,
  -0.802973;-0.407043;0.435375;,
  -0.298675;-0.375116;0.877543;,
  0.066963;-0.993921;0.087389;,
  0.355844;-0.350950;0.866146;,
  0.144166;-0.985933;0.084574;,
  0.245114;-0.966898;0.070898;,
  0.838262;-0.348617;0.419265;,
  -0.882742;0.355130;-0.307652;,
  -0.983634;0.180177;0.000857;,
  -0.408986;0.362771;-0.837334;,
  0.306290;0.444063;-0.842018;,
  -0.048313;0.513281;-0.856860;,
  -0.143832;0.948765;-0.281348;,
  0.378242;0.023177;0.925416;,
  0.897340;0.143578;0.417332;,
  -0.908432;0.024053;0.417339;,
  -0.376122;-0.027058;0.926175;,
  -0.907994;0.074450;-0.412315;,
  -0.384567;0.085198;-0.919157;,
  0.363411;0.134174;-0.921916;,
  0.888944;0.192563;-0.415570;,
  0.285093;-0.797771;-0.531304;,
  -0.126096;-0.826255;-0.549001;,
  0.597394;-0.756251;-0.266842;,
  -0.477555;-0.830476;-0.286793;,
  0.949144;-0.314837;-0.001581;,
  0.602815;-0.749961;0.272346;,
  0.255405;-0.966834;-0.000008;,
  -0.057697;-0.998334;0.001032;,
  -0.482555;-0.825433;0.292918;,
  -0.925517;-0.378697;0.002540;,
  -0.132208;-0.816166;0.562489;,
  0.340271;-0.662344;0.667470;,
  0.123049;-0.992401;0.000198;,
  0.092214;-0.995739;0.000266;,
  0.362990;-0.298708;-0.882617;,
  0.866517;-0.270397;-0.419564;,
  -0.839616;-0.328679;-0.432452;,
  -0.315243;-0.321285;-0.892972;,
  -0.320782;-0.292869;0.900737;,
  -0.843558;-0.314461;0.435345;,
  0.868077;-0.257561;0.424389;,
  0.361469;-0.269724;0.892518;,
  0.367252;-0.070536;-0.927443;,
  0.901216;-0.048821;-0.430611;,
  -0.889282;-0.149277;-0.432312;,
  -0.354021;-0.111156;-0.928608;,
  0.369366;-0.011323;0.929215;,
  0.900557;0.075328;0.428162;,
  -0.902157;-0.049407;0.428569;,
  -0.362891;-0.062401;0.929740;,
  0.359370;0.088442;-0.928995;,
  0.895634;0.120838;-0.428062;,
  -0.904325;-0.003033;-0.426835;,
  -0.371011;0.038170;-0.927844;,
  -0.348499;-0.156188;0.924204;,
  -0.886076;-0.170022;0.431233;,
  0.900927;-0.069881;0.428307;,
  0.369323;-0.115855;0.922051;,
  -0.975803;-0.218650;0.000925;,
  -0.996855;-0.079245;-0.000206;,
  0.990919;-0.134456;-0.001281;,
  0.998744;0.050107;0.000095;,
  -0.999896;0.014388;0.000092;,
  0.988745;0.149609;-0.000086;,
  0.331509;0.446882;0.830902;,
  -0.434938;0.370861;0.820543;,
  0.791456;0.516238;0.327255;,
  -0.884509;0.383392;0.265808;,
  0.949930;0.312464;0.000200;,
  0.789281;0.517614;-0.330321;,
  0.869110;0.492400;0.046789;,
  -0.569483;0.819799;0.060164;,
  -0.989390;-0.145283;0.000068;,
  0.999416;-0.034169;-0.000317;,
  -0.999647;-0.026575;-0.000068;,
  0.993867;0.110582;0.000049;,
  0.849167;0.527577;0.024037;,
  -0.922948;0.384858;-0.007178;,
  -0.998409;0.056390;0.000307;,
  0.982393;0.186827;-0.000124;,
  0.702778;-0.711408;-0.000923;,
  -0.603316;-0.797498;0.002703;,
  -0.959570;-0.281466;0.001691;,
  0.975972;-0.217891;-0.001765;,
  -0.103076;0.681813;-0.724229;,
  -0.062234;0.697847;0.713538;,
  -0.073784;0.756619;0.649680;,
  -0.047776;0.235693;-0.970653;,
  -0.081961;0.801808;0.591934;,
  -0.075303;0.783817;0.616409;,
  -0.035073;0.234612;-0.971456;,
  -0.003299;0.238454;-0.971148;,
  0.015768;0.243322;-0.969817;,
  -0.117395;0.926313;0.357999;,
  0.105664;-0.983410;0.147443;,
  -0.421661;0.783671;-0.456138;,
  0.197844;0.852275;-0.484236;,
  -0.108239;0.903398;0.414917;,
  -0.676244;0.639264;-0.366108;,
  0.739405;0.660056;-0.132684;,
  0.143832;-0.948765;0.281348;,
  0.124461;-0.915550;0.382463;,
  0.253629;0.870083;0.422644;,
  -0.477037;0.765499;0.431796;,
  -0.951504;0.220139;0.214895;,
  -0.994563;-0.103969;-0.005965;,
  0.161520;-0.970878;0.176940;,
  0.857118;0.487240;0.167171;;
  146;
  4;93,1,0,92;,
  4;93,92,8,9;,
  4;95,2,3,94;,
  4;95,94,10,11;,
  4;97,5,4,96;,
  4;97,96,16,17;,
  4;99,6,7,98;,
  4;99,98,18,19;,
  4;101,9,8,100;,
  4;101,100,22,23;,
  4;103,11,10,102;,
  4;103,102,20,21;,
  4;105,12,13,104;,
  4;105,104,19,18;,
  4;107,14,15,106;,
  4;107,106,17,16;,
  4;92,0,2,95;,
  4;92,95,11,8;,
  4;107,16,19,104;,
  4;107,104,13,14;,
  4;3,108,122,94;,
  4;108,12,105,122;,
  4;122,105,18,109;,
  4;94,122,109,10;,
  4;15,110,123,106;,
  4;110,1,93,123;,
  4;123,93,9,111;,
  4;106,123,111,17;,
  4;96,4,6,99;,
  4;96,99,19,16;,
  4;10,109,124,102;,
  4;109,18,98,124;,
  4;124,98,7,112;,
  4;102,124,112,20;,
  4;100,8,11,103;,
  4;100,103,21,22;,
  4;17,111,125,97;,
  4;111,9,101,125;,
  4;125,101,23,113;,
  4;97,125,113,5;,
  4;24,114,115,26;,
  4;114,25,27,115;,
  4;25,114,116,28;,
  4;114,24,29,116;,
  4;26,115,117,31;,
  4;115,27,30,117;,
  4;28,116,126,120;,
  4;116,29,118,126;,
  4;126,118,39,119;,
  4;120,126,119,38;,
  4;31,117,127,57;,
  4;117,30,121,127;,
  4;127,121,32,56;,
  4;57,127,56,33;,
  4;33,56,58,34;,
  4;56,32,35,58;,
  4;34,58,59,36;,
  4;58,35,37,59;,
  4;36,59,119,39;,
  4;59,37,38,119;,
  4;140,141,60,134;,
  4;136,136,135,135;,
  4;63,29,24,62;,
  4;63,62,4,5;,
  4;65,26,31,64;,
  4;65,64,7,6;,
  4;67,21,20,66;,
  4;67,66,33,34;,
  4;69,23,22,68;,
  4;69,68,36,39;,
  4;6,4,62,65;,
  4;62,24,26,65;,
  4;20,112,128,66;,
  4;112,7,64,128;,
  4;128,64,31,57;,
  4;66,128,57,33;,
  4;68,22,21,67;,
  4;68,67,34,36;,
  4;5,113,129,63;,
  4;113,23,69,129;,
  4;129,69,39,118;,
  4;63,129,118,29;,
  4;137,140,134,137;,
  4;135,135,138,143;,
  4;139,139,136,136;,
  4;142,60,141,142;,
  4;40,70,71,42;,
  4;70,41,43,71;,
  4;41,70,72,44;,
  4;70,40,45,72;,
  4;42,71,73,47;,
  4;71,43,46,73;,
  4;44,72,130,76;,
  4;72,45,74,130;,
  4;130,74,55,75;,
  4;76,130,75,54;,
  4;47,73,131,79;,
  4;73,46,77,131;,
  4;131,77,48,78;,
  4;79,131,78,49;,
  4;49,78,80,50;,
  4;78,48,51,80;,
  4;50,80,81,52;,
  4;80,51,53,144;,
  4;52,81,75,55;,
  4;81,53,54,75;,
  4;43,41,82,83;,
  4;82,53,51,83;,
  4;85,45,40,84;,
  4;85,84,0,1;,
  4;87,42,47,86;,
  4;87,86,3,2;,
  4;89,49,50,88;,
  4;89,88,13,12;,
  4;91,52,55,90;,
  4;91,90,15,14;,
  4;2,0,84,87;,
  4;84,40,42,87;,
  4;3,86,132,108;,
  4;86,47,79,132;,
  4;132,79,49,89;,
  4;108,132,89,12;,
  4;91,14,13,88;,
  4;91,88,50,52;,
  4;15,90,133,110;,
  4;90,55,74,133;,
  4;133,74,45,85;,
  4;110,133,85,1;,
  4;76,54,53,82;,
  4;76,82,41,44;,
  4;46,43,83,77;,
  4;83,51,48,77;,
  3;60,134,61;,
  4;35,145,146,37;,
  4;61,134,143,121;,
  4;121,143,138,147;,
  4;32,148,145,35;,
  4;37,146,149,38;,
  3;38,149,120;,
  3;150,150,151;,
  4;25,152,153,27;,
  4;30,154,155,155;,
  4;156,156,150,150;,
  4;27,153,154,30;,
  3;120,157,28;,
  4;28,157,152,25;;
 }
}
