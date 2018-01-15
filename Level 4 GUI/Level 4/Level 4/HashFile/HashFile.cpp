#pragma once
#include "stdafx.h"
#include "Library.h"
#include "HashFile.h"
#include <sstream>

/************************************************************************
* FUNCTION																*
*	HashFile															*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Default constructor: creates an empty class for a future logical	*
*	file.																*
* SEE ALSO																*
*	PhysicalFile::PhysicalFile (default constructor).					*
************************************************************************/
HashFile::HashFile(void)
{
	PhysicalFile();	//create the class's default physical level
	LogicalFHBuffer = (LogicalFileHeader*)&FHBuffer;	//initialize the class's variables
	LogicalBuffer = (LogicalBlock*)CurrBlock.Buffer;
	LHBuffChanged = false;
	LBuffChanged = false;
	UserName = "";
}

/************************************************************************
* FUNCTION																*
*	HashFile															*
* PARAMETERS															*
*	fileName: string, the name of the file.								*
*	userName: string, the name of the user (not necessarily the owner).	*
*	recordSize: positive integer, the size of eahc record.				*
*	workingDir: string, the directory of the file.						*
*	code: integer, 1 if the file doesn't already exists, 2 otherwise.	*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Full constructor. Assigns values to the variables and calls			*
*		the functions necessary to the creation or the opening of the	*
*		file. Uses functions from the PhysicalFile class.				*
* SEE ALSO																*
*	PhysicalFile::PhysicalFile, HashFile::hcreate, HashFile::hopen.		*
************************************************************************/
HashFile::HashFile(string fileName, string userName, unsigned int recordSize, int HashFuncID, string workingDir, int code)
{
	LogicalFHBuffer = (LogicalFileHeader*)&FHBuffer;	//initialize the class's variables
	LogicalBuffer = (LogicalBlock*)CurrBlock.Buffer;
	LHBuffChanged = false;
	LBuffChanged = false;
	UserName = "";
	PhysicalFile();	//create the class's default physical level
	unsigned int sizeOrMode;
	switch(code)	//depending on the code, we will now want to create or to open a file
	{
	case 1:
		sizeOrMode = 1000;
		hcreate(fileName, userName, recordSize, HashFuncID, workingDir, sizeOrMode);
		break;
	case 2:
		sizeOrMode = 0;
		hopen(fileName, userName, workingDir, sizeOrMode);
		break;
	default:	//should have used the default constructor if you didn't want to create or to open a file now
		throwErr("ERROR: Illegal operation code");
	}
}

/************************************************************************
* FUNCTION																*
*	HashFile															*
* PARAMETERS															*
*	fileName: string, the name of the file.								*
*	userName: string, the name of the user (not necessarily the owner).	*
*	recordSize: positive integer, the size of each record.				*
*	workingDir: string, the directory of the file.						*
*	code: integer, 1 if the file doesn't already exists, 2 otherwise.	*
*	sizeOrMode: positive integer, it meaning is determined through the	*
*		value of the "code" field.										*
*	keyPlace: integer, beginning of the record's key inside each record.*
*	keyType: char, type of the key (int or string).						*
*	keySize: integer, size of the key in bytes.							*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Full constructor. Assigns values to the variables and calls			*
*		the functions necessary to the creation or the opening of the	*
*		file. Uses functions from the PhysicalFile class.				*
*	Same as the function above, with sizeOrMode (and possibly other		*
*		parameters) provided.											*
* SEE ALSO																*
*	PhysicalFile::PhysicalFile, HashFile::hcreate, HashFile::hopen.		*
************************************************************************/
HashFile::HashFile(string fileName, string userName, unsigned int recordSize, string workingDir, int code, unsigned int sizeOrMode, int HashFuncID, int keyPlace, char keyType, int keySize)
{
	LogicalFHBuffer = (LogicalFileHeader*)&FHBuffer;	//initialize the class's variables
	LogicalBuffer = (LogicalBlock*)CurrBlock.Buffer;
	LHBuffChanged = false;
	LBuffChanged = false;
	UserName = userName;
	PhysicalFile(fileName, workingDir, code, sizeOrMode);	//create the class's physical level
	switch(code)	//depending on the code, we will now want to create or to open a file
	{
	case 1:
		hcreate(fileName, userName, recordSize, HashFuncID, workingDir, sizeOrMode, keyPlace, keyType, keySize);
		break;
	case 2:
		hopen(fileName, userName, workingDir, sizeOrMode);
		break;
	default:
		throwErr("ERROR: Illegal operation code");
	}
}

/************************************************************************
* FUNCTION																*
*	~HashFile															*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Destructor: Closes the file if not previously done and				*
*		the file has not been deleted. Simply uses hclose.				*
* SEE ALSO																*
*	HashFile::hclose.													*
************************************************************************/
HashFile::~HashFile(void)
{
	hclose();	//destructing the class does not mean deleting the file, but closing it
}

/************************************************************************
* FUNCTION																*
*	hcreate																*
* PARAMETERS															*
*	fileName: string, the name of the file.								*
*	userName: string, the name of the user (not necessarily the owner).	*
*	recordSize: positive integer, the size of each record.				*
*	workingDir: string, the directory of the file.						*
*	fileSize: positive integer, size of the file in blocks.				*
*	keyPlace: positive integer, beginning of the record's key inside	* 
*	each record.														*
*	keyType: char, type of the key (int or string).						*
*	keySize: positiveinteger, size of the key in bytes.					*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Creates the file as a series of empty physical Blocks through		*
*		pcreate. Subsequently fetches received information into the		*
*		File Header logical buffer and writes it into the file using	*
*		writeFH.														*
* SEE ALSO																*
*	PhysicalFile::pcreate, PhysicalFile::popen,							*
*	PhysicalFile::readFH, PhysicalFile::writeFH.						*
************************************************************************/
void HashFile::hcreate(string fileName, string userName, unsigned int recordSize, int HashFuncID, string workingDir, unsigned int fileSize, unsigned int keyPlace, char keyType, unsigned int keySize)
{
	hashVal = new HashValue(fileSize);
	pcreate(fileName, hashVal->maxHval() + 1, workingDir);	//create the file on the physical level with the number of blocks indicated by the HashValue class
	popen(fileName, 1, workingDir);	//open the file on the physical level, allowing us to edit the empty file header
	strncpy_s(LogicalFHBuffer->FileName, sizeof(LogicalFHBuffer->FileName), fileName.c_str(), strlen(fileName.c_str()));	//store the filename
	strncpy_s(LogicalFHBuffer->OwnerName, sizeof(LogicalFHBuffer->OwnerName), userName.c_str(), strlen(userName.c_str()));	//store the owner name
	LogicalFHBuffer->FileSize = hashVal->maxHval() + 1;	//store the file size in blocks, as prepared by the hashvalue class
	getDate(LogicalFHBuffer->CreationDate);	//store the creation date, in dd/mm/yy format
	LogicalFHBuffer->RecordSize = recordSize;	//store the record size in bytes
	LogicalFHBuffer->NrOfRecsInFile = 0;	//initialize the number of records in the file
	LogicalFHBuffer->KeyOffset = keyPlace;	//store the key offset
	LogicalFHBuffer->KeyType = keyType;	//store the key type
	LogicalFHBuffer->KeySize = keySize;	//store the key size
	LogicalFHBuffer->HashFuncID = HashFuncID;	//store the hash function code ID
	writeFH();	//save all of these changes
	pclose();	//and we just finished creating the file
}

/************************************************************************
* FUNCTION																*
*	hdelete																*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Deletes the file using pdelete: all unsaved data is lost.			*
* SEE ALSO																*
*	PhysicalFile::pdelete.												*
************************************************************************/
void HashFile::hdelete(void)
{
	pdelete();	//there is nothing to delete on the logical level in order to delete the file
}

/************************************************************************
* FUNCTION																*
*	hopen																*
* PARAMETERS															*
*	fileName: string, the name of the file.								*
*	userName: string, the name of the user.								*
*	workingDir: string, the directory of the file.						*
*	openMode: I/O opening mode: 0 for input, 1 for output, 2 for both.	* 
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Opens the file for input/output/both. If the user does not have		*
*		the appropriate authorizations to write into the file, closes	*
*		the file back, throws an exception and aborts. Also gives		*
*		their starting values to the update flags.						*
* SEE ALSO																*
*	HashFile::hclose.													*
************************************************************************/
void HashFile::hopen(string fileName, string userName, string workingDir, int openMode)
{
	popen(fileName, openMode, workingDir);	//open the file in the physical level
	LogicalBuffer = (LogicalBlock*)(CurrBlock.Buffer);	//now initialize the logical buffer and the flags for this file
	LBuffChanged = false;
	LHBuffChanged = false;
	UserName = userName;	//we store the current user's name
	if(openMode)
	{
		readFH();
		if(strcmp(LogicalFHBuffer->OwnerName, UserName.c_str()))	//if the user is trying to open the file in writing mode and is not the owner
		{
			hclose();
			throwErr("ERROR: You do not have sufficient rights to open this file in writing mode");
		}
	}
	hashVal = new HashValue(LogicalFHBuffer->FileSize - 1);
}

/************************************************************************
* FUNCTION																*
*	hclose																*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Closes the file if it was not previously closed using flush to		*
*		"clean" the "dirty" buffers and pclose.							*
* SEE ALSO																*
*	PhysicalFile::pclose, HashFile::flush.								*
************************************************************************/
void HashFile::hclose(void)
{
	flush(2);	//flush both buffers before closing
	pclose();	//and proceed to close the I/O file stream
}

/************************************************************************
* FUNCTION																*
*	flush																*
* PARAMETERS															*
*	buffer: integer, indicates which buffer is to be "flushed": 0 for	*
*		the File Header, 1 for the normal block buffer, 2 for both.		*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	"Cleans" the "dirty" buffer(s): writes any block modified and not	*
*		yet written still in the buffer. Necessary before closing a		*
*		file. Used by hclose.											*
* SEE ALSO																*
*	HashFile::hclose, HashFile::seek.									*
************************************************************************/
void HashFile::flush(int buffer)
{
	if(!openmode)	//if the file had been opened in read-only mode, refuse saving any data
		return;
	if(buffer == 0 && LHBuffChanged)	//if we want to flush the file header buffer and it has indeed been modified and not saved yet
	{
		writeFH();	//save it
		LHBuffChanged = false;	//and now that the block has been saved, we can update the LHBuffChanged flag
	}
	else if(buffer == 1 && LBuffChanged)	//if we want to flush the logical data buffer and it has indeed been modified and not saved yet
	{
		writeBlock(LogicalBuffer->BlockNr);	//save it
		LBuffChanged = false;	//and now that the block has been saved, we can update the LBuffChanged flag
	}
	else if(buffer == 2)	//if we want to flush both buffers
	{
		if(LHBuffChanged)	//if the file header buffer has been modified and not saved it
			flush(0);	//flush it
		if(LBuffChanged)	//if the logical data has been modified and not saved it
			flush(1);	//flush it
	}
}

/************************************************************************
* FUNCTION																*
*	seek																*
* PARAMETERS															*
*	key: string of characters, the key of the record.					*
* RETURN VALUE															*
*	bool: Indicates if the record was found.							*
* MEANING																*
*	This function looks for a record that matches the provided key in	*
*		the relevant block, using the hash function specified during	*
*		the	creation of the file. If the record is not found and may	*
*		have overflowed, we will look in all the records, one by one,	*
*		because we use linear probing (cf. write below).				*
*	If the record is not found in the record and may not have			*
*		overflowed, or if it is not present in the file, false is		*
*		returned. I preferred this to an exception because in the case	*
*		of write, it is not an error: it is expected (refer there).		*
*	This function is private, it is only used by read and write.		*
* SEE ALSO																*
*	HashFile::read, HashFile::write.									*
************************************************************************/
bool HashFile::seek(char* key)
{
	if(!opened)
		throwErr("ERROR: No file has been opened");
	unsigned int index = hashVal->HashFunction(LogicalFHBuffer->HashFuncID, key) + 1;	//we store the number of the block where the record should go with the key we received
	if(seekInBlock(index, key))	//if the file has been found in this block, we can return true
		return true;
	if(LogicalBuffer->NrOfOverflowedRecs != 0)	//this record has not been found in the 'first block' but may have overflowed
	{
		unsigned int curBlock = index;	//we copy the number of the 'first block' in a variable that will represent the position of the current block number throughout the loop
		while((curBlock = ((curBlock == FileSize - 1) ? 1 : curBlock + 1)) != index)	//we will be looking for the record iteratively in the other blocks, using linear probing (as does HashFile::write) to increase our chances of finding it early
			if(seekInBlock(curBlock, key))	//if the file has been found in this block, we can return true
				return true;
	}
	return false;	//the record has ultimately not been found, hence we return false
}

/************************************************************************
* FUNCTION																*
*	seek																*
* PARAMETERS															*
*	key: integer, the key of the record.								*
* RETURN VALUE															*
*	bool: Indicates if the record was found.							*
* MEANING																*
*	This function looks for a record that matches the provided key in	*
*		the relevant block, using the hash function specified during	*
*		the	creation of the file. If the record is not found and may	*
*		have overflowed, we will look in all the records, one by one,	*
*		because we use linear probing (cf. write below).				*
*	If the record is not found in the record and may not have			*
*		overflowed, or if it is not present in the file, false is		*
*		returned. I preferred this to an exception because in the case	*
*		of write, it is not an error: it is expected (refer there).		*
*	This function is private, it is only used by read and write.		*
* SEE ALSO																*
*	HashFile::read, HashFile::write.									*
************************************************************************/
bool HashFile::seek(int key)
{
	if(!opened)
		throwErr("ERROR: No file has been opened");
	unsigned int index = hashVal->HashFunction(LogicalFHBuffer->HashFuncID, key) + 1;	//we store the number of the block where the record should go with the key we received
	if(seekInBlock(index, key))	//if the file has been found in this block, we can return true
		return true;
	if(LogicalBuffer->NrOfOverflowedRecs != 0)	//this record has not been found in the 'first block' but may have overflowed
	{
		unsigned int curBlock = index;	//we copy the number of the 'first block' in a variable that will represent the position of the current block number throughout the loop
		while((curBlock = ((curBlock == FileSize - 1) ? 1 : curBlock + 1)) != index)	//we will be looking for the record iteratively in the other blocks, using linear probing (as does HashFile::write) to increase our chances of finding it early
			if(seekInBlock(curBlock, key))	//if the file has been found in this block, we can return true
				return true;
	}
	return false;	//the record has ultimately not been found, hence we return false
}

/************************************************************************
* FUNCTION																*
*	seekInBlock															*
* PARAMETERS															*
*	position: integer, the number of the data block where we are to		*
*		seek the record with the given key.								*
*	key: pointer to char, the C string key of the record that we are to	*
*		seek.															*
* RETURN VALUE															*
*	bool: indicates whether (true) or not (false) the record was found	*
*		in the specified block.											*
* MEANING																*
*	This function allows us to write a simpler seek function, by		*
*		calling this specific function for every block where we will be	*
*		looking for a record.											*
* SEE ALSO																*
*	HashFile::seek														*
************************************************************************/
bool HashFile::seekInBlock(int position, char* key)
{
	if(position != CurrBlock.Nr)	//if we don't remain in the same block, we must read the new block
		readBlock(position);
	for(unsigned int curKeyIndex = LogicalFHBuffer->KeyOffset ; curKeyIndex < (LogicalBuffer->NrOfRecsInBlock * LogicalFHBuffer->RecordSize) ; curKeyIndex += LogicalFHBuffer->RecordSize)	//for each record in the 'first' block
	{
		char* curKey = new char[LogicalFHBuffer->KeySize];
		memcpy(curKey,&LogicalBuffer->Data[curKeyIndex],LogicalFHBuffer->KeySize);	//we store the current record's char pointer
		bool identical = true;
		for(unsigned int position = 0 ; position < LogicalFHBuffer->KeySize && (key[position] || curKey[position]) ; position++)
			if(curKey[position] != key[position])
				identical = false;
		if(identical)	//if we found a record with the indentical key
		{
			CurrBlock.Nr = LogicalBuffer->BlockNr;	//we move the buffer and update the number of the current record in the buffer, for HashFile::read to know where we found it
			CurrRecNrInBuffer = (curKeyIndex - LogicalFHBuffer->KeyOffset) / LogicalFHBuffer->RecordSize;
			return true;	//returning true means that we indeed found a record with the same key specified as the parameter
		}
	}
	return false;
}

/************************************************************************
* FUNCTION																*
*	seekInBlock															*
* PARAMETERS															*
*	position: integer, the number of the data block where we are to		*
*		seek the record with the given key.								*
*	key: integer, the C string key of the record that we are to seek.	*
* RETURN VALUE															*
*	bool: indicates whether (true) or not (false) the record was found	*
*		in the specified block.											*
* MEANING																*
*	This function allows us to write a simpler seek function, by		*
*		calling this specific function for every block where we will be	*
*		looking for a record.Same as above with an integer key this		*
*		time on.														*
* SEE ALSO																*
*	HashFile::seek														*
************************************************************************/
bool HashFile::seekInBlock(int position, int key)
{
	if(position != CurrBlock.Nr)	//if we don't remain in the same block, we must read the new block
		readBlock(position);
	for(unsigned int curKeyIndex = LogicalFHBuffer->KeyOffset ; curKeyIndex < (LogicalBuffer->NrOfRecsInBlock * LogicalFHBuffer->RecordSize) ; curKeyIndex += LogicalFHBuffer->RecordSize)	//for each record in the 'first' block
	{	
		//we compute the value of the key: the characters in the blockNr field represent an integer in base 256
		int numCurKey = (unsigned char)LogicalBuffer->Data[curKeyIndex] + 256 * (unsigned char)LogicalBuffer->Data[curKeyIndex + 1] + 65536 * (unsigned char)LogicalBuffer->Data[curKeyIndex + 2] + 16777216 * (unsigned char)LogicalBuffer->Data[curKeyIndex + 3];
		if(numCurKey == key)	//if we found a record with the indentical key
		{
			CurrBlock.Nr = LogicalBuffer->BlockNr;	//we move the buffer and update the number of the current record in the buffer, for HashFile::read to know where we found it
			CurrRecNrInBuffer = (curKeyIndex - LogicalFHBuffer->KeyOffset) / LogicalFHBuffer->RecordSize;
			return true;	//returning true means that we indeed found a record with the same key specified as the parameter
		}
	}
	return false;
}

/************************************************************************
* FUNCTION																*
*	read																*
* PARAMETERS															*
*	key: string, the key of the record to be read.						*
*	record: string of characters, points to the record to be read.		*
*	readType: int, indicates if the record will be read only (0 -by		*
*		default) or also updated (1). In the latter case, the user's	*
*		authorizations on the file are to be checked, as it was done	*
*		in hopen.														*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	The function checks the user's authorizations (cf. above parameter	*
*		readType), gets the position of the record using seek, and		*
*		writes the bytes into the pointer to the record.				*
* SEE ALSO																*
*	HashFile::hopen, HashFile::seek.									*
************************************************************************/
void HashFile::read(string& key, char* record, int readType)
{
	read(const_cast<char*>(key.c_str()),record,readType);	//just convert the C++ string to a C string and call read
}

/************************************************************************
* FUNCTION																*
*	read																*
* PARAMETERS															*
*	key: string of characters, the key of the record to be read.		*
*	record: string of characters, points to the record to be read.		*
*	readType: int, indicates if the record will be read only (0 -by		*
*		default) or also updated (1). In the latter case, the user's	*
*		authorizations on the file are to be checked, as it was done	*
*		in hopen.														*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	The function checks the user's authorizations to update (cf. above	*
*		parameter readType), gets the position of the record using seek,*
*		and	writes the bytes into the pointer to the record.			*
* SEE ALSO																*
*	HashFile::hopen, HashFile::seek.									*
************************************************************************/
void HashFile::read(char* temp, char* record, int readType)
{
	if(openmode == 1)
		throwErr("ERROR: The file has not been opened in read mode");
	if(readType)	//if the user is trying to read the record in order to update it
	{
		bool identical = true;
		for(unsigned int position = 0 ; position < 12 && (UserName.c_str()[position] || LogicalFHBuffer->OwnerName[position]) ; position++)
			if(UserName.c_str()[position] != LogicalFHBuffer->OwnerName[position])
				identical = false;	//read the username, in order to check the user's permission to update the record
		if(openmode != 2 || !identical)	//if the file was opened in read-only mode or the name was incorrect, access denied
		{
			hclose();	//access denied, we close the file and throw an exception
			throwErr("ERROR: You do not have sufficient rights to update a record");
		}
	}
	readFH(); //read the file header, in case this has not been done yet
	char* key = new char[LogicalFHBuffer->KeySize + 1];	//we are going to store the key in a bigger string and mark the last character NULL
	memcpy(key,temp,LogicalFHBuffer->KeySize);
	key[LogicalFHBuffer->KeySize] = NULL;	//This will allow us to make HashFunction stop reading the key after [KeySize] characters
	if(!seek(key))	//seek the record using HashFile::seek
		throwErr("ERROR: Record not found");
	memcpy(record, &LogicalBuffer->Data[LogicalFHBuffer->RecordSize * CurrRecNrInBuffer], LogicalFHBuffer->RecordSize);	//we read the record into the provided pointer to char
	if(readType)
		updateflag = true;	//as read succeeded, we turn on the update flag before returning the record to the user
}

/************************************************************************
* FUNCTION																*
*	read																*
* PARAMETERS															*
*	key: integer, the key of the record to be read.						*
*	record: string of characters, points to the record to be read.		*
*	readType: int, indicates if the record will be read only (0 -by		*
*		default) or also updated (1). In the latter case, the user's	*
*		authorizations on the file are to be checked, as it was done	*
*		in hopen.														*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	The function checks the user's authorizations to update (cf. above	*
*		parameter readType), gets the position of the record using seek,*
*		and	writes the bytes into the pointer to the record.			*
* SEE ALSO																*
*	HashFile::hopen, HashFile::seek.									*
************************************************************************/
void HashFile::read(int key, char* record, int readType)
{
	if(openmode == 1)
		throwErr("ERROR: The file has not been opened in read mode");
	readFH(); //read the file header, in case this has not been done yet
	if(readType)	//if the user is trying to read the record in order to update it
	{
		bool identical = true;
		for(unsigned int position = 0 ; position < 12 && (UserName.c_str()[position] || LogicalFHBuffer->OwnerName[position]) ; position++)
			if(UserName.c_str()[position] != LogicalFHBuffer->OwnerName[position])
				identical = false;	//read the username, in order to check the user's permission to update the record
		if(openmode != 2 || !identical)	//if the file was opened in read-only mode or the name was incorrect, access denied
		{
			hclose();	//access denied, we close the file and throw an exception
			throwErr("ERROR: You do not have sufficient rights to update a record");
		}
	}
	if(!seek(key))	//seek the record using HashFile::seek
		throwErr("ERROR: Record not found");
	memcpy(record, &LogicalBuffer->Data[LogicalFHBuffer->RecordSize * CurrRecNrInBuffer], LogicalFHBuffer->RecordSize);	//we read the record into the provided char pointer
	if(readType)
		updateflag = true;	//we turn on the update flag before returning the record to the user
}

/************************************************************************
* FUNCTION																*
*	writes																*
* PARAMETERS															*
*	key: string, the key of the record to be written.					*
*	record: string of characters, a pointer to the record in the main	*
*	program's memory.													*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	The function determines if a record with the same key doesn't		*
*		already exist. If it doesn't, it then proceeds to get to the	*
*		future position of the record using seek and uses linear		*
*		probing until it finds a big enough place in the block in order	*
*		to write the record. It then proceeds to update the block.		*
* SEE ALSO																*
*	HashFile::seek.														*
************************************************************************/
void HashFile::write(string& key, char* record)
{
	write(const_cast<char*>(key.c_str()),record);	//just convert the C++ string to a C string and call write
}

/************************************************************************
* FUNCTION																*
*	writes																*
* PARAMETERS															*
*	key: string of characters, the key of the record to be written.		*
*	record: string of characters, a pointer to the record in the main	*
*	program's memory.													*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	The function determines if a record with the same key doesn't		*
*		already exist. If it doesn't, it then proceeds to get to the	*
*		future position of the record using seek and uses linear		*
*		probing until it finds a big enough place in the block in order	*
*		to write the record. It then proceeds to update the block.		*
* SEE ALSO																*
*	HashFile::seek.														*
************************************************************************/
void HashFile::write(char* key, char* record)
{
	if(openmode == 0)
		throwErr("ERROR: The file has not been opened in write mode");
	if(seek(key))	//if a block with the same key is already within the file, invoke exception
		throwErr("ERROR: A record with the same key already exists");
	if(writeInBlock(hashVal->HashFunction(LogicalFHBuffer->HashFuncID, key) + 1, record))	//attempt to write the record in the block designated by the key according to the hash function
		return;
	else //if the block is full, the record will overflow and we will look iteratively for place in the other blocks (in accordance with the principle of linear probing)
	{
		LogicalBuffer->NrOfOverflowedRecs++;
		writeBlock();	//We are going to overwrite the block really soon, so we write it now.
		int startBlock = LogicalBuffer->BlockNr;	//two copies of LogicalBuffer->BlockNr: startBlock is the necessary reminder of the first block, designated by the key
		unsigned int blockNr = LogicalBuffer->BlockNr;	//and blockNr  indicates the current block. It is optional but improves the readability
		for(blockNr = ((blockNr == FileSize - 1) ? 1 : blockNr + 1) ; blockNr != startBlock ; blockNr = (blockNr + 1 == FileSize) ? 1 : (blockNr + 1) % LogicalFHBuffer->FileSize)	//we check each block iteratively
			if(writeInBlock(blockNr, record))	//read the next block and attempt to write therein
				return;
	}
	throwErr("ERROR: The file is full");	//since all else failed, it must means that there is no place left in the file
}

/************************************************************************
* FUNCTION																*
*	writes																*
* PARAMETERS															*
*	key: integer, the key of the record to be written.					*
*	record: string of characters, a pointer to the record in the main	*
*	program's memory.													*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	The function determines if a record with the same key doesn't		*
*		already exist. If it doesn't, it then proceeds to get to the	*
*		future position of the record using seek and uses linear		*
*		probing until it finds a big enough place in the block in order	*
*		to write the record. It then proceeds to update the block.		*
* SEE ALSO																*
*	HashFile::seek.														*
************************************************************************/
void HashFile::write(int key, char* record)
{
	if(openmode == 0)
		throwErr("ERROR: The file has not been opened in write mode");
	if(seek(key))	//if a block with the same key is already within the file, invoke exception
		throwErr("ERROR: A record with the same key already exists");
	if(writeInBlock(hashVal->HashFunction(LogicalFHBuffer->HashFuncID, key) + 1, record))	//attempt to write the record in the block designated by the key according to the hash function
		return;
	else //if the block is full, the record will overflow and we will look iteratively for place in the other blocks (in accordance with the principle of linear probing)
	{
		LogicalBuffer->NrOfOverflowedRecs++;
		writeBlock();	//We are going to overwrite the block really soon, so we write it now.
		int startBlock = LogicalBuffer->BlockNr;	//two copies of LogicalBuffer->BlockNr: startBlock is the necessary reminder of the first block, designated by the key
		unsigned int blockNr = LogicalBuffer->BlockNr;	//and blockNr  indicates the current block. It is optional but improves the readability
		for(blockNr = ((blockNr == FileSize - 1) ? 1 : blockNr + 1) ; blockNr != startBlock ; blockNr = (blockNr + 1 == FileSize) ? 1 : (blockNr + 1) % LogicalFHBuffer->FileSize)	//we check each block iteratively
			if(writeInBlock(blockNr, record))	//read the next block and attempt to write therein
				return;
	}
	throwErr("ERROR: The file is full");	//since all else failed, it must means that there is no place left in the file
}

/************************************************************************
* FUNCTION																*
*	writeInBlock														*
* PARAMETERS															*
*	position: integer, the number of the data block where we are to		*
*		write the record.												*
*	record: a pointer to the record in bytes.							*
* RETURN VALUE															*
*	bool: indicates whether (true) or not (false) the record could be	*
*		written in the specified block, meaning there was enough place	*
*		in the block.													*
* MEANING																*
*	This function allows us to write simpler write functions, by		*
*		calling this function every time we want to write in a specific	*
*		block.															*
* SEE ALSO																*
*	HashFile::seek														*
************************************************************************/
bool HashFile::writeInBlock(int position, char* record)
{
	readBlock(position);	//get the required block
	if((LogicalBuffer->NrOfRecsInBlock + 1) * LogicalFHBuffer->RecordSize < 1000)	//if we have enough place in the first block, write in there
	{
		memcpy(&LogicalBuffer->Data[LogicalFHBuffer->RecordSize * LogicalBuffer->NrOfRecsInBlock], record, LogicalFHBuffer->RecordSize);	//we copy the record to the Data array
		LogicalBuffer->NrOfRecsInBlock++;	//and increment the relevant variables
		LogicalFHBuffer->NrOfRecsInFile++;
		LBuffChanged = true;	//these flags will allow us not to write the block write now: we earn that much in I/O time
		LHBuffChanged = true;
		return true;
	}
	return false;
}

/************************************************************************
* FUNCTION																*
*	delrec																*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Deletes the record that is present in the buffer "physically"		*
*		(bit-per-bit overwriting) instead of "logically" (marking the	*
*		bits as invalid): the function read has to be called for update	*
*		previously (using the third parameter, cf. Level 2), thereby	*
*		locking the buffer on the record that has just been read.		*
*	It then proceeds to read the record's key for future use (see		*
*		further) and overwrites the record's bits with the last record	*
*		in the block using memcpy. The block's and the file header's	*
*		variables are then updated (NrOfRecsInBlock and LBuffChanged,	*
*		NrOfRecsInFile and LHBuffChanged, respectively).				*
*	If the record should have originally been in another block, this	*
*		block is read in the buffer (using HashFunction to get its		*
*		position), and its NrOfOverflowedRecs and LHBuffChanged			*
*		variables are then updated accordingly.							*
* SEE ALSO																*
*	HashFile::read														*
************************************************************************/
void HashFile::delrec(void)
{
	if(!updateflag)	//the function read has to be previously called for update
		throwErr("ERROR: The read function with update parameter has not been since the last update unlocking");
	else if(openmode != 2)	//the user must have read and write authorizations
		throwErr("ERROR: The present file is not opened in read AND write mode");
	else
	{
		//recuperate the record's key in order to know if the record overflowed
		int moveToBlock = 0, curKeyIndex = CurrRecNrInBuffer * LogicalFHBuffer->RecordSize + LogicalFHBuffer->KeyOffset;
		if(LogicalFHBuffer->KeyType == 'I')	//if the file has integer key type
		{
			int curKey = (unsigned char)LogicalBuffer->Data[curKeyIndex] + 256 * (unsigned char)LogicalBuffer->Data[curKeyIndex + 1] + 65536 * (unsigned char)LogicalBuffer->Data[curKeyIndex + 2] + 16777216 * (unsigned char)LogicalBuffer->Data[curKeyIndex + 3];
			if(hashVal->HashFunction(LogicalFHBuffer->HashFuncID, curKey) + 1 != LogicalBuffer->BlockNr)	//if the record's original block number, that was just calculated, is different from the buffer's block number
				moveToBlock = hashVal->HashFunction(LogicalFHBuffer->HashFuncID, curKey) + 1;	//the record overflowed, so moveToBlock will contain its original block's number
		}
		else	//the record has string key type
		{
			char* curKey = new char[LogicalFHBuffer->KeySize];
			memcpy(curKey,&LogicalBuffer->Data[curKeyIndex],LogicalFHBuffer->KeySize);	//the string key is stored into curKey for use in the hash function
			if(hashVal->HashFunction(LogicalFHBuffer->HashFuncID, curKey) + 1 != LogicalBuffer->BlockNr)	//if the record's original block number, that was just calculated, is different from the buffer's block number
				moveToBlock = hashVal->HashFunction(LogicalFHBuffer->HashFuncID, curKey) + 1;	//the record overflowed, so moveToBlock will contain its original block's number
		}

		//physically delete the record, overwriting it by the last record in block
		memcpy(&LogicalBuffer->Data[CurrRecNrInBuffer * LogicalFHBuffer->RecordSize], &LogicalBuffer->Data[(LogicalBuffer->NrOfRecsInBlock - 1) * LogicalFHBuffer->RecordSize], LogicalFHBuffer->RecordSize);
		LBuffChanged = true;	//LogicalBuffer was just modified
		LogicalBuffer->NrOfRecsInBlock--;	//decrement NrOfRecsInblock: one less record
		LogicalFHBuffer->NrOfRecsInFile--;	//decrement NrOfRecsInFile: one less record
		LHBuffChanged = true;	//File Header Buffer was just modified
		if(moveToBlock)	//if the deleted record originally overflowed
		{
			readBlock(moveToBlock);	//move the buffer to the original block
			LogicalBuffer->NrOfOverflowedRecs--;	//decrement NrOfOverflowedRecs: one overflowed record does not exist anymore
			LBuffChanged = true;	//and there we modified LogicalBuffer again
		}
	}
}

/************************************************************************
* FUNCTION																*
*	update																*
* PARAMETERS															*
*	record: a byte pointer to the record to be updated.					*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	This function updates a record by overwriting the old record's		*
*		bytes with the new ones: as in delrec, the function read has	*
*		to be called for update previously (using the third parameter,	*
*		cf. Level 2), thereby locking the buffer on the record that has	*
*		just been read.													*
*	Using the pointer to the updated record received as a parameter, it	*
*		then checks if its key is identical to the new record and		*
*		continues (attempting to update a record with another record	*
*		that has a different key is an illegal action). As everything	*
*		is ready, the old record's bits are overwritten by the updated	*
*		one's using memcpy.												*
*	The block's LHBuffChanged is then updated to true, as is usual when	*
*		the buffer is modified and not immediately written.				*
* SEE ALSO																*
*	HashFile::read														*
************************************************************************/
void HashFile::update(char* record)
{
	if(!updateflag)	//the function read has to be previously called for update
		throwErr("ERROR: The read function with update parameter has not been since the last update unlocking");
	else if(openmode != 2)	//the user must have read and write authorizations
		throwErr("ERROR: The present file is not opened in read AND write mode");
	else
	{
		for(unsigned int chIndex = LogicalFHBuffer->KeyOffset ; chIndex < LogicalFHBuffer->KeyOffset + LogicalFHBuffer->KeySize ; chIndex++)	//compare the new record's key with the old record's byte-per-byte
			if(LogicalBuffer->Data[CurrRecNrInBuffer * LogicalFHBuffer->RecordSize + chIndex] != record[chIndex])	//if the key is any different
			{
				updateflag = false;	//unlock the file and throw an excpetion for illegal attempt to update a record with another that has a different key
				throwErr("ERROR: Attempting to update a record by a record with another key");
			}
		memcpy(&LogicalBuffer->Data[CurrRecNrInBuffer * LogicalFHBuffer->RecordSize], record, LogicalFHBuffer->RecordSize);	//all is well, update the record by written the new record's bytes over the old one's
		LBuffChanged = true;	//LogicalBuffer was just modified
	}
}

/************************************************************************
* FUNCTION																*
*	updateoff															*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Same as above, but flushes the file header buffer if it was			*
*		modified and not saved.											*
* SEE ALSO																*
*	PhysicalFile::readFH												*
************************************************************************/
void HashFile::updateoff(void)
{
	if(updateflag)
		updateflag = false;	//the class is not locked for update anymore
	else
		throwErr("ERROR: Attempting to unlock for update a record that is already unlocked");
}

/************************************************************************
* FUNCTION																*
*	readBlock															*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	The logical extension of PhysicalFile::readBlock: instead of just	*
*		writing the block in the memory, it first checks if it is not	*
*		thereby going to overwrite unsaved data.						*
* SEE ALSO																*
*	PhysicalFile::readBlock.											*
************************************************************************/
void HashFile::readBlock(void)
{
	if(LBuffChanged)	//if the last record that was read was modified and not saved
		flush(1);	//save the changes made to LogicalBuffer
	PhysicalFile::readBlock();	//as per PhysicalFile::readBlock
}

/************************************************************************
* FUNCTION																*
*	readBlock															*
* PARAMETERS															*
*																		*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	The logical (no pun intended) extension of PhysicalFile::readBlock: *
*		instead of just	writing the block in the memory, it first		*
*		checks if it is not	thereby going to overwrite unsaved data.	*
*		Same as above, with	the block's number parameter.				*
* SEE ALSO																*
*	PhysicalFile::readBlock, HashFile::readBlock.						*
************************************************************************/
void HashFile::readBlock(unsigned int position)
{	
	if(LBuffChanged)	//if the last record that was read was modified and not saved
		flush(1);	//save the changes made to LogicalBuffer
	PhysicalFile::readBlock(position);	//as per PhysicalFile::readBlock with the position parameter
}

/************************************************************************
* FUNCTION																*
*	readFH																*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Same as above, but flushes the file header buffer if it was			*
*		modified and not saved.											*
* SEE ALSO																*
*	PhysicalFile::readFH												*
************************************************************************/
void HashFile::readFH(void)
{	
	if(LHBuffChanged)	//if the logical file header buffer was modified and not saved
		flush(0);	//save the changes made to LogicalFHBuffer
	PhysicalFile::readFH();	//as per PhysicalFile::readFH
}

/************************************************************************
* FUNCTION																*
*	getKeyType															*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	char: Indicates the key type ('I'-Integer, 'C'-C string, 'S'-C++	*
*		string.															*
* MEANING																*
*	Returns the key type for exterior methods, such as the main.		*
* SEE ALSO																*
*	Block.h -> struct LogicalFileHeader									*
************************************************************************/
char HashFile::getKeyType(void)
{
	readFH();
	return LogicalFHBuffer->KeyType;	//returns the key type character, as explained above
}

/************************************************************************
* FUNCTION																*
*	isOpen																*
* PARAMETERS															*
*	status: a Boolean array with two field for the two private			*
*		indicators.														*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Returns the open status with openMode.								*
* SEE ALSO																*
************************************************************************/
void HashFile::isOpen(bool* status)
{
	status[0] = opened;	//the first value is straight the opened field value
	status[1] = openmode!=0;	//the openmode will be false if read only and true otherwise
}

/************************************************************************
* FUNCTION																*
*	getInfo																*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	string*: an array of strings that contain important information		*
*		stored in the class.											*
* MEANING																*
*	Returns a lot of valuable information about the file 'in buffer',	*
*		such as file size, key type, hash func ID, creation date, user	*
*		namea and file name.											*
* SEE ALSO																*
************************************************************************/
string* HashFile::getInfo(void)
{
	readFH();
	string* arr = new string[6];
	stringstream ss;	//create a stringstream
	ss << LogicalFHBuffer->FileSize;	//add number to the stream
	arr[0] = ss.str();
	switch(LogicalFHBuffer->KeyType)
	{
	case 'I':
		arr[1] = "Integer";
		break;
	case 'C':
		arr[1] = "C string";
		break;
	case 'S':
		arr[1] = "C++ string";
		break;
	}
	switch(LogicalFHBuffer->HashFuncID)
	{
	case 0:
		arr[2] = "MODHfunc";
		break;
	case 1:
		arr[2] = "MULTHfunc";
		break;
	case 2:
		arr[2] = "RSHfunc";
		break;
	case 3:
		arr[2] = "JSHfuncc";
		break;
	case 4:
		arr[2] = "PJWHfunc";
		break;
	case 5:
		arr[2] = "ELFHfunc";
		break;
	case 6:
		arr[2] = "BKDRHfunc";
		break;
	case 7:
		arr[2] = "SDBMHfunc";
		break;
	case 8:
		arr[2] = "DJBHfunc";
		break;
	case 9:
		arr[2] = "APHfunc";
		break;
	}
	arr[3] = string(LogicalFHBuffer->CreationDate);
	arr[4] = UserName;
	arr[5] = FileName;
	return arr;
}

/************************************************************************
* FUNCTION																*
*	getOpenMode															*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	int: indicates if the files is opened in read-only mode (0),		*
*		write-only mode (1) or read and write (2).						*
* MEANING																*
*	Returns the file's open mode, as indicate in the returned parameter.*
* SEE ALSO																*
************************************************************************/
int HashFile::getOpenMode(void)
{
	return openmode;
}

/************************************************************************
* FUNCTION																*
*	getBlockDesc														*
* PARAMETERS															*
*	blockDesk: an array fo integer containing the number of record in	*
*	the block *(this + i).												*
* RETURN VALUE															*
*	none									`							*
* MEANING																*
*	Indicates the number of records in each block. It is more safe to	*
*		use an array receievd as a parameter than to return one.		*
* SEE ALSO																*
************************************************************************/
void HashFile::getBlockDesc(int* blockDesc)
{
	blockDesc[0] = LogicalFHBuffer->FileSize;
	for(unsigned int blockNr = 1; blockNr < LogicalFHBuffer->FileSize; blockNr++)
	{
		readBlock(blockNr);
		blockDesc[blockNr] = LogicalBuffer->NrOfRecsInBlock;
	}
}

/************************************************************************
* FUNCTION																*
*	getFileSize															*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	int: the file's size in blocks (or KB).								*
* MEANING																*
*	Returns the file's size for functions that may need it.				*
* SEE ALSO																*
************************************************************************/
int HashFile::getFileSize(void)
{
	return LogicalFHBuffer->FileSize;
}

/************************************************************************
* FUNCTION																*
*	RecordsInBlock														*
* PARAMETERS															*
*	charKeys: a byte pointer that will contain the block's entire data.	*
*	blockNr: integer, the number of record in said block.				*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Returns valuable information on a block: its content and number of	*
*		records.														*
* SEE ALSO																*
************************************************************************/
int HashFile::RecordsInBlock(char* charKeys, int blockNr)
{
	readBlock(blockNr);
	memcpy(charKeys, LogicalBuffer->Data, 1024);
	return LogicalBuffer->NrOfRecsInBlock;
}

/************************************************************************
* FUNCTION																*
*	emptyVolume															*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	double: the percentage of volume available for more record in the	*
*		file.															*
* MEANING																*
*	Returns the percentage of remaining volume for more record in the	*
*		file in buffer.													*
* SEE ALSO																*
************************************************************************/
double HashFile::emptyVolume(void)
{
	readFH();
	double totalAvailable = 1024 / LogicalFHBuffer->RecordSize * LogicalFHBuffer->FileSize;
	double occupied = LogicalFHBuffer->NrOfRecsInFile;
	return 100 - ( occupied * 100 ) / totalAvailable;
}
