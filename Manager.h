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
#ifndef Manager_h
#define Manager_h

#include "Arduino.h"
#include "Kernel.h"
#include "Module.h"
#include "Switch.h"

struct Chainlist
{
	Module* module;
	Chainlist* pSuivant;
};

class Manager
{
	protected:
		Chainlist* DelModule(Chainlist*, int);

	public:
		Manager();
		~Manager();

		Chainlist *liste;

		void AddModule(Module*);
		void DelModule(int);
		Module* FindModule(int);
		char* ToJson();
		void Update();
};

extern Manager manager;

#endif
