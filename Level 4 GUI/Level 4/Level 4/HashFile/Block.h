#pragma once
#include <string>
using namespace std;

const unsigned int BLOCK_LENGTH = 1024;

/****************************************************
*	The Physical Block class.						*
*	Contains three fields:							*
* 	BlockNr - the serial number of the 	block.		*
*	Filler - free space needed for the				*
*		other Blocks.								*
*	Data - Data in the block.						*
/***************************************************/
struct PhysicalBlock
{
	unsigned int BlockNr;
	char Filler[20];
	char Data[1000];
	PhysicalBlock();
};

/****************************************************
*	The Physical Block class.						*
*	Contains five fields:							*
*	NrOfOverflowedRecs - represents the number		*
*		of overflowed records in the block.			*
*	NrOfRecsInBlock - the total number of			*
*		records in the block.						*
* 	BlockNr - the serial number of the 	block.		*
*	Filler - free space needed for the				*
*		other Blocks.								*
*	Data - Data in the block.						*
****************************************************/
struct LogicalBlock
{
	unsigned int BlockNr;
	unsigned int NrOfOverflowedRecs;
	unsigned int NrOfRecsInBlock;
	char Filler[12];
	char Data[1000];
};

/****************************************************
*	The Volume Header Class.						*
*	This class represents the file header,			*
*	containing metadata information on the file.	*
*	Contains the serial Block number (0), the file	*
*	name, the name of the owner, the size in blocks,*
*	the date of creation, the number of records,	*
*	the key offset, the key type, the key size		*
*	(the last three relative to the hash indexing)	*
*	and filler data.								*
****************************************************/
struct LogicalFileHeader
{
	unsigned int BlockNr;
	char FileName[12];
	char OwnerName[10];
	unsigned int FileSize;
	char CreationDate[10];
	unsigned int RecordSize;
	unsigned int NrOfRecsInFile;
	unsigned int KeyOffset;
	char KeyType;
	unsigned int KeySize;
	int HashFuncID;
	char Filler[963];
};

/****************************************************
*	Used for the CurrBlock object in class			*
*	PhysicalFile. Contains the current block		*
*	and its serial number.							*
****************************************************/
struct CurrentBlock
{
	int Nr;
	PhysicalBlock* Buffer;
};