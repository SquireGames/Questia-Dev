#ifndef BARRIER_H
#define BARRIER_H

#include <mutex>
#include <condition_variable>

#include "QuestiaEng/Utl/Toggler.h"
#include "QuestiaEng/Utl/Ticker.h"

namespace utl
{

class Barrier
{
public:
	Barrier(int count) noexcept;
	~Barrier() noexcept;
	
	void wait() noexcept;
	
private:
	std::mutex mutex;
	std::condition_variable releaseCondVar;
	int maxCount;
	Ticker readyCounter;
	Toggler generationToggler;
};
	
}

#endif // BARRIER_H
