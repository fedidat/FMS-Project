#pragma once
#include <fstream>
#include <string>
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
public:
	CurrentBlock CurrBlock;	//Physical buffer for the current block
	//------------------ API methods -----------------------
	PhysicalFile(void);
	PhysicalFile(string fileName, string workingDir="", int code=2);
	PhysicalFile(string fileName, string workingDir, int code, unsigned int sizeOrMode);
	~PhysicalFile(void);
	//Creates a file on the physical level
	void pcreate(string fileName, unsigned int fileSize=1000, string workingDir="");
	//Deletes a file
	void pdelete(void);
	//Opens a file on the physical file
	void popen(string fileName, int openMode=0, string workingDir="");
	//Closes a file
	void pclose(void);
	//Writes a block
	void writeBlock(void);
	void writeBlock(unsigned int position);
	//Reads a block
	void readBlock(void);
	void readBlock(unsigned int position);
	//Writes the file header buffer
	void writeFH(void);
	//Reads the file header buffer
	void readFH(void);
private:
	//----------------- Private methods --------------------
	//Moves the buffer to the the required block
	void SeekToBlock(unsigned int);
	//Indicates if the file already exists (no need to call pcreate)
	bool FileExists(string filePath);
	//Initializes all the blocks to strings of zeros
	void InitializeData(void);
};