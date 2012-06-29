#include "Arduino.h"
#include "Timer.h"

Timer::Timer()
{
	Init();
}

Timer::~Timer()
{
}

void Timer::Init()
{
	m_lT0 = millis();
	m_lT = m_lT0;
}

void Timer::Reset()
{
	Init();
}

void Timer::Stop()
{
	m_lT0 = m_lT  = 0;
}

unsigned long Timer::GetTimeStart()
{
	return m_lT0;
}

unsigned long Timer::GetTime()
{
	return millis();
}

unsigned long Timer::GetTotalTime()
{
	if(m_lT0 == 0) return 0;
	else
	{
		return(millis() - m_lT0);
	}
}

unsigned long Timer::GetElapseTime()
{
    unsigned long lCurrentTime;
    unsigned int iElapseTime;

	lCurrentTime = millis();

	iElapseTime = lCurrentTime - m_lT;
	m_lT = lCurrentTime;

	return(iElapseTime);
}
