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

#include "TemperatureSensor.h"

#ifdef XPL
	extern xPL xpl;
#endif

char *ftoa(char *a, double f, int precision)
{
  long p[] = {0,10,100,1000,10000,100000,1000000,10000000,100000000};

  char *ret = a;
  long heiltal = (long)f;
  itoa(heiltal, a, 10);
  while (*a != '\0') a++;
  *a++ = '.';
  long desimal = abs((long)((f - heiltal) * p[precision]));
  itoa(desimal, a, 10);
  return ret;
}

// adresse to string
void addr2str(DeviceAddress deviceAddress, char* return_me)
{
     static char *hex = "0123456789ABCDEF";
     uint8_t i, j;

     for (i=0, j=0; i<8; i++)
     {
          return_me[j++] = hex[deviceAddress[i] / 16];
          return_me[j++] = hex[deviceAddress[i] & 15];
     }
     return_me[j] = '\0';

}

TemperatureSensor::TemperatureSensor()
{

}

TemperatureSensor::TemperatureSensor(int _id, DeviceAddress _addr)
{
	m_lastRefreshTime = 0;
	m_fValue = 0;
	strcpy(m_sValue,"0");

	memcpy(m_address, _addr, 8);

	m_iID = _id;
	addr2str(m_address, m_name);
}

TemperatureSensor::~TemperatureSensor()
{
}

void TemperatureSensor::Update(float _value)
{
	if(abs(m_fValue - _value) > 0.1)
	{
		m_fValue = _value;

		ftoa(m_sValue,m_fValue, 2);

		char str[50];
		sprintf(str,"Temp%d:%s", m_iID, m_sValue);
		ConnectingStuff::Debug(str);

		SendStatus();
	}
}

void TemperatureSensor::Action(void*)
{

}

char* TemperatureSensor::ToJson()
{
	char str[100];
	sprintf(str,"{\"type\":\"temp\",\"id\":\"%s\",\"value\":\"%s\"}", m_name, m_sValue);
	return str;
}

void TemperatureSensor::SendStatus()
{
#ifdef XPL
	xPL_Message msg;

	msg.hop = 1;
	msg.type = XPL_TRIG;

	strcpy(msg.source.vendor_id, "cstuff");
	strcpy(msg.source.device_id, "temp");
	strcpy(msg.source.instance_id, ConnectingStuff::GetCARDNAME());

	strcpy(msg.target.vendor_id, "*");
	//strcpy(msg.target.device_id, "xxx");
	//strcpy(msg.target.instance_id, "xxx");

	strcpy(msg.schema.class_id, "sensor");
	strcpy(msg.schema.type_id, "basic");

	msg.AddCommand("device",m_iID);
	msg.AddCommand("type","temp");
	msg.AddCommand("current",m_sValue);

	xpl.SendMessage(&msg);
#endif
}
