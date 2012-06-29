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
