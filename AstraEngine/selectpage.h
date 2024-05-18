#pragma once
#include "windowinformation.h"
#include "AsciiArtResource.h"
#include <thread>
#include <string>
#include <atomic>
class selectpage {
public:
	selectpage();
	std::string startselectpage(std::string choice1, std::string choice2);
	void endselectpage();
	void cls();
	void initializeUI();
	void updateUI();

	void detectWindowChange();
	void detectMouseEvent();


	windowinformation WindowInformation;
	SaveDataInformationLogo ChoiceLogo1;
	SaveDataInformationLogo ChoiceLogo2;
private:
	void ClickChoiceLogo1();
	void ClickChoiceLogo2();
	std::atomic<int> thread_information{ 0 };//0�����������У�1�����˳���2�������е�����ⴰ�ڱ仯������¼�
	std::atomic<int> choice{ 0 };//1��ʾѡ���һ��ѡ�2��ʾѡ��ڶ���ѡ��
};