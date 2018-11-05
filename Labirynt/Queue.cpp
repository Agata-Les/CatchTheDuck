#include "Queue.h"

namespace ThreadSafe
{

std::string Queue::pop()
{
	guard.lock();
	const auto element = queue.front();
	queue.pop();
	guard.unlock();

	return element;
}

void Queue::push(const std::string& message)
{
	guard.lock();
	queue.push(message);
	guard.unlock();
}

bool Queue::empty() const
{
	return queue.empty();
}

} // namespace ThreadSafe