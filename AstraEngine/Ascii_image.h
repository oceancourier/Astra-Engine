#pragma once
#include <iostream>
#include <Windows.h>
#include <thread>
#include "AsciiArtResource.h"
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
class Ascii_image {
public:
	//����Ϊ����ַ����ĺ�������ͱ�������
	int centerX;
	int centerY;
	//�����ַ�������������
	int topLeftX;
	int topLeftY;
	int topRightX;
	int topRightY;
	int bottomLeftX;
	int bottomLeftY;
	int bottomRightX;
	int bottomRightY;
	//�����ַ������ĸ��ǵ�����
	void setCenter(int x, int y) {
		centerX = x;
		centerY = y;
	}
	void UpdateAsciiVector();//���ַ�������Ϊvector
	int getCenterX() const { return centerX; }
	int getCenterY() const { return centerY; }
	void print(int color = 7);//����ַ���
	static void gotoxy(int x, int y);//���ù��λ��
	void setFilename(std::string filename);//�����ļ���
	//
	int newWidth = 160; // Updated width
	int newHeight = 46; // Updated height

	std::string getfilename() {return filename;}
protected:
private:
	//Structs
	#pragma pack(push, 1)
		struct BMPHeader {
			char header[2];
			int fileSize;
			int reserved;
			int offset;
		};

		struct BMPInfoHeader {
			int size;
			int width;
			int height;
			short planes;
			short bitCount;
			int compression;
			int imageSize;
			int xResolution;
			int yResolution;
			int nColors;
			int importantColors;
		};
	#pragma pack(pop)
	const char* GRAY_SCALE = "@%#*+=-:. ";
	//����ͼƬ��صĺ�������

	int pixelToGray(COLORREF color);//������ת��Ϊ�Ҷ�ֵ

	std::vector<std::vector<COLORREF>> readBMP(std:: string filename);//��ȡBMP�ļ�

	std::vector<std::vector<COLORREF>> resizeBMP(std::vector<std::vector<COLORREF>>& originalPixels, int newWidth, int newHeight);//����ͼƬ��С

	char grayToChar(int gray);//���Ҷ�ֵת��Ϊ�ַ�


	std::string filename="no file";
	std::vector<std::string> art;

};
