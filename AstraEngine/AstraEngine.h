#pragma once
#include "filemanager.h"
#include "AudioPlayer.h"
#include "selectpage.h"
#include "ChapterPage.h"
#include "mainpage.h"
#include "save_loadpage.h"
#include "gamepage.h"
#include "savedatamanager.h"
#include "AsciiArtResource.h"
#include "Ascii_image.h"
#include "windowinformation.h"
#include "InputBox.h"
#include <string>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

class AstraEngine {
public:
	explicit AstraEngine();
	void startgame();

	mainpage Mainpage;
	gamepage Gamepage;
	save_loadpage Save_loadpage;
	filemanager Filemanager;
	savedatamanager Savedatamanager;
	selectpage Selectpage;
	ChapterPage ChapterPage;
	AudioPlayer AudioPlayer;

	//MusicPlayer MusicPlayer;

	void cls();
	void initializeFile();

	//用于控制Mainpage的函数
	void Mainpage_clicknewgamebotton();
	void Mainpage_clickcontinuebotton();
	void Mainpage_clickexitbotton();


	//用于控制Gamepage的函数
	void startgamepage();
	void Gamepage_clicksavebotton();
	void Gamepage_clickloadbotton();
	void Gamepage_clicktitlebotton();
	void Gamepage_clickscreen();
	void updateimage(const std::string& imagepath);
	void updatetextbox(const std::string& text);

	//用于控制Save_loadpage的函数


	//用于控制Selectpage的函数
	//用于设置控制台的函数
	void setconsole();

	//用于控制窗口的函数
private:
	void game_run();
	std::atomic<int> game_information{ 0 };//0代表正在运行，1代表退出，2代表
};