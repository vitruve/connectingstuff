#include <ConnectingStuff.h>
#include <EtherCard.h>

HttpServer server;

Switch interSalon;
Light lumiereSalon(1,13,"Salon");

void setup()
{
  // Definition de l'ID de la carte
  ConnectingStuff::SetCARDID(1, "carte1");    
  
  // Init du serveur HTTP
  uint8_t mymac[6] = { 0x54,0x55,0x58,0x10,0x00,0x11 };
  uint8_t myip[4] = { 192,168,1,133 };
  uint8_t gwip[4] = { 192,168,1,240};
  uint8_t broadcast[4] = { 192,168,1,255};
  EthernetConf::Init(mymac, myip, gwip, broadcast);
  
  // Definition des pages web à servir
  server.AddPage("add", &AddModule);
  server.AddPage("del", &DelModule);
  server.AddPage("reset", &Reset);
  server.AddDefaultPage(&Default);
  
  // Init des modules
  interSalon.Init(7, "Salon");
  interSalon.LinkModule(&lumiereSalon, 1, 0, ONOFF);
  
  manager.AddModule(new Light(1, 12, "Sam"));
  manager.AddModule(&interSalon);
  manager.AddModule(&lumiereSalon);
}

void loop()
{
  // Attend une requette HTTP
  server.Listen(); 
  manager.Update();
}

///////////////////////////////////////////////////////////////////////////////
// Page par défaut
void Default(char* arg1)
{
  // Si aucun argument, on affiche l'état des modules en Json
  if(arg1 == NULL)
  {
    server.Print(manager.ToJson());
  }
  else
  {
    // Recherche du module demandé
    Module* module = manager.FindModule(atoi(arg1));
  
    if(module != NULL)
    {   
      bool flag = false;
      
      // En fonction du type de module on lance une action
      switch(module->GetType())
      {
        case LIGHT:
          {
            flag = true;
            Light* l = (Light*)module;
            char* value = server.GetArg();
            if(value != NULL)
            {
              l->Set(atoi(value));
            }
            server.Print(l->ToJson());
            break;
          }
        default:
          flag = false;
      }
      
      // Puis on affiche l'état du module en Json
      if(!flag) server.Print(module->ToJson());
    }
    else
    {
      // Aucun module trouvé, on suppose que l'utilisateur veut forcer l'état d'une pin.
      // On tente de basculer la pin correspondante
      char* value = server.GetArg();
      digitalWrite(atoi(arg1), atoi(value));
      server.Print("Force pin ");
      server.Print(arg1);
      server.Print(" to value ");
      server.Println(value);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
// Ajout d'un module
void AddModule(char* arg1)
{
  char* type = server.GetArg();
  
  if(memcmp(type, "light", 5) == 0)
  {
    int card = atoi(server.GetArg());
    int pin  = atoi(server.GetArg());
    char* name = server.GetArg(); 
    manager.AddModule(new Light(card,pin,name));

    server.Print(PSTR("Adding light module on card "));
    server.Print(card);
    server.Print(PSTR(" and pin "));
    server.Print(pin);
    server.Print(PSTR(" and name ");
    server.Println(name);
  }
}

///////////////////////////////////////////////////////////////////////////////
// Suppression d'un module
void DelModule(char* arg1)
{
  int idModule = atoi(server.GetArg());
  manager.DelModule(idModule);
  
  server.Print(PSTR("Deleting module"));
  server.Println(idModule);
}

///////////////////////////////////////////////////////////////////////////////
// Reset du programme
void Reset(char* arg1)
{
  ConnectingStuff::SoftReset();
}