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

#include "Arduino.h"
#include "1wireManager.h"
#include "Manager.h"

OnewireManager::OnewireManager()
{
	oneWire = new OneWire(ONE_WIRE_BUS);
	sensors = new DallasTemperature(oneWire);

	m_iNbDevice = 0;

	sensors->begin();
}

OnewireManager::~OnewireManager()
{
	for(int i=0; i<m_iNbDevice;i++)
		free(m_sensorList[i]);

	free(m_sensorList);
}

void OnewireManager::Init()
{
  m_refreshTimer.Init();

  m_sensorList = (TemperatureSensor**)malloc ( sensors->getDeviceCount() * sizeof(TemperatureSensor*) );

  for(int i=0;i<sensors->getDeviceCount();i++)
  {
	DeviceAddress newAddr;
    if (!sensors->getAddress(newAddr, i))
    {
      Serial.println("No more device found");
      break;
    }
    else
    {
      sensors->setResolution(newAddr, 12);

      Serial.print("Sensor address ");
      printAddress(newAddr);
      Serial.print(", Resolution: ");
      Serial.println(sensors->getResolution(newAddr), DEC);

      m_sensorList[m_iNbDevice] = new TemperatureSensor(99, newAddr);
      manager.AddModule(m_sensorList[m_iNbDevice]);

      ++m_iNbDevice;
    }
  }

  Update();
}

void OnewireManager::Update()
{
	if(m_refreshTimer.GetTotalTime() > GET_TEMP_TIME )
    {
      Serial.println("Requesting temperatures...");
      sensors->requestTemperatures();

      for(int i=0;i<m_iNbDevice;i++)
      {
    	  float value = sensors->getTempC(m_sensorList[i]->m_address);
    	  if(value != DEVICE_DISCONNECTED)
    		  m_sensorList[i]->Update(value);
      }

      m_refreshTimer.Reset();
    }
}

void OnewireManager::printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

