#include "log.h"

std::string GetTime() {
	time_t t = time(0);
	tm* now = localtime(&t);
	return std::to_string(now->tm_hour) + ":" + std::to_string(now->tm_min) + ":" + std::to_string(now->tm_sec);
}

Log::Log(std::string path) {
	std::ofstream file(path);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open log path at " + path + ".\nCheck that you have write permission.");
	}
	file.close();
}

write(std::string text, Level level) {
	std::string file_text = text;
	std::string print_text = text;
	bool write_to_file = true;
	switch(level) {
		case Level::DEBUG:
			file_text = "[DEBUG] " + text;
			print_text = "[" + colours::GREEN + "DEBUG" + colours::RESET + "] " + text;
			write_to_file = false;
			break;
		case Level::WARN:
			file_text = "[WARN] " + text;
			print_text = "[" + colours::YELLOW + "WARN" + colours::RESET + "] " + text;
			break;
	}
}

static std::string generate_path(std::string name) {
	if (name.is_empty()) {
		return "";
	}
	std::string base;
	#ifdef _WIN32
		base = std::string(getenv("APPDATA"));
	#else
		base = std::string(getenv("HOME"));
	#endif
	return base + "/" + name;
}
