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

