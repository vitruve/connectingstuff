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

#ifndef OnewireManager_h
#define OnewireManager_h

#ifdef ONEWIRE

#include "Arduino.h"
#include "Kernel.h"
#include "Timer.h"
#include "TemperatureSensor.h"

#include "../OneWire/OneWire.h"
#include "../DallasTemperature/DallasTemperature.h";

#define ONE_WIRE_BUS 22
#define TEMPERATURE_PRECISION 12
#define GET_TEMP_TIME 60000
#define DEFAULT_KILL_TIME 1000
#define DEFAULT_START_TIME 1000

class OnewireManager
{
	protected:
		OneWire* oneWire;
		DallasTemperature* sensors;

		Timer m_refreshTimer;
		uint8_t m_iNbDevice;

		TemperatureSensor** m_sensorList;

		void printAddress(DeviceAddress);

	public:
		OnewireManager();
		~OnewireManager();

		void Init();
		void Update();
};

#endif
#endif
