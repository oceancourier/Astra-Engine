#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <windows.h>
#include <cctype>
#include <cwctype>
class AsciiArt {
protected:
    std::vector<std::string> art;

public:
    AsciiArt() : centerX(0), centerY(0), topLeftX(0), topLeftY(0), topRightX(0), topRightY(0), bottomLeftX(0), bottomLeftY(0), bottomRightX(0), bottomRightY(0),color(7) {}

    virtual ~AsciiArt() {}

    void setCenter(int x, int y) {
        centerX = x;
        centerY = y;
    }

    int getCenterX() const { return centerX; }
    int getCenterY() const { return centerY; }

    std::pair<int, int> getTopLeft() const {
        return { topLeftX, topLeftY };
    }

    std::pair<int, int> getTopRight() const {
        return { topRightX, topRightY };
    }

    std::pair<int, int> getBottomLeft() const {
        return { bottomLeftX, bottomLeftY };
    }

    std::pair<int, int> getBottomRight() const {
        return { bottomRightX, bottomRightY };
    }

    virtual void print(int color=7) {
        int startX = centerX - static_cast<int>(art[0].length()) / 2;
        int startY = centerY - static_cast<int>(art.size()) / 2;

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);

        for (int i = 0; i < art.size(); ++i) {
            gotoxy(startX, startY + i);
            std::cout << art[i];
        }

        SetConsoleTextAttribute(hConsole, 7); // Reset console color to default

        // Calculate and update the coordinates
        topLeftX = centerX - static_cast<int>(art[0].length() / 2);
        topLeftY = centerY - static_cast<int>(art.size() / 2);
        topRightX = centerX + static_cast<int>(art[0].length() / 2);
        topRightY = centerY - static_cast<int>(art.size() / 2);
        bottomLeftX = centerX - static_cast<int>(art[0].length() / 2);
        bottomLeftY = centerY + static_cast<int>(art.size() / 2);
        bottomRightX = centerX + static_cast<int>(art[0].length() / 2);
        bottomRightY = centerY + static_cast<int>(art.size() / 2);
		this->color = color;
    }

    static void gotoxy(int x, int y) {
        COORD coord{};
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    int centerX;
    int centerY;
    int topLeftX;
    int topLeftY;
    int topRightX;
    int topRightY;
    int bottomLeftX;
    int bottomLeftY;
    int bottomRightX;
    int bottomRightY;
    int color;
};

class AstraLogo : public AsciiArt {
public:
    AstraLogo() {
        art = {
        ":::'###:::::'######::'########:'########:::::'###:::::::'########:'##::: ##::'######:::'####:'##::: ##:'########:",
        ":'##  ##:::'##... ##:... ##..:: ##.... ##:::'## ##:::::: ##.....:: ###:: ##:'##... ##::. ##:: ###:: ##: ##.....::",
        ":'##:. ##:: ##:::..::::: ##:::: ##:::: ##::'##:. ##::::: ##::::::: ####: ##: ##:::..:::: ##:: ####: ##: ##:::::::",
        "'##:::. ##:. ######::::: ##:::: ########::'##:::. ##:::: ######::: ## ## ##: ##::'####:: ##:: ## ## ##: ######:::",
        " #########::..... ##:::: ##:::: ##.. ##::: #########:::: ##...:::: ##. ####: ##::: ##::: ##:: ##. ####: ##...::::",
        " ##.... ##:'##::: ##:::: ##:::: ##::. ##:: ##.... ##:::: ##::::::: ##:. ###: ##::: ##::: ##:: ##:. ###: ##:::::::",
        " ##:::: ##:. ######::::: ##:::: ##:::. ##: ##:::: ##:::: ########: ##::. ##:. ######:::'####: ##::. ##: ########:",
        "..:::::..:::......::::::..:::::..:::::..::..:::::..:::::........::..::::..:::......::::....::..::::..::........::"
        };
    }
};

class StartLogo : public AsciiArt {
public:
    StartLogo() {
        art = {
        "+------------+",
        "| Start Game |",
        "+------------+"
        };
    }
};

class ExitLogo : public AsciiArt {
public:
    ExitLogo() {
        art = {
        "+------------+",
        "| Exit  Game |",
        "+------------+"
        };
    }
};

class ContinueLogo : public AsciiArt {
public:
    ContinueLogo() {
        art = {
        "+------------+",
        "|  Continue  |",
        "+------------+"
        };
    }
};
class SaveLogo : public AsciiArt {
public:
    SaveLogo() {
        art = {
        "+------------+",
        "|    Save    |",
        "+------------+"
        };
    }
};
class LoadLogo : public AsciiArt {
public:
    LoadLogo() {
        art = {
        "+------------+",
        "|    Load    |",
        "+------------+"
        };
    }
};
class TitleLogo : public AsciiArt {
public:
    TitleLogo() {
        art = {
        "+------------+",
        "|  MainMenu  |",
        "+------------+"
        };
    }
};
class InsufficientspaceLogo : public AsciiArt {
public:
    InsufficientspaceLogo() {
        art = {
        "+----------------------------------+",
        "|                                  |",
        "|   Insufficient space for image   |",
        "|                                  |",
        "+----------------------------------+"
        };
    }
};
class ImageNotLoadedLogo : public AsciiArt {
public:
    ImageNotLoadedLogo() {
        art = {
        "+----------------------------------+",
        "|                                  |",
        "|         Image Not Loaded         |",
        "|                                  |",
        "+----------------------------------+"
        };
    }
};
class SaveDataInformationLogo : public AsciiArt {
public:
    SaveDataInformationLogo() {
        art = {
            "+--------------------------------------------------------------+",
            "|                                                              |",
            "|                                                              |",
            "|                                                              |",
            "+--------------------------------------------------------------+"
        };
    }

    // 添加一个string成员来存储要显示的文字
    std::string displayText;

    // 清除文字
    void clearText() {
        art = blankart;
        displayText.clear();  // 同时清除displayText内容
    }

    // 设置要显示的文字
    void setText(const std::string& text) {
        displayText = text;
        insertText(displayText);  // 调用insertText来更新显示
    }

    // 在Logo中心显示文字
    void insertText(const std::string& text) {
        size_t centerLineIndex = 2; // 中间行索引
        int lineWidth = 62; // 文本行可用宽度 (64 - 2)

        int textWidth = stringDisplayWidth(text);
        std::string centeredText;

        if (textWidth > lineWidth) {
            // 处理文本超出宽度情况，简单截断处理
            centeredText = text.substr(0, lineWidth / 2) + "..."; // 添加省略号
            // 重新计算以确保省略号后宽度合适
            while (stringDisplayWidth(centeredText) > lineWidth) {
                centeredText = centeredText.substr(0, centeredText.size() - 4) + "...";
            }
        }
        else {
            int padding = (lineWidth - textWidth) / 2;
            centeredText = std::string(padding, ' ') + text;
        }

        // 构建完整的显示行
        centeredText = "| " + centeredText + std::string(lineWidth - stringDisplayWidth(centeredText), ' ') + " |";
        art[centerLineIndex] = centeredText; // 替换中间行
    }


    std::vector<std::string> blankart = {
        "+--------------------------------------------------------------+",
        "|                                                              |",
        "|                                                              |",
        "|                                                              |",
        "+--------------------------------------------------------------+"
    };
    // 计算字符串的显示宽度（考虑中文字符占两个位置）
    int stringDisplayWidth(const std::string& text) {
        int width = 0;
        for (size_t i = 0; i < text.length(); ++i) {
            if ((unsigned char)text[i] >= 128) {  // 假设非ASCII字符为中文
                width += 2; // 中文字符宽度
                if ((unsigned char)text[i] < 224) ++i; // 对于双字节编码(如GBK)
                else if ((unsigned char)text[i] < 240) i += 2; // 对于三字节编码(如UTF-8中的中文)
                else i += 3; // 对于四字节编码
            }
            else {
                width += 1; // 英文字符宽度
            }
        }
        return width+2;
    }
    // 打印当前艺术品状态
};

class BackLogo : public AsciiArt {
public:
    BackLogo() {
        art = {
        "+------------+",
        "|    Back    |",
        "+------------+"
        };
    }
};