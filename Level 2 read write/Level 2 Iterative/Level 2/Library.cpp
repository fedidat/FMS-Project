#include "Library.h"
#include "HashValue.h"
using namespace std;

void throwErr(char* msg, bool pError)
{
	char* err = new char[strlen(msg) + pError?strlen(strerror(errno)) + 2 : 0 + 3];
	strcpy(err, msg);
	if(pError)
	{
		strcat(err, ": ");
		strcat(err, strerror(errno));
	}
	strcat(err,".\n");
	throw exception(err);
}

ostream& operator<<(ostream& out, const HashFuncIDcode func)
{
    const char* s = 0;
#define PROCESS_VAL(p) case(p): s = #p; break;
    switch(func)
	{
        PROCESS_VAL(DUMMYfunc);     //this translates HashFuncIDcodes in letters. Not the shortest method (array takes 2 lines), but the most systemic.
        PROCESS_VAL(MODHfunc);
        PROCESS_VAL(MULTHfunc);
        PROCESS_VAL(RSHfunc);
        PROCESS_VAL(JSHfunc);
        PROCESS_VAL(PJWHfunc);
        PROCESS_VAL(ELFHfunc);
        PROCESS_VAL(BKDRHfunc);
        PROCESS_VAL(SDBMHfunc);
        PROCESS_VAL(DJBHfunc);
        PROCESS_VAL(APHfunc);
    }
#undef PROCESS_VAL
    return out << s;
}