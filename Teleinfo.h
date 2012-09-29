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
#ifndef Teleinfo_h
#define Teleinfo_h

#include "Arduino.h"
#include "AnalogSensor.h"

class Teleinfo : public Module
{
	protected:
		AnalogSensor* m_sensor;

		unsigned int m_HCHP;
		unsigned int m_IINST;

		int m_sensorThreshold;
		bool m_bTurnRecorded;

		float m_fCompteurC;

		Timer m_OneTurnTimer;

		// A completer/Modifier pour la vraie teleinfo

	public:
		Teleinfo();
		Teleinfo(int, char *);
		~Teleinfo();

		void Action(void*);
		char* ToJson();
		void SendStatus();

		void Update();

		void SetThreshold(int);
		void SetHCHP(unsigned int);
		void SetCompteurC(float);

		unsigned int GetTotal();
		unsigned int GetInst();
};

#endif
