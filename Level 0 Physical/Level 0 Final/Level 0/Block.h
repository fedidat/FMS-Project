#pragma once
#include<string>
using namespace std;

const unsigned int BlockLength = 1024;

///**************************************************
//*		The Primitive Block class.					*
//*		Contains two fields:						*
//*		BlockNr - the serial number of the block.	*
//*		Data - Data in the block.					*
//***************************************************/
//class BaseBlock
//{
//	unsigned int BlockNr;
//	char Data[1020];
//	void Initialize();
//	void Zeros();
//};

/************************************************
*	The Physical Block class.					*
*	Contains three fields:						*						
* 	BlockNr - the serial number of the 	block.	*
*	Filler - free space needed for the			*
*		other Blocks.							*
*	Data - Data in the block.					*
/***********************************************/
struct PhysicalBlock
{
	unsigned int BlockNr;
	char Filler[20];
	char Data[1000];
	void Initialize();
};

///************************************************
//*	The Physical Block class.					*
//*	Contains five fields:						*
//*	NrOfOverflowedRecs - represents the number	*
//*		of overflowed records in the block.		*
//*	NrOfRecsInBlock - the total number of		*
//*		records in the block.					*
//* 	BlockNr - the serial number of the 	block.	*
//*	Filler - free space needed for the			*
//*		other Blocks.							*
//*	Data - Data in the block.					*
///***********************************************/
//class LogicalBlock
//{
//public:
//	unsigned int BlockNr;
//	unsigned int NrOfOverflowedRecs;
//	unsigned char NrOfRecsInBlock;
//	char Filler[11];
//	char Data[1000];
//	void Initialize(); // Create sector filled with NULL
//	void Initialize(unsigned int num); // Create sector with specific number, and filled with NULL
//	void Zeros();
//};
//
///****************************************************
//*	The Volume Header Class.						*
//*	This class represents the file header,			*
//*	containing metadata information on the file.	*
//*	Contains the serial Block number (0), the file	*
//*	name, the name of the owner, the size in blocks,*
//*	the date of creation, the number of records,	*
//*	the key offset, the key type, the key size		*
//*	(the last three relative to the hash) and		*
//*	filler data.									*
//****************************************************/
//class FileHeader
//{
//public:
//	unsigned int BlockNr;
//	char FileName[12];
//	char OwnerName[10];
//	unsigned int FileSize;
//	char CreationDate[10];
//	unsigned int RecordSize;
//	unsigned int NrOfRecsInFile;
//	unsigned int KeyOffset;
//	char KeyType[2];
//	unsigned int KeySize;
//	char Filler[958];
//	void Initialize();
//	void Initialize(string name, string owner);
//};
//
///****************************************************
//*	The General Block type, represents a block in	*
//*	the file, with various implementations to		*
//*	choose from (as described above).				*
//****************************************************/
//union Block
//{
//	BaseBlock baseBlock;
//	PhysicalBlock physicalBlock;
//	LogicalBlock logicalBlock;
//	FileHeader header;
//	Block();
//	char* getData();
//	unsigned int getNumber();
//};

/****************************************************
*	Used for the CurrBlock object in class			*
*	PhysicalFile. Contains the current block		*
*	and its serial number.							*
****************************************************/
struct CurrentBlock
{
	int Nr;
	PhysicalBlock Buffer;
	char* getCurData();
	void setCurData(string data, int num);
};