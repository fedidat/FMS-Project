#pragma once
#include <fstream>
#include <string>
#include "Library.h"
#include "Block.h"
using namespace std;

/****************************************************************************
*	PhysicalFile class, simulates a file on the Physical level,				*
*	responsible for I/O and manipulations with basic PhyicalBlock class.	*
****************************************************************************/

class PhysicalFile
{
protected:
	//------------------- Data Members ---------------------
	bool opened;	//Indicates if the file is open
	int openmode;	//Indicates if the file is open for input, output or both
	fstream Filefl;	//The file stream
	string WorkingDir;	//The file path
	string FileName;
	unsigned int FileSize;
	PhysicalBlock FHBuffer;	//Physical buffer for the file header
	CurrentBlock CurrBlock;	//Physical buffer for the current block
public:
	//------------------ API methods -----------------------
	PhysicalFile(void);
	PhysicalFile(string fileName, string workingDir="", int code=2);
	PhysicalFile(string fileName, string workingDir, int code, unsigned int sizeOrMode);
	~PhysicalFile(void);
	//Create a file on the physical level
	void pcreate(string fileName, unsigned int fileSize=1000, string workingDir="");
	//Delete a file
	void pdelete(void);
	//Open a file on the physical file
	void popen(string fileName, int openMode=0, string workingDir="");
	//Close a file
	void pclose(void);
	//Write a block
	void writeBlock(void);
	//Write a block
	void writeBlock(unsigned int position);
	//Read a block
	void readBlock(void);
	//Read a block
	void readBlock(unsigned int position);
	//Read the file header buffer
	void readFH(void);
	//Write the file header buffer
	void writeFH(void);
private:
	//----------------- Private methods --------------------
	//Move the buffer to the the required block
	void SeekToBlock(unsigned int);
	//Indicate if the file already exists (no need to call pcreate)
	bool FileExists(string filePath);
	//Initialize all the blocks to strings of zeros
	void InitializeData(void);
};