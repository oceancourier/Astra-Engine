#include "InputBox.h"

InputBox::InputBox(int w, int h) : width(w), height(h), content(""), prompt("Enter your input:") {}

void InputBox::displayBox() {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(hStdout, &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    position.X = (consoleWidth - width) / 2;
    position.Y = (consoleHeight - height) / 2 - 1; // Adjust for the prompt above the box

    // Display prompt above the box
    SetConsoleCursorPosition(hStdout, { position.X, position.Y });
    std::cout << prompt;

    // Draw the top border of the box
    position.Y += 1;
    SetConsoleCursorPosition(hStdout, position);
    std::cout << '+' << std::string(width - 2, '-') << '+';

    // Draw the input area (middle of the box)
    for (int i = 1; i < height - 1; ++i) {
        position.Y += 1;
        SetConsoleCursorPosition(hStdout, position);
        std::cout << '|' << std::string(width - 2, ' ') << '|';
    }

    // Draw the bottom border of the box
    position.Y += 1;
    SetConsoleCursorPosition(hStdout, position);
    std::cout << '+' << std::string(width - 2, '-') << '+';
}

void InputBox::getInput() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &csbi);

    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    // Calculate the position just inside the box's upper left corner
    COORD inputPosition = {
        (SHORT)((consoleWidth - width) / 2 + 1),
        (SHORT)((csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2 - height / 2 + 1)
    };

    SetConsoleCursorPosition(hStdout, inputPosition);
    std::getline(std::cin, content);
}

void InputBox::setPrompt(const std::string& newPrompt) {
    prompt = newPrompt;
}

const std::string& InputBox::getContent() const {
    return content;
}

const std::string& InputBox::getPrompt() const {
    return prompt;
}
