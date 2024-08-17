#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class Items
{
private:
	Int32^ ItemID{};
	array<Byte>^ ItemImage{};
	String^ ItemDescr{};
	String^ ActiveCharacteristics{};
	String^ PassiveCharacteristics{};
	String^ GameStage{};
	Int32^ ItemType{};
	Int32^ ItemCost{};
	String^ ItemName{};
private: System::Windows::Forms::Panel^ item_descr_panel{};
private: System::Windows::Forms::TextBox^ item_preview{};
private: System::Windows::Forms::TextBox^ item_information{};
private: System::Windows::Forms::PictureBox^ image_of_item{};
public:
	Items(SqlDataReader^ reader, Panel^ item_descr_panel)
	{
		ItemID = reader->GetInt32(0);
		ItemImage = (array<Byte>^)reader->GetSqlBinary(1);
		ItemDescr = reader->GetString(2);
		ActiveCharacteristics = reader->IsDBNull(3) ? "-" : reader->GetString(3);
		PassiveCharacteristics = reader->IsDBNull(4) ? "-" : reader->GetString(4);
		GameStage = reader->IsDBNull(5) ? "-" : reader->GetString(5);
		ItemType = reader->GetInt32(6);
		ItemCost = reader->GetInt32(7);
		ItemName = reader->GetString(8);
		//
		// item_picture
		//
		this->image_of_item = gcnew System::Windows::Forms::PictureBox();
		this->image_of_item->BackColor = System::Drawing::Color::Transparent;
		this->image_of_item->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->image_of_item->Size = System::Drawing::Size(60, 60);
		this->image_of_item->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		//Импорт изображения из БД.
		this->image_of_item->Image = this->getPNGfromByte();
		this->image_of_item->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Items::image_of_item_btn_MouseClick);
		//
		// item_preview
		//
		this->item_preview = gcnew System::Windows::Forms::TextBox();
		this->item_preview->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
		this->item_preview->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->item_preview->ForeColor = System::Drawing::Color::DarkBlue;
		this->item_preview->ReadOnly = true;
		this->item_preview->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->item_preview->Location = System::Drawing::Point(70, 10);
		this->item_preview->Size = System::Drawing::Size(130, 40);
		this->item_preview->Multiline = true;

		this->item_preview->AppendText(this->ItemName + "\r\n");
		this->item_preview->AppendText("Цена в монетах: " + this->ItemCost->ToString());
		//
		// item_information
		//
		this->item_information = gcnew System::Windows::Forms::TextBox();
		this->item_information->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
		this->item_information->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->item_information->ForeColor = System::Drawing::Color::DarkBlue;
		this->item_information->ReadOnly = true;
		this->item_information->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->item_information->Location = System::Drawing::Point(5, 70);
		this->item_information->Size = System::Drawing::Size(330, 330);
		this->item_information->Multiline = true;
		this->item_information->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;

		this->item_information->AppendText("Описание:\r\n" + this->ItemDescr + "\r\n\r\n");
		this->item_information->AppendText("Активные характеристики:\r\n" + this->ActiveCharacteristics + "\r\n\r\n");
		this->item_information->AppendText("Пассивные характеристики:\r\n" + this->PassiveCharacteristics + "\r\n\r\n");
		this->item_information->AppendText("Наиболее подходящая стадия игры: " + this->GameStage + "\r\n");
		this->getTypeHero();

		this->item_descr_panel = item_descr_panel;
	}
	System::Windows::Forms::PictureBox^ getItemPB()
	{
		return this->image_of_item;
	}
	System::Windows::Forms::Panel^ getDescrPanel()
	{
		return this->item_descr_panel;
	}
	System::Drawing::Image^ getPNGfromByte()
	{
		System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream(this->ItemImage);
		return gcnew Bitmap(ms);
	}
	void getTypeHero();
	TextBox^ getItemInformation()
	{
		return this->item_information;
	}
private: System::Void image_of_item_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	this->item_descr_panel->Controls->Clear();
	System::Windows::Forms::PictureBox^ copy_image = gcnew System::Windows::Forms::PictureBox();
	copy_image->Image = this->image_of_item->Image;
	copy_image->Location = System::Drawing::Point(5, 5);
	copy_image->BackColor = this->image_of_item->BackColor;
	copy_image->BorderStyle = this->image_of_item->BorderStyle;
	copy_image->Size = this->image_of_item->Size;
	copy_image->SizeMode = this->image_of_item->SizeMode;
	this->item_descr_panel->BackColor = System::Drawing::Color::CadetBlue;
	this->item_descr_panel->Controls->Add(copy_image);
	this->item_descr_panel->Controls->Add(this->item_preview);
	this->item_descr_panel->Controls->Add(this->item_information);
	this->item_descr_panel->Cursor = System::Windows::Forms::Cursors::IBeam;
	this->item_preview->Focus();
}
};

