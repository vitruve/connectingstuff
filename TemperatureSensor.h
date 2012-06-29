/*
Output.h - Library for domotic ouput management
  Created by Lebrun Olivier 05/08/2010
*/
#ifndef TemperatureSensor_h
#define TemperatureSensor_h

#include "Arduino.h"
#include "Sensor.h"
#include "Kernel.h"
#include "../DallasTemperature/DallasTemperature.h";

#ifdef XPL
#include "../xPL/xPL.h"
#endif

class TemperatureSensor : public Sensor
{
	public:
		DeviceAddress m_address;

		TemperatureSensor();
	   	TemperatureSensor(int, DeviceAddress);
	   	~TemperatureSensor();

	   	void Action(void*);
		char* ToJson();
		void SendStatus();

		void Update(float);
};

#endif
