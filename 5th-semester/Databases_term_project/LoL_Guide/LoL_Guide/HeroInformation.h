#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class HeroInformation
{
private:
	Int32^ HeroID{};
	String^ SkillsCombination{};
	String^ SkillsTree{};
	String^ SkillsRecharge{};
private:
	System::Windows::Forms::TextBox^ information_text{};
public:
	HeroInformation(SqlDataReader^ reader)
	{
		this->HeroID = reader->GetInt32(0);
		this->SkillsCombination = reader->GetString(1);
		this->SkillsTree = reader->GetString(2);
		this->SkillsRecharge = reader->GetString(3);
		//
		// information_text
		//
		this->information_text = gcnew System::Windows::Forms::TextBox();
		this->information_text->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
		this->information_text->Font = (gcnew System::Drawing::Font(L"Times New Roman", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->information_text->ForeColor = System::Drawing::Color::DarkBlue;
		this->information_text->ReadOnly = true;
		this->information_text->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->information_text->Location = System::Drawing::Point(10, 10);
		this->information_text->Size = System::Drawing::Size(230, 370);
		this->information_text->Multiline = true;
		this->information_text->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		this->information_text->AppendText("Комбинации навыков: \r\n" + this->SkillsCombination + "\r\n\r\n");
		this->information_text->AppendText("Дерево прокачки навыков: \r\n" + this->SkillsTree + "\r\n\r\n");
		this->information_text->AppendText("Перезарядка навыков: \r\n" + this->SkillsRecharge);
	}
	System::Windows::Forms::TextBox^ getInfHero()
	{
		return this->information_text;
	}
};