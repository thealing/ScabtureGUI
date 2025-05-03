#include "Profiler.h"

static int _level;
static Thread* _thread;

static void threadProc(void*)
{
	MessageBeep(MB_OK);
	while (true)
	{
		int totalCount = 0;
		int activeCount = 0;
		double startTime = getTime();
		double updateTime = startTime;
		double enterTime = 0;
		int durationCount = 0;
		double durationSum = 0;
		while (true)
		{
			double currentTime = getTime();
			if (currentTime - updateTime >= 0.0011)
			{
				updateTime = currentTime;
				totalCount++;
				if (_level > 0)
				{
					activeCount++;
				}
			}
			if (currentTime - startTime >= 1.5)
			{
				break;
			}
			if (_level > 0)
			{
				if (enterTime == 0 && activeCount < totalCount)
				{
					enterTime = currentTime;
				}
			}
			else if (enterTime != 0)
			{
				durationCount++;
				durationSum += currentTime - enterTime;
				enterTime = 0;
			}
		}
		wprintf(L"Profiler: Usage: %i %% Duration: %f ms", activeCount * 100 / totalCount, durationSum * 1000 / max(1, durationCount));
	}
}

void enterBlock()
{
	if (_thread == NULL)
	{
		_thread = new Thread(Callback(threadProc, NULL));
	}
	_level++;
}

void leaveBlock()
{
	_level--;
}
