#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <windows.h>

class textbox {
private:
    int width, height; // 文本框的宽度和高度
    int centerX, centerY; // 文本框中心的坐标
    std::string text; // 文本框中的文本内容
    std::vector<std::string> lines; // 存储处理后的每一行文本
    int textSpeed{ 500 };  // 文本显示速度，以毫秒为单位

public:
    textbox(int w = 10, int h = 3);
    void setDimensions(int w, int h);
    void setCenter(int x, int y);
    void setText(const std::string& newText);
    void setTextSpeed(int speed);
    void displayFrame() const;
    void displayText();
	void updateposition();
    std::string getcurrenttext();

	int topleftx;
	int toplefty;
	int bottomrightx;
	int bottomrighty;
private:
    void generateLines();
    void animateText() const;
    void setCursorPosition(int x, int y) const;

};