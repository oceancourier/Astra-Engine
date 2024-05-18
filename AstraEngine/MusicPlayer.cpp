#include "MusicPlayer.h"
#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <vector>

#pragma comment(lib, "winmm.lib")

MusicPlayer::MusicPlayer() {
}

MusicPlayer::~MusicPlayer() {
    CloseMusic();
}

void MusicPlayer::SetMusic(const std::string& musicFilePath) {
    StopMusic();
    CloseMusic();
    OpenMusic(musicFilePath);
}

void MusicPlayer::StopMusic() {
    std::wstring command = L"stop " + m_currentAlias;
    mciSendString(command.c_str(), nullptr, 0, nullptr);
}

void MusicPlayer::CloseMusic() {
    std::wstring command = L"close " + m_currentAlias;
    mciSendString(command.c_str(), nullptr, 0, nullptr);
}

void MusicPlayer::OpenMusic(const std::string& musicFilePath) {
    std::wstring wideMusicFilePath = utf8_to_wstring(musicFilePath);

    std::wstring command = L"open \"" + wideMusicFilePath + L"\" type waveaudio alias mp3";
    MCIERROR err = mciSendString(command.c_str(), nullptr, 0, nullptr);
    if (err != 0) {
        wchar_t errorText[256];
        mciGetErrorString(err, errorText, 256);
        std::wcerr << L"Error opening music file: " << errorText << std::endl;
    }
    else {
        m_currentAlias = L"mp3";
    }
}
std::wstring MusicPlayer::utf8_to_wstring(const std::string& utf8str) {
    std::wstring wstr;
    if (!utf8str.empty()) {
        size_t charsNeeded = mbstowcs(nullptr, utf8str.c_str(), 0); // 计算所需的宽字符数
        if (charsNeeded == static_cast<size_t>(-1)) {
            throw std::runtime_error("Failed converting UTF-8 string to wstring.");
        }
        std::vector<wchar_t> buffer(charsNeeded + 1);
        size_t charsConverted = mbstowcs(buffer.data(), utf8str.c_str(), utf8str.length());
        if (charsConverted != charsNeeded) {
            throw std::runtime_error("Failed converting UTF-8 string to wstring.");
        }
        wstr.assign(buffer.data(), charsConverted);
    }
    return wstr;
}
bool MusicPlayer::PlayMusic(const std::string& musicFilePath) {
    StopMusic();
    CloseMusic();
    OpenMusic(musicFilePath);

    std::wstring command = L"play " + m_currentAlias;
    MCIERROR err = mciSendString(command.c_str(), nullptr, 0, nullptr);
    if (err != 0) {
        wchar_t errorText[256];
        mciGetErrorString(err, errorText, 256);
        std::wcerr << L"Error playing music: " << errorText << std::endl;
        return false;
    }
    return true;
}
