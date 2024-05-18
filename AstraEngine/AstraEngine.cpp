#include "AstraEngine.h"

AstraEngine::AstraEngine() 
	: Savedatamanager{this},
	Filemanager{this},
	Gamepage{ this },
	Mainpage{ this },
	Save_loadpage{ this , &Savedatamanager}
{
	cls();
	initializeFile();
	system("chcp 65001 > nul");//���ÿ���̨����ΪUTF-8
	//setconsole();
}

void AstraEngine::startgame()
{
	Mainpage.startmainpage();
	thread_local std::thread game_run_thread(&AstraEngine::game_run, this);
	game_run_thread.join();
}
void AstraEngine::cls()
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

void AstraEngine::initializeFile()
{
	InputBox inputfilename;
	while (true) {
		inputfilename.setPrompt("�������ļ���");
		inputfilename.displayBox();
		inputfilename.getInput();
		std::filesystem::path exepath = std::filesystem::current_path();
		std::string filename = inputfilename.getContent();
		std::filesystem::path filepath = exepath / filename;
		if (std::filesystem::exists(filepath)) {
			Filemanager.setfilename(inputfilename.getContent());
			Filemanager.initialize_file_data();
			cls();
			break;
		}
		else {
			std::cout << "�ļ�����������������\n";
		}
	}

}

void AstraEngine::Mainpage_clicknewgamebotton()
{
	Mainpage.endmainpage();
	Savedatamanager.newgame();
	Gamepage.startgamepage();
}

void AstraEngine::Mainpage_clickcontinuebotton()
{
	Mainpage.endmainpage();
	Save_loadpage.startsave_loadpage(1,2);
}

void AstraEngine::Mainpage_clickexitbotton()
{
	Mainpage.endmainpage();
	this->game_information = 1;
}

void AstraEngine::startgamepage()
{
	Mainpage.endmainpage();
	Gamepage.show_UI();
}

void AstraEngine::Gamepage_clicksavebotton()
{
	Gamepage.endgamepage();
	Save_loadpage.startsave_loadpage(2, 1);
}

void AstraEngine::Gamepage_clickloadbotton()
{
	Gamepage.endgamepage();
	Save_loadpage.startsave_loadpage(2, 2);
}

void AstraEngine::Gamepage_clicktitlebotton()
{
	Gamepage.endgamepage();
	Mainpage.startmainpage();
}

void AstraEngine::Gamepage_clickscreen()
{
	Filemanager.readcurrentline();
}

void AstraEngine::updateimage(const std::string& imagepath)
{
	Gamepage.changeimage(imagepath);
}

void AstraEngine::updatetextbox(const std::string& text)
{
	Gamepage.changetext(text);
}




void AstraEngine::setconsole()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// ����һ��CONSOLE_FONT_INFOEX�ṹ������ȡ��ǰ����������
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);

	// ��ȡ��ǰ����̨����������
	GetCurrentConsoleFontEx(hConsole, FALSE, &cfi);

	// �޸��������ƣ������Ը���ΪConsolasΪ��
	wcscpy_s(cfi.FaceName, L"Consolas");

	// �������ÿ���̨���壬ֻ�ı���������
	SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void AstraEngine::game_run()
{
	while (game_information == 0) {
		Sleep(100);
	}
}
