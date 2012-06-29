#include "Output.h"
#include "Kernel.h"

Output::Output()
{
}

Output::Output(uint8_t _card, uint8_t _io)
{
	Init(_card,  _io);
}

Output::~Output()
{
}

void Output::Init(uint8_t _card, uint8_t _io)
{
	m_iCard = _card;
	m_iio = _io;
	m_iState = LOW;

	m_iID = m_iCard*100 + m_iio;

	if(ConnectingStuff::GetCARDID() == m_iCard) pinMode(m_iio, OUTPUT);
}

// force la sortie a  une valeur
void Output::Set(uint8_t _state)
{
	if(m_iState != _state)
	{
		m_iState = _state;

		if(m_iState != LOW && m_iState != 0)
		{
			m_OnTimer.Reset();
		}
		else
		{
			m_OnTimer.Stop();
		}

		// Si la sortie est sur cette carte on la met a jour
		if(ConnectingStuff::GetCARDID() == m_iCard)
		{
			if(m_iState == HIGH && m_iState == LOW)
			{
				digitalWrite(m_iio, m_iState);
			}
			else
			{
				analogWrite(m_iio, m_iState);
			}
		}
		else
		{
			// TODO Traitement si la sortie est sur une autre carte
		}
	}
}

uint8_t Output::Read(void)
{
	return m_iState;
}

uint8_t Output::ReadReal(void)
{
	if(ConnectingStuff::GetCARDID() == m_iCard)
	{
		digitalRead(m_iio);
	}
	else
	{
		return m_iState;
	}
}

unsigned long Output::GetOnTime(void)
{
	return m_OnTimer.GetTotalTime();
}

void Output::Toogle()
{
	if(m_iState == HIGH)
	{
		Set(LOW);
	}
	else
	{
		Set(HIGH);
	}
}

uint8_t Output::GetCardID()
{
	return m_iCard;
}

int Output::GetID()
{
	return m_iID;
}

