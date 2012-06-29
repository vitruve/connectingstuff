/*
Output.h - Library for domotic ouput management
  Created by Lebrun Olivier 05/08/2010
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
