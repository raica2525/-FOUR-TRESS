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
 178;
 45.70740;222.36430;-41.29890;,
 63.08490;214.43401;-36.31080;,
 20.46080;121.82940;-35.04020;,
 3.08320;129.75960;-40.02840;,
 75.98090;208.69180;-22.20140;,
 33.35680;116.08720;-20.93090;,
 80.93980;206.67619;-2.75130;,
 38.31580;114.07150;-1.48080;,
 76.63260;208.92720;16.82770;,
 34.00860;116.32260;18.09820;,
 64.21390;214.84180;31.28950;,
 21.58980;122.23710;32.56010;,
 47.01100;222.83510;36.75920;,
 4.38680;130.23039;38.02970;,
 29.63350;230.76530;31.77100;,
 -12.99090;138.16060;33.04160;,
 16.73750;236.50760;17.66170;,
 -25.88690;143.90280;18.93220;,
 11.77870;238.52310;-1.78840;,
 -30.84580;145.91840;-0.51790;,
 16.08560;236.27209;-21.36740;,
 -26.53870;143.66740;-20.09690;,
 28.50450;230.35741;-35.82930;,
 -14.11990;137.75281;-34.55880;,
 45.70740;222.36430;-41.29890;,
 3.08320;129.75960;-40.02840;,
 -22.16350;29.22460;-33.76980;,
 -39.54130;37.15480;-38.75790;,
 -9.26740;23.48250;-19.66030;,
 -4.30860;21.46680;-0.21030;,
 -8.61570;23.71790;19.36870;,
 -21.03450;29.63240;33.83060;,
 -38.23760;37.62570;39.30020;,
 -55.61540;45.55590;34.31210;,
 -68.51150;51.29810;20.20270;,
 -73.47040;53.31370;0.75270;,
 -69.16340;51.06260;-18.82640;,
 -56.74460;45.14800;-33.28820;,
 -39.54130;37.15480;-38.75790;,
 48.63850;227.55170;-2.33780;,
 48.63850;227.55170;-2.33780;,
 48.63850;227.55170;-2.33780;,
 48.63850;227.55170;-2.33780;,
 48.63850;227.55170;-2.33780;,
 48.63850;227.55170;-2.33780;,
 48.63850;227.55170;-2.33780;,
 48.63850;227.55170;-2.33780;,
 48.63850;227.55170;-2.33780;,
 48.63850;227.55170;-2.33780;,
 48.63850;227.55170;-2.33780;,
 48.63850;227.55170;-2.33780;,
 -36.71080;42.12370;0.20620;,
 -36.71080;42.12370;0.20620;,
 -36.71080;42.12370;0.20620;,
 -36.71080;42.12370;0.20620;,
 -36.71080;42.12370;0.20620;,
 -36.71080;42.12370;0.20620;,
 -36.71080;42.12370;0.20620;,
 -36.71080;42.12370;0.20620;,
 -36.71080;42.12370;0.20620;,
 -36.71080;42.12370;0.20620;,
 -36.71080;42.12370;0.20620;,
 -36.71080;42.12370;0.20620;,
 54.75080;239.00870;-12.53940;,
 59.41060;236.88220;-11.20190;,
 50.66710;217.88631;-10.94120;,
 46.00740;220.01270;-12.27880;,
 62.86860;235.34241;-7.41850;,
 54.12520;216.34660;-7.15790;,
 64.19820;234.80200;-2.20310;,
 55.45480;215.80589;-1.94240;,
 63.04340;235.40559;3.04690;,
 54.29980;216.40981;3.30760;,
 59.71330;236.99139;6.92480;,
 50.96990;217.99550;7.18550;,
 55.10040;239.13490;8.39150;,
 46.35700;220.13890;8.65210;,
 50.44070;241.26140;7.05400;,
 41.69730;222.26559;7.31460;,
 46.98270;242.80110;3.27060;,
 38.23930;223.80530;3.53120;,
 45.65300;243.34160;-1.94480;,
 36.90960;224.34570;-1.68420;,
 46.80790;242.73790;-7.19490;,
 38.06450;223.74200;-6.93430;,
 50.13780;241.15190;-11.07280;,
 41.39450;222.15610;-10.81210;,
 54.75080;239.00870;-12.53940;,
 46.00740;220.01270;-12.27880;,
 54.92560;239.07159;-2.07400;,
 54.92560;239.07159;-2.07400;,
 54.92560;239.07159;-2.07400;,
 54.92560;239.07159;-2.07400;,
 54.92560;239.07159;-2.07400;,
 54.92560;239.07159;-2.07400;,
 54.92560;239.07159;-2.07400;,
 54.92560;239.07159;-2.07400;,
 54.92560;239.07159;-2.07400;,
 54.92560;239.07159;-2.07400;,
 54.92560;239.07159;-2.07400;,
 54.92560;239.07159;-2.07400;,
 46.18220;220.07581;-1.81330;,
 46.18220;220.07581;-1.81330;,
 46.18220;220.07581;-1.81330;,
 46.18220;220.07581;-1.81330;,
 46.18220;220.07581;-1.81330;,
 46.18220;220.07581;-1.81330;,
 46.18220;220.07581;-1.81330;,
 46.18220;220.07581;-1.81330;,
 46.18220;220.07581;-1.81330;,
 46.18220;220.07581;-1.81330;,
 46.18220;220.07581;-1.81330;,
 46.18220;220.07581;-1.81330;,
 72.32690;207.91389;-2.78860;,
 79.07080;212.83600;-2.93090;,
 74.66680;214.62601;-20.20460;,
 68.45280;209.48860;-17.98390;,
 79.71710;204.51080;-2.89150;,
 74.78320;206.51630;-22.24350;,
 72.97340;199.58881;-2.74920;,
 68.56940;201.37891;-20.02290;,
 72.32690;207.91389;-2.78860;,
 68.45280;209.48860;-17.98390;,
 63.21380;219.72569;-32.73520;,
 58.37790;213.97450;-29.00690;,
 61.95240;212.22960;-36.28180;,
 57.11640;206.47861;-32.55340;,
 58.37790;213.97450;-29.00690;,
 47.78070;226.76860;-37.16520;,
 44.80170;220.17020;-32.90390;,
 44.66240;220.11990;-41.24480;,
 41.68340;213.52161;-36.98350;,
 44.80170;220.17020;-32.90390;,
 32.50270;233.86760;-32.30760;,
 31.36190;226.41490;-28.63080;,
 27.54610;228.07280;-35.80270;,
 26.40540;220.62041;-32.12580;,
 31.36190;226.41490;-28.63080;,
 21.47350;239.12030;-19.46400;,
 21.65960;231.03571;-17.33240;,
 15.18990;233.95760;-21.41380;,
 15.37610;225.87320;-19.28220;,
 21.65960;231.03571;-17.33240;,
 17.64830;241.11960;-2.07570;,
 18.29480;232.79430;-2.03630;,
 10.90450;236.19740;-1.93340;,
 11.55100;227.87241;-1.89400;,
 18.29480;232.79430;-2.03630;,
 22.05230;239.32919;15.19800;,
 22.16890;231.21960;13.15910;,
 15.83840;234.19189;17.41860;,
 15.95500;226.08220;15.37970;,
 22.16890;231.21960;13.15910;,
 33.50550;234.22971;27.72860;,
 32.24390;226.73351;24.18200;,
 28.66950;228.47870;31.45690;,
 27.40810;220.98260;27.91030;,
 32.24390;226.73351;24.18200;,
 48.93850;227.18690;32.15860;,
 45.82020;220.53810;28.07910;,
 45.95950;220.58839;36.41990;,
 42.84120;213.93970;32.34040;,
 45.82020;220.53810;28.07910;,
 64.21650;220.08800;27.30100;,
 59.25990;214.29330;23.80590;,
 63.07570;212.63530;30.97790;,
 58.11910;206.84081;27.48270;,
 59.25990;214.29330;23.80590;,
 75.24560;214.83521;14.45730;,
 68.96210;209.67250;12.50760;,
 75.43190;206.75070;16.58890;,
 69.14830;201.58800;14.63910;,
 68.96210;209.67250;12.50760;,
 79.07080;212.83600;-2.93090;,
 72.32690;207.91389;-2.78860;,
 79.71710;204.51080;-2.89150;,
 72.97340;199.58881;-2.74920;,
 72.32690;207.91389;-2.78860;;
 
 132;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;3,2,26,27;,
 4;2,5,28,26;,
 4;5,7,29,28;,
 4;7,9,30,29;,
 4;9,11,31,30;,
 4;11,13,32,31;,
 4;13,15,33,32;,
 4;15,17,34,33;,
 4;17,19,35,34;,
 4;19,21,36,35;,
 4;21,23,37,36;,
 4;23,25,38,37;,
 3;39,1,0;,
 3;40,4,1;,
 3;41,6,4;,
 3;42,8,6;,
 3;43,10,8;,
 3;44,12,10;,
 3;45,14,12;,
 3;46,16,14;,
 3;47,18,16;,
 3;48,20,18;,
 3;49,22,20;,
 3;50,24,22;,
 3;51,27,26;,
 3;52,26,28;,
 3;53,28,29;,
 3;54,29,30;,
 3;55,30,31;,
 3;56,31,32;,
 3;57,32,33;,
 3;58,33,34;,
 3;59,34,35;,
 3;60,35,36;,
 3;61,36,37;,
 3;62,37,38;,
 4;63,64,65,66;,
 4;64,67,68,65;,
 4;67,69,70,68;,
 4;69,71,72,70;,
 4;71,73,74,72;,
 4;73,75,76,74;,
 4;75,77,78,76;,
 4;77,79,80,78;,
 4;79,81,82,80;,
 4;81,83,84,82;,
 4;83,85,86,84;,
 4;85,87,88,86;,
 3;89,64,63;,
 3;90,67,64;,
 3;91,69,67;,
 3;92,71,69;,
 3;93,73,71;,
 3;94,75,73;,
 3;95,77,75;,
 3;96,79,77;,
 3;97,81,79;,
 3;98,83,81;,
 3;99,85,83;,
 3;100,87,85;,
 3;101,66,65;,
 3;102,65,68;,
 3;103,68,70;,
 3;104,70,72;,
 3;105,72,74;,
 3;106,74,76;,
 3;107,76,78;,
 3;108,78,80;,
 3;109,80,82;,
 3;110,82,84;,
 3;111,84,86;,
 3;112,86,88;,
 4;113,114,115,116;,
 4;114,117,118,115;,
 4;117,119,120,118;,
 4;119,121,122,120;,
 4;116,115,123,124;,
 4;115,118,125,123;,
 4;118,120,126,125;,
 4;120,122,127,126;,
 4;124,123,128,129;,
 4;123,125,130,128;,
 4;125,126,131,130;,
 4;126,127,132,131;,
 4;129,128,133,134;,
 4;128,130,135,133;,
 4;130,131,136,135;,
 4;131,132,137,136;,
 4;134,133,138,139;,
 4;133,135,140,138;,
 4;135,136,141,140;,
 4;136,137,142,141;,
 4;139,138,143,144;,
 4;138,140,145,143;,
 4;140,141,146,145;,
 4;141,142,147,146;,
 4;144,143,148,149;,
 4;143,145,150,148;,
 4;145,146,151,150;,
 4;146,147,152,151;,
 4;149,148,153,154;,
 4;148,150,155,153;,
 4;150,151,156,155;,
 4;151,152,157,156;,
 4;154,153,158,159;,
 4;153,155,160,158;,
 4;155,156,161,160;,
 4;156,157,162,161;,
 4;159,158,163,164;,
 4;158,160,165,163;,
 4;160,161,166,165;,
 4;161,162,167,166;,
 4;164,163,168,169;,
 4;163,165,170,168;,
 4;165,166,171,170;,
 4;166,167,172,171;,
 4;169,168,173,174;,
 4;168,170,175,173;,
 4;170,171,176,175;,
 4;171,172,177,176;;
 
 MeshMaterialList {
  2;
  132;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\battery\\color_bt_001.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\battery\\color_bt_002.jpg";
   }
  }
 }
 MeshNormals {
  172;
  0.418087;0.908322;-0.012462;,
  -0.016698;-0.006032;-0.999842;,
  0.447107;-0.217698;-0.867585;,
  0.782554;-0.367093;-0.502844;,
  0.908256;-0.418225;-0.012644;,
  0.798983;-0.361158;0.480824;,
  0.475873;-0.207308;0.854733;,
  0.016699;0.006032;0.999842;,
  -0.447106;0.217699;0.867585;,
  -0.782554;0.367096;0.502842;,
  -0.908254;0.418228;0.012646;,
  -0.798983;0.361162;-0.480821;,
  -0.475871;0.207309;-0.854734;,
  -0.016698;-0.006032;-0.999842;,
  0.447106;-0.217698;-0.867585;,
  0.782554;-0.367094;-0.502844;,
  0.908255;-0.418226;-0.012644;,
  0.798982;-0.361160;0.480823;,
  0.475873;-0.207308;0.854733;,
  0.016699;0.006032;0.999842;,
  -0.447105;0.217698;0.867585;,
  -0.782554;0.367096;0.502842;,
  -0.908254;0.418229;0.012646;,
  -0.798982;0.361162;-0.480821;,
  -0.475871;0.207309;-0.854734;,
  -0.016698;-0.006031;-0.999842;,
  0.447106;-0.217698;-0.867585;,
  0.782554;-0.367094;-0.502843;,
  0.908254;-0.418227;-0.012644;,
  0.798982;-0.361161;0.480823;,
  0.475872;-0.207309;0.854733;,
  0.016699;0.006031;0.999842;,
  -0.447104;0.217698;0.867586;,
  -0.782553;0.367096;0.502843;,
  -0.908253;0.418229;0.012646;,
  -0.798982;0.361163;-0.480822;,
  -0.475870;0.207309;-0.854734;,
  -0.418081;-0.908324;0.012463;,
  0.418085;0.908323;-0.012463;,
  -0.016698;-0.006034;-0.999842;,
  0.447103;-0.217698;-0.867587;,
  0.782556;-0.367094;-0.502841;,
  0.908256;-0.418225;-0.012636;,
  0.798986;-0.361161;0.480817;,
  0.475879;-0.207310;0.854729;,
  0.016702;0.006030;0.999842;,
  -0.447106;0.217696;0.867586;,
  -0.782557;0.367094;0.502839;,
  -0.908256;0.418224;0.012645;,
  -0.798986;0.361158;-0.480818;,
  -0.475876;0.207306;-0.854732;,
  -0.418089;-0.908320;0.012463;,
  -0.908257;0.418222;0.012646;,
  -0.589465;0.807779;0.004970;,
  0.908254;-0.418228;-0.012647;,
  0.589467;-0.807777;-0.004972;,
  -0.782705;0.367156;0.502563;,
  -0.477868;0.764789;0.432134;,
  0.782702;-0.367163;-0.502563;,
  0.477866;-0.764788;-0.432138;,
  -0.447382;0.217817;0.867413;,
  -0.182346;0.638213;0.747954;,
  0.447378;-0.217822;-0.867413;,
  0.182339;-0.638219;-0.747949;,
  0.016696;0.006027;0.999842;,
  0.222081;0.456226;0.861707;,
  -0.016701;-0.006035;-0.999842;,
  -0.222085;-0.456239;-0.861698;,
  0.476135;-0.207436;0.854556;,
  0.620537;0.268506;0.736775;,
  -0.476141;0.207423;-0.854556;,
  -0.620540;-0.268521;-0.736768;,
  0.799120;-0.361231;0.480541;,
  0.901489;0.129631;0.412933;,
  -0.799125;0.361217;-0.480542;,
  -0.901488;-0.129644;-0.412931;,
  0.908254;-0.418228;-0.012646;,
  0.996859;0.077326;-0.017114;,
  -0.908258;0.418219;0.012646;,
  -0.996859;-0.077330;0.017114;,
  0.782701;-0.367158;-0.502567;,
  0.887170;0.124466;-0.444339;,
  -0.782703;0.367155;0.502567;,
  -0.887170;-0.124471;0.444338;,
  0.447376;-0.217823;-0.867414;,
  0.595534;0.259476;-0.760271;,
  -0.447378;0.217818;0.867414;,
  -0.595536;-0.259484;0.760266;,
  -0.016701;-0.006036;-0.999842;,
  0.193089;0.445754;-0.874083;,
  0.016696;0.006029;0.999842;,
  -0.193095;-0.445762;0.874077;,
  -0.476141;0.207428;-0.854555;,
  -0.207353;0.629177;-0.749094;,
  0.476137;-0.207434;0.854555;,
  0.207343;-0.629188;0.749087;,
  -0.799125;0.361222;-0.480539;,
  -0.492192;0.759610;-0.425135;,
  0.799124;-0.361226;0.480538;,
  0.492185;-0.759617;0.425132;,
  0.476409;0.869107;-0.132996;,
  0.411757;0.898757;-0.150640;,
  0.524265;0.847499;-0.083020;,
  0.542605;0.839869;-0.014126;,
  0.526576;0.848332;0.055242;,
  0.480410;0.870551;0.106522;,
  0.416379;0.900424;0.125958;,
  0.351628;0.929852;0.108316;,
  0.303566;0.951023;0.058341;,
  0.285123;0.958433;-0.010546;,
  0.301256;0.950189;-0.079914;,
  0.347623;0.928409;-0.131203;,
  -0.412192;-0.899540;0.144657;,
  -0.474044;-0.871180;0.127778;,
  -0.519834;-0.850516;0.079965;,
  -0.537385;-0.843220;0.014059;,
  -0.522045;-0.851313;-0.052300;,
  -0.477873;-0.872562;-0.101359;,
  -0.416616;-0.901134;-0.119952;,
  -0.354673;-0.929292;-0.103074;,
  -0.308697;-0.949553;-0.055269;,
  -0.291055;-0.956647;0.010634;,
  -0.306488;-0.948755;0.077000;,
  -0.350842;-0.927910;0.126064;,
  0.418082;0.908324;-0.012443;,
  0.418071;0.908329;-0.012442;,
  0.418074;0.908327;-0.012454;,
  0.418069;0.908330;-0.012467;,
  0.418063;0.908333;-0.012459;,
  0.418081;0.908324;-0.012463;,
  0.418102;0.908314;-0.012478;,
  0.418096;0.908317;-0.012480;,
  0.418098;0.908316;-0.012473;,
  0.418102;0.908314;-0.012469;,
  0.418101;0.908315;-0.012471;,
  0.418079;0.908325;-0.012455;,
  -0.418085;-0.908322;0.012461;,
  -0.418074;-0.908328;0.012463;,
  -0.418082;-0.908324;0.012442;,
  -0.418095;-0.908318;0.012461;,
  -0.418078;-0.908326;0.012471;,
  -0.418077;-0.908326;0.012449;,
  -0.418110;-0.908311;0.012460;,
  -0.418110;-0.908311;0.012470;,
  -0.418093;-0.908319;0.012480;,
  -0.418094;-0.908318;0.012477;,
  -0.418088;-0.908321;0.012465;,
  -0.418088;-0.908321;0.012458;,
  0.996860;0.077314;-0.017117;,
  0.887173;0.124453;-0.444337;,
  -0.996859;-0.077329;0.017116;,
  -0.887171;-0.124469;0.444336;,
  0.595539;0.259481;-0.760265;,
  -0.595541;-0.259482;0.760263;,
  0.193092;0.445762;-0.874078;,
  -0.193096;-0.445764;0.874076;,
  -0.207351;0.629179;-0.749093;,
  0.207344;-0.629186;0.749088;,
  -0.492191;0.759609;-0.425138;,
  0.492179;-0.759620;0.425132;,
  -0.589469;0.807776;0.004972;,
  0.589457;-0.807784;-0.004973;,
  -0.477865;0.764788;0.432139;,
  0.477863;-0.764790;-0.432137;,
  -0.182343;0.638216;0.747951;,
  0.182344;-0.638217;-0.747950;,
  0.222080;0.456229;0.861705;,
  -0.222083;-0.456232;-0.861703;,
  0.620540;0.268513;0.736770;,
  -0.620541;-0.268508;-0.736771;,
  0.901490;0.129636;0.412928;,
  -0.901489;-0.129635;-0.412930;;
  132;
  4;1,2,14,13;,
  4;2,3,15,14;,
  4;3,4,16,15;,
  4;4,5,17,16;,
  4;5,6,18,17;,
  4;6,7,19,18;,
  4;7,8,20,19;,
  4;8,9,21,20;,
  4;9,10,22,21;,
  4;10,11,23,22;,
  4;11,12,24,23;,
  4;12,1,13,24;,
  4;13,14,26,25;,
  4;14,15,27,26;,
  4;15,16,28,27;,
  4;16,17,29,28;,
  4;17,18,30,29;,
  4;18,19,31,30;,
  4;19,20,32,31;,
  4;20,21,33,32;,
  4;21,22,34,33;,
  4;22,23,35,34;,
  4;23,24,36,35;,
  4;24,13,25,36;,
  3;0,100,101;,
  3;0,102,100;,
  3;0,103,102;,
  3;0,104,103;,
  3;0,105,104;,
  3;0,106,105;,
  3;0,107,106;,
  3;0,108,107;,
  3;0,109,108;,
  3;0,110,109;,
  3;0,111,110;,
  3;0,101,111;,
  3;37,112,113;,
  3;37,113,114;,
  3;37,114,115;,
  3;37,115,116;,
  3;37,116,117;,
  3;37,117,118;,
  3;37,118,119;,
  3;37,119,120;,
  3;37,120,121;,
  3;37,121,122;,
  3;37,122,123;,
  3;37,123,112;,
  4;39,40,40,39;,
  4;40,41,41,40;,
  4;41,42,42,41;,
  4;42,43,43,42;,
  4;43,44,44,43;,
  4;44,45,45,44;,
  4;45,46,46,45;,
  4;46,47,47,46;,
  4;47,48,48,47;,
  4;48,49,49,48;,
  4;49,50,50,49;,
  4;50,39,39,50;,
  3;38,124,125;,
  3;38,126,124;,
  3;38,127,126;,
  3;38,128,127;,
  3;38,129,128;,
  3;38,130,129;,
  3;38,131,130;,
  3;38,132,131;,
  3;38,133,132;,
  3;38,134,133;,
  3;38,135,134;,
  3;38,125,135;,
  3;51,136,137;,
  3;51,137,138;,
  3;51,138,139;,
  3;51,139,140;,
  3;51,140,141;,
  3;51,141,142;,
  3;51,142,143;,
  3;51,143,144;,
  3;51,144,145;,
  3;51,145,146;,
  3;51,146,147;,
  3;51,147,136;,
  4;52,53,57,56;,
  4;148,54,58,149;,
  4;54,55,59,58;,
  4;150,52,56,151;,
  4;56,57,61,60;,
  4;149,58,62,152;,
  4;58,59,63,62;,
  4;151,56,60,153;,
  4;60,61,65,64;,
  4;152,62,66,154;,
  4;62,63,67,66;,
  4;153,60,64,155;,
  4;64,65,69,68;,
  4;154,66,70,156;,
  4;66,67,71,70;,
  4;155,64,68,157;,
  4;68,69,73,72;,
  4;156,70,74,158;,
  4;70,71,75,74;,
  4;157,68,72,159;,
  4;72,73,77,76;,
  4;158,74,78,160;,
  4;74,75,79,78;,
  4;159,72,76,161;,
  4;76,77,81,80;,
  4;160,78,82,162;,
  4;78,79,83,82;,
  4;161,76,80,163;,
  4;80,81,85,84;,
  4;162,82,86,164;,
  4;82,83,87,86;,
  4;163,80,84,165;,
  4;84,85,89,88;,
  4;164,86,90,166;,
  4;86,87,91,90;,
  4;165,84,88,167;,
  4;88,89,93,92;,
  4;166,90,94,168;,
  4;90,91,95,94;,
  4;167,88,92,169;,
  4;92,93,97,96;,
  4;168,94,98,170;,
  4;94,95,99,98;,
  4;169,92,96,171;,
  4;96,97,53,52;,
  4;170,98,54,148;,
  4;98,99,55,54;,
  4;171,96,52,150;;
 }
 MeshTextureCoords {
  178;
  0.000000;0.000000;,
  0.083330;0.000000;,
  0.083330;0.500000;,
  0.000000;0.500000;,
  0.166670;0.000000;,
  0.166670;0.500000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.333330;0.000000;,
  0.333330;0.500000;,
  0.416670;0.000000;,
  0.416670;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.583330;0.000000;,
  0.583330;0.500000;,
  0.666670;0.000000;,
  0.666670;0.500000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  0.833330;0.000000;,
  0.833330;0.500000;,
  0.916670;0.000000;,
  0.916670;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.083330;1.000000;,
  0.000000;1.000000;,
  0.166670;1.000000;,
  0.250000;1.000000;,
  0.333330;1.000000;,
  0.416670;1.000000;,
  0.500000;1.000000;,
  0.583330;1.000000;,
  0.666670;1.000000;,
  0.750000;1.000000;,
  0.833330;1.000000;,
  0.916670;1.000000;,
  1.000000;1.000000;,
  0.041670;0.000000;,
  0.125000;0.000000;,
  0.208330;0.000000;,
  0.291670;0.000000;,
  0.375000;0.000000;,
  0.458330;0.000000;,
  0.541670;0.000000;,
  0.625000;0.000000;,
  0.708330;0.000000;,
  0.791670;0.000000;,
  0.875000;0.000000;,
  0.958330;0.000000;,
  0.041670;1.000000;,
  0.125000;1.000000;,
  0.208330;1.000000;,
  0.291670;1.000000;,
  0.375000;1.000000;,
  0.458330;1.000000;,
  0.541670;1.000000;,
  0.625000;1.000000;,
  0.708330;1.000000;,
  0.791670;1.000000;,
  0.875000;1.000000;,
  0.958330;1.000000;,
  0.000000;0.000000;,
  0.083330;0.000000;,
  0.083330;1.000000;,
  0.000000;1.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.416670;0.000000;,
  0.416670;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.583330;0.000000;,
  0.583330;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  0.916670;0.000000;,
  0.916670;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.041670;0.000000;,
  0.125000;0.000000;,
  0.208330;0.000000;,
  0.291670;0.000000;,
  0.375000;0.000000;,
  0.458330;0.000000;,
  0.541670;0.000000;,
  0.625000;0.000000;,
  0.708330;0.000000;,
  0.791670;0.000000;,
  0.875000;0.000000;,
  0.958330;0.000000;,
  0.041670;1.000000;,
  0.125000;1.000000;,
  0.208330;1.000000;,
  0.291670;1.000000;,
  0.375000;1.000000;,
  0.458330;1.000000;,
  0.541670;1.000000;,
  0.625000;1.000000;,
  0.708330;1.000000;,
  0.791670;1.000000;,
  0.875000;1.000000;,
  0.958330;1.000000;,
  0.000000;0.000000;,
  0.000000;0.250000;,
  0.083330;0.250000;,
  0.083330;0.000000;,
  0.000000;0.500000;,
  0.083330;0.500000;,
  0.000000;0.750000;,
  0.083330;0.750000;,
  0.000000;1.000000;,
  0.083330;1.000000;,
  0.166670;0.250000;,
  0.166670;0.000000;,
  0.166670;0.500000;,
  0.166670;0.750000;,
  0.166670;1.000000;,
  0.250000;0.250000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.250000;0.750000;,
  0.250000;1.000000;,
  0.333330;0.250000;,
  0.333330;0.000000;,
  0.333330;0.500000;,
  0.333330;0.750000;,
  0.333330;1.000000;,
  0.416670;0.250000;,
  0.416670;0.000000;,
  0.416670;0.500000;,
  0.416670;0.750000;,
  0.416670;1.000000;,
  0.500000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.500000;0.750000;,
  0.500000;1.000000;,
  0.583330;0.250000;,
  0.583330;0.000000;,
  0.583330;0.500000;,
  0.583330;0.750000;,
  0.583330;1.000000;,
  0.666670;0.250000;,
  0.666670;0.000000;,
  0.666670;0.500000;,
  0.666670;0.750000;,
  0.666670;1.000000;,
  0.750000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  0.750000;0.750000;,
  0.750000;1.000000;,
  0.833330;0.250000;,
  0.833330;0.000000;,
  0.833330;0.500000;,
  0.833330;0.750000;,
  0.833330;1.000000;,
  0.916670;0.250000;,
  0.916670;0.000000;,
  0.916670;0.500000;,
  0.916670;0.750000;,
  0.916670;1.000000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  1.000000;0.750000;,
  1.000000;1.000000;;
 }
}