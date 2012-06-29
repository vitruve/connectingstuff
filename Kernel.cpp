#include "Kernel.h"

static unsigned long debugTimer;
static int CARDID;
static char CARDNAME[8];
static uint8_t broadcastAddr[4];
static const char* VERSION = "0.1";

#ifdef XPL
	extern xPL xpl;
#endif

#ifdef ETH
	extern byte Ethernet::buffer[BUFFER_SIZE];
#endif

#ifdef LCD
	LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#endif

#ifdef XPL
void ConnectingStuff::InitXpl(xPLSendExternal _callbackSend, xPLAfterParseAction _callbackAfter)
{
	xpl.SendExternal = _callbackSend;
	xpl.AfterParseAction = _callbackAfter;
	xpl.Begin("xpl", "arduino", "domogik");
	xpl.hbeat_interval = 5;
}
#endif

void ConnectingStuff::SetCARDID(uint8_t _id, char* _name)
{
	CARDID = _id ;
	strcpy(CARDNAME, _name);

	char idStr[12];
	itoa(_id,idStr,12);
	Serial.print("Card ID: ");
	Serial.println(idStr);

#ifdef LCD
	lcd.begin(16, 4);
	ConnectingStuff::PrintLCD(0,15,idStr);
#endif
}

uint8_t ConnectingStuff::GetCARDID()
{ return CARDID; }

char* ConnectingStuff::GetCARDNAME()
{ return CARDNAME; }

const char* ConnectingStuff::GetVERSION()
{ return VERSION; }

void ConnectingStuff::SoftReset()
{
	Serial.println("Reset"); 
	asm volatile ("  jmp 0"); 
}

void ConnectingStuff::PrintLCD(int _r, int _c, int _value)
{
#ifdef LCD
	char str[12];
	itoa(_value,str,12);
	ConnectingStuff::PrintLCD(_r,_c,str);
#endif
}

void ConnectingStuff::PrintLCD(int _r, int _c, char* _value)
{
#ifdef LCD
	lcd.setCursor(_c,_r);
	lcd.print(_value);
#endif
}

void ConnectingStuff::Debug(int _value)
{
	char str[12];
	itoa(_value,str,12);
	ConnectingStuff::Debug(str);
}

void ConnectingStuff::Debug(char* _value)
{
	debugTimer = millis();

	Serial.println(_value);
	ConnectingStuff::PrintLCD(3,0,_value);

#ifdef LCD
	int len = strlen(_value);
	if(len < 16)
	{
		for(int i = len; i < 16; i++)
		{
			lcd.setCursor(i,3);
			lcd.print(" ");
		}
	}
#endif
}

void ConnectingStuff::DebugShowTime()
{
	uint8_t offset;
	int time = (millis() - debugTimer) / 1000;

	if(time < 10) offset = 0;
	else if(time < 100) offset = 1;
	else if(time < 1000) offset = 2;
	else if(time < 10000) offset = 3;
	else if(time < 100000) offset = 4;

#ifdef LCD
	lcd.setCursor(15-offset,3);
	lcd.print((millis() - debugTimer) / 1000);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ETH
void EthernetConf::Init(uint8_t* _mac, uint8_t* _ip, uint8_t* _gwip, uint8_t* _broadcastAddr)
{
	if (ether.begin(sizeof Ethernet::buffer, _mac) == 0)
	{
	    Serial.println( "Failed to access Ethernet controller");
	    ConnectingStuff::SoftReset();
	}

	ether.staticSetup(_ip, _gwip);
	EtherCard::copyIp(broadcastAddr, _broadcastAddr);

    Serial.println("Ethernet controller ready");
}

uint8_t* EthernetConf::getBroadcastAddr()
{
	return broadcastAddr;
}
#endif
