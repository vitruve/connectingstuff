#include "HttpServer.h"

#ifdef ETH
HttpServer::HttpServer()
{
	m_iCallBackIndex = 0;
	m_defaultPage = NULL;

}

HttpServer::~HttpServer()
{
}

void HttpServer::AddPage(String _page, CallbackType _callback)
{
	Page nouvellePage;
	nouvellePage.page = _page;
	nouvellePage.func = _callback;

	m_callBack[m_iCallBackIndex++] = nouvellePage;
}

void HttpServer::AddDefaultPage(CallbackType _callback)
{
	m_defaultPage = _callback;
}

void HttpServer::http200ok()
{
	bfill.emit_p(PSTR(
		"HTTP/1.0 200 OK\r\n"
		"Content-Type: text/html\r\n"
		"Pragma: no-cache\r\n"
		"\r\n"));
}

void HttpServer::http404()
{
	bfill.emit_p(PSTR(
		"HTTP/1.0 404 OK\r\n"
		"Content-Type: text/html\r\n"
		"\r\n404"));
}

char* HttpServer::ParseUrl(char *str)
{
  int8_t r=-1;
  int8_t i = 0;
  int index = 4;
  int index1 = 0;
  int plen = 0;
  char ch = str[index];
  char clientline[CMDBUF];
  while( ch != ' ' && index < CMDBUF)
  {
    clientline[index1++] = ch;
    ch = str[++index];
  }
  clientline[index1] = '\0';

  // convert clientline into a proper
  // string for further processing
  String urlString = String(clientline);

  // extract the operation
  String op = urlString.substring(0,urlString.indexOf(' '));

  // we're only interested in the first part...
  urlString = urlString.substring(urlString.indexOf('/'), urlString.indexOf(' ', urlString.indexOf('/')));

  // put what's left of the URL back in client line
  urlString.toCharArray(clientline, CMDBUF);

  return clientline;
}

char* HttpServer::GetArg(char *str)
{
  static char clientline[CMDBUF];

  if(str != NULL)
  {
	  sprintf(clientline,"%s",ParseUrl(str));
	  return strtok(clientline,"/");
  }
  else
  {
	  return strtok(NULL,"/");
  }
}


void HttpServer::Print(int _integer)
{
	char  tmp[50];
	itoa(_integer, tmp, 50);
	Print(tmp);
}

void HttpServer::Println(int _integer)
{
        char  tmp[50];
        itoa(_integer, tmp, 50);
        Println(tmp);
}

void HttpServer::Print(char* str)
{
	bfill.emit_p(PSTR("$S"), str);
}

void HttpServer::Println(char* str)
{
	bfill.emit_p(PSTR("$S\n<br>"), str);
}

void HttpServer::Listen(word len)
{
	bool pageFound = false;

	// read packet, handle ping and wait for a tcp packet:
	if(len == 0)
	{
		len = ether.packetReceive();
	}

	word pos = ether.packetLoop(len);

	if (pos)
	{
		bfill = ether.tcpOffset();
	    char* data = (char *) Ethernet::buffer + pos;

	    char* arg1 = GetArg(data);
	    //String page = String(arg1);


	    for(int i=0;i<m_iCallBackIndex;i++)
	    {
	    	if (m_callBack[i].page == String(arg1))
			{
	    		http200ok();
				m_callBack[i].func(arg1);
				ether.httpServerReply(bfill.position());
				pageFound = true;
			}
	    }

	if(!pageFound)
	{
      if(m_defaultPage != NULL)
      {
    	 http200ok();
    	 m_defaultPage(arg1);
      }
      else
      {
    	  http404();
      }
	}
	    ether.httpServerReply(bfill.position());
	}
}
#endif
