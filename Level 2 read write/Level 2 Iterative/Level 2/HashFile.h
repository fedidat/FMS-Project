#pragma once
#include "PhysicalFile.h"
#include "HashValue.h"

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
	HashValue* hashVal;	//HashValue class used to compute the place of the records.
public:
	//--------------------- Methods ------------------------
	//Default constructor
	HashFile(void);
	//Partial constructor
	HashFile(string fileName, string userName, unsigned int recordSize, int HashFuncID, string workingDir="", int code=2);
	//Full constructor
	HashFile(string fileName, string userName, unsigned int recordSize, string workingDir, int code, unsigned int sizeOrMode, int HashFuncID, int keyPlace=0, char keyType='I', int keySize=4);
	//Destructor
	~HashFile(void);
	//Create a file
	void hcreate(string fileName, string userName, unsigned int recordSize, int HashFuncID, string WorkingDir="", unsigned int fileSize=1000, unsigned int keyPlace=0, char keyType='I', unsigned int keySize=4);
	//Delete a file
	void hdelete(void);
	//Open a file
	void hopen(string fileName, string userName, string workingDir, int openMode);
	//Close a file
	void hclose(void);
	//Flush a logical/file header buffers
	void flush(int buffer=1);
private:
	//Seeks a record in the currently opened file with the same C string key as the variable key
	bool seek(char* key);
	//Seeks a record in the currently opened file with the same integer key as the variable key
	bool seek(int key);
	//Seeks a record in a single specified block with a char* key
	bool seekInBlock(int position, char* key);
	//Seeks a record in a single specified block with an integer key
	bool seekInBlock(int position, int key);
public:
	//Read a record with a C++ string key
	void read(string& key, char* record, int readType=0);
	//Read a record with a C string key
	void read(char* key, char* record, int readType=0);
	//Read a record with an integer key
	void read(int key, char* record, int readType=0);
	//Write a record with a C++ string key
	void write(string& key, char* record);
	//Write a record with a C string key
	void write(char* key, char* record);
	//Write a record with an integer key
	void write(int key, char* record);
private:
	//Attempts to write a record in a single specified block
	bool writeInBlock(int position, char* record);
public:
	//Calculates the absolute deviation of the records in the file
	float deviation(void);
private:
	//Flushes the LogicalBuffer if necessary and reads the current block
	void readBlock(void);
	//Flushes the LogicalBuffer if necessary and reads a block
	void readBlock(unsigned int position);
	//Flushes the LogicalFHBuffer if necessary and reads the file header
	void readFH(void);
};