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

void calcPi(SafeQueue & inQueue, std::unordered_map & resMap)
{
	int nextVal;
	while(inQueue.getNext(&nextVal))
	{
		
	}
}

Class SafeQueue{
	private
	  std::mutex mutex;
	  std::queue theQueue;
	public

	SafeQueue(int num_digits)
	{
		for(int i = 0; i < num_digits; i++)
		{
			theQueue.push_back(i);
		}
	}

	bool getnext(&int val){
    int ret;

		std::lock_guard<std::mutex> lock(mutex);
		if(theQueue.empty())
			return false;
		else
			{
				val = theQueue.front();
			  theQueue.pop();
			  return true;
			}
	}

}

int main()
{
	srand(time(NULL));


	SafeQueue digitQueue(100);
	//digitQueue.initialize();



	std::mutex mutex;

	std::thread thread1(calcPi, &digitQueue);
	std::thread thread2(calcPi, &digitQueue);

	thread1.join();
	thread2.join();

	return 0;
}
