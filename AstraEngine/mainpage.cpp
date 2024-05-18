#include "mainpage.h"
#include "AstraEngine.h"
#include <iostream>
#include <Windows.h>
void mainpage::endmainpage()
{
	thread_information = 1;
	cls();
}
mainpage::mainpage(AstraEngine *astraengine)
{
	this->astraEngine = astraengine;
}
void mainpage::startmainpage() {
	cls();
	initializeUI();
	thread_information = 0;

	std::thread detectMouseEventThread(&mainpage::detect_MouseEvent, this);
	detectMouseEventThread.detach();

	std::thread detectWindowChangeThread(&mainpage::detectWindowChange, this);
	detectWindowChangeThread.join();
}
void mainpage::show_UI()
{
	initializeUI();

	std::thread detectMouseEventThread(&mainpage::detect_MouseEvent, this);
	detectMouseEventThread.detach();

	std::thread detectWindowChangeThread(&mainpage::detectWindowChange, this);
	detectWindowChangeThread.join();

}
void mainpage::hide_UI()
{
	cls();
}
void mainpage::updateUI(){
	cls();
	astraLogo.setCenter(WindowInformation.WindowWidth / 2, WindowInformation.WindowHeight / 2-5);
	astraLogo.print();
	startLogo.setCenter(WindowInformation.WindowWidth / 2, astraLogo.bottomLeftY  + 4);
	startLogo.print();
	//std::cout << "startlogocenterX:" << startLogo.getCenterY() << std::endl;
	continueLogo.setCenter(WindowInformation.WindowWidth / 2, astraLogo.bottomLeftY + 8);
	continueLogo.print();
	//std::cout << "continuelogocenterX:" << continueLogo.getCenterY() << std::endl;
	exitLogo.setCenter(WindowInformation.WindowWidth / 2, astraLogo.bottomLeftY + 12);
	exitLogo.print();
	//std::cout << "exitlogocenterX:" << exitLogo.getCenterY() << std::endl;
	updateinformation();
}
void mainpage::cls(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD cCharsWritten;
	COORD coordScreen = { 0, 0 };    // ����̨��Ļ���Ͻǵ�����
	DWORD dwConSize;

	// ��ȡ����̨��ǰ����Ϣ
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		return;
	}

	// ���û�������С�뵱ǰ���ڴ�Сһ��
	COORD newSize;
	newSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	newSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	if (!SetConsoleScreenBufferSize(hConsole, newSize)) {
		// ����޷����û�������С����������Ϊ�µĳߴ�ȵ�ǰ�������ߴ�С
		std::cerr << "Error setting buffer size.\n";
	}
	// �������̨���������ַ���
	dwConSize = newSize.X * newSize.Y;

	// ������̨��������ȫ������
	if (!FillConsoleOutputCharacter(
		hConsole,         // Handle to console screen buffer 
		(TCHAR)' ',      // Character to write to the buffer
		dwConSize,        // Number of cells to write
		coordScreen,      // Coordinates of first cell
		&cCharsWritten))  // Receive number of characters written
	{
		return;
	}

	// ������ƶ�������̨���Ͻ�
	if (!SetConsoleCursorPosition(hConsole, coordScreen)) {
		return;
	}
}
void mainpage::initializeUI() {
	astraLogo.setCenter(WindowInformation.WindowWidth / 2, WindowInformation.WindowHeight / 2);
	astraLogo.print();
	//std::cout << "astralogocenterX:" << astraLogo.getCenterY() << std::endl;
	startLogo.setCenter(WindowInformation.WindowWidth / 2, astraLogo.bottomLeftY + 3);
	startLogo.print();
	//std::cout << "startlogocenterX:" << startLogo.getCenterY() << std::endl;
	continueLogo.setCenter(WindowInformation.WindowWidth / 2, astraLogo.bottomLeftY + 6);
	continueLogo.print();
	//std::cout << "continuelogocenterX:" << continueLogo.getCenterY() << std::endl;
	exitLogo.setCenter(WindowInformation.WindowWidth / 2, astraLogo.bottomLeftY + 9);
	exitLogo.print();
	//std::cout << "exitlogocenterX:" << exitLogo.getCenterY() << std::endl;
	updateinformation();
}
void mainpage::detectWindowChange()
{
	int windowWidth = WindowInformation.WindowWidth;
	int windowHeight = WindowInformation.WindowHeight;
	while (true) {
		WindowInformation.getConsoleSize();
		if (windowWidth != WindowInformation.WindowWidth || windowHeight != WindowInformation.WindowHeight) {
			windowWidth = WindowInformation.WindowWidth;
			windowHeight = WindowInformation.WindowHeight;
			updateUI();
			//std::cout << "Window size changed to " << windowWidth << "x" << windowHeight << std::endl;
		}
		if (thread_information == 1)
		{
			break;
		}
	}
}
mainpage::~mainpage()
{
	system("cls");
}

void mainpage::detect_MouseEvent()
{
	while (true) {
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
					if (pos.X >= startLogoInformation.topleftX && pos.X <= startLogoInformation.toprightX &&
						pos.Y >= startLogoInformation.topleftY && pos.Y <= startLogoInformation.bottomleftY) {
						if (startLogo.color != 6)
						{
							startLogo.print(6);
						}	
					}
					else {
						if (startLogo.color != 7)
						{
							startLogo.print(7);
						}
					}
					if (pos.X >= continueLogoInformation.topleftX && pos.X <= continueLogoInformation.toprightX &&
						pos.Y >= continueLogoInformation.topleftY && pos.Y <= continueLogoInformation.bottomleftY) {
						if (continueLogo.color != 6)
						{
							continueLogo.print(6);
						}
					}
					else {
						if (continueLogo.color != 7)
						{
							continueLogo.print(7);
						}
					}
					if (pos.X >= exitLogoInformation.topleftX && pos.X <= exitLogoInformation.toprightX &&
						pos.Y >= exitLogoInformation.topleftY && pos.Y <= exitLogoInformation.bottomleftY) {
						if (exitLogo.color != 6)
						{
							exitLogo.print(6);
						}
					}
					else {
						if (exitLogo.color != 7)
						{
							exitLogo.print(7);
						}
					}
				}
				if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
					COORD pos = mer.dwMousePosition; // ֱ��ʹ�ÿ���̨������λ�ã���ת��Ϊ�ͻ�������
					if (pos.X >= startLogoInformation.topleftX && pos.X <= startLogoInformation.toprightX &&
						pos.Y >= startLogoInformation.topleftY && pos.Y <= startLogoInformation.bottomleftY) {
						astraEngine->Mainpage_clicknewgamebotton();
					}
					if (pos.X >= continueLogoInformation.topleftX && pos.X <= continueLogoInformation.toprightX &&
						pos.Y >= continueLogoInformation.topleftY && pos.Y <= continueLogoInformation.bottomleftY) {
						astraEngine->Mainpage_clickcontinuebotton();
					}
					if (pos.X >= exitLogoInformation.topleftX && pos.X <= exitLogoInformation.toprightX &&
						pos.Y >= exitLogoInformation.topleftY && pos.Y <= exitLogoInformation.bottomleftY) {
						std::cout << "Exit Logo Clicked" << std::endl;
						astraEngine->Mainpage_clickexitbotton();
						break; // ֻ�����ڲ�ѭ��
					}
				}
			}
		}
		if (thread_information == 1) {
			break; // ȷ�����������ѭ��
		}
	}
}

//������Ϣ
void mainpage::updateinformation()
{
	//������Ϣ
	astraLogoInformation.topleftX = astraLogo.topLeftX;
	astraLogoInformation.topleftY = astraLogo.topLeftY;
	astraLogoInformation.toprightX = astraLogo.topRightX;
	astraLogoInformation.toprightY = astraLogo.topRightY;
	astraLogoInformation.bottomleftX = astraLogo.bottomLeftX;
	astraLogoInformation.bottomleftY = astraLogo.bottomLeftY;
	astraLogoInformation.bottomrightX = astraLogo.bottomRightX;
	astraLogoInformation.bottomrightY = astraLogo.bottomRightY;
	//������������Ϣ
	startLogoInformation.topleftX = startLogo.topLeftX;
	startLogoInformation.topleftY = startLogo.topLeftY;
	startLogoInformation.toprightX = startLogo.topRightX;
	startLogoInformation.toprightY = startLogo.topRightY;
	startLogoInformation.bottomleftX = startLogo.bottomLeftX;
	startLogoInformation.bottomleftY = startLogo.bottomLeftY;
	startLogoInformation.bottomrightX = startLogo.bottomRightX;
	startLogoInformation.bottomrightY = startLogo.bottomRightY;
	//������������Ϣ
	exitLogoInformation.topleftX = exitLogo.topLeftX;
	exitLogoInformation.topleftY = exitLogo.topLeftY;
	exitLogoInformation.toprightX = exitLogo.topRightX;
	exitLogoInformation.toprightY = exitLogo.topRightY;
	exitLogoInformation.bottomleftX = exitLogo.bottomLeftX;
	exitLogoInformation.bottomleftY = exitLogo.bottomLeftY;
	exitLogoInformation.bottomrightX = exitLogo.bottomRightX;
	exitLogoInformation.bottomrightY = exitLogo.bottomRightY;
	//������������Ϣ
	continueLogoInformation.topleftX = continueLogo.topLeftX;
	continueLogoInformation.topleftY = continueLogo.topLeftY;
	continueLogoInformation.toprightX = continueLogo.topRightX;
	continueLogoInformation.toprightY = continueLogo.topRightY;
	continueLogoInformation.bottomleftX = continueLogo.bottomLeftX;
	continueLogoInformation.bottomleftY = continueLogo.bottomLeftY;
	continueLogoInformation.bottomrightX = continueLogo.bottomRightX;
	continueLogoInformation.bottomrightY = continueLogo.bottomRightY;
	//���½���
}
//������Ϣ
