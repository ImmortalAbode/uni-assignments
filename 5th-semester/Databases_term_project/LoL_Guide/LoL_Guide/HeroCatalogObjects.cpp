#include "HeroCatalogObjects.h"
#include "DataBaseFunctions.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

System::Void HeroCatalogObjects::search_hero_TB_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	if (e->KeyCode == Keys::Enter)
	{
		e->SuppressKeyPress = true;
		this->isEnter = true;
		this->prev_text = this->search_hero_TB->Text;
		this->panel_for_groups->Controls->Clear();

		DataBaseFunctions^ func = gcnew DataBaseFunctions();
		String^ searching_text = this->search_hero_TB->Text;
		func->FindHeroes(this->panel_for_groups, this->panel_for_descr, searching_text);
		this->panel_for_descr->Controls->Clear();
		this->panel_for_descr->BackColor = System::Drawing::Color::Transparent;
	}
}