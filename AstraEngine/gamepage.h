#pragma once
#include "windowinformation.h"
#include "AsciiArtResource.h"
#include "textbox.h"
#include "Ascii_image.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <atomic>
#include <thread>
#include <mutex>
class AstraEngine;
class gamepage {
public:
	//void detect_MouseEvent();
	//void updateinformation();
	void startgamepage();
	void endgamepage();
	void cls();

	void changeimage(std::string filename);
	void changetext(std::string text);

	void initializeUI();
	void show_UI();
	void updateUI();
	void setCursorToBottomRight();
	void detectWindowChange();
	void hide_UI();
	//~gamepage();

	std::string getcurrenttext();
	std::string getcurrentimagepath();
	gamepage(AstraEngine *astraengine);
	void setcurrenttext(std::string text) { textbox.setText(text); }
	void setcurrentimagepath(std::string imagepath) { Ascii_image.setFilename(imagepath); /*Ascii_image.UpdateAsciiVector();*/ }
protected:
	std::atomic<int> thread_information{ 0 };//0代表正在运行，1代表退出，2代表运行但不监测窗口变化和鼠标事件
	windowinformation WindowInformation;
private:
	Ascii_image Ascii_image;
	InsufficientspaceLogo InsufficientspaceLogo;
	textbox textbox;
	SaveLogo SaveLogo;
	LoadLogo LoadLogo;
	TitleLogo TitleLogo;

	AstraEngine* astraEngine;
	void detect_MouseEvent();
};