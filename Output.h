/*
Output.h - Library for domotic ouput management
  Created by Lebrun Olivier 05/08/2010
*/
#ifndef Output_h
#define Output_h

#include "Arduino.h"
#include "Timer.h"
#include "Input.h"


class Output
{
	public:
	   unsigned long m_iAutoOff;

	protected:
	   	uint8_t m_iCard;
	   	uint8_t m_iio;
		int m_iID;

		uint8_t m_iState;
		long m_lUpTime;

		Timer m_OnTimer; // tps d'activite depuis le dernier off;

	public:
		Output();
		Output(uint8_t, uint8_t); // carte, sortie
		~Output();

		void Init(uint8_t, uint8_t);

		void Set(uint8_t);
		void Toogle();

		uint8_t Read(void);
		uint8_t ReadReal(void);

		uint8_t GetCardID();
		int GetID();

		unsigned long GetOnTime(void);



};

#endif
