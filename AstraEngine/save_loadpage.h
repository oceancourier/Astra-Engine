#pragma once
#include <atomic>
#include "AsciiArtResource.h"
#include "filemanager.h"
#include "windowinformation.h"
#include "savedatamanager.h"
#include "textbox.h"
class AstraEngine;
class save_loadpage
{
public:
	save_loadpage(AstraEngine *astraengine,savedatamanager *Savedatamanager);
	void startsave_loadpage(int start_from,int start_mode);
	void endsave_loadpage();
	void initializeSaveDataInformationLogo();
	void updateSaveDataInformationLogo();
	void initializeUI();
	void cls();
	void updateUI();

	void hide_UI();

	void clicksave_loadbotton1();
	void clicksave_loadbotton2();
	void clicksave_loadbotton3();
	void clickbackbotton();
	std::atomic<int> thread_information{ 0 };//0�����������У�1�����˳���2�������е�����ⴰ�ڱ仯������¼�
	std::atomic<int> save_loadpage_mode{ 0 };//1��ʾ�����˵����룬2��ʾ����Ϸ�������
	std::atomic<int> save_or_load{ 0 };//1��ʾ�浵��2��ʾ����

	SaveDataInformationLogo SaveDataInformationLogo1;
	SaveDataInformationLogo SaveDataInformationLogo2;
	SaveDataInformationLogo SaveDataInformationLogo3;
	BackLogo backlogo;

private:
	windowinformation WindowInformation;
	void detectWindowChange();
	void detectMouseEvent();
	AstraEngine *astraEngine;
	savedatamanager* SaveDataManager;
};