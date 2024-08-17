#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class ItemsAssemblies
{
	Int32^ ItemsAssembliesID{};
	Int32^ HeroID{};
	Int32^ FirstItem{};
	Int32^ SecondItem{};
	Int32^ ThirdItem{};
	Int32^ FourthItem{};
	Int32^ FifthItem{};
	Int32^ SixthItem{};
public:
	ItemsAssemblies(SqlDataReader^ reader)
	{
		this->ItemsAssembliesID = reader->GetInt32(0);
		this->HeroID = reader->GetInt32(1);
		this->FirstItem = reader->GetInt32(2);
		this->SecondItem = reader->GetInt32(3);
		this->ThirdItem = reader->GetInt32(4);
		this->FourthItem = reader->GetInt32(5);
		this->FifthItem = reader->GetInt32(6);
		this->SixthItem = reader->GetInt32(7);
	}
	Int32^ getFirstItemID()
	{
		return this->FirstItem;
	}
	Int32^ getSecondItemID()
	{
		return this->SecondItem;
	}
	Int32^ getThirdItemID()
	{
		return this->ThirdItem;
	}
	Int32^ getFourthItemID()
	{
		return this->FourthItem;
	}
	Int32^ getFifthItemID()
	{
		return this->FifthItem;
	}
	Int32^ getSixthItemID()
	{
		return this->SixthItem;
	}
	
};

