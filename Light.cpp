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

#include "Light.h"
#include "Kernel.h"

#ifdef XPL
	extern xPL xpl;
#endif

Light::Light()
{
	m_type = LIGHT;
}

Light::Light(uint8_t _card, uint8_t _io, char* _name)
{
	m_output.Init(_card,  _io);
	m_type = LIGHT;
	m_iID = m_output.GetID();
	strcpy(m_name, _name);
}

Light::~Light()
{
}

void Light::SetAutoOff(int _time)
{
	m_iAutoOffTime = _time;
	m_OffTimer.Init();
}

void Light::Update()
{
	if(m_OffTimer.GetTotalTime() > m_iAutoOffTime)
	{
		Set(LOW);
	}
}

void Light::Action(void* _arg)
{
	ConfigModule* config = (ConfigModule*)_arg;
	
	switch(config->onOff)
		{
			case ONOFF:
				Toogle();
				break;
			case OFF:
				Set(LOW);
				break;
			case ON:
				Set(HIGH);
				break;
			default:
				break;
		}

		if(m_output.Read() > 0)
		{
			m_OffTimer.Reset();
		}
}

void Light::Toogle()
{
	m_output.Toogle();
	SendStatus();

	char str[50];
	sprintf(str,"Light%d:%d", m_iID, (int)m_output.Read());
	ConnectingStuff::Debug(str);
}

void Light::Set(uint8_t _state)
{
	m_output.Set(_state);
	SendStatus();

	char str[50];
	sprintf(str,"Light%d:%d", m_iID, (int)m_output.Read());
	ConnectingStuff::Debug(str);
}

char* Light::ToJson()
{
	char str[150];
	sprintf(str,"{\"type\":\"light\",\"id\":\"%d\",\"name\":\"%s\",\"pin\":\"%d\",\"value\":\"%d\"}", m_iID, m_name, m_iID, (int)m_output.Read());
	return str;
}

void Light::SendStatus()
{
#ifdef XPL
	xPL_Message msg;

	msg.hop = 1;
	msg.type = XPL_TRIG;

	strcpy(msg.source.vendor_id, "cstuff");
	strcpy(msg.source.device_id, "light");
	strcpy(msg.source.instance_id, ConnectingStuff::GetCARDNAME());

	strcpy(msg.target.vendor_id, "*");
	//strcpy(msg.target.device_id, "xxx");
	//strcpy(msg.target.instance_id, "xxx");

	strcpy(msg.schema.class_id, "lighting");
	strcpy(msg.schema.type_id, "device");

	msg.AddCommand("network","1");
	msg.AddCommand("device","11");
	msg.AddCommand("channel","1");
	char buffer[50];
	strcpy(buffer, m_output.Read() == 0 ? "off" : "on");
	msg.AddCommand("state",buffer);
	msg.AddCommand("level",m_output.Read());

	xpl.SendMessage(&msg);
#endif
}
