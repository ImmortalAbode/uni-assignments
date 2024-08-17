#include "EntryAdmin.h"
#include "DataBaseFunctions.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

System::Void EntryAdmin::entry_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	DataBaseFunctions^ func = gcnew DataBaseFunctions();
	func->CheckPass(this->password->Text, this->btns_panel, this->descr_panel);
}