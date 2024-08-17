#pragma once

#include "AdminTableButtons.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class Admin
{
private:
	//Основные панели
	Panel^ btns_panel{};
	Panel^ descr_panel{};
	//Панель кнопок-таблиц
	Button^ heroes_table_btn{};
	Button^ heroInformation_table_btn{};
	Button^ heroTypes_table_btn{};
	Button^ typeRunes_table_btn{};
	Button^ keyRunes_table_btn{};
	Button^ additionalRunes_table_btn{};
	Button^ adaptiveRunes_table_btn{};
	Button^ items_table_btn{};
	Button^ spells_table_btn{};
	Button^ runesAssemblies_table_btn{};
	Button^ itemsAssemblies_table_btn{};
	Button^ spellsAssemblies_table_btn{};
	
	Label^ modering_label{};
public:
	Admin(Panel^ btns_panel, Panel^ descr_panel)
	{
		descr_panel->Controls->Clear();
		//
		// btns_panel
		//
		btns_panel->Size = System::Drawing::Size(250, 653);
		btns_panel->BackColor = System::Drawing::Color::White;
		btns_panel->Visible = true;
		this->btns_panel = btns_panel;
		//
		// descr_panel
		//
		descr_panel->Location = System::Drawing::Point(250, 0);
		descr_panel->Size = System::Drawing::Size(900, 653);
		descr_panel->BackColor = System::Drawing::SystemColors::InactiveCaption;
		this->descr_panel = descr_panel;
		//
		// Кнопки таблиц на панели btns_panel
		//
		AdminTableButtons^ heroes_table_btn = gcnew AdminTableButtons(40, 10, "Герои", descr_panel);
		this->heroes_table_btn = heroes_table_btn->getTableBTN();
		this->btns_panel->Controls->Add(this->heroes_table_btn);

		AdminTableButtons^ heroInformation_table_btn = gcnew AdminTableButtons(40, 60, "Информация о героях", descr_panel);
		this->heroInformation_table_btn = heroInformation_table_btn->getTableBTN();
		this->btns_panel->Controls->Add(this->heroInformation_table_btn);

		AdminTableButtons^ heroTypes_table_btn = gcnew AdminTableButtons(40, 110, "Типы героев", descr_panel);
		this->heroTypes_table_btn = heroTypes_table_btn->getTableBTN();
		this->btns_panel->Controls->Add(this->heroTypes_table_btn);

		AdminTableButtons^ typeRunes_table_btn = gcnew AdminTableButtons(40, 160, "Типы рун", descr_panel);
		this->typeRunes_table_btn = typeRunes_table_btn->getTableBTN();
		this->btns_panel->Controls->Add(this->typeRunes_table_btn);

		AdminTableButtons^ keyRunes_table_btn = gcnew AdminTableButtons(40, 210, "Ключевые руны", descr_panel);
		this->keyRunes_table_btn = keyRunes_table_btn->getTableBTN();
		this->btns_panel->Controls->Add(this->keyRunes_table_btn);

		AdminTableButtons^ additionalRunes_table_btn = gcnew AdminTableButtons(40, 260, "Дополнительные руны", descr_panel);
		this->additionalRunes_table_btn = additionalRunes_table_btn->getTableBTN();
		this->btns_panel->Controls->Add(this->additionalRunes_table_btn);

		AdminTableButtons^ adaptiveRunes_table_btn = gcnew AdminTableButtons(40, 310, "Адаптивные руны", descr_panel);
		this->adaptiveRunes_table_btn = adaptiveRunes_table_btn->getTableBTN();
		this->btns_panel->Controls->Add(this->adaptiveRunes_table_btn);

		AdminTableButtons^ items_table_btn = gcnew AdminTableButtons(40, 360, "Предметы", descr_panel);
		this->items_table_btn = items_table_btn->getTableBTN();
		this->btns_panel->Controls->Add(this->items_table_btn);

		AdminTableButtons^ spells_table_btn = gcnew AdminTableButtons(40, 410, "Заклинания", descr_panel);
		this->spells_table_btn = spells_table_btn->getTableBTN();
		this->btns_panel->Controls->Add(this->spells_table_btn);

		AdminTableButtons^ runesAssemblies_table_btn = gcnew AdminTableButtons(40, 460, "Сборки рун", descr_panel);
		this->runesAssemblies_table_btn = runesAssemblies_table_btn->getTableBTN();
		this->btns_panel->Controls->Add(this->runesAssemblies_table_btn);

		AdminTableButtons^ itemsAssemblies_table_btn = gcnew AdminTableButtons(40, 510, "Сборки предметов", descr_panel);
		this->itemsAssemblies_table_btn = itemsAssemblies_table_btn->getTableBTN();
		this->btns_panel->Controls->Add(this->itemsAssemblies_table_btn);

		AdminTableButtons^ spellsAssemblies_table_btn = gcnew AdminTableButtons(40, 560, "Сборки заклинаний", descr_panel);
		this->spellsAssemblies_table_btn = spellsAssemblies_table_btn->getTableBTN();
		this->btns_panel->Controls->Add(this->spellsAssemblies_table_btn);
		//
		// modering_label
		//
		this->modering_label = gcnew Label();
		this->modering_label->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
		this->modering_label->BackColor = System::Drawing::Color::Transparent;
		this->modering_label->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->modering_label->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->modering_label->ForeColor = System::Drawing::Color::Khaki;
		this->modering_label->Location = System::Drawing::Point(5, 610);
		this->modering_label->Size = System::Drawing::Size(240, 60);
		this->modering_label->Text = L"Сейчас вы администрируете базу данных по LoL_Guide";
		this->btns_panel->Controls->Add(this->modering_label);
	}
};

