/*
  Input.h - Library for domotic input management
  Created by Lebrun Olivier 05/08/2010
*/
#ifndef timer_h
#define timer_h

class Timer
{
	protected:

	    unsigned long m_lT0;
	    unsigned long m_lT;

	public:
		Timer();
		~Timer();

		unsigned long GetElapseTime();
		unsigned long GetTotalTime();
		unsigned long GetTime();
		unsigned long GetTimeStart();

		void Init();
		void Reset();
		void Stop();
};

#endif
