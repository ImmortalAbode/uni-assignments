#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class EntryAdmin
{
private:
	Label^ autorization_admin{};
	Button^ entry{};
	TextBox^ password{};
	Button^ show_pass{};
	bool show{ false };
	Panel^ descr_panel{};
	Panel^ btns_panel{};
public:
	EntryAdmin(Panel^ btns_panel, Panel^ descr_panel)
	{
		//
		// descr_panel
		//
		descr_panel->Location = System::Drawing::Point(500, 200);
		descr_panel->Size = System::Drawing::Size(400, 150);
		descr_panel->BackgroundImage = Image::FromFile("D:\\KAI\\Базы данных\\Моя курсовая работа\\Images\\Картинки для формы\\submenu_items.jpg");
		descr_panel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		descr_panel->Visible = true;
		this->descr_panel = descr_panel;
		this->btns_panel = btns_panel;
		//
		// autorization_admin
		//
		this->autorization_admin = gcnew System::Windows::Forms::Label();
		this->autorization_admin->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
		this->autorization_admin->BackColor = System::Drawing::Color::Transparent;
		this->autorization_admin->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->autorization_admin->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->autorization_admin->ForeColor = System::Drawing::Color::Khaki;
		this->autorization_admin->Location = System::Drawing::Point(30, 10);
		this->autorization_admin->Size = System::Drawing::Size(400, 20);
		this->autorization_admin->Text = L"Пароль доступа к панели администрирования";
		descr_panel->Controls->Add(this->autorization_admin);
		//
		// password
		//
		this->password = gcnew System::Windows::Forms::TextBox();
		this->password->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
		this->password->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->password->ForeColor = System::Drawing::Color::DarkBlue;
		this->password->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->password->Location = System::Drawing::Point(20, 50);
		this->password->Size = System::Drawing::Size(300, 40);
		this->password->AppendText("Введите пароль");
		descr_panel->Controls->Add(this->password);
		this->password->Leave += gcnew System::EventHandler(this, &EntryAdmin::password_Leave);
		this->password->Enter += gcnew System::EventHandler(this, &EntryAdmin::password_Enter);
		//
		// show_pass
		//
		this->show_pass = gcnew System::Windows::Forms::Button();
		this->show_pass->Location = System::Drawing::Point(330, 50);
		this->show_pass->Size = System::Drawing::Size(25, 25);
		this->show_pass->BackgroundImage = Image::FromFile("D:\\KAI\\Базы данных\\Моя курсовая работа\\Images\\Картинки для формы\\Показать пароль.png");
		this->show_pass->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->show_pass->Cursor = System::Windows::Forms::Cursors::Hand;
		this->show_pass->FlatAppearance->MouseDownBackColor = System::Drawing::Color::MintCream;
		this->show_pass->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
		this->show_pass->BackColor = System::Drawing::Color::CornflowerBlue;
		descr_panel->Controls->Add(this->show_pass);
		this->show_pass->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &EntryAdmin::show_pass_MouseClick);
		//
		// entry
		//
		this->entry = gcnew Button();
		this->entry->Cursor = System::Windows::Forms::Cursors::Hand;
		this->entry->FlatAppearance->MouseDownBackColor = System::Drawing::Color::MintCream;
		this->entry->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
		this->entry->BackColor = System::Drawing::Color::CornflowerBlue;
		this->entry->Location = System::Drawing::Point(150, 100);
		this->entry->Size = System::Drawing::Size(100, 40);
		this->entry->Text = L"Войти";
		descr_panel->Controls->Add(this->entry);
		this->entry->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &EntryAdmin::entry_MouseClick);
	}
private: System::Void password_Leave(System::Object^ sender, System::EventArgs^ e)
{
	if (this->password->Text == "")
	{
		this->password->Text = "Введите пароль";
		this->password->UseSystemPasswordChar = false;
	}
}
private: System::Void password_Enter(System::Object^ sender, System::EventArgs^ e)
{
	if (this->password->Text == "Введите пароль")
	{
		this->password->Text = "";
		this->password->UseSystemPasswordChar = true;
	}
}
private: System::Void show_pass_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	if (this->password->Text != "Введите пароль")
	{
		show = !show;
		if (show)
			this->password->UseSystemPasswordChar = false;
		else
			this->password->UseSystemPasswordChar = true;
	}
}
private: System::Void entry_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
};

