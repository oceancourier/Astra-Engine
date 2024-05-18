#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#pragma comment(lib, "winmm.lib")
class AudioPlayer {
private:
    std::wstring musicPath;
    bool isPlaying;

    // Helper function to convert std::string to std::wstring
    std::wstring stringToWideString(const std::string& str) {
        if (str.empty()) return std::wstring();
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
        std::wstring wstrTo(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
        return wstrTo;
    }

public:
    AudioPlayer() : isPlaying(false) {}

    // Load music file
    bool loadMusic(const std::string& path) {
        musicPath = stringToWideString(path);
        return !musicPath.empty();
    }

    // Play music asynchronously
    bool play() {
        if (musicPath.empty()) {
            std::wcerr << L"No music file loaded." << std::endl;
            return false;
        }
        if (!PlaySound(musicPath.c_str(), NULL, SND_FILENAME | SND_ASYNC)) {
            std::wcerr << L"Failed to play the music." << std::endl;
            return false;
        }
        isPlaying = true;
        return true;
    }

    // Stop music playback
    void stop() {
        if (isPlaying) {
            PlaySound(NULL, NULL, SND_ASYNC);
            isPlaying = false;
        }
    }

    // Check if music is currently playing
    bool isCurrentlyPlaying() const {
        return isPlaying;
    }
};