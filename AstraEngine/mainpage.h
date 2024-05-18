#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include "windowinformation.h"
#include "AsciiArtResource.h"
class AstraEngine;
class Logoinformation {
public:
	int topleftX;
	int topleftY;
	int toprightX;
	int toprightY;
	int bottomleftX;
	int bottomleftY;
	int bottomrightX;
	int bottomrightY;
};
class mainpage {
public:
	mainpage(AstraEngine *astraengine=nullptr);
	void startmainpage();
	void endmainpage();

	void initializeUI();
	void show_UI();
	void updateUI();


	void detectWindowChange();
	void hide_UI();
	~mainpage();
protected:
	void detect_MouseEvent();
private:
	AstraLogo astraLogo{};
	StartLogo startLogo{};
	ExitLogo exitLogo{};
	ContinueLogo continueLogo{};

	Logoinformation astraLogoInformation{};
	Logoinformation startLogoInformation{};
	Logoinformation exitLogoInformation{};
	Logoinformation continueLogoInformation{};

	void updateinformation();
	void cls();
	std::atomic<int> thread_information{0};//0代表正在运行，1代表退出，2代表

	windowinformation WindowInformation;
	AstraEngine *astraEngine;//指向上层AstraEngine的指针
};
