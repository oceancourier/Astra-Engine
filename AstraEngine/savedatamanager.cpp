#include "savedatamanager.h"
#include "AstraEngine.h"
savedatamanager::savedatamanager(AstraEngine *astraengine)
{
	this->astraEngine = astraengine;
	initializesavefile();
}

void savedatamanager::newgame()
{
	tmp_savedata = savedata();
	update_gamepage();
}

void savedatamanager::UpdateTime() {
    // ��ȡ��ǰʱ��
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // ʹ�� tm �ṹ��ȫ�汾
    std::tm now_tm;
    localtime_s(&now_tm, &now_time);  // ע�⣬localtime_s�Ĳ���˳����localtime��ͬ

    // ʹ�� stringstream �� put_time ��ȫ�ظ�ʽ��ʱ��
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");

    // ��ȡ��ʽ�����ַ���
    std::string currentTime = oss.str();

    // �����ǰʱ��
    std::cout << "��ǰʱ��: " << currentTime << std::endl;
}

void savedatamanager::setsavefilename(const std::string& filename)
{
	save_file_name = filename;
	save_file_directory = "save/";
	save_file_path = save_file_directory + save_file_name;
}

void savedatamanager::setloadfilename(const std::string& filename)
{
	load_file_name = filename;
	load_file_directory = "save/";
	load_file_path = load_file_directory + load_file_name;
}

void savedatamanager::savefile(int datanum) {
	update_tmp_data();
	std::string filename;
	switch (datanum) {
	case 1:
		filename = "save/savedata1.txt";
		break;
	case 2:
		filename = "save/savedata2.txt";
		break;
	case 3:
		filename = "save/savedata3.txt";
		break;
	default:
		std::cerr << "Invalid data number provided.\n";
		return;
	}

	std::ofstream saveListFile(filename);
	if (saveListFile.is_open()) {
		saveListFile << tmp_savedata.serialize();
		saveListFile.close();
	}
	else {
		std::cerr << "Failed to open file: " << filename << "\n";
	}
}

void savedatamanager::update_historychoice(std::string new_choice)
{
	tmp_savedata.historychoice += new_choice;
}

std::string savedatamanager::get_historychoice()
{
    return tmp_savedata.historychoice;
}

void savedatamanager::update_tmp_data() {
    tmp_savedata.current_mark = astraEngine->Filemanager.getcurrentposition();
    tmp_savedata.current_text = astraEngine->Gamepage.getcurrenttext();
    tmp_savedata.current_image_path = astraEngine->Gamepage.getcurrentimagepath();
    tmp_savedata.now_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    // ����ʱ���ַ���
    char buffer[26];
    if (ctime_s(buffer, sizeof(buffer), &tmp_savedata.now_time) == 0) {
        tmp_savedata.currentTime = buffer;
    }
    else {
        std::cerr << "Failed to convert time" << std::endl;
    }

    // ɾ��current_text�е����л��з�
    std::string clean_text = tmp_savedata.currentTime;
    clean_text.erase(std::remove(clean_text.begin(), clean_text.end(), '\n'), clean_text.end());

    // ����preview�ַ�����ȷ�������������з�
    tmp_savedata.preview = clean_text + " " + tmp_savedata.current_text; // ����ո�ָ�ʱ����ı�
}

void savedatamanager::readsavefile(int datanum) {
    std::string filename;
    switch (datanum) {
    case 1:
        filename = "save/savedata1.txt";
        break;
    case 2:
        filename = "save/savedata2.txt";
        break;
    case 3:
        filename = "save/savedata3.txt";
        break;
    default:
        std::cerr << "Invalid data number provided.\n";
        return;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return;
    }

    std::string line;
    while (getline(file, line)) {
        size_t pos = line.find(": ");
        if (pos == std::string::npos) continue;
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 2);

        if (key == "Current Time") {
            tmp_savedata.currentTime = value;
        }
        else if (key == "Now Time") {
            tmp_savedata.now_time = static_cast<std::time_t>(std::stoll(value));
        }
        else if (key == "Image Path") {
            tmp_savedata.current_image_path = value;
        }
        else if (key == "Text") {
            tmp_savedata.current_text = value;
        }
        else if (key == "Mark") {
            tmp_savedata.current_mark = static_cast<std::streampos>(std::stoll(value));
        }
        else if (key == "Preview") {
            tmp_savedata.preview = value;
        }
    }

	file.close();  // �ر��ļ�
}

void savedatamanager::update_gamepage()
{
	astraEngine->Gamepage.setcurrentimagepath(tmp_savedata.current_image_path);
    astraEngine->updatetextbox(tmp_savedata.current_text);
	astraEngine->Filemanager.setcurrentposition(tmp_savedata.current_mark);
}

std::string savedatamanager::get_preview(int datanum) {
    std::string filename;
    // �����ṩ�� datanum ѡ����ȷ���ļ���
    switch (datanum) {
    case 1:
        filename = "save/savedata1.txt";
        break;
    case 2:
        filename = "save/savedata2.txt";
        break;
    case 3:
        filename = "save/savedata3.txt";
        break;
    default:
        std::cerr << "Invalid data number provided.\n";
        return "";
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return "";
    }

    std::string line, preview;
    while (getline(file, line)) {
        // ֻ������ "Preview" ��ص���
        size_t pos = line.find(": ");
        if (pos == std::string::npos) continue;
        std::string key = line.substr(0, pos);
        if (key == "Preview") {
            preview = line.substr(pos + 2);
            break;  // �ҵ��󼴿�ֹͣ��ȡ
        }
    }

    file.close();  // �ر��ļ�
    return preview;  // �����ҵ��� Preview �ַ���
}

void savedatamanager::initializesavefile()
{
    // ���save�ļ����Ƿ����
    std::filesystem::path saveFolderPath = "save";
    if (!std::filesystem::exists(saveFolderPath))
    {
        // ����save�ļ���
        std::filesystem::create_directory(saveFolderPath);
    }
    readsavedatalist();
}

void savedatamanager::readsavedatalist()
{
	// ��ȡ�浵�б�
	std::ifstream saveListFile1("save/savedata1.txt");
	if (saveListFile1.is_open())
	{
		savedatalist[1]=1;
	}
    std::ifstream saveListFile2("save/savedata2.txt");
    if (saveListFile2.is_open())
    {
        savedatalist[2]=1;
    }
	std::ifstream saveListFile3("save/savedata3.txt");
	if (saveListFile3.is_open())
	{
		savedatalist[3] = 1;
	}
	//std::ofstream saveListFile("save/savedatalist.txt");
	//if (saveListFile.is_open()) {
	//	saveListFile << "SaveData1: " << savedatalist[1] << "\n";
	//	saveListFile << "SaveData2: " << savedatalist[2] << "\n";
	//	saveListFile << "SaveData3: " << savedatalist[3] << "\n";
	//	saveListFile << get_preview(1) << "\n";
	//	saveListFile.close();
	//}
	//else {
	//	std::cerr << "Failed to open file: save/savedatalist.txt\n";
	//}
}

