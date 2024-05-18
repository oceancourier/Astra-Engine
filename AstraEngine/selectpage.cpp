#include "selectpage.h"

selectpage::selectpage()
{
}

std::string selectpage::startselectpage(std::string choice1, std::string choice2)
{
	updateUI();
	ChoiceLogo1.insertText(choice1);
	ChoiceLogo2.insertText(choice2);
	thread_information = 0;
	updateUI();
	std::thread detectWindowChangeThread(&selectpage::detectWindowChange, this);
	detectWindowChangeThread.detach();
	std::thread detectMouseEventThread(&selectpage::detectMouseEvent, this);
	detectMouseEventThread.join();
	//�ȴ�ѡ������󷵻�
	if (choice == 1)
	{
		return choice1;
	}
	else if (choice == 2)
	{
		return choice2;
	}
}

void selectpage::cls()
{
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

void selectpage::updateUI()
{
	cls();  // ��������������
	int partWidth = WindowInformation.WindowWidth / 3;
	int windowHeight = WindowInformation.WindowHeight;
	int buttonHeight = 5; // ÿ����ť�ĸ߶�
	int spaceBetweenButtons = 2; // ��ť֮��Ŀռ�

	// �����ܸ߶ȵļ���
	int totalButtonsHeight = (buttonHeight + spaceBetweenButtons) * 2 - spaceBetweenButtons;
	int startY = (windowHeight - totalButtonsHeight) / 2;  // �����һ����ť����ʼYλ��

	int button1Y = startY;
	int button2Y = button1Y + buttonHeight + spaceBetweenButtons;

	// ���а�ť��ˮƽ����λ������Ϊ��Ļ��ȵ�һ��
	int centerX = WindowInformation.WindowWidth / 2;

	// ����ÿ��SaveDataInformationLogo������λ��
	ChoiceLogo1.setCenter(centerX, button1Y);
	ChoiceLogo2.setCenter(centerX, button2Y);

	// ��ӡÿ��logo
	ChoiceLogo1.print(7);
	ChoiceLogo2.print(7);
}

void selectpage::detectWindowChange()
{
	int windowWidth = WindowInformation.WindowWidth;
	int windowHeight = WindowInformation.WindowHeight;
	while (true) {
		if (thread_information == 0)
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

void selectpage::detectMouseEvent()
{
	while (true) {
		if (thread_information == 0)
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
						if (pos.X >= ChoiceLogo1.topLeftX && pos.X <= ChoiceLogo1.topRightX &&
							pos.Y >= ChoiceLogo1.topLeftY && pos.Y <= ChoiceLogo1.bottomLeftY) {
							if (ChoiceLogo1.color != 6)
							{
								ChoiceLogo1.print(6);
							}
						}
						else {
							if (ChoiceLogo1.color != 7)
							{
								ChoiceLogo1.print(7);
							}
						}
						if (pos.X >= ChoiceLogo2.topLeftX && pos.X <= ChoiceLogo2.topRightX &&
							pos.Y >= ChoiceLogo2.topLeftY && pos.Y <= ChoiceLogo2.bottomLeftY) {
							if (ChoiceLogo2.color != 6)
							{
								ChoiceLogo2.print(6);
							}
						}
						else {
							if (ChoiceLogo2.color != 7)
							{
								ChoiceLogo2.print(7);
							}
						}

					}
					if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
						COORD pos = mer.dwMousePosition; // ֱ��ʹ�ÿ���̨������λ�ã���ת��Ϊ�ͻ�������
						if (pos.X >= ChoiceLogo1.topLeftX && pos.X <= ChoiceLogo1.topRightX &&
							pos.Y >= ChoiceLogo1.topLeftY && pos.Y <= ChoiceLogo1.bottomLeftY) {
							ClickChoiceLogo1();
						}
						else if (pos.X >= ChoiceLogo2.topLeftX && pos.X <= ChoiceLogo2.topRightX &&
							pos.Y >= ChoiceLogo2.topLeftY && pos.Y <= ChoiceLogo2.bottomLeftY) {
							ClickChoiceLogo2();
						}
					}
				}
			}
		}
		if (thread_information == 1) {
			return; // ȷ�����������ѭ��
		}
	}
}

void selectpage::ClickChoiceLogo1()
{
	choice = 1;
	thread_information = 1;
}
void selectpage::ClickChoiceLogo2()
{
	choice = 2;
	thread_information = 1;
}