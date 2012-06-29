/*
  Input.h - Library for domotic input management
  Created by Lebrun Olivier 05/08/2010
*/
#ifndef Input_h
#define Input_h

#include "Arduino.h"
#include "Timer.h"

#define DEBOUNCE_DELAY 50

class Input
{
	protected:
		//int m_iCard;													// Id de la carte
		uint8_t m_iio;													// Numero d'io

		uint8_t m_iState;												// etat courant
		uint8_t m_iLastState;										// etat precedent

		// Debounce (voir tuto arduino)
		Timer m_TimerDebounce;
		//uint8_t m_bLastDebounceState;
		bool m_bDebounceInput;

	public:
		Input();
		Input(int, bool = true);
		~Input();

		void Init(int, bool = true);
		uint8_t   Read();												// Retourne la valeur de l'entrée
		uint8_t GetState();
		uint8_t GetLastState();
		bool StateChange();

		void SetInternalPullupResistor();
};

#endif
