#pragma once
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
	opened = false;
	FileName = "";
}

/************************************************************************
* FUNCTION																*
*	PhysicalFile														*
* PARAMETERS															*
*	name: string, the name of the file.									*
*	path: string, the directory of the file.							*
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
* SEE ALSO																*
************************************************************************/
PhysicalFile::PhysicalFile(string name, string path, int code, unsigned int sizeOrMode)
{
	FileName = name;
	if(path!="")
		WorkingDir = path;
	switch(code)
	{
	case 1:
		pcreate(name,sizeOrMode,path);
		break;
	case 2:
		popen(name,sizeOrMode,path);
		break;
	default:
		throw exception("ERROR: Illegal operation code.");
	}
}

/************************************************************************
* FUNCTION																*
*	PhysicalFile														*
* PARAMETERS															*
*	name: string, the name of the file.									*
*	path: string, the directory of the file.							*
*	code: integer, 1 if the file doesn't already exists, 2 otherwise.	*
*		Gives a	meaning to the fourth parameter.						*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Full constructor. Assigns values to the variables and calls			*
*		the functions necessary to the creation or the opening of the	*
*		file.															*
*	Same as the function with sizeOrMode provided, just artificially	*
*		assigned.														*
* SEE ALSO																*
************************************************************************/
PhysicalFile::PhysicalFile(string name, string path, int code)
{
	FileName = name;
	if(path!="")
		WorkingDir = path;
	int sizeOrMode;
	switch(code)
	{
	case 1:
		sizeOrMode = 1000;
		pcreate(name,sizeOrMode,path);
		break;
	case 2:
		sizeOrMode = 0;
		popen(name,sizeOrMode,path);
		break;
	default:
		throw exception("ERROR: Illegal operation code.");
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
************************************************************************/
PhysicalFile::~PhysicalFile(void)
{
	if(opened == true && FileName != "")
		pclose();
}

/************************************************************************
* FUNCTION																*
*	pcreate																*
* PARAMETERS															*
*	name: string, the name of the file.									*
*	path: string, the directory of the file.							*
*	size: positive integer, the size of the file in blocks.				*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Creates the file as a series of empty physical Blocks.				*
* SEE ALSO																*
************************************************************************/
void PhysicalFile::pcreate(string name, unsigned int size, string path)
{	
	string filePath = path + name + ".hash";
	if(FileExists(filePath))
		throw exception("ERROR: File already exists.");
	else
	{
		Filefl.open(filePath, ios::binary | ios::out);
		opened = true;
		FileSize = size;
		InitializeData();
		pclose();
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
	if(opened == false)
	{
		string letsdo=WorkingDir+FileName+".hash";
		if(remove((WorkingDir+FileName+".hash").c_str())!=0)
			throw exception("ERROR: File deleting failed.");
		FileName = "";
	}
	else
		throw exception("ERROR: File is still open");
}

/************************************************************************
* FUNCTION																*
*	popen																*
* PARAMETERS															*
*	name: string, the name of the file.									*
*	path: string, the directory of the file.							*
*	mode: I/O opening mode: 0 for input, 1 for output, 2 for both.		* 
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Opens the file for input/output/both.								*
* SEE ALSO																*
************************************************************************/
void PhysicalFile::popen(string name, int mode, string path)
{
	FileName = name;
	openmode = mode;
	WorkingDir = path;
	char* filePath = new char[path.length()+name.length()+5];
	strcpy(filePath,(path+name+".hash").c_str());
	Filefl.open(filePath, ios::binary | ios::in);
	if(!Filefl)
		throw exception("ERROR: File does not exist.");
	readFH();
	if(openmode)
	{
		Filefl.close();
		Filefl.open((path+name+".hash").c_str(), ios::binary | ios::in | ios::out);
		if(Filefl)
		{
			opened = true;
			CurrBlock.Nr = -1;
		}
	}
	else
	{
		opened = true;
		CurrBlock.Nr = -1;
	}
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
*	block: positive integer, the block's number.						*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Writes a block to the desired block number.							*
* SEE ALSO																*
************************************************************************/
void PhysicalFile::writeBlock(unsigned int block)
{
	SeekToBlock(block);
	Filefl.write(reinterpret_cast<char*>(&CurrBlock.Buffer),sizeof(PhysicalBlock));
	CurrBlock.Nr++;
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
	Filefl.write(reinterpret_cast<char*>(&CurrBlock.Buffer),sizeof(PhysicalBlock));
	CurrBlock.Nr++;
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
************************************************************************/
void PhysicalFile::readBlock(void)
{
	SeekToBlock(CurrBlock.Nr);
	Filefl.read(reinterpret_cast<char*>(&CurrBlock.Buffer),sizeof(PhysicalBlock));
	CurrBlock.Nr++;
}

/************************************************************************
* FUNCTION																*
*	readBlock															*
* PARAMETERS															*
*	block: positive integer, the block's number.						*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Reads from the desired block.										*
* SEE ALSO																*
************************************************************************/
void PhysicalFile::readBlock(unsigned int block)
{
	SeekToBlock(block);
	Filefl.read(reinterpret_cast<char*>(&CurrBlock.Buffer),sizeof(PhysicalBlock));
	CurrBlock.Nr++;
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
************************************************************************/
void PhysicalFile::writeFH(void)
{
	SeekToBlock(0);
	Filefl.read(reinterpret_cast<char*>(&FHBuffer),sizeof(PhysicalBlock));
	CurrBlock.Nr++;
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
************************************************************************/
void PhysicalFile::readFH(void)
{
	SeekToBlock(0);
	Filefl.write(reinterpret_cast<char*>(&FHBuffer),sizeof(PhysicalBlock));
	CurrBlock.Nr++;
}

/************************************************************************
* FUNCTION																*
*	SeekToBlock															*
* PARAMETERS															*
*	block: positive integer, the block's number.						*
* RETURN VALUE															*
*	none																*
* MEANING																*
*	Changes the position of the current block to the desired block,		*
*		for future use of read/write block functions.					*
* SEE ALSO																*
************************************************************************/
void PhysicalFile::SeekToBlock(unsigned int block)
{
	if(block > FileSize)
		throw exception("ERROR: Block does not exist.");
	int ByteNumber = (block*BlockLength);	//plus 2?
	Filefl.seekg(ByteNumber);
	Filefl.seekp(ByteNumber);
	CurrBlock.Nr = block;
}

/************************************************************************
* FUNCTION																*
*	FileExists															*
* PARAMETERS															*
*	filePath: string, represents the path to the file to be checked.	*
* RETURN VALUE															*
*	bool, true if the file already exists, false otherwise.				*
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
************************************************************************/
void PhysicalFile::InitializeData(void)
{
	PhysicalBlock Empty;
	Empty.Initialize();
	CurrBlock.Buffer = Empty;
	CurrBlock.Nr=0;
	for(CurrBlock.Buffer.BlockNr=0;CurrBlock.Buffer.BlockNr<FileSize;CurrBlock.Buffer.BlockNr++)
	{
		SeekToBlock(CurrBlock.Nr);
		writeBlock();
	}
	CurrBlock.Nr=-1;
}