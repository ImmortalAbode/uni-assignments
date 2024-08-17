#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class AdditionalRunes
{
private:
	Int32^ AdditionalRuneID{};
	Int32^ TypeRuneID{};
	array<Byte>^ AdditionalRuneImage{};
	String^ AdditionalRuneName{};
	String^ AdditionalRuneDescr{};
	//Информационные панели.
private: System::Windows::Forms::Panel^ additionalrunes_catalog_panel{};
private: System::Windows::Forms::Panel^ all_descr_panel{};
	   //Объекты панелей со свойствами данных БД.
private: System::Windows::Forms::PictureBox^ additional_image{};
private: System::Windows::Forms::TextBox^ additional_name{};
private: System::Windows::Forms::TextBox^ additional_descr{};
public:
	AdditionalRunes(SqlDataReader^ reader, Panel^ additionalrunes_catalog_panel, Panel^ all_descr_panel)
	{
		this->AdditionalRuneID = reader->GetInt32(0);
		this->TypeRuneID = reader->GetInt32(1);
		this->AdditionalRuneImage = (array<Byte>^)reader->GetSqlBinary(2);
		this->AdditionalRuneDescr = reader->GetString(3);
		this->AdditionalRuneName = reader->GetString(4);
		//
		// additional_image
		// 
		this->additional_image = gcnew System::Windows::Forms::PictureBox();
		this->additional_image->BackColor = System::Drawing::Color::Transparent;
		this->additional_image->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->additional_image->Size = System::Drawing::Size(40, 40);
		this->additional_image->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		//Импорт изображения из БД.
		this->additional_image->Image = getPNGfromByte();
		this->additional_image->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AdditionalRunes::additional_image_MouseClick);
		//
		// additional_descr
		// 
		this->additional_descr = gcnew System::Windows::Forms::TextBox();
		this->additional_descr->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
		this->additional_descr->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->additional_descr->ForeColor = System::Drawing::Color::DarkBlue;
		this->additional_descr->ReadOnly = true;
		this->additional_descr->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->additional_descr->Location = System::Drawing::Point(5, 95);
		this->additional_descr->Size = System::Drawing::Size(340, 300);
		this->additional_descr->Multiline = true;
		this->additional_descr->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		this->additional_descr->AppendText(this->AdditionalRuneDescr);
		//
		// additional_name
		// 
		this->additional_name = gcnew System::Windows::Forms::TextBox();
		this->additional_name->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
		this->additional_name->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->additional_name->ForeColor = System::Drawing::Color::DarkBlue;
		this->additional_name->ReadOnly = true;
		this->additional_name->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->additional_name->Location = System::Drawing::Point(100, 5);
		this->additional_name->Size = System::Drawing::Size(200, 100);
		this->additional_name->AppendText(this->AdditionalRuneName);
		//
		// all_descr_panel
		//
		this->all_descr_panel = all_descr_panel;
		this->additionalrunes_catalog_panel = additionalrunes_catalog_panel;
	}
	void SpecializedActionsForSelectingAdditionalRunes()
	{
		this->additionalrunes_catalog_panel->Controls->Add(this->additional_image);
	}
	System::Windows::Forms::PictureBox^ getAdditionalPB()
	{
		return this->additional_image;
	}
	System::Drawing::Image^ getPNGfromByte()
	{
		System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream(this->AdditionalRuneImage);
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
		return this->additional_descr;
	}
private: System::Void additional_image_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	this->all_descr_panel->Controls->Clear();
	System::Windows::Forms::PictureBox^ copy_image = gcnew System::Windows::Forms::PictureBox();
	copy_image->Image = this->additional_image->Image;
	copy_image->Location = System::Drawing::Point(5, 5);
	copy_image->BackColor = this->additional_image->BackColor;
	copy_image->BorderStyle = this->additional_image->BorderStyle;
	copy_image->Size = System::Drawing::Size(85, 85);
	copy_image->SizeMode = this->additional_image->SizeMode;
	this->all_descr_panel->BackColor = System::Drawing::Color::CadetBlue;
	this->all_descr_panel->Controls->Add(copy_image);
	this->all_descr_panel->Controls->Add(this->additional_name);
	this->all_descr_panel->Controls->Add(this->additional_descr);
	this->all_descr_panel->Cursor = System::Windows::Forms::Cursors::IBeam;
}
};

