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
	//等待选择结束后返回
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

void selectpage::updateUI()
{
	cls();  // 假设是清屏函数
	int partWidth = WindowInformation.WindowWidth / 3;
	int windowHeight = WindowInformation.WindowHeight;
	int buttonHeight = 5; // 每个按钮的高度
	int spaceBetweenButtons = 2; // 按钮之间的空间

	// 更新总高度的计算
	int totalButtonsHeight = (buttonHeight + spaceBetweenButtons) * 2 - spaceBetweenButtons;
	int startY = (windowHeight - totalButtonsHeight) / 2;  // 计算第一个按钮的起始Y位置

	int button1Y = startY;
	int button2Y = button1Y + buttonHeight + spaceBetweenButtons;

	// 所有按钮的水平中心位置设置为屏幕宽度的一半
	int centerX = WindowInformation.WindowWidth / 2;

	// 设置每个SaveDataInformationLogo的中心位置
	ChoiceLogo1.setCenter(centerX, button1Y);
	ChoiceLogo2.setCenter(centerX, button2Y);

	// 打印每个logo
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
						COORD pos = mer.dwMousePosition; // 直接使用控制台的坐标位置，不转换为客户端坐标
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
			return; // 确保能跳出外层循环
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