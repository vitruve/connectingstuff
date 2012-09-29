#include <ConnectingStuff.h>
 
// Definition d'un interrupteur sur l'io n°2
Teleinfo teleinfo(A2,"Teleinfo");
unsigned int total;
 
void setup()
{
  Serial.begin(9600);
  Serial.println("Start...");
  
  // Définit l'ID unique de la carte sur le réseau
  ConnectingStuff::SetCARDID(1, "carte1");
  
  // Le seuil en dessous duquel la partie noire du disque est détecté avec fiabilité
  // à tester sur plusieurs tours avec l'affichage de la console
  teleinfo.SetThreshold(400);
  
  // Valeur "C" du compteur à roue (inscrit dessus)
  // C'est le nombre de w/h consommés pour un tour de roue
  teleinfo.SetCompteurC(6.6);
  
  // Permet de préinitialisé le compteur HP avec la valeur lue sur le compteur
  teleinfo.SetHCHP(1000);
}
 
void loop()
{
  // lecture de l'état de l'io et mise à jour de l'interrupteur
  teleinfo.Update();
 
 if(total != teleinfo.GetTotal())
 {
  total = teleinfo.GetTotal();
   
  Serial.print("INST: ");
  Serial.print(teleinfo.GetInst());
  Serial.print("w/h, TOTAL: ");
  Serial.println(total);
 }
}