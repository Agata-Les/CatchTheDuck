#pragma once

#include <string>
#include <queue>
#include <mutex>

namespace ThreadSafe
{

class Queue
{
public:
	std::string pop();
	void push(const std::string& message);
	bool empty() const;

private:
	std::queue<std::string> queue;
	std::mutex guard;
};

} // namespace ThreadSafe