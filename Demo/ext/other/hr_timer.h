#pragma once

#include <windows.h>


//================================================================================================================================================


namespace Other
{

	class Timer
	{
	private:
		unsigned long long* counters;
		unsigned long long  freq;

	public:
		Timer(int = 1, bool = false);
		~Timer(void);

		void start(int = 0);
		double get(double = 1., int = 0);
	};

}