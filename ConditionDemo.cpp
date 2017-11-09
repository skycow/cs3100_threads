#include <condition_variable>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

void waitForInput(std::uint16_t threadId, std::condition_variable& event, std::mutex& mutex, bool& ready)
{
	std::unique_lock<std::mutex> lock(mutex);
	event.wait(lock, [&] { return ready; });
	std::cout << "Thread " << threadId << " notified of keyboard event!" << std::endl;
}

int main()
{
	std::condition_variable eventKeyboard;
	std::mutex mutex;
	bool ready = false;

	std::thread thread1(waitForInput, 1, std::ref(eventKeyboard), std::ref(mutex), std::ref(ready));
	std::thread thread2(waitForInput, 2, std::ref(eventKeyboard), std::ref(mutex), std::ref(ready));
	std::thread thread3(waitForInput, 3, std::ref(eventKeyboard), std::ref(mutex), std::ref(ready));
	std::thread thread4(waitForInput, 4, std::ref(eventKeyboard), std::ref(mutex), std::ref(ready));

	std::string input;
	std::cout << "Press enter for the amazing demo: ";
	std::getline(std::cin, input);

	ready = true;
	eventKeyboard.notify_one();
	eventKeyboard.notify_one();

	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();

	return 0;
}
