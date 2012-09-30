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

#ifndef Kernel_h
#define Kernel_h

// Active/Desactive les parties du code non necessaires
// A voir pour faire ca directement dans le sketch ... mais cela
// semble poser problème avec l'environnement arduino
#undef LCD
#define ETH
#undef XPL
#undef ONEWIRE

#include "Arduino.h"

#ifdef LCD
#include "../LiquidCrystal/LiquidCrystal.h"
#endif

#ifdef ETH
#include "../ethercard/EtherCard.h"
#define BUFFER_SIZE 700
#endif

#ifdef XPL
#include "../xPL/xPL.h"
#endif

class ConnectingStuff 
{
	public:

	static void SetCARDID(uint8_t, char*);
	static uint8_t GetCARDID();
	static char* GetCARDNAME();
	static const char* GetVERSION();
	static void SoftReset();

	static void PrintLCD(int, int, int);
	static void PrintLCD(int, int, char*);
	static void Debug(int);
	static void Debug(char*);

	static void DebugShowTime();
};

#ifdef ETH
class EthernetConf
{
	public:

	static void Init(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint8_t _csPin =8);
	static uint8_t* GetBroadcastAddr();
};
#endif

#endif

