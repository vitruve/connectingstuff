/*
 * connectingStuff, Arduino Based Home Automation
 * http://connectingstuff.net/blog/
 *
 * Copyright (C) 2012 olivier.lebrun@gmail.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "Switch.h"
#include "Kernel.h"

#ifdef XPL
	extern xPL xpl;
#endif

Switch::Switch()
{
	m_iLongPressDelay = DEFAULT_LONG_PRESS_DELAY;
	m_type = SWITCH;
}

Switch::Switch(int _io, char* _name, int _maxModuleToManage, int _longPressDelay)
{
	Init(_io, _name, _maxModuleToManage, _longPressDelay);
}

Switch::~Switch()
{
}

void Switch::Init(int _io, char* _name, int _maxModuleToManage, int _longPressDelay)
{
	m_Input.Init(_io);

	m_type = SWITCH;
	m_iID = ConnectingStuff::GetCARDID()*100 + _io;
	memcpy(m_name, _name, 8);

	m_iNbClic = 0;
	m_bLongPress = false;

	m_Input.SetInternalPullupResistor();

	m_oAttachedModule = (ConfigModule*)malloc ( _maxModuleToManage * sizeof(ConfigModule) );

	m_iAttachedModuleIndex = 0;
	m_bAsConfigOnMoreThan1Clic = false;
}

/// Lie une sortie a  une entree
/// nbClic : nb de "clic"
/// time : duree
/// onOff : la sortie doit etre activer, desactiver ou les deux
void Switch::LinkModule(Module* _module, uint8_t _nbClic, int _time, Statut _onOff)
{
	ConfigModule config;

	config.nbClic = _nbClic;
	config.time = _time;
	config.onOff = _onOff;
	config.emitter = this;
	config.receiver = _module;
	m_oAttachedModule[m_iAttachedModuleIndex++] = config;

	if(_nbClic > 1)
		m_bAsConfigOnMoreThan1Clic = true;
}

SwitchState Switch::GetState()
{
	SwitchState state;

	if(m_Input.GetState() == HIGH) state = RELEASE;
	else
	{
		if(m_bLongPress) state = LONGPRESS;
		else state = PRESS;

		char str[50];
		sprintf(str,"Switch%d:%d", m_iID, state);
		ConnectingStuff::Debug(str);
	}

	return state;
}

int Switch::GetLongPressTime()
{
	if(m_bLongPress)
	{
		return (int)m_PressTimer.GetTotalTime();
	}
	else return 0;
}

uint8_t Switch::GetNbClic()
{
  return m_iNbClic;
}

void Switch::Update()
{
	// Recupre l'état de l'io
	m_Input.Read();

	// Un changement d'état est détecté
	if(m_Input.StateChange())
	{
		// Un appuis sur l'interrupteur est détecté : on démarre le timer de pression
		if(m_Input.GetState() == LOW)
		{
			m_PressTimer.Reset();
			m_iNbClic = 0;
		}

		// l'interrupteur vient d'etre relaché
		else
		{
			// Si un appuis long vient d'etre relaché
			if(m_bLongPress == true)
			{
				// TODO Traitement appuis long

				m_bLongPress = false;
			}
			// Sinon, on incrémente le nombre de pressions de l'interrupteur
			// et on met a  jour le timer du dernier relaché
			else
			{
				SendStatus();

				++m_iNbClic;
				m_ReleaseTimer.Reset();
			}
		}
	}
	else
	{
		// L'interrupteur est en position relaché et
		// le temps max entre deux appuis/relaché est écoulé (DEFAULT_LONG_PRESS_DELAY est la duree max entre deux appuis/relaché)
		if(m_Input.GetState() == HIGH && m_ReleaseTimer.GetTotalTime() > DEFAULT_LONG_PRESS_DELAY)
		{
			// Un ou plusieurs appuis court on été détecté
			if(m_iNbClic > 0)
			{
				// Traitement appuis court

				for(uint8_t i = 0; i < m_iAttachedModuleIndex; i++)
				{
					//Serial.print(m_iNbClic);
					//Serial.print(",");
					//Serial.println(m_oAttachedModule[i].nbClic);

					if(m_oAttachedModule[i].nbClic > 0 && m_iNbClic == m_oAttachedModule[i].nbClic)
					{
						RunModuleAction(m_oAttachedModule[i]);
					}
				}
			}

			//m_iNbClic = 0;
		}

		// L'interrupteur est en position appuyé
		if(m_Input.GetState() == LOW)
		{
			// Un appuis long est détecté
			if(m_PressTimer.GetTotalTime() > DEFAULT_LONG_PRESS_DELAY)
			{
				m_bLongPress = true;

				// Traitement appuis long

				for(uint8_t i = 0; i < m_iAttachedModuleIndex; i++)
				{
					if(m_oAttachedModule[i].time > 0 && m_PressTimer.GetTotalTime() > m_oAttachedModule[i].time)
					{
						RunModuleAction(m_oAttachedModule[i]);

						m_PressTimer.Reset();
					}
				}
			}
		}
	}

	GetState();
}

void Switch::RunModuleAction(ConfigModule _config)
{
	_config.receiver->Action(&_config);
}

void Switch::Action(void*){}

char* Switch::ToJson()
{
	char str[150];
	sprintf(str,"{\"type\":\"switch\",\"id\":\"%d\",\"name\":\"%s\",\"pin\":\"%d\",\"value\":\"%d\"}", m_iID, m_name, m_iID, (int)GetState());
	return str;
}

void Switch::SendStatus()
{
#ifdef XPL
	xPL_Message msg;

	msg.hop = 1;
	msg.type = XPL_TRIG;

	msg.SetTarget_P(PSTR("*"));
	msg.SetSchema_P(PSTR("sensor"), PSTR("basic"));

	char id[20];
	sprintf(id,"%d",m_iID);

	msg.AddCommand("device",id);
	msg.AddCommand_P(PSTR("type"),PSTR("input"));
	msg.AddCommand_P(PSTR("current"),PSTR("pulse"));

	xpl.SendMessage(&msg);
#endif
}
