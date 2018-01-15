#pragma once
#include "HashFile.h"
#include <time.h>

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
************************************************************************/
HashFile::HashFile(void)
{
	PhysicalFile();
	LogicalFHBuffer = (LogicalFileHeader*)&FHBuffer;
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
************************************************************************/
HashFile::HashFile(string fileName, string userName, unsigned int recordSize, string workingDir, int code)
{
	PhysicalFile();
	LogicalFHBuffer = (LogicalFileHeader*)&FHBuffer;
	LogicalBuffer = (LogicalBlock*)CurrBlock.Buffer;
	LHBuffChanged = false;
	LBuffChanged = false;
	UserName = "";
	unsigned int sizeOrMode;
	switch(code)
	{
	case 1:
		sizeOrMode = 1000;
		hcreate(fileName, userName, recordSize, workingDir, sizeOrMode);
		break;
	case 2:
		sizeOrMode = 0;
		hopen(fileName, userName, workingDir, sizeOrMode);
		break;
	default:
		throw exception("ERROR: Illegal operation code.");
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
************************************************************************/
HashFile::HashFile(string fileName, string userName, unsigned int recordSize, string workingDir, int code, unsigned int sizeOrMode, int keyPlace, char keyType, int keySize)
{
	LogicalFHBuffer = (LogicalFileHeader*)&FHBuffer;
	LogicalBuffer = (LogicalBlock*)CurrBlock.Buffer;
	LHBuffChanged = false;
	LBuffChanged = false;
	UserName = userName;
	PhysicalFile(fileName, workingDir, code, sizeOrMode);

	switch(code)
	{
	case 1:
		hcreate(fileName, userName, recordSize, workingDir, sizeOrMode, keyPlace, keyType, keySize);
		break;
	case 2:
		hopen(fileName, userName, workingDir, sizeOrMode);
		break;
	default:
		throw exception("ERROR: Illegal operation code.");
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
*	Destructor. Closes the file if not previously done and				*
*		the file has not been deleted. Simply uses pclose.				*
* SEE ALSO																*
************************************************************************/
HashFile::~HashFile(void)
{
	hclose();
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
*		pcreate. Subsequently fetches information inside the File		*
*		Header block and writes it into the file using writeFH.			*
* SEE ALSO																*
************************************************************************/
void HashFile::hcreate(string fileName, string userName, unsigned int recordSize, string workingDir, unsigned int fileSize, unsigned int keyPlace, char keyType, unsigned int keySize)
{
	pcreate(fileName, fileSize, workingDir);
	popen(fileName, 1, workingDir);
	readFH();
	strcpy(LogicalFHBuffer->FileName, fileName.c_str());
	strcpy(LogicalFHBuffer->OwnerName, userName.c_str());
	LogicalFHBuffer->FileSize = fileSize;
	_strdate(LogicalFHBuffer->CreationDate);	//mm/dd/yy format
	LogicalFHBuffer->RecordSize = recordSize;
	LogicalFHBuffer->NrOfRecsInFile = 0;
	LogicalFHBuffer->KeyOffset = keyPlace;
	LogicalFHBuffer->KeyType = keyType;
	LogicalFHBuffer->KeySize = keySize;
	writeFH();
}

/************************************************************************
* FUNCTION																*
*	hdelete																*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Deletes the file using pclose: all unsaved data is lost.			*
* SEE ALSO																*
************************************************************************/
void HashFile::hdelete(void)
{
	pdelete();
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
*		the file back, throws an exception and aborts.					*
* SEE ALSO																*
************************************************************************/
void HashFile::hopen(string fileName, string userName, string workingDir, int openMode)
{
	popen(fileName, openMode, workingDir);
	LBuffChanged = false;
	LHBuffChanged = false;
	UserName = userName;
	readFH();
	const char* charUser = UserName.c_str();
	if(openMode && strcmp(LogicalFHBuffer->OwnerName, charUser))
	{
		hclose();
		throw exception("ERROR: You do not have sufficient rights to open this file in writing mode.");
	}
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
************************************************************************/
void HashFile::hclose(void)
{
	flush(2);
	pclose();
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
************************************************************************/
void HashFile::flush(int buffer)
{
	if(!openmode)
		return;
	if(buffer == 0 && LHBuffChanged)
		writeFH();
	else if(buffer == 1 && LBuffChanged)
		writeBlock();
	else if(buffer == 2)
	{
		if(LHBuffChanged)
			writeFH();
		if(LBuffChanged)
			writeBlock();
	}
}