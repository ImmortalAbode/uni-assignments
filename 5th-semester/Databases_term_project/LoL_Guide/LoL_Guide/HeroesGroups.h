#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class HeroesGroups
{
private:
	TextBox^ group_hero_name{};
	Panel^ group_hero_panel{};
public:
	HeroesGroups(Int32 dx_point_GHN, Int32 dy_point_GHN, String^ group_name, Int32 dx_point_GHP, Int32 dy_point_GHP)
	{
		//
		// group_hero_panel
		//
		this->group_hero_panel = gcnew System::Windows::Forms::Panel();
		this->group_hero_panel->BackColor = System::Drawing::Color::LightBlue;
		this->group_hero_panel->Cursor = System::Windows::Forms::Cursors::Hand;
		this->group_hero_panel->Location = System::Drawing::Point(dx_point_GHP, dy_point_GHP);
		this->group_hero_panel->Size = System::Drawing::Size(680, 120);
		this->group_hero_panel->AutoScroll = true;
		//
		// group_hero_name
		//
		this->group_hero_name = gcnew System::Windows::Forms::TextBox{};
		this->group_hero_name->BackColor = System::Drawing::Color::DarkBlue;
		this->group_hero_name->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->group_hero_name->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->group_hero_name->ForeColor = System::Drawing::Color::LightBlue;
		this->group_hero_name->Location = System::Drawing::Point(dx_point_GHN, dy_point_GHN);
		this->group_hero_name->Size = System::Drawing::Size(150, 30);
		this->group_hero_name->Text = group_name->ToUpper();
		this->group_hero_name->ReadOnly = true;
		this->group_hero_name->Cursor = System::Windows::Forms::Cursors::Arrow;
		this->group_hero_name->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
	}
	TextBox^ get_GHN()
	{
		return this->group_hero_name;
	}
	Panel^ get_GHP()
	{
		return this->group_hero_panel;
	}
};

