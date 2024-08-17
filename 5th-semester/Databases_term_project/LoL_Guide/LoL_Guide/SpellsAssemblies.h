#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class SpellsAssemblies
{
	Int32^ SpellsAssembliesID{};
	Int32^ HeroID{};
	Int32^ FirstSpell{};
	Int32^ SecondSpell{};
public:
	SpellsAssemblies(SqlDataReader^ reader)
	{
		this->SpellsAssembliesID = reader->GetInt32(0);
		this->HeroID = reader->GetInt32(1);
		this->FirstSpell = reader->GetInt32(2);
		this->SecondSpell = reader->GetInt32(3);
	}
	Int32^ getFirstSpellID()
	{
		return this->FirstSpell;
	}
	Int32^ getSecondSpellID()
	{
		return this->SecondSpell;
	}
};