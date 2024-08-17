#include "ItemsCatalogObjects.h"
#include "DataBaseFunctions.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

System::Void ItemsCatalogObjects::search_item_text_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	if (e->KeyCode == Keys::Enter)
	{
		e->SuppressKeyPress = true;
		this->isEnter = true;
		this->prev_text = this->search_item_text->Text;
		this->panel_for_objects->Controls->Clear();

		DataBaseFunctions^ func = gcnew DataBaseFunctions();
		String^ searching_text = this->search_item_text->Text;
		func->FindItems(this->panel_for_objects, this->descr_panel, searching_text);
		this->descr_panel->Controls->Clear();
		this->descr_panel->BackColor = System::Drawing::Color::Transparent;
	}
}