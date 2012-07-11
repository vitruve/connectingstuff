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

#ifndef Module_h
#define Module_h

#include "Arduino.h"
#include "Timer.h"

enum Type {SWITCH = 0, LIGHT = 1, DIMMER = 2};

class Module
{
        protected:
                int m_iID;
                Type m_type;
                char m_name[16];

        public:
                //Module(void);
                //virtual ~Module(void);
                virtual void Action(void*);
                virtual char* ToJson();
                virtual void SendStatus();

                int GetID()
                {
                        return m_iID;
                }

                char* GetName()
                {
                        return m_name;
                }

                void SetName(char* _name)
                {
                        strcpy(m_name, _name);
                }

                Type GetType()
                {
                        return m_type;
                }


};
#endif
