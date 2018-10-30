#include "Logger.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace constant
{
	const std::string info{" [INF] "};
	const std::string error{" [ERR] "};
}

void Logger::info(const std::string& message)
{
	messagePool.push(getCurrentTime() + constant::info + message);
}

void Logger::error(const std::string& message)
{
	messagePool.push(getCurrentTime() + constant::error + message);
}


Logger::Logger()
{
	char fileName[] = "log.txt";
	logFile.open(fileName, std::fstream::out | std::fstream::trunc);
	loggerThread = std::make_unique<std::thread>(&Logger::threadMain, this);
}


Logger::~Logger()
{
	isRunning = false;
	loggerThread->join();
	logFile.close();
}

void Logger::threadMain()
{
	while (isRunning)
	{
		if (messagePool.empty()) std::this_thread::sleep_for(std::chrono::seconds(2));

		else
		{
			logFile << messagePool.pop();
		}
	}
}

std::string Logger::getCurrentTime()
{
	time_t time { std::time(nullptr) };
	struct tm timeInfo;
	localtime_s(&timeInfo, &time);

	std::ostringstream ss;
	ss << std::put_time(&timeInfo, "%d-%m-%Y %H:%M:%S");
	return ss.str();
}
