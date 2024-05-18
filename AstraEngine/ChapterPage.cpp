#include "ChapterPage.h"

void ChapterPage::startChapterPage(std::string ChapterString)
{
	this->message = ChapterString;
	thread_information = 0;
	WindowInformation.getConsoleSize();
	updateUI();
	std::thread detectWindowChangeThread(&ChapterPage::detectWindowChange, this);
	detectWindowChangeThread.detach();
	std::thread detectMouseEventThread(&ChapterPage::detectMouseEvent, this);
	detectMouseEventThread.join();
}

void ChapterPage::updateUI()
{
	cls();
	// 获取控制台窗口句柄
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// 获取屏幕缓冲区信息
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	// 计算屏幕中心位置
	int screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int screenHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	int x = (screenWidth - message.length()) / 2;
	int y = screenHeight / 2;

	// 设置光标位置
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(hConsole, pos);

	// 输出消息
	std::cout << message;
}

void ChapterPage::cls()
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

void ChapterPage::detectMouseEvent()
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
					if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
						thread_information = 1;
						return;
					}
				}
			}
		}
		if (thread_information == 1) {
			return; // 确保能跳出外层循环
		}
	}
}

void ChapterPage::detectWindowChange()
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
