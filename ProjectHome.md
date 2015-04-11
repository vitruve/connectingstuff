[ConnectingStuff](http://connectingstuff.net/blog/connectingstuff/) est une librairie permettant d'utiliser une ou plusieurs cartes Arduino comme "contrôleur domotique".
<br>
<br>Quelques caractéristiques en vrac:<br>
<ul><li>Spécialiser des io en module: interrupteurs, bouton poussoir, lumières, variateurs, compteurs…<br>
</li><li>Association des modules émetteurs (interrupteurs, capteurs ...) et récepteurs (lumières ...) comme on appaire des modules Chacon par exemple.<br>
</li><li>Pilotage des io/modules en Http (REST Like interface)<br>
</li><li>Notification en xPL (<a href='http://connectingstuff.net/blog/xpl-arduino/'>xPL.Arduino</a>) des changements d’états des modules configurés<br>
</li><li>Réception statut des sondes de température 1wire<br>
</li><li>...</li></ul>

Futures proche :<br>
<ul><li>Pilotage des sorties et modules d’une carte Arduino à partir d’une autre carte<br>
</li><li>Pilotage des io/Modules en xPL<br>
</li><li>Notification Http des changements d’états des modules configurés<br>
</li><li>Pilotage et réception des modules homeeasy (chacon, …)<br>
</li><li>Identification de badges RFID<br>
</li><li>Réception statut des sondes Oregon<br>
</li><li>Réception Téléinfo<br>
</li><li>...</li></ul>

Cette librairie dépend des librairies suivantes (selon les fonctions utilisées):<br>
<ul><li><a href='http://connectingstuff.net/blog/xpl-arduino/'>xPL.Arduino</a> pour l'envoi/réception des messages xPL.<br>
</li><li><a href='https://github.com/jcw/ethercard'>ethercard</a> pour le réseau (nécessite un shield ethernet à base de ENC28J60)<br>
</li><li><a href='http://www.arduino.cc/playground/Learning/OneWire/'>Onewire</a> et <a href='http://milesburton.com/Dallas_Temperature_Control_Library'>DallasTemperature</a>