#pragma once

#include "Queue.h"
#include <fstream>
#include <thread>
#include <memory>

class Logger
{
public:
	void info(const std::string& message);
	void error(const std::string& message);

	Logger();
	~Logger();

private:
	std::unique_ptr<std::thread> loggerThread;
	bool isRunning = true;
	ThreadSafe::Queue messagePool;
	std::fstream logFile;
	void threadMain();
	std::string getCurrentTime();
};
