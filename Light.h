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

#ifndef Light_h
#define Light_h

#include "Arduino.h"
#include "Output.h"
#include "Switch.h"
#include "Module.h"
#include "Timer.h"

#ifdef XPL
#include "../xPL/xPL.h"
#endif

class Light : public Module
{
	protected:
		Timer m_OffTimer;
		int m_iAutoOffTime;

		Output m_output;

	public:
		Light();
		Light(uint8_t, uint8_t, char*); // carte, sortie
		~Light();

		void SetAutoOff(int);
		void Update();

		void Action(void*);
		char* ToJson();
		void SendStatus();

		void Set(uint8_t);
		void Toogle();
};

#endif
