#include "simpleui_logger.h"

std::map<ColourEnums, const char*> Colours = {
	{RESET, "\033[0m"},
	{BOLD, "\033[1m"},
	{BLACK, "\033[30m"},
	{RED, "\033[31m"},
	{GREEN, "\033[32m"},
	{YELLOW, "\033[33m"},
	{BLUE, "\033[34m"},
	{MAGENTA, "\033[35m"},
	{CYAN, "\033[36m"},
	{WHITE, "\033[37m"}
};

bool SimpleUI_debug = false;

std::string GetTime() {
	time_t t = time(0);
	tm* now = localtime(&t);
	return std::to_string(now->tm_hour) + ":" + std::to_string(now->tm_min) + ":" + std::to_string(now->tm_sec);
}

void SimpleUI_Log(std::string str, Level level) {
	std::string currentTime = GetTime();
	const char* now = currentTime.c_str();
	const char* text = str.c_str();
	switch (level) {
		case Level::DEBUG:
			if (SimpleUI_debug) {
				printf("[%sDEBUG%s] [%s%s%s]: %s\n",
					Colours[GREEN], Colours[RESET],
					Colours[GREEN], now, Colours[RESET],
					text);
			} break;
		case Level::INFO:
			printf("[%sINFO%s] [%s%s%s]: %s\n",
				Colours[CYAN], Colours[RESET],
				Colours[GREEN], now, Colours[RESET],
				text); break;
		case Level::WARN:
			printf("[%sWARN%s] [%s%s%s]: %s%s%s\n",
				Colours[YELLOW], Colours[RESET],
				Colours[GREEN], now, Colours[RESET],
				Colours[YELLOW], text, Colours[RESET]); break;
		case Level::ERROR:
			fprintf(stderr, "[%sERROR%s] [%s%s%s]: %s%s%s\n",
				Colours[RED], Colours[RESET],
				Colours[GREEN], now, Colours[RESET],
				Colours[RED], text, Colours[RESET]); break;
	}
}

void SimpleUI_Log(int str, Level level) {
	SimpleUI_Log(std::to_string(str), level);
}

void SimpleUI_Log(double str, Level level) {
	SimpleUI_Log(std::to_string(str), level);
}

void SimpleUI_Log(float str, Level level) {
	SimpleUI_Log(std::to_string(str), level);
}
