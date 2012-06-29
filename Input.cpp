#include "Input.h"

Input::Input()
{
}

Input::Input(int _io, bool _deboune)
{
	Init(_io, _deboune);
}

Input::~Input()
{
}

void Input::Init(int _io, bool _deboune)
{
	m_iio = _io;
	m_bDebounceInput = _deboune;

	pinMode(m_iio, INPUT);		// configuration de l'io en Entrée
	m_iLastState = m_iState = HIGH;
	Read();
}

void Input::SetInternalPullupResistor()
{
	digitalWrite(m_iio, HIGH);		// activation de la resistance de pullup
	m_iState = HIGH;
}

uint8_t Input::GetState()
{
	return m_iState;
}

uint8_t Input::GetLastState()
{
	return m_iLastState;
}

bool Input::StateChange()
{
	if(m_iState != m_iLastState)
		return true;

	return false;
}

/// Retourne l'état de l'io associée après traitement anti-rebond
// voir http://arduino.cc/en/Tutorial/Debounce
uint8_t Input::Read()
{
	static uint8_t iLastDebounceState = HIGH;

	uint8_t iReading = digitalRead(m_iio);

	if(m_bDebounceInput)
	{
		// Reset du timer anti-rebond
		if (iReading != iLastDebounceState)
		{
			m_TimerDebounce.Reset();
		}

		if (m_TimerDebounce.GetTotalTime() > DEBOUNCE_DELAY)
		{
			m_iLastState = m_iState;
			m_iState = iReading;
		}

		iLastDebounceState = iReading;
	}
	else
	{
		m_iLastState = m_iState;
		m_iState = iReading;
	}

	return m_iState;
}
