#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class AdaptiveRunes
{
private:
	Int32^ AdaptiveRuneID{};
	array<Byte>^ AdaptiveRuneImage{};
	String^ AdaptiveRuneDescr{};
	String^ AdaptiveRuneName{};
//Информационные панели.
private: System::Windows::Forms::Panel^ adaptiverunes_catalog_panel{};
private: System::Windows::Forms::Panel^ all_descr_panel{};
//Объекты панелей со свойствами данных БД.
private: System::Windows::Forms::PictureBox^ adaptive_image{};
private: System::Windows::Forms::TextBox^ adaptive_name{};
private: System::Windows::Forms::TextBox^ adaptive_descr{};
public:
	AdaptiveRunes(SqlDataReader^ reader, Panel^ adaptiverunes_catalog_panel, Panel^ all_descr_panel)
	{
		this->AdaptiveRuneID = reader->GetInt32(0);
		this->AdaptiveRuneImage = (array<Byte>^)reader->GetSqlBinary(1);
		this->AdaptiveRuneDescr = reader->GetString(2);
		this->AdaptiveRuneName = reader->GetString(3);
		//
		// adaptive_image
		// 
		this->adaptive_image = gcnew System::Windows::Forms::PictureBox();
		this->adaptive_image->BackColor = System::Drawing::Color::Transparent;
		this->adaptive_image->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->adaptive_image->Size = System::Drawing::Size(40, 40);
		this->adaptive_image->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		//Импорт изображения из БД.
		this->adaptive_image->Image = getPNGfromByte();
		this->adaptive_image->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AdaptiveRunes::adaptive_image_MouseClick);
		//
		// adaptive_descr
		// 
		this->adaptive_descr = gcnew System::Windows::Forms::TextBox();
		this->adaptive_descr->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
		this->adaptive_descr->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->adaptive_descr->ForeColor = System::Drawing::Color::DarkBlue;
		this->adaptive_descr->ReadOnly = true;
		this->adaptive_descr->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->adaptive_descr->Location = System::Drawing::Point(5, 95);
		this->adaptive_descr->Size = System::Drawing::Size(340, 300);
		this->adaptive_descr->Multiline = true;
		this->adaptive_descr->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		this->adaptive_descr->AppendText(this->AdaptiveRuneDescr);
		//
		// adaptive_name
		// 
		this->adaptive_name = gcnew System::Windows::Forms::TextBox();
		this->adaptive_name->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
		this->adaptive_name->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->adaptive_name->ForeColor = System::Drawing::Color::DarkBlue;
		this->adaptive_name->ReadOnly = true;
		this->adaptive_name->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->adaptive_name->Location = System::Drawing::Point(100, 5);
		this->adaptive_name->Size = System::Drawing::Size(200, 100);
		this->adaptive_name->AppendText(this->AdaptiveRuneName);
		//
		// all_descr_panel
		//
		this->all_descr_panel = all_descr_panel;
		this->adaptiverunes_catalog_panel = adaptiverunes_catalog_panel;
		
	}
	void SpecializedActionsForSelectingAdaptiveRunes()
	{
		this->adaptiverunes_catalog_panel->Controls->Add(this->adaptive_image);
	}
	System::Windows::Forms::PictureBox^ getAdaptivePB()
	{
		return this->adaptive_image;
	}
	System::Drawing::Image^ getPNGfromByte()
	{
		System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream(this->AdaptiveRuneImage);
		return gcnew Bitmap(ms);
	}
	System::Windows::Forms::Panel^ GetDescrPanel()
	{
		return this->all_descr_panel;
	}
	System::Windows::Forms::TextBox^ GetText()
	{
		return this->adaptive_descr;
	}
private: System::Void adaptive_image_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		this->all_descr_panel->Controls->Clear();
		System::Windows::Forms::PictureBox^ copy_image = gcnew System::Windows::Forms::PictureBox();
		copy_image->Image = this->adaptive_image->Image;
		copy_image->Location = System::Drawing::Point(5, 5);
		copy_image->BackColor = this->adaptive_image->BackColor;
		copy_image->BorderStyle = this->adaptive_image->BorderStyle;
		copy_image->Size = System::Drawing::Size(85, 85);
		copy_image->SizeMode = this->adaptive_image->SizeMode;
		this->all_descr_panel->BackColor = System::Drawing::Color::CadetBlue;
		this->all_descr_panel->Controls->Add(copy_image);
		this->all_descr_panel->Controls->Add(this->adaptive_name);
		this->all_descr_panel->Controls->Add(this->adaptive_descr);
		this->all_descr_panel->Cursor = System::Windows::Forms::Cursors::IBeam;
	}
};

