#pragma once

#include "HeroCatalogObjects.h"
#include "HeroInformation.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class Heroes
{
private:
	Int32^ HeroID{};
	String^ HeroName{};
	array<Byte>^ HeroImage{};
	String^ HeroHistory{};
	String^ HeroSKillsDescr{};
	Int32^ HeroType{};
private:
	System::Windows::Forms::PictureBox^ hero_image{};
	System::Windows::Forms::TextBox^ hero_name{};
	System::Windows::Forms::TextBox^ hero_type{};
	System::Windows::Forms::TextBox^ hero_descr{};
	System::Windows::Forms::Panel^ hero_descr_panel{};
	System::Windows::Forms::Panel^ hero_information_panel{};
	System::Windows::Forms::Button^ hero_inf_btn{};
	System::Windows::Forms::Button^ hero_runes_assembl_btn{};
	System::Windows::Forms::Button^ hero_items_assembl_btn{};
	System::Windows::Forms::Button^ hero_spells_assembl_btn{};
	System::Windows::Forms::Panel^ more_inf_about_obj_panel{};
	HeroInformation^ information{};
public:
	Heroes(SqlDataReader^ reader, Panel^ hero_descr_panel)
	{
		this->HeroID = reader->GetInt32(0);
		this->HeroName = reader->GetString(1);
		this->HeroImage = (array<Byte>^)reader->GetSqlBinary(2);
		this->HeroHistory = reader->GetString(3);
		this->HeroSKillsDescr = reader->GetString(4);
		this->HeroType = reader->GetInt32(5);
		//
		// hero_image
		// 
		this->hero_image = gcnew System::Windows::Forms::PictureBox();
		this->hero_image->BackColor = System::Drawing::Color::Transparent;
		this->hero_image->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->hero_image->Size = System::Drawing::Size(85, 90);
		this->hero_image->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		//Импорт изображения из БД.
		this->hero_image->Image = getPNGfromByte();
		this->hero_image->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Heroes::hero_image_MouseClick);
		//
		// hero_descr
		// 
		this->hero_descr = gcnew System::Windows::Forms::TextBox();
		this->hero_descr->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
		this->hero_descr->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->hero_descr->ForeColor = System::Drawing::Color::DarkBlue;
		this->hero_descr->ReadOnly = true;
		this->hero_descr->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->hero_descr->Location = System::Drawing::Point(5, 95);
		this->hero_descr->Size = System::Drawing::Size(330, 300);
		this->hero_descr->Multiline = true;
		this->hero_descr->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		this->hero_descr->AppendText(this->HeroSKillsDescr);
		//
		// hero_name
		// 
		this->hero_name = gcnew System::Windows::Forms::TextBox();
		this->hero_name->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
		this->hero_name->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->hero_name->ForeColor = System::Drawing::Color::DarkBlue;
		this->hero_name->ReadOnly = true;
		this->hero_name->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->hero_name->Location = System::Drawing::Point(100, 5);
		this->hero_name->Size = System::Drawing::Size(100, 30);
		this->hero_name->AppendText(this->HeroName);
		//
		// hero_descr_panel
		//
		this->hero_descr_panel = hero_descr_panel;
		//
		// more_inf_about_obj_panel
		//
		this->more_inf_about_obj_panel = gcnew System::Windows::Forms::Panel{};
		this->more_inf_about_obj_panel->AutoScroll = true;
		//
		// hero_information_panel
		//
		this->hero_information_panel = gcnew System::Windows::Forms::Panel{};
		this->hero_information_panel->BackColor = System::Drawing::Color::CadetBlue;
		this->hero_information_panel->Cursor = System::Windows::Forms::Cursors::Hand;
		this->hero_information_panel->Location = System::Drawing::Point(340, 10);
		this->hero_information_panel->Size = System::Drawing::Size(250, 385);
		this->hero_information_panel->AutoScroll = false;
		//
		// hero_inf_btn
		//
		this->hero_inf_btn = gcnew System::Windows::Forms::Button{};
		this->hero_inf_btn->BackColor = System::Drawing::Color::ForestGreen;
		this->hero_inf_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->hero_inf_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Red;
		this->hero_inf_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
		this->hero_inf_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->hero_inf_btn->ForeColor = System::Drawing::Color::Yellow;
		this->hero_inf_btn->Location = System::Drawing::Point(340, 400);
		this->hero_inf_btn->Size = System::Drawing::Size(120, 45);
		this->hero_inf_btn->Text = L"Информация";
		this->hero_inf_btn->UseVisualStyleBackColor = false;
		this->hero_inf_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Heroes::hero_inf_btn_MouseClick);
		//
		// hero_runes_assembl_btn
		//
		this->hero_runes_assembl_btn = gcnew System::Windows::Forms::Button{};
		this->hero_runes_assembl_btn->BackColor = System::Drawing::Color::ForestGreen;
		this->hero_runes_assembl_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->hero_runes_assembl_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Red;
		this->hero_runes_assembl_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
		this->hero_runes_assembl_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->hero_runes_assembl_btn->ForeColor = System::Drawing::Color::Yellow;
		this->hero_runes_assembl_btn->Location = System::Drawing::Point(340, 450);
		this->hero_runes_assembl_btn->Size = System::Drawing::Size(120, 45);
		this->hero_runes_assembl_btn->Text = L"Сборки рун";
		this->hero_runes_assembl_btn->UseVisualStyleBackColor = false;
		this->hero_runes_assembl_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Heroes::hero_runes_assembl_btn_MouseClick);
		//
		// hero_items_assembl_btn
		//
		this->hero_items_assembl_btn = gcnew System::Windows::Forms::Button{};
		this->hero_items_assembl_btn->BackColor = System::Drawing::Color::ForestGreen;
		this->hero_items_assembl_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->hero_items_assembl_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Red;
		this->hero_items_assembl_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
		this->hero_items_assembl_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->hero_items_assembl_btn->ForeColor = System::Drawing::Color::Yellow;
		this->hero_items_assembl_btn->Location = System::Drawing::Point(470, 400);
		this->hero_items_assembl_btn->Size = System::Drawing::Size(120, 45);
		this->hero_items_assembl_btn->Text = L"Сборки предметов";
		this->hero_items_assembl_btn->UseVisualStyleBackColor = false;
		this->hero_items_assembl_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Heroes::hero_items_assembl_btn_MouseClick);
		//
		// hero_spells_assembl_btn
		//
		this->hero_spells_assembl_btn = gcnew System::Windows::Forms::Button{};
		this->hero_spells_assembl_btn->BackColor = System::Drawing::Color::ForestGreen;
		this->hero_spells_assembl_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->hero_spells_assembl_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Red;
		this->hero_spells_assembl_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
		this->hero_spells_assembl_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->hero_spells_assembl_btn->ForeColor = System::Drawing::Color::Yellow;
		this->hero_spells_assembl_btn->Location = System::Drawing::Point(470, 450);
		this->hero_spells_assembl_btn->Size = System::Drawing::Size(120, 45);
		this->hero_spells_assembl_btn->Text = L"Сборки заклинаний";
		this->hero_spells_assembl_btn->UseVisualStyleBackColor = false;
		this->hero_spells_assembl_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Heroes::hero_spells_assembl_btn_MouseClick);
	}
	Int32^ getHeroType()
	{
		return this->HeroType;
	}
	System::Windows::Forms::PictureBox^ getHeroPB()
	{
		return this->hero_image;
	}
	System::Drawing::Image^ getPNGfromByte()
	{
		System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream(this->HeroImage);
		return gcnew Bitmap(ms);
	}
	System::Windows::Forms::TextBox^ getTypeText()
	{
		return this->hero_type;
	}
private: System::Void hero_image_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		this->hero_descr_panel->Controls->Clear();
		this->hero_information_panel->Controls->Clear();
		this->more_inf_about_obj_panel->Controls->Clear();
		this->more_inf_about_obj_panel->BackColor = System::Drawing::Color::Transparent;
		System::Windows::Forms::PictureBox^ copy_image = gcnew System::Windows::Forms::PictureBox();
		copy_image->Image = this->hero_image->Image;
		copy_image->Location = System::Drawing::Point(5, 5);
		copy_image->BackColor = this->hero_image->BackColor;
		copy_image->BorderStyle = this->hero_image->BorderStyle;
		copy_image->Size = System::Drawing::Size(85, 85);
		copy_image->SizeMode = this->hero_image->SizeMode;
		this->hero_descr_panel->BackColor = System::Drawing::Color::DarkSlateGray;
		this->hero_descr_panel->Controls->Add(copy_image);
		this->hero_descr_panel->Controls->Add(this->hero_name);
		this->hero_descr_panel->Controls->Add(this->hero_type);
		this->hero_descr_panel->Controls->Add(this->hero_descr);
		this->hero_descr_panel->Cursor = System::Windows::Forms::Cursors::IBeam;
		this->hero_descr_panel->Location = System::Drawing::Point(710, 0);
		this->hero_descr_panel->Size = System::Drawing::Size(600, 560);
		this->hero_descr_panel->Controls->Add(this->hero_information_panel);
		this->hero_descr_panel->Controls->Add(this->hero_inf_btn);
		this->hero_descr_panel->Controls->Add(this->hero_runes_assembl_btn);
		this->hero_descr_panel->Controls->Add(this->hero_items_assembl_btn);
		this->hero_descr_panel->Controls->Add(this->hero_spells_assembl_btn);
		this->hero_descr_panel->Controls->Add(this->more_inf_about_obj_panel);
		this->hero_name->Focus();
	}
private: System::Void hero_inf_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
private: System::Void hero_runes_assembl_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
private: System::Void hero_items_assembl_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
private: System::Void hero_spells_assembl_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
};

