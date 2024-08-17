#include "TypeRunes.h"
#include "KeyRunes.h"
#include "DataBaseFunctions.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

System::Void TypeRunes::types_box_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (types_box->Text == this->TypeRuneName)
	{
		this->all_descr_panel->Controls->Clear();
		this->obj->getOtherRunesPanel()->Controls->Clear();
		this->all_descr_panel->BackColor = System::Drawing::Color::Transparent;

		this->obj->getOtherRunesPanel()->Controls->Add(this->obj->getKeyText());
		this->obj->getOtherRunesPanel()->Controls->Add(this->obj->getAdditionalText());
		this->obj->getOtherRunesPanel()->Controls->Add(this->obj->getAdaptiveText());
		this->obj->getDescr()->Text = this->TypeRuneDescr;
		this->runes_catalog_panel->Controls->Add(this->obj->getDescr());
		this->obj->getPB()->Image = this->getPNGfromByte();
		this->runes_catalog_panel->Controls->Add(this->obj->getPB());

		DataBaseFunctions^ funcs = gcnew DataBaseFunctions();
		funcs->SelectKeyRunes(this->obj->getOtherRunesPanel(), this->all_descr_panel, this->TypeRuneID);
		funcs->SelectAdditionalRunes(this->obj->getOtherRunesPanel(), this->all_descr_panel, this->TypeRuneID);
		funcs->SelectAdaptiveRunes(this->obj->getOtherRunesPanel(), this->all_descr_panel);
	}
};