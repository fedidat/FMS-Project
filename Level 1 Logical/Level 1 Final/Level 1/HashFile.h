#pragma once
#include "PhysicalFile.h"

/****************************************************************************
*	LogicalFile class, uses the PhsyicalFile class and manipulates the		*
*	buffer, for both logical data blocks and file header.					*
****************************************************************************/

class HashFile : public PhysicalFile
{
	//------------------- Data Members ---------------------
	string UserName;	//Indicates the name of the current user
	LogicalBlock* LogicalBuffer;	//Logical buffer for the current block
	LogicalFileHeader* LogicalFHBuffer;	//Logical buffer for the file header
	bool updateflag;	//Indicates if the last block read was modified
	bool LBuffChanged;	//Indicates if the current block was modified since the last update
	bool LHBuffChanged;	//Indicates if the file header was modified since the last update
	unsigned int CurrRecNrInBuffer;	//Number of the current record in the buffer
public:
	//--------------------- Methods ------------------------
	HashFile(void);
	HashFile(string fileName, string userName, unsigned int recordSize, string workingDir="", int code=2);
	HashFile(string fileName, string userName, unsigned int recordSize, string workingDir, int code, unsigned int sizeOrMode, int keyPlace=0, char keyType='I', int keySize=4);
	~HashFile(void);
	//Creates the file
	void hcreate(string fileName, string userName, unsigned int recordSize, string WorkingDir="", unsigned int fileSize=1000, unsigned int keyPlace=0, char keyType='I', unsigned int keySize=4);
	//Deletes the file
	void hdelete(void);
	//Opens the file
	void hopen(string fileName, string userName, string workingDir, int openMode);
	//Closes the file
	void hclose(void);
	//Flushes the logical/file header buffers
	void flush(int buffer=1);
};