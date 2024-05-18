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

	void initialize_file_data();//��ʼ���ļ�����
	std::streampos readFromMark(const std::string& mark);//�ӱ�Ǵ���ȡ
	void setfilename(const std::string& filename);//�����ļ���

	void readcurrentline();//�����ļ�
	std::streampos getcurrentposition() { return currentposition; }
	void setcurrentposition(std::streampos position) { currentposition = position; }
private:

	std::string filename;//�ļ���

	std::unordered_map<std::string, std::streampos> markersofchapter;//�����½ڱ��

	std::streampos currentposition;//��ǰλ��
	AstraEngine* astraEngine;
protected:

};