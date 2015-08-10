#include "hr_timer.h"


//================================================================================================================================================


namespace Other
{

	Timer::Timer(int n, bool _start)
	{
		this->counters = new  unsigned __int64[n];
		QueryPerformanceFrequency((LARGE_INTEGER*)&freq);

		if (_start)
		{
			for (int i = 0; i < n; ++i)
			{
				start(i);
			}
		}
	}
	Timer::~Timer(void)
	{
		delete[] this->counters;
	}

	void Timer::start(int counter) 
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&this->counters[counter]);
	} 
	double Timer::get(double multiply, int counter) 
	{
		unsigned __int64 end;
		QueryPerformanceCounter((LARGE_INTEGER*)&end);
		return (double(end - this->counters[counter]) / freq) * multiply;
	}

}
