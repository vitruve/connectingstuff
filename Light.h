/*
Output.h - Library for domotic ouput management
  Created by Lebrun Olivier 05/08/2010
*/
#ifndef Light_h
#define Light_h

#include "Arduino.h"
#include "Output.h"
#include "Switch.h"
#include "Module.h"
#include "Timer.h"

#ifdef XPL
#include "../xPL/xPL.h"
#endif

class Light : public Module
{
	protected:
		Timer m_OffTimer;
		int m_iAutoOffTime;

		Output m_output;

	public:
		Light();
		Light(uint8_t, uint8_t, char*); // carte, sortie
		~Light();

		void SetAutoOff(int);
		void Update();

		void Action(void*);
		char* ToJson();
		void SendStatus();

		void Set(uint8_t);
		void Toogle();
};

#endif
