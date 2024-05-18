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
	system("chcp 65001 > nul");//设置控制台编码为UTF-8
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

void AstraEngine::initializeFile()
{
	InputBox inputfilename;
	while (true) {
		inputfilename.setPrompt("请输入文件名");
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
			std::cout << "文件名错误，请重新输入\n";
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

	// 定义一个CONSOLE_FONT_INFOEX结构体来获取当前的字体设置
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);

	// 获取当前控制台的字体设置
	GetCurrentConsoleFontEx(hConsole, FALSE, &cfi);

	// 修改字体名称，这里以更改为Consolas为例
	wcscpy_s(cfi.FaceName, L"Consolas");

	// 重新设置控制台字体，只改变字体类型
	SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void AstraEngine::game_run()
{
	while (game_information == 0) {
		Sleep(100);
	}
}
