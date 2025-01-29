#include "../Logger.h"

int main() {
	Logger::getInstance().setLogFile("log.txt");
	Logger::getInstance().log("Error message", LogLevel::Error);
	return 0;
}