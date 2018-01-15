#pragma once

namespace Level4 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for HowtoUseDialog
	/// </summary>
	public ref class HowtoUseDialog : public System::Windows::Forms::Form
	{
	public:
		HowtoUseDialog(void)
		{
			InitializeComponent();
			this->AcceptButton = this->closeButton;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~HowtoUseDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  closeButton;
	protected: 
	private: System::Windows::Forms::RichTextBox^  DescRichTextBox;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(HowtoUseDialog::typeid));
			this->closeButton = (gcnew System::Windows::Forms::Button());
			this->DescRichTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// closeButton
			// 
			this->closeButton->Location = System::Drawing::Point(431, 330);
			this->closeButton->Name = L"closeButton";
			this->closeButton->Size = System::Drawing::Size(71, 32);
			this->closeButton->TabIndex = 3;
			this->closeButton->Text = L"OK";
			this->closeButton->UseVisualStyleBackColor = true;
			this->closeButton->Click += gcnew System::EventHandler(this, &HowtoUseDialog::closeButton_Click);
			// 
			// DescRichTextBox
			// 
			this->DescRichTextBox->Location = System::Drawing::Point(12, 12);
			this->DescRichTextBox->Name = L"DescRichTextBox";
			this->DescRichTextBox->Size = System::Drawing::Size(490, 312);
			this->DescRichTextBox->TabIndex = 2;
			this->DescRichTextBox->Text = resources->GetString(L"DescRichTextBox.Text");
			// 
			// HowtoUseDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(514, 373);
			this->Controls->Add(this->closeButton);
			this->Controls->Add(this->DescRichTextBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"HowtoUseDialog";
			this->ShowIcon = false;
			this->Text = L"Help";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void closeButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close();
			 }
	};
}
