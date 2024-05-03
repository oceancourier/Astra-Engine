#pragma once
#pragma once
#ifndef FileManager
#define FileManager

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
class filemanager {
public:
	void initialize_file_data();
	void readFromMark(const std::string& mark);
private:
	std::string filename;
	void createchapterdata();
	std::unordered_map<std::string, std::streampos> markers;
protected:

};

#endif // FileManager