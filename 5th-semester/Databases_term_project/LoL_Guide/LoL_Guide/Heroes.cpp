#include "Heroes.h"
#include "HeroInformation.h"
#include "DataBaseFunctions.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

System::Void Heroes::hero_inf_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	this->hero_information_panel->Controls->Clear();
	this->hero_descr_panel->Controls->Remove(this->more_inf_about_obj_panel);
	//
	// more_inf_about_obj_panel
	//
	this->more_inf_about_obj_panel = gcnew System::Windows::Forms::Panel{};
	this->more_inf_about_obj_panel->AutoScroll = true;
	this->more_inf_about_obj_panel->BackColor = System::Drawing::Color::Transparent;

	DataBaseFunctions^ funcs = gcnew DataBaseFunctions{};
	funcs->SelectInformationHero(this->hero_information_panel, this->HeroID);
}
System::Void Heroes::hero_runes_assembl_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	this->hero_information_panel->Controls->Clear();
	this->hero_descr_panel->Controls->Remove(this->more_inf_about_obj_panel);
	//
	// more_inf_about_obj_panel
	//
	this->more_inf_about_obj_panel = gcnew System::Windows::Forms::Panel{};
	this->more_inf_about_obj_panel->AutoScroll = true;
	this->more_inf_about_obj_panel->BackColor = System::Drawing::Color::Transparent;

	DataBaseFunctions^ funcs = gcnew DataBaseFunctions{};
	funcs->SelectRuneAssembl(this->hero_descr_panel, this->hero_information_panel, this->HeroID, this->more_inf_about_obj_panel);
	this->hero_descr_panel->Controls->Add(this->more_inf_about_obj_panel);
}
System::Void Heroes::hero_items_assembl_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	this->hero_information_panel->Controls->Clear();
	this->hero_descr_panel->Controls->Remove(this->more_inf_about_obj_panel);
	//
	// more_inf_about_obj_panel
	//
	this->more_inf_about_obj_panel = gcnew System::Windows::Forms::Panel{};
	this->more_inf_about_obj_panel->AutoScroll = true;
	this->more_inf_about_obj_panel->BackColor = System::Drawing::Color::Transparent;

	DataBaseFunctions^ funcs = gcnew DataBaseFunctions{};
	funcs->SelectItemAssembl(this->hero_descr_panel, this->hero_information_panel, this->HeroID, this->more_inf_about_obj_panel);
	this->hero_descr_panel->Controls->Add(this->more_inf_about_obj_panel);
}
System::Void Heroes::hero_spells_assembl_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	this->hero_information_panel->Controls->Clear();
	this->hero_descr_panel->Controls->Remove(this->more_inf_about_obj_panel);
	//
	// more_inf_about_obj_panel
	//
	this->more_inf_about_obj_panel = gcnew System::Windows::Forms::Panel{};
	this->more_inf_about_obj_panel->AutoScroll = true;
	this->more_inf_about_obj_panel->BackColor = System::Drawing::Color::Transparent;

	DataBaseFunctions^ funcs = gcnew DataBaseFunctions{};
	funcs->SelectSpellAssembl(this->hero_descr_panel, this->hero_information_panel, this->HeroID, this->more_inf_about_obj_panel);
	this->hero_descr_panel->Controls->Add(this->more_inf_about_obj_panel);
}