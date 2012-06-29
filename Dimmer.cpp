#include "Dimmer.h"

Dimmer::Dimmer()
{
	m_type = DIMMER;
}

Dimmer::Dimmer(uint8_t _card, uint8_t _io, char* _name)
{
	m_output.Init(_card,  _io);
	m_type = DIMMER;
	strcpy(m_name, _name);
}

Dimmer::~Dimmer()
{
}

void Dimmer::SetPoint(uint8_t _value, unsigned long _duree)
{
	uint8_t state = m_output.Read();
	m_iSetPoint = _value;

	if(state != m_iSetPoint)
	{
		if(_duree == 0) m_output.Set(_value);
		else
		{
			m_iPas = _duree / (abs(m_iSetPoint - state));
			m_Timer.Reset();
		}
	}
}

void Dimmer::Update()
{
	uint8_t state = m_output.Read();

	if(m_iSetPoint != state)
	{
		if( m_Timer.GetTotalTime() >= m_iPas)
		{
			uint8_t increment = (uint8_t)(m_Timer.GetTotalTime() / m_iPas);

			if(m_iSetPoint < state) increment *= -1;

			m_output.Set(CheckPwmValue(state + increment));

			m_Timer.Reset();
		}
	}
}

uint8_t Dimmer::CheckPwmValue(uint8_t _value)
{
	if(_value < 0) _value = 0;
	else if(_value > 255) _value = 255;

	return _value;
}
