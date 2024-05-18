#include "gamepage.h"
#include "AstraEngine.h"
std::string gamepage::getcurrenttext()
{
	return textbox.getcurrenttext();
}
std::string gamepage::getcurrentimagepath()
{
	return Ascii_image.getfilename();
}
gamepage::gamepage(AstraEngine *astraengine) {
	this->astraEngine = astraengine;
}
void gamepage::startgamepage()
{
	updateUI();
	thread_information = 0;
	//textbox.setTextSpeed(1);

	std::thread detectMouseEventThread(&gamepage::detect_MouseEvent, this);
	detectMouseEventThread.detach();

	std::thread detectWindowChangeThread(&gamepage::detectWindowChange, this);
	detectWindowChangeThread.join();
}
void gamepage::endgamepage()
{
	thread_information = 1;
	cls();
}
void gamepage::cls()
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

void gamepage::changeimage(std::string filename)
{
	Ascii_image.setFilename(filename);
	//Ascii_image.UpdateAsciiVector();
	cls();
}
void gamepage::changetext(std::string text)
{
	textbox.setText(text);
}
void gamepage::detectWindowChange()
{
	int windowWidth = WindowInformation.WindowWidth;
	int windowHeight = WindowInformation.WindowHeight;
	while (true) {
		WindowInformation.getConsoleSize();
		if (thread_information == 0) {
			if (windowWidth != WindowInformation.WindowWidth || windowHeight != WindowInformation.WindowHeight) {
				windowWidth = WindowInformation.WindowWidth;
				windowHeight = WindowInformation.WindowHeight;
				updateUI();
				//std::cout << "Window size changed to " << windowWidth << "x" << windowHeight << std::endl;
			}
		}
		if (thread_information == 1)
		{
			return;
		}
		Sleep(100);
	}
}

void gamepage::hide_UI()
{
	thread_information = 2;
	cls();
}

void gamepage::show_UI()
{
	initializeUI();
	thread_information = 0;
}

void gamepage::initializeUI()
{
	int partWidth = WindowInformation.WindowWidth / 3;

	// ����ÿ��ͼ������ĵ㲢��ʾ
	SaveLogo.setCenter((partWidth / 2), WindowInformation.WindowHeight - 2);
	LoadLogo.setCenter((partWidth / 2) + partWidth, WindowInformation.WindowHeight - 2);
	TitleLogo.setCenter((partWidth / 2) + partWidth * 2, WindowInformation.WindowHeight - 2);
	SaveLogo.print();
	LoadLogo.print();
	TitleLogo.print();

	// ��ʾ�ı���
	textbox.setDimensions(WindowInformation.WindowWidth, 5);
	textbox.setCenter(WindowInformation.WindowWidth / 2, WindowInformation.WindowHeight - 6);
	textbox.displayFrame();
	textbox.displayText();
	if (WindowInformation.WindowWidth < Ascii_image.newWidth || WindowInformation.WindowHeight <45)
	{
		InsufficientspaceLogo.setCenter(WindowInformation.WindowWidth / 2, WindowInformation.WindowHeight / 2);
		InsufficientspaceLogo.print();
	}
	else {
		Ascii_image.setCenter(WindowInformation.WindowWidth / 2, WindowInformation.WindowHeight - 27);
		Ascii_image.print();
	}
	textbox.displayText();
}

void gamepage::updateUI()
{
	cls();
	int partWidth = WindowInformation.WindowWidth / 3;

	// ����ÿ��ͼ������ĵ㲢��ʾ
	SaveLogo.setCenter((partWidth / 2), WindowInformation.WindowHeight - 2);
	LoadLogo.setCenter((partWidth / 2) + partWidth, WindowInformation.WindowHeight - 2);
	TitleLogo.setCenter((partWidth / 2) + partWidth * 2, WindowInformation.WindowHeight - 2);
	SaveLogo.print();
	LoadLogo.print();
	TitleLogo.print();

	// ��ʾ�ı���
	textbox.setDimensions(WindowInformation.WindowWidth, 5);
	textbox.setCenter(WindowInformation.WindowWidth / 2, WindowInformation.WindowHeight - 6);
	textbox.displayFrame();

	if (WindowInformation.WindowWidth < Ascii_image.newWidth || WindowInformation.WindowHeight<54)
	{
		InsufficientspaceLogo.setCenter(WindowInformation.WindowWidth / 2, WindowInformation.WindowHeight / 2);
		InsufficientspaceLogo.print();
	}
	else {
		Ascii_image.setCenter(WindowInformation.WindowWidth / 2, WindowInformation.WindowHeight - 31);
		Ascii_image.print();
	}
	textbox.displayText();
	setCursorToBottomRight();
}
void gamepage::setCursorToBottomRight() {
	// ��ȡ����̨��������
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsoleOutput == INVALID_HANDLE_VALUE) {
		std::cerr << "Failed to get the console handle." << std::endl;
		return;
	}

	// ��ȡ��ǰ����̨���ڵ���Ϣ
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hConsoleOutput, &csbi)) {
		std::cerr << "Failed to get console screen buffer info." << std::endl;
		return;
	}

	// �������½ǵ�λ��
	COORD bottomRightPos;
	bottomRightPos.X = csbi.srWindow.Right;  // �ұ߽�
	bottomRightPos.Y = csbi.srWindow.Bottom; // �±߽�

	// ���ù��λ��
	if (!SetConsoleCursorPosition(hConsoleOutput, bottomRightPos)) {
		std::cerr << "Failed to set cursor position." << std::endl;
	}
}

void gamepage::detect_MouseEvent()
{
	while (true) {
		if (thread_information == 0) {
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
						if (pos.X >= SaveLogo.topLeftX && pos.X <= SaveLogo.topRightX &&
							pos.Y >= SaveLogo.topLeftY && pos.Y <= SaveLogo.bottomLeftY) {
							if (SaveLogo.color != 6)
							{
								SaveLogo.print(6);
							}
						}
						else {
							if (SaveLogo.color != 7)
							{
								SaveLogo.print(7);
							}
						}
						if (pos.X >= LoadLogo.topLeftX && pos.X <= LoadLogo.topRightX &&
							pos.Y >= LoadLogo.topLeftY && pos.Y <= LoadLogo.bottomLeftY) {
							if (LoadLogo.color != 6)
							{
								LoadLogo.print(6);
							}
						}
						else {
							if (LoadLogo.color != 7)
							{
								LoadLogo.print(7);
							}
						}
						if (pos.X >= TitleLogo.topLeftX && pos.X <= TitleLogo.topRightX &&
							pos.Y >= TitleLogo.topLeftY && pos.Y <= TitleLogo.bottomLeftY) {
							if (TitleLogo.color != 6)
							{
								TitleLogo.print(6);
							}
						}
						else {
							if (TitleLogo.color != 7)
							{
								TitleLogo.print(7);
							}
						}
					}
					if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
						COORD pos = mer.dwMousePosition; // ֱ��ʹ�ÿ���̨������λ�ã���ת��Ϊ�ͻ�������
						if (pos.X >= SaveLogo.topLeftX && pos.X <= SaveLogo.topRightX &&
							pos.Y >= SaveLogo.topLeftY && pos.Y <= SaveLogo.bottomLeftY) {
							astraEngine->Gamepage_clicksavebotton();
						}
						else if (pos.X >= LoadLogo.topLeftX && pos.X <= LoadLogo.topRightX &&
							pos.Y >= LoadLogo.topLeftY && pos.Y <= LoadLogo.bottomLeftY) {
							astraEngine->Gamepage_clickloadbotton();
						}
						else if (pos.X >= TitleLogo.topLeftX && pos.X <= TitleLogo.topRightX &&
							pos.Y >= TitleLogo.topLeftY && pos.Y <= TitleLogo.bottomLeftY) {
							astraEngine->Gamepage_clicktitlebotton();
						}
						else {
							astraEngine->Gamepage_clickscreen();
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