#pragma once

#include <string>

class MusicPlayer {
public:
    MusicPlayer();
    ~MusicPlayer();

    bool PlayMusic(const std::string& musicFilePath);
    void SetMusic(const std::string& musicFilePath);
    void StopMusic();
    void CloseMusic();
    std::wstring utf8_to_wstring(const std::string& utf8str);
private:
    std::wstring m_currentAlias;

    void OpenMusic(const std::string& musicFilePath);
};
