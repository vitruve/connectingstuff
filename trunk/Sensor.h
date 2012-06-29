/*
Output.h - Library for domotic ouput management
  Created by Lebrun Olivier 05/08/2010
*/
#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"
#include "Module.h"

class Sensor : public Module
{
	public:
	   	float m_fValue;
	   	char m_sValue[10];
	   	unsigned long m_lastRefreshTime;
};

#endif
