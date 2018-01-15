#include "Library.h"
#include "HashValue.h"
using namespace std;

void throwErr(char* msg, bool pError)
{
	char* erro = new char[strlen(msg) + pError?strlen(strerror(errno)) + 2 : 0 + 3];
	strcpy(erro, msg);
	if(pError)
	{
		strcat(erro, ": ");
		strcat(erro, strerror(errno));
	}
	strcat(erro,".\n");
	throw exception(erro);
}