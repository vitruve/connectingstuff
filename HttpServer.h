/*
 * connectingStuff, Arduino Based Home Automation
 * http://connectingstuff.net/blog/
 *
 * Copyright (C) 2012 olivier.lebrun@gmail.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
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
		void Listen(word = 0);

		char* GetArg(char *str = NULL);

};
#endif

#endif
