#include <ConnectingStuff.h>
 
Switch interSalon;
Light lumiereSalon(1, 12, "Salon");
Light lumiereSam(1, 13, "Sam");
 
void setup()
{
  // Définit l'ID unique de la carte sur le réseau
  ConnectingStuff::SetCARDID(1, "carte1");
 
  interSalon.Init(2, "Salon/Sam");
 
  interSalon.LinkModule(&lumiereSalon, 1, 0, ONOFF);
  interSalon.LinkModule(&lumiereSalon, 0, 2000, OFF);
  interSalon.LinkModule(&lumiereSam, 0, 2000, OFF);
}
 
void loop()
{
    interSalon.Update();
}