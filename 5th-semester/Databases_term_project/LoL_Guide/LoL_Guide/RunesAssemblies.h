#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class RunesAssemblies
{
	Int32^ RunesAssembliesID{};
	Int32^ HeroID{};
	Int32^ RuneType{};
	Int32^ FirstKeyRune{};
	Int32^ SecondKeyRune{};
	Int32^ ThirdKeyRune{};
	Int32^ FourthKeyRune{};
	Int32^ FirstAdditionalRune{};
	Int32^ SecondAdditionalRune{};
	Int32^ FirstAdaptiveRune{};
	Int32^ SecondAdaptiveRune{};
	Int32^ ThirdAdaptiveRune{};
public:
	RunesAssemblies(SqlDataReader^ reader)
	{
		this->RunesAssembliesID = reader->GetInt32(0);
		this->HeroID = reader->GetInt32(1);
		this->RuneType = reader->GetInt32(2);
		this->FirstKeyRune = reader->GetInt32(3);
		this->SecondKeyRune = reader->GetInt32(4);
		this->ThirdKeyRune = reader->GetInt32(5);
		this->FourthKeyRune = reader->GetInt32(6);
		this->FirstAdditionalRune = reader->GetInt32(7);
		this->SecondAdditionalRune = reader->GetInt32(8);
		this->FirstAdaptiveRune = reader->GetInt32(9);
		this->SecondAdaptiveRune = reader->GetInt32(10);
		this->ThirdAdaptiveRune = reader->GetInt32(11);
	}
	Int32^ getRuneTypeID()
	{
		return this->RuneType;
	}
	Int32^ getFirstKeyRuneID()
	{
		return this->FirstKeyRune;
	}
	Int32^ getSecondKeyRuneID()
	{
		return this->SecondKeyRune;
	}
	Int32^ getThirdKeyRuneID()
	{
		return this->ThirdKeyRune;
	}
	Int32^ getFourthKeyRuneID()
	{
		return this->FourthKeyRune;
	}
	Int32^ getFirstAdditionalRuneID()
	{
		return this->FirstAdditionalRune;
	}
	Int32^ getSecondAdditionalRuneID()
	{
		return this->SecondAdditionalRune;
	}
	Int32^ getFirstAdaptiveRuneID()
	{
		return this->FirstAdaptiveRune;
	}
	Int32^ getSecondAdaptiveRuneID()
	{
		return this->SecondAdaptiveRune;
	}
	Int32^ getThirdAdaptiveRuneID()
	{
		return this->ThirdAdaptiveRune;
	}
};

