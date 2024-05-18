#include <iostream>
#include <string>
#include <windows.h>
#include "windowinformation.h"
class InputBox {
private:
	int width, height; // 方框的宽度和高度
	std::string content; // 存储输入内容的字符串
	std::string prompt; // 说明性文字

public:
	InputBox(int w = 50, int h = 5);
	void displayBox();
	void getInput();
	void setPrompt(const std::string& newPrompt);
	const std::string& getContent() const;
	const std::string& getPrompt() const;
};