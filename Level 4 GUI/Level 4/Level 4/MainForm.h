/**
*	"Level 4"
*	By Pinhas Fedidat (ID 7665692), Aviram Michaeli (ID 302210224), 2011.
*	For Dr. Moshe Goldstein, Project in File Management Systems, Jerusalem College of Technology.
*	The software is provided "as is", without any warranty. 
*	You are free to make any changes, as long as you keep this disclaimer in its present form.
*	Copyright Pinhas Fedidat.
*/

#pragma once
#include "stdafx.h"
#include "CreateDialog.h"
#include "OpenDialog.h"
#include "HashDocDialog.h"
#include "HowtoUseDialog.h"
#include <iostream>

#pragma region records
//the two types of 128-byte record
struct iRecord	//integer record
{
	int key;
	char firstName[40];
	char lastName[40];
	char city[44];
};
struct cRecord //string record
{
	char key[20];
	char firstName[40];
	char lastName[40];
	char city[28];
};
#pragma endregion

namespace Level4 {
	#pragma region namespaces
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	#pragma endregion

	/// <summary>
	/// MainForm handles every action involving records and blocks,
	/// but uses sub-dialogs to create, open and delete files.
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			BeginStatus();
			file = new HashFile();	//use HashFile's default constructor
			this->ActiveControl = this->MainMenuStrip;	//basically, clear ActiveControl
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
		#pragma region MainFormComponents
		//Dozens of controls
		private: System::Windows::Forms::MenuStrip^  menuStrip1;
		private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  deleteToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenu;
		private: System::Windows::Forms::StatusStrip^  statusStrip1;
		private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel;
		private: System::Windows::Forms::GroupBox^  readGroupBox;
		private: System::Windows::Forms::TextBox^  readTextBoxF0;
		private: System::Windows::Forms::Button^  readButton;
		private: System::Windows::Forms::GroupBox^  viewGroupBox;
		private: System::Windows::Forms::TextBox^  viewTextBoxF0;
		private: System::Windows::Forms::TextBox^  viewTextBoxF1;
		private: System::Windows::Forms::TextBox^  viewTextBoxF2;
		private: System::Windows::Forms::TextBox^  viewTextBoxF3;
		private: System::Windows::Forms::Button^  updateTriggerButton;
		private: System::Windows::Forms::Button^  updateCancelButton;
		private: System::Windows::Forms::Button^  updateConfirmButton;
		private: System::Windows::Forms::Button^  deleteTriggerButton;
		private: System::Windows::Forms::Button^  deleteConfirmButton;
		private: System::Windows::Forms::Button^  deleteCancelButton;
		private: System::Windows::Forms::GroupBox^  writeGroupBox;
		private: System::Windows::Forms::TextBox^  writeTextBoxF0;
		private: System::Windows::Forms::TextBox^  writeTextBoxF1;
		private: System::Windows::Forms::TextBox^  writeTextBoxF2;
		private: System::Windows::Forms::TextBox^  writeTextBoxF3;
		private: System::Windows::Forms::Button^  writeButton;
		private: System::Windows::Forms::GroupBox^  fileGroupBox;
		private: System::Windows::Forms::Label^  HashfunctionLabel;
		private: System::Windows::Forms::Label^  keytypeLabel;
		private: System::Windows::Forms::Label^  filesizeLabel;
		private: System::Windows::Forms::Label^  creationdateLabel;
		private: System::Windows::Forms::TextBox^  userTextBox;
		private: System::Windows::Forms::Label^  userLabel;
		private: System::Windows::Forms::Label^  filenameLabel;
		private: System::Windows::Forms::Label^  label5;
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::Label^  label3;
		private: System::Windows::Forms::Label^  label4;
		private: System::Windows::Forms::Label^  writeLabelF4;
		private: System::Windows::Forms::Label^  writeLabelF2;
		private: System::Windows::Forms::Label^  writeLabelF1;
		private: System::Windows::Forms::Label^  writeLabelF0;
		private: System::Windows::Forms::ListView^  blockListView;
		private: System::Windows::Forms::ListView^  recordListView;
		private: System::Windows::Forms::GroupBox^  fileMapGroupBox;
		private: System::Windows::Forms::Label^  recordLabel;
		private: System::Windows::Forms::Label^  blockLabel;
		private: System::Windows::Forms::ColumnHeader^  numColumnHeader;
		private: System::Windows::Forms::ColumnHeader^  recColumnHeader;
		private: System::Windows::Forms::ColumnHeader^  keyColumnHeader;
		private: System::Windows::Forms::ColumnHeader^  F1ColumnHeader;
		private: System::Windows::Forms::ColumnHeader^  F2ColumnHeader;
		private: System::Windows::Forms::ColumnHeader^  F3ColumnHeader;
		private: System::Windows::Forms::Label^  emptyVolumeLabel;
		private: System::Windows::Forms::ToolStripMenuItem^  howToUseToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  hashDocToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;

		private: HashFile* file;	//and our precious HashFile

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		#pragma endregion
		#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->howToUseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->hashDocToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->readGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->readButton = (gcnew System::Windows::Forms::Button());
			this->readTextBoxF0 = (gcnew System::Windows::Forms::TextBox());
			this->viewGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->deleteCancelButton = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->updateCancelButton = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->updateConfirmButton = (gcnew System::Windows::Forms::Button());
			this->deleteConfirmButton = (gcnew System::Windows::Forms::Button());
			this->updateTriggerButton = (gcnew System::Windows::Forms::Button());
			this->viewTextBoxF3 = (gcnew System::Windows::Forms::TextBox());
			this->deleteTriggerButton = (gcnew System::Windows::Forms::Button());
			this->viewTextBoxF2 = (gcnew System::Windows::Forms::TextBox());
			this->viewTextBoxF1 = (gcnew System::Windows::Forms::TextBox());
			this->viewTextBoxF0 = (gcnew System::Windows::Forms::TextBox());
			this->writeGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->writeLabelF4 = (gcnew System::Windows::Forms::Label());
			this->writeLabelF2 = (gcnew System::Windows::Forms::Label());
			this->writeLabelF1 = (gcnew System::Windows::Forms::Label());
			this->writeLabelF0 = (gcnew System::Windows::Forms::Label());
			this->writeButton = (gcnew System::Windows::Forms::Button());
			this->writeTextBoxF3 = (gcnew System::Windows::Forms::TextBox());
			this->writeTextBoxF2 = (gcnew System::Windows::Forms::TextBox());
			this->writeTextBoxF1 = (gcnew System::Windows::Forms::TextBox());
			this->writeTextBoxF0 = (gcnew System::Windows::Forms::TextBox());
			this->fileGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->emptyVolumeLabel = (gcnew System::Windows::Forms::Label());
			this->filenameLabel = (gcnew System::Windows::Forms::Label());
			this->creationdateLabel = (gcnew System::Windows::Forms::Label());
			this->HashfunctionLabel = (gcnew System::Windows::Forms::Label());
			this->keytypeLabel = (gcnew System::Windows::Forms::Label());
			this->filesizeLabel = (gcnew System::Windows::Forms::Label());
			this->userTextBox = (gcnew System::Windows::Forms::TextBox());
			this->userLabel = (gcnew System::Windows::Forms::Label());
			this->blockListView = (gcnew System::Windows::Forms::ListView());
			this->numColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->recColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->recordListView = (gcnew System::Windows::Forms::ListView());
			this->keyColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->F1ColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->F2ColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->F3ColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->fileMapGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->recordLabel = (gcnew System::Windows::Forms::Label());
			this->blockLabel = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->readGroupBox->SuspendLayout();
			this->viewGroupBox->SuspendLayout();
			this->writeGroupBox->SuspendLayout();
			this->fileGroupBox->SuspendLayout();
			this->fileMapGroupBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->fileToolStripMenuItem, 
				this->aboutToolStripMenu});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(538, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->newToolStripMenuItem, 
				this->openToolStripMenuItem, this->deleteToolStripMenuItem, this->exitToolStripMenuItem1});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(35, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
			this->newToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->newToolStripMenuItem->Text = L"Create";
			this->newToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::newToolStripMenuItem_Click);
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->openToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openToolStripMenuItem_Click);
			// 
			// deleteToolStripMenuItem
			// 
			this->deleteToolStripMenuItem->Enabled = false;
			this->deleteToolStripMenuItem->Name = L"deleteToolStripMenuItem";
			this->deleteToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D));
			this->deleteToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->deleteToolStripMenuItem->Text = L"Delete";
			this->deleteToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::deleteToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem1
			// 
			this->exitToolStripMenuItem1->Name = L"exitToolStripMenuItem1";
			this->exitToolStripMenuItem1->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Q));
			this->exitToolStripMenuItem1->Size = System::Drawing::Size(146, 22);
			this->exitToolStripMenuItem1->Text = L"Exit";
			this->exitToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MainForm::exitToolStripMenuItem1_Click);
			// 
			// aboutToolStripMenu
			// 
			this->aboutToolStripMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->howToUseToolStripMenuItem, 
				this->hashDocToolStripMenuItem, this->aboutToolStripMenuItem});
			this->aboutToolStripMenu->Name = L"aboutToolStripMenu";
			this->aboutToolStripMenu->ShortcutKeys = System::Windows::Forms::Keys::F1;
			this->aboutToolStripMenu->Size = System::Drawing::Size(48, 20);
			this->aboutToolStripMenu->Text = L"About";
			// 
			// howToUseToolStripMenuItem
			// 
			this->howToUseToolStripMenuItem->Name = L"howToUseToolStripMenuItem";
			this->howToUseToolStripMenuItem->ShortcutKeys = System::Windows::Forms::Keys::F1;
			this->howToUseToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->howToUseToolStripMenuItem->Text = L"How to use";
			this->howToUseToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::howToUseToolStripMenuItem_Click);
			// 
			// hashDocToolStripMenuItem
			// 
			this->hashDocToolStripMenuItem->Name = L"hashDocToolStripMenuItem";
			this->hashDocToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->hashDocToolStripMenuItem->Text = L"Hash Doc";
			this->hashDocToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::hashDocToolStripMenuItem_Click);
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->aboutToolStripMenuItem->Text = L"About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::aboutToolStripMenuItem_Click);
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->toolStripStatusLabel});
			this->statusStrip1->Location = System::Drawing::Point(0, 434);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(538, 22);
			this->statusStrip1->TabIndex = 1;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel
			// 
			this->toolStripStatusLabel->Name = L"toolStripStatusLabel";
			this->toolStripStatusLabel->Size = System::Drawing::Size(38, 17);
			this->toolStripStatusLabel->Text = L"Ready";
			// 
			// readGroupBox
			// 
			this->readGroupBox->Controls->Add(this->label5);
			this->readGroupBox->Controls->Add(this->readButton);
			this->readGroupBox->Controls->Add(this->readTextBoxF0);
			this->readGroupBox->Enabled = false;
			this->readGroupBox->Location = System::Drawing::Point(370, 28);
			this->readGroupBox->Name = L"readGroupBox";
			this->readGroupBox->Size = System::Drawing::Size(164, 75);
			this->readGroupBox->TabIndex = 1000;
			this->readGroupBox->TabStop = false;
			this->readGroupBox->Text = L"Find a record";
			this->readGroupBox->EnabledChanged += gcnew System::EventHandler(this, &MainForm::isKeyFilled);
			this->readGroupBox->Enter += gcnew System::EventHandler(this, &MainForm::readAB);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(6, 21);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(25, 13);
			this->label5->TabIndex = 30;
			this->label5->Text = L"Key";
			// 
			// readButton
			// 
			this->readButton->Enabled = false;
			this->readButton->Location = System::Drawing::Point(50, 45);
			this->readButton->Name = L"readButton";
			this->readButton->Size = System::Drawing::Size(60, 23);
			this->readButton->TabIndex = 1;
			this->readButton->Text = L"Seek";
			this->readButton->UseVisualStyleBackColor = true;
			this->readButton->Click += gcnew System::EventHandler(this, &MainForm::readButton_Click);
			// 
			// readTextBoxF0
			// 
			this->readTextBoxF0->Location = System::Drawing::Point(37, 19);
			this->readTextBoxF0->Name = L"readTextBoxF0";
			this->readTextBoxF0->Size = System::Drawing::Size(107, 20);
			this->readTextBoxF0->TabIndex = 0;
			this->readTextBoxF0->TextChanged += gcnew System::EventHandler(this, &MainForm::isKeyFilled);
			// 
			// viewGroupBox
			// 
			this->viewGroupBox->Controls->Add(this->label1);
			this->viewGroupBox->Controls->Add(this->deleteCancelButton);
			this->viewGroupBox->Controls->Add(this->label2);
			this->viewGroupBox->Controls->Add(this->updateCancelButton);
			this->viewGroupBox->Controls->Add(this->label3);
			this->viewGroupBox->Controls->Add(this->label4);
			this->viewGroupBox->Controls->Add(this->updateConfirmButton);
			this->viewGroupBox->Controls->Add(this->deleteConfirmButton);
			this->viewGroupBox->Controls->Add(this->updateTriggerButton);
			this->viewGroupBox->Controls->Add(this->viewTextBoxF3);
			this->viewGroupBox->Controls->Add(this->deleteTriggerButton);
			this->viewGroupBox->Controls->Add(this->viewTextBoxF2);
			this->viewGroupBox->Controls->Add(this->viewTextBoxF1);
			this->viewGroupBox->Controls->Add(this->viewTextBoxF0);
			this->viewGroupBox->Enabled = false;
			this->viewGroupBox->Location = System::Drawing::Point(192, 46);
			this->viewGroupBox->Name = L"viewGroupBox";
			this->viewGroupBox->Size = System::Drawing::Size(172, 153);
			this->viewGroupBox->TabIndex = 1001;
			this->viewGroupBox->TabStop = false;
			this->viewGroupBox->Text = L"View a record";
			this->viewGroupBox->EnabledChanged += gcnew System::EventHandler(this, &MainForm::areReadFilled);
			this->viewGroupBox->Enter += gcnew System::EventHandler(this, &MainForm::updateAB);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 99);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(24, 13);
			this->label1->TabIndex = 32;
			this->label1->Text = L"City";
			// 
			// deleteCancelButton
			// 
			this->deleteCancelButton->Location = System::Drawing::Point(6, 123);
			this->deleteCancelButton->Name = L"deleteCancelButton";
			this->deleteCancelButton->Size = System::Drawing::Size(76, 23);
			this->deleteCancelButton->TabIndex = 17;
			this->deleteCancelButton->Text = L"Cancel";
			this->deleteCancelButton->UseVisualStyleBackColor = true;
			this->deleteCancelButton->Click += gcnew System::EventHandler(this, &MainForm::deleteCancelButton_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 73);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(56, 13);
			this->label2->TabIndex = 31;
			this->label2->Text = L"Last name";
			// 
			// updateCancelButton
			// 
			this->updateCancelButton->Location = System::Drawing::Point(6, 123);
			this->updateCancelButton->Name = L"updateCancelButton";
			this->updateCancelButton->Size = System::Drawing::Size(76, 23);
			this->updateCancelButton->TabIndex = 12;
			this->updateCancelButton->Text = L"Cancel";
			this->updateCancelButton->UseVisualStyleBackColor = true;
			this->updateCancelButton->Click += gcnew System::EventHandler(this, &MainForm::updateCancelButton_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 48);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(55, 13);
			this->label3->TabIndex = 30;
			this->label3->Text = L"First name";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 23);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(25, 13);
			this->label4->TabIndex = 29;
			this->label4->Text = L"Key";
			// 
			// updateConfirmButton
			// 
			this->updateConfirmButton->Location = System::Drawing::Point(88, 123);
			this->updateConfirmButton->Name = L"updateConfirmButton";
			this->updateConfirmButton->Size = System::Drawing::Size(78, 23);
			this->updateConfirmButton->TabIndex = 11;
			this->updateConfirmButton->Text = L"Confirm";
			this->updateConfirmButton->UseVisualStyleBackColor = true;
			this->updateConfirmButton->Click += gcnew System::EventHandler(this, &MainForm::updateConfirmButton_Click);
			// 
			// deleteConfirmButton
			// 
			this->deleteConfirmButton->Location = System::Drawing::Point(88, 123);
			this->deleteConfirmButton->Name = L"deleteConfirmButton";
			this->deleteConfirmButton->Size = System::Drawing::Size(78, 23);
			this->deleteConfirmButton->TabIndex = 16;
			this->deleteConfirmButton->Text = L"Confirm";
			this->deleteConfirmButton->UseVisualStyleBackColor = true;
			this->deleteConfirmButton->Click += gcnew System::EventHandler(this, &MainForm::deleteConfirmButton_Click);
			// 
			// updateTriggerButton
			// 
			this->updateTriggerButton->Location = System::Drawing::Point(88, 123);
			this->updateTriggerButton->Name = L"updateTriggerButton";
			this->updateTriggerButton->Size = System::Drawing::Size(78, 23);
			this->updateTriggerButton->TabIndex = 10;
			this->updateTriggerButton->Text = L"Update";
			this->updateTriggerButton->UseVisualStyleBackColor = true;
			this->updateTriggerButton->Click += gcnew System::EventHandler(this, &MainForm::updateTriggerButton_Click);
			// 
			// viewTextBoxF3
			// 
			this->viewTextBoxF3->Location = System::Drawing::Point(69, 97);
			this->viewTextBoxF3->Name = L"viewTextBoxF3";
			this->viewTextBoxF3->Size = System::Drawing::Size(97, 20);
			this->viewTextBoxF3->TabIndex = 8;
			this->viewTextBoxF3->TextChanged += gcnew System::EventHandler(this, &MainForm::areReadFilled);
			// 
			// deleteTriggerButton
			// 
			this->deleteTriggerButton->Location = System::Drawing::Point(6, 123);
			this->deleteTriggerButton->Name = L"deleteTriggerButton";
			this->deleteTriggerButton->Size = System::Drawing::Size(76, 23);
			this->deleteTriggerButton->TabIndex = 15;
			this->deleteTriggerButton->Text = L"Delete";
			this->deleteTriggerButton->UseVisualStyleBackColor = true;
			this->deleteTriggerButton->Click += gcnew System::EventHandler(this, &MainForm::deleteTriggerButton_Click);
			// 
			// viewTextBoxF2
			// 
			this->viewTextBoxF2->Location = System::Drawing::Point(69, 71);
			this->viewTextBoxF2->Name = L"viewTextBoxF2";
			this->viewTextBoxF2->Size = System::Drawing::Size(97, 20);
			this->viewTextBoxF2->TabIndex = 7;
			this->viewTextBoxF2->TextChanged += gcnew System::EventHandler(this, &MainForm::areReadFilled);
			// 
			// viewTextBoxF1
			// 
			this->viewTextBoxF1->Location = System::Drawing::Point(69, 45);
			this->viewTextBoxF1->Name = L"viewTextBoxF1";
			this->viewTextBoxF1->Size = System::Drawing::Size(97, 20);
			this->viewTextBoxF1->TabIndex = 6;
			this->viewTextBoxF1->TextChanged += gcnew System::EventHandler(this, &MainForm::areReadFilled);
			// 
			// viewTextBoxF0
			// 
			this->viewTextBoxF0->Location = System::Drawing::Point(69, 19);
			this->viewTextBoxF0->Name = L"viewTextBoxF0";
			this->viewTextBoxF0->ReadOnly = true;
			this->viewTextBoxF0->Size = System::Drawing::Size(97, 20);
			this->viewTextBoxF0->TabIndex = 5;
			this->viewTextBoxF0->TextChanged += gcnew System::EventHandler(this, &MainForm::areReadFilled);
			// 
			// writeGroupBox
			// 
			this->writeGroupBox->Controls->Add(this->writeLabelF4);
			this->writeGroupBox->Controls->Add(this->writeLabelF2);
			this->writeGroupBox->Controls->Add(this->writeLabelF1);
			this->writeGroupBox->Controls->Add(this->writeLabelF0);
			this->writeGroupBox->Controls->Add(this->writeButton);
			this->writeGroupBox->Controls->Add(this->writeTextBoxF3);
			this->writeGroupBox->Controls->Add(this->writeTextBoxF2);
			this->writeGroupBox->Controls->Add(this->writeTextBoxF1);
			this->writeGroupBox->Controls->Add(this->writeTextBoxF0);
			this->writeGroupBox->Enabled = false;
			this->writeGroupBox->Location = System::Drawing::Point(12, 46);
			this->writeGroupBox->Name = L"writeGroupBox";
			this->writeGroupBox->Size = System::Drawing::Size(174, 153);
			this->writeGroupBox->TabIndex = 1002;
			this->writeGroupBox->TabStop = false;
			this->writeGroupBox->Text = L"Write a record";
			this->writeGroupBox->EnabledChanged += gcnew System::EventHandler(this, &MainForm::areWriteFilled);
			this->writeGroupBox->Enter += gcnew System::EventHandler(this, &MainForm::writeAB);
			// 
			// writeLabelF4
			// 
			this->writeLabelF4->AutoSize = true;
			this->writeLabelF4->Location = System::Drawing::Point(6, 99);
			this->writeLabelF4->Name = L"writeLabelF4";
			this->writeLabelF4->Size = System::Drawing::Size(24, 13);
			this->writeLabelF4->TabIndex = 28;
			this->writeLabelF4->Text = L"City";
			// 
			// writeLabelF2
			// 
			this->writeLabelF2->AutoSize = true;
			this->writeLabelF2->Location = System::Drawing::Point(6, 73);
			this->writeLabelF2->Name = L"writeLabelF2";
			this->writeLabelF2->Size = System::Drawing::Size(56, 13);
			this->writeLabelF2->TabIndex = 27;
			this->writeLabelF2->Text = L"Last name";
			// 
			// writeLabelF1
			// 
			this->writeLabelF1->AutoSize = true;
			this->writeLabelF1->Location = System::Drawing::Point(6, 48);
			this->writeLabelF1->Name = L"writeLabelF1";
			this->writeLabelF1->Size = System::Drawing::Size(55, 13);
			this->writeLabelF1->TabIndex = 26;
			this->writeLabelF1->Text = L"First name";
			// 
			// writeLabelF0
			// 
			this->writeLabelF0->AutoSize = true;
			this->writeLabelF0->Location = System::Drawing::Point(6, 23);
			this->writeLabelF0->Name = L"writeLabelF0";
			this->writeLabelF0->Size = System::Drawing::Size(25, 13);
			this->writeLabelF0->TabIndex = 25;
			this->writeLabelF0->Text = L"Key";
			// 
			// writeButton
			// 
			this->writeButton->Location = System::Drawing::Point(42, 122);
			this->writeButton->Name = L"writeButton";
			this->writeButton->Size = System::Drawing::Size(60, 23);
			this->writeButton->TabIndex = 24;
			this->writeButton->Text = L"Write";
			this->writeButton->UseVisualStyleBackColor = true;
			this->writeButton->Click += gcnew System::EventHandler(this, &MainForm::writeButton_Click);
			// 
			// writeTextBoxF3
			// 
			this->writeTextBoxF3->Location = System::Drawing::Point(68, 96);
			this->writeTextBoxF3->Name = L"writeTextBoxF3";
			this->writeTextBoxF3->Size = System::Drawing::Size(100, 20);
			this->writeTextBoxF3->TabIndex = 23;
			this->writeTextBoxF3->TextChanged += gcnew System::EventHandler(this, &MainForm::areWriteFilled);
			// 
			// writeTextBoxF2
			// 
			this->writeTextBoxF2->Location = System::Drawing::Point(68, 70);
			this->writeTextBoxF2->Name = L"writeTextBoxF2";
			this->writeTextBoxF2->Size = System::Drawing::Size(100, 20);
			this->writeTextBoxF2->TabIndex = 22;
			this->writeTextBoxF2->TextChanged += gcnew System::EventHandler(this, &MainForm::areWriteFilled);
			// 
			// writeTextBoxF1
			// 
			this->writeTextBoxF1->Location = System::Drawing::Point(67, 45);
			this->writeTextBoxF1->Name = L"writeTextBoxF1";
			this->writeTextBoxF1->Size = System::Drawing::Size(101, 20);
			this->writeTextBoxF1->TabIndex = 21;
			this->writeTextBoxF1->TextChanged += gcnew System::EventHandler(this, &MainForm::areWriteFilled);
			// 
			// writeTextBoxF0
			// 
			this->writeTextBoxF0->Location = System::Drawing::Point(67, 19);
			this->writeTextBoxF0->Name = L"writeTextBoxF0";
			this->writeTextBoxF0->Size = System::Drawing::Size(101, 20);
			this->writeTextBoxF0->TabIndex = 20;
			this->writeTextBoxF0->TextChanged += gcnew System::EventHandler(this, &MainForm::areWriteFilled);
			// 
			// fileGroupBox
			// 
			this->fileGroupBox->Controls->Add(this->emptyVolumeLabel);
			this->fileGroupBox->Controls->Add(this->filenameLabel);
			this->fileGroupBox->Controls->Add(this->creationdateLabel);
			this->fileGroupBox->Controls->Add(this->HashfunctionLabel);
			this->fileGroupBox->Controls->Add(this->keytypeLabel);
			this->fileGroupBox->Controls->Add(this->filesizeLabel);
			this->fileGroupBox->Enabled = false;
			this->fileGroupBox->Location = System::Drawing::Point(370, 109);
			this->fileGroupBox->Name = L"fileGroupBox";
			this->fileGroupBox->Size = System::Drawing::Size(164, 128);
			this->fileGroupBox->TabIndex = 1003;
			this->fileGroupBox->TabStop = false;
			this->fileGroupBox->Text = L"File information";
			// 
			// emptyVolumeLabel
			// 
			this->emptyVolumeLabel->AutoSize = true;
			this->emptyVolumeLabel->Location = System::Drawing::Point(6, 101);
			this->emptyVolumeLabel->Name = L"emptyVolumeLabel";
			this->emptyVolumeLabel->Size = System::Drawing::Size(76, 13);
			this->emptyVolumeLabel->TabIndex = 1007;
			this->emptyVolumeLabel->Text = L"Empty volume:";
			// 
			// filenameLabel
			// 
			this->filenameLabel->AutoSize = true;
			this->filenameLabel->Location = System::Drawing::Point(6, 16);
			this->filenameLabel->Name = L"filenameLabel";
			this->filenameLabel->Size = System::Drawing::Size(55, 13);
			this->filenameLabel->TabIndex = 1006;
			this->filenameLabel->Text = L"File name:";
			// 
			// creationdateLabel
			// 
			this->creationdateLabel->AutoSize = true;
			this->creationdateLabel->Location = System::Drawing::Point(6, 84);
			this->creationdateLabel->Name = L"creationdateLabel";
			this->creationdateLabel->Size = System::Drawing::Size(73, 13);
			this->creationdateLabel->TabIndex = 3;
			this->creationdateLabel->Text = L"Creation date:";
			// 
			// HashfunctionLabel
			// 
			this->HashfunctionLabel->AutoSize = true;
			this->HashfunctionLabel->Location = System::Drawing::Point(6, 67);
			this->HashfunctionLabel->Name = L"HashfunctionLabel";
			this->HashfunctionLabel->Size = System::Drawing::Size(76, 13);
			this->HashfunctionLabel->TabIndex = 2;
			this->HashfunctionLabel->Text = L"Hash function:";
			// 
			// keytypeLabel
			// 
			this->keytypeLabel->AutoSize = true;
			this->keytypeLabel->Location = System::Drawing::Point(6, 50);
			this->keytypeLabel->Name = L"keytypeLabel";
			this->keytypeLabel->Size = System::Drawing::Size(51, 13);
			this->keytypeLabel->TabIndex = 1;
			this->keytypeLabel->Text = L"Key type:";
			// 
			// filesizeLabel
			// 
			this->filesizeLabel->AutoSize = true;
			this->filesizeLabel->Location = System::Drawing::Point(6, 33);
			this->filesizeLabel->Name = L"filesizeLabel";
			this->filesizeLabel->Size = System::Drawing::Size(81, 13);
			this->filesizeLabel->TabIndex = 0;
			this->filesizeLabel->Text = L"File size (in KB):";
			// 
			// userTextBox
			// 
			this->userTextBox->Location = System::Drawing::Point(434, 2);
			this->userTextBox->Name = L"userTextBox";
			this->userTextBox->ReadOnly = true;
			this->userTextBox->Size = System::Drawing::Size(100, 20);
			this->userTextBox->TabIndex = 1004;
			// 
			// userLabel
			// 
			this->userLabel->AutoSize = true;
			this->userLabel->BackColor = System::Drawing::SystemColors::MenuBar;
			this->userLabel->Location = System::Drawing::Point(370, 5);
			this->userLabel->Name = L"userLabel";
			this->userLabel->Size = System::Drawing::Size(58, 13);
			this->userLabel->TabIndex = 1005;
			this->userLabel->Text = L"Username:";
			// 
			// blockListView
			// 
			this->blockListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->numColumnHeader, 
				this->recColumnHeader});
			this->blockListView->FullRowSelect = true;
			this->blockListView->HideSelection = false;
			this->blockListView->Location = System::Drawing::Point(6, 32);
			this->blockListView->MultiSelect = false;
			this->blockListView->Name = L"blockListView";
			this->blockListView->Size = System::Drawing::Size(175, 150);
			this->blockListView->TabIndex = 1008;
			this->blockListView->UseCompatibleStateImageBehavior = false;
			this->blockListView->View = System::Windows::Forms::View::Details;
			this->blockListView->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::updateRecView);
			// 
			// numColumnHeader
			// 
			this->numColumnHeader->Text = L"Block #";
			// 
			// recColumnHeader
			// 
			this->recColumnHeader->Text = L"Records";
			this->recColumnHeader->Width = 110;
			// 
			// recordListView
			// 
			this->recordListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->keyColumnHeader, 
				this->F1ColumnHeader, this->F2ColumnHeader, this->F3ColumnHeader});
			this->recordListView->FullRowSelect = true;
			this->recordListView->HideSelection = false;
			this->recordListView->Location = System::Drawing::Point(187, 32);
			this->recordListView->MultiSelect = false;
			this->recordListView->Name = L"recordListView";
			this->recordListView->Size = System::Drawing::Size(321, 150);
			this->recordListView->TabIndex = 1009;
			this->recordListView->UseCompatibleStateImageBehavior = false;
			this->recordListView->View = System::Windows::Forms::View::Details;
			this->recordListView->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::typeRecordInSeek);
			// 
			// keyColumnHeader
			// 
			this->keyColumnHeader->Text = L"Key";
			// 
			// F1ColumnHeader
			// 
			this->F1ColumnHeader->Text = L"First name";
			this->F1ColumnHeader->Width = 85;
			// 
			// F2ColumnHeader
			// 
			this->F2ColumnHeader->Text = L"Last name";
			this->F2ColumnHeader->Width = 85;
			// 
			// F3ColumnHeader
			// 
			this->F3ColumnHeader->Text = L"City";
			this->F3ColumnHeader->Width = 85;
			// 
			// fileMapGroupBox
			// 
			this->fileMapGroupBox->Controls->Add(this->recordLabel);
			this->fileMapGroupBox->Controls->Add(this->blockLabel);
			this->fileMapGroupBox->Controls->Add(this->recordListView);
			this->fileMapGroupBox->Controls->Add(this->blockListView);
			this->fileMapGroupBox->Location = System::Drawing::Point(12, 243);
			this->fileMapGroupBox->Name = L"fileMapGroupBox";
			this->fileMapGroupBox->Size = System::Drawing::Size(514, 188);
			this->fileMapGroupBox->TabIndex = 1010;
			this->fileMapGroupBox->TabStop = false;
			this->fileMapGroupBox->Text = L"File map view";
			// 
			// recordLabel
			// 
			this->recordLabel->AutoSize = true;
			this->recordLabel->Location = System::Drawing::Point(187, 16);
			this->recordLabel->Name = L"recordLabel";
			this->recordLabel->Size = System::Drawing::Size(130, 13);
			this->recordLabel->TabIndex = 1011;
			this->recordLabel->Text = L"Records in selected block";
			// 
			// blockLabel
			// 
			this->blockLabel->AutoSize = true;
			this->blockLabel->Location = System::Drawing::Point(6, 16);
			this->blockLabel->Name = L"blockLabel";
			this->blockLabel->Size = System::Drawing::Size(39, 13);
			this->blockLabel->TabIndex = 1010;
			this->blockLabel->Text = L"Blocks ('x' - occupied)";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(538, 456);
			this->Controls->Add(this->fileMapGroupBox);
			this->Controls->Add(this->userLabel);
			this->Controls->Add(this->userTextBox);
			this->Controls->Add(this->fileGroupBox);
			this->Controls->Add(this->writeGroupBox);
			this->Controls->Add(this->viewGroupBox);
			this->Controls->Add(this->readGroupBox);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->readGroupBox->ResumeLayout(false);
			this->readGroupBox->PerformLayout();
			this->viewGroupBox->ResumeLayout(false);
			this->viewGroupBox->PerformLayout();
			this->writeGroupBox->ResumeLayout(false);
			this->writeGroupBox->PerformLayout();
			this->fileGroupBox->ResumeLayout(false);
			this->fileGroupBox->PerformLayout();
			this->fileMapGroupBox->ResumeLayout(false);
			this->fileMapGroupBox->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		#pragma region Level4Methods
		private: System::Void newToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			//Creates a file through CreateDialog
			bool success = false;	//will indicate if the file has been successfully created
			this->toolStripStatusLabel->Text = L"Creating a file";
			CreateDialog^ create = gcnew CreateDialog(file, &success) ;
			create->ShowInTaskbar = false;
			create->ShowDialog();
			if(success)
			{
				bool status[2];
				file->isOpen(status);	//get the folder's opened status, to check if the user also opened the file that was just created
				if(status[0])
				{
					this->toolStripStatusLabel->Text = L"File successfully created and opened";
					OpenedStatus();
				}
				else
				{
					this->toolStripStatusLabel->Text = L"File successfully created";
					BeginStatus();
				}
			}
		}
		private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			//Opens a file through OpenDialog
			this->toolStripStatusLabel->Text = L"Opening a file";
			bool success = false;
			OpenDialog^ open = gcnew OpenDialog(file, &success) ;
			open->ShowInTaskbar = false;
			open->ShowDialog();
			if(success)
			{
				OpenedStatus();
				this->toolStripStatusLabel->Text = L"File successfully opened";
			}
		}
		private: System::Void deleteToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			//Deletes a file: demands confirmation, closes the file and deletes
			System::Windows::Forms::DialogResult result = MessageBox::Show("Do you really want to delete this file?", "Warning", MessageBoxButtons::YesNo, MessageBoxIcon::Warning, MessageBoxDefaultButton::Button2);
			if(result != System::Windows::Forms::DialogResult::Yes)
			{
				this->toolStripStatusLabel->Text = L"File deletion aborted";
				return;
			}
			try{
				file->hclose();
				file->hdelete();
			}
			catch(std::exception ex){
				this->aboutToolStripMenuItem->Text = gcnew String(ex.what());
			}
			this->toolStripStatusLabel->Text = L"File successfully deleted";
			this->deleteToolStripMenuItem->Enabled = false;
			this->ActiveControl = this->MainMenuStrip;
			BeginStatus();
		}
		private: System::Void exitToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
			this->Close();	//the user just pressed the Exit button (or the shortcut combination Ctrl+Q)
		}
		private: System::Void howToUseToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			//Displays a 'short' explanation of my own on the program's functonality
			 this->toolStripStatusLabel->Text = L"Reading the help documentation";
			 HowtoUseDialog^ help = gcnew HowtoUseDialog();
			 help->ShowInTaskbar = false;
			 help->ShowDialog();
		 }
		private: System::Void hashDocToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			//Displays the Hash Documentation, copied from the introduction to HashValue.h, used in this program
			 this->toolStripStatusLabel->Text = L"Reading the hash documentation";
			 HashDocDialog^ doc = gcnew HashDocDialog();
			 doc->ShowInTaskbar = false;
			 doc->ShowDialog();
		 }
		private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			//Displays the classic About dialog
			this->toolStripStatusLabel->Text = L"Reading the about documentation";
			MessageBox::Show("\"HashEdit Level 4 Final\" (w/ GUI layer), nicknamed HashEdit\n" +
				"By Pinhas Fedidat (ID 7665692), Aviram Michaeli (ID 302210224), 2011, " +
				"for Mr. Ezra Dasht and Dr. Moshe Goldstein, Mini-project in File Management Systems, Jerusalem College of Technology.\n" +
				"The software is provided \"as is\", without any warranty.",
				"About", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		private: System::Void BeginStatus() {
			//Hides and clear almost everything: this occurs when a file is not opened
			this->writeTextBoxF0->Text = "";
			this->writeTextBoxF1->Text = "";
			this->writeTextBoxF2->Text = "";
			this->writeTextBoxF3->Text = "";
			this->viewTextBoxF0->Text = "";
			this->viewTextBoxF1->Text = "";
			this->viewTextBoxF2->Text = "";
			this->viewTextBoxF3->Text = "";
			this->readTextBoxF0->Text = "";
			this->deleteTriggerButton->BringToFront();
			this->updateTriggerButton->BringToFront();
			this->deleteTriggerButton->Enabled = false;
			this->updateTriggerButton->Enabled = false;
			this->writeGroupBox->Enabled = false;
			this->viewGroupBox->Enabled = false;
			this->readGroupBox->Enabled = false;
			this->deleteToolStripMenuItem->Enabled = false;
			this->fileGroupBox->Enabled = false;
			this->filesizeLabel->Text = "File size (in KB):";
			this->keytypeLabel->Text = "Key type: ";
			this->HashfunctionLabel->Text = "Hash function: ";
			this->creationdateLabel->Text = "Creation date: ";
			this->userTextBox->Text = "";
			this->filenameLabel->Text = "File name: ";
			this->blockListView->Items->Clear();
			this->recordListView->Items->Clear();
			this->fileMapGroupBox->Enabled = false;
			this->emptyVolumeLabel->Text = "Empty volume: ";
		}
		private: System::Void OpenedStatus() {
			//A file has been opened: display what is relevant to the user according to his openmode
			this->deleteTriggerButton->BringToFront();
			this->updateTriggerButton->BringToFront();
			this->fileMapGroupBox->Enabled = true;
			if(file->getOpenMode() != 1)	//read mode
			{
				this->readGroupBox->Enabled = true;
				this->viewGroupBox->Enabled = true;
				this->writeGroupBox->Enabled = false;
			}
			if(file->getOpenMode() != 0)	//write mode (independant of read mode)
			{
				this->readGroupBox->Enabled = false;
				this->viewGroupBox->Enabled = false;
				this->writeGroupBox->Enabled = true;
				this->deleteToolStripMenuItem->Enabled = true;
				this->deleteTriggerButton->Enabled = true;
				this->updateTriggerButton->Enabled = true;
			}
			this->fileGroupBox->Enabled = true;
			this->filesizeLabel->Text = "File size (in KB): " + gcnew String(file->getInfo()[0].c_str());
			this->keytypeLabel->Text = "Key type: " + gcnew String(file->getInfo()[1].c_str());
			this->HashfunctionLabel->Text = "Hash function: " + gcnew String(file->getInfo()[2].c_str());
			this->creationdateLabel->Text = "Creation date: " + gcnew String(file->getInfo()[3].c_str());
			this->userTextBox->Text = gcnew String(file->getInfo()[4].c_str());
			this->filenameLabel->Text = "File name: " + gcnew String(file->getInfo()[5].c_str()) + ".hash";
			this->ActiveControl = this->writeTextBoxF0;

			this->updateBlockList();
		}
		private: System::Void isKeyFilled(System::Object^  sender, System::EventArgs^  e) {
			//an elegant way to ensure the user filled the fields in an orderly manner before he executes
			Int32 test = 0;
			if(((file->getKeyType() == 'I')
				?(!Int32::TryParse(this->readTextBoxF0->Text, test) || this->readTextBoxF0->Text->Length >= 10)
				:this->readTextBoxF0->Text->Length >= 20) || this->readTextBoxF0->Text->Length == 0)
				this->readButton->Enabled = false;
			else
				this->readButton->Enabled = true;
		}
		private: System::Void areReadFilled(System::Object^  sender, System::EventArgs^  e) {
			//an elegant way to ensure the user filled the fields in an orderly manner before he executes
			if(((file->getKeyType() == 'I')
				? this->viewTextBoxF3->Text->Length >= 44 : this->viewTextBoxF3->Text->Length >= 28)
				|| this->viewTextBoxF1->Text->Length == 0 || this->viewTextBoxF1->Text->Length >= 40
				|| this->viewTextBoxF2->Text->Length == 0 || this->viewTextBoxF2->Text->Length >= 40)
			{
				this->deleteTriggerButton->Enabled = false;
				this->updateTriggerButton->Enabled = false;
			}
			else
			{
				this->deleteTriggerButton->Enabled = true;
				this->updateTriggerButton->Enabled = true;
			}
		}
		private: System::Void areWriteFilled(System::Object^  sender, System::EventArgs^  e) {
			//an elegant way to ensure the user filled the fields in an orderly manner before he executes
			Int32 test = 0;
			if(((file->getKeyType() == 'I')
				?(!Int32::TryParse(this->writeTextBoxF0->Text, test) || this->writeTextBoxF0->Text->Length >= 10
				|| this->writeTextBoxF3->Text->Length >= 44)
				:(this->writeTextBoxF0->Text->Length >= 20 || this->writeTextBoxF3->Text->Length >= 28))
				|| this->writeTextBoxF0->Text->Length == 0 || this->writeTextBoxF3->Text->Length == 0
				|| this->writeTextBoxF1->Text->Length == 0 || this->writeTextBoxF1->Text->Length >= 40
				|| this->writeTextBoxF2->Text->Length == 0 || this->writeTextBoxF2->Text->Length >= 40)
				this->writeButton->Enabled = false;
			else
				this->writeButton->Enabled = true;
		}
		private: System::Void writeAB(System::Object^  sender, System::EventArgs^  e) {
			//this function indicates that the program is waiting for the user to fill the fields of the group box he entered
			this->toolStripStatusLabel->Text = "Awaiting write parameters input";
			this->AcceptButton = this->writeButton;
		}
		private: System::Void updateAB(System::Object^  sender, System::EventArgs^  e) {
			//this function indicates that the program is waiting for the user to fill the fields of the group box he entered
			this->toolStripStatusLabel->Text = "Awaiting update parameters input";
			this->AcceptButton = this->updateTriggerButton;
		}
		private: System::Void readAB(System::Object^  sender, System::EventArgs^  e) {
			//this function indicates that the program is waiting for the user to fill the fields of the group box he entered
			this->toolStripStatusLabel->Text = "Awaiting read parameter input";
			this->AcceptButton = this->readButton;
		}
		private: System::Void writeButton_Click(System::Object^  sender, System::EventArgs^  e) {
			//Write a record into the file: recuperate parameters from the fields, call HashFile::write and update
			try
			{
				if(file->getKeyType() == 'I')
				{
					iRecord rec;
					char* ptr = (char*)&rec;
					rec.key = Int32::Parse(this->writeTextBoxF0->Text);
					std::string buffer;
					MarshalString(this->writeTextBoxF1->Text, buffer);
					strncpy_s(rec.firstName, 40, buffer.c_str(), buffer.size());
					MarshalString(this->writeTextBoxF2->Text, buffer);
					strncpy_s(rec.lastName, 40, buffer.c_str(), buffer.size());
					MarshalString(this->writeTextBoxF3->Text, buffer);
					strncpy_s(rec.city, 44, buffer.c_str(), buffer.size());
					file->write(rec.key, ptr);
				}
				else
				{
					cRecord rec;
					char* ptr = (char*)&rec;
					std::string buffer;
					MarshalString(this->writeTextBoxF1->Text, buffer);
					strncpy_s(rec.firstName, 40, buffer.c_str(), buffer.size());
					MarshalString(this->writeTextBoxF2->Text, buffer);
					strncpy_s(rec.lastName, 40, buffer.c_str(), buffer.size());
					MarshalString(this->writeTextBoxF3->Text, buffer);
					strncpy_s(rec.city, 28, buffer.c_str(), buffer.size());
					MarshalString(this->writeTextBoxF0->Text, buffer);
					strncpy_s(rec.key, 20, buffer.c_str(), buffer.size());
					if(file->getKeyType() == 'S')
						file->write(buffer, ptr);
					else
						file->write(const_cast<char*>(buffer.c_str()), ptr);
				}
				this->updateBlockList();
				this->toolStripStatusLabel->Text = "Record successfully written";
			}
			catch(std::exception ex){
				MessageBox::Show(gcnew String(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		private: System::Void readButton_Click(System::Object^  sender, System::EventArgs^  e) {
			//Read a record that is within the file: recuperate parameters from the fields, call HashFile::read and update
			try
			{
				if(file->getKeyType() == 'I')
				{
					iRecord rec;
					char* ptr = (char*)&rec;
					rec.key = Int32::Parse(this->readTextBoxF0->Text);
					file->read(rec.key, ptr, 0);
					this->viewTextBoxF0->Text = System::Convert::ToString(rec.key);
					this->viewTextBoxF1->Text = gcnew String(rec.firstName);
					this->viewTextBoxF2->Text = gcnew String(rec.lastName);
					this->viewTextBoxF3->Text = gcnew String(rec.city);
				}
				else
				{
					cRecord rec;
					char* ptr = (char*)&rec;
					std::string buffer;
					MarshalString(this->readTextBoxF0->Text, buffer);
					if(file->getKeyType() == 'S')
						file->read(buffer, ptr, 0);
					else
						file->read(const_cast<char*>(buffer.c_str()), ptr, 0);
					this->viewTextBoxF0->Text = gcnew String(rec.key);
					this->viewTextBoxF1->Text = gcnew String(rec.firstName);
					this->viewTextBoxF2->Text = gcnew String(rec.lastName);
					this->viewTextBoxF3->Text = gcnew String(rec.city);
				}
				this->updateBlockList();
				this->toolStripStatusLabel->Text = "Record successfully read";
			}
			catch(std::exception ex){
				MessageBox::Show(gcnew String(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		private: System::Void updateTriggerButton_Click(System::Object^  sender, System::EventArgs^  e) {
			//this function triggers the update process through a clever control manipulation
			this->menuStrip1->Enabled = false;
			this->writeGroupBox->Enabled = false;
			this->readGroupBox->Enabled = false;
			this->updateCancelButton->BringToFront();
			this->updateConfirmButton->BringToFront();
			this->toolStripStatusLabel->Text = "Awaiting update decision";
			this->viewTextBoxF0->Enabled = false;
			this->viewTextBoxF1->Enabled = false;
			this->viewTextBoxF2->Enabled = false;
			this->viewTextBoxF3->Enabled = false;
			this->AcceptButton = this->updateConfirmButton;
		}
		private: System::Void deleteTriggerButton_Click(System::Object^  sender, System::EventArgs^  e) {
			//this function triggers the update process through a clever control manipulation
			this->menuStrip1->Enabled = false;
			this->writeGroupBox->Enabled = false;
			this->readGroupBox->Enabled = false;
			this->deleteCancelButton->BringToFront();
			this->deleteConfirmButton->BringToFront();
			this->toolStripStatusLabel->Text = "Awaiting delete decision";
			this->viewTextBoxF0->Enabled = false;
			this->viewTextBoxF1->Enabled = false;
			this->viewTextBoxF2->Enabled = false;
			this->viewTextBoxF3->Enabled = false;
			this->AcceptButton = this->deleteConfirmButton;
		}
		private: System::Void deleteCancelButton_Click(System::Object^  sender, System::EventArgs^  e) {
			//this function allows the user to cancel his choice: after all, changes are hardly reversible
			this->menuStrip1->Enabled = true;
			this->writeGroupBox->Enabled = true;
			this->readGroupBox->Enabled = true;
			this->deleteTriggerButton->BringToFront();
			this->updateTriggerButton->BringToFront();
			this->toolStripStatusLabel->Text = "Record deletion aborted";
			this->viewTextBoxF0->Enabled = true;
			this->viewTextBoxF1->Enabled = true;
			this->viewTextBoxF2->Enabled = true;
			this->viewTextBoxF3->Enabled = true;
			this->AcceptButton = this->updateTriggerButton;
		}
		private: System::Void updateCancelButton_Click(System::Object^  sender, System::EventArgs^  e) {
			//this function allows the user to cancel his choice: after all, changes are hardly reversible
			this->menuStrip1->Enabled = true;
			this->writeGroupBox->Enabled = true;
			this->readGroupBox->Enabled = true;
			this->deleteTriggerButton->BringToFront();
			this->updateTriggerButton->BringToFront();
			this->toolStripStatusLabel->Text = "Record update aborted";
			this->viewTextBoxF0->Enabled = true;
			this->viewTextBoxF1->Enabled = true;
			this->viewTextBoxF2->Enabled = true;
			this->viewTextBoxF3->Enabled = true;
			this->AcceptButton = this->updateTriggerButton;
		}
		private: System::Void updateConfirmButton_Click(System::Object^  sender, System::EventArgs^  e) {
			//the user confirmed his intention to update the record: recuperate parameters, read, update, updateoff
			try
			{
				if(file->getKeyType()=='I')
				{
					iRecord rec;
					char* ptr = (char*)&rec;
					rec.key = Int32::Parse(this->viewTextBoxF0->Text);
					std::string buffer;
					MarshalString(this->viewTextBoxF1->Text, buffer);
					strncpy_s(rec.firstName, 40, buffer.c_str(), buffer.size());
					MarshalString(this->viewTextBoxF2->Text, buffer);
					strncpy_s(rec.lastName, 40, buffer.c_str(), buffer.size());
					MarshalString(this->viewTextBoxF3->Text, buffer);
					strncpy_s(rec.city, 44, buffer.c_str(), buffer.size());
					file->read(rec.key, new char, 1);
					file->update(ptr);
				}
				else
				{
					cRecord rec;
					char* ptr = (char*)&rec;
					std::string buffer;
					MarshalString(this->viewTextBoxF1->Text, buffer);
					strncpy_s(rec.firstName, 40, buffer.c_str(), buffer.size());
					MarshalString(this->viewTextBoxF2->Text, buffer);
					strncpy_s(rec.lastName, 40, buffer.c_str(), buffer.size());
					MarshalString(this->viewTextBoxF3->Text, buffer);
					strncpy_s(rec.city, 28, buffer.c_str(), buffer.size());
					MarshalString(this->viewTextBoxF0->Text, buffer);
					strncpy_s(rec.key, 20, buffer.c_str(), buffer.size());
					if(file->getKeyType() == 'S')
						file->read(buffer, new char, 1);
					else
						file->read(const_cast<char*>(buffer.c_str()), new char, 1);
					file->update(ptr);
				}
				file->updateoff();
				this->menuStrip1->Enabled = true;
				this->writeGroupBox->Enabled = true;
				this->readGroupBox->Enabled = true;
				this->deleteTriggerButton->BringToFront();
				this->updateTriggerButton->BringToFront();
				this->viewTextBoxF0->Enabled = true;
				this->viewTextBoxF1->Enabled = true;
				this->viewTextBoxF2->Enabled = true;
				this->viewTextBoxF3->Enabled = true;
				this->toolStripStatusLabel->Text = "Record successfully updated";
				this->AcceptButton = this->updateTriggerButton;
				this->updateBlockList();
			}
			catch(std::exception ex){
				MessageBox::Show(gcnew String(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		private: System::Void deleteConfirmButton_Click(System::Object^  sender, System::EventArgs^  e) {
			//the user confirmed his intention to delete the record: recuperate parameters, read, delrec, updateoff
			try
			{
				if(file->getKeyType() == 'I')
					file->read(Int32::Parse(this->viewTextBoxF0->Text), new char, 1);
				else
				{
					std::string buffer;
					MarshalString(this->viewTextBoxF0->Text, buffer);
					if(file->getKeyType() == 'S')
						file->read(buffer, new char, 1);
					else
						file->read(const_cast<char*>(buffer.c_str()), new char, 1);
				}
				file->delrec();
				file->updateoff();
				this->viewTextBoxF0->Text = "";
				this->viewTextBoxF1->Text = "";
				this->viewTextBoxF2->Text = "";
				this->viewTextBoxF3->Text = "";
				this->menuStrip1->Enabled = true;
				this->writeGroupBox->Enabled = true;
				this->readGroupBox->Enabled = true;
				this->deleteTriggerButton->BringToFront();
				this->updateTriggerButton->BringToFront();
				this->viewTextBoxF0->Enabled = true;
				this->viewTextBoxF1->Enabled = true;
				this->viewTextBoxF2->Enabled = true;
				this->viewTextBoxF3->Enabled = true;
				this->toolStripStatusLabel->Text = "Record successfully deleted";
				this->AcceptButton = this->updateTriggerButton;
				this->updateBlockList();
			}
			catch(std::exception ex){
				MessageBox::Show(gcnew String(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		private: System::Void updateBlockList(){
			//updates the block list, allowing an overview of all the blocks in the program
			this->blockListView->Items->Clear();
			this->recordListView->Items->Clear();
			int* blockDesc = new int[file->getFileSize()];
			file->getBlockDesc(blockDesc);

			for(int blockNr=1; blockNr<blockDesc[0]; blockNr++)
			{
				String^ NrOfRecs = "";
				int RecNr=0;
				for(; RecNr < blockDesc[blockNr] ; RecNr++)
					NrOfRecs += L'x'; //Unicode would have been awesome because it has checkboxes, but it does not work everywhere...

				ListViewItem^ block = this->blockListView->Items->Add(Convert::ToString(blockNr));
				block->SubItems->Add(NrOfRecs);
			}
			this->emptyVolumeLabel->Text = L"Empty volume: " + Convert::ToString(floor((file->emptyVolume()/0.01 + 0.05))*0.01) + L"%";
		}
		private: System::Void updateRecView(System::Object^  sender, System::EventArgs^  e) {
			//updates the record list, allowing an overview of all the records in the block selected in blockListView
			this->recordListView->Items->Clear();
			if(this->blockListView->SelectedIndices->Count)
			{
				char dataInBlock[1024];
				Collections::IEnumerator^ recEnum = this->blockListView->SelectedIndices->GetEnumerator();
				recEnum->MoveNext();
				int recsInBlock = file->RecordsInBlock(dataInBlock, this->blockListView->SelectedIndices[0] + 1);
				if(file->getKeyType() == 'I')
				{
					for(int i=0; i<recsInBlock; i++)
					{
						iRecord rec = *((iRecord*)&dataInBlock[128*i]);
						ListViewItem^ record = this->recordListView->Items->Add(System::Convert::ToString(rec.key));
						record->SubItems->Add(gcnew String(rec.firstName));
						record->SubItems->Add(gcnew String(rec.lastName));
						record->SubItems->Add(gcnew String(rec.city));
					}
				}
				else
				{
					for(int i=0; i<recsInBlock; i+=128)
					{
						cRecord rec = *((cRecord*)&dataInBlock[i]);
						ListViewItem^ record = this->recordListView->Items->Add(gcnew String(rec.key));
						record->SubItems->Add(gcnew String(rec.firstName));
						record->SubItems->Add(gcnew String(rec.lastName));
						record->SubItems->Add(gcnew String(rec.city));
					}
				}
			}
		}
		private: System::Void typeRecordInSeek(System::Object^  sender, System::EventArgs^  e) {
				//a feature I found useful, copying the record's key of the selected record from the record view
				//to the seek group box's key field, allowing for a quick edit
				 if(this->recordListView->SelectedItems->Count && file->getOpenMode()!=1)
				 {
					 ListViewItem^ item =  safe_cast<ListViewItem^>(this->recordListView->SelectedItems[0]);
					 this->readTextBoxF0->Text = item->SubItems[0]->Text;
				 }
		}
		#pragma endregion
	};
}