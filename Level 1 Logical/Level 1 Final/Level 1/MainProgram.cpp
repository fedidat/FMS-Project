/**
 *	"Level 1"
 *	Copyright Pinhas Fedidat (ID 7665692), Aviram Michaeli (ID 302210224), 2011.
 *	For Dr. Ezra Dasht, Project in File Management Systems, Jerusalem College of Technology.
 *	The software is provided "as is", without any warranty. 
 *	Change as you want, as long as you keep this disclaimer.
 *
 *	WARNING: I am not responsible for input errors since I did not implement input exception 
 *	handling with cin buffer cleaning (I'll do it for the last levels, these are just examples). 
 */

#include <iostream>
#include "HashFile.h"
using namespace std;

int MainMenu()
{
	int choice;
	cout<<"\t\t\t Main Menu"<<endl;
	cout<<"1.................................. ...... Create a File (NEW)"<<endl;
	cout<<"2................ Create a File in the current directory (NEW)"<<endl;
	cout<<"3........................................... Open a File (NEW)"<<endl;
	cout<<"4.................. Open a File in the current directory (NEW)"<<endl;
	cout<<"5.......................................... Close a file (NEW)"<<endl;
	cout<<"6......................................... Delete a File (NEW)"<<endl;
	cout<<"7............................................... Write a Block"<<endl;
	cout<<"8........................................... Read From a Block"<<endl;
	cout<<"0........................................................ Exit"<<endl;
	cin>>choice;
	return choice;
}

void CreateFile(HashFile &file, bool currentDir=true)
{
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
	cout<<"Please enter the type of the key: (integer-'I', string-'S')"<<endl;
	cin>>keyType;
	cout<<"Please enter the size of the key in bytes:"<<endl;
	cin>>keySize;
	file.hcreate(fileName, userName, recordSize, workingDir, fileSize, keyPlace, keyType, keySize);
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
void WriteToFile(HashFile &file)
{
	unsigned int number;
	string data;
	cout<<"Insert your data:"<<endl;
	fflush(stdin);
	getline(cin, data);
	cout<<"Which block do you wish to write to?"<<endl;
	cin>>number;
	file.CurrBlock.setCurData(data, number);
	file.writeBlock(number);
	cout<<"Block successfully written"<<endl;
}
string ReadFromFile(HashFile &file)
{
	unsigned int block;
	cout<<"Which block to you want to read?"<<endl;
	cin>>block;
	file.readBlock(block);
	cout<<"Reading block number "<<block<<":"<<endl;
	return file.CurrBlock.getCurData();
}

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
			case 7:
				WriteToFile(file);
				break;
			case 8:
				cout<<ReadFromFile(file)<<endl;
				if(ReadFromFile(file) == "")
					cout<<"\t(Empty Block)"<<endl;
				break;
			default:
				throw exception("ERROR: Illegal choice number");
			}
		}
		catch (exception ex)
		{
			cout<<ex.what()<<endl;
		}
		cout<<endl;
		choice = MainMenu();
	}
	system("pause");
	return 0;
}
