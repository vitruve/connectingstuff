#include <ConnectingStuff.h>

// Définition d'une sortie
Input entree;
Output sortie;

void setup()
{
  // Définit l'ID unique de la carte sur le réseau
  ConnectingStuff::SetCARDID(1, "carte1");
  
  // Initialisation de l'entrée 2
  entree.Init(2);
  entree.SetInternalPullupResistor();
  
  // Initialisation de la sortie de la carte 1, io 13
  sortie.Init(1,13);
}
 
void loop()
{
  entree.Read();
  
  // Bascule la sortie à chaque changement d'état de l'entrée
  if(entree.StateChange())
  {
    sortie.Toogle();
  }
}