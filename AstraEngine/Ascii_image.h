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
	//下面为输出字符画的函数定义和变量定义
	int centerX;
	int centerY;
	//保存字符画的中心坐标
	int topLeftX;
	int topLeftY;
	int topRightX;
	int topRightY;
	int bottomLeftX;
	int bottomLeftY;
	int bottomRightX;
	int bottomRightY;
	//保存字符画的四个角的坐标
	void setCenter(int x, int y) {
		centerX = x;
		centerY = y;
	}
	void UpdateAsciiVector();//将字符画保存为vector
	int getCenterX() const { return centerX; }
	int getCenterY() const { return centerY; }
	void print(int color = 7);//输出字符画
	static void gotoxy(int x, int y);//设置光标位置
	void setFilename(std::string filename);//设置文件名
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
	//生成图片相关的函数定义

	int pixelToGray(COLORREF color);//将像素转换为灰度值

	std::vector<std::vector<COLORREF>> readBMP(std:: string filename);//读取BMP文件

	std::vector<std::vector<COLORREF>> resizeBMP(std::vector<std::vector<COLORREF>>& originalPixels, int newWidth, int newHeight);//调整图片大小

	char grayToChar(int gray);//将灰度值转换为字符


	std::string filename="no file";
	std::vector<std::string> art;

};
