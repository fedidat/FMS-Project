#include <iostream>
#include <strstream>
#include <cstring>
#include <cmath>
#include "Library.h"
using namespace std;

#include "HashValue.h"

#define TRUE  1
#define FALSE 0

int divisible(int num, int divisor)
{
   if ((num % divisor) == 0)
     return  TRUE;
   else
     return  FALSE;	   
};

union {
 unsigned int u;
 int i;
} hashval;
//===========================================

HashValue::HashValue() 
{
		Kval.i   = -1;
		Hval     = -1;
		HfuncID  = DUMMYfunc;
		Hvalmax  = -1;
};

HashValue::HashValue(int highest_hash_val)
{
		Kval.i   = -1;
		Hval     = -1;
		HfuncID  = DUMMYfunc;
		Hvalmax  = genprime(highest_hash_val);
};
//===========================================
int HashValue::maxHval()
{
   return (Hvalmax);
}

//===========================================

int newprime(int currval, int *primelst, int imax)
{
   int maxval;
	int isprime;
	int i;
	int new_imax;
	
   maxval = (int) floor((float)currval/2.0) + 1;
   isprime = TRUE;
   for (i = 0; primelst[i] <= maxval; i++)
   {
	  if (divisible(currval,primelst[i])) 
	  {
       isprime = FALSE;
       break;
	  }
   }       
   if (isprime)
   {
	  primelst[++imax] = currval;
   }
	new_imax = imax;
	return (new_imax);	       
}

int HashValue::genprime(int maxprime)
{
    int *fullprimelst;
	  
    if (maxprime <= 19) 
	   fullprimelst = new int [19];
    else
      fullprimelst = new int [maxprime];
      
    int *primelst = &fullprimelst[2];
    
    fullprimelst[0] = 1;
    fullprimelst[1] = 2;
    
    primelst[0] = 3;
    primelst[1] = 5;
    primelst[2] = 7;
    primelst[3] = 11;
    primelst[4] = 13;
    primelst[5] = 17;
    primelst[6] = 19; 

    int imax, currval;
    int i;
    int retprimeval;

    if (maxprime < 19) 
	 {
	   imax = 0;
	   for (i = 0; primelst[i] <= maxprime; imax = i, i++);
      if (primelst[imax] != maxprime)
		{
			  imax++;
      }
	 }
	 else 
	 {
      for (imax = 6, currval = 23; currval <= maxprime; currval += 2)
      {
	     imax = newprime(currval, primelst, imax);	    
      }
		if (maxprime != primelst[imax])
		{
		  int new_imax;
		  do 
		  { 
	       new_imax = newprime(currval, primelst, imax);
			 currval += 2;
		  } while (new_imax == imax);
		  imax = new_imax;
		} 
	 }    
    retprimeval = primelst[imax];
	 
	 primelst = NULL;
	 delete [] fullprimelst;
	 
	 return retprimeval;
}
//===========================================

int HashValue::MODH(int key)
{
   HfuncID = MODHfunc;
   Kval.i = key;
	if (key < 0) key *= -1;
	Hval = key % Hvalmax;
	return (Hval);
};
int HashValue::MODH(int key, int highest_hash_val)
{
   if (highest_hash_val < 0) 
     return (-1);
   else 	
     Hvalmax = genprime(highest_hash_val); 
   return(MODH(key));
};
//===========================================

int HashValue::MULTH(int key)
{
   HfuncID = MULTHfunc;
   Kval.i = key;
   if (key < 0) key *= -1;

   float A,kA;

   A    = (float)((sqrt(5.0)-1.0)/2.0);
   kA   = (float) key * A;
   Hval = (int) floor(Hvalmax * (kA - floor(kA)));
   
   return (Hval); 
};
int HashValue::MULTH(int key, int highest_hash_val)
{
   if (highest_hash_val < 0) 
     return (-1);
   else 	
     Hvalmax = genprime(highest_hash_val); 
   return(MULTH(key));
};
//===========================================

int HashValue::RSHash(const char * strkey) 
{
   unsigned int b = 378551;
   unsigned int a = 63689;
   unsigned int hash = 0;

   for(unsigned int i = 0; i < strlen(strkey); i++)
   {
      hash = hash*a+strkey[i];
      a = a*b;
   }

   hashval.u = hash & 0x7FFFFFFF;
   if (hashval.i < 0) hashval.i *= -1;
   Hval = hashval.i % Hvalmax;

   return (Hval);
};
int HashValue::RSHash(const char * strkey, int highest_hash_val) 
{
   if (highest_hash_val < 0)
     return (-1);
   else
     Hvalmax = genprime(highest_hash_val);
   return(RSHash(strkey));
};
/* End Of RS Hash Function */
//===========================================

int HashValue::JSHash(const char* strkey)
{

   unsigned int hash = 1315423911;

   for(unsigned int i = 0; i < strlen(strkey); i++)
   {
      hash ^= ((hash << 5) + strkey[i] + (hash >> 2));
   }

   hashval.u = hash & 0x7FFFFFFF; 
   if (hashval.i < 0) hashval.i *= -1;
   Hval = hashval.i % Hvalmax;

   return (Hval);
};
int HashValue::JSHash(const char * strkey, int highest_hash_val)
{
   if (highest_hash_val < 0)
     return (-1);
   else
     Hvalmax = genprime(highest_hash_val);
   return(JSHash(strkey));
};
/* End Of JS Hash Function */
//===========================================

int HashValue::PJWHash(const char* strkey)
{
   unsigned int BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
   unsigned int ThreeQuarters    = (unsigned int)((BitsInUnignedInt  * 3) / 4);
   unsigned int OneEighth        = (unsigned int)(BitsInUnignedInt / 8);
   unsigned int HighBits         = (unsigned int)(0xFFFFFFFF) << (BitsInUnignedInt - OneEighth);
   unsigned int hash             = 0;
   unsigned int test             = 0;

   for(unsigned int i = 0; i < strlen(strkey); i++)
   {

      hash = (hash << OneEighth) + strkey[i];

      if((test = hash & HighBits)  != 0)
      {
         hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
      }
   }
    hashval.u = hash & 0x7FFFFFFF; 
    if (hashval.i < 0) hashval.i *= -1;
    Hval = hashval.i % Hvalmax;

    return (Hval);
};
int HashValue::PJWHash(const char* strkey, int highest_hash_val)
{
   if (highest_hash_val < 0)
     return (-1);
   else
     Hvalmax = genprime(highest_hash_val);
   return(PJWHash(strkey));
};
/* End Of  P. J. Weinberger Hash Function */
//===========================================

int HashValue::ELFHash(const char* strkey)
{
   unsigned int hash = 0;
   unsigned int x    = 0;

   for(unsigned int i = 0; i < strlen(strkey); i++)
   {
      hash = (hash << 4) + strkey[i];
      if((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
         hash &= ~x;
      }
   }
   hashval.u = hash & 0x7FFFFFFF; 
   if (hashval.i < 0) hashval.i *= -1;
   Hval = hashval.i % Hvalmax;

   return (Hval);
};
int HashValue::ELFHash(const char* strkey, int highest_hash_val)
{
   if (highest_hash_val < 0)
     return (-1);
   else
     Hvalmax = genprime(highest_hash_val);
   return(ELFHash(strkey));
};
/* End Of ELF Hash Function */
//===========================================

int HashValue::BKDRHash(const char* strkey)
{

   unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
   unsigned int hash = 0;

   for(unsigned int i = 0; i < strlen(strkey); i++)
   {

      hash = (hash*seed)+strkey[i];

   }
	
   hashval.u = hash & 0x7FFFFFFF; 
   if (hashval.i < 0) hashval.i *= -1;
   Hval = hashval.i % Hvalmax;

   return (Hval);
};
int HashValue::BKDRHash(const char* strkey, int highest_hash_val)
{
   if (highest_hash_val < 0)
     return (-1);
   else
     Hvalmax = genprime(highest_hash_val);
   return(BKDRHash(strkey));
};
/* End Of BKDR Hash Function */
//===========================================

int HashValue::SDBMHash(const char* strkey)
{

   unsigned int hash = 0;

   for(unsigned int i = 0; i < strlen(strkey); i++)
   {

      hash = strkey[i] + (hash << 6) + (hash << 16) - hash;

   }
	
   hashval.u = hash & 0x7FFFFFFF; 
   if (hashval.i < 0) hashval.i *= -1;
   Hval = hashval.i % Hvalmax;

   return (Hval);
};
int HashValue::SDBMHash(const char* strkey, int highest_hash_val)
{
   if (highest_hash_val < 0)
     return (-1);
   else
     Hvalmax = genprime(highest_hash_val);
   return(SDBMHash(strkey));
};
/* End Of SDBM Hash Function */
//===========================================

int HashValue::DJBHash(const char* strkey)
{
   unsigned int hash = 5381;

   for(unsigned int i = 0; i < strlen(strkey); i++)
   {
      hash = ((hash << 5) + hash) + strkey[i];
   }
   hashval.u = hash & 0x7FFFFFFF; 
   if (hashval.i < 0) hashval.i *= -1;
   Hval = hashval.i % Hvalmax;

   return (Hval);
};
int HashValue::DJBHash(const char* strkey, int highest_hash_val)
{
   if (highest_hash_val < 0)
     return (-1);
   else
     Hvalmax = genprime(highest_hash_val);
   return(DJBHash(strkey));
};
/* End Of DJB Hash Function */
//===========================================

int HashValue::APHash(const char* strkey)
{
   unsigned int hash = 0;

   for(unsigned int i = 0; i < strlen(strkey); i++)
   {
      if ((i & 1) == 0)
      {
         hash ^=((hash << 7)^strkey[i]^(hash >> 3));
      }
      else
      {
         hash ^= (~((hash << 11)^strkey[i]^(hash >> 5)));
      }
   }
   hashval.u = hash & 0x7FFFFFFF; 
   if (hashval.i < 0) hashval.i *= -1;
   Hval = hashval.i % Hvalmax;

   return (Hval);
};
int HashValue::APHash(const char* strkey, int highest_hash_val)
{
   if (highest_hash_val < 0)
     return (-1);
   else
     Hvalmax = genprime(highest_hash_val);
   return(APHash(strkey));
};
/* End Of AP Hash Function */
//===========================================

int HashValue::HashFunction(int hashfuncID, const char* strkey, int highest_hash_val)
{
   int key;
   int i;
	
   switch (hashfuncID)
   {
      case MODHfunc:
        for (i = 0, key = 0; strkey[i] != '\0'; i++)
	   key += strkey[i];
      return(MODH(key, highest_hash_val));
      case MULTHfunc: 
        for (i = 0, key = 0; strkey[i] != '\0'; i++)
	   key += strkey[i];		  
      return (MULTH(key, highest_hash_val));		
      case RSHfunc:
      return(RSHash(strkey, highest_hash_val));
      case JSHfunc:
      return(JSHash(strkey, highest_hash_val));
      case PJWHfunc:
      return(PJWHash(strkey, highest_hash_val));
      case ELFHfunc:
      return(ELFHash(strkey, highest_hash_val));
      case BKDRHfunc:
      return(BKDRHash(strkey, highest_hash_val));
      case SDBMHfunc:
      return(SDBMHash(strkey, highest_hash_val));
      case DJBHfunc:  
      return(DJBHash(strkey, highest_hash_val));
      case APHfunc:   	  
      return(APHash(strkey, highest_hash_val));
      default:
      return(-1);
   }
};
int HashValue::HashFunction(int hashfuncID, const char* strkey)
{
   int key;
   int i;
	
   switch (hashfuncID)
   {
      case MODHfunc:
        for (i = 0, key = 0; strkey[i] != '\0'; i++)
           key += strkey[i];
      return(MODH(key));
      case MULTHfunc: 
	for (i = 0, key = 0; strkey[i] != '\0'; i++)
	   key += strkey[i];		  
      return (MULTH(key));		
      case RSHfunc:
      return(RSHash(strkey));
      case JSHfunc:
      return(JSHash(strkey));
      case PJWHfunc:
      return(PJWHash(strkey));
      case ELFHfunc:
      return(ELFHash(strkey));
      case BKDRHfunc:
      return(BKDRHash(strkey));
      case SDBMHfunc:
      return(SDBMHash(strkey));
      case DJBHfunc:  
      return(DJBHash(strkey));
      case APHfunc:   	  
      return(APHash(strkey));
      default:
      return (-1);
   }
};
//===========================================

int HashValue::HashFunction(int hashfuncID, int key, int highest_hash_val)
{
   char strkey[10];
	
   switch (hashfuncID)
   {
      case MODHfunc:
      return(MODH(key, highest_hash_val));
      case MULTHfunc:   
      return(MULTH(key, highest_hash_val));
      default:
        ostrstream ostrkey(strkey, 10);
        ostrkey << key << ends;
      return (HashFunction(hashfuncID, strkey, highest_hash_val));
   }
};
int HashValue::HashFunction(int hashfuncID, int key)
{
   char strkey[10];
	
   switch (hashfuncID)
   {
      case MODHfunc:
      return(MODH(key));
      case MULTHfunc:   
      return (MULTH(key));		 
      default:
        ostrstream ostrkey(strkey, 10);
        ostrkey << key << ends;
      return (HashFunction(hashfuncID, strkey));
   }
};
//================================================================

