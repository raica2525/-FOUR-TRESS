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
 210;
 553.02722;69.21190;-558.24512;,
 -563.63312;69.21190;-558.24512;,
 -563.63312;3347.59766;-558.24512;,
 553.02722;3347.59766;-558.24512;,
 -563.63312;3347.59766;558.41541;,
 553.02722;3347.59766;558.41541;,
 -563.63312;69.21190;558.41541;,
 553.02722;69.21190;558.41541;,
 -563.63312;69.21190;-558.24512;,
 553.02722;69.21190;-558.24512;,
 -563.63312;69.21190;558.41541;,
 -563.63312;3347.59766;558.41541;,
 553.02722;69.21190;558.41541;,
 553.02722;3347.59766;558.41541;,
 886.92181;108.15970;-892.13959;,
 -897.52777;108.15970;-892.13959;,
 -897.52777;1892.61060;-892.13959;,
 886.92181;1892.61060;-892.13959;,
 -897.52777;1892.61060;892.30609;,
 886.92181;1892.61060;892.30609;,
 -897.52777;108.15970;892.30609;,
 886.92181;108.15970;892.30609;,
 -897.52777;108.15970;-892.13959;,
 886.92181;108.15970;-892.13959;,
 -897.52777;108.15970;892.30609;,
 -897.52777;1892.61060;892.30609;,
 886.92181;108.15970;892.30609;,
 886.92181;1892.61060;892.30609;,
 140.71770;155.76120;-894.19122;,
 -898.22998;155.76120;-894.19122;,
 -898.22998;4813.89355;-894.19122;,
 140.71770;4813.89355;-894.19122;,
 -898.22998;4813.89355;144.75841;,
 140.71770;4813.89355;144.75841;,
 -898.22998;155.76120;144.75841;,
 140.71770;155.76120;144.75841;,
 -898.22998;155.76120;-894.19122;,
 140.71770;155.76120;-894.19122;,
 -898.22998;155.76120;144.75841;,
 -898.22998;4813.89355;144.75841;,
 140.71770;155.76120;144.75841;,
 140.71770;4813.89355;144.75841;,
 682.77863;219.90190;191.73129;,
 186.52119;219.90190;191.73129;,
 186.52119;6107.26660;191.73129;,
 682.77863;6107.26660;191.73129;,
 186.52119;6107.26660;687.98938;,
 682.77863;6107.26660;687.98938;,
 186.52119;219.90190;687.98938;,
 682.77863;219.90190;687.98938;,
 186.52119;219.90190;191.73129;,
 682.77863;219.90190;191.73129;,
 186.52119;219.90190;687.98938;,
 186.52119;6107.26660;687.98938;,
 682.77863;219.90190;687.98938;,
 682.77863;6107.26660;687.98938;,
 -160.90871;118.27030;156.31030;,
 -728.01031;118.27030;156.31030;,
 -728.01031;4270.99268;156.31030;,
 -160.90871;4270.99268;156.31030;,
 -728.01031;4270.99268;723.40997;,
 -160.90871;4270.99268;723.40997;,
 -728.01031;118.27030;723.40997;,
 -160.90871;118.27030;723.40997;,
 -728.01031;118.27030;156.31030;,
 -160.90871;118.27030;156.31030;,
 -728.01031;118.27030;723.40997;,
 -728.01031;4270.99268;723.40997;,
 -160.90871;118.27030;723.40997;,
 -160.90871;4270.99268;723.40997;,
 147.25630;137.43359;-355.60950;,
 -355.61200;137.43359;-355.60950;,
 -355.61200;7299.01953;-355.60950;,
 147.25630;7299.01953;-355.60950;,
 -355.61200;7299.01953;147.26019;,
 147.25630;7299.01953;147.26019;,
 -355.61200;137.43359;147.26019;,
 147.25630;137.43359;147.26019;,
 -355.61200;137.43359;-355.60950;,
 147.25630;137.43359;-355.60950;,
 -355.61200;137.43359;147.26019;,
 -355.61200;7299.01953;147.26019;,
 147.25630;137.43359;147.26019;,
 147.25630;7299.01953;147.26019;,
 875.82312;132.59550;178.40491;,
 405.07660;132.59550;178.40491;,
 405.07660;2430.71094;178.40491;,
 875.82312;2430.71094;178.40491;,
 405.07660;2430.71094;847.02228;,
 875.82312;2430.71094;847.02228;,
 405.07660;132.59550;847.02228;,
 875.82312;132.59550;847.02228;,
 405.07660;132.59550;178.40491;,
 875.82312;132.59550;178.40491;,
 405.07660;132.59550;847.02228;,
 405.07660;2430.71094;847.02228;,
 875.82312;132.59550;847.02228;,
 875.82312;2430.71094;847.02228;,
 994.38190;0.70070;-999.59949;,
 -1004.98792;0.70070;-999.59949;,
 -1004.98792;2000.06921;-999.59949;,
 994.38190;2000.06921;-999.59949;,
 -1004.98792;2000.06921;999.76990;,
 994.38190;2000.06921;999.76990;,
 -1004.98792;0.70070;999.76990;,
 994.38190;0.70070;999.76990;,
 -1004.98792;0.70070;-999.59949;,
 994.38190;0.70070;-999.59949;,
 -1004.98792;0.70070;999.76990;,
 -1004.98792;2000.06921;999.76990;,
 994.38190;0.70070;999.76990;,
 994.38190;2000.06921;999.76990;,
 751.99219;143.84109;122.52060;,
 117.31010;143.84109;122.52060;,
 117.31010;6183.31152;122.52060;,
 751.99219;6183.31152;122.52060;,
 117.31010;6183.31152;757.19952;,
 751.99219;6183.31152;757.19952;,
 117.31010;143.84109;757.19952;,
 751.99219;143.84109;757.19952;,
 117.31010;143.84109;122.52060;,
 751.99219;143.84109;122.52060;,
 117.31010;143.84109;757.19952;,
 117.31010;6183.31152;757.19952;,
 751.99219;143.84109;757.19952;,
 751.99219;6183.31152;757.19952;,
 657.10553;34.99780;-662.32507;,
 -667.71143;34.99780;-662.32507;,
 -667.71143;3424.65796;-662.32507;,
 657.10553;3424.65796;-662.32507;,
 -667.71143;3424.65796;662.49219;,
 657.10553;3424.65796;662.49219;,
 -667.71143;34.99780;662.49219;,
 657.10553;34.99780;662.49219;,
 -667.71143;34.99780;-662.32507;,
 657.10553;34.99780;-662.32507;,
 -667.71143;34.99780;662.49219;,
 -667.71143;3424.65796;662.49219;,
 657.10553;34.99780;662.49219;,
 657.10553;3424.65796;662.49219;,
 211.85809;34.99780;-965.33197;,
 -969.37109;34.99780;-965.33197;,
 -969.37109;4934.66064;-965.33197;,
 211.85809;4934.66064;-965.33197;,
 -969.37109;4934.66064;215.89940;,
 211.85809;4934.66064;215.89940;,
 -969.37109;34.99780;215.89940;,
 211.85809;34.99780;215.89940;,
 -969.37109;34.99780;-965.33197;,
 211.85809;34.99780;-965.33197;,
 -969.37109;34.99780;215.89940;,
 -969.37109;4934.66064;215.89940;,
 211.85809;34.99780;215.89940;,
 211.85809;4934.66064;215.89940;,
 213.16190;34.99780;-421.51471;,
 -421.51880;34.99780;-421.51471;,
 -421.51880;7401.45312;-421.51471;,
 213.16190;7401.45312;-421.51471;,
 -421.51880;7401.45312;213.16570;,
 213.16190;7401.45312;213.16570;,
 -421.51880;34.99780;213.16570;,
 213.16190;34.99780;213.16570;,
 -421.51880;34.99780;-421.51471;,
 213.16190;34.99780;-421.51471;,
 -421.51880;34.99780;213.16570;,
 -421.51880;7401.45312;213.16570;,
 213.16190;34.99780;213.16570;,
 213.16190;7401.45312;213.16570;,
 -127.11960;34.99780;122.52060;,
 -761.80048;34.99780;122.52060;,
 -761.80048;4354.26758;122.52060;,
 -127.11960;4354.26758;122.52060;,
 -761.80048;4354.26758;757.19952;,
 -127.11960;4354.26758;757.19952;,
 -761.80048;34.99780;757.19952;,
 -127.11960;34.99780;757.19952;,
 -761.80048;34.99780;122.52060;,
 -127.11960;34.99780;122.52060;,
 -761.80048;34.99780;757.19952;,
 -761.80048;4354.26758;757.19952;,
 -127.11960;34.99780;757.19952;,
 -127.11960;4354.26758;757.19952;,
 957.79059;35.57840;61.98390;,
 323.10931;35.57840;61.98390;,
 323.10931;2527.73291;61.98390;,
 957.79059;2527.73291;61.98390;,
 323.10931;2527.73291;963.44623;,
 957.79059;2527.73291;963.44623;,
 323.10931;35.57840;963.44623;,
 957.79059;35.57840;963.44623;,
 323.10931;35.57840;61.98390;,
 957.79059;35.57840;61.98390;,
 323.10931;35.57840;963.44623;,
 323.10931;2527.73291;963.44623;,
 957.79059;35.57840;963.44623;,
 957.79059;2527.73291;963.44623;,
 875.82312;132.59550;178.40491;,
 405.07660;132.59550;178.40491;,
 405.07660;2430.71094;178.40491;,
 875.82312;2430.71094;178.40491;,
 405.07660;2430.71094;847.02228;,
 875.82312;2430.71094;847.02228;,
 405.07660;132.59550;847.02228;,
 875.82312;132.59550;847.02228;,
 405.07660;132.59550;178.40491;,
 875.82312;132.59550;178.40491;,
 405.07660;132.59550;847.02228;,
 405.07660;2430.71094;847.02228;,
 875.82312;132.59550;847.02228;,
 875.82312;2430.71094;847.02228;;
 
 90;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;1,10,11,2;,
 4;12,0,3,13;,
 4;14,15,16,17;,
 4;17,16,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;15,24,25,16;,
 4;26,14,17,27;,
 4;28,29,30,31;,
 4;31,30,32,33;,
 4;33,32,34,35;,
 4;35,34,36,37;,
 4;29,38,39,30;,
 4;40,28,31,41;,
 4;42,43,44,45;,
 4;45,44,46,47;,
 4;47,46,48,49;,
 4;49,48,50,51;,
 4;43,52,53,44;,
 4;54,42,45,55;,
 4;56,57,58,59;,
 4;59,58,60,61;,
 4;61,60,62,63;,
 4;63,62,64,65;,
 4;57,66,67,58;,
 4;68,56,59,69;,
 4;70,71,72,73;,
 4;73,72,74,75;,
 4;75,74,76,77;,
 4;77,76,78,79;,
 4;71,80,81,72;,
 4;82,70,73,83;,
 4;84,85,86,87;,
 4;87,86,88,89;,
 4;89,88,90,91;,
 4;91,90,92,93;,
 4;85,94,95,86;,
 4;96,84,87,97;,
 4;98,99,100,101;,
 4;101,100,102,103;,
 4;103,102,104,105;,
 4;105,104,106,107;,
 4;99,108,109,100;,
 4;110,98,101,111;,
 4;112,113,114,115;,
 4;115,114,116,117;,
 4;117,116,118,119;,
 4;119,118,120,121;,
 4;113,122,123,114;,
 4;124,112,115,125;,
 4;126,127,128,129;,
 4;129,128,130,131;,
 4;131,130,132,133;,
 4;133,132,134,135;,
 4;127,136,137,128;,
 4;138,126,129,139;,
 4;140,141,142,143;,
 4;143,142,144,145;,
 4;145,144,146,147;,
 4;147,146,148,149;,
 4;141,150,151,142;,
 4;152,140,143,153;,
 4;154,155,156,157;,
 4;157,156,158,159;,
 4;159,158,160,161;,
 4;161,160,162,163;,
 4;155,164,165,156;,
 4;166,154,157,167;,
 4;168,169,170,171;,
 4;171,170,172,173;,
 4;173,172,174,175;,
 4;175,174,176,177;,
 4;169,178,179,170;,
 4;180,168,171,181;,
 4;182,183,184,185;,
 4;185,184,186,187;,
 4;187,186,188,189;,
 4;189,188,190,191;,
 4;183,192,193,184;,
 4;194,182,185,195;,
 4;196,197,198,199;,
 4;199,198,200,201;,
 4;201,200,202,203;,
 4;203,202,204,205;,
 4;197,206,207,198;,
 4;208,196,199,209;;
 
 MeshMaterialList {
  3;
  90;
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
  0,
  0,
  0,
  0,
  0,
  0;;
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
    "data\\TEXTURE\\block\\haiiro.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\block\\sukekuro.png";
   }
  }
 }
 MeshNormals {
  12;
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;;
  90;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;;
 }
 MeshTextureCoords {
  210;
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;;
 }
}
