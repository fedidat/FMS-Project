/*
  ********************************************************************
  *                  General HashValue Class                         *
  *                                                                  *
  * Author: Moshe Goldstein - 2005                                   *
  * This is a modified version of the                                *
  *                                                                  *
  *                  General Hash Functions Library                  *
  *                                                                  *
  * Author: Arash Partow - 2002                                      *
  * URL: http://www.partow.net                                       *
  *                                                                  *
  * Copyright Notice:                                                *
  * Free use of this library is permitted under the guidelines and   *
  * in accordance with the most current version of the Common Public *
  * License.                                                         *
  * http://www.opensource.org/licenses/cpl.php                       *
  *                                                                  *
  ********************************************************************
*/
/*
  ******************************************************************************
  * Description                                                                *
  * Hash functions are by definition and implementation pseudo random number   *
  * generators (PRNG). From this generalization its generally accepted that    *
  * the performance of hash functions and also comparisons between hash        *
  * functions can be achieved by treating hash function as PRNGs.              * 
  * Analysis techniques such a Poisson distribution can be used to analyze     *
  * the collision rates of different hash functions for different groups of    *
  * data. In general there is a theoretical hash function known as the         *
  * perfect hash function for any group of data. The perfect hash function     *
  * by definition states that no collisions will occur meaning no repeating    *
  * hash values will arise from different elements of the group. In reality    *
  * it is very difficult to find a perfect hash function, in practice it is    *
  * recognized that a perfect hash function is the hash function that produces * 
  * the least amount of collisions for a particular set of data.               *
  * The problem is that there are so many permutations of types of data, some  *
  * highly random, others containing high degrees of patterning that it is     *
  * difficult to generalize a hash function for all data types or even for     *
  * specific data types. All one can do is via trial and error find the hash   *
  * function that best suites there needs. Some dimensions to analyze for      *
  * choosing hash functions are:                                               *
  * - Data Distribution                                                        *
  *   This is the measure of how well the hash function distributes the hash   *
  *   values of elements within a set of data. Analysis in this measure        *
  *   requires knowing the number of collisions that occur with the data set   *
  *   meaning non-unique hash values, If chaining is used for collision        *
  *   resolution the average length of the chains (which would in theory be    *
  *   the average of each bucket's collision count) analyzed, also the amount  *
  *   of grouping of the hash values within ranges should be analyzed.         *
  * - Hash Function Efficiency                                                 *
  *   This is the measure of how efficiently the hash function produces hash   *
  *   values for elements within a set of data. When algorithms which contain  *
  *   hash functions are analyzed it is generally assumed that hash functions  *
  *   have a complexity of O(1), that is why look-ups for data in a hash-table *
  *   are said to be of O(1) complexity, where as look-ups of data in maps     *
  *   (Red-Black Trees) are said to be of O(logn) complexity. A hash function  *
  *   should in theory be a very quick, stable and deterministic operation. A  *
  *   hash function may not always lend itself to being of O(1) complexity,    *
  *   however in general the linear traversal through a string of data to be   *
  *   hashed is so quick and the fact that hash functions are generally used   *
  *   on primary keys which by definition are supposed to be much smaller      *
  *   associative identifiers of larger blocks of data implies that the whole  *
  *   operation should be quick and to a certain degree stable.                *
  * The hash functions in this module are known as simple hash functions. They *
  * are typically used for data hashing (string hashing). They are used to     *
  * create keys which are used in associative containers such as hash-tables.  *
  * These hash functions are not cryptographically safe, they can easily be    *
  * reversed and many different combinations of data can be easily found to    *
  * produce identical hash values for any combination of data.                 *
  *                                                                            *
  * Hashing Methodologies                                                      *
  * Hash functions are typically defined by the way they create hash values    *
  * from data. There are two main methodologies for a hash algorithm to        *
  * implement, they are:                                                       * 
  * - Addative Hashing                                                         *
  *   This is where the hash value is constructed by traversing through the    *
  *   data and continually incrementing an initial value by a calculated value *
  *   relative to an element within the data. The calculation done on the      *
  *   element value is usually in the form of a multiplication by a prime      *
  *   number.                                                                  *
  * - Rotative Hashing                                                         *
  *   Same as additive hashing in that every element in the data string is     *
  *   used to construct the hash, but unlike additive hashing the values are   *
  *   put through a process of bitwise shifting. Usually a combination of both *
  *   left and right shifts, the shift amounts as before are prime. The result *
  *   of each process is added to some form of accumulating count, the final   *
  *   result being the hash value is passed back as the final accumulation.    * 
  *                                                                            *
  * Hash Functions and Prime Numbers                                           *
  * There isn't much real mathematical work which can definitely prove the     *
  * relationship between prime numbers and pseudo random number generators.    *
  * Nevertheless, the best results have been found to include the use of prime *
  * numbers. PRNGs are currently studied as a statistical entity, they are not *
  * studied as deterministic entities hence any analysis done can only bare    *
  * witness to the overall result rather than to determine how and/or why the  *
  * result came into being. If a more discrete analysis could be carried out,  *
  * one could better understand what prime numbers work better and why they    *
  * work better, and at the same time why other prime numbers don't work as    *
  * well, answering these questions with stable, repeatable proofs can better  *
  * equip one for designing better PRNGs and hence eventually better hash      *
  * functions.                                                                 *
  * Deciding what is the right or even yet the best possible combination of    *
  * hashing methodologies and use of prime numbers is still very much a black  *
  * art. No single methodology can lay claim to being the ultimate general     *
  * purpose hash function. The best one can do is to evolve via trial and      *
  * error and statistical analysis methods for obtaining suitable hashing      *
  * algorithms that meet their needs.                                          *
  *                                                                            *
  * Available Hash Functions in this module                                    *
  * The General Hash Functions Library has six (additive and rotative) general *
  * purpose string hashing algorithms (see below).                             *
  * I (M.G.) added two traditional integer hashing functions to the library:   *
  * - the Modulo hash function                                                 *
  *   h(k) = k mod m                                                           *
  *   When using this method, we usually avoid certain values of m.            *
  *   Powers of 2 are usually avoided, because (k mod 2^b) simply selects the  *
  *   b low order bits of k. Unless we know that all the 2^b possible values   *
  *   of the lower order bits are equally likely, this will not be a good      *
  *   choice, because some bits of the key are not used in the hash function.  *
  *   Prime numbers which are close to powers of 2 seem to be generally good   *
  *   choices for m.                                                           *
  *   For example, if we have 4000 elements, and we have chosen an overflow    *
  *   table organization, but wish to have the probability of collisions quite *
  *   low, then we might choose m = 4093. (4093 is the largest prime less than *
  *   4096 = 212.)                                                             *
  * - Knuth's Multiplicative hash function                                     *
  *   The hash function is:                                                    * 
  *                        h(k) = floor(m * (kA - floor(kA)))                  *
  *   That is:                                                                 *
  *   - Multiply the key k by a constant A, 0 < A < 1                          *
  *   - Extract the fractional part of the product                             *
  *   - Multiply this value by m.                                              *
  *   The value of m is not critical and we typically choose a power of 2 so   *
  *   that we can get the following efficient procedure on most digital        *
  *   computers:                                                               *
  *   - Choose m = 2^p                                                         *
  *   - Multiply the w bits of k by floor(A * 2^w) to obtain a 2w bit product. *
  *   - Extract the p most significant bits of the lower half of this product. * 
  *   It seems that                                                            *
  *                  A = (sqrt(5)-1)/2 = 0.6180339887                          *
  *   is a good choice (see Knuth, "Sorting and Searching", v. 3 of "The Art   *
  *   of Computer Programming").                                               *
  ******************************************************************************
*/

#ifndef INCLUDE_GENERALHASHFUNCTION_H
#define INCLUDE_GENERALHASHFUNCTION_H

// Hash Function ID codes
enum HashFuncIDcode {
	DUMMYfunc = -1,
	MODHfunc = 0, 
	MULTHfunc,
    RSHfunc, 
	JSHfunc, 
	PJWHfunc, 
    ELFHfunc, 
    BKDRHfunc,
    SDBMHfunc,
    DJBHfunc,
    APHfunc
};

#include <iostream>
#include <cstring>
using namespace std;

class HashValue {
  private:
    union {
      char*  c;
      int    i;
    } Kval; // the key value
    int Hval; // the hash value corresponding to Kval
    /* int HfuncID; // ID code of hash function applied on Kval, whose value is in Hval */
	HashFuncIDcode HfuncID;
    int Hvalmax; // the highest permissible hash value (a prime number)	 
/*
  ***********************************************************************
  * FUNCTION                                                            *
  *   genprime                                                          *
  * PARAMETERS                                                          *
  *   int - highest possible (prime) value                              *
  * RETURN VALUE                                                        *
  *   A (positive) integer: the smallest prime number greater than the  *  
  *   integer received as parameter.                                    *
  * MEANING                                                             *
  *   This function computes a prime number p                           *
  *            0 <= PARAMETER <= p                                      * 
  *   such that p is the smallest of all the prime numbers for which    *
  *   this condition holds.                                             *
  ***********************************************************************/	 
    int genprime(int);
/*
  *********************************************************************
  * MOD Hash Function                                                 *
  * This is the Modulo hash function (see above explanations)         * 
  *********************************************************************/	 	 
    int MODH(int,int);
    int MODH(int);
/*
  *************************************************************************
  * MULT Hash Function                                                    *
  * This is Knuth's Multiplicative hash function (see above explanations) *
  *************************************************************************/	 	 
    int MULTH(int,int);
    int MULTH(int);
/*
  ************************************************************************
  * RS Hash Function                                                     *
  * A simple hash function from Robert Sedgwicks Algorithms in C book.   *
  * Some simple optimizations were added to the algorithm in order to    *
  * speed up its hashing process.                                        *
  ************************************************************************/	 
    int RSHash(const char*,int);
    int RSHash(const char*);
/*
  ************************************************************************
  * JS Hash Function                                                     *  
  * A bitwise hash function written by Justin Sobel                      *  
  ************************************************************************/	 
    int JSHash(const char*,int);
    int JSHash(const char*);
/*
  ************************************************************************
  * PJW Hash Function                                                    *  
  * A hash algorithm based on work by Peter J. Weinberger of AT&T Bell   *
  * Labs                                                                 *
  ************************************************************************/	 	 
    int PJWHash(const char*,int);
    int PJWHash(const char*);
/*
  ************************************************************************
  * ELF Hash Function                                                    *
  * Similar to the PJW Hash function, but tweaked for 32-bit processors. * 
  * It is the hash function widely used on most UNIX systems.            *
  ************************************************************************/	 
    int ELFHash(const char*,int);
    int ELFHash(const char*);
/*
  **************************************************************************
  * BKDR Hash Function                                                     *
  * This hash function comes from B. Kernighan & D. Ritchie's book "The C  *
  * Programming Language". It is a simple hash function using a strange    *
  * set of possible seeds which all constitute a pattern of 31....31...31, * 
  * etc, it seems to be very similar to the DJB hash function.             *
  **************************************************************************/	 
    int BKDRHash(const char*,int);
    int BKDRHash(const char*);
/*
  ***************************************************************************
  * SDBM Hash Function                                                      *
  * This is the algorithm of choice which is used in the open source SDBM   *
  * project. The hash function seems to have a good over-all distribution   *
  * for many different data sets. It seems to work well in situations where * 
  * there is a high variance in the MSBs of the elements in a data set.     *
  ***************************************************************************/	 
    int SDBMHash(const char*,int);
    int SDBMHash(const char*);
/*
  **************************************************************************
  * DJB Hash Function                                                      *
  * An algorithm produced by Daniel J. Bernstein and shown first to the    *
  * world on the comp.lang.c newsgroup. Its efficient as far as processing * 
  * is concerned.                                                          *
  **************************************************************************/	 
    int DJBHash(const char*,int);
    int DJBHash(const char*);
/*
  ***************************************************************************
  * AP Hash Function                                                        *
  * An algorithm produced by me Arash Partow. Ideas were taken from all of  *
  * the above hash functions making a hybrid rotative and additive hash     *
  * function algorithm based around four primes 3,5,7 and 11. There isn't   * 
  * any real mathematical analysis explaining why one should use this hash  *
  * function instead of the others described above other than the fact that *
  * I tired to resemble the design as close as possible to a simple LFBSR.  *
  * An empirical result which demonstrated the distributive abilities of    *
  * the hash algorithm was obtained using a hash-table with 100003 buckets, *
  * hashing The Project Gutenberg Etext of Webster's Unabridged Dictionary, *
  * the longest encountered chain length was 7, the average chain length    *
  * was 2, the number of empty buckets was 4579.                            * 
  ***************************************************************************/	 
    int APHash(const char*,int);
    int APHash(const char*);
	 
  public:
/*
  **************************************************************************
  * FUNCTION                                                               *
  *   HashValue()                                                          *
  * PARAMETERS                                                             *
  *   none                                                                 *
  * RETURN VALUE                                                           *
  *   none (this is the default constructor)                               *
  * MEANING                                                                *
  *   All the data members of the HashValue object are initialized to a    *
  *   default value.                                                       *
  **************************************************************************/
    HashValue();
/*
  ******************************************************************************
  * FUNCTION                                                                   *
  *   HashValue                                                                *
  * PARAMETERS                                                                 *
  *   int -  highest possible hash value                                       *
  * RETURN VALUE                                                               *
  *   none (this is a constructor)                                             *
  * MEANING                                                                    *
  *   All the data members of the HashValue object are initialized to a        *
  *   default value; especially, Hvalmax is assigned the smallest prime number * 
  *   greater than the integer received as parameter.                          *
  ******************************************************************************/	 
    HashValue(int highest_hash_val);
/*
  **************************************************************************
  * FUNCTION                                                               *
  *   maxHval()                                                            *
  * PARAMETERS                                                             *
  *   none                                                                 *
  * RETURN VALUE                                                           *
  *   the current (prime number) value upon which the hash value will be   *
  *   computed when HashFunction (see below) will be called.               *
  * MEANING                                                                *
  *   the data member Hvalmax is returned                                  *
  **************************************************************************/
    int maxHval();
/*
  **************************************************************************
  * FUNCTION                                                               *
  *   HashFunction  (version nr 1a)                                        *
  * PARAMETERS                                                             *
  *   int - hash function ID code                                          *
  *   const char* - string key value                                       *
  *   int - highest possible hash value                                    *
  * RETURN VALUE                                                           *
  *   A (positive) integer, result of the hash function computation.       *
  * MEANING                                                                *
  *   The "hash function ID code" identifies the hashing function to be    *
  *   applied on the key value received as 2nd parameter.                  *
  *   Based on the 3rd parameter, a new prime number is generated and      *
  *   assigned to the data member field Hvalmax. The hash function will    *
  *   be computed based on the new value of Hvalmax.                       *
  *   The computed value returned is:  0 <= return value <= 3rd parameter  *
  **************************************************************************/	 
    int HashFunction(int, const char*, int);
/*
  **************************************************************************
  * FUNCTION                                                               *
  *   HashFunction  (version nr 1b)                                        *
  * PARAMETERS                                                             *
  *   int - hash function ID code                                          *
  *   const char* - string key value                                       *
  * RETURN VALUE                                                           *
  *   A (positive) integer, result of the hash function computation.       *
  * MEANING                                                                *
  *   The "hash function ID code" identifies the hashing function to be    *
  *   applied on the key value received as 2nd parameter.                  *
  *   The hash function will be computed based on the current value of the *
  *   data member field Hvalmax.                                           *
  *   The computed value returned is:  0 <= return value <= 3rd parameter  *
  **************************************************************************/
    int HashFunction(int, const char*);
/*
  **************************************************************************
  * FUNCTION                                                               *
  *   HashFunction  (version nr 2a)                                        *
  * PARAMETERS                                                             *
  *   int - hash function ID code                                          *
  *   int - integer key value                                              *
  *   int - highest possible hash value                                    *
  * RETURN VALUE                                                           *
  *   A (positive) integer, result of the hash function computation.       *
  * MEANING                                                                *
  *   See above (in version nr 1a).                                        *
  **************************************************************************/	 
    int HashFunction(int, int, int);
/*
  **************************************************************************
  * FUNCTION                                                               *
  *   HashFunction  (version nr 2a)                                        *
  * PARAMETERS                                                             *
  *   int - hash function ID code                                          *
  *   int - integer key value                                              *
  * RETURN VALUE                                                           *
  *   A (positive) integer, result of the hash function computation.       *
  * MEANING                                                                *
  *   See above (in version nr 1b).                                        *
  **************************************************************************/
    int HashFunction(int, int);
};
#endif
