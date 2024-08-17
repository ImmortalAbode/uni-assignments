#pragma once

#include "DataBaseFunctions.h"

namespace LoLGuide {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для LoL_Guide
	/// </summary>
	public ref class LoL_Guide : public System::Windows::Forms::Form
	{
	public:
		LoL_Guide(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~LoL_Guide()
		{
			if (components)
			{
				delete components;
			}
		}
	//Основная панель кнопок.
	private: System::Windows::Forms::Panel^ main_panel;
	private: System::Windows::Forms::Button^ Items_btn;
	private: System::Windows::Forms::Button^ runes_btn;
	private: System::Windows::Forms::Button^ spells_btn;
	private: System::Windows::Forms::Button^ hero_btn;
	//Постоянные кнопки управления.
	private: System::Windows::Forms::Button^ close_btn;
	private: System::Windows::Forms::Button^ cancel_btn;
	private: System::Windows::Forms::Button^ admin_btn;
	//Надпись снизу формы.
	private: System::Windows::Forms::Label^ label1;
	//Информационная панель.
	private: System::Windows::Forms::Panel^ objects_panel;
	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(LoL_Guide::typeid));
			this->main_panel = (gcnew System::Windows::Forms::Panel());
			this->Items_btn = (gcnew System::Windows::Forms::Button());
			this->spells_btn = (gcnew System::Windows::Forms::Button());
			this->hero_btn = (gcnew System::Windows::Forms::Button());
			this->runes_btn = (gcnew System::Windows::Forms::Button());
			this->admin_btn = (gcnew System::Windows::Forms::Button());
			this->cancel_btn = (gcnew System::Windows::Forms::Button());
			this->close_btn = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->objects_panel = (gcnew System::Windows::Forms::Panel());
			this->main_panel->SuspendLayout();
			this->SuspendLayout();
			// 
			// main_panel
			// 
			this->main_panel->BackColor = System::Drawing::Color::Transparent;
			this->main_panel->Controls->Add(this->Items_btn);
			this->main_panel->Controls->Add(this->spells_btn);
			this->main_panel->Controls->Add(this->hero_btn);
			this->main_panel->Controls->Add(this->runes_btn);
			this->main_panel->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->main_panel->Location = System::Drawing::Point(839, 38);
			this->main_panel->Name = L"main_panel";
			this->main_panel->Size = System::Drawing::Size(412, 199);
			this->main_panel->TabIndex = 0;
			// 
			// Items_btn
			// 
			this->Items_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Items_btn.BackgroundImage")));
			this->Items_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->Items_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::MintCream;
			this->Items_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->Items_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Items_btn->ForeColor = System::Drawing::Color::DodgerBlue;
			this->Items_btn->Location = System::Drawing::Point(209, 12);
			this->Items_btn->Name = L"Items_btn";
			this->Items_btn->Size = System::Drawing::Size(187, 85);
			this->Items_btn->TabIndex = 0;
			this->Items_btn->Text = L"Предметы";
			this->Items_btn->UseVisualStyleBackColor = true;
			this->Items_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &LoL_Guide::Items_btn_MouseClick);
			// 
			// spells_btn
			// 
			this->spells_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"spells_btn.BackgroundImage")));
			this->spells_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->spells_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::MintCream;
			this->spells_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->spells_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->spells_btn->ForeColor = System::Drawing::Color::DodgerBlue;
			this->spells_btn->Location = System::Drawing::Point(209, 103);
			this->spells_btn->Name = L"spells_btn";
			this->spells_btn->Size = System::Drawing::Size(187, 85);
			this->spells_btn->TabIndex = 4;
			this->spells_btn->Text = L"Заклинания";
			this->spells_btn->UseVisualStyleBackColor = true;
			this->spells_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &LoL_Guide::spells_btn_MouseClick);
			// 
			// hero_btn
			// 
			this->hero_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"hero_btn.BackgroundImage")));
			this->hero_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->hero_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::MintCream;
			this->hero_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->hero_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->hero_btn->ForeColor = System::Drawing::Color::DodgerBlue;
			this->hero_btn->Location = System::Drawing::Point(16, 12);
			this->hero_btn->Name = L"hero_btn";
			this->hero_btn->Size = System::Drawing::Size(187, 85);
			this->hero_btn->TabIndex = 3;
			this->hero_btn->Text = L"Персонажи";
			this->hero_btn->UseVisualStyleBackColor = true;
			this->hero_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &LoL_Guide::hero_btn_MouseClick);
			// 
			// runes_btn
			// 
			this->runes_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"runes_btn.BackgroundImage")));
			this->runes_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->runes_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::MintCream;
			this->runes_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->runes_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->runes_btn->ForeColor = System::Drawing::Color::DodgerBlue;
			this->runes_btn->Location = System::Drawing::Point(16, 103);
			this->runes_btn->Name = L"runes_btn";
			this->runes_btn->Size = System::Drawing::Size(187, 85);
			this->runes_btn->TabIndex = 5;
			this->runes_btn->Text = L"Руны";
			this->runes_btn->UseVisualStyleBackColor = true;
			this->runes_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &LoL_Guide::runes_btn_MouseClick);
			// 
			// admin_btn
			// 
			this->admin_btn->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->admin_btn->BackColor = System::Drawing::Color::Transparent;
			this->admin_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->admin_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->admin_btn->ForeColor = System::Drawing::Color::Red;
			this->admin_btn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"admin_btn.Image")));
			this->admin_btn->Location = System::Drawing::Point(1195, 488);
			this->admin_btn->Name = L"admin_btn";
			this->admin_btn->Size = System::Drawing::Size(187, 78);
			this->admin_btn->TabIndex = 5;
			this->admin_btn->Text = L"Admin";
			this->admin_btn->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->admin_btn->UseVisualStyleBackColor = false;
			this->admin_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &LoL_Guide::admin_btn_MouseClick);
			// 
			// cancel_btn
			// 
			this->cancel_btn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->cancel_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cancel_btn.BackgroundImage")));
			this->cancel_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->cancel_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::MintCream;
			this->cancel_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->cancel_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->cancel_btn->ForeColor = System::Drawing::Color::DodgerBlue;
			this->cancel_btn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cancel_btn.Image")));
			this->cancel_btn->Location = System::Drawing::Point(1195, 572);
			this->cancel_btn->Name = L"cancel_btn";
			this->cancel_btn->Size = System::Drawing::Size(187, 78);
			this->cancel_btn->TabIndex = 1;
			this->cancel_btn->UseVisualStyleBackColor = true;
			this->cancel_btn->Visible = false;
			this->cancel_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &LoL_Guide::cancel_btn_MouseClick);
			// 
			// close_btn
			// 
			this->close_btn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->close_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"close_btn.BackgroundImage")));
			this->close_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->close_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightCoral;
			this->close_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->close_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->close_btn->ForeColor = System::Drawing::Color::DarkOrange;
			this->close_btn->Location = System::Drawing::Point(1332, 0);
			this->close_btn->Name = L"close_btn";
			this->close_btn->Size = System::Drawing::Size(50, 50);
			this->close_btn->TabIndex = 2;
			this->close_btn->Text = L"x";
			this->close_btn->UseVisualStyleBackColor = true;
			this->close_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &LoL_Guide::close_btn_MouseClick);
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label1->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 16.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::Color::Khaki;
			this->label1->Location = System::Drawing::Point(3, 610);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(363, 39);
			this->label1->TabIndex = 3;
			this->label1->Text = L"League Of Legends GUIDE";
			// 
			// objects_panel
			// 
			this->objects_panel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->objects_panel->AutoScroll = true;
			this->objects_panel->BackColor = System::Drawing::Color::White;
			this->objects_panel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"objects_panel.BackgroundImage")));
			this->objects_panel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->objects_panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->objects_panel->Cursor = System::Windows::Forms::Cursors::Hand;
			this->objects_panel->Location = System::Drawing::Point(0, 0);
			this->objects_panel->Name = L"objects_panel";
			this->objects_panel->Size = System::Drawing::Size(703, 653);
			this->objects_panel->TabIndex = 6;
			this->objects_panel->Visible = false;
			// 
			// LoL_Guide
			// 
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1382, 653);
			this->Controls->Add(this->main_panel);
			this->Controls->Add(this->cancel_btn);
			this->Controls->Add(this->admin_btn);
			this->Controls->Add(this->close_btn);
			this->Controls->Add(this->objects_panel);
			this->Controls->Add(this->label1);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"LoL_Guide";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->main_panel->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void close_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		this->Close();
	}
	private: System::Void cancel_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		this->Controls->Clear();
		InitializeComponent();
	}
	private: System::Void Items_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		this->cancel_btn->Visible = true;
		this->Items_btn->Visible = false;
		this->hero_btn->Visible = false;
		this->spells_btn->Visible = false;
		this->runes_btn->Visible = false;
		this->label1->Visible = false;
		this->admin_btn->Visible = false;
		this->objects_panel->Visible = true;
		DataBaseFunctions^ getItems = gcnew DataBaseFunctions();
		getItems->SelectItems(objects_panel, main_panel);
	}
	private: System::Void admin_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		this->cancel_btn->Visible = true;
		this->Items_btn->Visible = false;
		this->hero_btn->Visible = false;
		this->spells_btn->Visible = false;
		this->runes_btn->Visible = false;
		this->label1->Visible = false;
		this->admin_btn->Visible = false;
		this->objects_panel->Visible = false;
		DataBaseFunctions^ getAdminEntry = gcnew DataBaseFunctions();
		getAdminEntry->AdminEntry(objects_panel, main_panel);
	}
private: System::Void spells_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		this->cancel_btn->Visible = true;
		this->Items_btn->Visible = false;
		this->hero_btn->Visible = false;
		this->spells_btn->Visible = false;
		this->runes_btn->Visible = false;
		this->label1->Visible = false;
		this->admin_btn->Visible = false;
		this->objects_panel->Visible = true;
		DataBaseFunctions^ getSpells = gcnew DataBaseFunctions();
		getSpells->SelectSpells(objects_panel, main_panel);
	}
private: System::Void runes_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		this->cancel_btn->Visible = true;
		this->Items_btn->Visible = false;
		this->hero_btn->Visible = false;
		this->spells_btn->Visible = false;
		this->runes_btn->Visible = false;
		this->label1->Visible = false;
		this->admin_btn->Visible = false;
		this->objects_panel->Visible = true;
		DataBaseFunctions^ getInformationRunes = gcnew DataBaseFunctions();
		getInformationRunes->SelectTypeRunes(objects_panel, main_panel);
	}
private: System::Void hero_btn_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		this->cancel_btn->Visible = true;
		this->Items_btn->Visible = false;
		this->hero_btn->Visible = false;
		this->spells_btn->Visible = false;
		this->runes_btn->Visible = false;
		this->label1->Visible = false;
		this->admin_btn->Visible = false;
		this->objects_panel->Visible = true;
		DataBaseFunctions^ getHeroInf = gcnew DataBaseFunctions();
		getHeroInf->SelectHeroes(objects_panel, main_panel);
	}
};
}
