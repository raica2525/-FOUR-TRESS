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
 111;
 -8.56050;0.16470;6.21310;,
 -3.27220;0.16470;10.05520;,
 -3.11220;3.07040;9.56310;,
 -8.14150;3.07040;5.90900;,
 3.26440;0.16470;10.05520;,
 3.10440;3.07040;9.56310;,
 8.55270;0.16470;6.21310;,
 8.13380;3.07040;5.90900;,
 10.57240;0.16470;-0.00340;,
 10.05480;3.07040;-0.00340;,
 7.51300;0.16470;-6.22020;,
 7.14500;3.07040;-5.91580;,
 3.26440;0.16470;-10.06230;,
 3.10440;3.07040;-9.56990;,
 -3.27220;0.16470;-10.06230;,
 -3.11220;3.07040;-9.56990;,
 -7.52070;0.16470;-6.22020;,
 -7.15300;3.07040;-5.91580;,
 -10.58020;0.16470;-0.00340;,
 -10.06260;3.07040;-0.00340;,
 -2.64800;5.69210;8.13420;,
 -6.92610;5.69210;5.02610;,
 2.64040;5.69210;8.13420;,
 6.91840;5.69210;5.02600;,
 8.55270;5.69210;-0.00340;,
 6.07740;5.69210;-5.03290;,
 2.64040;5.69210;-8.14130;,
 -2.64800;5.69210;-8.14130;,
 -6.08510;5.69210;-5.03290;,
 -8.56050;5.69210;-0.00340;,
 -1.92470;7.77240;5.90900;,
 -5.03310;7.77240;3.65060;,
 1.91700;7.77240;5.90900;,
 5.02540;7.77240;3.65060;,
 6.21270;7.77240;-0.00340;,
 4.41440;7.77240;-3.65770;,
 1.91700;7.77240;-5.91580;,
 -1.92470;7.77240;-5.91580;,
 -4.42210;7.77240;-3.65770;,
 -6.22050;7.77240;-0.00340;,
 -1.01400;9.10820;3.10500;,
 -2.64800;9.10820;1.91760;,
 1.00600;9.10820;3.10500;,
 2.64040;9.10820;1.91760;,
 3.26440;9.10820;-0.00340;,
 2.31880;9.10820;-1.92480;,
 1.00600;9.10820;-3.11180;,
 -1.01400;9.10820;-3.11180;,
 -2.32660;9.10820;-1.92470;,
 -3.27220;9.10820;-0.00340;,
 -0.00400;9.56840;-0.00340;,
 -3.27220;-17.50420;10.05520;,
 -8.56050;-17.50420;6.21310;,
 -8.56050;-19.37570;6.21310;,
 -3.27220;-19.37570;10.05520;,
 3.26440;-17.50420;10.05520;,
 3.26440;-19.37570;10.05520;,
 8.55270;-17.50420;6.21310;,
 8.55270;-19.37570;6.21310;,
 10.57240;-17.50420;-0.00340;,
 10.57240;-19.37570;-0.00340;,
 -10.58020;-17.50420;-0.00340;,
 -10.58020;-19.37570;-0.00340;,
 -0.00400;-19.37570;-0.00340;,
 10.57240;-2.92110;-2.76060;,
 7.51300;-4.06140;-12.24490;,
 3.26440;-5.63880;-18.33580;,
 -3.27220;-5.63880;-18.33580;,
 -7.52070;-4.17940;-12.41300;,
 -10.58020;-2.92110;-2.76060;,
 5.69450;-13.56180;-39.24550;,
 8.55270;-14.71380;-33.02900;,
 8.40830;-17.50420;-36.95700;,
 5.08490;-17.47230;-43.14140;,
 2.20870;-13.56180;-43.08790;,
 2.20870;-17.45240;-46.96380;,
 -2.21640;-13.56180;-43.08790;,
 -2.21640;-17.45240;-46.96380;,
 -5.70230;-13.56180;-39.24550;,
 -5.09280;-17.47230;-43.14140;,
 -8.56050;-14.71380;-33.02900;,
 -8.41610;-17.50420;-36.95700;,
 8.40830;-19.37570;-38.82140;,
 5.08490;-19.37570;-45.03820;,
 2.20870;-19.37570;-48.88020;,
 -2.21640;-19.37570;-48.88020;,
 -5.09280;-19.37570;-45.03820;,
 -8.41610;-19.37570;-38.82130;,
 -0.00400;-19.37570;-38.82130;,
 10.57240;-17.50420;-2.76060;,
 -0.00400;-17.50420;-0.00340;,
 -0.00400;-17.50420;-2.76060;,
 -10.58020;-17.50420;-2.76060;,
 -0.00400;-17.50420;-36.95700;,
 7.68930;-10.38610;-21.15230;,
 7.69980;-17.50420;-21.61490;,
 5.35590;-9.14800;-24.92790;,
 2.32300;-9.26960;-27.60840;,
 -2.33070;-9.28470;-27.64340;,
 -5.36730;-9.20870;-25.13240;,
 -7.69860;-10.36500;-21.12050;,
 -7.70840;-17.50420;-21.61490;,
 7.69980;-19.37570;-21.61490;,
 -0.00430;-19.37570;-21.61640;,
 -0.00400;-19.37570;-36.95700;,
 8.40830;-19.37570;-36.95700;,
 -7.70840;-19.37570;-21.61490;,
 -8.41610;-19.37570;-36.95700;,
 10.57240;-19.37570;-2.76060;,
 -0.00400;-19.37570;-2.76060;,
 -10.58020;-19.37570;-2.76060;;
 
 119;
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
 3;41,40,50;,
 3;40,42,50;,
 3;42,43,50;,
 3;43,44,50;,
 3;44,45,50;,
 3;45,46,50;,
 3;46,47,50;,
 3;47,48,50;,
 3;48,49,50;,
 3;49,41,50;,
 4;51,52,53,54;,
 4;55,51,54,56;,
 4;57,55,56,58;,
 4;59,57,58,60;,
 4;52,61,62,53;,
 3;54,53,63;,
 3;56,54,63;,
 3;58,56,63;,
 3;60,58,63;,
 3;53,62,63;,
 4;10,8,64,65;,
 4;12,10,65,66;,
 4;14,12,66,67;,
 4;16,14,67,68;,
 4;18,16,68,69;,
 4;70,71,72,73;,
 4;74,70,73,75;,
 4;76,74,75,77;,
 4;78,76,77,79;,
 4;80,78,79,81;,
 4;55,57,6,4;,
 4;51,55,4,1;,
 4;52,51,1,0;,
 4;73,72,82,83;,
 4;75,73,83,84;,
 4;77,75,84,85;,
 4;79,77,85,86;,
 4;81,79,86,87;,
 3;83,82,88;,
 3;84,83,88;,
 3;85,84,88;,
 3;86,85,88;,
 3;87,86,88;,
 4;89,59,90,91;,
 4;91,90,61,92;,
 4;60,63,90,59;,
 4;63,62,61,90;,
 4;87,88,93,81;,
 4;88,82,72,93;,
 4;94,95,72,71;,
 4;96,94,71,70;,
 4;97,96,70,74;,
 4;98,97,74,76;,
 4;99,98,76,78;,
 4;100,99,78,80;,
 4;101,100,80,81;,
 4;102,103,104,105;,
 4;103,106,107,104;,
 4;64,94,96,65;,
 4;65,96,97,66;,
 4;66,97,98,67;,
 4;67,98,99,68;,
 4;68,99,100,69;,
 4;94,64,89,95;,
 4;69,100,101,92;,
 4;102,108,109,103;,
 4;103,109,110,106;,
 4;106,101,81,107;,
 4;102,105,72,95;,
 4;93,72,105,104;,
 4;95,89,108,102;,
 4;89,91,109,108;,
 4;91,92,110,109;,
 4;92,101,106,110;,
 4;81,93,104,107;,
 4;64,8,59,89;,
 4;8,6,57,59;,
 4;0,18,61,52;,
 4;18,69,92,61;;
 
 MeshMaterialList {
  5;
  119;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
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
  110;
  -0.805875;0.088099;0.585495;,
  -0.307814;0.088075;0.947361;,
  0.307813;0.088072;0.947362;,
  0.805876;0.088092;0.585495;,
  0.986569;0.158220;-0.040599;,
  0.749236;0.384652;-0.539156;,
  0.316107;0.527205;-0.788753;,
  -0.316113;0.527195;-0.788757;,
  -0.749242;0.384632;-0.539161;,
  -0.986570;0.158216;-0.040599;,
  -0.760182;0.342168;0.552308;,
  -0.290366;0.342163;0.893651;,
  0.290367;0.342159;0.893652;,
  0.760188;0.342161;0.552305;,
  0.937270;0.341803;-0.068527;,
  0.756669;0.318826;-0.570791;,
  0.338534;0.342042;-0.876585;,
  -0.338527;0.342045;-0.876587;,
  -0.756667;0.318827;-0.570793;,
  -0.937270;0.341806;-0.068518;,
  -0.627297;0.631482;0.455773;,
  -0.239605;0.631486;0.737438;,
  0.239609;0.631485;0.737437;,
  0.627304;0.631481;0.455766;,
  0.773619;0.630926;-0.058705;,
  0.638169;0.601124;-0.481030;,
  0.280757;0.631261;-0.722970;,
  -0.280750;0.631265;-0.722969;,
  -0.638157;0.601136;-0.481032;,
  -0.773612;0.630935;-0.058699;,
  -0.439984;0.839180;0.319675;,
  -0.168064;0.839176;0.517241;,
  0.168059;0.839177;0.517241;,
  0.439984;0.839182;0.319667;,
  0.542819;0.838748;-0.042996;,
  0.458847;0.818570;-0.345548;,
  0.198085;0.839005;-0.506787;,
  -0.198096;0.839000;-0.506792;,
  -0.458856;0.818561;-0.345557;,
  -0.542816;0.838751;-0.042993;,
  -0.225206;0.960475;0.163616;,
  -0.086027;0.960477;0.264731;,
  0.086015;0.960478;0.264733;,
  0.225195;0.960479;0.163609;,
  0.277940;0.960329;-0.022745;,
  0.239254;0.954117;-0.180048;,
  0.101858;0.960413;-0.259292;,
  -0.101872;0.960412;-0.259290;,
  -0.239270;0.954113;-0.180051;,
  -0.277942;0.960329;-0.022740;,
  -0.000005;0.999994;-0.003604;,
  -0.809021;0.000000;0.587779;,
  -0.309013;0.000000;0.951058;,
  0.309013;0.000000;0.951058;,
  0.809021;0.000000;0.587779;,
  0.951064;0.000000;0.308994;,
  -0.951064;0.000000;0.308994;,
  0.000000;-1.000000;-0.000000;,
  0.915113;0.356550;-0.188258;,
  0.653944;0.658146;-0.373096;,
  0.247874;0.837922;-0.486257;,
  -0.247869;0.837941;-0.486227;,
  -0.653603;0.658376;-0.373288;,
  -0.915026;0.356636;-0.188515;,
  0.946411;0.235574;-0.220932;,
  0.624089;0.659909;-0.418370;,
  0.186853;0.862279;-0.470702;,
  -0.186228;0.862712;-0.470158;,
  -0.624492;0.660090;-0.417481;,
  -0.946751;0.234841;-0.220255;,
  0.798203;0.425178;-0.426727;,
  0.745340;0.470573;-0.472261;,
  0.369891;0.655782;-0.658126;,
  -0.369875;0.655787;-0.658131;,
  -0.745336;0.470572;-0.472266;,
  -0.798217;0.425158;-0.426719;,
  0.978071;0.000000;0.208274;,
  0.809021;0.000000;0.587779;,
  -0.809021;0.000000;0.587779;,
  -0.978071;0.000000;0.208274;,
  0.963453;0.192242;-0.186553;,
  -0.963455;0.192194;-0.186591;,
  0.756046;0.452734;-0.472681;,
  0.363913;0.650567;-0.666581;,
  -0.363898;0.650573;-0.666583;,
  -0.756040;0.452740;-0.472685;,
  0.000001;-0.976439;0.215791;,
  0.000002;-0.705747;0.708464;,
  0.939002;0.300947;-0.166449;,
  0.533144;0.786611;-0.311449;,
  0.130194;0.936597;-0.325325;,
  -0.129563;0.936892;-0.324725;,
  -0.533056;0.786998;-0.310621;,
  -0.939318;0.300231;-0.165964;,
  0.998676;-0.013592;-0.049621;,
  -0.998674;-0.013566;-0.049669;,
  0.000002;-0.923513;0.383567;,
  0.000000;-0.923510;0.383574;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.705743;0.708468;,
  0.000004;-0.705752;0.708459;,
  0.994846;0.001879;-0.101382;,
  -0.994845;0.001969;-0.101392;,
  -0.998621;0.000000;-0.052505;,
  -0.998938;0.000000;0.046079;,
  0.998621;0.000000;-0.052500;,
  0.998935;0.000000;0.046131;,
  0.988592;0.000000;-0.150620;,
  0.000000;0.000000;1.000000;,
  -0.988598;0.000000;-0.150579;;
  119;
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
  3;40,41,50;,
  3;41,42,50;,
  3;42,43,50;,
  3;43,44,50;,
  3;44,45,50;,
  3;45,46,50;,
  3;46,47,50;,
  3;47,48,50;,
  3;48,49,50;,
  3;49,40,50;,
  4;52,78,51,52;,
  4;53,52,52,53;,
  4;77,53,53,54;,
  4;76,77,54,55;,
  4;78,79,56,51;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  4;5,4,64,65;,
  4;6,5,65,66;,
  4;7,6,66,67;,
  4;8,7,67,68;,
  4;9,8,68,69;,
  4;59,58,80,82;,
  4;60,59,82,83;,
  4;61,60,83,84;,
  4;62,61,84,85;,
  4;63,62,85,81;,
  4;53,77,3,2;,
  4;52,53,2,1;,
  4;78,52,1,0;,
  4;82,80,70,71;,
  4;83,82,71,72;,
  4;84,83,72,73;,
  4;85,84,73,74;,
  4;81,85,74,75;,
  3;57,96,86;,
  3;57,57,86;,
  3;57,57,86;,
  3;57,57,86;,
  3;97,57,86;,
  4;57,57,57,57;,
  4;57,57,57,57;,
  4;98,98,98,98;,
  4;98,98,98,98;,
  4;97,86,87,99;,
  4;86,96,100,87;,
  4;88,94,80,58;,
  4;89,88,58,59;,
  4;90,89,59,60;,
  4;91,90,60,61;,
  4;92,91,61,62;,
  4;93,92,62,63;,
  4;95,93,63,81;,
  4;57,57,57,57;,
  4;57,57,57,57;,
  4;64,88,89,65;,
  4;65,89,90,66;,
  4;66,90,91,67;,
  4;67,91,92,68;,
  4;68,92,93,69;,
  4;88,64,101,94;,
  4;69,93,95,102;,
  4;57,57,57,57;,
  4;57,57,57,57;,
  4;103,95,81,104;,
  4;105,106,80,94;,
  4;98,98,98,98;,
  4;94,101,107,105;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;102,95,103,109;,
  4;98,98,98,98;,
  4;64,4,76,101;,
  4;4,3,77,76;,
  4;0,9,79,78;,
  4;9,69,102,79;;
 }
 MeshTextureCoords {
  111;
  0.457200;0.499180;,
  0.483640;0.499180;,
  0.484440;0.484650;,
  0.459290;0.484650;,
  0.516320;0.499180;,
  0.515520;0.484650;,
  0.542760;0.499180;,
  0.540670;0.484650;,
  0.552860;0.499180;,
  0.550270;0.484650;,
  0.537560;0.499180;,
  0.535720;0.484650;,
  0.516320;0.499180;,
  0.515520;0.484650;,
  0.483640;0.499180;,
  0.484440;0.484650;,
  0.462400;0.499180;,
  0.464240;0.484650;,
  0.447100;0.499180;,
  0.449690;0.484650;,
  0.486760;0.471540;,
  0.465370;0.471540;,
  0.513200;0.471540;,
  0.534590;0.471540;,
  0.542760;0.471540;,
  0.530390;0.471540;,
  0.513200;0.471540;,
  0.486760;0.471540;,
  0.469570;0.471540;,
  0.457200;0.471540;,
  0.490380;0.461140;,
  0.474830;0.461140;,
  0.509590;0.461140;,
  0.525130;0.461140;,
  0.531060;0.461140;,
  0.522070;0.461140;,
  0.509590;0.461140;,
  0.490380;0.461140;,
  0.477890;0.461140;,
  0.468900;0.461140;,
  0.494930;0.454460;,
  0.486760;0.454460;,
  0.505030;0.454460;,
  0.513200;0.454460;,
  0.516320;0.454460;,
  0.511590;0.454460;,
  0.505030;0.454460;,
  0.494930;0.454460;,
  0.488370;0.454460;,
  0.483640;0.454460;,
  0.499980;0.452160;,
  0.483640;0.587520;,
  0.457200;0.587520;,
  0.457200;0.596880;,
  0.483640;0.596880;,
  0.516320;0.587520;,
  0.516320;0.596880;,
  0.542760;0.587520;,
  0.542760;0.596880;,
  0.552860;0.587520;,
  0.552860;0.596880;,
  0.447100;0.587520;,
  0.447100;0.596880;,
  0.499980;0.596880;,
  0.552860;0.514610;,
  0.537560;0.520310;,
  0.516320;0.528190;,
  0.483640;0.528190;,
  0.462400;0.520900;,
  0.447100;0.514610;,
  0.528470;0.567810;,
  0.542760;0.573570;,
  0.542040;0.587520;,
  0.525420;0.587360;,
  0.511040;0.567810;,
  0.511040;0.587260;,
  0.488920;0.567810;,
  0.488920;0.587260;,
  0.471490;0.567810;,
  0.474540;0.587360;,
  0.457200;0.573570;,
  0.457920;0.587520;,
  0.542040;0.596880;,
  0.525420;0.596880;,
  0.511040;0.596880;,
  0.488920;0.596880;,
  0.474540;0.596880;,
  0.457920;0.596880;,
  0.499980;0.596880;,
  0.552860;0.587520;,
  0.499980;0.587520;,
  0.499980;0.587520;,
  0.447100;0.587520;,
  0.499980;0.587520;,
  0.538450;0.551930;,
  0.538500;0.587520;,
  0.526780;0.545740;,
  0.511610;0.546350;,
  0.488350;0.546420;,
  0.473160;0.546040;,
  0.461510;0.551820;,
  0.461460;0.587520;,
  0.538500;0.596880;,
  0.499980;0.596880;,
  0.499980;0.596880;,
  0.542040;0.596880;,
  0.461460;0.596880;,
  0.457920;0.596880;,
  0.552860;0.596880;,
  0.499980;0.596880;,
  0.447100;0.596880;;
 }
}
