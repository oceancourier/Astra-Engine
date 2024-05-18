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
    // 获取当前时间
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // 使用 tm 结构安全版本
    std::tm now_tm;
    localtime_s(&now_tm, &now_time);  // 注意，localtime_s的参数顺序与localtime不同

    // 使用 stringstream 和 put_time 安全地格式化时间
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");

    // 获取格式化的字符串
    std::string currentTime = oss.str();

    // 输出当前时间
    std::cout << "当前时间: " << currentTime << std::endl;
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

    // 创建时间字符串
    char buffer[26];
    if (ctime_s(buffer, sizeof(buffer), &tmp_savedata.now_time) == 0) {
        tmp_savedata.currentTime = buffer;
    }
    else {
        std::cerr << "Failed to convert time" << std::endl;
    }

    // 删除current_text中的所有换行符
    std::string clean_text = tmp_savedata.currentTime;
    clean_text.erase(std::remove(clean_text.begin(), clean_text.end(), '\n'), clean_text.end());

    // 创建preview字符串，确保它不包含换行符
    tmp_savedata.preview = clean_text + " " + tmp_savedata.current_text; // 加入空格分隔时间和文本
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

	file.close();  // 关闭文件
}

void savedatamanager::update_gamepage()
{
	astraEngine->Gamepage.setcurrentimagepath(tmp_savedata.current_image_path);
    astraEngine->updatetextbox(tmp_savedata.current_text);
	astraEngine->Filemanager.setcurrentposition(tmp_savedata.current_mark);
}

std::string savedatamanager::get_preview(int datanum) {
    std::string filename;
    // 根据提供的 datanum 选择正确的文件名
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
        // 只查找与 "Preview" 相关的行
        size_t pos = line.find(": ");
        if (pos == std::string::npos) continue;
        std::string key = line.substr(0, pos);
        if (key == "Preview") {
            preview = line.substr(pos + 2);
            break;  // 找到后即可停止读取
        }
    }

    file.close();  // 关闭文件
    return preview;  // 返回找到的 Preview 字符串
}

void savedatamanager::initializesavefile()
{
    // 检查save文件夹是否存在
    std::filesystem::path saveFolderPath = "save";
    if (!std::filesystem::exists(saveFolderPath))
    {
        // 创建save文件夹
        std::filesystem::create_directory(saveFolderPath);
    }
    readsavedatalist();
}

void savedatamanager::readsavedatalist()
{
	// 读取存档列表
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

