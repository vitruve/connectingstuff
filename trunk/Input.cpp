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

#include "Input.h"

Input::Input()
{
}

Input::Input(int _io, bool _deboune)
{
	Init(_io, _deboune);
}

Input::~Input()
{
}

void Input::Init(int _io, bool _deboune)
{
	m_iio = _io;
	m_bDebounceInput = _deboune;

	pinMode(m_iio, INPUT);		// configuration de l'io en Entrée
	m_iLastState = m_iState = HIGH;
	Read();
}

void Input::SetInternalPullupResistor()
{
	digitalWrite(m_iio, HIGH);		// activation de la resistance de pullup
	m_iState = HIGH;
}

uint8_t Input::GetState()
{
	return m_iState;
}

uint8_t Input::GetLastState()
{
	return m_iLastState;
}

bool Input::StateChange()
{
	if(m_iState != m_iLastState)
		return true;

	return false;
}

/// Retourne l'état de l'io associée après traitement anti-rebond
// voir http://arduino.cc/en/Tutorial/Debounce
uint8_t Input::Read()
{
	static uint8_t iLastDebounceState = HIGH;

	uint8_t iReading = digitalRead(m_iio);

	if(m_bDebounceInput)
	{
		// Reset du timer anti-rebond
		if (iReading != iLastDebounceState)
		{
			m_TimerDebounce.Reset();
		}

		if (m_TimerDebounce.GetTotalTime() > DEBOUNCE_DELAY)
		{
			m_iLastState = m_iState;
			m_iState = iReading;
		}

		iLastDebounceState = iReading;
	}
	else
	{
		m_iLastState = m_iState;
		m_iState = iReading;
	}

	return m_iState;
}
