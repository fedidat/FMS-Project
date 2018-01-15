#pragma once

namespace Level4 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for HashDocDialog
	/// </summary>
	public ref class HashDocDialog : public System::Windows::Forms::Form
	{
	public:
		HashDocDialog(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~HashDocDialog()
		{
			if (components)
			{
				delete components;
				this->AcceptButton = this->closeButton;
			}
		}
	private: System::Windows::Forms::RichTextBox^  DescRichTextBox;
	private: System::Windows::Forms::Button^  closeButton;
	private: System::Windows::Forms::Label^  introLabel;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(HashDocDialog::typeid));
			this->DescRichTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->closeButton = (gcnew System::Windows::Forms::Button());
			this->introLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// DescRichTextBox
			// 
			this->DescRichTextBox->Location = System::Drawing::Point(12, 25);
			this->DescRichTextBox->Name = L"DescRichTextBox";
			this->DescRichTextBox->Size = System::Drawing::Size(474, 285);
			this->DescRichTextBox->TabIndex = 0;
			this->DescRichTextBox->Text = resources->GetString(L"DescRichTextBox.Text");
			// 
			// closeButton
			// 
			this->closeButton->Location = System::Drawing::Point(415, 316);
			this->closeButton->Name = L"closeButton";
			this->closeButton->Size = System::Drawing::Size(71, 32);
			this->closeButton->TabIndex = 1;
			this->closeButton->Text = L"OK";
			this->closeButton->UseVisualStyleBackColor = true;
			this->closeButton->Click += gcnew System::EventHandler(this, &HashDocDialog::button1_Click);
			// 
			// introLabel
			// 
			this->introLabel->AutoSize = true;
			this->introLabel->Location = System::Drawing::Point(12, 9);
			this->introLabel->Name = L"introLabel";
			this->introLabel->Size = System::Drawing::Size(301, 13);
			this->introLabel->TabIndex = 2;
			this->introLabel->Text = L"From the introduction to HashValue.h, used for this mini-project";
			// 
			// HashDocDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(498, 355);
			this->Controls->Add(this->introLabel);
			this->Controls->Add(this->closeButton);
			this->Controls->Add(this->DescRichTextBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"HashDocDialog";
			this->ShowIcon = false;
			this->Text = L"Hash functions documentation";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close();
			 }
	};
}
