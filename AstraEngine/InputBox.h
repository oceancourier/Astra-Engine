#include <iostream>
#include <string>
#include <windows.h>
#include "windowinformation.h"
class InputBox {
private:
	int width, height; // ����Ŀ�Ⱥ͸߶�
	std::string content; // �洢�������ݵ��ַ���
	std::string prompt; // ˵��������

public:
	InputBox(int w = 50, int h = 5);
	void displayBox();
	void getInput();
	void setPrompt(const std::string& newPrompt);
	const std::string& getContent() const;
	const std::string& getPrompt() const;
};