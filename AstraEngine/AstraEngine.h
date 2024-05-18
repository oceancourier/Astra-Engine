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

	//���ڿ���Mainpage�ĺ���
	void Mainpage_clicknewgamebotton();
	void Mainpage_clickcontinuebotton();
	void Mainpage_clickexitbotton();


	//���ڿ���Gamepage�ĺ���
	void startgamepage();
	void Gamepage_clicksavebotton();
	void Gamepage_clickloadbotton();
	void Gamepage_clicktitlebotton();
	void Gamepage_clickscreen();
	void updateimage(const std::string& imagepath);
	void updatetextbox(const std::string& text);

	//���ڿ���Save_loadpage�ĺ���


	//���ڿ���Selectpage�ĺ���
	//�������ÿ���̨�ĺ���
	void setconsole();

	//���ڿ��ƴ��ڵĺ���
private:
	void game_run();
	std::atomic<int> game_information{ 0 };//0�����������У�1�����˳���2����
};