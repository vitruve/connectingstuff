/*
 * connectingStuff, Arduino Based Home Automation
 * http://connectingstuff.net/blog/
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

#ifndef Output_h
#define Output_h

#include "Arduino.h"
#include "Timer.h"
#include "Input.h"


class Output
{
	public:
	   unsigned long m_iAutoOff;

	protected:
	   	uint8_t m_iCard;
	   	uint8_t m_iio;
		int m_iID;

		uint8_t m_iState;
		long m_lUpTime;

		Timer m_OnTimer; // tps d'activite depuis le dernier off;

	public:
		Output();
		Output(uint8_t, uint8_t); // carte, sortie
		~Output();

		void Init(uint8_t, uint8_t);

		void Set(uint8_t);
		void Toogle();

		uint8_t Read(void);
		uint8_t ReadReal(void);

		uint8_t GetCardID();
		int GetID();

		unsigned long GetOnTime(void);



};

#endif
