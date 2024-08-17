#pragma once

#include "RunesCatalogObjects.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class TypeRunes
{
//Данные БД.
private:
	Int32^ TypeRuneID{};
	array<Byte>^ TypeRuneImage{};
	String^ TypeRuneDescr{};
	String^ TypeRuneName{};
private: System::Windows::Forms::PictureBox^ type_rune_PB{};
//Информационные панели.
private: System::Windows::Forms::Panel^ all_descr_panel{};
private: System::Windows::Forms::Panel^ runes_catalog_panel{};
//Объекты панелей со свойствами данных БД.
private: System::Windows::Forms::ComboBox^ types_box{};
private: RunesCatalogObjects^ obj{};
public:
	TypeRunes(SqlDataReader^ reader, Panel^ runes_catalog_panel, Panel^ all_descr_panel)
	{
		this->TypeRuneID = reader->GetInt32(0);
		this->TypeRuneImage = (array<Byte>^)reader->GetSqlBinary(1);
		this->TypeRuneDescr = reader->GetString(2);
		this->TypeRuneName = reader->GetString(3);
		//
		// type_rune_PB
		// 
		this->type_rune_PB = gcnew System::Windows::Forms::PictureBox();
		this->type_rune_PB->BackColor = System::Drawing::Color::Transparent;
		this->type_rune_PB->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->type_rune_PB->Size = System::Drawing::Size(50, 50);
		this->type_rune_PB->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
		//Импорт изображения из БД.
		this->type_rune_PB->Image = getPNGfromByte();
		//
		// Панели
		//
		this->all_descr_panel = all_descr_panel;
		this->all_descr_panel->Location = System::Drawing::Point(710, 0);
		this->all_descr_panel->Size = System::Drawing::Size(350, 410);
		this->runes_catalog_panel = runes_catalog_panel;
	}
	void SpecializedActionsForSelectingTypeRunes(RunesCatalogObjects^ obj)
	{
		this->runes_catalog_panel->Cursor = System::Windows::Forms::Cursors::Arrow;
		//
		// types_box_copy
		//
		this->obj = obj;
		this->types_box = this->obj->getComboBox();
		this->types_box->SelectedIndexChanged += gcnew System::EventHandler(this, &TypeRunes::types_box_SelectedIndexChanged);
		this->obj->getComboBox()->Items->Add(this->TypeRuneName);
	}
	System::Drawing::Image^ getPNGfromByte()
	{
		System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream(this->TypeRuneImage);
		return gcnew Bitmap(ms);
	}
	System::Windows::Forms::PictureBox^ getTypeRuneImage()
	{
		return this->type_rune_PB;
	}
	Int32^ getTypeRune()
	{
		return this->TypeRuneID;
	}
private: System::Void types_box_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
};

