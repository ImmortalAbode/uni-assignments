#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;

ref class AdminTableButtons
{
private:
	//Основная информационно-рабочая панель
	Panel^ descr_panel{};
	//Экземляр однотипных кнопок
	Button^ table_button{};
	//Панель выплывающих TextBoxes
	Panel^ panel_for_textBoxes{};
	TextBox^ help_inf{};
	TextBox^ text_string0{};
	TextBox^ text_string1{};
	TextBox^ text_string2{};
	TextBox^ text_string3{};
	TextBox^ text_string4{};
	TextBox^ text_string5{};
	TextBox^ text_string6{};
	TextBox^ text_string7{};
	TextBox^ text_string8{};
	TextBox^ text_string9{};
	TextBox^ text_string10{};
	TextBox^ text_string11{};

	Label^ text_errors{};
	//Прикрепленные к основной панели объекты
	Button^ add_btn{};
	Button^ del_btn{};
	Button^ edit_btn{};
	Button^ accept_btn{};
	DataGridView^ data{};
	String^ identificator_btn{};
	String^ put_btn{};
public:
	AdminTableButtons(int x, int y, String^ name, Panel^ descr_panel)
	{
		this->identificator_btn = name;
		this->descr_panel = descr_panel;
		this->descr_panel->BackgroundImage = nullptr;
		this->descr_panel->BackColor = System::Drawing::Color::FromArgb(61, 69, 123);
		//
		// table_button
		//
		this->table_button = gcnew System::Windows::Forms::Button{};
		this->table_button->BackColor = System::Drawing::Color::ForestGreen;
		this->table_button->Cursor = System::Windows::Forms::Cursors::Hand;
		this->table_button->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Red;
		this->table_button->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
		this->table_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->table_button->ForeColor = System::Drawing::Color::Yellow;
		this->table_button->Location = System::Drawing::Point(x, y);
		this->table_button->Text = name;
		this->table_button->Size = System::Drawing::Size(150, 40);
		this->table_button->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AdminTableButtons::table_button_MouseClick);
		//
		// DataGridView
		//
		this->data = gcnew DataGridView();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->data))->BeginInit();
		this->data->ColumnHeadersHeight = 20;
		this->data->RowHeadersWidth = 60;
		this->data->Location = System::Drawing::Point(10, 290);
		this->data->Size = System::Drawing::Size(880, 355);
		this->data->BackgroundColor = System::Drawing::Color::CadetBlue;
		this->data->AllowUserToAddRows = false;
		this->data->AllowUserToDeleteRows = false;
		this->data->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Left)
			| System::Windows::Forms::AnchorStyles::Right));
		this->data->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
		this->data->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
		this->data->Cursor = System::Windows::Forms::Cursors::IBeam;
		this->data->EnableHeadersVisualStyles = false;
		this->data->GridColor = System::Drawing::Color::Chocolate;
		this->data->ReadOnly = true;
		this->data->ScrollBars = System::Windows::Forms::ScrollBars::Both;
		this->data->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::Sunken;
		this->data->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Sunken;
		this->data->RowHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Sunken;
		this->data->RowTemplate->Height = 50;
		this->data->RowTemplate->ReadOnly = true;
		this->data->ScrollBars = System::Windows::Forms::ScrollBars::Both;

		System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
		dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
		dataGridViewCellStyle1->BackColor = System::Drawing::Color::Peru;
		dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		dataGridViewCellStyle1->ForeColor = System::Drawing::Color::Black;
		dataGridViewCellStyle1->SelectionBackColor = System::Drawing::Color::Peru;
		dataGridViewCellStyle1->SelectionForeColor = System::Drawing::Color::Black;
		dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
		this->data->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;

		System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
		dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
		dataGridViewCellStyle2->BackColor = System::Drawing::Color::Peru;
		dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		dataGridViewCellStyle2->ForeColor = System::Drawing::Color::Black;
		dataGridViewCellStyle2->SelectionBackColor = System::Drawing::Color::Peru;
		dataGridViewCellStyle2->SelectionForeColor = System::Drawing::Color::Black;
		dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
		this->data->RowHeadersDefaultCellStyle = dataGridViewCellStyle2;

		System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
		dataGridViewCellStyle3->BackColor = System::Drawing::Color::PeachPuff;
		dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		dataGridViewCellStyle3->ForeColor = System::Drawing::Color::Black;
		dataGridViewCellStyle3->SelectionBackColor = System::Drawing::Color::Peru;
		dataGridViewCellStyle3->SelectionForeColor = System::Drawing::Color::Black;
		dataGridViewCellStyle3->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
		this->data->RowsDefaultCellStyle = dataGridViewCellStyle3;
		//
		// Buttons
		//
		this->add_btn = gcnew Button();
		this->add_btn->BackgroundImage = Image::FromFile("D:\\KAI\\Базы данных\\Моя курсовая работа\\Images\\Картинки для формы\\Добавить.png");
		this->add_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->add_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->add_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::MintCream;
		this->add_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
		this->add_btn->BackColor = System::Drawing::Color::DarkGreen;
		this->add_btn->Location = System::Drawing::Point(10, 10);
		this->add_btn->Size = System::Drawing::Size(40, 40);
		this->add_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AdminTableButtons::add_btn_MouseClick);

		this->del_btn = gcnew Button();
		this->del_btn->BackgroundImage = Image::FromFile("D:\\KAI\\Базы данных\\Моя курсовая работа\\Images\\Картинки для формы\\Удалить.png");
		this->del_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->del_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->del_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::MintCream;
		this->del_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
		this->del_btn->BackColor = System::Drawing::Color::DarkRed;
		this->del_btn->Location = System::Drawing::Point(10, 60);
		this->del_btn->Size = System::Drawing::Size(40, 40);
		this->del_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AdminTableButtons::del_btn_MouseClick);

		this->edit_btn = gcnew Button();
		this->edit_btn->BackgroundImage = Image::FromFile("D:\\KAI\\Базы данных\\Моя курсовая работа\\Images\\Картинки для формы\\Изменить.png");
		this->edit_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->edit_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->edit_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::MintCream;
		this->edit_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
		this->edit_btn->BackColor = System::Drawing::Color::LightGoldenrodYellow;
		this->edit_btn->Location = System::Drawing::Point(10, 110);
		this->edit_btn->Size = System::Drawing::Size(40, 40);
		this->edit_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AdminTableButtons::edit_btn_MouseClick);

		this->accept_btn = gcnew Button();
		this->accept_btn->BackgroundImage = Image::FromFile("D:\\KAI\\Базы данных\\Моя курсовая работа\\Images\\Картинки для формы\\Применить.png");
		this->accept_btn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->accept_btn->Cursor = System::Windows::Forms::Cursors::Hand;
		this->accept_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::MintCream;
		this->accept_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
		this->accept_btn->BackColor = System::Drawing::Color::CornflowerBlue;
		this->accept_btn->Location = System::Drawing::Point(10, 160);
		this->accept_btn->Size = System::Drawing::Size(40, 40);
		this->accept_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AdminTableButtons::accept_btn_MouseClick);
		//
		// help
		//
		this->help_inf = gcnew System::Windows::Forms::TextBox();
		this->help_inf->BackColor = System::Drawing::Color::CornflowerBlue;
		this->help_inf->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->help_inf->ForeColor = System::Drawing::Color::White;
		this->help_inf->TextAlign = System::Windows::Forms::HorizontalAlignment::Left;
		this->help_inf->Location = System::Drawing::Point(220, 150);
		this->help_inf->Size = System::Drawing::Size(605, 100);
		this->help_inf->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		this->help_inf->ReadOnly = true;
		this->help_inf->Multiline = true;

		this->help_inf->AppendText("\t\t\t\tПамятка для админа:\r\n");
		this->help_inf->AppendText("При работе с любой таблицей добавление осуществляется указанием всех обязательных полей (*), а затем при нажатии кнопки Apply данные заносятся в БД.\r\n");
		this->help_inf->AppendText("Для удаления любой строки таблицы достаточно указать ID удаляемого объекта, который можно найти в выведенных данных. Остальные поля не важны. Также необходимо в конце нажать кнопку Apply.\r\n");
		this->help_inf->AppendText("Для изменения любой строки таблицы достаточно указать ID изменяемого объекта, который можно найти в выведенных данных,");
		this->help_inf->AppendText("a также изменяемое поле (оно может быть и одно). Также необходимо в конце нажать кнопку Apply.\r\n");
		this->help_inf->AppendText("Для поиска можно воспользоваться встроенной сортировкой любого столбца таблицы DataGridView.\r\n");
		this->help_inf->AppendText("Для обновление выводимой таблицы данных - заново нажмите на нужную таблицу.\r\n");
		//
		// text_errors
		//
		this->text_errors = gcnew System::Windows::Forms::Label();
		this->text_errors->BackColor = System::Drawing::Color::Transparent;
		this->text_errors->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->text_errors->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->text_errors->ForeColor = System::Drawing::Color::Red;
		this->text_errors->Location = System::Drawing::Point(5, 120);
		this->text_errors->Size = System::Drawing::Size(200, 130);
		//
		// panel_for_textBoxes
		//
		this->panel_for_textBoxes = gcnew Panel();
		this->panel_for_textBoxes->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)));
		this->panel_for_textBoxes->BackColor = System::Drawing::SystemColors::InactiveCaption;
		this->panel_for_textBoxes->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->panel_for_textBoxes->Cursor = System::Windows::Forms::Cursors::Arrow;
		this->panel_for_textBoxes->Location = System::Drawing::Point(60, 10);
		this->panel_for_textBoxes->Size = System::Drawing::Size(830, 270);
	}
	Button^ getTableBTN()
	{
		return this->table_button;
	}
private: System::Void table_button_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
private: System::Void add_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
private: System::Void del_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
private: System::Void edit_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
private: System::Void accept_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
};

