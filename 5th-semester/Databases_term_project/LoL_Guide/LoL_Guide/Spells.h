#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class Spells
{
private:
	Int32^ SpellID{};
	array<Byte>^ SpellImage{};
	String^ SpellName{};
	String^ SpellDescr{};
	String^ SpellRecharge{};
	String^ SpellLIne{};
//Информационные панели.
private: System::Windows::Forms::Panel^ spells_catalog_panel{};
private: System::Windows::Forms::Panel^ spells_descr_panel{};
//Объекты панелей со свойствами данных БД.
private: System::Windows::Forms::PictureBox^ spells_image{};
private: System::Windows::Forms::TextBox^ spells_name{};
private: System::Windows::Forms::TextBox^ spells_descr{};
public:
	Spells(SqlDataReader^ reader, Panel^ spells_panel, Panel^ spells_descr_panel)
	{
		this->SpellID = reader->GetInt32(0);
		this->SpellImage = (array<Byte>^) reader->GetSqlBinary(1);
		this->SpellName = reader->GetString(2);
		this->SpellDescr = reader->GetString(3);
		this->SpellRecharge = reader->GetString(4);
		this->SpellLIne = reader->GetString(5);

		//
		// spells_image
		// 
		this->spells_image = gcnew System::Windows::Forms::PictureBox();
		this->spells_image->BackColor = System::Drawing::Color::Transparent;
		this->spells_image->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->spells_image->Size = System::Drawing::Size(80, 80);
		this->spells_image->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		//Импорт изображения из БД.
		this->spells_image->Image = getPNGfromByte();
		this->spells_image->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Spells::spell_MouseClick);
		//
		// spells_descr
		// 
		this->spells_descr = gcnew System::Windows::Forms::TextBox();
		this->spells_descr->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
		this->spells_descr->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->spells_descr->ForeColor = System::Drawing::Color::DarkBlue;
		this->spells_descr->ReadOnly = true;
		this->spells_descr->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->spells_descr->Location = System::Drawing::Point(5, 95);
		this->spells_descr->Size = System::Drawing::Size(340, 300);
		this->spells_descr->Multiline = true;
		this->spells_descr->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		this->spells_descr->AppendText("Описание: \r\n" + this->SpellDescr + "\r\n\r\n");
		this->spells_descr->AppendText("Перезарядка: \r\n" + this->SpellRecharge + "\r\n\r\n");
		this->spells_descr->AppendText("Линия: \r\n" + this->SpellLIne);
		//
		// spells_name
		// 
		this->spells_name = gcnew System::Windows::Forms::TextBox();
		this->spells_name->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
		this->spells_name->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->spells_name->ForeColor = System::Drawing::Color::DarkBlue;
		this->spells_name->ReadOnly = true;
		this->spells_name->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->spells_name->Location = System::Drawing::Point(100, 5);
		this->spells_name->Size = System::Drawing::Size(200, 100);
		this->spells_name->AppendText(this->SpellName);
		//
		// all_descr_panel
		//
		this->spells_descr_panel = spells_descr_panel;
		this->spells_catalog_panel = spells_panel;
	}
	System::Windows::Forms::Panel^ getDescrPanel()
	{
		return this->spells_descr_panel;
	}
	System::Windows::Forms::TextBox^ getTextBox()
	{
		return this->spells_descr;
	}
	void SpecializedActionsForSelectingSpells()
	{
		this->spells_catalog_panel->Controls->Add(this->spells_image);
	}
	System::Windows::Forms::PictureBox^ getSpellPB()
	{
		return this->spells_image;
	}
	System::Drawing::Image^ getPNGfromByte()
	{
		System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream(this->SpellImage);
		return gcnew Bitmap(ms);
	}
private: System::Void spell_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		this->spells_descr_panel->Controls->Clear();
		System::Windows::Forms::PictureBox^ copy_image = gcnew System::Windows::Forms::PictureBox();
		copy_image->Image = this->spells_image->Image;
		copy_image->Location = System::Drawing::Point(5, 5);
		copy_image->BackColor = this->spells_image->BackColor;
		copy_image->BorderStyle = this->spells_image->BorderStyle;
		copy_image->Size = System::Drawing::Size(85, 85);
		copy_image->SizeMode = this->spells_image->SizeMode;
		this->spells_descr_panel->BackColor = System::Drawing::Color::CadetBlue;
		this->spells_descr_panel->Controls->Add(copy_image);
		this->spells_descr_panel->Controls->Add(this->spells_name);
		this->spells_descr_panel->Controls->Add(this->spells_descr);
		this->spells_descr_panel->Cursor = System::Windows::Forms::Cursors::IBeam;
	}
};

