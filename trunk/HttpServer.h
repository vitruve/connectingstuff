/*
Output.h - Library for domotic ouput management
  Created by Lebrun Olivier 05/08/2010
*/
#ifndef HttpServer_h
#define HttpServer_h

#include "Kernel.h"

#ifdef ETH

#include "Arduino.h"
#include "../ethercard/EtherCard.h"

#define DATE_BUFFER_SIZE 30
#define CMDBUF 50

#define API_URL "/abha++/index.php?p=services/http2xpl"

typedef void (*CallbackType)(char*);

struct Page
{
	String page;
	CallbackType func;
};

class HttpServer
{
	protected:
		BufferFiller bfill;

		CallbackType m_defaultPage;
		Page m_callBack[10];
		int m_iCallBackIndex;

		void http200ok();
		void http404();
		char* ParseUrl(char*);

	public:
		HttpServer();
		~HttpServer();

		void AddPage(String,CallbackType);
		void AddDefaultPage(CallbackType);
	
		void Print(int);
                void Println(int);
		void Print(char*);
		void Println(char*);
		void Listen(word);

		char* GetArg(char *str = NULL);

};
#endif

#endif
