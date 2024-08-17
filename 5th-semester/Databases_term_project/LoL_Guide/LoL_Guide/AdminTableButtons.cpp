#include "AdminTableButtons.h"
#include "DataBaseFunctions.h"
#include "AdminPanelTextBoxes.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

System::Void AdminTableButtons::table_button_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	this->descr_panel->Controls->Clear();
	this->panel_for_textBoxes->Controls->Clear();

	this->descr_panel->Controls->Add(this->panel_for_textBoxes);
	this->descr_panel->Controls->Add(this->add_btn);
	this->descr_panel->Controls->Add(this->del_btn);
	this->descr_panel->Controls->Add(this->edit_btn);
	this->descr_panel->Controls->Add(this->accept_btn);
	this->descr_panel->Controls->Add(this->data);
	this->text_errors->Text = "";
	this->text_errors->ForeColor = System::Drawing::Color::Red;
	DataBaseFunctions^ func = gcnew DataBaseFunctions();
	func->getDataGridView(this->identificator_btn, this->data);
}
System::Void AdminTableButtons::del_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	this->put_btn = "delete";
	this->panel_for_textBoxes->Controls->Clear();
	this->panel_for_textBoxes->Controls->Add(this->text_errors);
	this->panel_for_textBoxes->Controls->Add(this->help_inf);

	this->text_errors->Text = "";
	this->text_errors->ForeColor = System::Drawing::Color::Red;

	if (this->identificator_btn == "Герои")
	{
		AdminPanelTextBoxes^ text_HeroID = gcnew AdminPanelTextBoxes(5, 5, "*Hero ID");
		this->text_string1 = text_HeroID->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
	}
	else if (this->identificator_btn == "Информация о героях")
	{
		AdminPanelTextBoxes^ text_HeroID = gcnew AdminPanelTextBoxes(5, 5, "*Hero ID");
		this->text_string1 = text_HeroID->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
	}
	else if (this->identificator_btn == "Типы героев")
	{
		AdminPanelTextBoxes^ text_TypeID = gcnew AdminPanelTextBoxes(5, 5, "*Type ID");
		this->text_string1 = text_TypeID->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
	}
	else if (this->identificator_btn == "Типы рун")
	{
		AdminPanelTextBoxes^ text_TypeRuneID = gcnew AdminPanelTextBoxes(5, 5, "*Type Rune ID");
		this->text_string1 = text_TypeRuneID->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
	}
	else if (this->identificator_btn == "Ключевые руны")
	{
		AdminPanelTextBoxes^ text_KeyRuneID = gcnew AdminPanelTextBoxes(5, 5, "*Key Rune ID");
		this->text_string1 = text_KeyRuneID->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
	}
	else if (this->identificator_btn == "Дополнительные руны")
	{
		AdminPanelTextBoxes^ text_AdditionalRuneID = gcnew AdminPanelTextBoxes(5, 5, "*Additional Rune ID");
		this->text_string1 = text_AdditionalRuneID->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
	}
	else if (this->identificator_btn == "Адаптивные руны")
	{
		AdminPanelTextBoxes^ text_AdaptiveRuneID = gcnew AdminPanelTextBoxes(5, 5, "*Adaptive Rune ID");
		this->text_string1 = text_AdaptiveRuneID->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
	}
	else if (this->identificator_btn == "Предметы")
	{
		AdminPanelTextBoxes^ text_ItemID = gcnew AdminPanelTextBoxes(5, 5, "*Item ID");
		this->text_string1 = text_ItemID->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
	}
	else if (this->identificator_btn == "Заклинания")
	{
		AdminPanelTextBoxes^ text_SpellID = gcnew AdminPanelTextBoxes(5, 5, "*Spell ID");
		this->text_string1 = text_SpellID->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
	}
	else if (this->identificator_btn == "Сборки рун")
	{
		AdminPanelTextBoxes^ text_RuneAssembliesID = gcnew AdminPanelTextBoxes(5, 5, "*Runes Assembly ID");
		this->text_string1 = text_RuneAssembliesID->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
	}
	else if (this->identificator_btn == "Сборки предметов")
	{
		AdminPanelTextBoxes^ text_ItemAssembliesID = gcnew AdminPanelTextBoxes(5, 5, "*Items Assembly ID");
		this->text_string1 = text_ItemAssembliesID->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
	}
	else
	{
		AdminPanelTextBoxes^ text_SpellAssembliesID = gcnew AdminPanelTextBoxes(5, 5, "*Spells Assembly ID");
		this->text_string1 = text_SpellAssembliesID->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
	}
}
System::Void AdminTableButtons::add_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	this->put_btn = "add";
	this->panel_for_textBoxes->Controls->Clear();
	this->panel_for_textBoxes->Controls->Add(this->text_errors);
	this->panel_for_textBoxes->Controls->Add(this->help_inf);

	this->text_errors->Text = "";
	this->text_errors->ForeColor = System::Drawing::Color::Red;

	if (this->identificator_btn == "Герои")
	{
		AdminPanelTextBoxes^ text_heroName = gcnew AdminPanelTextBoxes(5, 5, "*Hero Name");
		this->text_string1 = text_heroName->getTextBox();
		AdminPanelTextBoxes^ text_heroHistory = gcnew AdminPanelTextBoxes(220, 5, "*Hero History");
		this->text_string2 = text_heroHistory->getTextBox();
		this->text_string2->Multiline = true;
		this->text_string2->Size = System::Drawing::Size(300, 130);
		this->text_string2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_heroSkillsDescr = gcnew AdminPanelTextBoxes(530, 5, "*Hero Skills Description");
		this->text_string3 = text_heroSkillsDescr->getTextBox();
		this->text_string3->Multiline = true;
		this->text_string3->Size = System::Drawing::Size(295, 130);
		this->text_string3->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_heroType = gcnew AdminPanelTextBoxes(5, 30, "*Hero Type");
		this->text_string4 = text_heroType->getTextBox();
		AdminPanelTextBoxes^ text_heroImage = gcnew AdminPanelTextBoxes(5, 55, "*Hero Image (path to file)");
		this->text_string5 = text_heroImage->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
		this->panel_for_textBoxes->Controls->Add(this->text_string4);
		this->panel_for_textBoxes->Controls->Add(this->text_string5);
	}
	else if (this->identificator_btn == "Информация о героях")
	{
		AdminPanelTextBoxes^ text_heroID = gcnew AdminPanelTextBoxes(5, 90, "*Hero ID");
		this->text_string1 = text_heroID->getTextBox();
		AdminPanelTextBoxes^ text_skillsCombination = gcnew AdminPanelTextBoxes(5, 5, "Skills Combination");
		this->text_string2 = text_skillsCombination->getTextBox();
		this->text_string2->Multiline = true;
		this->text_string2->Size = System::Drawing::Size(200, 80);
		this->text_string2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_skillsTree = gcnew AdminPanelTextBoxes(220, 5, "Skills Tree");
		this->text_string3 = text_skillsTree->getTextBox();
		this->text_string3->Multiline = true;
		this->text_string3->Size = System::Drawing::Size(300, 130);
		this->text_string3->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_skillsRecharge = gcnew AdminPanelTextBoxes(530, 5, "*Skills Recharge");
		this->text_string4 = text_skillsRecharge->getTextBox();
		this->text_string4->Multiline = true;
		this->text_string4->Size = System::Drawing::Size(300, 130);
		this->text_string4->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
		this->panel_for_textBoxes->Controls->Add(this->text_string4);
	}
	else if (this->identificator_btn == "Типы героев")
	{
		AdminPanelTextBoxes^ text_heroID = gcnew AdminPanelTextBoxes(5, 5, "*Type Name");
		this->text_string1 = text_heroID->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
	}
	else if (this->identificator_btn == "Типы рун")
	{
		AdminPanelTextBoxes^ text_typeRuneImage = gcnew AdminPanelTextBoxes(5, 5, "*Type Rune Image (path to file)");
		this->text_string1 = text_typeRuneImage->getTextBox();
		AdminPanelTextBoxes^ text_typeRuneDescr = gcnew AdminPanelTextBoxes(220, 5, "*Type Rune Description");
		this->text_string2 = text_typeRuneDescr->getTextBox();
		this->text_string2->Multiline = true;
		this->text_string2->Size = System::Drawing::Size(200, 80);
		this->text_string2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_typeRuneName = gcnew AdminPanelTextBoxes(5, 30, "*Type Rune Name");
		this->text_string3 = text_typeRuneName->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
	}
	else if (this->identificator_btn == "Ключевые руны")
	{
		AdminPanelTextBoxes^ text_typeRuneID = gcnew AdminPanelTextBoxes(5, 5, "*Type Rune ID");
		this->text_string1 = text_typeRuneID->getTextBox();
		AdminPanelTextBoxes^ text_KeyRuneImage = gcnew AdminPanelTextBoxes(5, 30, "*Key Rune Image (path to file)");
		this->text_string2 = text_KeyRuneImage->getTextBox();
		AdminPanelTextBoxes^ text_KeyRuneDescr = gcnew AdminPanelTextBoxes(220, 5, "*Key Rune Description");
		this->text_string3 = text_KeyRuneDescr->getTextBox();
		this->text_string3->Multiline = true;
		this->text_string3->Size = System::Drawing::Size(300, 130);
		this->text_string3->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_KeyRuneName = gcnew AdminPanelTextBoxes(5, 55, "*Key Rune Name");
		this->text_string4 = text_KeyRuneName->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
		this->panel_for_textBoxes->Controls->Add(this->text_string4);
	}
	else if (this->identificator_btn == "Дополнительные руны")
	{
		AdminPanelTextBoxes^ text_AdditionalRuneID = gcnew AdminPanelTextBoxes(5, 5, "*Type Rune ID");
		this->text_string1 = text_AdditionalRuneID->getTextBox();
		AdminPanelTextBoxes^ text_AdditionalRuneImage = gcnew AdminPanelTextBoxes(5, 30, "*Additional Rune Image (path to file)");
		this->text_string2 = text_AdditionalRuneImage->getTextBox();
		AdminPanelTextBoxes^ text_AdditionalRuneDescr = gcnew AdminPanelTextBoxes(220, 5, "*Additional Rune Description");
		this->text_string3 = text_AdditionalRuneDescr->getTextBox();
		this->text_string3->Multiline = true;
		this->text_string3->Size = System::Drawing::Size(300, 130);
		this->text_string3->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_AdditionalRuneName = gcnew AdminPanelTextBoxes(5, 55, "*Additional Rune Name");
		this->text_string4 = text_AdditionalRuneName->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
		this->panel_for_textBoxes->Controls->Add(this->text_string4);
	}
	else if (this->identificator_btn == "Адаптивные руны")
	{
		AdminPanelTextBoxes^ text_AdaptiveRuneImage = gcnew AdminPanelTextBoxes(5, 5, "*Adaptive Rune Image (path to file)");
		this->text_string1 = text_AdaptiveRuneImage->getTextBox();
		AdminPanelTextBoxes^ text_AdaptiveRuneDescr = gcnew AdminPanelTextBoxes(220, 5, "*Adaptive Rune Description");
		this->text_string2 = text_AdaptiveRuneDescr->getTextBox();
		this->text_string2->Multiline = true;
		this->text_string2->Size = System::Drawing::Size(300, 130);
		this->text_string2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_AdaptiveRuneName = gcnew AdminPanelTextBoxes(5, 30, "*Adaptive Rune Name");
		this->text_string3 = text_AdaptiveRuneName->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
	}
	else if (this->identificator_btn == "Предметы")
	{
		AdminPanelTextBoxes^ text_ItemImage = gcnew AdminPanelTextBoxes(5, 5, "*Item Image (path to file)");
		this->text_string1 = text_ItemImage->getTextBox();
		AdminPanelTextBoxes^ text_ItemDescr = gcnew AdminPanelTextBoxes(220, 5, "Item Description");
		this->text_string2 = text_ItemDescr->getTextBox();
		this->text_string2->Multiline = true;
		this->text_string2->Size = System::Drawing::Size(300, 130);
		this->text_string2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_ActiveCharacteristics = gcnew AdminPanelTextBoxes(530, 5, "Active Characteristics");
		this->text_string3 = text_ActiveCharacteristics->getTextBox();
		this->text_string3->Multiline = true;
		this->text_string3->Size = System::Drawing::Size(300, 50);
		this->text_string3->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_PassiveCharacteristics = gcnew AdminPanelTextBoxes(530, 60, "Passive Characteristics");
		this->text_string4 = text_PassiveCharacteristics->getTextBox();
		this->text_string4->Multiline = true;
		this->text_string4->Size = System::Drawing::Size(300, 50);
		this->text_string4->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_GameStage = gcnew AdminPanelTextBoxes(5, 30, "Game Stage");
		this->text_string5 = text_GameStage->getTextBox();
		AdminPanelTextBoxes^ text_ItemType = gcnew AdminPanelTextBoxes(5, 55, "*Item Type");
		this->text_string6 = text_ItemType->getTextBox();
		AdminPanelTextBoxes^ text_ItemCost = gcnew AdminPanelTextBoxes(5, 80, "*Item Cost");
		this->text_string7 = text_ItemCost->getTextBox();
		AdminPanelTextBoxes^ text_ItemName = gcnew AdminPanelTextBoxes(530, 115, "*Item Name");
		this->text_string8 = text_ItemName->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
		this->panel_for_textBoxes->Controls->Add(this->text_string4);
		this->panel_for_textBoxes->Controls->Add(this->text_string5);
		this->panel_for_textBoxes->Controls->Add(this->text_string6);
		this->panel_for_textBoxes->Controls->Add(this->text_string7);
		this->panel_for_textBoxes->Controls->Add(this->text_string8);
	}
	else if (this->identificator_btn == "Заклинания")
	{
		AdminPanelTextBoxes^ text_ItemImage = gcnew AdminPanelTextBoxes(5, 5, "*Spell Image (path to file)");
		this->text_string1 = text_ItemImage->getTextBox();
		AdminPanelTextBoxes^ text_ItemDescr = gcnew AdminPanelTextBoxes(5, 30, "*Spell Name");
		this->text_string2 = text_ItemDescr->getTextBox();
		AdminPanelTextBoxes^ text_ActiveCharacteristics = gcnew AdminPanelTextBoxes(220, 5, "*Spell Description");
		this->text_string3 = text_ActiveCharacteristics->getTextBox();
		this->text_string3->Multiline = true;
		this->text_string3->Size = System::Drawing::Size(300, 100);
		this->text_string3->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_PassiveCharacteristics = gcnew AdminPanelTextBoxes(5, 55, "*Spell Recharge");
		this->text_string4 = text_PassiveCharacteristics->getTextBox();
		AdminPanelTextBoxes^ text_GameStage = gcnew AdminPanelTextBoxes(5, 80, "Spell Line");
		this->text_string5 = text_GameStage->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
		this->panel_for_textBoxes->Controls->Add(this->text_string4);
		this->panel_for_textBoxes->Controls->Add(this->text_string5);
	}
	else if (this->identificator_btn == "Сборки рун")
	{
		AdminPanelTextBoxes^ text_HeroID = gcnew AdminPanelTextBoxes(5, 5, "*Hero ID");
		this->text_string1 = text_HeroID->getTextBox();
		AdminPanelTextBoxes^ text_RuneType = gcnew AdminPanelTextBoxes(5, 30, "*Rune Type");
		this->text_string2 = text_RuneType->getTextBox();
		AdminPanelTextBoxes^ text_FirstKeyRune = gcnew AdminPanelTextBoxes(220, 5, "*First Key Rune");
		this->text_string3 = text_FirstKeyRune->getTextBox();
		AdminPanelTextBoxes^ text_SecondKeyRune = gcnew AdminPanelTextBoxes(220, 30, "*Second Key Rune");
		this->text_string4 = text_SecondKeyRune->getTextBox();
		AdminPanelTextBoxes^ text_ThirdKeyRune = gcnew AdminPanelTextBoxes(220, 55, "*Third Key Rune");
		this->text_string5 = text_ThirdKeyRune->getTextBox();
		AdminPanelTextBoxes^ text_FourthKeyRune = gcnew AdminPanelTextBoxes(220, 80, "*Fourth Key Rune");
		this->text_string6 = text_FourthKeyRune->getTextBox();
		AdminPanelTextBoxes^ text_FirstAdditionalRune = gcnew AdminPanelTextBoxes(5, 55, "*First Additional Rune");
		this->text_string7 = text_FirstAdditionalRune->getTextBox();
		AdminPanelTextBoxes^ text_SecondAdditionalRune = gcnew AdminPanelTextBoxes(5, 80, "*Second Additional Rune");
		this->text_string8 = text_SecondAdditionalRune->getTextBox();
		AdminPanelTextBoxes^ text_FirstAdaptiveRune = gcnew AdminPanelTextBoxes(430, 5, "*First Adaptive Rune");
		this->text_string9 = text_FirstAdaptiveRune->getTextBox();
		AdminPanelTextBoxes^ text_SecondAdaptiveRune = gcnew AdminPanelTextBoxes(430, 30, "*Second Adaptive Rune");
		this->text_string10 = text_SecondAdaptiveRune->getTextBox();
		AdminPanelTextBoxes^ text_ThirdAdaptiveRune = gcnew AdminPanelTextBoxes(430, 55, "*Third Adaptive Rune");
		this->text_string11 = text_ThirdAdaptiveRune->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
		this->panel_for_textBoxes->Controls->Add(this->text_string4);
		this->panel_for_textBoxes->Controls->Add(this->text_string5);
		this->panel_for_textBoxes->Controls->Add(this->text_string6);
		this->panel_for_textBoxes->Controls->Add(this->text_string7);
		this->panel_for_textBoxes->Controls->Add(this->text_string8);
		this->panel_for_textBoxes->Controls->Add(this->text_string9);
		this->panel_for_textBoxes->Controls->Add(this->text_string10);
		this->panel_for_textBoxes->Controls->Add(this->text_string11);
	}
	else if (this->identificator_btn == "Сборки предметов")
	{
		AdminPanelTextBoxes^ text_HeroID = gcnew AdminPanelTextBoxes(5, 5, "*Hero ID");
		this->text_string1 = text_HeroID->getTextBox();
		AdminPanelTextBoxes^ text_FirstItem = gcnew AdminPanelTextBoxes(220, 5, "*First Item");
		this->text_string2 = text_FirstItem->getTextBox();
		AdminPanelTextBoxes^ text_SecondItem = gcnew AdminPanelTextBoxes(220, 30, "*Second Item");
		this->text_string3 = text_SecondItem->getTextBox();
		AdminPanelTextBoxes^ text_ThirdItem = gcnew AdminPanelTextBoxes(220, 55, "*Third Item");
		this->text_string4 = text_ThirdItem->getTextBox();
		AdminPanelTextBoxes^ text_FourthItem = gcnew AdminPanelTextBoxes(530, 5, "*Fourth Item");
		this->text_string5 = text_FourthItem->getTextBox();
		AdminPanelTextBoxes^ text_FifthItem = gcnew AdminPanelTextBoxes(530, 30, "*Fifth Item");
		this->text_string6 = text_FifthItem->getTextBox();
		AdminPanelTextBoxes^ text_SixthItem = gcnew AdminPanelTextBoxes(530, 55, "*Sixth Item");
		this->text_string7 = text_SixthItem->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
		this->panel_for_textBoxes->Controls->Add(this->text_string4);
		this->panel_for_textBoxes->Controls->Add(this->text_string5);
		this->panel_for_textBoxes->Controls->Add(this->text_string6);
		this->panel_for_textBoxes->Controls->Add(this->text_string7);
	}
	else
	{
		AdminPanelTextBoxes^ text_HeroID = gcnew AdminPanelTextBoxes(5, 5, "*Hero ID");
		this->text_string1 = text_HeroID->getTextBox();
		AdminPanelTextBoxes^ text_FirstSpell = gcnew AdminPanelTextBoxes(5, 30, "*First Spell");
		this->text_string2 = text_FirstSpell->getTextBox();
		AdminPanelTextBoxes^ text_SecondSpell = gcnew AdminPanelTextBoxes(5, 55, "*Second Spell");
		this->text_string3 = text_SecondSpell->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
	}
}
System::Void AdminTableButtons::edit_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	this->put_btn = "edit";
	this->panel_for_textBoxes->Controls->Clear();
	this->panel_for_textBoxes->Controls->Add(this->text_errors);
	this->panel_for_textBoxes->Controls->Add(this->help_inf);

	this->text_errors->Text = "";
	this->text_errors->ForeColor = System::Drawing::Color::Red;

	if (this->identificator_btn == "Герои")
	{
		AdminPanelTextBoxes^ text_HideID = gcnew AdminPanelTextBoxes(5, 80, "*Update ID");
		this->text_string0 = text_HideID->getTextBox();
		AdminPanelTextBoxes^ text_heroName = gcnew AdminPanelTextBoxes(5, 5, "Hero Name");
		this->text_string1 = text_heroName->getTextBox();
		AdminPanelTextBoxes^ text_heroHistory = gcnew AdminPanelTextBoxes(220, 5, "Hero History");
		this->text_string2 = text_heroHistory->getTextBox();
		this->text_string2->Multiline = true;
		this->text_string2->Size = System::Drawing::Size(300, 130);
		this->text_string2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_heroSkillsDescr = gcnew AdminPanelTextBoxes(530, 5, "Hero Skills Description");
		this->text_string3 = text_heroSkillsDescr->getTextBox();
		this->text_string3->Multiline = true;
		this->text_string3->Size = System::Drawing::Size(295, 130);
		this->text_string3->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_heroType = gcnew AdminPanelTextBoxes(5, 30, "Hero Type");
		this->text_string4 = text_heroType->getTextBox();
		AdminPanelTextBoxes^ text_heroImage = gcnew AdminPanelTextBoxes(5, 55, "Hero Image (path to file)");
		this->text_string5 = text_heroImage->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string0);
		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
		this->panel_for_textBoxes->Controls->Add(this->text_string4);
		this->panel_for_textBoxes->Controls->Add(this->text_string5);
	}
	else if (this->identificator_btn == "Информация о героях")
	{
		AdminPanelTextBoxes^ text_HideID = gcnew AdminPanelTextBoxes(220, 110, "*Update ID");
		this->text_string0 = text_HideID->getTextBox();
		AdminPanelTextBoxes^ text_heroID = gcnew AdminPanelTextBoxes(5, 90, "new Hero ID");
		this->text_string1 = text_heroID->getTextBox();
		AdminPanelTextBoxes^ text_skillsCombination = gcnew AdminPanelTextBoxes(5, 5, "Skills Combination");
		this->text_string2 = text_skillsCombination->getTextBox();
		this->text_string2->Multiline = true;
		this->text_string2->Size = System::Drawing::Size(200, 80);
		this->text_string2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_skillsTree = gcnew AdminPanelTextBoxes(220, 5, "Skills Tree");
		this->text_string3 = text_skillsTree->getTextBox();
		this->text_string3->Multiline = true;
		this->text_string3->Size = System::Drawing::Size(300, 100);
		this->text_string3->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_skillsRecharge = gcnew AdminPanelTextBoxes(530, 5, "Skills Recharge");
		this->text_string4 = text_skillsRecharge->getTextBox();
		this->text_string4->Multiline = true;
		this->text_string4->Size = System::Drawing::Size(300, 130);
		this->text_string4->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;

		this->panel_for_textBoxes->Controls->Add(this->text_string0);
		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
		this->panel_for_textBoxes->Controls->Add(this->text_string4);
	}
	else if (this->identificator_btn == "Типы героев")
	{
		AdminPanelTextBoxes^ text_HideID = gcnew AdminPanelTextBoxes(5, 30, "*Update ID");
		this->text_string0 = text_HideID->getTextBox();
		AdminPanelTextBoxes^ text_heroID = gcnew AdminPanelTextBoxes(5, 5, "Type Name");
		this->text_string1 = text_heroID->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string0);
		this->panel_for_textBoxes->Controls->Add(this->text_string1);
	}
	else if (this->identificator_btn == "Типы рун")
	{
		AdminPanelTextBoxes^ text_HideID = gcnew AdminPanelTextBoxes(5, 55, "*Update ID");
		this->text_string0 = text_HideID->getTextBox();
		AdminPanelTextBoxes^ text_typeRuneImage = gcnew AdminPanelTextBoxes(5, 5, "Type Rune Image (path to file)");
		this->text_string1 = text_typeRuneImage->getTextBox();
		AdminPanelTextBoxes^ text_typeRuneDescr = gcnew AdminPanelTextBoxes(220, 5, "Type Rune Description");
		this->text_string2 = text_typeRuneDescr->getTextBox();
		this->text_string2->Multiline = true;
		this->text_string2->Size = System::Drawing::Size(200, 80);
		this->text_string2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_typeRuneName = gcnew AdminPanelTextBoxes(5, 30, "Type Rune Name");
		this->text_string3 = text_typeRuneName->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string0);
		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
	}
	else if (this->identificator_btn == "Ключевые руны")
	{
		AdminPanelTextBoxes^ text_HideID = gcnew AdminPanelTextBoxes(5, 80, "*Update ID");
		this->text_string0 = text_HideID->getTextBox();
		AdminPanelTextBoxes^ text_typeRuneID = gcnew AdminPanelTextBoxes(5, 5, "Type Rune ID");
		this->text_string1 = text_typeRuneID->getTextBox();
		AdminPanelTextBoxes^ text_KeyRuneImage = gcnew AdminPanelTextBoxes(5, 30, "Key Rune Image (path to file)");
		this->text_string2 = text_KeyRuneImage->getTextBox();
		AdminPanelTextBoxes^ text_KeyRuneDescr = gcnew AdminPanelTextBoxes(220, 5, "Key Rune Description");
		this->text_string3 = text_KeyRuneDescr->getTextBox();
		this->text_string3->Multiline = true;
		this->text_string3->Size = System::Drawing::Size(300, 130);
		this->text_string3->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_KeyRuneName = gcnew AdminPanelTextBoxes(5, 55, "Key Rune Name");
		this->text_string4 = text_KeyRuneName->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string0);
		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
		this->panel_for_textBoxes->Controls->Add(this->text_string4);
	}
	else if (this->identificator_btn == "Дополнительные руны")
	{
		AdminPanelTextBoxes^ text_HideID = gcnew AdminPanelTextBoxes(5, 80, "*Update ID");
		this->text_string0 = text_HideID->getTextBox();
		AdminPanelTextBoxes^ text_AdditionalRuneID = gcnew AdminPanelTextBoxes(5, 5, "Type Rune ID");
		this->text_string1 = text_AdditionalRuneID->getTextBox();
		AdminPanelTextBoxes^ text_AdditionalRuneImage = gcnew AdminPanelTextBoxes(5, 30, "Additional Rune Image (path to file)");
		this->text_string2 = text_AdditionalRuneImage->getTextBox();
		AdminPanelTextBoxes^ text_AdditionalRuneDescr = gcnew AdminPanelTextBoxes(220, 5, "Additional Rune Description");
		this->text_string3 = text_AdditionalRuneDescr->getTextBox();
		this->text_string3->Multiline = true;
		this->text_string3->Size = System::Drawing::Size(300, 130);
		this->text_string3->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_AdditionalRuneName = gcnew AdminPanelTextBoxes(5, 55, "Additional Rune Name");
		this->text_string4 = text_AdditionalRuneName->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string0);
		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
		this->panel_for_textBoxes->Controls->Add(this->text_string4);
	}
	else if (this->identificator_btn == "Адаптивные руны")
	{
		AdminPanelTextBoxes^ text_HideID = gcnew AdminPanelTextBoxes(5, 55, "*Update ID");
		this->text_string0 = text_HideID->getTextBox();
		AdminPanelTextBoxes^ text_AdaptiveRuneImage = gcnew AdminPanelTextBoxes(5, 5, "Adaptive Rune Image (path to file)");
		this->text_string1 = text_AdaptiveRuneImage->getTextBox();
		AdminPanelTextBoxes^ text_AdaptiveRuneDescr = gcnew AdminPanelTextBoxes(220, 5, "Adaptive Rune Description");
		this->text_string2 = text_AdaptiveRuneDescr->getTextBox();
		this->text_string2->Multiline = true;
		this->text_string2->Size = System::Drawing::Size(300, 130);
		this->text_string2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_AdaptiveRuneName = gcnew AdminPanelTextBoxes(5, 30, "Adaptive Rune Name");
		this->text_string3 = text_AdaptiveRuneName->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string0);
		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
	}
	else if (this->identificator_btn == "Предметы")
	{
		AdminPanelTextBoxes^ text_HideID = gcnew AdminPanelTextBoxes(220, 115, "*Update ID");
		this->text_string0 = text_HideID->getTextBox();
		AdminPanelTextBoxes^ text_ItemImage = gcnew AdminPanelTextBoxes(5, 5, "Item Image (path to file)");
		this->text_string1 = text_ItemImage->getTextBox();
		AdminPanelTextBoxes^ text_ItemDescr = gcnew AdminPanelTextBoxes(220, 5, "Item Description");
		this->text_string2 = text_ItemDescr->getTextBox();
		this->text_string2->Multiline = true;
		this->text_string2->Size = System::Drawing::Size(300, 105);
		this->text_string2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_ActiveCharacteristics = gcnew AdminPanelTextBoxes(530, 5, "Active Characteristics");
		this->text_string3 = text_ActiveCharacteristics->getTextBox();
		this->text_string3->Multiline = true;
		this->text_string3->Size = System::Drawing::Size(300, 50);
		this->text_string3->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_PassiveCharacteristics = gcnew AdminPanelTextBoxes(530, 60, "Passive Characteristics");
		this->text_string4 = text_PassiveCharacteristics->getTextBox();
		this->text_string4->Multiline = true;
		this->text_string4->Size = System::Drawing::Size(300, 50);
		this->text_string4->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_GameStage = gcnew AdminPanelTextBoxes(5, 30, "Game Stage");
		this->text_string5 = text_GameStage->getTextBox();
		AdminPanelTextBoxes^ text_ItemType = gcnew AdminPanelTextBoxes(5, 55, "Item Type");
		this->text_string6 = text_ItemType->getTextBox();
		AdminPanelTextBoxes^ text_ItemCost = gcnew AdminPanelTextBoxes(5, 80, "Item Cost");
		this->text_string7 = text_ItemCost->getTextBox();
		AdminPanelTextBoxes^ text_ItemName = gcnew AdminPanelTextBoxes(530, 115, "Item Name");
		this->text_string8 = text_ItemName->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string0);
		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
		this->panel_for_textBoxes->Controls->Add(this->text_string4);
		this->panel_for_textBoxes->Controls->Add(this->text_string5);
		this->panel_for_textBoxes->Controls->Add(this->text_string6);
		this->panel_for_textBoxes->Controls->Add(this->text_string7);
		this->panel_for_textBoxes->Controls->Add(this->text_string8);
	}
	else if (this->identificator_btn == "Заклинания")
	{
		AdminPanelTextBoxes^ text_HideID = gcnew AdminPanelTextBoxes(530, 5, "*Update ID");
		this->text_string0 = text_HideID->getTextBox();
		AdminPanelTextBoxes^ text_ItemImage = gcnew AdminPanelTextBoxes(5, 5, "Spell Image (path to file)");
		this->text_string1 = text_ItemImage->getTextBox();
		AdminPanelTextBoxes^ text_ItemDescr = gcnew AdminPanelTextBoxes(5, 30, "Spell Name");
		this->text_string2 = text_ItemDescr->getTextBox();
		AdminPanelTextBoxes^ text_ActiveCharacteristics = gcnew AdminPanelTextBoxes(220, 5, "Spell Description");
		this->text_string3 = text_ActiveCharacteristics->getTextBox();
		this->text_string3->Multiline = true;
		this->text_string3->Size = System::Drawing::Size(300, 100);
		this->text_string3->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		AdminPanelTextBoxes^ text_PassiveCharacteristics = gcnew AdminPanelTextBoxes(5, 55, "Spell Recharge");
		this->text_string4 = text_PassiveCharacteristics->getTextBox();
		AdminPanelTextBoxes^ text_GameStage = gcnew AdminPanelTextBoxes(5, 80, "Spell Line");
		this->text_string5 = text_GameStage->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string0);
		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
		this->panel_for_textBoxes->Controls->Add(this->text_string4);
		this->panel_for_textBoxes->Controls->Add(this->text_string5);
	}
	else if (this->identificator_btn == "Сборки рун")
	{
		AdminPanelTextBoxes^ text_HideID = gcnew AdminPanelTextBoxes(220, 105, "*Update ID");
		this->text_string0 = text_HideID->getTextBox();
		AdminPanelTextBoxes^ text_HeroID = gcnew AdminPanelTextBoxes(5, 5, "Hero ID");
		this->text_string1 = text_HeroID->getTextBox();
		AdminPanelTextBoxes^ text_RuneType = gcnew AdminPanelTextBoxes(5, 30, "Rune Type");
		this->text_string2 = text_RuneType->getTextBox();
		AdminPanelTextBoxes^ text_FirstKeyRune = gcnew AdminPanelTextBoxes(220, 5, "First Key Rune");
		this->text_string3 = text_FirstKeyRune->getTextBox();
		AdminPanelTextBoxes^ text_SecondKeyRune = gcnew AdminPanelTextBoxes(220, 30, "Second Key Rune");
		this->text_string4 = text_SecondKeyRune->getTextBox();
		AdminPanelTextBoxes^ text_ThirdKeyRune = gcnew AdminPanelTextBoxes(220, 55, "Third Key Rune");
		this->text_string5 = text_ThirdKeyRune->getTextBox();
		AdminPanelTextBoxes^ text_FourthKeyRune = gcnew AdminPanelTextBoxes(220, 80, "Fourth Key Rune");
		this->text_string6 = text_FourthKeyRune->getTextBox();
		AdminPanelTextBoxes^ text_FirstAdditionalRune = gcnew AdminPanelTextBoxes(5, 55, "First Additional Rune");
		this->text_string7 = text_FirstAdditionalRune->getTextBox();
		AdminPanelTextBoxes^ text_SecondAdditionalRune = gcnew AdminPanelTextBoxes(5, 80, "Second Additional Rune");
		this->text_string8 = text_SecondAdditionalRune->getTextBox();
		AdminPanelTextBoxes^ text_FirstAdaptiveRune = gcnew AdminPanelTextBoxes(430, 5, "First Adaptive Rune");
		this->text_string9 = text_FirstAdaptiveRune->getTextBox();
		AdminPanelTextBoxes^ text_SecondAdaptiveRune = gcnew AdminPanelTextBoxes(430, 30, "Second Adaptive Rune");
		this->text_string10 = text_SecondAdaptiveRune->getTextBox();
		AdminPanelTextBoxes^ text_ThirdAdaptiveRune = gcnew AdminPanelTextBoxes(430, 55, "Third Adaptive Rune");
		this->text_string11 = text_ThirdAdaptiveRune->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string0);
		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
		this->panel_for_textBoxes->Controls->Add(this->text_string4);
		this->panel_for_textBoxes->Controls->Add(this->text_string5);
		this->panel_for_textBoxes->Controls->Add(this->text_string6);
		this->panel_for_textBoxes->Controls->Add(this->text_string7);
		this->panel_for_textBoxes->Controls->Add(this->text_string8);
		this->panel_for_textBoxes->Controls->Add(this->text_string9);
		this->panel_for_textBoxes->Controls->Add(this->text_string10);
		this->panel_for_textBoxes->Controls->Add(this->text_string11);
	}
	else if (this->identificator_btn == "Сборки предметов")
	{
		AdminPanelTextBoxes^ text_HideID = gcnew AdminPanelTextBoxes(5, 30, "*Update ID");
		this->text_string0 = text_HideID->getTextBox();
		AdminPanelTextBoxes^ text_HeroID = gcnew AdminPanelTextBoxes(5, 5, "Hero ID");
		this->text_string1 = text_HeroID->getTextBox();
		AdminPanelTextBoxes^ text_FirstItem = gcnew AdminPanelTextBoxes(220, 5, "First Item");
		this->text_string2 = text_FirstItem->getTextBox();
		AdminPanelTextBoxes^ text_SecondItem = gcnew AdminPanelTextBoxes(220, 30, "Second Item");
		this->text_string3 = text_SecondItem->getTextBox();
		AdminPanelTextBoxes^ text_ThirdItem = gcnew AdminPanelTextBoxes(220, 55, "Third Item");
		this->text_string4 = text_ThirdItem->getTextBox();
		AdminPanelTextBoxes^ text_FourthItem = gcnew AdminPanelTextBoxes(530, 5, "Fourth Item");
		this->text_string5 = text_FourthItem->getTextBox();
		AdminPanelTextBoxes^ text_FifthItem = gcnew AdminPanelTextBoxes(530, 30, "Fifth Item");
		this->text_string6 = text_FifthItem->getTextBox();
		AdminPanelTextBoxes^ text_SixthItem = gcnew AdminPanelTextBoxes(530, 55, "Sixth Item");
		this->text_string7 = text_SixthItem->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string0);
		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
		this->panel_for_textBoxes->Controls->Add(this->text_string4);
		this->panel_for_textBoxes->Controls->Add(this->text_string5);
		this->panel_for_textBoxes->Controls->Add(this->text_string6);
		this->panel_for_textBoxes->Controls->Add(this->text_string7);
	}
	else
	{
		AdminPanelTextBoxes^ text_HideID = gcnew AdminPanelTextBoxes(5, 80, "*Update ID");
		this->text_string0 = text_HideID->getTextBox();
		AdminPanelTextBoxes^ text_HeroID = gcnew AdminPanelTextBoxes(5, 5, "Hero ID");
		this->text_string1 = text_HeroID->getTextBox();
		AdminPanelTextBoxes^ text_FirstSpell = gcnew AdminPanelTextBoxes(5, 30, "First Spell");
		this->text_string2 = text_FirstSpell->getTextBox();
		AdminPanelTextBoxes^ text_SecondSpell = gcnew AdminPanelTextBoxes(5, 55, "Second Spell");
		this->text_string3 = text_SecondSpell->getTextBox();

		this->panel_for_textBoxes->Controls->Add(this->text_string0);
		this->panel_for_textBoxes->Controls->Add(this->text_string1);
		this->panel_for_textBoxes->Controls->Add(this->text_string2);
		this->panel_for_textBoxes->Controls->Add(this->text_string3);
	}
}
System::Void AdminTableButtons::accept_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	DataBaseFunctions^ func = gcnew DataBaseFunctions();

	this->text_errors->Text = "";
	this->text_errors->ForeColor = System::Drawing::Color::Red;

	if (this->identificator_btn == "Герои")
	{
		if (this->put_btn == "add") func->InsertHero(this->text_string1->Text, this->text_string5->Text, this->text_string2->Text, this->text_string3->Text, this->text_string4->Text, this->text_errors);
		if (this->put_btn == "delete") func->DeleteHero(this->text_string1->Text, this->text_errors);
		if (this->put_btn == "edit") func->UpdateHero(this->text_string0->Text, this->text_string1->Text, this->text_string5->Text, this->text_string2->Text, this->text_string3->Text, this->text_string4->Text, this->text_errors);
	}
	else if (this->identificator_btn == "Информация о героях")
	{
		if (this->put_btn == "add") func->InsertHeroInformation(this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_string4->Text, this->text_errors);
		if (this->put_btn == "delete") func->DeleteHeroInformation(this->text_string1->Text, this->text_errors);
		if (this->put_btn == "edit") func->UpdateHeroInformation(this->text_string0->Text, this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_string4->Text, this->text_errors);
	}
	else if (this->identificator_btn == "Типы героев")
	{
		if (this->put_btn == "add") func->InsertTypeHero(this->text_string1->Text, this->text_errors);
		if (this->put_btn == "delete") func->DeleteHeroType(this->text_string1->Text, this->text_errors);
		if (this->put_btn == "edit") func->UpdateTypeHero(this->text_string0->Text, this->text_string1->Text, this->text_errors);
	}
	else if (this->identificator_btn == "Типы рун")
	{
		if (this->put_btn == "add") func->InsertTypeRune(this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_errors);
		if (this->put_btn == "delete") func->DeleteRuneType(this->text_string1->Text, this->text_errors);
		if (this->put_btn == "edit") func->UpdateTypeRune(this->text_string0->Text, this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_errors);
	}
	else if (this->identificator_btn == "Ключевые руны")
	{
		if (this->put_btn == "add") func->InsertKeyRune(this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_string4->Text, this->text_errors);
		if (this->put_btn == "delete") func->DeleteKeyRune(this->text_string1->Text, this->text_errors);
		if (this->put_btn == "edit") func->UpdateKeyRune(this->text_string0->Text, this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_string4->Text, this->text_errors);
	}
	else if (this->identificator_btn == "Дополнительные руны")
	{
		if (this->put_btn == "add") func->InsertAdditionalRune(this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_string4->Text, this->text_errors);
		if (this->put_btn == "delete") func->DeleteAdditionalRune(this->text_string1->Text, this->text_errors);
		if (this->put_btn == "edit") func->UpdateAdditionalRune(this->text_string0->Text, this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_string4->Text, this->text_errors);
	}
	else if (this->identificator_btn == "Адаптивные руны")
	{
		if (this->put_btn == "add") func->InsertAdaptiveRune(this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_errors);
		if (this->put_btn == "delete") func->DeleteAdaptiveRune(this->text_string1->Text, this->text_errors);
		if (this->put_btn == "edit") func->UpdateAdaptiveRune(this->text_string0->Text, this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_errors);
	}
	else if (this->identificator_btn == "Предметы")
	{
		if (this->put_btn == "add") func->InsertItem(this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_string4->Text, this->text_string5->Text, this->text_string6->Text, this->text_string7->Text, this->text_string8->Text, this->text_errors);
		if (this->put_btn == "delete") func->DeleteItems(this->text_string1->Text, this->text_errors);
		if (this->put_btn == "edit") func->UpdateItem(this->text_string0->Text, this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_string4->Text, this->text_string5->Text, this->text_string6->Text, this->text_string7->Text, this->text_string8->Text, this->text_errors);
	}
	else if (this->identificator_btn == "Заклинания")
	{
		if (this->put_btn == "add") func->InsertSpell(this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_string4->Text, this->text_string5->Text, this->text_errors);
		if (this->put_btn == "delete") func->DeleteSpells(this->text_string1->Text, this->text_errors);
		if (this->put_btn == "edit") func->UpdateSpell(this->text_string0->Text, this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_string4->Text, this->text_string5->Text, this->text_errors);
	}
	else if (this->identificator_btn == "Сборки рун")
	{
		if (this->put_btn == "add") func->InsertRuneAssembl(this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_string4->Text, this->text_string5->Text, this->text_string6->Text, this->text_string7->Text, this->text_string8->Text, this->text_string9->Text, this->text_string10->Text, this->text_string11->Text, this->text_errors);
		if (this->put_btn == "delete") func->DeleteRunesAssembl(this->text_string1->Text, this->text_errors);
		if (this->put_btn == "edit")  func->UpdateRuneAssembl(this->text_string0->Text, this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_string4->Text, this->text_string5->Text, this->text_string6->Text, this->text_string7->Text, this->text_string8->Text, this->text_string9->Text, this->text_string10->Text, this->text_string11->Text, this->text_errors);
	}
	else if (this->identificator_btn == "Сборки предметов")
	{
		if (this->put_btn == "add") func->InsertItemAssembl(this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_string4->Text, this->text_string5->Text, this->text_string6->Text, this->text_string7->Text, this->text_errors);
		if (this->put_btn == "delete") func->DeleteItemsAssembl(this->text_string1->Text, this->text_errors);
		if (this->put_btn == "edit") func->UpdateItemAssembl(this->text_string0->Text, this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_string4->Text, this->text_string5->Text, this->text_string6->Text, this->text_string7->Text, this->text_errors);
	}
	else
	{
		if (this->put_btn == "add") func->InsertSpellAssembl(this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_errors);
		if (this->put_btn == "delete") func->DeleteSpellsAssembl(this->text_string1->Text, this->text_errors);
		if (this->put_btn == "edit") func->UpdateSpellAssembl(this->text_string0->Text, this->text_string1->Text, this->text_string2->Text, this->text_string3->Text, this->text_errors);
	}
}