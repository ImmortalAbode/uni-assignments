#pragma once
#include <iostream>

#include "ItemsCatalogObjects.h"
#include "Items.h" 
#include "TypeRunes.h"
#include "KeyRunes.h"
#include "RunesCatalogObjects.h"
#include "AdditionalRunes.h"
#include "AdaptiveRunes.h"
#include "Spells.h"
#include "HeroCatalogObjects.h"
#include "Heroes.h"
#include "HeroInformation.h"
#include "RunesAssemblies.h"
#include "ItemsAssemblies.h"
#include "SpellsAssemblies.h"
#include "Admin.h"
#include "EntryAdmin.h"
#include "HeroesGroups.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class DataBaseFunctions
{

public:
	//Свойства.
	SqlConnection^ conn;
	SqlConnectionStringBuilder^ connStringBuilder;

	//Подключение к БД.
	void ConnectToDB()
	{
		//Data Source=DESKTOP-LIFJDVL;Initial Catalog=League_of_LegendsDB;Integrated Security=True
		this->connStringBuilder = gcnew SqlConnectionStringBuilder();
		this->connStringBuilder->DataSource = "DESKTOP-LIFJDVL";
		this->connStringBuilder->InitialCatalog = "League_of_LegendsDB";
		this->connStringBuilder->IntegratedSecurity = true;

		this->conn = gcnew SqlConnection(Convert::ToString(this->connStringBuilder));
	}
	void OpenConnection()
	{
		ConnectToDB();
		this->conn->Open();
	}
	void CloseConnection()
	{
		if (this->conn != nullptr)
			this->conn->Close();
	}
	SqlDataReader^ getReader(String^ query)
	{
		SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
		SqlDataReader^ reader = SQL_command->ExecuteReader();
		return reader;
	}
	//Запросы к БД.
	String^ getHeroType(Int32^ ID)
	{
		try
		{
			this->OpenConnection();
			String^ query = "SELECT * FROM dbo.HeroTypes WHERE TypeID = " + ID;
			SqlDataReader^ reader = getReader(query);
			while (reader->Read())
				return reader->GetString(1);
			return "-";
		}
		finally
		{
			this->CloseConnection();
		}
	}
	void SelectItems(Panel^ submenu_panel, Panel^ panel_for_descr)
	{
		try
		{
			this->OpenConnection();
			String^ query = "SELECT * FROM dbo.Items";
			SqlDataReader^ reader = getReader(query);
			ItemsCatalogObjects^ obj = gcnew ItemsCatalogObjects(submenu_panel, panel_for_descr);
			Int32 dx{ 5 }, dy{ 5 };
			while (reader->Read())
			{
				Items^ cur_PB = gcnew Items(reader, panel_for_descr);
				cur_PB->getDescrPanel()->Location = System::Drawing::Point(710, 0);
				cur_PB->getDescrPanel()->Size = System::Drawing::Size(350, 410);
				cur_PB->getItemPB()->Location = System::Drawing::Point(dx, dy);
				obj->getPanelForObjects()->Controls->Add(cur_PB->getItemPB());
				if (dx > 600) { dy += 65; dx = 5; }
				else { dx += 60; }
			}
		}
		finally { this->CloseConnection(); }
	}
	void SelectTypeRunes(Panel^ submenu_panel, Panel^ panel_for_descr)
	{
		try
		{
			OpenConnection();
			String^ query = "SELECT * FROM dbo.TypeRunes";
			SqlDataReader^ reader = getReader(query);
			RunesCatalogObjects^ obj = gcnew RunesCatalogObjects(submenu_panel);
			while (reader->Read())
			{
				TypeRunes^ cur_type = gcnew TypeRunes(reader, submenu_panel, panel_for_descr);
				cur_type->SpecializedActionsForSelectingTypeRunes(obj);
			}
		}
		finally
		{
			CloseConnection();
		}
	}
	void SelectKeyRunes(Panel^ submenu_panel, Panel^ panel_for_descr, Int32^ type_rune_ID)
	{
		try
		{
			this->OpenConnection();
			String^ query = "SELECT * FROM dbo.KeyRunes WHERE TypeRuneID = " + type_rune_ID;
			SqlDataReader^ reader = getReader(query);
			Int32 dx{ -40 }, dy{ 60 }, count{};
			Boolean flag{ false };
			while (reader->Read())
			{
				KeyRunes^ cur_key = gcnew KeyRunes(reader, submenu_panel, panel_for_descr);
				cur_key->SpecializedActionsForSelectingKeyRunes();
				if (count < 3)
					dx += 60;
				else
				{
					dy += 50;
					dx = 20;
					count = 0;
				}
				count++;
				cur_key->getKeyPB()->Location = System::Drawing::Point(dx, dy);
			}
		}
		finally { this->CloseConnection(); }
	}
	void SelectAdditionalRunes(Panel^ submenu_panel, Panel^ panel_for_descr, Int32^ type_rune_ID)
	{
		try
		{
			this->OpenConnection();
			String^ query = "SELECT * FROM dbo.AdditionalRunes WHERE TypeRuneID = " + type_rune_ID;
			SqlDataReader^ reader = getReader(query);
			Int32 dx{ 200 }, dy{ 60 }, count{};
			while (reader->Read())
			{
				AdditionalRunes^ cur_additional = gcnew AdditionalRunes(reader, submenu_panel, panel_for_descr);
				cur_additional->SpecializedActionsForSelectingAdditionalRunes();
				if (count < 3)
					dx += 50;
				else 
				{
					dy += 50;
					dx = 250;
					count = 0;
				}
				count++;
				cur_additional->getAdditionalPB()->Location = System::Drawing::Point(dx, dy);
			}
		}
		finally { this->CloseConnection(); }
	}
	void SelectAdaptiveRunes(Panel^ submenu_panel, Panel^ panel_for_descr)
	{
		try
		{
			this->OpenConnection();
			String^ query = "SELECT * FROM dbo.AdaptiveRunes";
			SqlDataReader^ reader = getReader(query);
			Int32 dx{ 440 }, dy{ 60 }, count{};
			while (reader->Read())
			{
				AdaptiveRunes^ cur_adaptive = gcnew AdaptiveRunes(reader, submenu_panel, panel_for_descr);
				cur_adaptive->SpecializedActionsForSelectingAdaptiveRunes();
				if (count < 3)
					dx += 50;
				else
				{
					dy += 50;
					dx = 490;
					count = 0;
				}
				count++;
				cur_adaptive->getAdaptivePB()->Location = System::Drawing::Point(dx, dy);
			}
		}
		finally { this->CloseConnection(); }
	}
	void SelectSpells(Panel^ submenu_panel, Panel^ panel_for_descr)
	{
		try
		{
			this->OpenConnection();
			String^ query = "SELECT * FROM dbo.Spells";
			SqlDataReader^ reader = getReader(query);
			Int32 dx{}, dy{};
			while (reader->Read())
			{
				Spells^ cur_spell = gcnew Spells(reader, submenu_panel, panel_for_descr);
				cur_spell->getSpellPB()->Location = System::Drawing::Point(dx, dy);
				cur_spell->getDescrPanel()->Location = System::Drawing::Point(710, 0);
				cur_spell->getDescrPanel()->Size = System::Drawing::Size(350, 410);
				cur_spell->SpecializedActionsForSelectingSpells();
				if (dx > 1000) { dy += 70; dx = 0; }
				else { dx += 90; }
			}
		}
		finally { this->CloseConnection(); }
	}
	void SelectHeroes(Panel^ submenu_panel, Panel^ panel_for_descr)
	{
		try
		{
			HeroCatalogObjects^ obj = gcnew HeroCatalogObjects(submenu_panel, panel_for_descr);
			this->OpenConnection();
			String^ query_1 = "SELECT * FROM dbo.HeroTypes";
			SqlDataReader^ reader_1 = getReader(query_1);
			Int32 dx_GHN{ 280 }, dy_GHN{ 10 }, dx_GHP{}, dy_GHP{ 50 };
			while (reader_1->Read())
			{
				HeroesGroups^ cur_group = gcnew HeroesGroups(dx_GHN, dy_GHN, reader_1->GetString(1), dx_GHP, dy_GHP);
				this->OpenConnection();
				String^ query_2 = "SELECT * FROM dbo.Heroes WHERE HeroType = '" + reader_1->GetInt32(0) + "'";
				SqlDataReader^ reader_2 = getReader(query_2);
				Int32 dx_hero_img{ 5 };
				while (reader_2->Read())
				{
					Heroes^ cur_hero = gcnew Heroes(reader_2, panel_for_descr);
					cur_group->get_GHP()->Controls->Add(cur_hero->getHeroPB());
					cur_hero->getHeroPB()->Location = System::Drawing::Point(dx_hero_img, 5);
					dx_hero_img += 100;
				}
				obj->getGroupsCatalogPanel()->Controls->Add(cur_group->get_GHN());
				obj->getGroupsCatalogPanel()->Controls->Add(cur_group->get_GHP());
				this->CloseConnection();
				dy_GHN += 170;
				dy_GHP += 170;
			}
			
		}
		finally { this->CloseConnection(); }
	}
	void SelectInformationHero(Panel^ hero_information_panel, Int32^ hero_ID)
	{
		try
		{
			this->OpenConnection();
			String^ query = "SELECT * FROM dbo.HeroInformation WHERE HeroID = " + hero_ID;
			SqlDataReader^ reader = getReader(query);
			while (reader->Read())
			{
				HeroInformation^ cur_hero_inf = gcnew HeroInformation(reader);
				hero_information_panel->Controls->Add(cur_hero_inf->getInfHero());
			}
		}
		finally { this->CloseConnection(); }
	}
	void SelectRuneAssembl(Panel^ hero_descr_panel, Panel^ hero_information_panel, Int32^ hero_ID, Panel^ more_inf_about_obj_panel)
	{
		try
		{
			Int32 dx{ 5 }, dy{ 5 };
			this->OpenConnection();
			String^ query = "SELECT * FROM dbo.RunesAssemblies WHERE HeroID = " + hero_ID;
			SqlDataReader^ reader = getReader(query);
			while (reader->Read())
			{
				RunesAssemblies^ cur_assebl = gcnew RunesAssemblies(reader);
				int i{ 1 };
				String^ query_2{};
				SqlDataReader^ reader_2{};
				while (i <= 10)
				{
					switch (i)
					{
					case 1:
						this->OpenConnection();
						query_2 = "SELECT * FROM dbo.TypeRunes WHERE TypeRuneID = " + cur_assebl->getRuneTypeID();
						reader_2 = getReader(query_2);
						while (reader_2->Read())
						{
							TypeRunes^ searched_type = gcnew TypeRunes(reader_2, hero_information_panel, more_inf_about_obj_panel);
							searched_type->getTypeRuneImage()->Location = System::Drawing::Point(dx, dy);
							searched_type->getTypeRuneImage()->Size = System::Drawing::Size(40, 40);
							hero_information_panel->Controls->Add(searched_type->getTypeRuneImage());
						}
						this->CloseConnection();
						break;
					case 2:
						this->OpenConnection();
						query_2 = "SELECT * FROM dbo.KeyRunes WHERE KeyRuneID = " + cur_assebl->getFirstKeyRuneID();
						reader_2 = getReader(query_2);
						while (reader_2->Read())
						{
							KeyRunes^ searched_key = gcnew KeyRunes(reader_2, hero_information_panel, more_inf_about_obj_panel);
							searched_key->SpecializedActionsForSelectingKeyRunes();
							searched_key->getKeyPB()->Location = System::Drawing::Point(dx, dy);
							searched_key->GetDescrPanel()->Location = System::Drawing::Point(5, 400);
							searched_key->GetDescrPanel()->Size = System::Drawing::Size(330, 155);
							searched_key->GetText()->Size = System::Drawing::Size(300, 150);
						}
						this->CloseConnection();
						break;
					case 3:
						this->OpenConnection();
						query_2 = "SELECT * FROM dbo.KeyRunes WHERE KeyRuneID = " + cur_assebl->getSecondKeyRuneID();
						reader_2 = getReader(query_2);
						while (reader_2->Read())
						{
							KeyRunes^ searched_key = gcnew KeyRunes(reader_2, hero_information_panel, more_inf_about_obj_panel);
							searched_key->SpecializedActionsForSelectingKeyRunes();
							searched_key->getKeyPB()->Location = System::Drawing::Point(dx, dy);
							searched_key->GetDescrPanel()->Location = System::Drawing::Point(5, 400);
							searched_key->GetDescrPanel()->Size = System::Drawing::Size(330, 155);
							searched_key->GetText()->Size = System::Drawing::Size(300, 150);
						}
						this->CloseConnection();
						break;
					case 4:
						this->OpenConnection();
						query_2 = "SELECT * FROM dbo.KeyRunes WHERE KeyRuneID = " + cur_assebl->getThirdKeyRuneID();
						reader_2 = getReader(query_2);
						while (reader_2->Read())
						{
							KeyRunes^ searched_key = gcnew KeyRunes(reader_2, hero_information_panel, more_inf_about_obj_panel);
							searched_key->SpecializedActionsForSelectingKeyRunes();
							searched_key->getKeyPB()->Location = System::Drawing::Point(dx, dy);
							searched_key->GetDescrPanel()->Location = System::Drawing::Point(5, 400);
							searched_key->GetDescrPanel()->Size = System::Drawing::Size(330, 155);
							searched_key->GetText()->Size = System::Drawing::Size(300, 150);
						}
						this->CloseConnection();
						break;
					case 5:
						this->OpenConnection();
						query_2 = "SELECT * FROM dbo.KeyRunes WHERE KeyRuneID = " + cur_assebl->getFourthKeyRuneID();
						reader_2 = getReader(query_2);
						while (reader_2->Read())
						{
							KeyRunes^ searched_key = gcnew KeyRunes(reader_2, hero_information_panel, more_inf_about_obj_panel);
							searched_key->SpecializedActionsForSelectingKeyRunes();
							searched_key->getKeyPB()->Location = System::Drawing::Point(dx, dy);
							searched_key->GetDescrPanel()->Location = System::Drawing::Point(5, 400);
							searched_key->GetDescrPanel()->Size = System::Drawing::Size(330, 155);
							searched_key->GetText()->Size = System::Drawing::Size(300, 150);
						}
						this->CloseConnection();
						break;
					case 6:
						this->OpenConnection();
						query_2 = "SELECT * FROM dbo.AdditionalRunes WHERE AdditionalRuneID = " + cur_assebl->getFirstAdditionalRuneID();
						reader_2 = getReader(query_2);
						while (reader_2->Read())
						{
							AdditionalRunes^ searched_key = gcnew AdditionalRunes(reader_2, hero_information_panel, more_inf_about_obj_panel);
							searched_key->SpecializedActionsForSelectingAdditionalRunes();
							searched_key->getAdditionalPB()->Location = System::Drawing::Point(dx, dy);
							searched_key->GetDescrPanel()->Location = System::Drawing::Point(5, 400);
							searched_key->GetDescrPanel()->Size = System::Drawing::Size(330, 155);
							searched_key->GetText()->Size = System::Drawing::Size(300, 150);
						}
						this->CloseConnection();
						break;
					case 7:
						this->OpenConnection();
						query_2 = "SELECT * FROM dbo.AdditionalRunes WHERE AdditionalRuneID = " + cur_assebl->getSecondAdditionalRuneID();
						reader_2 = getReader(query_2);
						while (reader_2->Read())
						{
							AdditionalRunes^ searched_key = gcnew AdditionalRunes(reader_2, hero_information_panel, more_inf_about_obj_panel);
							searched_key->SpecializedActionsForSelectingAdditionalRunes();
							searched_key->getAdditionalPB()->Location = System::Drawing::Point(dx, dy);
							searched_key->GetDescrPanel()->Location = System::Drawing::Point(5, 400);
							searched_key->GetDescrPanel()->Size = System::Drawing::Size(330, 155);
							searched_key->GetText()->Size = System::Drawing::Size(300, 150);
						}
						this->CloseConnection();
						break;
					case 8:
						this->OpenConnection();
						query_2 = "SELECT * FROM dbo.AdaptiveRunes WHERE AdaptiveRuneID = " + cur_assebl->getFirstAdaptiveRuneID();
						reader_2 = getReader(query_2);
						while (reader_2->Read())
						{
							AdaptiveRunes ^ searched_key = gcnew AdaptiveRunes(reader_2, hero_information_panel, more_inf_about_obj_panel);
							searched_key->SpecializedActionsForSelectingAdaptiveRunes();
							searched_key->getAdaptivePB()->Location = System::Drawing::Point(dx, dy);
							searched_key->GetDescrPanel()->Location = System::Drawing::Point(5, 400);
							searched_key->GetDescrPanel()->Size = System::Drawing::Size(330, 155);
							searched_key->GetText()->Size = System::Drawing::Size(300, 50);
							searched_key->GetText()->ScrollBars = System::Windows::Forms::ScrollBars::None;
						}
						this->CloseConnection();
						break;
					case 9:
						this->OpenConnection();
						query_2 = "SELECT * FROM dbo.AdaptiveRunes WHERE AdaptiveRuneID = " + cur_assebl->getSecondAdaptiveRuneID();
						reader_2 = getReader(query_2);
						while (reader_2->Read())
						{
							AdaptiveRunes^ searched_key = gcnew AdaptiveRunes(reader_2, hero_information_panel, more_inf_about_obj_panel);
							searched_key->SpecializedActionsForSelectingAdaptiveRunes();
							searched_key->getAdaptivePB()->Location = System::Drawing::Point(dx, dy);
							searched_key->GetDescrPanel()->Location = System::Drawing::Point(5, 400);
							searched_key->GetDescrPanel()->Size = System::Drawing::Size(330, 155);
							searched_key->GetText()->Size = System::Drawing::Size(300, 50);
							searched_key->GetText()->ScrollBars = System::Windows::Forms::ScrollBars::None;
						}
						this->CloseConnection();
						break;
					case 10:
						this->OpenConnection();
						query_2 = "SELECT * FROM dbo.AdaptiveRunes WHERE AdaptiveRuneID = " + cur_assebl->getThirdAdaptiveRuneID();
						reader_2 = getReader(query_2);
						while (reader_2->Read())
						{
							AdaptiveRunes^ searched_key = gcnew AdaptiveRunes(reader_2, hero_information_panel, more_inf_about_obj_panel);
							searched_key->SpecializedActionsForSelectingAdaptiveRunes();
							searched_key->getAdaptivePB()->Location = System::Drawing::Point(dx, dy);
							searched_key->GetDescrPanel()->Location = System::Drawing::Point(5, 400);
							searched_key->GetDescrPanel()->Size = System::Drawing::Size(330, 155);
							searched_key->GetText()->Size = System::Drawing::Size(300, 50);
							searched_key->GetText()->ScrollBars = System::Windows::Forms::ScrollBars::None;
						}
						this->CloseConnection();
						break;
					default:;
					}
					if (i == 2 || i == 5 || i == 7)
					{
						dx = 5;
						dy += 40;
					}
					else
						dx += 40;
					i++;
				}
				dy += 50;
				dx = 5;
			}
		}
		finally { this->CloseConnection(); }
	}
	void SelectItemAssembl(Panel^ hero_descr_panel, Panel^ hero_information_panel, Int32^ hero_ID, Panel^ more_inf_about_obj_panel)
	{
		try
		{
			Int32 dx{ 5 }, dy{ 5 };
			this->OpenConnection();
			String^ query = "SELECT * FROM dbo.ItemsAssemblies WHERE HeroID = " + hero_ID;
			SqlDataReader^ reader = getReader(query);
			while (reader->Read())
			{
				ItemsAssemblies^ cur_assebl = gcnew ItemsAssemblies(reader);
				int i{ 1 };
				String^ query_2{};
				SqlDataReader^ reader_2{};
				while (i <= 6)
				{
					switch (i)
					{
					case 1:
						this->OpenConnection();
						query_2 = "SELECT * FROM dbo.Items WHERE ItemID = " + cur_assebl->getFirstItemID();
						reader_2 = getReader(query_2);
						while (reader_2->Read())
						{
							Items^ searched_item = gcnew Items(reader_2, more_inf_about_obj_panel);
							searched_item->getItemPB()->Location = System::Drawing::Point(dx, dy);
							searched_item->getItemPB()->Size = System::Drawing::Size(40, 40);
							hero_information_panel->Controls->Add(searched_item->getItemPB());
							searched_item->getDescrPanel()->Size = System::Drawing::Size(300, 150);
							searched_item->getDescrPanel()->Location = System::Drawing::Point(5, 400);
							searched_item->getDescrPanel()->Size = System::Drawing::Size(330, 155);
							searched_item->getItemInformation()->Size = System::Drawing::Size(300, 330);
						}
						this->CloseConnection();
						break;
					case 2:
						this->OpenConnection();
						query_2 = "SELECT * FROM dbo.Items WHERE ItemID = " + cur_assebl->getSecondItemID();
						reader_2 = getReader(query_2);
						while (reader_2->Read())
						{
							Items^ searched_item = gcnew Items(reader_2, more_inf_about_obj_panel);
							searched_item->getItemPB()->Location = System::Drawing::Point(dx, dy);
							searched_item->getItemPB()->Size = System::Drawing::Size(40, 40);
							hero_information_panel->Controls->Add(searched_item->getItemPB());
							searched_item->getDescrPanel()->Size = System::Drawing::Size(300, 150);
							searched_item->getDescrPanel()->Location = System::Drawing::Point(5, 400);
							searched_item->getDescrPanel()->Size = System::Drawing::Size(330, 155);
							searched_item->getItemInformation()->Size = System::Drawing::Size(300, 330);
						}
						this->CloseConnection();
						break;
					case 3:
						this->OpenConnection();
						query_2 = "SELECT * FROM dbo.Items WHERE ItemID = " + cur_assebl->getThirdItemID();
						reader_2 = getReader(query_2);
						while (reader_2->Read())
						{
							Items^ searched_item = gcnew Items(reader_2, more_inf_about_obj_panel);
							searched_item->getItemPB()->Location = System::Drawing::Point(dx, dy);
							searched_item->getItemPB()->Size = System::Drawing::Size(40, 40);
							hero_information_panel->Controls->Add(searched_item->getItemPB());
							searched_item->getDescrPanel()->Size = System::Drawing::Size(300, 150);
							searched_item->getDescrPanel()->Location = System::Drawing::Point(5, 400);
							searched_item->getDescrPanel()->Size = System::Drawing::Size(330, 155);
							searched_item->getItemInformation()->Size = System::Drawing::Size(300, 330);
						}
						this->CloseConnection();
						break;
					case 4:
						this->OpenConnection();
						query_2 = "SELECT * FROM dbo.Items WHERE ItemID = " + cur_assebl->getFourthItemID();
						reader_2 = getReader(query_2);
						while (reader_2->Read())
						{
							Items^ searched_item = gcnew Items(reader_2, more_inf_about_obj_panel);
							searched_item->getItemPB()->Location = System::Drawing::Point(dx, dy);
							searched_item->getItemPB()->Size = System::Drawing::Size(40, 40);
							hero_information_panel->Controls->Add(searched_item->getItemPB());
							searched_item->getDescrPanel()->Size = System::Drawing::Size(300, 150);
							searched_item->getDescrPanel()->Location = System::Drawing::Point(5, 400);
							searched_item->getDescrPanel()->Size = System::Drawing::Size(330, 155);
							searched_item->getItemInformation()->Size = System::Drawing::Size(300, 330);
						}
						this->CloseConnection();
						break;
					case 5:
						this->OpenConnection();
						query_2 = "SELECT * FROM dbo.Items WHERE ItemID = " + cur_assebl->getFifthItemID();
						reader_2 = getReader(query_2);
						while (reader_2->Read())
						{
							Items^ searched_item = gcnew Items(reader_2, more_inf_about_obj_panel);
							searched_item->getItemPB()->Location = System::Drawing::Point(dx, dy);
							searched_item->getItemPB()->Size = System::Drawing::Size(40, 40);
							hero_information_panel->Controls->Add(searched_item->getItemPB());
							searched_item->getDescrPanel()->Size = System::Drawing::Size(300, 150);
							searched_item->getDescrPanel()->Location = System::Drawing::Point(5, 400);
							searched_item->getDescrPanel()->Size = System::Drawing::Size(330, 155);
							searched_item->getItemInformation()->Size = System::Drawing::Size(300, 330);
						}
						this->CloseConnection();
						break;
					case 6:
						this->OpenConnection();
						query_2 = "SELECT * FROM dbo.Items WHERE ItemID = " + cur_assebl->getSixthItemID();
						reader_2 = getReader(query_2);
						while (reader_2->Read())
						{
							Items^ searched_item = gcnew Items(reader_2, more_inf_about_obj_panel);
							searched_item->getItemPB()->Location = System::Drawing::Point(dx, dy);
							searched_item->getItemPB()->Size = System::Drawing::Size(40, 40);
							hero_information_panel->Controls->Add(searched_item->getItemPB());
							searched_item->getDescrPanel()->Size = System::Drawing::Size(300, 150);
							searched_item->getDescrPanel()->Location = System::Drawing::Point(5, 400);
							searched_item->getDescrPanel()->Size = System::Drawing::Size(330, 155);
							searched_item->getItemInformation()->Size = System::Drawing::Size(300, 330);
						}
						this->CloseConnection();
						break;
					default:;
					}
					dx += 40;
					i++;
				}
				dy += 50;
				dx = 5;
			}
		}
		finally { this->CloseConnection(); }
	}
	void SelectSpellAssembl(Panel^ hero_descr_panel, Panel^ hero_information_panel, Int32^ hero_ID, Panel^ more_inf_about_obj_panel)
	{
		try
		{
			Int32 dx{ 5 }, dy{ 5 };
			this->OpenConnection();
			String^ query = "SELECT * FROM dbo.SpellsAssemblies WHERE HeroID = " + hero_ID;
			SqlDataReader^ reader = getReader(query);
			while (reader->Read())
			{
				SpellsAssemblies^ cur_assebl = gcnew SpellsAssemblies(reader);
				int i{ 1 };
				String^ query_2{};
				SqlDataReader^ reader_2{};
				while (i <= 2)
				{
					switch (i)
					{
					case 1:
						this->OpenConnection();
						query_2 = "SELECT * FROM dbo.Spells WHERE SpellID = " + cur_assebl->getFirstSpellID();
						reader_2 = getReader(query_2);
						while (reader_2->Read())
						{
							Spells^ searched_spell = gcnew Spells(reader_2, hero_information_panel, more_inf_about_obj_panel);
							searched_spell->SpecializedActionsForSelectingSpells();
							searched_spell->getSpellPB()->Location = System::Drawing::Point(dx, dy);
							searched_spell->getSpellPB()->Size = System::Drawing::Size(40, 40);
							searched_spell->getTextBox()->Size = System::Drawing::Size(300, 150);
							searched_spell->getDescrPanel()->Location = System::Drawing::Point(5, 400);
							searched_spell->getDescrPanel()->Size = System::Drawing::Size(330, 155);
						}
						this->CloseConnection();
						break;
					case 2:
						this->OpenConnection();
						query_2 = "SELECT * FROM dbo.Spells WHERE SpellID = " + cur_assebl->getSecondSpellID();
						reader_2 = getReader(query_2);
						while (reader_2->Read())
						{
							Spells^ searched_spell = gcnew Spells(reader_2, hero_information_panel, more_inf_about_obj_panel);
							searched_spell->SpecializedActionsForSelectingSpells();
							searched_spell->getSpellPB()->Location = System::Drawing::Point(dx, dy);
							searched_spell->getSpellPB()->Size = System::Drawing::Size(40, 40);
							searched_spell->getTextBox()->Size = System::Drawing::Size(300, 150);
							searched_spell->getDescrPanel()->Location = System::Drawing::Point(5, 400);
							searched_spell->getDescrPanel()->Size = System::Drawing::Size(330, 155);
						}
						this->CloseConnection();
						break;
					default:;
					}
					dx += 40;
					i++;
				}
				dy += 50;
				dx = 5;
			}
		}
		finally { CloseConnection(); }
	}
	void FindHeroes(Panel^ groups_catalog_panel, Panel^ panel_for_descr, String^ search_text)
	{
		try
		{
			this->OpenConnection();
			String^ query_1 = "SELECT * FROM dbo.HeroTypes";
			SqlDataReader^ reader_1 = getReader(query_1);
			Int32 dx_GHN{ 280 }, dy_GHN{ 10 }, dx_GHP{}, dy_GHP{ 50 };
			while (reader_1->Read())
			{
				HeroesGroups^ cur_group = gcnew HeroesGroups(dx_GHN, dy_GHN, reader_1->GetString(1), dx_GHP, dy_GHP);
				this->OpenConnection();
				String^ query_2{};
				if (search_text == "")
					query_2 = "SELECT * FROM dbo.Heroes WHERE HeroType = '" + reader_1->GetInt32(0) + "'";
				else
					query_2 = "SELECT * FROM dbo.Heroes WHERE HeroName LIKE '%" + search_text + "%' AND HeroType = '" + reader_1->GetInt32(0) + "'";
				SqlDataReader^ reader_2 = getReader(query_2);
				Int32 dx_hero_img{ 5 };
				while (reader_2->Read())
				{
					Heroes^ cur_hero = gcnew Heroes(reader_2, panel_for_descr);
					cur_group->get_GHP()->Controls->Add(cur_hero->getHeroPB());
					cur_hero->getHeroPB()->Location = System::Drawing::Point(dx_hero_img, 5);
					dx_hero_img += 100;
				}
				groups_catalog_panel->Controls->Add(cur_group->get_GHN());
				groups_catalog_panel->Controls->Add(cur_group->get_GHP());
				this->CloseConnection();
				dy_GHN += 170;
				dy_GHP += 170;
			}
		}
		finally { this->CloseConnection(); }
	}
	void FindItems(Panel^ panel_for_objects, Panel^ descr_panel, String^ search_text)
	{
		try
		{
			this->OpenConnection();
			String^ query{};
			if (search_text == "")
				query = "SELECT * FROM dbo.Items";
			else
				query = "SELECT * FROM dbo.Items WHERE ItemName LIKE '%" + search_text + "%'";
			SqlDataReader^ reader = getReader(query);
			Int32 dx{ 5 }, dy{ 5 };
			while (reader->Read())
			{
				Items^ cur_item = gcnew Items(reader, descr_panel);
				cur_item->getItemPB()->Location = System::Drawing::Point(dx, dy);
				panel_for_objects->Controls->Add(cur_item->getItemPB());
				if (dx > 600) { dy += 65; dx = 5; }
				else { dx += 60; }
			}
		}
		finally { this->CloseConnection(); }
	}
	void AdminEntry(Panel^ btns_panel, Panel^ descr_panel)
	{
		try
		{
			this->OpenConnection();
			EntryAdmin^ obj = gcnew EntryAdmin(btns_panel, descr_panel);
		}
		finally { this->CloseConnection(); }
	}
	void CheckPass(String^ pass, Panel^ btns_panel, Panel^ descr_panel)
	{
		try
		{
			this->OpenConnection();
			DataTable^ table = gcnew DataTable();
			String^ query = "Select * FROM Admins";
			SqlDataReader^ reader = this->getReader(query);
			while (reader->Read())
			{
				if (reader->GetString(1) == pass)
				{
					MessageBox::Show("Вы авторизовались.");
					Admin^ obj = gcnew Admin(btns_panel, descr_panel);
					return;
				}
			}
			MessageBox::Show("Неверный пароль!");
		}
		finally { this->CloseConnection(); }
	}
	void getDataGridView(String^ identificator, DataGridView^ data)
	{
		try
		{
			this->OpenConnection();
			DataTable^ table = gcnew DataTable();
			String^ query{};
			if (identificator == "Герои")
				query = "SELECT * FROM Heroes";
			else if (identificator == "Информация о героях")
				query = "SELECT * FROM HeroInformation";
			else if (identificator == "Типы героев")
				query = "SELECT * FROM HeroTypes";
			else if (identificator == "Типы рун")
				query = "SELECT * FROM TypeRunes";
			else if (identificator == "Ключевые руны")
				query = "SELECT * FROM KeyRunes";
			else if (identificator == "Дополнительные руны")
				query = "SELECT * FROM AdditionalRunes";
			else if (identificator == "Адаптивные руны")
				query = "SELECT * FROM AdaptiveRunes";
			else if (identificator == "Предметы")
				query = "SELECT * FROM Items";
			else if (identificator == "Заклинания")
				query = "SELECT * FROM Spells";
			else if (identificator == "Сборки рун")
				query = "SELECT * FROM RunesAssemblies";
			else if (identificator == "Сборки предметов")
				query = "SELECT * FROM ItemsAssemblies";
			else
				query = "SELECT * FROM SpellsAssemblies";
			SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
			SqlDataAdapter^ adapter = gcnew SqlDataAdapter();
			adapter->SelectCommand = SQL_command;
			adapter->Fill(table);

			data->DataSource = table;
		}
		finally { this->CloseConnection(); }
	}
	//Функции для добавления данных админом.
	bool checkNumeric(String^ check_obj)
	{
		for (int i{}; i < check_obj->Length; i++)
		{
			if (check_obj[i] < '0' || check_obj[i] > '9')
			{
				return false;
				break;
			}
		}
		return true;
	}
	bool checkID(String^ tableName, String^ table_column, String^ check_obj, int num_str)
	{
		try
		{
			this->OpenConnection();
			String^ query = "SELECT * FROM " + tableName + " WHERE " + table_column + " = '" + check_obj + "'";
			SqlDataReader^ reader = getReader(query);
			while (reader->Read())
			{
				Int32^ value = reader->GetInt32(num_str);
				if (value->ToString() == check_obj)
				{
					return true;
					break;
				}
			}
		}
		finally { this->CloseConnection(); }
		return false;
	}
	bool checkName(String^ tableName, String^ table_column, String^ check_obj, int num_str)
	{
		try
		{
			this->OpenConnection();
			String^ query = "SELECT * FROM " + tableName + " WHERE " + table_column + " = '" + check_obj + "'";
			SqlDataReader^ reader = getReader(query);
			while (reader->Read())
			{
				if (reader->GetString(num_str) == check_obj)
				{
					return true;
					break;
				}
			}
		}
		finally { this->CloseConnection(); }
		return false;
	}
	bool checkPathImage(String^ path_to_image)
	{
		Image^ newImage{};
		try
		{
			newImage = gcnew Bitmap(path_to_image);
		}
		catch (Exception^ ex)
		{
			return false;
		}
		return true;
	}
	//Добавление
	void InsertHero(String^ HeroName, String^ HeroImage, String^ HeroHistory, String^ HeroSkillsDescr, String^ HeroType, Label^ text_errors)
	{
		if (HeroName == "*Hero Name" || HeroImage == "*Hero Image (path to file)" || HeroHistory == "*Hero History" || HeroSkillsDescr == "*Hero Skills Description" || HeroType == "*Hero Type")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (HeroName->Length > 20)
			text_errors->Text += "Имя героя не должно содержать больше 20 символов.";
		if (!this->checkPathImage(HeroImage))
			text_errors->Text += "По данному пути не существует искомого файла изображения. ";
		if (!this->checkNumeric(HeroType))
			text_errors->Text += "Тип героя должен содержать ID соответствующего типа в таблице TypesHero. ";
		else
		{
			if (!this->checkID("dbo.HeroTypes", "TypeID", HeroType, 0))
				text_errors->Text += "Такого типа героя не существует.";
			try
			{
				this->OpenConnection();
				String^ query = "SELECT * FROM dbo.Heroes WHERE (HeroName = '" + HeroName + "') AND (HeroType = '" + HeroType + "')";
				SqlDataReader^ reader = getReader(query);
				while (reader->Read())
				{
					text_errors->Text += "Нельзя создавать персонажа с тем же именем и типом. ";
					break;
				}
			}
			finally { this->CloseConnection(); }
		}
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				String^ query =
					"INSERT INTO dbo.Heroes(HeroName, HeroImage, HeroHistory, HeroSkillsDescr, HeroType) " +
					"VALUES " +
					"(@HeroName, (SELECT BulkColumn FROM Openrowset (BULK '" + HeroImage + "', Single_Blob) as img), @HeroHistory, @HeroSkillsDescr, @HeroType)";
				SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->Parameters->AddWithValue("@HeroName", HeroName);
				SQL_command->Parameters->AddWithValue("@HeroHistory", HeroHistory);
				SQL_command->Parameters->AddWithValue("@HeroSkillsDescr", HeroSkillsDescr);
				SQL_command->Parameters->AddWithValue("@HeroType", HeroType);
				SQL_command->ExecuteNonQuery();
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были добавлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void InsertHeroInformation(String^ HeroID, String^ SkillsCombination, String^ SkillsTree, String^ SkillsRecharge, Label^ text_errors)
	{
		if (HeroID == "*Hero ID" || SkillsRecharge == "*Skills Recharge")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (!this->checkNumeric(HeroID))
			text_errors->Text += "ID героя дожен содержать ID соответствующего героя в таблице Heroes. ";
		else
		{
			if (this->checkID("dbo.HeroInformation", "HeroID", HeroID, 0))
				text_errors->Text += "Информация о таком герое уже была добавлена в базу данных. ";
			if (!this->checkID("dbo.Heroes", "HeroID", HeroID, 0))
				text_errors->Text += "Сначала необходимо добавить самого героя, а не информацию о нем. ";
		}
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				String^ query =
					"INSERT INTO dbo.HeroInformation(HeroID, SkillsCombination, SkillsTree, SkillsRecharge) " +
					"VALUES " +
					"(@HeroID, @SkillsCombination, @SkillsTree, @SkillsRecharge)";
				SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
				if (SkillsCombination == "Skills Combination") SkillsCombination = "-";
				if (SkillsTree == "Skills Tree") SkillsTree = "-";
				SQL_command->Parameters->AddWithValue("@HeroID", HeroID);
				SQL_command->Parameters->AddWithValue("@SkillsCombination", SkillsCombination);
				SQL_command->Parameters->AddWithValue("@SkillsTree", SkillsTree);
				SQL_command->Parameters->AddWithValue("@SkillsRecharge", SkillsRecharge);
				SQL_command->ExecuteNonQuery();
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были добавлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void InsertTypeHero(String^ TypeName, Label^ text_errors)
	{
		if (TypeName == "*Type Name")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (TypeName->Length > 10)
			text_errors->Text += "Тип героя не должен содержать больше 10 символов.";
		if (this->checkName("dbo.HeroTypes", "TypeName", TypeName, 1))
			text_errors->Text += "Такой тип героя уже существует. ";
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				String^ query =
					"INSERT INTO dbo.HeroTypes(TypeName) " +
					"VALUES " +
					"(@TypeName)";
				SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->Parameters->AddWithValue("@TypeName", TypeName);
				SQL_command->ExecuteNonQuery();
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были добавлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void InsertTypeRune(String^ TypeRuneImage, String^ TypeRuneDescr, String^ TypeRuneName, Label^ text_errors)
	{
		if (TypeRuneImage == "*Type Rune Image (path to file)" || TypeRuneDescr == "*Type Rune Description" || TypeRuneName == "*Type Rune Name")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (TypeRuneName->Length > 30)
			text_errors->Text += "Имя руны не должно содержать больше 30 символов.";
		if (!this->checkPathImage(TypeRuneImage))
			text_errors->Text += "По данному пути не существует искомого файла изображения. ";
		if (this->checkName("dbo.TypeRunes", "TypeRuneName", TypeRuneName, 3))
			text_errors->Text += "Такой тип руны уже существует. ";
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				String^ query =
					"INSERT INTO dbo.TypeRunes(TypeRuneImage, TypeRuneDescr, TypeRuneName) " +
					"VALUES " +
					"((SELECT BulkColumn FROM Openrowset (BULK '" + TypeRuneImage + "', Single_Blob) as img), @TypeRuneDescr, @TypeRuneName)";
				SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->Parameters->AddWithValue("@TypeRuneDescr", TypeRuneDescr);
				SQL_command->Parameters->AddWithValue("@TypeRuneName", TypeRuneName);
				SQL_command->ExecuteNonQuery();
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были добавлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void InsertKeyRune(String^ TypeRuneID, String^ KeyRuneImage, String^ KeyRuneDescr, String^ KeyRuneName, Label^ text_errors)
	{
		if (TypeRuneID == "*Type Rune ID" || KeyRuneImage == "*Key Rune Image (path to file)" || KeyRuneDescr == "*Key Rune Description" || KeyRuneName == "*Key Rune Name")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (KeyRuneName->Length > 50)
			text_errors->Text += "Имя ключевой руны не должно содержать больше 50 символов.";
		if (!this->checkPathImage(KeyRuneImage))
			text_errors->Text += "По данному пути не существует искомого файла изображения. ";
		if (this->checkName("dbo.KeyRunes", "KeyRuneName", KeyRuneName, 4))
			text_errors->Text += "Такая ключевая руна уже существует. ";
		if (!this->checkNumeric(TypeRuneID))
				text_errors->Text += "Тип руны, к которому относится ключевая руна, должен содержать ID соответствующего типа руны в таблице TypeRunes. ";
		else
		{
			if (!this->checkID("dbo.TypeRunes", "TypeRuneID", TypeRuneID, 0))
				text_errors->Text += "Такого типа руны не существует.";
		}
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				String^ query =
					"INSERT INTO dbo.KeyRunes(TypeRuneID, KeyRuneImage, KeyRuneDescr, KeyRuneName) " +
					"VALUES " +
					"(@TypeRuneID, (SELECT BulkColumn FROM Openrowset (BULK '" + KeyRuneImage + "', Single_Blob) as img), @KeyRuneDescr, @KeyRuneName)";
				SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->Parameters->AddWithValue("@TypeRuneID", TypeRuneID);
				SQL_command->Parameters->AddWithValue("@KeyRuneDescr", KeyRuneDescr);
				SQL_command->Parameters->AddWithValue("@KeyRuneName", KeyRuneName);
				SQL_command->ExecuteNonQuery();
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были добавлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void InsertAdditionalRune(String^ TypeRuneID, String^ AdditionalRuneImage, String^ AdditionalRuneDescr, String^ AdditionalRuneName, Label^ text_errors)
	{
		if (TypeRuneID == "*Type Rune ID" || AdditionalRuneImage == "*Additional Rune Image (path to file)" || AdditionalRuneDescr == "*Additional Rune Description" || AdditionalRuneName == "*Additional Rune Name")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (AdditionalRuneName->Length > 50)
			text_errors->Text += "Имя дополнительной руны не должно содержать больше 50 символов.";
		if (!this->checkPathImage(AdditionalRuneImage))
			text_errors->Text += "По данному пути не существует искомого файла изображения. ";
		if (this->checkName("dbo.AdditionalRunes", "AdditionalRuneName", AdditionalRuneName, 4))
			text_errors->Text += "Такая дополнительная руна уже существует. ";
		if (!this->checkNumeric(TypeRuneID))
				text_errors->Text += "Тип руны, к которому относится дополнительная руна, должен содержать ID соответствующего типа руны в таблице TypeRunes. ";
		else
		{
			if (!this->checkID("dbo.TypeRunes", "TypeRuneID", TypeRuneID, 0))
				text_errors->Text += "Такого типа руны не существует.";
		}
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				String^ query =
					"INSERT INTO dbo.AdditionalRunes(TypeRuneID, AdditionalRuneImage, AdditionalRuneDescr, AdditionalRuneName) " +
					"VALUES " +
					"(@TypeRuneID, (SELECT BulkColumn FROM Openrowset (BULK '" + AdditionalRuneImage + "', Single_Blob) as img), @AdditionalRuneDescr, @AdditionalRuneName)";
				SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->Parameters->AddWithValue("@TypeRuneID", TypeRuneID);
				SQL_command->Parameters->AddWithValue("@AdditionalRuneDescr", AdditionalRuneDescr);
				SQL_command->Parameters->AddWithValue("@AdditionalRuneName", AdditionalRuneName);
				SQL_command->ExecuteNonQuery();
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были добавлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void InsertAdaptiveRune(String^ AdaptiveRuneImage, String^ AdaptiveRuneDescr, String^ AdaptiveRuneName, Label^ text_errors)
	{
		if (AdaptiveRuneImage == "*Adaptive Rune Image (path to file)" || AdaptiveRuneDescr == "*Adaptive Rune Description" || AdaptiveRuneName == "*Adaptive Rune Name")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (AdaptiveRuneName->Length > 30)
			text_errors->Text += "Имя адаптивной руны не должно содержать больше 30 символов.";
		if (!this->checkPathImage(AdaptiveRuneImage))
			text_errors->Text += "По данному пути не существует искомого файла изображения. ";
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				String^ query =
					"INSERT INTO dbo.AdaptiveRunes(AdaptiveRuneImage, AdaptiveRuneDescr, AdaptiveRuneName) " +
					"VALUES " +
					"((SELECT BulkColumn FROM Openrowset (BULK '" + AdaptiveRuneImage + "', Single_Blob) as img), @AdaptiveRuneDescr, @AdaptiveRuneName)";
				SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->Parameters->AddWithValue("@AdaptiveRuneDescr", AdaptiveRuneDescr);
				SQL_command->Parameters->AddWithValue("@AdaptiveRuneName", AdaptiveRuneName);
				SQL_command->ExecuteNonQuery();
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были добавлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void InsertItem(String^ ItemImage, String^ ItemDescr, String^ ActiveCharacteristics, String^ PassiveCharacteristics, String^ GameStage, String^ ItemType, String^ ItemCost, String^ ItemName, Label^ text_errors)
	{
		if (ItemImage == "*Item Image (path to file)" || ItemType == "*Item Type" || ItemCost == "*Item Cost" || ItemName == "*Item Name")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (ItemName->Length > 30)
			text_errors->Text += "Имя предмета не должно содержать больше 10 символов.";
		if (!this->checkPathImage(ItemImage))
			text_errors->Text += "По данному пути не существует искомого файла изображения. ";
		int cost{};
		if (!this->checkNumeric(ItemCost))
			text_errors->Text += "Цена предмета должна содержать числовое значение. ";
		else
			for (int i{}; i < ItemCost->Length; i++)
			{
				cost += static_cast<int>((ItemCost[i] - '0') * pow(10, ItemCost->Length - i - 1));
			}
		if (!this->checkNumeric(ItemType))
			text_errors->Text += "Тип предмета должен содержать ID соответствующего типа героя в таблице HeroTypes. ";
		else
		{
			if (!this->checkID("dbo.HeroTypes", "TypeID", ItemType, 0))
				text_errors->Text += "Такого типа героя не существует.";
		}
		if (this->checkID("dbo.Items", "ItemName", ItemName, 8))
			text_errors->Text += "Такой предмет уже существует. ";
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				String^ query =
					"INSERT INTO dbo.Items(ItemImage, ItemDescr, ActiveCharacteristics, PassiveCharacteristics, GameStage, ItemType, ItemCost, ItemName) " +
					"VALUES " +
					"((SELECT BulkColumn FROM Openrowset (BULK '" + ItemImage + "', Single_Blob) as img), @ItemDescr, @ActiveCharacteristics, @PassiveCharacteristics, @GameStage, @ItemType, @ItemCost, @ItemName)";
				SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
				if (ItemDescr == "Item Description") ItemDescr = "-";
				if (ActiveCharacteristics == "Active Characteristics") ActiveCharacteristics = "-";
				if (PassiveCharacteristics == "Passive Characteristics") PassiveCharacteristics = "-";
				if (GameStage == "Game Stage") GameStage = "-";
				SQL_command->Parameters->AddWithValue("@ItemDescr", ItemDescr);
				SQL_command->Parameters->AddWithValue("@ActiveCharacteristics", ActiveCharacteristics);
				SQL_command->Parameters->AddWithValue("@PassiveCharacteristics", PassiveCharacteristics);
				SQL_command->Parameters->AddWithValue("@GameStage", GameStage);
				SQL_command->Parameters->AddWithValue("@ItemType", ItemType);
				SQL_command->Parameters->AddWithValue("@ItemCost", cost);
				SQL_command->Parameters->AddWithValue("@ItemName", ItemName);
				SQL_command->ExecuteNonQuery();
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были добавлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void InsertSpell(String^ SpellImage, String^ SpellName, String^ SpellDescr, String^ SpellRecharge, String^ SpellLine, Label^ text_errors)
	{
		if (SpellImage == "*Spell Image (path to file)" || SpellName == "*Spell Name" || SpellDescr == "*Spell Description" || SpellRecharge == "*Spell Recharge")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (SpellName->Length > 25)
			text_errors->Text += "Имя предмета не должно содержать больше 25 символов.";
		if (SpellRecharge->Length > 10)
			text_errors->Text += "Перезарядка предмета не должна содержать больше 10 символов.";
		if (!this->checkPathImage(SpellImage))
			text_errors->Text += "По данному пути не существует искомого файла изображения. ";
		if (this->checkID("dbo.Spells", "SpellName", SpellName, 2))
			text_errors->Text += "Такое заклинание уже существует. ";
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				String^ query =
					"INSERT INTO dbo.Spells(SpellImage, SpellName, SpellDescr, SpellRecharge, SpellLine) " +
					"VALUES " +
					"((SELECT BulkColumn FROM Openrowset (BULK '" + SpellImage + "', Single_Blob) as img), @SpellName, @SpellDescr, @SpellRecharge, @SpellLine)";
				SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
				if (SpellLine == "Spell Line") SpellLine = "-";
				SQL_command->Parameters->AddWithValue("@SpellName", SpellName);
				SQL_command->Parameters->AddWithValue("@SpellDescr", SpellDescr);
				SQL_command->Parameters->AddWithValue("@SpellRecharge", SpellRecharge);
				SQL_command->Parameters->AddWithValue("@SpellLine", SpellLine);
				SQL_command->ExecuteNonQuery();
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были добавлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void InsertRuneAssembl(String^ HeroID, String^ RuneType, String^ FirstKeyRune, String^ SecondKeyRune, String^ ThirdKeyRune, String^ FourthKeyRune, String^ FirstAdditionalRune, String^ SecondAdditionalRune, String^ FirstAdaptiveRune, String^ SecondAdaptiveRune, String^ ThirdAdaptiveRune, Label^ text_errors)
	{
		if (HeroID == "*Hero ID" || RuneType == "*Rune Type" || FirstKeyRune == "*First Key Rune" || SecondKeyRune == "*Second Key Rune" || ThirdKeyRune == "*Third Key Rune" ||
			FourthKeyRune == "*Fourth Key Rune" || FirstAdditionalRune == "*First Additional Rune" || SecondAdditionalRune == "*Second Additional Rune" || FirstAdaptiveRune == "*First Adaptive Rune" ||
			SecondAdaptiveRune == "*Second Adaptive Rune" || ThirdAdaptiveRune == "*Third Adaptive Rune")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (!this->checkNumeric(HeroID) || !this->checkNumeric(RuneType) || !this->checkNumeric(FirstKeyRune) || !this->checkNumeric(SecondKeyRune) || !this->checkNumeric(ThirdKeyRune) || 
			!this->checkNumeric(FourthKeyRune) || !this->checkNumeric(FirstAdditionalRune) || !this->checkNumeric(SecondAdditionalRune) || !this->checkNumeric(FirstAdaptiveRune) || 
			!this->checkNumeric(SecondAdaptiveRune) || !this->checkNumeric(ThirdAdaptiveRune))
			text_errors->Text += "Все значения полей должны быть числовыми. ";
		else
		{
			if (!this->checkID("dbo.HeroInformation", "HeroID", HeroID, 0) || !this->checkID("dbo.TypeRunes", "TypeRuneID", RuneType, 0) ||
				!this->checkID("dbo.KeyRunes", "KeyRuneID", FirstKeyRune, 0) || !this->checkID("dbo.KeyRunes", "KeyRuneID", SecondKeyRune, 0) || !this->checkID("dbo.KeyRunes", "KeyRuneID", ThirdKeyRune, 0) ||
				!this->checkID("dbo.KeyRunes", "KeyRuneID", FourthKeyRune, 0) || !this->checkID("dbo.AdditionalRunes", "AdditionalRuneID", FirstAdditionalRune, 0) ||
				!this->checkID("dbo.AdditionalRunes", "AdditionalRuneID", SecondAdditionalRune, 0) || !this->checkID("dbo.AdaptiveRunes", "AdaptiveRuneID", FirstAdaptiveRune, 0) ||
				!this->checkID("dbo.AdaptiveRunes", "AdaptiveRuneID", SecondAdaptiveRune, 0) || !this->checkID("dbo.AdaptiveRunes", "AdaptiveRuneID", ThirdAdaptiveRune, 0))
				text_errors->Text += "Какой-то из введенных Вами ID объектов не существует. ";
		}
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				String^ query =
					"INSERT INTO dbo.RunesAssemblies(HeroID, RuneType, FirstKeyRune, SecondKeyRune, ThirdKeyRune, FourthKeyRune, FirstAdditionalRune, SecondAdditionalRune, FirstAdaptiveRune, SecondAdaptiveRune, ThirdAdaptiveRune) " +
					"VALUES " +
					"(@HeroID, @RuneType, @FirstKeyRune, @SecondKeyRune, @ThirdKeyRune, @FourthKeyRune, @FirstAdditionalRune, @SecondAdditionalRune, @FirstAdaptiveRune, @SecondAdaptiveRune, @ThirdAdaptiveRune)";
				SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->Parameters->AddWithValue("@HeroID", HeroID);
				SQL_command->Parameters->AddWithValue("@RuneType", RuneType);
				SQL_command->Parameters->AddWithValue("@FirstKeyRune", FirstKeyRune);
				SQL_command->Parameters->AddWithValue("@SecondKeyRune", SecondKeyRune);
				SQL_command->Parameters->AddWithValue("@ThirdKeyRune", ThirdKeyRune);
				SQL_command->Parameters->AddWithValue("@FourthKeyRune", FourthKeyRune);
				SQL_command->Parameters->AddWithValue("@FirstAdditionalRune", FirstAdditionalRune);
				SQL_command->Parameters->AddWithValue("@SecondAdditionalRune", SecondAdditionalRune);
				SQL_command->Parameters->AddWithValue("@FirstAdaptiveRune", FirstAdaptiveRune);
				SQL_command->Parameters->AddWithValue("@SecondAdaptiveRune", SecondAdaptiveRune);
				SQL_command->Parameters->AddWithValue("@ThirdAdaptiveRune", ThirdAdaptiveRune);
				SQL_command->ExecuteNonQuery();
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были добавлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void InsertItemAssembl(String^ HeroID, String^ FirstItem, String^ SecondItem, String^ ThirdItem, String^ FourthItem, String^ FifthItem, String^ SixthItem, Label^ text_errors)
	{
		if (HeroID == "*Hero ID" || FirstItem == "*First Item" || SecondItem == "*Second Item" || ThirdItem == "*Third Item" || 
			FourthItem == "*Fouth Item" || FifthItem == "*Fifth Item" || SixthItem == "*Sixth Item")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (!this->checkNumeric(HeroID) || !this->checkNumeric(FirstItem) || !this->checkNumeric(SecondItem) || !this->checkNumeric(ThirdItem) || 
			!this->checkNumeric(FourthItem) || !this->checkNumeric(FifthItem) || !this->checkNumeric(SixthItem))
			text_errors->Text += "Все значения полей должны быть числовыми. ";
		else
		{
			if (!this->checkID("dbo.HeroInformation", "HeroID", HeroID, 0) || !this->checkID("dbo.Items", "ItemID", FirstItem, 0) || !this->checkID("dbo.Items", "ItemID", SecondItem, 0) ||
				!this->checkID("dbo.Items", "ItemID", ThirdItem, 0) || !this->checkID("dbo.Items", "ItemID", FourthItem, 0) || !this->checkID("dbo.Items", "ItemID", FifthItem, 0) ||
				!this->checkID("dbo.Items", "ItemID", SixthItem, 0))
				text_errors->Text += "Какой-то из введенных Вами ID объектов не существует. ";
		}
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				String^ query =
					"INSERT INTO dbo.ItemsAssemblies(HeroID, FirstItem, SecondItem, ThirdItem, FourthItem, FifthItem, SixthItem) " +
					"VALUES " +
					"(@HeroID, @FirstItem, @SecondItem, @ThirdItem, @FourthItem, @FifthItem, @SixthItem)";
				SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->Parameters->AddWithValue("@HeroID", HeroID);
				SQL_command->Parameters->AddWithValue("@FirstItem", FirstItem);
				SQL_command->Parameters->AddWithValue("@SecondItem", SecondItem);
				SQL_command->Parameters->AddWithValue("@ThirdItem", ThirdItem);
				SQL_command->Parameters->AddWithValue("@FourthItem", FourthItem);
				SQL_command->Parameters->AddWithValue("@FifthItem", FifthItem);
				SQL_command->Parameters->AddWithValue("@SixthItem", SixthItem);
				SQL_command->ExecuteNonQuery();
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были добавлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void InsertSpellAssembl(String^ HeroID, String^ FirstSpell, String^ SecondSpell, Label^ text_errors)
	{
		if (HeroID == "*Hero ID" || FirstSpell == "*First Spell" || SecondSpell == "*Second Spell")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (!this->checkNumeric(HeroID) || !this->checkNumeric(FirstSpell) || !this->checkNumeric(SecondSpell))
			text_errors->Text += "Все значения полей должны быть числовыми. ";
		else
		{
			if (!this->checkID("dbo.HeroInformation", "HeroID", HeroID, 0) || !this->checkID("dbo.Spells", "SpellID", FirstSpell, 0) ||
				!this->checkID("dbo.Spells", "SpellID", SecondSpell, 0))
				text_errors->Text += "Какой-то из введенных Вами ID объектов не существует. ";
		}
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				String^ query =
					"INSERT INTO dbo.SpellsAssemblies(HeroID, FirstSpell, SecondSpell) " +
					"VALUES " +
					"(@HeroID, @FirstSpell, @SecondSpell)";
				SqlCommand^ SQL_command = gcnew SqlCommand(query, conn);
				SQL_command->Parameters->AddWithValue("@HeroID", HeroID);
				SQL_command->Parameters->AddWithValue("@FirstSpell", FirstSpell);
				SQL_command->Parameters->AddWithValue("@SecondSpell", SecondSpell);
				SQL_command->ExecuteNonQuery();
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были добавлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	//Удаление
	void DeleteHero(String^ HeroID, Label^ text_errors)
	{
		if (HeroID == "*Hero ID")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (!this->checkNumeric(HeroID))
			text_errors->Text += "ID героя должен быть целочисленным. ";
		else
		{
			if (!this->checkID("dbo.Heroes", "HeroID", HeroID, 0))
				text_errors->Text += "Данный герой отсутствует в базе данных.";
		}
		if (text_errors->Text == "")
		{
			if (MessageBox::Show("Удаление героя выполнится каскадно, то есть вместе с ним удалится информация о нем и всех сборках предметов, рун и заклинаний (весь билд героя). Вы согласны?", "ПРЕДУПРЕЖДЕНИЕ!", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == ::DialogResult::Yes)
			{
				String^ query{};
				SqlCommand^ SQL_command{};
				try
				{
					this->OpenConnection();
					//Удаление сборок заклинаний, связанных с данным персонажем.
					query = "DELETE FROM dbo.SpellsAssemblies WHERE HeroID = '" + HeroID + "'";
					SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
					//Удаление сборок предметов, связанных с данным персонжем.
					query = "DELETE FROM dbo.ItemsAssemblies WHERE HeroID = '" + HeroID + "'";
					SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
					//Удаление сборок рун, связанных с данным персонжем.
					query = "DELETE FROM dbo.RunesAssemblies WHERE HeroID = '" + HeroID + "'";
					SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
					//Удаление информации, связанной с данным персонажем.
					query = "DELETE FROM dbo.HeroInformation WHERE HeroID = '" + HeroID + "'";
					SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
					//Удаление самого персонажа.
					query = "DELETE FROM dbo.Heroes WHERE HeroID = " + HeroID;
					SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();

					text_errors->ForeColor = System::Drawing::Color::ForestGreen;
					text_errors->Text = "Данные были удалены!";
				}
				finally { this->CloseConnection(); }
			}
		}
	}
	void DeleteHeroInformation(String^ HeroID, Label^ text_errors)
	{
		if (HeroID == "*Hero ID")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (!this->checkNumeric(HeroID))
			text_errors->Text += "ID информации о герое должно быть целочисленным. ";
		else
		{
			if (!this->checkID("dbo.HeroInformation", "HeroID", HeroID, 0))
				text_errors->Text += "Инфорамация о данном герое отсутствует в базе данных.";
		}
		if (text_errors->Text == "")
		{
			if (MessageBox::Show("Удаление информации выполнится каскадно, то есть вместе с ней удалятся все сборки предметов, рун и заклинаний (весь билд героя). Вы согласны?", "ПРЕДУПРЕЖДЕНИЕ!", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == ::DialogResult::Yes)
			{
				String^ query{};
				SqlCommand^ SQL_command{};
				try
				{
					this->OpenConnection();
					//Удаление сборок заклинаний, связанных с данным персонажем.
					query = "DELETE FROM dbo.SpellsAssemblies WHERE HeroID = '" + HeroID + "'";
					SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
					//Удаление сборок предметов, связанных с данным персонжем.
					query = "DELETE FROM dbo.ItemsAssemblies WHERE HeroID = '" + HeroID + "'";
					SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
					//Удаление сборок рун, связанных с данным персонжем.
					query = "DELETE FROM dbo.RunesAssemblies WHERE HeroID = '" + HeroID + "'";
					SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
					//Удаление самой информации о герое.
					query = "DELETE FROM dbo.HeroInformation WHERE HeroID = '" + HeroID + "'";
					SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();

					text_errors->ForeColor = System::Drawing::Color::ForestGreen;
					text_errors->Text = "Данные были удалены!";
				}
				finally { this->CloseConnection(); }
			}
		}
	}
	void DeleteHeroType(String^ TypeID, Label^ text_errors)
	{
		if (TypeID == "*Type ID")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (!this->checkNumeric(TypeID))
			text_errors->Text += "ID типа героя должен быть целочисленным. ";
		else
		{
			if (!this->checkID("dbo.HeroTypes", "TypeID", TypeID, 0))
				text_errors->Text += "Данный тип героя отсутствует в базе данных.";
			if (this->checkID("dbo.Heroes", "HeroType", TypeID, 5) || this->checkID("dbo.Items", "ItemType", TypeID, 6))
				text_errors->Text += "Данный объект нельзя удалить. Он связан с другими таблицами.";
		}
		if (text_errors->Text == "")
		{
			String^ query{};
			SqlCommand^ SQL_command{};
			try
			{
				this->OpenConnection();
				query = "DELETE FROM dbo.HeroTypes WHERE TypeID = '" + TypeID +"'";
				SQL_command = gcnew SqlCommand(query, this->conn);
				SQL_command->ExecuteNonQuery();

				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были удалены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void DeleteRuneType(String^ TypeRuneID, Label^ text_errors)
	{
		if (TypeRuneID == "*Type Rune ID")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (!this->checkNumeric(TypeRuneID))
			text_errors->Text += "ID типа руны должно быть целочисленным. ";
		else
		{
			if (!this->checkID("dbo.TypeRunes", "TypeRuneID", TypeRuneID, 0))
				text_errors->Text += "Данный тип руны отсутствует в базе данных.";
			if (this->checkID("dbo.KeyRunes", "TypeRuneID", TypeRuneID, 1) || this->checkID("dbo.AdditionalRunes", "TypeRuneID", TypeRuneID, 1))
				text_errors->Text += "Данный объект нельзя удалить. Он связан с другими таблицами.";
		}
		if (text_errors->Text == "")
		{
			String^ query{};
			SqlCommand^ SQL_command{};
			try
			{
				this->OpenConnection();
				query = "DELETE FROM dbo.TypeRunes WHERE TypeRuneID = '" + TypeRuneID + "'";
				SQL_command = gcnew SqlCommand(query, this->conn);
				SQL_command->ExecuteNonQuery();

				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были удалены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void DeleteKeyRune(String^ KeyRuneID, Label^ text_errors)
	{
		if (KeyRuneID == "*Key Rune ID")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (!this->checkNumeric(KeyRuneID))
			text_errors->Text += "ID ключевой руны должно быть целочисленным. ";
		else
		{
			if (!this->checkID("dbo.KeyRunes", "KeyRuneID", KeyRuneID, 0))
				text_errors->Text += "Данная ключевая руна отсутствует в базе данных.";
			if (this->checkID("dbo.RunesAssemblies", "FirstKeyRune", KeyRuneID, 3) || this->checkID("dbo.RunesAssemblies", "SecondKeyRune", KeyRuneID, 4) ||
				this->checkID("dbo.RunesAssemblies", "ThirdKeyRune", KeyRuneID, 5) || this->checkID("dbo.RunesAssemblies", "FourthKeyRune", KeyRuneID, 6))
				text_errors->Text += "Данный объект нельзя удалить. Он связан с другими таблицами.";
		}
		if (text_errors->Text == "")
		{
			String^ query{};
			SqlCommand^ SQL_command{};
			try
			{
				this->OpenConnection();
				query = "DELETE FROM dbo.KeyRunes WHERE KeyRuneID = '" + KeyRuneID + "'";
				SQL_command = gcnew SqlCommand(query, this->conn);
				SQL_command->ExecuteNonQuery();

				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были удалены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void DeleteAdditionalRune(String^ AdditionalRuneID, Label^ text_errors)
	{
		if (AdditionalRuneID == "*Additional Rune ID")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (!this->checkNumeric(AdditionalRuneID))
			text_errors->Text += "ID дополнительной руны должно быть целочисленным. ";
		else
		{
			if (!this->checkID("dbo.AdditionalRunes", "AdditionalRuneID", AdditionalRuneID, 0))
				text_errors->Text += "Данная дополнительная руна отсутствует в базе данных.";
			if (this->checkID("dbo.RunesAssemblies", "FirstAdditionalRune", AdditionalRuneID, 7) || this->checkID("dbo.RunesAssemblies", "SecondAdditionalRune", AdditionalRuneID, 8))
				text_errors->Text += "Данный объект нельзя удалить. Он связан с другими таблицами.";
		}
		if (text_errors->Text == "")
		{
			String^ query{};
			SqlCommand^ SQL_command{};
			try
			{
				this->OpenConnection();
				query = "DELETE FROM dbo.AdditionalRunes WHERE AdditionalRuneID = '" + AdditionalRuneID + "'";
				SQL_command = gcnew SqlCommand(query, this->conn);
				SQL_command->ExecuteNonQuery();

				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были удалены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void DeleteAdaptiveRune(String^ AdaptiveRuneID, Label^ text_errors)
	{
		if (AdaptiveRuneID == "*Adaptive Rune ID")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (!this->checkNumeric(AdaptiveRuneID))
			text_errors->Text += "ID адаптивной руны должно быть целочисленным. ";
		else
		{
			if (!this->checkID("dbo.AdaptiveRunes", "AdaptiveRuneID", AdaptiveRuneID, 0))
				text_errors->Text += "Данная адаптивная руна отсутствует в базе данных.";
			if (this->checkID("dbo.RunesAssemblies", "FirstAdaptiveRune", AdaptiveRuneID, 9) || this->checkID("dbo.RunesAssemblies", "SecondAdaptiveRune", AdaptiveRuneID, 10) ||
				this->checkID("dbo.RunesAssemblies", "ThirdAdaptiveRune", AdaptiveRuneID, 11))
				text_errors->Text += "Данный объект нельзя удалить. Он связан с другими таблицами.";
		}
		if (text_errors->Text == "")
		{
			String^ query{};
			SqlCommand^ SQL_command{};
			try
			{
				this->OpenConnection();
				query = "DELETE FROM dbo.AdaptiveRunes WHERE AdaptiveRuneID = '" + AdaptiveRuneID + "'";
				SQL_command = gcnew SqlCommand(query, this->conn);
				SQL_command->ExecuteNonQuery();

				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были удалены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void DeleteItems(String^ ItemID, Label^ text_errors)
	{
		if (ItemID == "*Item Rune ID")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (!this->checkNumeric(ItemID))
			text_errors->Text += "ID предмета должно быть целочисленным. ";
		else
		{
			if (!this->checkID("dbo.Items", "ItemID", ItemID, 0))
				text_errors->Text += "Данный ID предмета отсутствует в базе данных.";
			if (this->checkID("dbo.ItemsAssemblies", "FirstItem", ItemID, 9) || this->checkID("dbo.ItemsAssemblies", "SecondAssemblies", ItemID, 10) ||
				this->checkID("dbo.ItemsAssemblies", "ThirgtItem", ItemID, 11) || this->checkID("dbo.ItemsAssemblies", "FourthAsseblirs", ItemID, 11) ||
				this->checkID("dbo.ItemsAssemblies", "FifthtItem", ItemID, 11) || this->checkID("dbo.SixthAssemblies", "FourthAsseblirs", ItemID, 11))
				text_errors->Text += "Данный объект нельзя удалить. Он связан с другими таблицами.";
		}
		if (text_errors->Text == "")
		{
			String^ query{};
			SqlCommand^ SQL_command{};
			try
			{
				this->OpenConnection();
				query = "DELETE FROM dbo.Items WHERE ItemID = '" + ItemID + "'";
				SQL_command = gcnew SqlCommand(query, this->conn);
				SQL_command->ExecuteNonQuery();

				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были удалены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void DeleteSpells(String^ SpellID, Label^ text_errors)
	{
		if (SpellID == "*Spell ID")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (!this->checkNumeric(SpellID))
			text_errors->Text += "ID заклинания должно быть целочисленным. ";
		else
		{
			if (!this->checkID("dbo.Spells", "SpellID", SpellID, 0))
				text_errors->Text += "Данное заклинание отсутствует в базе данных.";
			if (this->checkID("dbo.SpellsAssemblies", "FirstSpell", SpellID, 2) || this->checkID("dbo.SpellsAssemblies", "SecondSpell", SpellID, 3))
				text_errors->Text += "Данный объект нельзя удалить. Он связан с другими таблицами.";
		}
		if (text_errors->Text == "")
		{
			String^ query{};
			SqlCommand^ SQL_command{};
			try
			{
				this->OpenConnection();
				query = "DELETE FROM dbo.Spells WHERE SpellID = '" + SpellID + "'";
				SQL_command = gcnew SqlCommand(query, this->conn);
				SQL_command->ExecuteNonQuery();

				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были удалены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void DeleteRunesAssembl(String^ RunesAssemblyID, Label^ text_errors)
	{
		if (RunesAssemblyID == "*Runes Assembly ID")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (!this->checkNumeric(RunesAssemblyID))
			text_errors->Text += "ID сборки рун должно быть целочисленным. ";
		else
		{
			if (!this->checkID("dbo.RunesAssemblies", "RunesAssemblyID", RunesAssemblyID, 0))
				text_errors->Text += "Данная сборка рун отсутствует в базе данных.";
		}
		if (text_errors->Text == "")
		{
			String^ query{};
			SqlCommand^ SQL_command{};
			try
			{
				this->OpenConnection();
				query = "DELETE FROM dbo.RunesAssemblies WHERE RunesAssemblyID = '" + RunesAssemblyID + "'";
				SQL_command = gcnew SqlCommand(query, this->conn);
				SQL_command->ExecuteNonQuery();

				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были удалены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void DeleteItemsAssembl(String^ ItemsAssemblyID, Label^ text_errors)
	{
		if (ItemsAssemblyID == "*Items Assembly ID")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (!this->checkNumeric(ItemsAssemblyID))
			text_errors->Text += "ID сборки предметов должен быть целочисленным. ";
		else
		{
			if (!this->checkID("dbo.ItemsAssemblies", "ItemsAssemblyID", ItemsAssemblyID, 0))
				text_errors->Text += "Данная сборка предметов отсутствует в базе данных.";
		}
		if (text_errors->Text == "")
		{
			String^ query{};
			SqlCommand^ SQL_command{};
			try
			{
				this->OpenConnection();
				query = "DELETE FROM dbo.ItemsAssemblies WHERE ItemsAssemblyID = '" + ItemsAssemblyID + "'";
				SQL_command = gcnew SqlCommand(query, this->conn);
				SQL_command->ExecuteNonQuery();

				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были удалены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void DeleteSpellsAssembl(String^ SpellsAssemblyID, Label^ text_errors)
	{
		if (SpellsAssemblyID == "*Spells Assembly ID")
			text_errors->Text += "Не все обязательные поля были заполнены. ";
		if (!this->checkNumeric(SpellsAssemblyID))
			text_errors->Text += "ID сборки заклинаний должно быть целочисленным. ";
		else
		{
			if (!this->checkID("dbo.SpellsAssemblies", "SpellsAssemblyID", SpellsAssemblyID, 0))
				text_errors->Text += "Данная сборка заклинаний отсутствует в базе данных.";
		}
		if (text_errors->Text == "")
		{
			String^ query{};
			SqlCommand^ SQL_command{};
			try
			{
				this->OpenConnection();
				query = "DELETE FROM dbo.SpellsAssemblies WHERE SpellsAssemblyID = '" + SpellsAssemblyID + "'";
				SQL_command = gcnew SqlCommand(query, this->conn);
				SQL_command->ExecuteNonQuery();

				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были удалены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	//Изменение
	void UpdateHero(String^ ID, String^ HeroName, String^ HeroImage, String^ HeroHistory, String^ HeroSkillsDescr, String^ HeroType, Label^ text_errors)
	{
		if (ID == "*Update ID")
			text_errors->Text += "Необходимо указать, какой кортеж вы хотите изменить. ";
		else if (this->checkNumeric(ID))
		{
			if (!this->checkID("dbo.Heroes", "HeroID", ID, 0))
				text_errors->Text += "В таблице отсутствует герой с таким ID. ";
			if (HeroImage != "Hero Image (path to file)" && !this->checkPathImage(HeroImage))
				text_errors->Text += "По данному пути не существует искомого файла изображения. ";
			if (HeroType != "Hero Type" && !this->checkNumeric(HeroType))
			{
				text_errors->Text += "Тип героя должен содержать ID соответствующего типа в таблице TypesHero. ";
				return;
			}
			if (HeroType != "Hero Type" && !this->checkID("dbo.HeroTypes", "TypeID", HeroType, 0))
				text_errors->Text += "Такого типа героя не существует.";
			if (HeroName != "Hero Name" && HeroName->Length > 20)
				text_errors->Text += "Имя героя не должно содержать больше 20 символов.";
			if (HeroName != "HeroName" && HeroType != "Hero Type")
			{
				try
				{
					this->OpenConnection();
					String^ query = "SELECT * FROM dbo.Heroes WHERE (HeroName = '" + HeroName + "') AND (HeroType = '" + HeroType + "')";
					SqlDataReader^ reader = getReader(query);
					while (reader->Read())
					{
						text_errors->Text += "Нельзя создавать персонажа с тем же именем и типом. ";
						break;
					}
				}
				finally { this->CloseConnection(); }
			}
		}
		else
			text_errors->Text += "Изменяемый ID должен иметь численный тип. ";
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				if (HeroName != "Hero Name")
				{
					String^ query = "UPDATE dbo.Heroes SET HeroName = '" + HeroName + "' WHERE HeroID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (HeroType != "Hero Type")
				{
					String^ query = "UPDATE dbo.Heroes SET HeroType = '" + HeroType + "' WHERE HeroID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (HeroHistory != "Hero History")
				{
					String^ query = "UPDATE dbo.Heroes SET HeroHistory = '" + HeroHistory + "' WHERE HeroID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (HeroSkillsDescr != "Hero Skills Description")
				{
					String^ query = "UPDATE dbo.Heroes SET HeroSkillsDescr = '" + HeroSkillsDescr + "' WHERE HeroID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (HeroImage != "Hero Image (path to file)")
				{
					String^ query = "UPDATE dbo.Heroes SET HeroImage = (SELECT BulkColumn FROM Openrowset(BULK '" + HeroImage + "', Single_Blob) as img) WHERE HeroID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были обновлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void UpdateHeroInformation(String^ ID, String^ HeroID, String^ SkillsCombination, String^ SkillsTree, String^ SkillsRecharge, Label^ text_errors)
	{
		if (ID == "*Update ID")
			text_errors->Text += "Необходимо указать, какой кортеж вы хотите изменить. ";
		else if (this->checkNumeric(ID))
		{
			if (!this->checkID("dbo.HeroInformation", "HeroID", ID, 0))
			{
				text_errors->Text += "Информация о таком герое отсутствует в таблице. ";
				return;
			}
			if (HeroID != "new Hero ID" && !this->checkNumeric(HeroID))
			{
				text_errors->Text += "Вы должны указать целочисленный new Hero ID. ";
				return;
			}
			if (HeroID != "new Hero ID" && !this->checkID("dbo.Heroes", "HeroID", HeroID, 0))
			{
				text_errors->Text += "Информация о таком герое отсутствует в таблице Heroes. ";
				return;
			}
			if (HeroID != "new Hero ID" && this->checkID("dbo.HeroInformation", "HeroID", HeroID, 0))
			{
				text_errors->Text += "Информация о таком герое уже есть в таблице. ";
				return;
			}
			if (HeroID != "new Hero ID" && (this->checkID("dbo.ItemsAssemblies", "HeroID", ID, 1) || this->checkID("dbo.RunesAssemblies", "HeroID", ID, 1) || this->checkID("dbo.SpellsAssemblies", "HeroID", ID, 1)))
			{
				text_errors->Text += "Нельзя обновить HeroID, так как он связан с другими таблицами. ";
				return;
			}
		}
		else
			text_errors->Text += "Изменяемый ID должен иметь численный тип. ";
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				String^ query = "UPDATE dbo.HeroInformation SET HeroID = '" + HeroID + "' WHERE HeroID = '" + ID + "'";
				SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
				SQL_command->ExecuteNonQuery();
				if (SkillsCombination != "Skills Combination")
				{
					String^ query = "UPDATE dbo.HeroInformation SET SkillsCombination = '" + SkillsCombination + "' WHERE HeroID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (SkillsTree != "Skills Tree")
				{
					String^ query = "UPDATE dbo.HeroInformation SET SkillsTree = '" + SkillsTree + "' WHERE HeroID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (SkillsRecharge != "Skills Recharge")
				{
					String^ query = "UPDATE dbo.HeroInformation SET SkillsRecharge = '" + SkillsRecharge + "' WHERE HeroID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были обновлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void UpdateTypeHero(String^ ID, String^ TypeName, Label^ text_errors)
	{
		if (ID == "*Update ID")
			text_errors->Text += "Необходимо указать, какой кортеж вы хотите изменить. ";
		else if (this->checkNumeric(ID))
		{
			if (!this->checkID("dbo.HeroTypes", "TypeID", ID, 0))
			{
				text_errors->Text += "ID такого типа героя отсутствует в таблице. ";
				return;
			}
			if (TypeName != "Type Name")
			{
				if (TypeName->Length > 10)
					text_errors->Text += "Тип героя не должен содержать больше 10 символов.";
				if (this->checkName("dbo.HeroTypes", "TypeName", TypeName, 1))
					text_errors->Text += "Такой тип героя уже существует. ";
			}
		}
		else
			text_errors->Text += "Изменяемый ID должен иметь численный тип. ";
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				if (TypeName != "Type Name")
				{
					String^ query = "UPDATE dbo.HeroTypes SET TypeName = '" + TypeName + "' WHERE TypeID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были обновлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void UpdateTypeRune(String^ ID, String^ TypeRuneImage, String^ TypeRuneDescr, String^ TypeRuneName, Label^ text_errors)
	{
		if (ID == "*Update ID")
			text_errors->Text += "Необходимо указать, какой кортеж вы хотите изменить. ";
		else if (this->checkNumeric(ID))
		{
			if (!this->checkID("dbo.TypeRunes", "TypeRuneID", ID, 0))
				text_errors->Text += "ID такого типа руны отсутствует в таблице. ";
			if (TypeRuneName != "Type Rune Name" && TypeRuneName->Length > 30)
				text_errors->Text += "Имя руны не должно содержать больше 30 символов.";
			if (TypeRuneImage != "Type Rune Image (path to file)" && !this->checkPathImage(TypeRuneImage))
				text_errors->Text += "По данному пути не существует искомого файла изображения. ";
			if (TypeRuneName != "Type Rune Name" && this->checkName("dbo.TypeRunes", "TypeRuneName", TypeRuneName, 3))
				text_errors->Text += "Такой тип руны уже существует. ";
		}
		else
			text_errors->Text += "Изменяемый ID должен иметь численный тип. ";
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				if (TypeRuneName != "Type Rune Name")
				{
					String^ query = "UPDATE dbo.TypeRunes SET TypeRuneName = '" + TypeRuneName + "' WHERE TypeRuneID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (TypeRuneDescr != "Type Rune Description")
				{
					String^ query = "UPDATE dbo.TypeRunes SET TypeRuneDescr = '" + TypeRuneDescr + "' WHERE TypeRuneID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (TypeRuneImage != "Type Rune Image (path to file)")
				{
					String^ query = "UPDATE dbo.TypeRunes SET TypeRuneImage = (SELECT BulkColumn FROM Openrowset(BULK '" + TypeRuneImage + "', Single_Blob) as img) WHERE TypeRuneID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были обновлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void UpdateKeyRune(String^ ID, String^ TypeRuneID, String^ KeyRuneImage, String^ KeyRuneDescr, String^ KeyRuneName, Label^ text_errors)
	{
		if (ID == "*Update ID")
			text_errors->Text += "Необходимо указать, какой кортеж вы хотите изменить. ";
		else if (this->checkNumeric(ID))
		{
			if (!this->checkID("dbo.KeyRunes", "KeyRuneID", ID, 0))
				text_errors->Text += "ID такой ключевой руны отсутствует в таблице. ";
			if (KeyRuneName != "Key Rune Name" && KeyRuneName->Length > 50)
				text_errors->Text += "Имя ключевой руны не должно содержать больше 50 символов.";
			if (KeyRuneImage != "Key Rune Image (path to file)" && !this->checkPathImage(KeyRuneImage))
				text_errors->Text += "По данному пути не существует искомого файла изображения. ";
			if (KeyRuneName != "Key Rune Name" && this->checkName("dbo.KeyRunes", "KeyRuneName", KeyRuneName, 4))
				text_errors->Text += "Такая ключевая руна уже существует. ";
			if (TypeRuneID != "Type Rune ID" && !this->checkNumeric(TypeRuneID))
			{
				text_errors->Text += "Тип руны, к которому относится ключевая руна, должен содержать ID соответствующего типа руны в таблице TypeRunes. ";
				return;
			}
			if (TypeRuneID != "Type Rune ID" && !this->checkID("dbo.TypeRunes", "TypeRuneID", TypeRuneID, 0))
				text_errors->Text += "Такого типа руны не существует.";
		}
		else
			text_errors->Text += "Изменяемый ID должен иметь численный тип. ";
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				if (TypeRuneID != "Type Rune ID")
				{
					String^ query = "UPDATE dbo.KeyRunes SET TypeRuneID = '" + TypeRuneID + "' WHERE KeyRuneID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (KeyRuneDescr != "Key Rune Description")
				{
					String^ query = "UPDATE dbo.KeyRunes SET KeyRuneDescr = '" + KeyRuneDescr + "' WHERE KeyRuneID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (KeyRuneName != "Key Rune Name")
				{
					String^ query = "UPDATE dbo.KeyRunes SET KeyRuneName = '" + KeyRuneName + "' WHERE KeyRuneID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (KeyRuneImage != "Key Rune Image (path to file)")
				{
					String^ query = "UPDATE dbo.KeyRunes SET KeyRuneImage = (SELECT BulkColumn FROM Openrowset(BULK '" + KeyRuneImage + "', Single_Blob) as img) WHERE KeyRuneID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были обновлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void UpdateAdditionalRune(String^ ID, String^ TypeRuneID, String^ AdditionalRuneImage, String^ AdditionalRuneDescr, String^ AdditionalRuneName, Label^ text_errors)
	{
		if (ID == "*Update ID")
			text_errors->Text += "Необходимо указать, какой кортеж вы хотите изменить. ";
		else if (this->checkNumeric(ID))
		{
			if (!this->checkID("dbo.AdditionalRunes", "AdditionalRuneID", ID, 0))
				text_errors->Text += "ID такой дополнительной руны отсутствует в таблице. ";
			if (AdditionalRuneName != "Additional Rune Name" && AdditionalRuneName->Length > 50)
				text_errors->Text += "Имя дополнительной руны не должно содержать больше 50 символов.";
			if (AdditionalRuneImage != "Additional Rune Image (path to file)" && !this->checkPathImage(AdditionalRuneImage))
				text_errors->Text += "По данному пути не существует искомого файла изображения. ";
			if (AdditionalRuneName != "Additional Rune Name" && this->checkName("dbo.AdditionalRunes", "AdditionalRuneName", AdditionalRuneName, 4))
				text_errors->Text += "Такая дополнительная руна уже существует. ";
			if (TypeRuneID != "Type Rune ID" && !this->checkNumeric(TypeRuneID))
			{
				text_errors->Text += "Тип руны, к которому относится дополнительная руна, должен содержать ID соответствующего типа руны в таблице TypeRunes. ";
				return;
			}
			if (TypeRuneID != "Type Rune ID" && !this->checkID("dbo.TypeRunes", "TypeRuneID", TypeRuneID, 0))
				text_errors->Text += "Такого типа руны не существует.";
		}
		else
			text_errors->Text += "Изменяемый ID должен иметь численный тип. ";
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				if (TypeRuneID != "Type Rune ID")
				{
					String^ query = "UPDATE dbo.AdditionalRunes SET TypeRuneID = '" + TypeRuneID + "' WHERE AdditionalRuneID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (AdditionalRuneDescr != "Additional Rune Description")
				{
					String^ query = "UPDATE dbo.AdditionalRunes SET AdditionalRuneDescr = '" + AdditionalRuneDescr + "' WHERE AdditionalRuneID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (AdditionalRuneName != "Additional Rune Name")
				{
					String^ query = "UPDATE dbo.AdditionalRunes SET AdditionalRuneName = '" + AdditionalRuneName + "' WHERE AdditionalRuneID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (AdditionalRuneImage != "Additional Rune Image (path to file)")
				{
					String^ query = "UPDATE dbo.AdditionalRunes SET AdditionalRuneImage = (SELECT BulkColumn FROM Openrowset(BULK '" + AdditionalRuneImage + "', Single_Blob) as img) WHERE AdditionalRuneID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были обновлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void UpdateAdaptiveRune(String^ ID, String^ AdaptiveRuneImage, String^ AdaptiveRuneDescr, String^ AdaptiveRuneName, Label^ text_errors)
	{
		if (ID == "*Update ID")
			text_errors->Text += "Необходимо указать, какой кортеж вы хотите изменить. ";
		else if (this->checkNumeric(ID))
		{
			if (!this->checkID("dbo.AdaptiveRunes", "AdaptiveRuneID", ID, 0))
				text_errors->Text += "ID такой адаптивной руны отсутствует в таблице. ";
			if (AdaptiveRuneName != "Adaptive Rune Name" && AdaptiveRuneName->Length > 30)
				text_errors->Text += "Имя адаптивной руны не должно содержать больше 30 символов.";
			if (AdaptiveRuneImage != "Adaptive Rune Image (path to file)" && !this->checkPathImage(AdaptiveRuneImage))
				text_errors->Text += "По данному пути не существует искомого файла изображения. ";
		}
		else
			text_errors->Text += "Изменяемый ID должен иметь численный тип. ";
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				if (AdaptiveRuneDescr != "Adaptive Rune Description")
				{
					String^ query = "UPDATE dbo.AdaptiveRunes SET AdaptiveRuneDescr = '" + AdaptiveRuneDescr + "' WHERE AdaptiveRuneID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (AdaptiveRuneName != "Adaptive Rune Name")
				{
					String^ query = "UPDATE dbo.AdaptiveRunes SET AdaptiveRuneName = '" + AdaptiveRuneName + "' WHERE AdaptiveRuneID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (AdaptiveRuneImage != "Adaptive Rune Image (path to file)")
				{
					String^ query = "UPDATE dbo.AdaptiveRunes SET AdaptiveRuneImage = (SELECT BulkColumn FROM Openrowset(BULK '" + AdaptiveRuneImage + "', Single_Blob) as img) WHERE AdaptiveRuneID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были обновлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void UpdateItem(String^ ID, String^ ItemImage, String^ ItemDescr, String^ ActiveCharacteristics, String^ PassiveCharacteristics, String^ GameStage, String^ ItemType, String^ ItemCost, String^ ItemName, Label^ text_errors)
	{
		int cost{};
		if (ID == "*Update ID")
			text_errors->Text += "Необходимо указать, какой кортеж вы хотите изменить. ";
		else if (this->checkNumeric(ID))
		{
			if (!this->checkID("dbo.Items", "ItemID", ID, 0))
				text_errors->Text += "ID такого предмета отсутствует в таблице. ";
			if (ItemName != "ItemName" && ItemName->Length > 30)
				text_errors->Text += "Имя предмета не должно содержать больше 10 символов.";
			if (ItemImage != "Item Image (path to file)" && !this->checkPathImage(ItemImage))
				text_errors->Text += "По данному пути не существует искомого файла изображения. ";
			if (ItemCost != "Item Cost" && !this->checkNumeric(ItemCost))
				text_errors->Text += "Цена предмета должна содержать числовое значение. ";
			else
				for (int i{}; i < ItemCost->Length; i++)
				{
					cost += static_cast<int>((ItemCost[i] - '0') * pow(10, ItemCost->Length - i - 1));
				}
			if (ItemType != "Item Type" && !this->checkNumeric(ItemType))
			{
				text_errors->Text += "Тип предмета должен содержать ID соответствующего типа героя в таблице HeroTypes. ";
				return;
			}
			if (ItemType != "Item Type" && !this->checkID("dbo.HeroTypes", "TypeID", ItemType, 0))
				text_errors->Text += "Такого типа героя не существует.";
			if (ItemName != "ItemName" && this->checkID("dbo.Items", "ItemName", ItemName, 8))
				text_errors->Text += "Такой предмет уже существует. ";
		}
		else
			text_errors->Text += "Изменяемый ID должен иметь численный тип. ";
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				if (ItemDescr != "Item Description")
				{
					String^ query = "UPDATE dbo.Items SET ItemDescr = '" + ItemDescr + "' WHERE ItemID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (ActiveCharacteristics != "Active Characteristics")
				{
					String^ query = "UPDATE dbo.Items SET ActiveCharacteristics = '" + ActiveCharacteristics + "' WHERE ItemID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (PassiveCharacteristics != "Passive Characteristics")
				{
					String^ query = "UPDATE dbo.Items SET PassiveCharacteristics = '" + PassiveCharacteristics + "' WHERE ItemID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (GameStage != "Game Stage")
				{
					String^ query = "UPDATE dbo.Items SET GameStage = '" + GameStage + "' WHERE ItemID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (ItemType != "Item Type")
				{
					String^ query = "UPDATE dbo.Items SET ItemType = '" + ItemType + "' WHERE ItemID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (ItemCost != "Item Cost")
				{
					String^ query = "UPDATE dbo.Items SET ItemCost = '" + ItemCost + "' WHERE ItemID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (ItemName != "Item Name")
				{
					String^ query = "UPDATE dbo.Items SET ItemName = '" + ItemName + "' WHERE ItemID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (ItemImage != "Item Image (path to file)")
				{
					String^ query = "UPDATE dbo.Items SET ItemImage = (SELECT BulkColumn FROM Openrowset(BULK '" + ItemImage + "', Single_Blob) as img) WHERE ItemID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были обновлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void UpdateSpell(String^ ID, String^ SpellImage, String^ SpellName, String^ SpellDescr, String^ SpellRecharge, String^ SpellLine, Label^ text_errors)
	{
		if (ID == "*Update ID")
			text_errors->Text += "Необходимо указать, какой кортеж вы хотите изменить. ";
		else if (this->checkNumeric(ID))
		{
			if (!this->checkID("dbo.Spells", "SpellID", ID, 0))
				text_errors->Text += "ID такого предмета отсутствует в таблице. ";
			if (SpellName != "Spell Name" && SpellName->Length > 25)
				text_errors->Text += "Имя предмета не должно содержать больше 25 символов.";
			if (SpellRecharge != "Spell Recharge" && SpellRecharge->Length > 10)
				text_errors->Text += "Перезарядка предмета не должна содержать больше 10 символов.";
			if (SpellImage != "Spell Image (path to file)" && !this->checkPathImage(SpellImage))
				text_errors->Text += "По данному пути не существует искомого файла изображения. ";
			if (SpellName != "Spell Name" && this->checkID("dbo.Spells", "SpellName", SpellName, 2))
				text_errors->Text += "Такое заклинание уже существует. ";
		}
		else
			text_errors->Text += "Изменяемый ID должен иметь численный тип. ";
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				if (SpellName != "Spell Name")
				{
					String^ query = "UPDATE dbo.Spells SET SpellName = '" + SpellName + "' WHERE SpellID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (SpellDescr != "Spell Description")
				{
					String^ query = "UPDATE dbo.Spells SET SpellDescr = '" + SpellDescr + "' WHERE SpellID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (SpellRecharge != "Spell Recharge")
				{
					String^ query = "UPDATE dbo.Spells SET SpellRecharge = '" + SpellRecharge + "' WHERE SpellID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (SpellLine != "Spell Line")
				{
					String^ query = "UPDATE dbo.Spells SET SpellLine = '" + SpellLine + "' WHERE SpellID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (SpellImage != "Spell Image (path to file)")
				{
					String^ query = "UPDATE dbo.Spells SET SpellImage = (SELECT BulkColumn FROM Openrowset(BULK '" + SpellImage + "', Single_Blob) as img) WHERE SpellID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были обновлены!";
				
			}
			finally { this->CloseConnection(); }
		}
	}
	void UpdateRuneAssembl(String^ ID, String^ HeroID, String^ RuneType, String^ FirstKeyRune, String^ SecondKeyRune, String^ ThirdKeyRune, String^ FourthKeyRune, String^ FirstAdditionalRune, String^ SecondAdditionalRune, String^ FirstAdaptiveRune, String^ SecondAdaptiveRune, String^ ThirdAdaptiveRune, Label^ text_errors)
	{
		if (ID == "*Update ID")
			text_errors->Text += "Необходимо указать, какой кортеж вы хотите изменить. ";
		else if (this->checkNumeric(ID))
		{
			if (!this->checkID("dbo.RunesAssemblies", "RunesAssemblyID", ID, 0))
				text_errors->Text += "ID такой сборки рун отсутствует в таблице. ";

			if ((HeroID != "HeroID" && !this->checkNumeric(HeroID)) || (RuneType != "Rune Type" && !this->checkNumeric(RuneType)) || 
			   (FirstKeyRune != "First Key Rune" && !this->checkNumeric(FirstKeyRune)) || (SecondKeyRune != "Second Key Rune" && !this->checkNumeric(SecondKeyRune)) || 
			   (ThirdKeyRune != "Third Key Rune" && !this->checkNumeric(ThirdKeyRune)) || (FourthKeyRune != "Fourth Key Rune" && !this->checkNumeric(FourthKeyRune)) || 
			   (FirstAdditionalRune != "First Additional Rune" && !this->checkNumeric(FirstAdditionalRune)) || (SecondAdditionalRune != "Second Additional Rune" && !this->checkNumeric(SecondAdditionalRune)) || 
			   (FirstAdaptiveRune != "First Adaptive Rune" && !this->checkNumeric(FirstAdaptiveRune)) || (SecondAdaptiveRune != "Second Adaptive Rune" && !this->checkNumeric(SecondAdaptiveRune)) || 
			   (ThirdAdaptiveRune != "Third Adaptive Rune" && !this->checkNumeric(ThirdAdaptiveRune)))
			{
			   text_errors->Text += "Все значения изменяемых полей должны быть числовыми. ";
			   return;
			}
			if ((HeroID != "Hero ID" && !this->checkID("dbo.HeroInformation", "HeroID", HeroID, 0)) || (RuneType != "Rune Type" && !this->checkID("dbo.TypeRunes", "TypeRuneID", RuneType, 0)) ||
				(FirstKeyRune != "First Key Rune" && !this->checkID("dbo.KeyRunes", "KeyRuneID", FirstKeyRune, 0)) || (SecondKeyRune != "Second Key Rune" && !this->checkID("dbo.KeyRunes", "KeyRuneID", SecondKeyRune, 0)) || 
				(ThirdKeyRune != "Third Key Rune" && !this->checkID("dbo.KeyRunes", "KeyRuneID", ThirdKeyRune, 0)) || (FourthKeyRune != "Fourth Key Rune" && !this->checkID("dbo.KeyRunes", "KeyRuneID", FourthKeyRune, 0)) || 
				(FirstAdditionalRune != "First Additional Rune" && !this->checkID("dbo.AdditionalRunes", "AdditionalRuneID", FirstAdditionalRune, 0)) ||
				(SecondAdditionalRune != "Second Additional Rune" && !this->checkID("dbo.AdditionalRunes", "AdditionalRuneID", SecondAdditionalRune, 0)) || 
				(FirstAdaptiveRune != "First Adaptive Rune" && !this->checkID("dbo.AdaptiveRunes", "AdaptiveRuneID", FirstAdaptiveRune, 0)) ||
				(SecondAdaptiveRune != "Second Adaptive Rune" && !this->checkID("dbo.AdaptiveRunes", "AdaptiveRuneID", SecondAdaptiveRune, 0)) || 
				(ThirdAdaptiveRune != "Third Adaptive Rune" && !this->checkID("dbo.AdaptiveRunes", "AdaptiveRuneID", ThirdAdaptiveRune, 0)))
				text_errors->Text += "Какой-то из введенных Вами для изменения ID составляющих не существует. ";
		}
		else
			text_errors->Text += "Изменяемый ID должен иметь численный тип. ";
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				if (HeroID != "Hero ID")
				{
					String^ query = "UPDATE dbo.RunesAssemblies SET HeroID = '" + HeroID + "' WHERE RunesAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (RuneType != "Rune Type")
				{
					String^ query = "UPDATE dbo.RunesAssemblies SET RuneType = '" + RuneType + "' WHERE RunesAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (FirstKeyRune != "First Key Rune")
				{
					String^ query = "UPDATE dbo.RunesAssemblies SET FirstKeyRune = '" + FirstKeyRune + "' WHERE RunesAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (SecondKeyRune != "Second Key Rune")
				{
					String^ query = "UPDATE dbo.RunesAssemblies SET SecondKeyRune = '" + SecondKeyRune + "' WHERE RunesAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (ThirdKeyRune != "Third Key Rune")
				{
					String^ query = "UPDATE dbo.RunesAssemblies SET ThirdKeyRune = '" + ThirdKeyRune + "' WHERE RunesAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (FourthKeyRune != "Fourth Key Rune")
				{
					String^ query = "UPDATE dbo.RunesAssemblies SET FourthKeyRune = '" + FourthKeyRune + "' WHERE RunesAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (FirstAdditionalRune != "First Additional Rune")
				{
					String^ query = "UPDATE dbo.RunesAssemblies SET FirstAdditionalRune = '" + FirstAdditionalRune + "' WHERE RunesAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (SecondAdditionalRune != "Second Additional Rune")
				{
					String^ query = "UPDATE dbo.RunesAssemblies SET SecondAdditionalRune = '" + SecondAdditionalRune + "' WHERE RunesAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (FirstAdaptiveRune != "First Adaptive Rune")
				{
					String^ query = "UPDATE dbo.RunesAssemblies SET FirstAdaptiveRune = '" + FirstAdaptiveRune + "' WHERE RunesAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (SecondAdaptiveRune != "Second Adaptive Rune")
				{
					String^ query = "UPDATE dbo.RunesAssemblies SET SecondAdaptiveRune = '" + SecondAdaptiveRune + "' WHERE RunesAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (ThirdAdaptiveRune != "Third Adaptive Rune")
				{
					String^ query = "UPDATE dbo.RunesAssemblies SET ThirdAdaptiveRune = '" + ThirdAdaptiveRune + "' WHERE RunesAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были обновлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void UpdateItemAssembl(String^ ID, String^ HeroID, String^ FirstItem, String^ SecondItem, String^ ThirdItem, String^ FourthItem, String^ FifthItem, String^ SixthItem, Label^ text_errors)
	{
		if (ID == "*Update ID")
			text_errors->Text += "Необходимо указать, какой кортеж вы хотите изменить. ";
		else if (this->checkNumeric(ID))
		{
			if (!this->checkID("dbo.ItemsAssemblies", "ItemsAssemblyID", ID, 0))
				text_errors->Text += "ID такой сборки предметов отсутствует в таблице. ";
			if ((HeroID != "Hero ID" && !this->checkNumeric(HeroID)) || (FirstItem != "First Item" && !this->checkNumeric(FirstItem)) || (SecondItem != "Second Item" && !this->checkNumeric(SecondItem)) || 
				(ThirdItem != "Third Item" && !this->checkNumeric(ThirdItem)) || (FourthItem != "Fourth Item" && !this->checkNumeric(FourthItem)) || 
				(FifthItem != "Fifth Item" && !this->checkNumeric(FifthItem)) || (SixthItem != "Sixth Item" && !this->checkNumeric(SixthItem)))
			{
				text_errors->Text += "Все значения изменяемых полей должны быть числовыми. ";
				return;
			}
			if ((HeroID != "Hero ID" && !this->checkID("dbo.HeroInformation", "HeroID", HeroID, 0)) || (FirstItem != "First Item" && !this->checkID("dbo.Items", "ItemID", FirstItem, 0)) ||
				(SecondItem != "Second Item" && !this->checkID("dbo.Items", "ItemID", SecondItem, 0)) || (ThirdItem != "Third Item" && !this->checkID("dbo.Items", "ItemID", ThirdItem, 0)) || 
				(FourthItem != "Fourth Item" && !this->checkID("dbo.Items", "ItemID", FourthItem, 0)) || (FifthItem != "Fifth Item" && !this->checkID("dbo.Items", "ItemID", FifthItem, 0)) ||
				(SixthItem != "Sixth Item" && !this->checkID("dbo.Items", "ItemID", SixthItem, 0)))
				text_errors->Text += "Какой-то из введенных Вами изменяемых ID составляющих не существует. ";
		}
		else
			text_errors->Text += "Изменяемый ID должен иметь численный тип. ";
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				if (HeroID != "Hero ID")
				{
					String^ query = "UPDATE dbo.ItemsAssemblies SET HeroID = '" + HeroID + "' WHERE ItemsAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (FirstItem != "First Item")
				{
					String^ query = "UPDATE dbo.ItemsAssemblies SET FirstItem = '" + FirstItem + "' WHERE ItemsAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (SecondItem != "Second Item")
				{
					String^ query = "UPDATE dbo.ItemsAssemblies SET SecondItem = '" + SecondItem + "' WHERE ItemsAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (ThirdItem != "Third Item")
				{
					String^ query = "UPDATE dbo.ItemsAssemblies SET ThirdItem = '" + ThirdItem + "' WHERE ItemsAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (FourthItem != "Fourth Item")
				{
					String^ query = "UPDATE dbo.ItemsAssemblies SET FourthItem = '" + FourthItem + "' WHERE ItemsAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (FifthItem != "Fifth Item")
				{
					String^ query = "UPDATE dbo.ItemsAssemblies SET FifthItem = '" + FifthItem + "' WHERE ItemsAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (SixthItem != "Sixth Item")
				{
					String^ query = "UPDATE dbo.ItemsAssemblies SET SixthItem = '" + SixthItem + "' WHERE ItemsAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были обновлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
	void UpdateSpellAssembl(String^ ID, String^ HeroID, String^ FirstSpell, String^ SecondSpell, Label^ text_errors)
	{
		if (ID == "*Update ID")
			text_errors->Text += "Необходимо указать, какой кортеж вы хотите изменить. ";
		else if (this->checkNumeric(ID))
		{
			if (!this->checkID("dbo.SpellsAssemblies", "SpellsAssemblyID", ID, 0))
				text_errors->Text += "ID такой ключевой руны отсутствует в таблице. ";
			if ((HeroID != "Hero ID" && !this->checkNumeric(HeroID)) || (FirstSpell != "First Spell" && !this->checkNumeric(FirstSpell)) || (SecondSpell != "Second Spell" && !this->checkNumeric(SecondSpell)))
			{
				text_errors->Text += "Все значения полей должны быть числовыми. ";
				return;
			}
			if ((HeroID != "Hero ID" && !this->checkID("dbo.HeroInformation", "HeroID", HeroID, 0)) || 
				(FirstSpell != "First Spell" && !this->checkID("dbo.Spells", "SpellID", FirstSpell, 0)) ||
				(SecondSpell != "Second Spell" && !this->checkID("dbo.Spells", "SpellID", SecondSpell, 0)))
				text_errors->Text += "Какой-то из введенных Вами изменяемых ID составляющих не существует. ";
		}
		else
			text_errors->Text += "Изменяемый ID должен иметь численный тип. ";
		if (text_errors->Text == "")
		{
			try
			{
				this->OpenConnection();
				if (HeroID != "Hero ID")
				{
					String^ query = "UPDATE dbo.SpellsAssemblies SET HeroID = '" + HeroID + "' WHERE SpellsAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (FirstSpell != "First Spell")
				{
					String^ query = "UPDATE dbo.SpellsAssemblies SET FirstSpell = '" + FirstSpell + "' WHERE SpellsAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				if (SecondSpell != "Second Spell")
				{
					String^ query = "UPDATE dbo.SpellsAssemblies SET SecondSpell = '" + SecondSpell + "' WHERE SpellsAssemblyID = '" + ID + "'";
					SqlCommand^ SQL_command = gcnew SqlCommand(query, this->conn);
					SQL_command->ExecuteNonQuery();
				}
				text_errors->ForeColor = System::Drawing::Color::ForestGreen;
				text_errors->Text = "Данные были обновлены!";
			}
			finally { this->CloseConnection(); }
		}
	}
};