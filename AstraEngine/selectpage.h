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
	std::atomic<int> thread_information{ 0 };//0代表正在运行，1代表退出，2代表运行但不监测窗口变化和鼠标事件
	std::atomic<int> choice{ 0 };//1表示选择第一个选项，2表示选择第二个选项
};