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

    // ���һ��string��Ա���洢Ҫ��ʾ������
    std::string displayText;

    // �������
    void clearText() {
        art = blankart;
        displayText.clear();  // ͬʱ���displayText����
    }

    // ����Ҫ��ʾ������
    void setText(const std::string& text) {
        displayText = text;
        insertText(displayText);  // ����insertText��������ʾ
    }

    // ��Logo������ʾ����
    void insertText(const std::string& text) {
        size_t centerLineIndex = 2; // �м�������
        int lineWidth = 62; // �ı��п��ÿ�� (64 - 2)

        int textWidth = stringDisplayWidth(text);
        std::string centeredText;

        if (textWidth > lineWidth) {
            // �����ı��������������򵥽ضϴ���
            centeredText = text.substr(0, lineWidth / 2) + "..."; // ���ʡ�Ժ�
            // ���¼�����ȷ��ʡ�Ժź��Ⱥ���
            while (stringDisplayWidth(centeredText) > lineWidth) {
                centeredText = centeredText.substr(0, centeredText.size() - 4) + "...";
            }
        }
        else {
            int padding = (lineWidth - textWidth) / 2;
            centeredText = std::string(padding, ' ') + text;
        }

        // ������������ʾ��
        centeredText = "| " + centeredText + std::string(lineWidth - stringDisplayWidth(centeredText), ' ') + " |";
        art[centerLineIndex] = centeredText; // �滻�м���
    }


    std::vector<std::string> blankart = {
        "+--------------------------------------------------------------+",
        "|                                                              |",
        "|                                                              |",
        "|                                                              |",
        "+--------------------------------------------------------------+"
    };
    // �����ַ�������ʾ��ȣ����������ַ�ռ����λ�ã�
    int stringDisplayWidth(const std::string& text) {
        int width = 0;
        for (size_t i = 0; i < text.length(); ++i) {
            if ((unsigned char)text[i] >= 128) {  // �����ASCII�ַ�Ϊ����
                width += 2; // �����ַ����
                if ((unsigned char)text[i] < 224) ++i; // ����˫�ֽڱ���(��GBK)
                else if ((unsigned char)text[i] < 240) i += 2; // �������ֽڱ���(��UTF-8�е�����)
                else i += 3; // �������ֽڱ���
            }
            else {
                width += 1; // Ӣ���ַ����
            }
        }
        return width+2;
    }
    // ��ӡ��ǰ����Ʒ״̬
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