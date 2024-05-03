#include "filemanager.h"
#include <fstream>
void filemanager::initialize_file_data()
{
	std::string fileroad;
	std::cout <<"输入文件名";
	std::cin >> fileroad;
	std::ifstream file(fileroad);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << fileroad << std::endl;
		return; // 错误返回
	}
	std::string line;
	std::string searchText = "Chapter";
	std::streampos position;
	while (getline(file, line)) {  // 读取
		if (line.substr(0, searchText.length()) == searchText) {
			markers[line] = position;
		}
	}
	file.close();
}
void filemanager::readFromMark(const std::string& mark) {
	std::string filename;
	std::cin >> filename;
	std::ifstream file(filename);
	if (markers.find(mark) == markers.end()) {
		std::cerr << "maybe" << std::endl;
		return;
	}
	file.seekg(markers[mark]);
	std::string line;
	std::getline(file, line);
	std::cout << "下一行 " << mark << line << std::endl;

	file.close();
}
void filemanager::createchapterdata()
{
}

