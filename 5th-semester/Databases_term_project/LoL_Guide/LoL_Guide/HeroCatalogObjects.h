#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class HeroCatalogObjects
{
private:
	System::Windows::Forms::Panel^ panel_for_groups{};
	System::Windows::Forms::Panel^ panel_for_descr{};
	System::Windows::Forms::TextBox^ search_hero_TB{};

	String^ prev_text{ "Поиск..." };
	bool isEnter{ false };
public:
	HeroCatalogObjects(Panel^ submenu_panel, Panel^ panel_for_descr)
	{
		this->panel_for_descr = panel_for_descr;
		//
		// search_hero_TB
		//
		this->search_hero_TB = gcnew System::Windows::Forms::TextBox();
		this->search_hero_TB->BackColor = System::Drawing::SystemColors::GrayText;
		this->search_hero_TB->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->search_hero_TB->ForeColor = System::Drawing::Color::WhiteSmoke;
		this->search_hero_TB->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->search_hero_TB->Location = System::Drawing::Point(5, 10);
		this->search_hero_TB->Size = System::Drawing::Size(680, 50);
		this->search_hero_TB->Text = "Поиск...";
		this->search_hero_TB->Enter += gcnew System::EventHandler(this, &HeroCatalogObjects::search_hero_TB_Enter);
		this->search_hero_TB->Leave += gcnew System::EventHandler(this, &HeroCatalogObjects::search_hero_TB_Leave);
		this->search_hero_TB->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &HeroCatalogObjects::search_hero_TB_KeyDown);
		
		submenu_panel->Controls->Add(search_hero_TB);

		//
		// panel_for_groups
		//
		this->panel_for_groups = gcnew System::Windows::Forms::Panel{};
		this->panel_for_groups->BackColor = System::Drawing::Color::DarkSlateBlue;
		this->panel_for_groups->Cursor = System::Windows::Forms::Cursors::Hand;
		this->panel_for_groups->Location = System::Drawing::Point(0, 50);
		this->panel_for_groups->Size = System::Drawing::Size(700, 600);
		this->panel_for_groups->AutoScroll = true;

		submenu_panel->Controls->Add(this->panel_for_groups);
	}
	Panel^ getGroupsCatalogPanel()
	{
		return this->panel_for_groups;
	}
private: System::Void search_hero_TB_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
private: System::Void search_hero_TB_Enter(System::Object^ sender, System::EventArgs^ e)
{
	isEnter = false;
	if (search_hero_TB->Text == "Поиск...")
	{
		this->search_hero_TB->Text = "";
		this->search_hero_TB->ForeColor = System::Drawing::Color::LightBlue;
	}
}
private: System::Void search_hero_TB_Leave(System::Object^ sender, System::EventArgs^ e)
{
	if (!isEnter)
	{
		this->search_hero_TB->Text = prev_text;
		if (prev_text == "Поиск...")
			this->search_hero_TB->ForeColor = System::Drawing::Color::WhiteSmoke;
	}
	if (search_hero_TB->Text == "")
	{
		this->search_hero_TB->Text = "Поиск...";
		this->search_hero_TB->ForeColor = System::Drawing::Color::WhiteSmoke;
	}
}
};

