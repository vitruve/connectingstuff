/*
Output.h - Library for domotic ouput management
  Created by Lebrun Olivier 05/08/2010
*/
#ifndef Dimmer_h
#define Dimmer_h

#include "Arduino.h"
#include "Timer.h"
#include "Output.h"
#include "Module.h"

class Dimmer : public Module
{
	public:
	   	unsigned long m_iAutoOff;

	protected:
	   	uint8_t m_iSetPoint;
	   	uint8_t m_iPas;

		Output m_output;

	   	Timer m_Timer;

	public:
		Dimmer();
		Dimmer(uint8_t, uint8_t, char*);
		~Dimmer();

		void SetPoint(uint8_t, unsigned long);
		void Update();
		uint8_t CheckPwmValue(uint8_t);

		unsigned long GetOnTime(void);
};

#endif
