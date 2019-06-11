#pragma once

#include <string>
#include <stdio.h>
#include <map>

enum ColourEnums {
	RESET,
	BOLD,
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE
};

extern std::map<ColourEnums, const char*> Colours;

extern bool SimpleUI_debug;

std::string GetTime();

enum class Level {
	DEBUG,
	INFO,
	WARN,
	ERROR
};

void SimpleUI_Log(std::string str, Level level = Level::INFO);
void SimpleUI_Log(int str, Level level = Level::INFO);
void SimpleUI_Log(double str, Level level = Level::INFO);
void SimpleUI_Log(float str, Level level = Level::INFO);
