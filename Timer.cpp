/*
 * connectingStuff, Arduino Based Home Automation
 * http://connectingstuff.net/blog/
 *
 * This code is parsing a xPL message stored in 'received' buffer
 * - isolate and store in 'line' buffer each part of the message -> detection of EOL character (DEC 10)
 * - analyse 'line', function of its number and store information in xpl_header memory
 * - check for each step if the message respect xPL protocol
 * - parse each command line
 *
 * Copyright (C) 2012 olivier.lebrun@gmail.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

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
