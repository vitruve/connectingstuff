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

#include "Tools.h"
#include "AnalogSensor.h"
#include "Kernel.h"

#ifdef XPL
	extern xPL xpl;
#endif

AnalogSensor::AnalogSensor()
{

}

AnalogSensor::AnalogSensor(int _id, char* _name)
{
	m_lastRefreshTime = 0;
	m_fValue = 0;
	strcpy(m_sValue,"0");

	memcpy(m_name, _name, 16);

	m_iID = _id;
}

AnalogSensor::~AnalogSensor()
{
}

void AnalogSensor::Update()
{
	m_fValue = analogRead(A0);

	ftoa(m_sValue,m_fValue, 2);

	char str[50];
	sprintf(str,"Analog%d:%s", m_iID, m_sValue);
	//ConnectingStuff::Debug(str);
}

void AnalogSensor::Action(void*)
{

}

char* AnalogSensor::ToJson()
{
	char str[100];
	sprintf(str,"{\"type\":\"analog\",\"id\":\"%s\",\"value\":\"%s\"}", m_name, m_sValue);
	return str;
}

void AnalogSensor::SendStatus()
{
/*#ifdef XPL
	xPL_Message msg;

	msg.hop = 1;
	msg.type = XPL_TRIG;

	strcpy(msg.source.vendor_id, "cstuff");
	strcpy(msg.source.device_id, "analog");
	strcpy(msg.source.instance_id, ConnectingStuff::GetCARDNAME());

	strcpy(msg.target.vendor_id, "*");
	//strcpy(msg.target.device_id, "xxx");
	//strcpy(msg.target.instance_id, "xxx");

	strcpy(msg.schema.class_id, "sensor");
	strcpy(msg.schema.type_id, "basic");

	msg.AddCommand("device",m_iID);
	msg.AddCommand("type","analog");
	msg.AddCommand("current",m_sValue);

	xpl.SendMessage(&msg);
#endif*/
}
