/**
 *	"Level 3"
 *	Copyright Pinhas Fedidat (ID 7665692), Aviram Michaeli (ID 302210224), 2011.
 *	For Dr. Moshe Goldstein, Project in File Management Systems, Jerusalem College of Technology.
 *	The software is provided "as is", without any warranty. 
 *	You are free to make any changes, as long as you keep this disclaimer in its present form.
 */

#define _CRT_SECURE_NO_WARNINGS	//prevents strcpy warnings
#include <iostream>	//include standard input/output header
#include "HashFile.h"	//include the physical and hash files implementations
#include "Library.h"	//include my library, containing an improved console output for errors and a standard one for HashFuncIDcodes
using namespace std;

/*********************************************************************************
********************************RECORDS DEFINITION********************************
*********************************************************************************/
struct cRecord
{
	//128 bytes = 7 records/block
	char ID[4];
	char firstName[50];
	char lastName[50];
	char city[24];
};
struct iRecord
{
	//128 bytes = 7 records/block
	int ID;
	char firstName[50];
	char lastName[50];
	char city[24];
};

/*********************************************************************************
*********************INTRODUCTORY FUNCTION ORDER PERSENTATION*********************
*********************************************************************************/
int MainMenu()
{
	int choice;
	cout<<"\t\t\t Main Menu"<<endl;
	cout<<"**********************OPERATIONS ON FILES**********************"<<endl;	//present the many options
	cout<<"1................................................ Create a File"<<endl;
	cout<<"2.................................................. Open a File"<<endl;
	cout<<"3................................................. Close a file"<<endl;
	cout<<"4................................................ Delete a File"<<endl;
	cout<<"5............................................... Write a Record"<<endl;
	cout<<"6................................................ Read a Record"<<endl;
	cout<<"7.............................................. Delete a Record"<<endl;
	cout<<"8.............................................. Update a Record"<<endl;
	cout<<"9..........................Test the Final win32 console version"<<endl;
	cout<<"0......................................................... EXIT"<<endl;
	cin>>choice;	//get the user's choice
	return choice;	//return it to the main function for use in the switch distributor
}

/*********************************************************************************
*****************************FILE OPERATION FUNCTIONS*****************************
*********************************************************************************/
void CreateFile(HashFile &file)
{
	char currentDir;
	cout<<"Do you want to create a file in the current directory? (Y/N)"<<endl;
	cin>>currentDir;
	int HashFuncID;	//user input for all the parameters, I will not detail this line by line
	unsigned int recordSize, fileSize, keyPlace, keySize;
	char keyType;
	string fileName, userName, workingDir;
	cout<<"Please enter the file name:"<<endl;
	cin>>fileName;
	cout<<"Please enter your name:"<<endl;
	cin>>userName;
	cout<<"Please enter the record size in bytes:"<<endl;
	cin>>recordSize;
	if(currentDir=='Y' || currentDir=='y')	//this allows for a single function for both relative and absolute folder addresses
		workingDir="";
	else
	{
		cout<<"Please enter the directory of the file: "<<endl;
		cin>>workingDir;
	}
	cout<<"Please enter the size of the file in blocks:"<<endl;
	cin>>fileSize;
	cout<<"Please enter the place of the key inside the record:"<<endl;
	cin>>keyPlace;
	cout<<"Please enter the type of the key: (integer-'I', char string-'C')"<<endl;
	cin>>keyType;
	cout<<"Please enter the size of the key in bytes:"<<endl;
	cin>>keySize;
	cout<<"Please enter the hash type:"<<endl;
	cin>>HashFuncID;
	file.hcreate(fileName, userName, recordSize, HashFuncID, workingDir, fileSize, keyPlace, keyType, keySize);	//call HashFile::hcreate
	cout<<"File successfully created as "<<fileName<<".hash."<<endl;
}
void OpenFile(HashFile &file)
{
	char currentDir;
	cout<<"Do you want to create a file in the current directory? (Y/N)"<<endl;
	cin>>currentDir;
	int openMode;	//input hopen parameters
	string fileName, userName, workingDir;
	cout<<"Please enter the file name:"<<endl;
	cin>>fileName;
	cout<<"Please enter your name:"<<endl;
	cin>>userName;
	if(currentDir=='Y' || currentDir=='y')	//this allows for a single function for both relative and absolute folder addresses
		workingDir="";
	else
	{
		cout<<"Please enter the directory of the file: "<<endl;
		cin>>workingDir;
	}
	cout<<"Please enter the opening mode: (read-0, write-1, both-2)"<<endl;
	cin>>openMode;
	file.hopen(fileName, userName, workingDir, openMode);	//call HashFile::hopen
	cout<<"File successfully opened."<<endl;
}

void WriteToFile(HashFile &file)
{
	switch(file.getKeyType())
	{
	case 'S':
		{
			cRecord record;	//input record variables
			cout<<"Please enter the key:"<<endl;
			cin>>record.ID;
			cout<<"Please enter the first name:"<<endl;
			cin>>record.firstName;
			cout<<"Please enter the last name:"<<endl;
			cin>>record.lastName;
			cout<<"Please enter the city of residence:"<<endl;
			cin>>record.city;
			char* ptr = (char*)(&record);
			file.write(string(record.ID), ptr);	//write the record to the file by calling the proper HashFile::write
			cout<<"Record successfully written."<<endl;
		}
		break;
	case 'C':
		{
			cRecord record;	//input record variables
			cout<<"Please enter the key:"<<endl;
			cin>>record.ID;
			cout<<"Please enter the first name:"<<endl;
			cin>>record.firstName;
			cout<<"Please enter the last name:"<<endl;
			cin>>record.lastName;
			cout<<"Please enter the city of residence:"<<endl;
			cin>>record.city;
			char* ptr = (char*)(&record);
			file.write(record.ID, ptr);	//write the record to the file by calling the proper HashFile::write
			cout<<"Record successfully written."<<endl;
		}
		break;
	case 'I':
		{
			iRecord record;	//input record variables
			cout<<"Please enter the key:"<<endl;
			cin>>record.ID;
			cout<<"Please enter the first name:"<<endl;
			cin>>record.firstName;
			cout<<"Please enter the last name:"<<endl;
			cin>>record.lastName;
			cout<<"Please enter the city of residence:"<<endl;
			cin>>record.city;
			char* ptr = (char*)(&record);
			file.write(record.ID, ptr);	//write the record to the file by calling the proper HashFile::write
			cout<<"Record successfully written."<<endl;
		}
		break;
	default:
		throwErr("ERROR: Illegal choice input");
	}
}
void ReadFromFile(HashFile &file)
{
	switch(file.getKeyType())
	{
	case 'S':
		{
			string key;
			cout<<"What is the key of the record?"<<endl;
			cin>>key;	//get the key of the record that the program has to read
			cRecord record;
			char* ptr = (char*)&record;
			file.read(key, ptr);	//read the record with the given key into the char pointer to the record using HashFile::read
			cout<<"#"<<record.ID<<" is "<<record.firstName<<" "<<record.lastName<<"; he lives in "<<record.city<<"."<<endl;	//display the record's content
		}
		break;
	case 'C':
		{
			char key[4];
			cout<<"What is the key of the record?"<<endl;
			cin>>key;	//get the key of the record that the program has to read
			cRecord record;
			char* ptr = (char*)&record;
			file.read(key, ptr);	//read the record with the given key into the char pointer to the record using HashFile::read
			cout<<"#"<<record.ID<<" is "<<record.firstName<<" "<<record.lastName<<"; he lives in "<<record.city<<"."<<endl;	//display the record's content
		}
		break;
	case 'I':
		{
			int key;
			cout<<"What is the key of the record?"<<endl;
			cin>>key;	//get the key of the record that the program has to read
			iRecord record;
			char* ptr = (char*)&record;
			file.read(key, ptr);	//read the record with the given key into the char pointer to the record using HashFile::read
			cout<<"#"<<record.ID<<" is "<<record.firstName<<" "<<record.lastName<<"; he lives in "<<record.city<<"."<<endl;	//display the record's content
		}
		break;
	default:
		throwErr("ERROR: Illegal choice input");
	}
}
void DeleteRecord(HashFile &file)
{
	switch(file.getKeyType())
	{
	case 'S':
		{
			string key;
			cout<<"What is the key of the record?"<<endl;
			cin>>key;	//get the key of the record that is to be deleted
			file.read(key, new char[128], 1);	//we only read the record in order to get in in the buffer, not to actually get its content
			file.delrec();	//delete the record using HashFile::delrec
			file.updateoff();	//update-unlock the record using HashFile::updateoff
		}
		break;
	case 'C':
		{
			char key[4];
			cout<<"What is the key of the record?"<<endl;
			cin>>key;	//get the key of the record that is to be deleted
			file.read(key, new char[128], 1);	//we only read the record in order to get in in the buffer, not to actually get its content
			file.delrec();	//delete the record using HashFile::delrec
			file.updateoff();	//update-unlock the record using HashFile::updateoff
		}
		break;
	case 'I':
		{
			int key;
			cout<<"What is the key of the record?"<<endl;
			cin>>key;	//get the key of the record that is to be deleted
			file.read(key, new char[128], 1);	//we only read the record in order to get in in the buffer, not to actually get its content
			file.delrec();	//delete the record using HashFile::delrec
			file.updateoff();	//update-unlock the record using HashFile::updateoff
		}
		break;
	default:
		throwErr("ERROR: Illegal choice input");
	}
}
void UpdateRecord(HashFile &file)
{
	switch(file.getKeyType())
	{
	case 'S':
		{
			cRecord record;	//fill the updated record
			char* ptr = (char*)&record;
			cout<<"What is the key of the record?"<<endl;
			cin>>record.ID;
			cout<<"Please enter the first name:"<<endl;
			cin>>record.firstName;
			cout<<"Please enter the last name:"<<endl;
			cin>>record.lastName;
			cout<<"Please enter the city of residence:"<<endl;
			cin>>record.city;
			file.read(string(record.ID), new char[128], 1);	//read the old record into HashFile's buffer
			file.update(ptr);	//update the record with a pointer to the new record using HashFile::update
			file.updateoff();	//update-unlock the record using HashFile::updateoff
		}
		break;
	case 'C':
		{
			cRecord record;	//fill the updated record
			char* ptr = (char*)&record;
			cout<<"What is the key of the record?"<<endl;
			cin>>record.ID;
			cout<<"Please enter the first name:"<<endl;
			cin>>record.firstName;
			cout<<"Please enter the last name:"<<endl;
			cin>>record.lastName;
			cout<<"Please enter the city of residence:"<<endl;
			cin>>record.city;
			file.read(record.ID, new char[128], 1);	//read the old record into HashFile's buffer
			file.update(ptr);	//update the record with a pointer to the new record using HashFile::update
			file.updateoff();	//update-unlock the record using HashFile::updateoff
		}
		break;
	case 'I':
		{
			iRecord record;	//fill the updated record
			char* ptr = (char*)&record;
			cout<<"What is the key of the record?"<<endl;
			cin>>record.ID;
			cout<<"Please enter the first name:"<<endl;
			cin>>record.firstName;
			cout<<"Please enter the last name:"<<endl;
			cin>>record.lastName;
			cout<<"Please enter the city of residence:"<<endl;
			cin>>record.city;
			file.read(record.ID, new char[128], 1);	//read the old record into HashFile's buffer
			file.update(ptr);	//update the record with a pointer to the new record using HashFile::update
			file.updateoff();	//update-unlock the record using HashFile::updateoff
		}
		break;
	default:
		throwErr("ERROR: Illegal choice input");
	}
}

void DelUpTest()
{
	//Phase 0: Prepare the files and the records (constructor, hcreate, hopen)
	HashFile test;
	test.hcreate("test", "user", 128, 0, "", 10);
	test.hopen("test", "user", "", 2);

	iRecord wRec;
	char* ptw = (char*)(&wRec);
	strcpy(wRec.firstName, "[forename]");
	strcpy(wRec.lastName,"[lastname]");
	strcpy(wRec.city, "[place]");
	iRecord rRec;
	char* ptr = (char*)(&rRec);
	iRecord pRec;
	char* ptu = (char*)(&pRec);
	strcpy(pRec.firstName, "now");
	strcpy(pRec.lastName, "anonymous");
	strcpy(pRec.city, "[hidden]");

	//Phase 1: Write a couple of records (write)
	for(wRec.ID = 0 ; wRec.ID <= 88 ; wRec.ID += (!(wRec.ID%11))?1:10)
		test.write(wRec.ID, ptw);

	//Phase 2: Reading some records before delete/update (read)
	cout<<"Before update: "<<endl;
	test.read(88, ptr);
	cout<<"Reading record #88: #"<<rRec.ID<<" is "<<rRec.firstName<<" "<<rRec.lastName<<"; he lives in "<<rRec.city<<"."<<endl;
	test.read(45, ptr);
	cout<<"Reading record #45: #"<<rRec.ID<<" is "<<rRec.firstName<<" "<<rRec.lastName<<"; he lives in "<<rRec.city<<"."<<endl;

	//Phase 2: Testing the last functions (delete, update)
	test.read(88, ptr, 1);
	test.delrec();
	test.updateoff();

	pRec.ID = 45;
	test.read(pRec.ID, ptr, 1);
	test.update(ptu);
	test.updateoff();

	//Phase 3: Check the results after delete/update (read)
	cout<<"After update: \nReading record #88: ";
	try{
		test.read(88, ptr);
		cout<<"#"<<rRec.ID<<" is "<<rRec.firstName<<" "<<rRec.lastName<<"; he lives in "<<rRec.city<<"."<<endl;
	}
	catch (exception ex){
		cout<<ex.what();
	}
	test.read(45, ptr);
	cout<<"Reading record #45: #"<<rRec.ID<<" is "<<rRec.firstName<<" "<<rRec.lastName<<"; he lives in "<<rRec.city<<"."<<endl;

	//Phase 4: Cleaning off (close, delete)
	test.hclose();
	test.hdelete();
}

/*********************************************************************************
***************************WIN32 CONSOLE USER INTERFACE***************************
*********************************************************************************/
int main()
{
	HashFile file;
	int choice;
	choice = MainMenu(); 
	while (choice)
	{
		try
		{
			switch (choice)
			{
			case 1:
				CreateFile(file);	//create a file
				break;
			case 2:
				OpenFile(file);	//open a file
				break;
			case 3:
				file.hclose();	//close a file
				cout<<"File successfully closed."<<endl;
				break;
			case 4:
				file.hdelete();	//delete a file
				cout<<"File successfully deleted."<<endl;
				break;
			case 5:
				WriteToFile(file);	//write a record
				break;
			case 6:
				ReadFromFile(file);	//read a record
				break;
			case 7:
				DeleteRecord(file);	//delete a record
				break;
			case 8:
				UpdateRecord(file);	//update a record
				break;
			case 9:
				DelUpTest();	//call level 3's test function
				break;
			default:
				throwErr("ERROR: Illegal choice number");
			}
		}
		catch (exception ex)
		{
			cout<<ex.what();
		}
		cout<<endl;
		choice = MainMenu();
	}
	system("pause");
	return 0;
}