#include "textbox.h"

textbox::textbox(int w, int h) : width(w), height(h), centerX(0), centerY(0), text(""), textSpeed(100) {}

void textbox::setDimensions(int w, int h) {
    width = w;
    height = h;
}

void textbox::setCenter(int x, int y) {
    centerX = x;
    centerY = y;
}

void textbox::setText(const std::string& newText) {
    text = newText;
    generateLines();
}

void textbox::setTextSpeed(int speed) {
    textSpeed = speed;
}

void textbox::displayFrame() const {
    int startY = centerY - height / 2;
    int startX = centerX - width / 2;

    setCursorPosition(startX, startY);
    std::cout << "+" << std::string(width - 2, '-') << "+";
    for (int i = 1; i < height - 1; ++i) {
        setCursorPosition(startX, startY + i);
        std::cout << "|" << std::string(width - 2, ' ') << "|";
    }
    setCursorPosition(startX, startY + height - 1);
    std::cout << "+" << std::string(width - 2, '-') << "+";
}

void textbox::displayText() {
    std::thread t([this]() {
        animateText();
        });
    t.join();
}

void textbox::generateLines() {
    lines.clear();
    std::string currentLine;
    int lineLength = 0;

    for (char ch : text) {
        if (ch == '\n' || lineLength == width - 2) {
            lines.push_back(currentLine);
            currentLine.clear();
            lineLength = 0;
            if (ch == '\n') continue;
        }
        currentLine += ch;
        lineLength++;
    }

    if (!currentLine.empty()) {
        lines.push_back(currentLine);
    }
}

void textbox::animateText() const {
    int startY = centerY - height / 2 + 1;
    int startX = centerX - width / 2 + 1;

    for (const auto& line : lines) {
        setCursorPosition(startX, startY++);
        for (char ch : line) {
            std::cout << ch;
            std::this_thread::sleep_for(std::chrono::microseconds(textSpeed));  // 控制文本显示速度
        }
        if (startY > centerY + height / 2 - 1)
            break;
    }
}

void textbox::setCursorPosition(int x, int y) const {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(hStdout, position);
}
void textbox::updateposition(){
	topleftx = centerX - width / 2;
	toplefty = centerY - height / 2;
	bottomrightx = centerX + width / 2;
	bottomrighty = centerY + height / 2;
}

std::string textbox::getcurrenttext()
{
    return text;
}
