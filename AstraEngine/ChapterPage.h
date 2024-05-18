#pragma once
#include "windowinformation.h"
#include <atomic>
#include <thread>
class ChapterPage {
public:
	void startChapterPage(std::string ChapterString);
	void updateUI();
	void cls();
	void detectMouseEvent();
	void detectWindowChange();
private:
	std::string message;
	windowinformation WindowInformation;
	std::atomic<int> thread_information{ 0 };//0代表正在运行，1代表退出，2代表运行但不监测窗口变化和鼠标事件
};