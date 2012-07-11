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

#include "Manager.h"

Manager::Manager()
{
	liste = NULL;
}

Manager::~Manager()
{
}

void Manager::AddModule(Module* _module)
{	
	ConnectingStuff::Debug("Add module");

	Chainlist* Nouveau = (Chainlist*)malloc(sizeof(Chainlist));

	Nouveau->module = _module;
	Nouveau->pSuivant = liste;
	liste = Nouveau;
}

void Manager::DelModule(int _ID)
{
	liste = DelModule(liste, _ID);
}

Chainlist* Manager::DelModule(Chainlist* _liste, int _ID)
{
	/* Liste vide, il n'y a plus rien à supprimer */
	if(_liste == NULL)
		return NULL;

	/* Si l'élément en cours de traitement doit être supprimé */
	if(_liste->module->GetID() == _ID)
	{
		/* On le supprime en prenant soin de mémoriser
		l'adresse de l'élément suivant */
		Chainlist* tmp = _liste->pSuivant;
		delete _liste;
		/* L'élément ayant été supprimé, la liste commencera à l'élément suivant
		pointant sur une liste qui ne contient plus aucun élément ayant la valeur recherchée */
		tmp = DelModule(tmp, _ID);
		return tmp;
	}
	else
	{
		/* Si l'élement en cours de traitement ne doit pas être supprimé,
		alors la liste finale commencera par cet élément et suivra une liste ne contenant
		plus d'élément ayant la valeur recherchée */
		_liste->pSuivant = DelModule(_liste->pSuivant, _ID);
		return _liste;
	}
}

Module* Manager::FindModule(int _ID)
{
	char debug[50];
	Chainlist* _liste = liste;

	while (_liste != NULL)
	{
		sprintf(debug,"%d",_liste->module->GetID());
		Serial.print("Scan module : ");
		Serial.println(debug);

		if(_liste->module->GetID() == _ID)
		{
			Serial.println("Found");
			return _liste->module;
		}

		_liste = _liste->pSuivant;
	}

	Serial.println("Not found");
	return NULL;
}

void Manager::Update()
{
	Chainlist* _liste = liste;

	while (_liste != NULL)
	{
		if(_liste->module->GetType() == SWITCH)
		{
			Switch* s = (Switch*)_liste->module;
			s->Update();
		}
		_liste = _liste->pSuivant;
	}
}

char* Manager::ToJson()
{
	char str[400];
	String json ="{\"Module\": [";

	int i = 0;
	Chainlist* _liste = liste;
	while (_liste != NULL)
	{
		if(++i == 1)
		{
			//sprintf(str,"%s", _liste->module->ToJson());
			json += _liste->module->ToJson();
		}
		else
		{
			//sprintf(str,"%s,%s", str, _liste->module->ToJson());
			json += ",";
			json += _liste->module->ToJson();
		}

		_liste = _liste->pSuivant;
	}

	json += "]}";
	json.toCharArray(str, 400);
	return str;
}

Manager manager;
