#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class RunesCatalogObjects
{
private:
	System::Windows::Forms::TextBox^ type_text{};
	System::Windows::Forms::TextBox^ type_descr{};
	System::Windows::Forms::TextBox^ text_keys_runes{};
	System::Windows::Forms::TextBox^ text_additional_runes{};
	System::Windows::Forms::TextBox^ text_adaptive_runes{};
	System::Windows::Forms::ComboBox^ types_box{};
	System::Windows::Forms::Panel^ panel_for_other_runes{};
	System::Windows::Forms::PictureBox^ type_image{};
public:
	RunesCatalogObjects(Panel^ submenu_panel)
	{
		//
		// type_text
		//
		type_text = gcnew System::Windows::Forms::TextBox{};
		this->type_text->BackColor = System::Drawing::Color::Navy;
		this->type_text->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->type_text->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->type_text->ForeColor = System::Drawing::Color::LightCyan;
		this->type_text->Location = System::Drawing::Point(27, 41);
		this->type_text->Size = System::Drawing::Size(133, 28);
		this->type_text->Text = L"ТИП РУНЫ";
		this->type_text->ReadOnly = true;
		this->type_text->Cursor = System::Windows::Forms::Cursors::Arrow;
		this->type_text->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		//
		// type_descr
		//
		this->type_descr = gcnew System::Windows::Forms::TextBox();
		this->type_descr->BackColor = System::Drawing::Color::DarkBlue;
		this->type_descr->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->type_descr->Multiline = true;
		this->type_descr->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->type_descr->ForeColor = System::Drawing::Color::WhiteSmoke;
		this->type_descr->ReadOnly = true;
		this->type_descr->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->type_descr->Location = System::Drawing::Point(465, 10);
		this->type_descr->Size = System::Drawing::Size(100, 60);
		//
		// text_keys_runes
		//
		text_keys_runes = gcnew System::Windows::Forms::TextBox{};
		this->text_keys_runes->BackColor = System::Drawing::Color::Navy;
		this->text_keys_runes->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->text_keys_runes->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->text_keys_runes->ForeColor = System::Drawing::Color::LightCyan;
		this->text_keys_runes->Location = System::Drawing::Point(30, 10);
		this->text_keys_runes->Size = System::Drawing::Size(140, 28);
		this->text_keys_runes->Text = L"Ключевые руны:";
		this->text_keys_runes->ReadOnly = true;
		this->text_keys_runes->Cursor = System::Windows::Forms::Cursors::Arrow;
		this->text_keys_runes->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		//
		// 	text_additional_runes
		//
		text_additional_runes = gcnew System::Windows::Forms::TextBox{};
		this->text_additional_runes->BackColor = System::Drawing::Color::Navy;
		this->text_additional_runes->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->text_additional_runes->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->text_additional_runes->ForeColor = System::Drawing::Color::LightCyan;
		this->text_additional_runes->Location = System::Drawing::Point(220, 10);
		this->text_additional_runes->Size = System::Drawing::Size(200, 28);
		this->text_additional_runes->Text = L"Дополнительные руны:";
		this->text_additional_runes->ReadOnly = true;
		this->text_additional_runes->Cursor = System::Windows::Forms::Cursors::Arrow;
		this->text_additional_runes->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		//
		// 	text_adaptive_runes
		//
		text_adaptive_runes = gcnew System::Windows::Forms::TextBox{};
		this->text_adaptive_runes->BackColor = System::Drawing::Color::Navy;
		this->text_adaptive_runes->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->text_adaptive_runes->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->text_adaptive_runes->ForeColor = System::Drawing::Color::LightCyan;
		this->text_adaptive_runes->Location = System::Drawing::Point(460, 10);
		this->text_adaptive_runes->Size = System::Drawing::Size(200, 28);
		this->text_adaptive_runes->Text = L"Адаптивные руны:";
		this->text_adaptive_runes->ReadOnly = true;
		this->text_adaptive_runes->Cursor = System::Windows::Forms::Cursors::Arrow;
		this->text_adaptive_runes->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		// 
		// types_box
		// 
		types_box = gcnew System::Windows::Forms::ComboBox{};
		this->types_box->BackColor = System::Drawing::Color::Navy;
		this->types_box->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->types_box->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 14, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Pixel,
			static_cast<System::Byte>(204)));
		this->types_box->ForeColor = System::Drawing::Color::LightCyan;
		this->types_box->Location = System::Drawing::Point(200, 41);
		this->types_box->MaxDropDownItems = 5;;
		this->types_box->Size = System::Drawing::Size(260, 28);
		this->types_box->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->types_box->Cursor = System::Windows::Forms::Cursors::Hand;
		//
		// panel_for_other_runes
		//
		this->panel_for_other_runes = gcnew System::Windows::Forms::Panel();
		this->panel_for_other_runes->BackColor = System::Drawing::Color::DarkSlateBlue;
		this->panel_for_other_runes->Cursor = System::Windows::Forms::Cursors::Hand;
		this->panel_for_other_runes->Location = System::Drawing::Point(6, 160);
		this->panel_for_other_runes->Size = System::Drawing::Size(685, 485);
		this->panel_for_other_runes->AutoScroll = true;
		//
		// type_image
		//
		this->type_image = gcnew System::Windows::Forms::PictureBox();
		this->type_image->BackColor = System::Drawing::Color::Transparent;
		this->type_image->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->type_image->Location = System::Drawing::Point(570, 0);
		this->type_image->Size = System::Drawing::Size(120, 120);
		this->type_image->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		submenu_panel->Controls->Add(this->type_text);
		submenu_panel->Controls->Add(this->types_box);
		submenu_panel->Controls->Add(this->type_image);
		submenu_panel->Controls->Add(this->panel_for_other_runes);
	}
	System::Windows::Forms::ComboBox^ getComboBox()
	{
		return this->types_box;
	}
	System::Windows::Forms::TextBox^ getTextBox()
	{
		return this->type_text;
	}
	System::Windows::Forms::TextBox^ getKeyText()
	{
		return this->text_keys_runes;
	}
	System::Windows::Forms::TextBox^ getAdditionalText()
	{
		return this->text_additional_runes;
	}
	System::Windows::Forms::TextBox^ getAdaptiveText()
	{
		return this->text_adaptive_runes;
	}
	System::Windows::Forms::TextBox^ getDescr()
	{
		return this->type_descr;
	}
	System::Windows::Forms::Panel^ getOtherRunesPanel()
	{
		return this->panel_for_other_runes;
	}
	System::Windows::Forms::PictureBox^ getPB()
	{
		return this->type_image;
	}
};

