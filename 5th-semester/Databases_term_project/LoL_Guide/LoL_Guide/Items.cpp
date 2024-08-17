#include "Items.h"
#include "DataBaseFunctions.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

void Items::getTypeHero()
{
	DataBaseFunctions^ func = gcnew DataBaseFunctions();
	this->item_information->AppendText("Наиболее подходящий тип чемпиона: " + func->getHeroType(this->ItemType));
}