#include "stdafx.h"
#include "Library.h"
#include "HashValue.h"
using namespace std;

void throwErr(char* msg, bool pError)
{
	char buff[64];
	strerror_s(buff, errno);
	char* erro = new char[strlen(msg) + 64];
	strncpy_s(erro, strlen(msg) + 64, msg, strlen(msg));
	if(pError)
	{
		strncat_s(erro, strlen(msg) + 64, ": ", 3);
		strncat_s(erro, strlen(msg) + 64, buff, 64);
	}
	strncat_s(erro, strlen(msg) + 64, ".\n", 2);
	throw exception(erro);
}

void MarshalString ( String ^ s, string& os ) {
   using namespace System::Runtime::InteropServices;
   const char* chars = 
      (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(System::IntPtr((void*)chars));
}
void getDate(char* date)
{
	char buff[12];
	_strdate_s(buff);
	memcpy(date, buff, 10);
	memcpy(date, &buff[3], 2);
	memcpy(&date[3], buff, 2);
}