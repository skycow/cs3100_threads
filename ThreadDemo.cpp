#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdlib>

int makeRandom(int max, std::mutex& mutex)
{
	std::lock_guard<std::mutex> lock(mutex);

	return (rand() % max) + 1;
}


void threadStart(int threadId, std::mutex& mutex)
{
	for (int value = 0; value < 4; value++)
	{
		std::cout << "Thread: " << threadId;
		std::cout << " Value: " << makeRandom(100, mutex) << std::endl;
	}
}


int main()
{
	srand(time(NULL));

	std::mutex mutex;

	std::thread thread1(threadStart, 1, std::ref(mutex));
	std::thread thread2(threadStart, 2, std::ref(mutex));

	thread1.join();
	thread2.join();

	return 0;
}

