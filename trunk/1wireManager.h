#ifndef OnewireManager_h
#define OnewireManager_h

#include "Arduino.h"
#include "Kernel.h"
#include "Timer.h"
#include "TemperatureSensor.h"

#include "../OneWire/OneWire.h"
#include "../DallasTemperature/DallasTemperature.h";

#define ONE_WIRE_BUS 22
#define TEMPERATURE_PRECISION 12
#define GET_TEMP_TIME 60000
#define DEFAULT_KILL_TIME 1000
#define DEFAULT_START_TIME 1000

class OnewireManager
{
	protected:
		OneWire* oneWire;
		DallasTemperature* sensors;

		Timer m_refreshTimer;
		uint8_t m_iNbDevice;

		TemperatureSensor** m_sensorList;

		void printAddress(DeviceAddress);

	public:
		OnewireManager();
		~OnewireManager();

		void Init();
		void Update();
};

#endif
