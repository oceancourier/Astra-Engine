#include "save_loadpage.h"
#include "AstraEngine.h"
save_loadpage::save_loadpage(AstraEngine *astraengine,savedatamanager *Savedatamanager)
{
	this->astraEngine = astraengine;
	this->SaveDataManager = Savedatamanager;
}

void save_loadpage::startsave_loadpage(int start_from, int start_mode)//1表示由主菜单进入，2表示由游戏界面进入
{
	initializeSaveDataInformationLogo();
	initializeUI();
	thread_information = 0;
	save_loadpage_mode = start_from;
	save_or_load = start_mode;

	std::thread detectMouseEventThread(&save_loadpage::detectMouseEvent, this);
	detectMouseEventThread.detach();
	std::thread detectWindowChangeThread(&save_loadpage::detectWindowChange, this);
	detectWindowChangeThread.join();
}

void save_loadpage::endsave_loadpage()
{
	thread_information = 1;
	cls();
}

void save_loadpage::initializeSaveDataInformationLogo()
{
	if (SaveDataManager->savedatalist[1] == 1) {
		SaveDataInformationLogo1.insertText(SaveDataManager->get_preview(1));
	}
	if (SaveDataManager->savedatalist[2] == 1) {
		SaveDataInformationLogo2.insertText(SaveDataManager->get_preview(2));
	}
	if (SaveDataManager->savedatalist[3] == 1) {
		SaveDataInformationLogo3.insertText(SaveDataManager->get_preview(3));
	}
}

void save_loadpage::updateSaveDataInformationLogo()
{
	SaveDataInformationLogo1.clearText();
	SaveDataInformationLogo2.clearText();
	SaveDataInformationLogo3.clearText();
	initializeSaveDataInformationLogo();
}

void save_loadpage::initializeUI()
{
	cls();  // 假设是清屏函数
	int partWidth = WindowInformation.WindowWidth / 3;
	int windowHeight = WindowInformation.WindowHeight;
	int buttonHeight = 5; // 每个按钮的高度
	int spaceBetweenButtons = 2; // 按钮之间的空间

	// 计算所有按钮加上间隔的总高度
	int totalButtonsHeight = (buttonHeight + spaceBetweenButtons) * 4 - spaceBetweenButtons;
	int startY = (windowHeight - totalButtonsHeight) / 2;  // 计算第一个按钮的起始Y位置

	int button1Y = startY;
	int button2Y = button1Y + buttonHeight + spaceBetweenButtons;
	int button3Y = button2Y + buttonHeight + spaceBetweenButtons;
	int button4Y = button3Y + buttonHeight + spaceBetweenButtons;

	// 所有按钮的水平中心位置设置为屏幕宽度的一半
	int centerX = WindowInformation.WindowWidth / 2;

	// 设置每个SaveDataInformationLogo的中心位置
	SaveDataInformationLogo1.setCenter(centerX, button1Y);
	SaveDataInformationLogo2.setCenter(centerX, button2Y);
	SaveDataInformationLogo3.setCenter(centerX, button3Y);
	backlogo.setCenter(centerX, button4Y);

	// 打印每个logo
	SaveDataInformationLogo1.print(7);
	SaveDataInformationLogo2.print(7);
	SaveDataInformationLogo3.print(7);
	backlogo.print(7);
}

void save_loadpage::cls()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD cCharsWritten;
	COORD coordScreen = { 0, 0 };    // 控制台屏幕左上角的坐标
	DWORD dwConSize;

	// 获取控制台当前的信息
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		return;
	}

	// 设置缓冲区大小与当前窗口大小一致
	COORD newSize;
	newSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	newSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	if (!SetConsoleScreenBufferSize(hConsole, newSize)) {
		// 如果无法设置缓冲区大小，可能是因为新的尺寸比当前缓冲区尺寸小
		std::cerr << "Error setting buffer size.\n";
	}
	// 计算控制台缓冲区的字符数
	dwConSize = newSize.X * newSize.Y;

	// 填充控制台缓冲区的全部区域
	if (!FillConsoleOutputCharacter(
		hConsole,         // Handle to console screen buffer 
		(TCHAR)' ',      // Character to write to the buffer
		dwConSize,        // Number of cells to write
		coordScreen,      // Coordinates of first cell
		&cCharsWritten))  // Receive number of characters written
	{
		return;
	}

	// 将光标移动到控制台左上角
	if (!SetConsoleCursorPosition(hConsole, coordScreen)) {
		return;
	}
}

void save_loadpage::updateUI()
{
	cls();  // 假设是清屏函数
	int partWidth = WindowInformation.WindowWidth / 3;
	int windowHeight = WindowInformation.WindowHeight;
	int buttonHeight = 5; // 每个按钮的高度
	int spaceBetweenButtons = 2; // 按钮之间的空间

	// 计算所有按钮加上间隔的总高度
	int totalButtonsHeight = (buttonHeight + spaceBetweenButtons) * 4 - spaceBetweenButtons;
	int startY = (windowHeight - totalButtonsHeight) / 2;  // 计算第一个按钮的起始Y位置

	int button1Y = startY;
	int button2Y = button1Y + buttonHeight + spaceBetweenButtons;
	int button3Y = button2Y + buttonHeight + spaceBetweenButtons;
	int button4Y = button3Y + buttonHeight + spaceBetweenButtons;

	// 所有按钮的水平中心位置设置为屏幕宽度的一半
	int centerX = WindowInformation.WindowWidth / 2;

	// 设置每个SaveDataInformationLogo的中心位置
	SaveDataInformationLogo1.setCenter(centerX, button1Y);
	SaveDataInformationLogo2.setCenter(centerX, button2Y);
	SaveDataInformationLogo3.setCenter(centerX, button3Y);
	backlogo.setCenter(centerX, button4Y);

	// 打印每个logo
	SaveDataInformationLogo1.print(7);
	SaveDataInformationLogo2.print(7);
	SaveDataInformationLogo3.print(7);
	backlogo.print(7);
}

void save_loadpage::hide_UI()
{
	thread_information = 2;
	cls();
}

void save_loadpage::clicksave_loadbotton1()
{
	if (save_or_load == 1) {
		SaveDataManager->savefile(1);
		SaveDataManager->savedatalist[1] = 1;
	}
	else if (save_or_load == 2) {
		SaveDataManager->readsavefile(1);
		SaveDataManager->update_gamepage();
	}
	updateSaveDataInformationLogo();
}

void save_loadpage::clicksave_loadbotton2()
{
	if (save_or_load == 1) {
		SaveDataManager->savefile(2);
		SaveDataManager->savedatalist[2] = 1;
	}
	else if (save_or_load == 2) {
		SaveDataManager->readsavefile(2);
		SaveDataManager->update_gamepage();
	}
	updateSaveDataInformationLogo();
}

void save_loadpage::clicksave_loadbotton3()
{
	if (save_or_load == 1) {
		SaveDataManager->savefile(3);
		SaveDataManager->savedatalist[3] = 1;
	}
	else if (save_or_load == 2) {
		SaveDataManager->readsavefile(3);
		SaveDataManager->update_gamepage();
	}
	updateSaveDataInformationLogo();
}

void save_loadpage::clickbackbotton()
{
	if (save_loadpage_mode == 1) {
		endsave_loadpage();
		astraEngine->Mainpage.startmainpage();
	}
	else if (save_loadpage_mode == 2) {
		endsave_loadpage();
		astraEngine->Gamepage.startgamepage();
	}
}

void save_loadpage::detectWindowChange()
{
	int windowWidth = WindowInformation.WindowWidth;
	int windowHeight = WindowInformation.WindowHeight;
	while (true) {
		if(thread_information==0)
		{
			WindowInformation.getConsoleSize();
			if (windowWidth != WindowInformation.WindowWidth || windowHeight != WindowInformation.WindowHeight) {
				windowWidth = WindowInformation.WindowWidth;
				windowHeight = WindowInformation.WindowHeight;
				updateUI();
				//std::cout << "Window size changed to " << windowWidth << "x" << windowHeight << std::endl;
			}
			if (thread_information == 1)
			{
				return;
			}
			Sleep(100);
		}
	}
}

void save_loadpage::detectMouseEvent()
{
	while (true) {
		if(thread_information==0)
		{
			HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
			DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
			SetConsoleMode(hStdin, fdwMode);
			INPUT_RECORD irInBuf[128];
			DWORD cNumRead;

			ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead);
			for (DWORD i = 0; i < cNumRead; i++) {
				if (irInBuf[i].EventType == MOUSE_EVENT) {
					MOUSE_EVENT_RECORD mer = irInBuf[i].Event.MouseEvent;
					if (mer.dwEventFlags == MOUSE_MOVED) {
						COORD pos = mer.dwMousePosition;
						if (pos.X >= SaveDataInformationLogo1.topLeftX && pos.X <= SaveDataInformationLogo1.topRightX &&
							pos.Y >= SaveDataInformationLogo1.topLeftY && pos.Y <= SaveDataInformationLogo1.bottomLeftY) {
							if (SaveDataInformationLogo1.color != 6)
							{
								SaveDataInformationLogo1.print(6);
							}
						}
						else {
							if (SaveDataInformationLogo1.color != 7)
							{
								SaveDataInformationLogo1.print(7);
							}
						}
						if (pos.X >= SaveDataInformationLogo2.topLeftX && pos.X <= SaveDataInformationLogo2.topRightX &&
							pos.Y >= SaveDataInformationLogo2.topLeftY && pos.Y <= SaveDataInformationLogo2.bottomLeftY) {
							if (SaveDataInformationLogo2.color != 6)
							{
								SaveDataInformationLogo2.print(6);
							}
						}
						else {
							if (SaveDataInformationLogo2.color != 7)
							{
								SaveDataInformationLogo2.print(7);
							}
						}
						if (pos.X >= SaveDataInformationLogo3.topLeftX && pos.X <= SaveDataInformationLogo3.topRightX &&
							pos.Y >= SaveDataInformationLogo3.topLeftY && pos.Y <= SaveDataInformationLogo3.bottomLeftY) {
							if (SaveDataInformationLogo3.color != 6)
							{
								SaveDataInformationLogo3.print(6);
							}
						}
						else {
							if (SaveDataInformationLogo3.color != 7)
							{
								SaveDataInformationLogo3.print(7);
							}
						}
						if (pos.X >= backlogo.topLeftX && pos.X <= backlogo.topRightX &&
							pos.Y >= backlogo.topLeftY && pos.Y <= backlogo.bottomLeftY) {
							if (backlogo.color != 6)
							{
								backlogo.print(6);
							}
						}
						else {
							if (backlogo.color != 7)
							{
								backlogo.print(7);
							}
						}
					}
					if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
						COORD pos = mer.dwMousePosition; // 直接使用控制台的坐标位置，不转换为客户端坐标
						if (pos.X >= SaveDataInformationLogo1.topLeftX && pos.X <= SaveDataInformationLogo1.topRightX &&
							pos.Y >= SaveDataInformationLogo1.topLeftY && pos.Y <= SaveDataInformationLogo1.bottomLeftY) {
							clicksave_loadbotton1();
						}
						else if (pos.X >= SaveDataInformationLogo2.topLeftX && pos.X <= SaveDataInformationLogo2.topRightX &&
							pos.Y >= SaveDataInformationLogo2.topLeftY && pos.Y <= SaveDataInformationLogo2.bottomLeftY) {
							clicksave_loadbotton2();
						}
						else if (pos.X >= SaveDataInformationLogo3.topLeftX && pos.X <= SaveDataInformationLogo3.topRightX &&
							pos.Y >= SaveDataInformationLogo3.topLeftY && pos.Y <= SaveDataInformationLogo3.bottomLeftY) {
							clicksave_loadbotton3();
						}
						else if (pos.X >= backlogo.topLeftX && pos.X <= backlogo.topRightX &&
							pos.Y >= backlogo.topLeftY && pos.Y <= backlogo.bottomLeftY)
						{
							clickbackbotton();
						}
					}
				}
			}
		}
		if (thread_information == 1) {
			return; // 确保能跳出外层循环
		}
	}
}
