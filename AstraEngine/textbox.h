#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <windows.h>

class textbox {
private:
    int width, height; // �ı���Ŀ�Ⱥ͸߶�
    int centerX, centerY; // �ı������ĵ�����
    std::string text; // �ı����е��ı�����
    std::vector<std::string> lines; // �洢������ÿһ���ı�
    int textSpeed{ 500 };  // �ı���ʾ�ٶȣ��Ժ���Ϊ��λ

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