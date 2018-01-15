#pragma once
#include "stdafx.h"
#include "HashFile\Hashfile.h"
#include "HashFile\Library.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace Level4 {

	/// <summary>
	/// Summary for OpenDialog
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class OpenDialog : public System::Windows::Forms::Form
	{
	public:
		OpenDialog(HashFile* hash, bool* status)
		{
			InitializeComponent();
			file = hash;
			success = status;
			this->ActiveControl = this->openFileButton;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~OpenDialog()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::GroupBox^  openFileGroupBox;
	private: System::Windows::Forms::Label^  fileLabel;
	private: System::Windows::Forms::TextBox^  openFileTextBox;
	private: System::Windows::Forms::Button^  openFileButton;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Label^  userNameLabel;
	private: System::Windows::Forms::TextBox^  userNameTextBox;
	private: System::Windows::Forms::RadioButton^  rwRadioButton;
	private: System::Windows::Forms::RadioButton^  readOnlyRadioButton;
	private: System::Windows::Forms::Button^  doneButton;
	private: System::Windows::Forms::Button^  cancelButton;
	private: System::Windows::Forms::RadioButton^  radioButton1;

	private: HashFile* file;
	private: bool* success;

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
			this->openFileTextBox = (gcnew System::Windows::Forms::TextBox());
			this->openFileButton = (gcnew System::Windows::Forms::Button());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->userNameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->userNameLabel = (gcnew System::Windows::Forms::Label());
			this->doneButton = (gcnew System::Windows::Forms::Button());
			this->cancelButton = (gcnew System::Windows::Forms::Button());
			this->openFileGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->rwRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->readOnlyRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->fileLabel = (gcnew System::Windows::Forms::Label());
			this->openFileGroupBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// openFileTextBox
			// 
			this->openFileTextBox->Enabled = false;
			this->openFileTextBox->Location = System::Drawing::Point(35, 23);
			this->openFileTextBox->Name = L"openFileTextBox";
			this->openFileTextBox->ReadOnly = true;
			this->openFileTextBox->Size = System::Drawing::Size(205, 20);
			this->openFileTextBox->TabIndex = 30;
			this->openFileTextBox->TextChanged += gcnew System::EventHandler(this, &OpenDialog::areAllFilled);
			// 
			// openFileButton
			// 
			this->openFileButton->Location = System::Drawing::Point(246, 19);
			this->openFileButton->Name = L"openFileButton";
			this->openFileButton->Size = System::Drawing::Size(64, 26);
			this->openFileButton->TabIndex = 0;
			this->openFileButton->Text = L"Browse...";
			this->openFileButton->UseVisualStyleBackColor = true;
			this->openFileButton->Click += gcnew System::EventHandler(this, &OpenDialog::openFileButton_Click);
			// 
			// openFileDialog
			// 
			this->openFileDialog->Filter = L"Hash files (*.hash)|*.hash";
			this->openFileDialog->Title = L"Open a hash file";
			this->openFileDialog->InitialDirectory = Environment::GetFolderPath(System::Environment::SpecialFolder::Desktop);
			// 
			// userNameTextBox
			// 
			this->userNameTextBox->Location = System::Drawing::Point(70, 51);
			this->userNameTextBox->Name = L"userNameTextBox";
			this->userNameTextBox->Size = System::Drawing::Size(240, 20);
			this->userNameTextBox->TabIndex = 1;
			this->userNameTextBox->TextChanged += gcnew System::EventHandler(this, &OpenDialog::areAllFilled);
			// 
			// userNameLabel
			// 
			this->userNameLabel->AutoSize = true;
			this->userNameLabel->Location = System::Drawing::Point(6, 54);
			this->userNameLabel->Name = L"userNameLabel";
			this->userNameLabel->Size = System::Drawing::Size(58, 13);
			this->userNameLabel->TabIndex = 4;
			this->userNameLabel->Text = L"User name";
			// 
			// doneButton
			// 
			this->doneButton->Enabled = false;
			this->doneButton->Location = System::Drawing::Point(274, 120);
			this->doneButton->Name = L"doneButton";
			this->doneButton->Size = System::Drawing::Size(75, 26);
			this->doneButton->TabIndex = 2;
			this->doneButton->Text = L"OK";
			this->doneButton->UseVisualStyleBackColor = true;
			this->doneButton->Click += gcnew System::EventHandler(this, &OpenDialog::doneButton_Click);
			// 
			// cancelButton
			// 
			this->cancelButton->Location = System::Drawing::Point(193, 120);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(75, 26);
			this->cancelButton->TabIndex = 3;
			this->cancelButton->Text = L"Cancel";
			this->cancelButton->UseVisualStyleBackColor = true;
			this->cancelButton->Click += gcnew System::EventHandler(this, &OpenDialog::cancelButton_Click);
			// 
			// openFileGroupBox
			// 
			this->openFileGroupBox->Controls->Add(this->radioButton1);
			this->openFileGroupBox->Controls->Add(this->rwRadioButton);
			this->openFileGroupBox->Controls->Add(this->readOnlyRadioButton);
			this->openFileGroupBox->Controls->Add(this->fileLabel);
			this->openFileGroupBox->Controls->Add(this->userNameLabel);
			this->openFileGroupBox->Controls->Add(this->userNameTextBox);
			this->openFileGroupBox->Controls->Add(this->openFileButton);
			this->openFileGroupBox->Controls->Add(this->openFileTextBox);
			this->openFileGroupBox->Location = System::Drawing::Point(12, 12);
			this->openFileGroupBox->Name = L"openFileGroupBox";
			this->openFileGroupBox->Size = System::Drawing::Size(338, 102);
			this->openFileGroupBox->TabIndex = 7;
			this->openFileGroupBox->TabStop = false;
			this->openFileGroupBox->Text = L"Open file parameters";
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(114, 79);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(101, 17);
			this->radioButton1->TabIndex = 31;
			this->radioButton1->Text = L"Write-only mode";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// rwRadioButton
			// 
			this->rwRadioButton->AutoSize = true;
			this->rwRadioButton->Checked = true;
			this->rwRadioButton->Location = System::Drawing::Point(219, 77);
			this->rwRadioButton->Name = L"rwRadioButton";
			this->rwRadioButton->Size = System::Drawing::Size(113, 17);
			this->rwRadioButton->TabIndex = 4;
			this->rwRadioButton->TabStop = true;
			this->rwRadioButton->Text = L"Read / write mode";
			this->rwRadioButton->UseVisualStyleBackColor = true;
			// 
			// readOnlyRadioButton
			// 
			this->readOnlyRadioButton->AutoSize = true;
			this->readOnlyRadioButton->Location = System::Drawing::Point(6, 77);
			this->readOnlyRadioButton->Name = L"readOnlyRadioButton";
			this->readOnlyRadioButton->Size = System::Drawing::Size(102, 17);
			this->readOnlyRadioButton->TabIndex = 5;
			this->readOnlyRadioButton->Text = L"Read-only mode";
			this->readOnlyRadioButton->UseVisualStyleBackColor = true;
			// 
			// fileLabel
			// 
			this->fileLabel->AutoSize = true;
			this->fileLabel->Location = System::Drawing::Point(6, 26);
			this->fileLabel->Name = L"fileLabel";
			this->fileLabel->Size = System::Drawing::Size(23, 13);
			this->fileLabel->TabIndex = 5;
			this->fileLabel->Text = L"File";
			// 
			// OpenDialog
			// 
			this->AcceptButton = this->doneButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(356, 153);
			this->Controls->Add(this->cancelButton);
			this->Controls->Add(this->openFileGroupBox);
			this->Controls->Add(this->doneButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"OpenDialog";
			this->Text = L"OpenDialog";
			this->openFileGroupBox->ResumeLayout(false);
			this->openFileGroupBox->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void openFileButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Browse in order to find the file is going to be opened
				 if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 this->openFileTextBox->Text = this->openFileDialog->FileName; 
					 this->ActiveControl = this->userNameTextBox;
				 }
			 }
	private: System::Void cancelButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 //The use canceled the opening of the file
				 this->Close();
			 }
	private: System::Void doneButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Opens the file: recuperate the parameters from the form's fields, call HashFile::hopen, return to MainForm
				 std::string filename, username, workingDir;
				 MarshalString(System::IO::Path::GetFileNameWithoutExtension(this->openFileDialog->FileName), filename);
				 MarshalString(this->userNameTextBox->Text, username);
				 MarshalString(System::IO::Path::GetDirectoryName(this->openFileDialog->FileName), workingDir);
				 try
				 {
					 bool status[2];
					 file->isOpen(status);
					 if(status[0])
						 file->hclose();
					 if(this->rwRadioButton->Checked == true)
						 file->hopen(filename, username, workingDir, 2);
					 else if(this->readOnlyRadioButton->Checked == true)
						 file->hopen(filename, username, workingDir, 0);
					 else
						 file->hopen(filename, username, workingDir, 1);
					 *success = true;
					 this->Close();
				 }
				 catch(std::exception ex)
				 {
					 MessageBox::Show(gcnew String(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				 }
			 }
	private: System::Void areAllFilled(System::Object^  sender, System::EventArgs^  e) {
				 //an elegant solution to allow the user to validate only if the fileds are in a suitable format
				 if(this->openFileTextBox->Text->Length <= 0
					 || this->userNameTextBox->Text->Length <= 0 || this->userNameTextBox->Text->Length >= 10)
					 this->doneButton->Enabled = false;
				 else
					 this->doneButton->Enabled = true;
			 }
	};
}
