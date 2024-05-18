#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
class windowinformation {
public:
    int WindowWidth;
    int WindowHeight;
    int WindowXPosition;
    int WindowYPosition;
    void getConsoleSize();
    windowinformation();
private:
	
};