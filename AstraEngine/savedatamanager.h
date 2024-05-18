#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <chrono>
#include <iostream>
class AstraEngine;
class savedata {
public:
	//������Ϸʱ��ı���
	std::string currentTime;
	std::time_t now_time;
	//���浱ǰ����Ϸ����
	std::string current_image_path;
	std::string current_text;
	std::streampos current_mark;
	//������ʷѡ��
	std::string historychoice;
	//չʾ��Ԥ���ַ���
	std::string preview;
	std::string serialize() const {//���л�����
		std::ostringstream oss;
		oss << "Current Time: " << currentTime << "\n";
		oss << "Now Time: " << now_time << "\n";
		oss << "Image Path: " << current_image_path << "\n";
		oss << "Text: " << current_text << "\n";
		oss << "Mark: " << static_cast<long long>(current_mark) << "\n";
		oss << "History Choice: " << historychoice << "\n";
		oss << "Preview: " << preview << "\n";
		return oss.str();
	}
};
class savedatamanager {
public:
	savedatamanager(AstraEngine* astraengine);
	void newgame();
	std::vector<int> savedatalist = { 0,0,0,0,0 };
	void UpdateTime();

	void setsavefilename(const std::string& filename);
	void setloadfilename(const std::string& filename);

	void savefile(int datanum);
	void update_historychoice(std::string new_choice);
	std::string get_historychoice();
	void update_tmp_data();

	void readsavefile(int datanum);
	void update_gamepage();
	std::string get_preview(int datanum);
	savedata savedata1;
	savedata savedata2;
	savedata savedata3;
	savedata tmp_savedata;
private:
	void initializesavefile();
	void readsavedatalist();
	std::string save_file_name;
	std::string save_file_path;
	std::string save_file_directory;

	std::string load_file_name;
	std::string load_file_path;
	std::string load_file_directory;

	AstraEngine* astraEngine;
};