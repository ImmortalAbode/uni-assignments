#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class KeyRunes
{
private:
	Int32^ KeyRuneID{};
	Int32^ TypeRuneID{};
	array<Byte>^ KeyRuneImage{};
	String^ KeyRuneName{};
	String^ KeyRuneDescr{};
//Информационные панели.
private: System::Windows::Forms::Panel^ keyrunes_catalog_panel{};
private: System::Windows::Forms::Panel^ all_descr_panel{};
//Объекты панелей со свойствами данных БД.
private: System::Windows::Forms::PictureBox^ key_image{};
private: System::Windows::Forms::TextBox^ key_name{};
private: System::Windows::Forms::TextBox^ key_descr{};
public:
	KeyRunes(SqlDataReader^ reader, Panel^ keyrunes_catalog_panel, Panel^ all_descr_panel)
	{
		this->KeyRuneID = reader->GetInt32(0);
		this->TypeRuneID = reader->GetInt32(1);
		this->KeyRuneImage = (array<Byte>^)reader->GetSqlBinary(2);
		this->KeyRuneDescr = reader->GetString(3);
		this->KeyRuneName = reader->GetString(4);
		//
		// key_image
		// 
		this->key_image = gcnew System::Windows::Forms::PictureBox();
		this->key_image->BackColor = System::Drawing::Color::Transparent;
		this->key_image->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->key_image->Size = System::Drawing::Size(40, 40);
		this->key_image->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		//Импорт изображения из БД.
		this->key_image->Image = getPNGfromByte();
		this->key_image->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &KeyRunes::key_image_MouseClick);
		//
		// key_descr
		// 
		this->key_descr = gcnew System::Windows::Forms::TextBox();
		this->key_descr->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
		this->key_descr->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->key_descr->ForeColor = System::Drawing::Color::DarkBlue;
		this->key_descr->ReadOnly = true;
		this->key_descr->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->key_descr->Location = System::Drawing::Point(5, 95);
		this->key_descr->Size = System::Drawing::Size(340, 300);
		this->key_descr->Multiline = true;
		this->key_descr->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		this->key_descr->AppendText(this->KeyRuneDescr);
		//
		// key_name
		// 
		this->key_name = gcnew System::Windows::Forms::TextBox();
		this->key_name->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
		this->key_name->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->key_name->ForeColor = System::Drawing::Color::DarkBlue;
		this->key_name->ReadOnly = true;
		this->key_name->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->key_name->Location = System::Drawing::Point(100, 5);
		this->key_name->Size = System::Drawing::Size(200, 100);
		this->key_name->AppendText(this->KeyRuneName);
		//
		// all_descr_panel
		//
		this->all_descr_panel = all_descr_panel;
		this->keyrunes_catalog_panel = keyrunes_catalog_panel;
	}
	void SpecializedActionsForSelectingKeyRunes()
	{
		this->keyrunes_catalog_panel->Controls->Add(this->key_image);
	}
	System::Windows::Forms::PictureBox^ getKeyPB()
	{
		return this->key_image;
	}
	System::Drawing::Image^ getPNGfromByte()
	{
		System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream(this->KeyRuneImage);
		return gcnew Bitmap(ms);
	}
	Int32^ getTypeRuneID()
	{
		return this->TypeRuneID;
	}
	System::Windows::Forms::Panel^ GetDescrPanel()
	{
		return this->all_descr_panel;
	}
	System::Windows::Forms::TextBox^ GetText()
	{
		return this->key_descr;
	}
private: System::Void key_image_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		this->all_descr_panel->Controls->Clear();
		System::Windows::Forms::PictureBox^ copy_image = gcnew System::Windows::Forms::PictureBox();
		copy_image->Image = this->key_image->Image;
		copy_image->Location = System::Drawing::Point(5, 5);
		copy_image->BackColor = this->key_image->BackColor;
		copy_image->BorderStyle = this->key_image->BorderStyle;
		copy_image->Size = System::Drawing::Size(85, 85);
		copy_image->SizeMode = this->key_image->SizeMode;
		this->all_descr_panel->BackColor = System::Drawing::Color::CadetBlue;
		this->all_descr_panel->Controls->Add(copy_image);
		this->all_descr_panel->Controls->Add(this->key_name);
		this->all_descr_panel->Controls->Add(this->key_descr);
		this->all_descr_panel->Cursor = System::Windows::Forms::Cursors::IBeam;
	}
};

