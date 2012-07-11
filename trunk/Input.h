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

#ifndef Input_h
#define Input_h

#include "Arduino.h"
#include "Timer.h"

#define DEBOUNCE_DELAY 50

class Input
{
	protected:
		//int m_iCard;													// Id de la carte
		uint8_t m_iio;													// Numero d'io

		uint8_t m_iState;												// etat courant
		uint8_t m_iLastState;										// etat precedent

		// Debounce (voir tuto arduino)
		Timer m_TimerDebounce;
		//uint8_t m_bLastDebounceState;
		bool m_bDebounceInput;

	public:
		Input();
		Input(int, bool = true);
		~Input();

		void Init(int, bool = true);
		uint8_t   Read();												// Retourne la valeur de l'entrée
		uint8_t GetState();
		uint8_t GetLastState();
		bool StateChange();

		void SetInternalPullupResistor();
};

#endif
