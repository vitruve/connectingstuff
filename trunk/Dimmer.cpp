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

#include "Dimmer.h"

Dimmer::Dimmer()
{
	m_type = DIMMER;
}

Dimmer::Dimmer(uint8_t _card, uint8_t _io, char* _name)
{
	m_output.Init(_card,  _io);
	m_type = DIMMER;
	strcpy(m_name, _name);
}

Dimmer::~Dimmer()
{
}

void Dimmer::SetPoint(uint8_t _value, unsigned long _duree)
{
	uint8_t state = m_output.Read();
	m_iSetPoint = _value;

	if(state != m_iSetPoint)
	{
		if(_duree == 0) m_output.Set(_value);
		else
		{
			m_iPas = _duree / (abs(m_iSetPoint - state));
			m_Timer.Reset();
		}
	}
}

void Dimmer::Update()
{
	uint8_t state = m_output.Read();

	if(m_iSetPoint != state)
	{
		if( m_Timer.GetTotalTime() >= m_iPas)
		{
			uint8_t increment = (uint8_t)(m_Timer.GetTotalTime() / m_iPas);

			if(m_iSetPoint < state) increment *= -1;

			m_output.Set(CheckPwmValue(state + increment));

			m_Timer.Reset();
		}
	}
}

uint8_t Dimmer::CheckPwmValue(uint8_t _value)
{
	if(_value < 0) _value = 0;
	else if(_value > 255) _value = 255;

	return _value;
}
