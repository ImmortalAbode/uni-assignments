#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class ItemsCatalogObjects
{
private:
	System::Windows::Forms::TextBox^ search_item_text{};
	System::Windows::Forms::Panel^ panel_for_objects{};
	System::Windows::Forms::Panel^ descr_panel{};

	String^ prev_text{ "Поиск..." };
	bool isEnter{ false };
public:
	ItemsCatalogObjects(Panel^ submenu_panel, Panel^ descr_panel)
	{
		//
		// panel_for_objects
		//
		this->panel_for_objects = gcnew System::Windows::Forms::Panel{};
		this->panel_for_objects->BackColor = System::Drawing::Color::DarkSlateBlue;
		this->panel_for_objects->Cursor = System::Windows::Forms::Cursors::Hand;
		this->panel_for_objects->Location = System::Drawing::Point(5, 60);
		this->panel_for_objects->Size = System::Drawing::Size(685, 580);
		this->panel_for_objects->AutoScroll = true;
		//
		// search_item_text
		//
		this->search_item_text = gcnew System::Windows::Forms::TextBox();
		this->search_item_text->BackColor = System::Drawing::SystemColors::GrayText;
		this->search_item_text->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->search_item_text->ForeColor = System::Drawing::Color::WhiteSmoke;
		this->search_item_text->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->search_item_text->Location = System::Drawing::Point(5, 10);
		this->search_item_text->Size = System::Drawing::Size(685, 50);
		this->search_item_text->Text = "Поиск...";
		this->search_item_text->Enter += gcnew System::EventHandler(this, &ItemsCatalogObjects::search_item_text_Enter);
		this->search_item_text->Leave += gcnew System::EventHandler(this, &ItemsCatalogObjects::search_item_text_Leave);
		this->search_item_text->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ItemsCatalogObjects::search_item_text_KeyDown);
		submenu_panel->Controls->Add(search_item_text);
		submenu_panel->Controls->Add(panel_for_objects);

		this->descr_panel = descr_panel;
	}
	System::Windows::Forms::Panel^ getPanelForObjects()
	{
		return this->panel_for_objects;
	}
private: System::Void search_item_text_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
private: System::Void search_item_text_Enter(System::Object^ sender, System::EventArgs^ e)
{
	isEnter = false;
	if (search_item_text->Text == "Поиск...")
	{
		this->search_item_text->Text = "";
		this->search_item_text->ForeColor = System::Drawing::Color::LightBlue;
	}
}
private: System::Void search_item_text_Leave(System::Object^ sender, System::EventArgs^ e)
{
	if (!isEnter)
	{
		this->search_item_text->Text = prev_text;
		if (prev_text == "Поиск...") 
			this->search_item_text->ForeColor = System::Drawing::Color::WhiteSmoke;
	}
	if (search_item_text->Text == "")
	{
		this->search_item_text->Text = "Поиск...";
		this->search_item_text->ForeColor = System::Drawing::Color::WhiteSmoke;
	}
}
};

