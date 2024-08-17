#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class AdminPanelTextBoxes
{
private:
	TextBox^ text{};
	String^ hide_text{};
public:
	AdminPanelTextBoxes(int x, int y, String^ text)
	{
		this->hide_text = text;
		//
		// text
		//
		this->text = gcnew System::Windows::Forms::TextBox();
		this->text->BackColor = System::Drawing::Color::White;
		this->text->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->text->ForeColor = System::Drawing::Color::Black;
		this->text->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->text->Location = System::Drawing::Point(x, y);
		this->text->Size = System::Drawing::Size(200, 40);
		this->text->Multiline = false;

		this->text->AppendText(text);
		this->text->Leave += gcnew System::EventHandler(this, &AdminPanelTextBoxes::text_Leave);
		this->text->Enter += gcnew System::EventHandler(this, &AdminPanelTextBoxes::text_Enter);
	}
	TextBox^ getTextBox()
	{
		return this->text;
	}
private: System::Void text_Leave(System::Object^ sender, System::EventArgs^ e)
{
	if (this->text->Text == "")
		this->text->Text = hide_text;
}
private: System::Void text_Enter(System::Object^ sender, System::EventArgs^ e)
{
	if (this->text->Text == hide_text)
		this->text->Text = "";
}
};

