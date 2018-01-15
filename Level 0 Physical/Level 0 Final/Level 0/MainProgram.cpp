/**
 *	"Level 0"
 *	Copyright Pinhas Fedidat (ID 7665692), Aviram Michaeli (ID 302210224), 2011.
 *	For Dr. Ezra Dasht, Project in File Management Systems, Jerusalem College of Technology.
 *	The software is provided "as is", without any warranty. 
 *	Change as you want, as long as you keep this disclaimer.
 */

#include <iostream>
#include "PhysicalFile.h"
using namespace std;

int MainMenu()
{
	int choice;
	cout<<"\t\t\t Main Menu"<<endl;
	cout<<"1................................................. Create File"<<endl;
	cout<<"2................................................... Open File"<<endl;
	cout<<"3.................................................. Close file"<<endl;
	cout<<"4................................................. Delete File"<<endl;
	cout<<"5............................................... Write a Block"<<endl;
	cout<<"6............................................. Read From Block"<<endl;
	cout<<"0........................................................ Exit"<<endl;
	cin>>choice;
	return choice;
}

void CreateFile(PhysicalFile &file)
{
	string name,dir;
	int size;
	cout<<"Please enter the file name:"<<endl;
	cin>>name;
	cout<<"Please enter the directory of the file: (\"cur\" for current directory)"<<endl;
	cin>>dir;
	cout<<"Please enter the size of the file: "<<endl;
	cin>>size;
	if(dir=="cur")
		file.pcreate(name,size);
	else
		file.pcreate(name,size,dir);
	cout<<"File successfully created as "<<name<<".hash."<<endl;
}
void OpenFile(PhysicalFile &file)
{
	string name,dir;
	cout<<"Please enter the file name:"<<endl;
	cin>>name;
	cout<<"Please enter the directory of the file: (\"cur\" for current directory)"<<endl;
	cin>>dir;
	if(dir=="cur")
		file.popen(name,2);
	else
		file.popen(name,2,dir);
	cout<<"File successfully opened."<<endl;
}
void WriteToFile(PhysicalFile &file)
{
	unsigned int number;
	string data;
	cout<<"Insert your data:"<<endl;
	fflush(stdin);
	getline(cin,data);
	cout<<"Which block do you wish to write to?"<<endl;
	cin>>number;
	file.CurrBlock.setCurData(data,number);
	file.writeBlock(number);
	cout<<"Block successfully written"<<endl;
}
string ReadFromFile(PhysicalFile &file)
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
	PhysicalFile file;
	int choice;
	choice = MainMenu(); 
	while (choice)
	{
		try
		{
			switch (choice)
			{
			case 1:
				CreateFile(file);
				break;
			case 2:
				OpenFile(file);
				break;
			case 3:
				file.pclose();
				cout<<"File successfully closed."<<endl;
				break;
			case 4:
				file.pdelete();
				cout<<"File successfully deleted."<<endl;
				break;
			case 5:
				WriteToFile(file);
				break;
			case 6:
				cout<<ReadFromFile(file)<<endl;
				if(ReadFromFile(file)=="")
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