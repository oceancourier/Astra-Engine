#include "windowinformation.h"
windowinformation::windowinformation() {
	getConsoleSize();
}
void windowinformation::getConsoleSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    WindowWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    WindowHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	WindowXPosition = csbi.srWindow.Left;
	WindowYPosition = csbi.srWindow.Top;
}