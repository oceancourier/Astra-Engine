#include "Ascii_image.h"
#include "AsciiArtResource.h"
#include <filesystem>

int Ascii_image::pixelToGray(COLORREF color) {
	int red = GetRValue(color);
	int green = GetGValue(color);
	int blue = GetBValue(color);
	return static_cast<int>(red * 0.299 + green * 0.587 + blue * 0.114);
}

std::vector<std::vector<COLORREF>> Ascii_image::readBMP(std::string filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        return {}; // Return an empty vector if the file cannot be opened
    }

    BMPHeader header;
    BMPInfoHeader infoHeader;

    file.read((char*)&header, sizeof(BMPHeader));
    file.read((char*)&infoHeader, sizeof(BMPInfoHeader));

    if (header.header[0] != 'B' || header.header[1] != 'M' || infoHeader.bitCount != 24) {
        return {}; // Return an empty vector for invalid or corrupt BMP files
    }

    int width = infoHeader.width;
    int height = infoHeader.height;
    std::vector<std::vector<COLORREF>> pixels(height, std::vector<COLORREF>(width));

    file.seekg(header.offset, std::ios::beg);
    int padSize = (4 - (width * 3) % 4) % 4;

    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            unsigned char r, g, b;
            file.read((char*)&b, 1);
            file.read((char*)&g, 1);
            file.read((char*)&r, 1);
            pixels[y][x] = RGB(r, g, b);
        }
        file.ignore(padSize);
    }

    file.close();
    return pixels;
}


std::vector<std::vector<COLORREF>> Ascii_image::resizeBMP(std::vector<std::vector<COLORREF>>& originalPixels, int newWidth, int newHeight) {
	int oldWidth = originalPixels[0].size();
	int oldHeight = originalPixels.size();
	std::vector<std::vector<COLORREF>> resizedPixels(newHeight, std::vector<COLORREF>(newWidth));

	for (int y = 0; y < newHeight; y++) {
		for (int x = 0; x < newWidth; x++) {
			int srcX = x * oldWidth / newWidth;
			int srcY = y * oldHeight / newHeight;
			resizedPixels[y][x] = originalPixels[srcY][srcX];
		}
	}

	return resizedPixels;
}

char Ascii_image::grayToChar(int gray) {
	int scale = 255 / (strlen(GRAY_SCALE) - 1);
	return GRAY_SCALE[gray / scale];
}

//void Ascii_image::UpdateAsciiVector()
//{
//    std::string line;
//    auto originalPixels = readBMP(filename);
//    auto resizedPixels = resizeBMP(originalPixels, newWidth, newHeight);
//    art.clear(); // Clear the existing art vector
//
//    for (int y = 0; y < newHeight; y++) {
//        for (int x = 0; x < newWidth; x++) {
//            int gray = pixelToGray(resizedPixels[y][x]);
//            line += grayToChar(gray);
//        }
//        art.push_back(line);
//        line.clear();
//    }
//}

void Ascii_image:: gotoxy(int x, int y) {
	COORD coord{};
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Ascii_image::setFilename(std::string filename)
{
	this->filename = filename;
}

void Ascii_image::print(int color) {
    auto pixels = readBMP(this->filename); // Attempt to read the BMP file
    if (pixels.empty()) { // Check if the pixels vector is empty (error case)
        ImageNotLoadedLogo tmpimage;
        tmpimage.centerX = centerX;
        tmpimage.centerY = centerY;
        tmpimage.print(); // Print the error image
        return; // Exit the function after handling the error
    }

    auto resizedPixels = resizeBMP(pixels, newWidth, newHeight);
    art.clear(); // Clear the existing art vector

    for (int y = 0; y < newHeight; y++) {
        std::string line;
        for (int x = 0; x < newWidth; x++) {
            int gray = pixelToGray(resizedPixels[y][x]);
            line += grayToChar(gray);
        }
        art.push_back(line);
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int startX = centerX - static_cast<int>(art[0].length()) / 2;
    int startY = centerY - static_cast<int>(art.size() + 1) / 2;
    SetConsoleTextAttribute(hConsole, color);

    for (int i = 0; i < art.size(); ++i) {
        gotoxy(startX, startY + i);
        std::cout << art[i];
    }

    SetConsoleTextAttribute(hConsole, 7); // Reset console color to default
    topLeftX = centerX - static_cast<int>(art[0].length() / 2);
    topLeftY = centerY - static_cast<int>(art.size() / 2);
    topRightX = centerX + static_cast<int>(art[0].length() / 2);
    topRightY = centerY - static_cast<int>(art.size() / 2);
    bottomLeftX = centerX - static_cast<int>(art[0].length() / 2);
    bottomLeftY = centerY + static_cast<int>(art.size() / 2);
    bottomRightX = centerX + static_cast<int>(art[0].length() / 2);
    bottomRightY = centerY + static_cast<int>(art.size() / 2);
}