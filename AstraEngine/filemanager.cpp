#include "filemanager.h"
#include "AstraEngine.h"
#include <fstream>
#include <locale>
#include <codecvt>
filemanager::filemanager(AstraEngine* astraengine)
{

	astraEngine = astraengine;
	initialize_file_data();
}
void filemanager::initialize_file_data()
{
	std::ifstream file(filename);
	filename=filename;
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return; // 错误返回
	}
	currentposition = file.tellg();
	std::string line;
	std::string searchText = "Chapter";
	std::streampos position = file.tellg();
	while (getline(file, line)) {  // 读取
		if (line.substr(0, searchText.length()) == searchText) {
			markersofchapter[line] = position;
		}
		position = file.tellg();
	}
	file.close();
}
std::streampos filemanager::readFromMark(const std::string& mark) {
    if (markersofchapter.find(mark) == markersofchapter.end()) {
        return std::streampos(-1);  // 返回无效位置，因为没有找到标记
    }
    return markersofchapter[mark];  // 返回找到的标记位置
}
void filemanager::setfilename(const std::string& filename)
{
	this->filename = filename;
}

void filemanager::readcurrentline()
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return; // 错误返回
    }
    file.seekg(currentposition); // 移动到上次读取结束的位置
    std::string currentline;

    if (std::getline(file, currentline)) { // 读取一行
        currentposition = file.tellg(); // 更新读取位置
        if (currentline.starts_with("Chapter")) {
            astraEngine->Gamepage.endgamepage();
            astraEngine->ChapterPage.startChapterPage(currentline);
            astraEngine->Gamepage.startgamepage();
        }
        else if (currentline.starts_with("image")) {
            std::istringstream iss(currentline);
            std::vector<std::string> words((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
            astraEngine->updateimage(words[1]);
        }
        else if (currentline.starts_with("Choice")) {
            std::istringstream iss(currentline);
            std::vector<std::string> words((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
            astraEngine->Gamepage.endgamepage();
            std::string choice = astraEngine->Selectpage.startselectpage(words[1], words[2]);
            astraEngine->Savedatamanager.update_historychoice(choice);
            astraEngine->Gamepage.startgamepage();
        }
        else if (currentline.starts_with("Ending")) {
            std::istringstream iss(currentline);
            std::vector<std::string> words((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
			std::string choice = astraEngine->Savedatamanager.get_historychoice();
            for (size_t i = 0; i < words.size(); i++) {
                if (words[i] == choice) {
					std::string chapter = words[i + 1];
					std::streampos endingpos = readFromMark(chapter);
					if (endingpos != std::streampos(-1))
                    {
						currentposition = endingpos;
						readcurrentline();
					}
                    else
                    {
						astraEngine->updatetextbox("Ending Error");
						astraEngine->Gamepage.updateUI();
					}
                }
            }
        }
        else if (currentline.starts_with("music")) {
            std::istringstream iss(currentline);
            std::vector<std::string> words((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
            std::string normalString = words[1];  // 直接使用第二个元素，假定它总是存在
            astraEngine->AudioPlayer.stop();
			astraEngine->AudioPlayer.loadMusic(normalString);
			astraEngine->AudioPlayer.play();
        }
		else if (currentline.starts_with("End")) {
			astraEngine->Gamepage.endgamepage();
			astraEngine->Mainpage.startmainpage();
		}
        else {
            astraEngine->updatetextbox(currentline);
            astraEngine->Gamepage.updateUI();
        }
    }
    file.close(); // 关闭文件
}
