#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include "PhysicalFile.h"
using namespace std;

/************************************************************************
* FUNCTION																*
*	PhysicalFile														*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Default constructor: creates an empty class for a future physical	*
*	file.																*
* SEE ALSO																*
************************************************************************/
PhysicalFile::PhysicalFile(void)
{
	opened = false;	//initialize the class's variables
	FileName = "";
}

/************************************************************************
* FUNCTION																*
*	PhysicalFile														*
* PARAMETERS															*
*	fileName: string, the name of the file.								*
*	workingDir: string, the directory of the file.						*
*	code: integer, 1 if the file doesn't already exists, 2 otherwise.	*
*		Gives a	meaning to the fourth parameter.						*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Full constructor. Assigns values to the variables and calls			*
*		the functions necessary to the creation or the opening of the	*
*		file.															*
* SEE ALSO																*
*	PhysicalFile::pcreate, PhysicalFile::popen.							*
************************************************************************/
PhysicalFile::PhysicalFile(string fileName, string workingDir, int code)
{
	FileName = fileName;	//initialize the class's variables
	WorkingDir = workingDir;
	int sizeOrMode;
	switch(code)	//depending on the code, we will now want to create or to open a file
	{
	case 1:
		sizeOrMode = 1000;
		pcreate(fileName, sizeOrMode, workingDir);
		break;
	case 2:
		sizeOrMode = 0;
		popen(fileName, sizeOrMode, workingDir);
		break;
	default:	//should have used the default constructor if you didn't want to create or to open a file now
		throwErr("ERROR: Illegal operation code");
	}
}

/************************************************************************
* FUNCTION																*
*	PhysicalFile														*
* PARAMETERS															*
*	fileName: string, the name of the file.								*
*	workingDir: string, the directory of the file.						*
*	code: integer, 1 if the file doesn't already exists, 2 otherwise.	*
*		Gives a	meaning to the fourth parameter.						*
*	sizeOrMode: positive integer, if code 1, size of the file, and if	*
*		code 2, I/O opening mode.										*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Full constructor. Assigns values to the variables and calls			*
*		the functions necessary to the creation or the opening of the	*
*		file.															*
*	Same as the function without sizeOrMode provided, with this field	*
*		provided by the user.											*
* SEE ALSO																*
*	PhysicalFile::pcreate, PhysicalFile::popen.							*
************************************************************************/
PhysicalFile::PhysicalFile(string fileName, string workingDir, int code, unsigned int sizeOrMode)
{
	FileName = fileName;	//initialize the class's variables
	WorkingDir = workingDir;
	switch(code)	//depending on the code, we will now want to create or to open a file
	{
	case 1:
		pcreate(fileName, sizeOrMode, workingDir);
		break;
	case 2:
		popen(fileName, sizeOrMode, workingDir);
		break;
	default:
		throwErr("ERROR: Illegal operation code");
	}
}

/************************************************************************
* FUNCTION																*
*	~PhysicalFile														*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Destructor. Closes the file if not previously done and				*
*		the file has not been deleted.									*
* SEE ALSO																*
*	PhysicalFile::pclose.												*
************************************************************************/
PhysicalFile::~PhysicalFile(void)
{
	if(opened == true && FileName != "")	//it makes no sense to close a file that is not opened or has been deleted
		pclose();	//we destroy the class by closing the file
}

/************************************************************************
* FUNCTION																*
*	pcreate																*
* PARAMETERS															*
*	fileName: string, the name of the file.								*
*	workingDir: string, the directory of the file.						*
*	fileSize: positive integer, the size of the file in blocks.			*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Creates the file as a series of empty physical Blocks.				*
* SEE ALSO																*
*	PhysicalFile::InitializeData, PhysicalFile::pclose.					*
************************************************************************/
void PhysicalFile::pcreate(string fileName, unsigned int fileSize, string workingDir)
{	
	string filePath = workingDir + fileName + ".hash";	//I find it more efficient to store the complete path than add it twice, but I may be wrong
	if(FileExists(filePath))	//if a file with the same name exists, it can't be created again before it is deleted
		throwErr("ERROR: The file could not be created", true);
	else
	{
		Filefl.open(filePath, ios::binary | ios::out);	//opening the file for output will 'create' it
		opened = true;	//initilizing opened and FileSize class variables
		FileSize = fileSize;
		InitializeData();	//initlize the data blocks by filling the file with binary zeros
		pclose();	//closing the file
	}
}

/************************************************************************
* FUNCTION																*
*	pdelete																*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Deletes the file on the physical level: all unsaved data is lost.	*
* SEE ALSO																*
************************************************************************/
void PhysicalFile::pdelete(void)
{
	if(opened)	//if the file is still opened, it cannot be deleted
		throwErr("ERROR: The file is still opened", true);
	else	//if the file has been closed beforehand, it can be deleted
	{
		if(remove((WorkingDir + FileName + ".hash").c_str()) != 0)	//if the file could not be deleted for some reason
			throwErr("ERROR: Failed to delete the file", true);	//display the errno error code, abort
		FileName = "";	//if it has been done, the file's name is "removed"
	}
}

/************************************************************************
* FUNCTION																*
*	popen																*
* PARAMETERS															*
*	fileName: string, the name of the file.								*
*	mode: I/O opening mode: 0 for input, 1 for output, 2 for both.		* 
*	workingDir: string, the directory of the file.						*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Opens the file for input/output/both.								*
* SEE ALSO																*
*	PhysicalFile::readFH												*
************************************************************************/
void PhysicalFile::popen(string fileName, int mode, string workingDir)
{
	Filefl.open((workingDir + fileName + ".hash").c_str(), ios::in | ios::binary);	//open in read-only mode
	if(!Filefl)	//if the file did not open in read-only mode, display error and exception
		throwErr("ERROR: The file could not be opened", true);
	readFH();
	if(mode == 0)
	{
		opened = true;
		CurrBlock.Nr = -1;
	}
	else if(mode == 1 || mode == 2)
	{
		Filefl.close();
		Filefl.open((workingDir + fileName + ".hash").c_str(), ios::in | ios::out | ios::binary);
		if(Filefl)
		{
			opened = true;
			CurrBlock.Nr = -1;
		}
		else
			throwErr("ERROR: The file could not be opened in output mode", true);
	}
	else
		throwErr("ERROR: Illegal open mode input");

	FileName = fileName;	//the file has successfully been opened, now initializing some variables
	openmode = mode;
	WorkingDir = workingDir;
	CurrBlock.Buffer = new PhysicalBlock();
}

/************************************************************************
* FUNCTION																*
*	pclose																*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Closes the file if it was not previously closed						*
* SEE ALSO																*
************************************************************************/
void PhysicalFile::pclose(void)
{
	if(opened)
	{
		Filefl.close();
		opened = false;
	}
}

/************************************************************************
* FUNCTION																*
*	writeBlock															*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Writes a block to the current block.								*
* SEE ALSO																*
************************************************************************/
void PhysicalFile::writeBlock(void)
{
	SeekToBlock(CurrBlock.Nr);
	Filefl.write(reinterpret_cast<char*>(CurrBlock.Buffer), sizeof(PhysicalBlock));
}

/************************************************************************
* FUNCTION																*
*	writeBlock															*
* PARAMETERS															*
*	position: positive integer, the block's position.					*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Writes a block to the desired block number.							*
* SEE ALSO																*
*	PhysicalFile::SeekToBlock.											*
************************************************************************/
void PhysicalFile::writeBlock(unsigned int position)
{
	SeekToBlock(position);
	Filefl.write(reinterpret_cast<char*>(CurrBlock.Buffer), sizeof(PhysicalBlock));
}

/************************************************************************
* FUNCTION																*
*	readBlock															*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Reads from the current block.										*
* SEE ALSO																*
*	PhysicalFile::SeekToBlock.											*
************************************************************************/
void PhysicalFile::readBlock(void)
{
	SeekToBlock(CurrBlock.Nr);
	Filefl.read(reinterpret_cast<char*>(CurrBlock.Buffer), sizeof(PhysicalBlock));
}

/************************************************************************
* FUNCTION																*
*	readBlock															*
* PARAMETERS															*
*	position: positive integer, the block's position.					*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Reads from the desired block.										*
* SEE ALSO																*
*	PhysicalFile::SeekToBlock.											*
************************************************************************/
void PhysicalFile::readBlock(unsigned int position)
{
	SeekToBlock(position);
	Filefl.read(reinterpret_cast<char*>(CurrBlock.Buffer), sizeof(PhysicalBlock));
}

/************************************************************************
* FUNCTION																*
*	writeFH																*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Writes the metadata block at position 0.							*
* SEE ALSO																*
*	PhysicalFile::SeekToBlock.											*
************************************************************************/
void PhysicalFile::writeFH(void)
{
	SeekToBlock(0);
	Filefl.write(reinterpret_cast<char*>(&FHBuffer), sizeof(PhysicalBlock));
}

/************************************************************************
* FUNCTION																*
*	readFH																*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Reads the metadata block at position 0.								*
* SEE ALSO																*
*	PhysicalFile::SeekToBlock.											*
************************************************************************/
void PhysicalFile::readFH(void)
{
	SeekToBlock(0);
	Filefl.read(reinterpret_cast<char*>(&FHBuffer), sizeof(PhysicalBlock));
}

/************************************************************************
* FUNCTION																*
*	SeekToBlock															*
* PARAMETERS															*
*	position: positive integer, the block's position.					*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Changes the position of the current block to the desired block,		*
*		for future use of read/write block functions.					*
* SEE ALSO																*
*	PhysicalFile::SeekToBlock.											*
************************************************************************/
void PhysicalFile::SeekToBlock(unsigned int position)
{
	if(position > FileSize)
		throwErr("ERROR: Block does not exist");
	int ByteNumber = (position*BlockLength);
	Filefl.seekg(ByteNumber);
	Filefl.seekp(ByteNumber);
	CurrBlock.Nr = position;
}

/************************************************************************
* FUNCTION																*
*	FileExists															*
* PARAMETERS															*
*	filePath: string, represents the path to the file to be checked.	*
* RETURN VALUE															*
*	bool: true if the file already exists, false otherwise.				*
* MEANING																*
*	Checks if the file already exists, used by functions such as the	*
*		pcreate.														*
* SEE ALSO																*
************************************************************************/
bool PhysicalFile::FileExists(string filePath)
{
	fstream FileOpen(filePath.c_str(), ios::binary | ios::in);
	if(FileOpen)
	{
		FileOpen.close();
		return true;
	}
	FileOpen.close();
	return false;
}

/************************************************************************
* FUNCTION																*
*	InitializeData														*
* PARAMETERS															*
*	none																*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Initializes all blocks in the file to "empty" blocks (their data is	*
*		a string of zeros).												*
* SEE ALSO																*
*	PhysicalFile::SeekToBlock, PhysicalFile::writeBlock.				*
************************************************************************/
void PhysicalFile::InitializeData(void)
{
	PhysicalBlock Empty;
	CurrBlock.Buffer = &Empty;
	CurrBlock.Nr=0;
	for(CurrBlock.Buffer->BlockNr=0 ; CurrBlock.Buffer->BlockNr < FileSize ; CurrBlock.Buffer->BlockNr++)
	{
		writeBlock(CurrBlock.Buffer->BlockNr);
	}
	CurrBlock.Nr=-1;
}