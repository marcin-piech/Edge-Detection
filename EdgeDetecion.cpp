#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef unsigned char byte_t;

struct BITMAPFILEHEADER {
	byte_t bfType[2];
	byte_t bfSize[4];
	byte_t bfReserved1[2];
	byte_t bfReserved2[2];
	byte_t bfOffBits[4];
};

struct BITMAPINFOHEADER {
	byte_t biSize[4];
	byte_t biWidth[4];
	byte_t biHeight[4];
	byte_t biPlanes[2];
	byte_t biBitCount[2];
	byte_t biCompression[4];
	byte_t biSizeImage[4];
	byte_t biXPelsPerMeter[4];
	byte_t biYPelsPerMeter[4];
	byte_t biClrUsed[4];
	byte_t biClrImportant[4];
};

struct MASKSCOLLECTION {
	short s1[3][3] = { {-1, 0, 1},
					 {-2, 0, 2},
					 {-1, 0, 1} };

	short s2[3][3] = { {0, 1, 2},
					 {-1, 0, 1},
					 {-2, -1, 0} };

	short s3[3][3] = { {1, 2, 1},
					 {0, 0, 0},
					 {-1, -2, -1} };

	short s4[3][3] = { {2, 1, 0},
					 {1, 0, -1},
					 {0, -1, -2} };

	short s5[3][3] = { {1, 0, -1},
					 {2, 0, -2},
					 {1, 0, -1} };

	short s6[3][3] = { {0, -1, -2},
					 {1, 0, -1},
					 {2, 1, 0} };

	short s7[3][3] = { {-1, -2, -1},
					 {0, 0, 0},
					 {1, 2, 1} };

	short s8[3][3] = { {-2, -1, 0},
					 {-1, 0, 1},
					 {0, 1, 2} };
};

struct PIXELS {
	byte_t b;
	byte_t g;
	byte_t r;
};

void readBFH(ifstream& ifs, BITMAPFILEHEADER& bfh) {
	ifs.read(reinterpret_cast<char*>(&bfh.bfType), sizeof(bfh.bfType));
	ifs.read(reinterpret_cast<char*>(&bfh.bfSize), sizeof(bfh.bfSize));
	ifs.read(reinterpret_cast<char*>(&bfh.bfReserved1), sizeof(bfh.bfReserved1));
	ifs.read(reinterpret_cast<char*>(&bfh.bfReserved2), sizeof(bfh.bfReserved2));
	ifs.read(reinterpret_cast<char*>(&bfh.bfOffBits), sizeof(bfh.bfOffBits));
}

void readBIH(ifstream& ifs, BITMAPINFOHEADER& bih) {
	ifs.read(reinterpret_cast<char*>(&bih.biSize), sizeof(bih.biSize));
	ifs.read(reinterpret_cast<char*>(&bih.biWidth), sizeof(bih.biWidth));
	ifs.read(reinterpret_cast<char*>(&bih.biHeight), sizeof(bih.biHeight));
	ifs.read(reinterpret_cast<char*>(&bih.biPlanes), sizeof(bih.biPlanes));
	ifs.read(reinterpret_cast<char*>(&bih.biBitCount), sizeof(bih.biBitCount));
	ifs.read(reinterpret_cast<char*>(&bih.biCompression), sizeof(bih.biCompression));
	ifs.read(reinterpret_cast<char*>(&bih.biSizeImage), sizeof(bih.biSizeImage));
	ifs.read(reinterpret_cast<char*>(&bih.biXPelsPerMeter), sizeof(bih.biXPelsPerMeter));
	ifs.read(reinterpret_cast<char*>(&bih.biYPelsPerMeter), sizeof(bih.biYPelsPerMeter));
	ifs.read(reinterpret_cast<char*>(&bih.biClrUsed), sizeof(bih.biClrUsed));
	ifs.read(reinterpret_cast<char*>(&bih.biClrImportant), sizeof(bih.biClrImportant));
}

void writeBFH(ofstream& ofs, BITMAPFILEHEADER& bfh) {
	ofs.write(reinterpret_cast<char*>(&bfh.bfType), sizeof(bfh.bfType));
	ofs.write(reinterpret_cast<char*>(&bfh.bfSize), sizeof(bfh.bfSize));
	ofs.write(reinterpret_cast<char*>(&bfh.bfReserved1), sizeof(bfh.bfReserved1));
	ofs.write(reinterpret_cast<char*>(&bfh.bfReserved2), sizeof(bfh.bfReserved2));
	ofs.write(reinterpret_cast<char*>(&bfh.bfOffBits), sizeof(bfh.bfOffBits));
}

void writeBIH(ofstream& ofs, BITMAPINFOHEADER& bih) {
	ofs.write(reinterpret_cast<char*>(&bih.biSize), sizeof(bih.biSize));
	ofs.write(reinterpret_cast<char*>(&bih.biWidth), sizeof(bih.biWidth));
	ofs.write(reinterpret_cast<char*>(&bih.biHeight), sizeof(bih.biHeight));
	ofs.write(reinterpret_cast<char*>(&bih.biPlanes), sizeof(bih.biPlanes));
	ofs.write(reinterpret_cast<char*>(&bih.biBitCount), sizeof(bih.biBitCount));
	ofs.write(reinterpret_cast<char*>(&bih.biCompression), sizeof(bih.biCompression));
	ofs.write(reinterpret_cast<char*>(&bih.biSizeImage), sizeof(bih.biSizeImage));
	ofs.write(reinterpret_cast<char*>(&bih.biXPelsPerMeter), sizeof(bih.biXPelsPerMeter));
	ofs.write(reinterpret_cast<char*>(&bih.biYPelsPerMeter), sizeof(bih.biYPelsPerMeter));
	ofs.write(reinterpret_cast<char*>(&bih.biClrUsed), sizeof(bih.biClrUsed));
	ofs.write(reinterpret_cast<char*>(&bih.biClrImportant), sizeof(bih.biClrImportant));
}

int wordValue(byte_t* t) {																// [2] bajty
	return t[0] + t[1] * 256;
}

int dwordValue(byte_t* t) {																// [4] bajty 
	return t[0] + t[1] * 256 + t[2] * 256 * 256 + t[3] * 256 * 256 * 256;
}

void showBFH(BITMAPFILEHEADER& bfh) {
	cout << "bfh.bfType " << wordValue(bfh.bfType) << endl;
	cout << "bfh.bfSize " << dwordValue(bfh.bfSize) << endl;
	cout << "bfh.bfReserved1 " << wordValue(bfh.bfReserved1) << endl;
	cout << "bfh.bfReserved2 " << wordValue(bfh.bfReserved2) << endl;
	cout << "bfh.bfOffBits " << dwordValue(bfh.bfOffBits) << endl;
}

void showBIH(BITMAPINFOHEADER& bih) {
	cout << "bih.biSize " << dwordValue(bih.biSize) << endl;
	cout << "bih.biWidth " << dwordValue(bih.biWidth) << endl;
	cout << "bih.biHeight " << dwordValue(bih.biHeight) << endl;
	cout << "bih.biPlanes " << wordValue(bih.biPlanes) << endl;
	cout << "bih.biBitCount " << wordValue(bih.biBitCount) << endl;
	cout << "bih.biCompression " << dwordValue(bih.biCompression) << endl;
	cout << "bih.biSizeImage " << dwordValue(bih.biSizeImage) << endl;
	cout << "bih.biXPelsPerMeter " << dwordValue(bih.biXPelsPerMeter) << endl;
	cout << "bih.biYPelsPerMeter " << dwordValue(bih.biYPelsPerMeter) << endl;
	cout << "bih.biClrUsed " << dwordValue(bih.biClrUsed) << endl;
	cout << "bih.biClrImportant " << dwordValue(bih.biClrImportant) << endl;
}


int main()																							//int main()
{
	ifstream ifs("picture.bmp", ios::binary);
	if (!ifs) {
		cout << "Blad otwarcia pliku \n";
		system("pause");
		return 0;
	}
	ofstream ofs("result.bmp", ios::binary);

	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;																			//structures

	MASKSCOLLECTION m;

	readBFH(ifs, bfh);
	readBIH(ifs, bih);

	writeBFH(ofs, bfh);
	writeBIH(ofs, bih);

	showBFH(bfh);
	cout << endl;
	showBIH(bih);
	cout << endl;

	int actualSize = dwordValue(bfh.bfSize) - dwordValue(bfh.bfOffBits);
	const int h = dwordValue(bih.biHeight);
	const int w = dwordValue(bih.biWidth);
	int zerosPerRow = 0;
	if (w % 4 != 0) {
		int bytesPerRow = w * 3;
		zerosPerRow = ((bytesPerRow / 4) + 1) * 4 - bytesPerRow;
	}
	cout << "zerosPerRow = " << zerosPerRow << endl;

	vector<vector<PIXELS>> p(h, vector<PIXELS>(w));												//vector

	unsigned char zero;
	for (int i = 0; i < h; i++) {																	//read
		for (int j = 0; j < w; j++) {
			// Blue
			ifs.read(reinterpret_cast<char*>(&p[i][j].b), sizeof(char));

			// Green
			ifs.read(reinterpret_cast<char*>(&p[i][j].g), sizeof(char));

			// Red
			ifs.read(reinterpret_cast<char*>(&p[i][j].r), sizeof(char));

		}
		for (int j = 0; j < zerosPerRow; j++) {
			ifs.read(reinterpret_cast<char*>(&zero), sizeof(char));
		}
	}

	// --------- Convolution ---------------														// Convolution

	//Blue value
	for (int i = 1; i < (h - 1); i++) {
		for (int j = 1; j < (w - 1); j++) {
			p[i][j].b = 0;
			// s1
			p[i][j].b = p[i][j].b + (m.s1[0][0] * p[i - 1][j - 1].b + m.s1[0][1] * p[i - 1][j].b + m.s1[0][2] * p[i - 1][j + 1].b + m.s1[1][0] * p[i][j - 1].b + m.s1[1][1] * p[i][j].b + m.s1[1][2] * p[i][j + 1].b + m.s1[2][0] * p[i + 1][j - 1].b + m.s1[2][1] * p[i + 1][j].b + m.s1[2][2] * p[i + 1][j + 1].b);
			// s2
			p[i][j].b = p[i][j].b + (m.s2[0][0] * p[i - 1][j - 1].b + m.s2[0][1] * p[i - 1][j].b + m.s2[0][2] * p[i - 1][j + 1].b + m.s2[1][0] * p[i][j - 1].b + m.s2[1][1] * p[i][j].b + m.s2[1][2] * p[i][j + 1].b + m.s2[2][0] * p[i + 1][j - 1].b + m.s2[2][1] * p[i + 1][j].b + m.s2[2][2] * p[i + 1][j + 1].b);
			// s3
			p[i][j].b = p[i][j].b + (m.s3[0][0] * p[i - 1][j - 1].b + m.s3[0][1] * p[i - 1][j].b + m.s3[0][2] * p[i - 1][j + 1].b + m.s3[1][0] * p[i][j - 1].b + m.s3[1][1] * p[i][j].b + m.s3[1][2] * p[i][j + 1].b + m.s3[2][0] * p[i + 1][j - 1].b + m.s3[2][1] * p[i + 1][j].b + m.s3[2][2] * p[i + 1][j + 1].b);
			// s4
			p[i][j].b = p[i][j].b + (m.s4[0][0] * p[i - 1][j - 1].b + m.s4[0][1] * p[i - 1][j].b + m.s4[0][2] * p[i - 1][j + 1].b + m.s4[1][0] * p[i][j - 1].b + m.s4[1][1] * p[i][j].b + m.s4[1][2] * p[i][j + 1].b + m.s4[2][0] * p[i + 1][j - 1].b + m.s4[2][1] * p[i + 1][j].b + m.s4[2][2] * p[i + 1][j + 1].b);
			// s5
			p[i][j].b = p[i][j].b + (m.s5[0][0] * p[i - 1][j - 1].b + m.s5[0][1] * p[i - 1][j].b + m.s5[0][2] * p[i - 1][j + 1].b + m.s5[1][0] * p[i][j - 1].b + m.s5[1][1] * p[i][j].b + m.s5[1][2] * p[i][j + 1].b + m.s5[2][0] * p[i + 1][j - 1].b + m.s5[2][1] * p[i + 1][j].b + m.s5[2][2] * p[i + 1][j + 1].b);
			// s6
			p[i][j].b = p[i][j].b + (m.s6[0][0] * p[i - 1][j - 1].b + m.s6[0][1] * p[i - 1][j].b + m.s6[0][2] * p[i - 1][j + 1].b + m.s6[1][0] * p[i][j - 1].b + m.s6[1][1] * p[i][j].b + m.s6[1][2] * p[i][j + 1].b + m.s6[2][0] * p[i + 1][j - 1].b + m.s6[2][1] * p[i + 1][j].b + m.s6[2][2] * p[i + 1][j + 1].b);
			// s7
			p[i][j].b = p[i][j].b + (m.s7[0][0] * p[i - 1][j - 1].b + m.s7[0][1] * p[i - 1][j].b + m.s7[0][2] * p[i - 1][j + 1].b + m.s7[1][0] * p[i][j - 1].b + m.s7[1][1] * p[i][j].b + m.s7[1][2] * p[i][j + 1].b + m.s7[2][0] * p[i + 1][j - 1].b + m.s7[2][1] * p[i + 1][j].b + m.s7[2][2] * p[i + 1][j + 1].b);
			// s8
			p[i][j].b = p[i][j].b + (m.s8[0][0] * p[i - 1][j - 1].b + m.s8[0][1] * p[i - 1][j].b + m.s8[0][2] * p[i - 1][j + 1].b + m.s8[1][0] * p[i][j - 1].b + m.s8[1][1] * p[i][j].b + m.s8[1][2] * p[i][j + 1].b + m.s8[2][0] * p[i + 1][j - 1].b + m.s8[2][1] * p[i + 1][j].b + m.s8[2][2] * p[i + 1][j + 1].b);

			// SUMA Obraz(x, y) / 8
			p[i][j].b = p[i][j].b / 8;
		}
	}

	// Green value
	for (int i = 1; i < (h - 1); i++) {
		for (int j = 1; j < (w - 1); j++) {
			p[i][j].g = 0;
			// s1
			p[i][j].g = p[i][j].g + (m.s1[0][0] * p[i - 1][j - 1].g + m.s1[0][1] * p[i - 1][j].g + m.s1[0][2] * p[i - 1][j + 1].g + m.s1[1][0] * p[i][j - 1].g + m.s1[1][1] * p[i][j].g + m.s1[1][2] * p[i][j + 1].g + m.s1[2][0] * p[i + 1][j - 1].g + m.s1[2][1] * p[i + 1][j].g + m.s1[2][2] * p[i + 1][j + 1].g);
			// s2
			p[i][j].g = p[i][j].g + (m.s2[0][0] * p[i - 1][j - 1].g + m.s2[0][1] * p[i - 1][j].g + m.s2[0][2] * p[i - 1][j + 1].g + m.s2[1][0] * p[i][j - 1].g + m.s2[1][1] * p[i][j].g + m.s2[1][2] * p[i][j + 1].g + m.s2[2][0] * p[i + 1][j - 1].g + m.s2[2][1] * p[i + 1][j].g + m.s2[2][2] * p[i + 1][j + 1].g);
			// s3
			p[i][j].g = p[i][j].g + (m.s3[0][0] * p[i - 1][j - 1].g + m.s3[0][1] * p[i - 1][j].g + m.s3[0][2] * p[i - 1][j + 1].g + m.s3[1][0] * p[i][j - 1].g + m.s3[1][1] * p[i][j].g + m.s3[1][2] * p[i][j + 1].g + m.s3[2][0] * p[i + 1][j - 1].g + m.s3[2][1] * p[i + 1][j].g + m.s3[2][2] * p[i + 1][j + 1].g);
			// s4
			p[i][j].g = p[i][j].g + (m.s4[0][0] * p[i - 1][j - 1].g + m.s4[0][1] * p[i - 1][j].g + m.s4[0][2] * p[i - 1][j + 1].g + m.s4[1][0] * p[i][j - 1].g + m.s4[1][1] * p[i][j].g + m.s4[1][2] * p[i][j + 1].g + m.s4[2][0] * p[i + 1][j - 1].g + m.s4[2][1] * p[i + 1][j].g + m.s4[2][2] * p[i + 1][j + 1].g);
			// s5
			p[i][j].g = p[i][j].g + (m.s5[0][0] * p[i - 1][j - 1].g + m.s5[0][1] * p[i - 1][j].g + m.s5[0][2] * p[i - 1][j + 1].g + m.s5[1][0] * p[i][j - 1].g + m.s5[1][1] * p[i][j].g + m.s5[1][2] * p[i][j + 1].g + m.s5[2][0] * p[i + 1][j - 1].g + m.s5[2][1] * p[i + 1][j].g + m.s5[2][2] * p[i + 1][j + 1].g);
			// s6
			p[i][j].g = p[i][j].g + (m.s6[0][0] * p[i - 1][j - 1].g + m.s6[0][1] * p[i - 1][j].g + m.s6[0][2] * p[i - 1][j + 1].g + m.s6[1][0] * p[i][j - 1].g + m.s6[1][1] * p[i][j].g + m.s6[1][2] * p[i][j + 1].g + m.s6[2][0] * p[i + 1][j - 1].g + m.s6[2][1] * p[i + 1][j].g + m.s6[2][2] * p[i + 1][j + 1].g);
			// s7
			p[i][j].g = p[i][j].g + (m.s7[0][0] * p[i - 1][j - 1].g + m.s7[0][1] * p[i - 1][j].g + m.s7[0][2] * p[i - 1][j + 1].g + m.s7[1][0] * p[i][j - 1].g + m.s7[1][1] * p[i][j].g + m.s7[1][2] * p[i][j + 1].g + m.s7[2][0] * p[i + 1][j - 1].g + m.s7[2][1] * p[i + 1][j].g + m.s7[2][2] * p[i + 1][j + 1].g);
			// s8
			p[i][j].g = p[i][j].g + (m.s8[0][0] * p[i - 1][j - 1].g + m.s8[0][1] * p[i - 1][j].g + m.s8[0][2] * p[i - 1][j + 1].g + m.s8[1][0] * p[i][j - 1].g + m.s8[1][1] * p[i][j].g + m.s8[1][2] * p[i][j + 1].g + m.s8[2][0] * p[i + 1][j - 1].g + m.s8[2][1] * p[i + 1][j].g + m.s8[2][2] * p[i + 1][j + 1].g);

			// SUMA Obraz(x, y) / 8
			p[i][j].g = p[i][j].g / 8;
		}
	}

	// Red value
	for (int i = 1; i < (h - 1); i++) {
		for (int j = 1; j < (w - 1); j++) {
			p[i][j].r = 0;
			// s1
			p[i][j].r = p[i][j].r + (m.s1[0][0] * p[i - 1][j - 1].r + m.s1[0][1] * p[i - 1][j].r + m.s1[0][2] * p[i - 1][j + 1].r + m.s1[1][0] * p[i][j - 1].r + m.s1[1][1] * p[i][j].r + m.s1[1][2] * p[i][j + 1].r + m.s1[2][0] * p[i + 1][j - 1].r + m.s1[2][1] * p[i + 1][j].r + m.s1[2][2] * p[i + 1][j + 1].r);
			// s2
			p[i][j].r = p[i][j].r + (m.s2[0][0] * p[i - 1][j - 1].r + m.s2[0][1] * p[i - 1][j].r + m.s2[0][2] * p[i - 1][j + 1].r + m.s2[1][0] * p[i][j - 1].r + m.s2[1][1] * p[i][j].r + m.s2[1][2] * p[i][j + 1].r + m.s2[2][0] * p[i + 1][j - 1].r + m.s2[2][1] * p[i + 1][j].r + m.s2[2][2] * p[i + 1][j + 1].r);
			// s3
			p[i][j].r = p[i][j].r + (m.s3[0][0] * p[i - 1][j - 1].r + m.s3[0][1] * p[i - 1][j].r + m.s3[0][2] * p[i - 1][j + 1].r + m.s3[1][0] * p[i][j - 1].r + m.s3[1][1] * p[i][j].r + m.s3[1][2] * p[i][j + 1].r + m.s3[2][0] * p[i + 1][j - 1].r + m.s3[2][1] * p[i + 1][j].r + m.s3[2][2] * p[i + 1][j + 1].r);
			// s4
			p[i][j].r = p[i][j].r + (m.s4[0][0] * p[i - 1][j - 1].r + m.s4[0][1] * p[i - 1][j].r + m.s4[0][2] * p[i - 1][j + 1].r + m.s4[1][0] * p[i][j - 1].r + m.s4[1][1] * p[i][j].r + m.s4[1][2] * p[i][j + 1].r + m.s4[2][0] * p[i + 1][j - 1].r + m.s4[2][1] * p[i + 1][j].r + m.s4[2][2] * p[i + 1][j + 1].r);
			// s5
			p[i][j].r = p[i][j].r + (m.s5[0][0] * p[i - 1][j - 1].r + m.s5[0][1] * p[i - 1][j].r + m.s5[0][2] * p[i - 1][j + 1].r + m.s5[1][0] * p[i][j - 1].r + m.s5[1][1] * p[i][j].r + m.s5[1][2] * p[i][j + 1].r + m.s5[2][0] * p[i + 1][j - 1].r + m.s5[2][1] * p[i + 1][j].r + m.s5[2][2] * p[i + 1][j + 1].r);
			// s6
			p[i][j].r = p[i][j].r + (m.s6[0][0] * p[i - 1][j - 1].r + m.s6[0][1] * p[i - 1][j].r + m.s6[0][2] * p[i - 1][j + 1].r + m.s6[1][0] * p[i][j - 1].r + m.s6[1][1] * p[i][j].r + m.s6[1][2] * p[i][j + 1].r + m.s6[2][0] * p[i + 1][j - 1].r + m.s6[2][1] * p[i + 1][j].r + m.s6[2][2] * p[i + 1][j + 1].r);
			// s7
			p[i][j].r = p[i][j].r + (m.s7[0][0] * p[i - 1][j - 1].r + m.s7[0][1] * p[i - 1][j].r + m.s7[0][2] * p[i - 1][j + 1].r + m.s7[1][0] * p[i][j - 1].r + m.s7[1][1] * p[i][j].r + m.s7[1][2] * p[i][j + 1].r + m.s7[2][0] * p[i + 1][j - 1].r + m.s7[2][1] * p[i + 1][j].r + m.s7[2][2] * p[i + 1][j + 1].r);
			// s8
			p[i][j].r = p[i][j].r + (m.s8[0][0] * p[i - 1][j - 1].r + m.s8[0][1] * p[i - 1][j].r + m.s8[0][2] * p[i - 1][j + 1].r + m.s8[1][0] * p[i][j - 1].r + m.s8[1][1] * p[i][j].r + m.s8[1][2] * p[i][j + 1].r + m.s8[2][0] * p[i + 1][j - 1].r + m.s8[2][1] * p[i + 1][j].r + m.s8[2][2] * p[i + 1][j + 1].r);

			// SUMA Obraz(x, y) / 8
			p[i][j].r = p[i][j].r / 8;
		}
	}

	// Black frame																					// Black frame
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {

			p[0][j].b = 0;
			p[i][0].b = 0;
			p[h - 1][j].b = 0;
			p[i][w - 1].b = 0;

			p[0][j].g = 0;
			p[i][0].g = 0;
			p[h - 1][j].g = 0;
			p[i][w - 1].g = 0;

			p[0][j].r = 0;
			p[i][0].r = 0;
			p[h - 1][j].r = 0;
			p[i][w - 1].r = 0;
		}
	}

	for (int i = 0; i < h; i++) {																	//write
		for (int j = 0; j < w; j++) {

			// Blue
			ofs.write(reinterpret_cast<char*>(&p[i][j].b), sizeof(char));

			// Green
			ofs.write(reinterpret_cast<char*>(&p[i][j].g), sizeof(char));

			// Red
			ofs.write(reinterpret_cast<char*>(&p[i][j].r), sizeof(char));
		}
		for (int j = 0; j < zerosPerRow; j++) {
			ofs.write(reinterpret_cast<char*>(&zero), sizeof(char));
		}
	}

	ifs.close();																					//close()
	ofs.close();

	return 0;
}