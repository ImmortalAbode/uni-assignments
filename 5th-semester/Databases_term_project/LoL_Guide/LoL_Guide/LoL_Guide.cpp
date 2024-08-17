#include "LoL_Guide.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array <String^>^ args)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	LoLGuide::LoL_Guide main_form;
	Application::Run(% main_form);
	return 0;
}
