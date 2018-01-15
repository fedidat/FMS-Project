/**
 *	"Level 2"
 *	Copyright Pinhas Fedidat (ID 7665692), Aviram Michaeli (ID 302210224), 2011.
 *	For Dr. Moshe Goldstein, Project in File Management Systems, Jerusalem College of Technology.
 *	The software is provided "as is", without any warranty. 
 *	Change as you want, as long as you keep this disclaimer.
 *
 *	WARNING: I am not responsible for input errors since I did not implement input exception 
 *	handling with cin buffer cleaning (I'll probably do it for the final application, these are just prototypes). 
 */

#define _CRT_SECURE_NO_WARNINGS	//prevents strcpy warnings
#include <iostream>
#include <ctime>
#include <vector>
#include <list>
#include "Library.h"
#include "HashFile.h"
using namespace std;

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

int MainMenu()
{
	int choice;
	cout<<"\t\t\t Main Menu"<<endl;
	cout<<"1................................................ Create a File"<<endl;
	cout<<"2....................... Create a File in the current directory"<<endl;
	cout<<"3.................................................. Open a File"<<endl;
	cout<<"4......................... Open a File in the current directory"<<endl;
	cout<<"5................................................. Close a file"<<endl;
	cout<<"6................................................ Delete a File"<<endl;
	cout<<"10.................. Write a Record with a C++ string key (NEW)"<<endl;
	cout<<"11................... Read a Record with a C++ string key (NEW)"<<endl;
	cout<<"12.................... Write a Record with a C string key (NEW)"<<endl;
	cout<<"13..................... Read a Record with a C string key (NEW)"<<endl;
	cout<<"14.................... Write a Record with an integer key (NEW)"<<endl;
	cout<<"15..................... Read a Record with an integer key (NEW)"<<endl;
	cout<<"20.....  Write 100 records in a file with C++ string keys (NEW)"<<endl;
	cout<<"21.......  Write 100 records in a file with C string keys (NEW)"<<endl;
	cout<<"22......... Write 100 records in a file with integer keys (NEW)"<<endl;
	cout<<"0......................................................... Exit"<<endl;
	cin>>choice;
	return choice;
}

void CreateFile(HashFile &file, bool currentDir=true)
{
	int HashFuncID;
	unsigned int recordSize, fileSize, keyPlace, keySize;
	char keyType;
	string fileName, userName, workingDir;
	cout<<"Please enter the file name:"<<endl;
	cin>>fileName;
	cout<<"Please enter your name:"<<endl;
	cin>>userName;
	cout<<"Please enter the record size in bytes:"<<endl;
	cin>>recordSize;
	if(currentDir)
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
	file.hcreate(fileName, userName, recordSize, HashFuncID, workingDir, fileSize, keyPlace, keyType, keySize);
	cout<<"File successfully created as "<<fileName<<".hash."<<endl;
}
void OpenFile(HashFile &file, bool currentDir=true)
{
	int openMode;
	string fileName, userName, workingDir;
	cout<<"Please enter the file name:"<<endl;
	cin>>fileName;
	cout<<"Please enter your name:"<<endl;
	cin>>userName;
	if(currentDir)
		workingDir="";
	else
	{
		cout<<"Please enter the directory of the file: "<<endl;
		cin>>workingDir;
	}
	cout<<"Please enter the opening mode: (read-0, write-1, both-2)"<<endl;
	cin>>openMode;
	file.hopen(fileName, userName, workingDir, openMode);
	cout<<"File successfully opened."<<endl;
}
void WriteCppToFile(HashFile &file)
{
	cRecord record;
	cout<<"Please enter the key:"<<endl;
	cin>>record.ID;
	cout<<"Please enter the first name:"<<endl;
	cin>>record.firstName;
	cout<<"Please enter the last name:"<<endl;
	cin>>record.lastName;
	cout<<"Please enter the city of residence:"<<endl;
	cin>>record.city;
	char* pointerToRecord = (char*)(&record);
	file.write(record.ID, pointerToRecord);
	cout<<"Record successfully written."<<endl;
}
cRecord* ReadCppFromFile(HashFile &file)
{
	string key;
	cout<<"What is the key of the record?"<<endl;
	cin>>key;
	char crecord[128];
	file.read(key, crecord);
	cRecord* record = (cRecord*)crecord;
	return record;
}
void WriteChToFile(HashFile &file)
{
	cRecord record;
	cout<<"Please enter the key:"<<endl;
	cin>>record.ID;
	cout<<"Please enter the first name:"<<endl;
	cin>>record.firstName;
	cout<<"Please enter the last name:"<<endl;
	cin>>record.lastName;
	cout<<"Please enter the city of residence:"<<endl;
	cin>>record.city;
	char* pointerToRecord = (char*)(&record);
	file.write(record.ID, pointerToRecord);
	cout<<"Record successfully written."<<endl;
}
cRecord* ReadChFromFile(HashFile &file)
{
	char key[4];
	cout<<"What is the key of the record?"<<endl;
	cin>>key;
	char crecord[128];
	file.read(key, crecord);
	cRecord* record = (cRecord*)crecord;
	return record;
}
void WriteIntToFile(HashFile &file)
{
	iRecord record;
	cout<<"Please enter the key:"<<endl;
	cin>>record.ID;
	cout<<"Please enter the first name:"<<endl;
	cin>>record.firstName;
	cout<<"Please enter the last name:"<<endl;
	cin>>record.lastName;
	cout<<"Please enter the city of residence:"<<endl;
	cin>>record.city;
	char* pointerToRecord = (char*)(&record);
	file.write(record.ID, pointerToRecord);
	cout<<"Record successfully written."<<endl;
}
iRecord* ReadIntFromFile(HashFile &file)
{
	int key;
	cout<<"What is the key of the record?"<<endl;
	cin>>key;
	char crecord[128];
	file.read(key, crecord);
	iRecord* record = (iRecord*)crecord;
	return record;
}

/*********************************************************************************************************
********************THE FOLLOWING FUNCTIONS WILL HELP TEST THE FUNCTIONS OF THIS LEVEL********************
*********************************************************************************************************/
void cppStrWriteTest()
{
	vector<list<int>*> foundKeys;	//this part generates 500 random numbers without repeat
	for(int i=0;i<500;i++)
		foundKeys.push_back(new list<int>);	//we generate 500 lists that will contain the numbers already found
	int randKeys[500], curKey = 0;
	for(int keysFoundSoFar = 0 ; keysFoundSoFar < 500 ;)
	{
		srand((unsigned)time(0) + curKey);
		curKey = rand();	//add a %MAX_KEY with define preprocessor to make a maximum key value, by default RAND_MAX
		bool repeated = false;
		for(list<int>::iterator checkRepeat =  foundKeys[curKey%500]->begin() ; checkRepeat != foundKeys[curKey%500]->end() ; checkRepeat++)
		{
			if(*checkRepeat == curKey)	//if a number had already been found, we will not add it
				repeated = true;
		}
		if(!repeated)
		{
			foundKeys[curKey%500]->push_back(curKey);	//if it was not repeated, the number is added to its list of numbers already found %MAX_KEY
			randKeys[keysFoundSoFar] = curKey; 
			keysFoundSoFar++;	//that's one more number in our counter to 500
		}
	}

	HashFile test;
	double shortTime = DBL_MAX, sparseDev = DBL_MAX;
	HashFuncIDcode shortHash, sparseHash;
	cout<<"Please note that a smaller absolute deviation means sparser results."<<endl;
	for(int func = 0 ; func <= 9 ; func++)
	{
		char titlech = (char)(func + 'a');
		char* titlechp = new char[2];
		titlechp[0] = titlech;
		titlechp[1] = NULL;

		try
		{
			test.hopen("cpp" + string(titlechp), "user", "", 2);	//attempt to delete a previous file if there is one
			test.hclose();
			test.hdelete();
		}
		catch (exception ex)
		{
		}

		test.hcreate("cpp" + string(titlechp), "user", 128, func, "", 100, 0, 'C', 4);	//then create it over again and open it
		test.hopen("cpp" + string(titlechp), "user", "", 2);

		cRecord rec;	//prepare a record
		char* recstr = "Dummy text";
		strcpy(rec.firstName, recstr);
		strcpy(rec.lastName, recstr);
		strcpy(rec.city, recstr);

		clock_t total = 0;
		string key;
		for(int id = 0 ; id < 500 ; id++)
		{
			key = "";
			key += 'a' + randKeys[id] / 26 / 26 / 26;
			key += 'a' + randKeys[id] / 26 / 26;
			key += 'a' + randKeys[id] / 26;
			key += 'a' + randKeys[id] % 26;
			strcpy(rec.ID, key.c_str());
			clock_t start = clock();
			test.write(key, (char*)(&rec));	//this is the heart of the function: the clock is running and we write records
			total += clock() - start;
		}
		
		cout<<"HashFunction: "<<(HashFuncIDcode)func<<", time taken: "<<(double)total / CLOCKS_PER_SEC<<"s, absolute deviation: "<<test.deviation()<<endl;
		if((double)total / CLOCKS_PER_SEC < shortTime)
		{
			shortTime = (double)total / CLOCKS_PER_SEC;
			shortHash = (HashFuncIDcode)func;
		}		
		if(test.deviation() < sparseDev)
		{
			sparseDev = test.deviation();
			sparseHash = (HashFuncIDcode)func;
		}
		test.hclose();
	}
	cout<<"Shortest hash function: "<<shortHash<<", most sparse results: "<<sparseHash<<"."<<endl;
}
void cStrWriteTest()
{	
	vector<list<int>*> foundKeys;	//this part generates 500 random numbers without repeat
	for(int i=0;i<500;i++)
		foundKeys.push_back(new list<int>);	//we generate 500 lists that will contain the numbers already found
	int randKeys[500], curKey = 0;
	for(int keysFoundSoFar = 0 ; keysFoundSoFar < 500 ;)
	{
		srand((unsigned)time(0) + curKey);
		curKey = rand();	//add a %MAX_KEY with define preprocessor to make a maximum key value, by default RAND_MAX
		bool repeated = false;
		for(list<int>::iterator checkRepeat =  foundKeys[curKey%500]->begin() ; checkRepeat != foundKeys[curKey%500]->end() ; checkRepeat++)
		{
			if(*checkRepeat == curKey)	//if a number had already been found, we will not add it
				repeated = true;
		}
		if(!repeated)
		{
			foundKeys[curKey%500]->push_back(curKey);	//if it was not repeated, the number is added to its list of numbers already found %MAX_KEY
			randKeys[keysFoundSoFar] = curKey; 
			keysFoundSoFar++;	//that's one more number in our counter to 500
		}
	}

	HashFile test;
	double shortTime = DBL_MAX, sparseDev = DBL_MAX;
	HashFuncIDcode shortHash, sparseHash;
	cout<<"Please note that a smaller absolute deviation means sparser results."<<endl;
	for(int func = 0 ; func <= 9 ; func++)
	{
		char titlech = (char)(func + 'a');
		char* titlechp = new char[2];
		titlechp[0] = titlech;
		titlechp[1] = NULL;

		try
		{
			test.hopen("c" + string(titlechp), "user", "", 2);
			test.hclose();
			test.hdelete();	//attempt to delete a previous file if there is one
		}
		catch (exception ex)
		{
		}

		test.hcreate("c" + string(titlechp), "user", 128, func, "", 100, 0, 'C', 4);
		test.hopen("c" + string(titlechp), "user", "", 2);	//then create it over again and open it

		cRecord rec;	//prepare a record
		char* recstr = "Dummy text";
		strcpy(rec.firstName, recstr);
		strcpy(rec.lastName, recstr);
		strcpy(rec.city, recstr);

		clock_t total = 0;
		char* key = new char[4];
		for(int id = 0 ; id < 500 ; id++)
		{
			key[0] = 'a' + randKeys[id] / 26 / 26 / 26;
			key[1] = 'a' + randKeys[id] / 26 / 26;
			key[2] = 'a' + randKeys[id] / 26;
			key[3] = 'a' + randKeys[id] % 26;
			memcpy(rec.ID, key, 4);
			clock_t start = clock();
			test.write(key, (char*)(&rec));	//this is the heart of the function: the clock is running and we write records
			total += clock() - start;
		}

		cout<<"HashFunction: "<<(HashFuncIDcode)func<<", time taken: "<<(double)total / CLOCKS_PER_SEC<<"s, absolute deviation: "<<test.deviation()<<endl;
		if((double)total / CLOCKS_PER_SEC < shortTime)
		{
			shortTime = (double)total / CLOCKS_PER_SEC;
			shortHash = (HashFuncIDcode)func;
		}		
		if(test.deviation() < sparseDev)
		{
			sparseDev = test.deviation();
			sparseHash = (HashFuncIDcode)func;
		}
		test.hclose();
	}
	cout<<"Shortest hash function: "<<shortHash<<", most sparse results: "<<sparseHash<<"."<<endl;
}
void IntWriteTest()
{
	vector<list<int>*> foundKeys;	//this part generates 500 random numbers without repeat
	for(int i=0;i<500;i++)
		foundKeys.push_back(new list<int>);	//we generate 500 lists that will contain the numbers already found
	int randKeys[500], curKey = 0;
	for(int keysFoundSoFar = 0 ; keysFoundSoFar < 500 ;)
	{
		srand((unsigned)time(0) + curKey);
		curKey = rand();	//add a %MAX_KEY with define preprocessor to make a maximum key value, by default RAND_MAX
		bool repeated = false;
		for(list<int>::iterator checkRepeat =  foundKeys[curKey%500]->begin() ; checkRepeat != foundKeys[curKey%500]->end() ; checkRepeat++)
		{
			if(*checkRepeat == curKey)	//if a number had already been found, we will not add it
				repeated = true;
		}
		if(!repeated)
		{
			foundKeys[curKey%500]->push_back(curKey);	//if it was not repeated, the number is added to its list of numbers already found %MAX_KEY
			randKeys[keysFoundSoFar] = curKey; 
			keysFoundSoFar++;	//that's one more number in our counter to 500
		}
	}

	HashFile test;
	double shortTime = DBL_MAX, sparseDev = DBL_MAX;
	HashFuncIDcode shortHash, sparseHash;
	cout<<"Please note that a smaller absolute deviation means sparser results."<<endl;
	for(int func = 0 ; func <= 9 ; func++)
	{
		char titlech = (char)(func + 'a');
		char* titlechp = new char[2];
		titlechp[0]=titlech;
		titlechp[1]=NULL;

		try
		{
			test.hopen("i" + string(titlechp), "user", "", 2);
			test.hclose();
			test.hdelete();	//attempt to delete a previous file if there is one
		}
		catch (exception ex)
		{
		}

		test.hcreate("i" + string(titlechp), "user", 128, func, "", 100, 0, 'I', 4);
		test.hopen("i" + string(titlechp), "user", "", 2);	//then create it over again and open it

		iRecord rec;	//prepare a record
		char* recstr = "Dummy text";
		strcpy(rec.firstName, recstr);
		strcpy(rec.lastName, recstr);
		strcpy(rec.city, recstr);

		clock_t total = 0;
		for(int id = 0 ; id < 500 ; id++)
		{
			rec.ID = randKeys[id];
			clock_t start = clock();
			test.write(randKeys[id], (char*)(&rec));	//this is the heart of the function: the clock is running and we write records
			total += clock() - start;
		}

		cout<<"HashFunction: "<<(HashFuncIDcode)func<<", time taken: "<<(double)total / CLOCKS_PER_SEC<<"s, absolute deviation: "<<test.deviation()<<endl;
		if((double)total / CLOCKS_PER_SEC < shortTime)
		{
			shortTime = (double)total / CLOCKS_PER_SEC;
			shortHash = (HashFuncIDcode)func;
		}		
		if(test.deviation() < sparseDev)
		{
			sparseDev = test.deviation();
			sparseHash = (HashFuncIDcode)func;
		}
		test.hclose();
	}
	cout<<"Shortest hash function: "<<shortHash<<", most sparse results: "<<sparseHash<<"."<<endl;
}
/*********************************************************************************************************
*****************************************END OF THE TEST FUNCTIONS****************************************
*********************************************************************************************************/

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
				CreateFile(file, false);
				break;
			case 2:
				CreateFile(file);
				break;
			case 3:
				OpenFile(file, false);
				break;
			case 4:
				OpenFile(file);
				break;
			case 5:
				file.hclose();
				cout<<"File successfully closed."<<endl;
				break;
			case 6:
				file.hdelete();
				cout<<"File successfully deleted."<<endl;
				break;
			case 10:
				WriteCppToFile(file);
				break;
			case 11:
				{
				cRecord record = *ReadCppFromFile(file);
				cout<<"#"<<record.ID<<" is "<<record.firstName<<" "<<record.lastName<<"; he lives in "<<record.city<<"."<<endl;
				}
				break;
			case 12:
				WriteChToFile(file);
				break;
			case 13:
				{
				cRecord record = *ReadChFromFile(file);
				cout<<"#"<<record.ID<<" is "<<record.firstName<<" "<<record.lastName<<"; he lives in "<<record.city<<"."<<endl;
				}
				break;
			case 14:
				WriteIntToFile(file);
				break;
			case 15:
				{
				iRecord record = *ReadIntFromFile(file);
				cout<<"#"<<record.ID<<" is "<<record.firstName<<" "<<record.lastName<<"; he lives in "<<record.city<<"."<<endl;
				}
				break;
			case 20:
				cppStrWriteTest();
				break;
			case 21:
				cStrWriteTest();
				break;
			case 22:
				IntWriteTest();
				break;
			case 0:
				return 0;
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