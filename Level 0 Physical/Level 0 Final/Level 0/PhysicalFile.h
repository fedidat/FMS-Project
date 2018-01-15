#pragma once
#include <fstream>
#include <string>
#include "Block.h"
using namespace std;

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
	PhysicalFile(string, string, int, unsigned int);
	PhysicalFile(string, string="", int=2);
	~PhysicalFile(void);
	//Creates the file on the physical level
	void pcreate(string, unsigned int=1000, string="");
	//Deletes the file
	void pdelete(void);
	//Opens the file on the physical file
	void popen(string, int=0, string="");
	//Closes the file
	void pclose(void);
	//Write a block
	void writeBlock(unsigned int);
	void writeBlock(void);
	//Read a block
	void readBlock(void);
	void readBlock(unsigned int);
	//Write the file header buffer
	void writeFH(void);
	//Read the file header buffer
	void readFH(void);
private:
	//----------------- Private methods --------------------
	//Moves the buffer to the the required block
	void SeekToBlock(unsigned int);
	//Indicates if the file already exists (no need to call pcreate)
	bool FileExists(string);
	//Initilizes all the blocks to strings of zeros
	void InitializeData(void);
};