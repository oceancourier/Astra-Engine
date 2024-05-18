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
	std::atomic<int> thread_information{ 0 };//0�����������У�1�����˳���2�������е�����ⴰ�ڱ仯������¼�
};