#include <ConnectingStuff.h>
 
// Definition d'un interrupteur sur l'io n°2
Switch interrupteur(2,"Salon");
 
void setup()
{
  Serial.begin(9600);
  Serial.println("Start...");
}
 
void loop()
{
  // lecture de l'état de l'io et mise à jour de l'interrupteur
  interrupteur.Update();
 
  // Récupération de l'état de l'interrupteur :
  // Appuis court, long ou relaché.
  SwitchState state = interrupteur.GetState();
 
  // Si appuis court, affichage du nombre d'appuis
  if(state == PRESS)
  {
    Serial.print("Nb Clic : ");
    Serial.println(interrupteur.GetNbClic());
  }
  // Si appuis long, affichage du temps d'appuis
  if(state == LONGPRESS)
  {
    Serial.print("LongPress Time : ");
    Serial.println(interrupteur.GetLongPressTime());
  }
 
  delay(10);
}