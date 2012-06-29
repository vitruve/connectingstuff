/*
 * connectingStuff, Arduino Based Home Automation
 * http://connectingstuff.net/blog/
 *
 * This code is parsing a xPL message stored in 'received' buffer
 * - isolate and store in 'line' buffer each part of the message -> detection of EOL character (DEC 10)
 * - analyse 'line', function of its number and store information in xpl_header memory
 * - check for each step if the message respect xPL protocol
 * - parse each command line
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

#ifndef Switch_h
#define Switch_h

#include "Arduino.h"
#include "Enum.h"
#include "Timer.h"
#include "Input.h"
#include "Module.h"

#ifdef XPL
#include "../xPL/xPL.h"
#endif

#define DEFAULT_LONG_PRESS_DELAY 300

struct ConfigModule
{
	uint8_t nbClic;
	int time;
	Statut onOff;
	Module* emitter;
	Module* receiver;
};

class Switch : public Module
{
	protected:
		Input m_Input;

		int m_iLongPressDelay;									// Delai pour considerer un appuis comme long

		Timer m_PressTimer;										// Timer état maintenu appuyé
		Timer m_ReleaseTimer;										// Timer état relaché

		uint8_t m_iNbClic;												// nombre de pressions sur l'interrupteur
		bool m_bLongPress;										// appuis long en cours

		uint8_t m_iAttachedModuleIndex;
		ConfigModule *m_oAttachedModule;

		bool m_bAsConfigOnMoreThan1Clic;				// Permet d'indiquer si aucun module lié n'utilise plus de une pression
																				// Sert a eliminer la latence de m_iLongPressDelay seconde apres la premiere pression

		void RunModuleAction(ConfigModule);

	public:
		Switch();
		Switch(int, char*, int = 1, int = DEFAULT_LONG_PRESS_DELAY);
		~Switch();

		void Init(int, char*, int = 1, int = DEFAULT_LONG_PRESS_DELAY);

		void Update();													// Mise �  jour
		SwitchState GetState();										// Retourne l'etat courante de l'interrupteur
		int GetLongPressTime();									// Retourne le temps en milliseconde depuis lequel l'interrupteur est appuyé
		uint8_t GetNbClic();                     						// Retourne le nb de d'appuis sur l'interrupteur

		void LinkModule(Module*, uint8_t, int, Statut );

		void Action(void*);
		char* ToJson();
		void SendStatus();
};

#endif
