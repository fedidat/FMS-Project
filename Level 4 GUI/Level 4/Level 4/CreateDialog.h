#pragma once
#include "stdafx.h"
#include "HashFile\HashFile.h"
#include "HashFile\Library.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace Level4 {

	/// <summary>
	/// Summary for CreateDialog
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	///
	/// This dialog physically creates a .hash file that you can manipulate within
	/// the main form.
	/// </summary>
	public ref class CreateDialog : public System::Windows::Forms::Form
	{
	public:
		CreateDialog(HashFile* hash, bool* flag)
		{
			InitializeComponent();
			this->ActiveControl = this->fileNameTextBox;
			success = flag;
			file = hash;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CreateDialog()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 

	private: bool* success;
	private: HashFile* file;
	private: System::Windows::Forms::Label^  hashFuncLabel;
	private: System::Windows::Forms::Label^  fileSizeLabel;
	private: System::Windows::Forms::NumericUpDown^  fileSizeNumericUpDown;
	private: System::Windows::Forms::ComboBox^  keyTypeComboBox;
	private: System::Windows::Forms::Label^  keyTypeLabel;
	private: System::Windows::Forms::ComboBox^  hashFuncComboBox;
	private: System::Windows::Forms::GroupBox^  createParametersGroupBox;
	private: System::Windows::Forms::CheckBox^  openChechBox;
	private: System::Windows::Forms::RadioButton^  rwRadioButton;
	private: System::Windows::Forms::RadioButton^  readOnlyRadioButton;
	private: System::Windows::Forms::Button^  filePathButton;
	private: System::Windows::Forms::TextBox^  filePathTextBox;
	private: System::Windows::Forms::Label^  filePathLabel;
	private: System::Windows::Forms::TextBox^  fileNameTextBox;
	private: System::Windows::Forms::Label^  userNameLabel;
	private: System::Windows::Forms::Label^  fileNameLabel;
	private: System::Windows::Forms::TextBox^  userNameTextBox;
	private: System::Windows::Forms::Button^  cancelButton;
	private: System::Windows::Forms::Button^  doneButton;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog;
	private: System::Windows::Forms::RadioButton^  radioButton1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->hashFuncLabel = (gcnew System::Windows::Forms::Label());
			this->fileSizeLabel = (gcnew System::Windows::Forms::Label());
			this->fileSizeNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->keyTypeComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->keyTypeLabel = (gcnew System::Windows::Forms::Label());
			this->hashFuncComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->createParametersGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->openChechBox = (gcnew System::Windows::Forms::CheckBox());
			this->rwRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->readOnlyRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->filePathButton = (gcnew System::Windows::Forms::Button());
			this->filePathTextBox = (gcnew System::Windows::Forms::TextBox());
			this->filePathLabel = (gcnew System::Windows::Forms::Label());
			this->fileNameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->userNameLabel = (gcnew System::Windows::Forms::Label());
			this->fileNameLabel = (gcnew System::Windows::Forms::Label());
			this->userNameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->cancelButton = (gcnew System::Windows::Forms::Button());
			this->doneButton = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->fileSizeNumericUpDown))->BeginInit();
			this->createParametersGroupBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// hashFuncLabel
			// 
			this->hashFuncLabel->AutoSize = true;
			this->hashFuncLabel->Location = System::Drawing::Point(6, 127);
			this->hashFuncLabel->Name = L"hashFuncLabel";
			this->hashFuncLabel->Size = System::Drawing::Size(73, 13);
			this->hashFuncLabel->TabIndex = 24;
			this->hashFuncLabel->Text = L"Hash function";
			// 
			// fileSizeLabel
			// 
			this->fileSizeLabel->AutoSize = true;
			this->fileSizeLabel->Location = System::Drawing::Point(6, 73);
			this->fileSizeLabel->Name = L"fileSizeLabel";
			this->fileSizeLabel->Size = System::Drawing::Size(78, 13);
			this->fileSizeLabel->TabIndex = 22;
			this->fileSizeLabel->Text = L"File size (in KB)";
			// 
			// fileSizeNumericUpDown
			// 
			this->fileSizeNumericUpDown->Location = System::Drawing::Point(90, 71);
			this->fileSizeNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100000, 0, 0, 0});
			this->fileSizeNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->fileSizeNumericUpDown->Name = L"fileSizeNumericUpDown";
			this->fileSizeNumericUpDown->Size = System::Drawing::Size(64, 20);
			this->fileSizeNumericUpDown->TabIndex = 10;
			this->fileSizeNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {40, 0, 0, 0});
			this->fileSizeNumericUpDown->ValueChanged += gcnew System::EventHandler(this, &CreateDialog::areAllFilled);
			// 
			// keyTypeComboBox
			// 
			this->keyTypeComboBox->FormattingEnabled = true;
			this->keyTypeComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"C++ string", L"C string", L"Integer"});
			this->keyTypeComboBox->Location = System::Drawing::Point(90, 97);
			this->keyTypeComboBox->Name = L"keyTypeComboBox";
			this->keyTypeComboBox->Size = System::Drawing::Size(233, 21);
			this->keyTypeComboBox->TabIndex = 11;
			this->keyTypeComboBox->TextChanged += gcnew System::EventHandler(this, &CreateDialog::areAllFilled);
			// 
			// keyTypeLabel
			// 
			this->keyTypeLabel->AutoSize = true;
			this->keyTypeLabel->Location = System::Drawing::Point(6, 100);
			this->keyTypeLabel->Name = L"keyTypeLabel";
			this->keyTypeLabel->Size = System::Drawing::Size(48, 13);
			this->keyTypeLabel->TabIndex = 23;
			this->keyTypeLabel->Text = L"Key type";
			// 
			// hashFuncComboBox
			// 
			this->hashFuncComboBox->FormattingEnabled = true;
			this->hashFuncComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(10) {L"MODHfunc", L"MULTHfunc", L"RSHfunc", L"JSHfunc", 
				L"PJWHfunc", L"ELFHfunc", L"BKDRHfunc", L"SDBMHfunc", L"DJBHfunc", L"APHfunc"});
			this->hashFuncComboBox->Location = System::Drawing::Point(90, 124);
			this->hashFuncComboBox->Name = L"hashFuncComboBox";
			this->hashFuncComboBox->Size = System::Drawing::Size(233, 21);
			this->hashFuncComboBox->TabIndex = 12;
			this->hashFuncComboBox->TextChanged += gcnew System::EventHandler(this, &CreateDialog::areAllFilled);
			// 
			// createParametersGroupBox
			// 
			this->createParametersGroupBox->Controls->Add(this->radioButton1);
			this->createParametersGroupBox->Controls->Add(this->openChechBox);
			this->createParametersGroupBox->Controls->Add(this->hashFuncComboBox);
			this->createParametersGroupBox->Controls->Add(this->rwRadioButton);
			this->createParametersGroupBox->Controls->Add(this->keyTypeLabel);
			this->createParametersGroupBox->Controls->Add(this->readOnlyRadioButton);
			this->createParametersGroupBox->Controls->Add(this->keyTypeComboBox);
			this->createParametersGroupBox->Controls->Add(this->filePathButton);
			this->createParametersGroupBox->Controls->Add(this->fileSizeNumericUpDown);
			this->createParametersGroupBox->Controls->Add(this->filePathTextBox);
			this->createParametersGroupBox->Controls->Add(this->fileSizeLabel);
			this->createParametersGroupBox->Controls->Add(this->filePathLabel);
			this->createParametersGroupBox->Controls->Add(this->hashFuncLabel);
			this->createParametersGroupBox->Controls->Add(this->fileNameTextBox);
			this->createParametersGroupBox->Controls->Add(this->userNameLabel);
			this->createParametersGroupBox->Controls->Add(this->fileNameLabel);
			this->createParametersGroupBox->Controls->Add(this->userNameTextBox);
			this->createParametersGroupBox->Location = System::Drawing::Point(12, 12);
			this->createParametersGroupBox->Name = L"createParametersGroupBox";
			this->createParametersGroupBox->Size = System::Drawing::Size(329, 211);
			this->createParametersGroupBox->TabIndex = 26;
			this->createParametersGroupBox->TabStop = false;
			this->createParametersGroupBox->Text = L"File create parameters";
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(78, 185);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(79, 17);
			this->radioButton1->TabIndex = 32;
			this->radioButton1->Text = L"Write mode";
			this->radioButton1->UseVisualStyleBackColor = true;
			//
			// folderBrowserDialog
			//
			this->folderBrowserDialog->RootFolder = System::Environment::SpecialFolder::Desktop;
			// 
			// openChechBox
			// 
			this->openChechBox->AutoSize = true;
			this->openChechBox->Checked = true;
			this->openChechBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->openChechBox->Location = System::Drawing::Point(6, 186);
			this->openChechBox->Name = L"openChechBox";
			this->openChechBox->Size = System::Drawing::Size(63, 17);
			this->openChechBox->TabIndex = 17;
			this->openChechBox->Text = L"Open in";
			this->openChechBox->UseVisualStyleBackColor = true;
			this->openChechBox->CheckedChanged += gcnew System::EventHandler(this, &CreateDialog::openSwitch);
			// 
			// rwRadioButton
			// 
			this->rwRadioButton->AutoSize = true;
			this->rwRadioButton->Checked = true;
			this->rwRadioButton->Location = System::Drawing::Point(249, 186);
			this->rwRadioButton->Name = L"rwRadioButton";
			this->rwRadioButton->Size = System::Drawing::Size(73, 17);
			this->rwRadioButton->TabIndex = 18;
			this->rwRadioButton->TabStop = true;
			this->rwRadioButton->Text = L"RW mode";
			this->rwRadioButton->UseVisualStyleBackColor = true;
			// 
			// readOnlyRadioButton
			// 
			this->readOnlyRadioButton->AutoSize = true;
			this->readOnlyRadioButton->Location = System::Drawing::Point(163, 185);
			this->readOnlyRadioButton->Name = L"readOnlyRadioButton";
			this->readOnlyRadioButton->Size = System::Drawing::Size(80, 17);
			this->readOnlyRadioButton->TabIndex = 19;
			this->readOnlyRadioButton->Text = L"Read mode";
			this->readOnlyRadioButton->UseVisualStyleBackColor = true;
			// 
			// filePathButton
			// 
			this->filePathButton->Location = System::Drawing::Point(259, 151);
			this->filePathButton->Name = L"filePathButton";
			this->filePathButton->Size = System::Drawing::Size(64, 29);
			this->filePathButton->TabIndex = 13;
			this->filePathButton->Text = L"Browse...";
			this->filePathButton->UseVisualStyleBackColor = true;
			this->filePathButton->Click += gcnew System::EventHandler(this, &CreateDialog::filePathButton_Click);
			this->filePathButton->Leave += gcnew System::EventHandler(this, &CreateDialog::areAllFilled);
			// 
			// filePathTextBox
			// 
			this->filePathTextBox->Enabled = false;
			this->filePathTextBox->Location = System::Drawing::Point(90, 156);
			this->filePathTextBox->Name = L"filePathTextBox";
			this->filePathTextBox->ReadOnly = true;
			this->filePathTextBox->Size = System::Drawing::Size(163, 20);
			this->filePathTextBox->TabIndex = 30;
			this->filePathTextBox->TabStop = false;
			this->filePathTextBox->TextChanged += gcnew System::EventHandler(this, &CreateDialog::areAllFilled);
			// 
			// filePathLabel
			// 
			this->filePathLabel->AutoSize = true;
			this->filePathLabel->Location = System::Drawing::Point(7, 159);
			this->filePathLabel->Name = L"filePathLabel";
			this->filePathLabel->Size = System::Drawing::Size(47, 13);
			this->filePathLabel->TabIndex = 25;
			this->filePathLabel->Text = L"File path";
			// 
			// fileNameTextBox
			// 
			this->fileNameTextBox->Location = System::Drawing::Point(90, 19);
			this->fileNameTextBox->Name = L"fileNameTextBox";
			this->fileNameTextBox->Size = System::Drawing::Size(233, 20);
			this->fileNameTextBox->TabIndex = 0;
			this->fileNameTextBox->TextChanged += gcnew System::EventHandler(this, &CreateDialog::areAllFilled);
			// 
			// userNameLabel
			// 
			this->userNameLabel->AutoSize = true;
			this->userNameLabel->Location = System::Drawing::Point(6, 48);
			this->userNameLabel->Name = L"userNameLabel";
			this->userNameLabel->Size = System::Drawing::Size(58, 13);
			this->userNameLabel->TabIndex = 21;
			this->userNameLabel->Text = L"User name";
			this->userNameLabel->TextChanged += gcnew System::EventHandler(this, &CreateDialog::areAllFilled);
			// 
			// fileNameLabel
			// 
			this->fileNameLabel->AutoSize = true;
			this->fileNameLabel->Location = System::Drawing::Point(6, 22);
			this->fileNameLabel->Name = L"fileNameLabel";
			this->fileNameLabel->Size = System::Drawing::Size(52, 13);
			this->fileNameLabel->TabIndex = 20;
			this->fileNameLabel->Text = L"File name";
			this->fileNameLabel->TextChanged += gcnew System::EventHandler(this, &CreateDialog::areAllFilled);
			// 
			// userNameTextBox
			// 
			this->userNameTextBox->Location = System::Drawing::Point(90, 45);
			this->userNameTextBox->Name = L"userNameTextBox";
			this->userNameTextBox->Size = System::Drawing::Size(233, 20);
			this->userNameTextBox->TabIndex = 1;
			this->userNameTextBox->TextChanged += gcnew System::EventHandler(this, &CreateDialog::areAllFilled);
			// 
			// cancelButton
			// 
			this->cancelButton->Location = System::Drawing::Point(207, 229);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(60, 30);
			this->cancelButton->TabIndex = 16;
			this->cancelButton->Text = L"Cancel";
			this->cancelButton->UseVisualStyleBackColor = true;
			this->cancelButton->Click += gcnew System::EventHandler(this, &CreateDialog::cancelButton_Click);
			// 
			// doneButton
			// 
			this->doneButton->Enabled = false;
			this->doneButton->Location = System::Drawing::Point(273, 229);
			this->doneButton->Name = L"doneButton";
			this->doneButton->Size = System::Drawing::Size(62, 30);
			this->doneButton->TabIndex = 15;
			this->doneButton->Text = L"OK";
			this->doneButton->UseVisualStyleBackColor = true;
			this->doneButton->Click += gcnew System::EventHandler(this, &CreateDialog::doneButton_Click);
			// 
			// CreateDialog
			// 
			this->AcceptButton = this->doneButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(346, 267);
			this->Controls->Add(this->doneButton);
			this->Controls->Add(this->cancelButton);
			this->Controls->Add(this->createParametersGroupBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"CreateDialog";
			this->Text = L"CreateDialog";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->fileSizeNumericUpDown))->EndInit();
			this->createParametersGroupBox->ResumeLayout(false);
			this->createParametersGroupBox->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void cancelButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close();	//cancel file creating
			 }
	private: System::Void doneButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 std::string filename;	//format the textboxes
				 MarshalString(this->fileNameTextBox->Text, filename);
				 std::string username;
				 MarshalString(this->userNameTextBox->Text, username);
				 std::string workingDir;
				 MarshalString(this->filePathTextBox->Text, workingDir);
				char keyType = (keyTypeComboBox->SelectedIndex==0)?'S':((keyTypeComboBox->SelectedIndex==1)?'C':'I');	//get the keytype
				try{
					bool status[2];
					file->isOpen(status);
					if(status[0])
						file->hclose();	//close any file still opened
					if(keyType == 'I')	//create a file containing integer records
						file->hcreate(filename, username, 128, hashFuncComboBox->SelectedIndex,
							workingDir, Decimal::ToInt32(fileSizeNumericUpDown->Value), 0, keyType, 4);
					else	//create a file containing string records
						file->hcreate(filename, username, 128, hashFuncComboBox->SelectedIndex,
							workingDir, Decimal::ToInt32(fileSizeNumericUpDown->Value), 0, keyType, 20);
					if(this->openChechBox->Checked == true)	//if the user wants to open the file that was just created
					{
						if(this->rwRadioButton->Checked == true)	//check the openmode, and execute
							file->hopen(filename, username, workingDir, 2);
						 else if(this->readOnlyRadioButton->Checked == true)
							 file->hopen(filename, username, workingDir, 0);
						 else
							 file->hopen(filename, username, workingDir, 1);
					}
					*success = true;
					this->Close();	//no problem, returning to mainform
				}
				catch(std::exception ex){
					MessageBox::Show(gcnew String(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			 }
	private: System::Void areAllFilled(System::Object^  sender, System::EventArgs^  e) {
				 if(this->fileNameTextBox->Text->Length <= 0 || this->fileNameTextBox->Text->Length >=12
					 || this->userNameTextBox->Text->Length <= 0 || this->userNameTextBox->Text->Length >=10
					 || this->keyTypeComboBox->SelectedIndex == -1 || this->hashFuncComboBox->SelectedIndex == -1
						 || this->filePathTextBox->Text->Length == 0)
					 this->doneButton->Enabled = false;	//an elegant solution to allow the user to validate only if the fileds are in a suitable format
				 else
					 this->doneButton->Enabled = true;
			 }
private: System::Void filePathButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (folderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			 {
				 this->filePathTextBox->Text = this->folderBrowserDialog->SelectedPath; 
			 }
		 }
private: System::Void openSwitch(System::Object^  sender, System::EventArgs^  e) {
			 if(this->openChechBox->Checked == true)	//if the user indicates he does not want to open the file, disable the openmode fields
			 {
				 this->readOnlyRadioButton->Enabled = true;
				 this->rwRadioButton->Enabled = true;
			 }
			 else	//and conversely
			 {
				 this->readOnlyRadioButton->Enabled = false;
				 this->rwRadioButton->Enabled = false;
			 }
		 }
};
}