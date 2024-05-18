#pragma once
#include <iostream>
#include <fstream>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>
#include <filesystem>
class AstraEngine;
class filemanager {
public:
	filemanager(AstraEngine* astraengine);

	void initialize_file_data();//初始化文件数据
	std::streampos readFromMark(const std::string& mark);//从标记处读取
	void setfilename(const std::string& filename);//设置文件名

	void readcurrentline();//保存文件
	std::streampos getcurrentposition() { return currentposition; }
	void setcurrentposition(std::streampos position) { currentposition = position; }
private:

	std::string filename;//文件名

	std::unordered_map<std::string, std::streampos> markersofchapter;//储存章节标记

	std::streampos currentposition;//当前位置
	AstraEngine* astraEngine;
protected:

};