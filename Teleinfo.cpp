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

#include "Teleinfo.h"
#include "Kernel.h"

#ifdef XPL
	extern xPL xpl;
#endif

Teleinfo::Teleinfo()
{

}

Teleinfo::Teleinfo(int _id, char* _name)
{
	m_sensor = new AnalogSensor(_id, "forTeleinfo");
	memcpy(m_name, _name, 16);

	m_iID = _id;

	m_sensorThreshold = 400;
	m_bTurnRecorded = false;
}

Teleinfo::~Teleinfo()
{
	delete m_sensor;
}

void Teleinfo::Update()
{
	m_sensor->Update();

	if(m_sensor->m_fValue < m_sensorThreshold && !m_bTurnRecorded)
	{
		m_bTurnRecorded = true;
		m_HCHP += (m_fCompteurC * 1000);

		m_IINST = m_fCompteurC * 3600 / (m_OneTurnTimer.GetTotalTime()/1000);

		m_OneTurnTimer.Reset();
	}
	else if(m_sensor->m_fValue > m_sensorThreshold)
	{
		m_bTurnRecorded = false;
	}
}

void Teleinfo::Action(void*)
{

}

char* Teleinfo::ToJson()
{
	char str[100];
	sprintf(str,"{\"type\":\"analog\",\"id\":\"%s\",\"value\":\"%s\"}", m_name, m_sensor->m_fValue);
	return str;
}

void Teleinfo::SendStatus()
{
/*#ifdef XPL
	xPL_Message msg;

	msg.hop = 1;
	msg.type = XPL_TRIG;

	strcpy(msg.source.vendor_id, "cstuff");
	strcpy(msg.source.device_id, "teleinfo");
	strcpy(msg.source.instance_id, ConnectingStuff::GetCARDNAME());

	strcpy(msg.target.vendor_id, "*");
	//strcpy(msg.target.device_id, "xxx");
	//strcpy(msg.target.instance_id, "xxx");

	strcpy(msg.schema.class_id, "teleinfo");
	strcpy(msg.schema.type_id, "basic");

	msg.AddCommand("HCHP",(int)m_HCHP);
	msg.AddCommand("IINST",m_IINST);

	xpl.SendMessage(&msg);
#endif*/
}

void Teleinfo::SetCompteurC(float _C)
{
	m_fCompteurC = _C;
}

void Teleinfo::SetHCHP(unsigned int _HCHP)
{
	m_HCHP = _HCHP;
}

void Teleinfo::SetThreshold(int _threshold)
{
	m_sensorThreshold = _threshold;
}

unsigned int Teleinfo::GetTotal()
{
	return m_HCHP / 1000;
}

unsigned int Teleinfo::GetInst()
{
	return m_IINST;
}
