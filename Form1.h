#pragma once
#include "AppLogic.h" 
#include <msclr/marshal_cppstd.h> 

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop; // dla marshal_as

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
		
			this->dataGridViewResults->AllowUserToAddRows = false;
			this->dataGridViewResults->AllowUserToDeleteRows = false;
			this->dataGridViewResults->ReadOnly = true;
		
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Button^ btnLoadCSV;
	private: System::Windows::Forms::TextBox^ textBoxFilePath;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialogCSV;
	private: System::Windows::Forms::Button^ btnRunSimulation;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ColorDialog^ colorDialog1;
	private: System::Windows::Forms::ColorDialog^ colorDialog2;
	private: System::Windows::Forms::DataGridView^ dataGridViewResults;
	private: System::Windows::Forms::NumericUpDown^ nudSimulationDays;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::NumericUpDown^ numRsiPeriod;
	private: System::Windows::Forms::NumericUpDown^ numRsiOversold;
	private: System::Windows::Forms::NumericUpDown^ numRsiOverbought;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::NumericUpDown^ MA1;
	private: System::Windows::Forms::NumericUpDown^ MA2;
	private: System::Windows::Forms::NumericUpDown^ stochKPeriod;
	private: System::Windows::Forms::NumericUpDown^ stochDPeriod;
	private: System::Windows::Forms::NumericUpDown^ macdFastPeriod;
	private: System::Windows::Forms::NumericUpDown^ macdSlowPeriod;
	private: System::Windows::Forms::NumericUpDown^ macdSignalPeriod;
	private: System::Windows::Forms::NumericUpDown^ stochRsiRsiPeriod;
	private: System::Windows::Forms::NumericUpDown^ StochRsiKPeriod;
	private: System::Windows::Forms::NumericUpDown^ stochRsiDPeriod;
	private: System::Windows::Forms::NumericUpDown^ initialCapital;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Label^ label16;



	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
	
		void InitializeComponent(void)
		{
			this->btnLoadCSV = (gcnew System::Windows::Forms::Button());
			this->textBoxFilePath = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialogCSV = (gcnew System::Windows::Forms::OpenFileDialog());
			this->btnRunSimulation = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->colorDialog2 = (gcnew System::Windows::Forms::ColorDialog());
			this->dataGridViewResults = (gcnew System::Windows::Forms::DataGridView());
			this->nudSimulationDays = (gcnew System::Windows::Forms::NumericUpDown());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->numRsiPeriod = (gcnew System::Windows::Forms::NumericUpDown());
			this->numRsiOversold = (gcnew System::Windows::Forms::NumericUpDown());
			this->numRsiOverbought = (gcnew System::Windows::Forms::NumericUpDown());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->MA1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->MA2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->stochKPeriod = (gcnew System::Windows::Forms::NumericUpDown());
			this->stochDPeriod = (gcnew System::Windows::Forms::NumericUpDown());
			this->macdFastPeriod = (gcnew System::Windows::Forms::NumericUpDown());
			this->macdSlowPeriod = (gcnew System::Windows::Forms::NumericUpDown());
			this->macdSignalPeriod = (gcnew System::Windows::Forms::NumericUpDown());
			this->stochRsiRsiPeriod = (gcnew System::Windows::Forms::NumericUpDown());
			this->StochRsiKPeriod = (gcnew System::Windows::Forms::NumericUpDown());
			this->stochRsiDPeriod = (gcnew System::Windows::Forms::NumericUpDown());
			this->initialCapital = (gcnew System::Windows::Forms::NumericUpDown());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewResults))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudSimulationDays))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numRsiPeriod))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numRsiOversold))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numRsiOverbought))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MA1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MA2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->stochKPeriod))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->stochDPeriod))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->macdFastPeriod))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->macdSlowPeriod))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->macdSignalPeriod))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->stochRsiRsiPeriod))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StochRsiKPeriod))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->stochRsiDPeriod))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initialCapital))->BeginInit();
			this->SuspendLayout();
			// 
			// btnLoadCSV
			// 
			this->btnLoadCSV->BackColor = System::Drawing::Color::Gainsboro;
			this->btnLoadCSV->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnLoadCSV->Location = System::Drawing::Point(93, 19);
			this->btnLoadCSV->Name = L"btnLoadCSV";
			this->btnLoadCSV->Size = System::Drawing::Size(182, 30);
			this->btnLoadCSV->TabIndex = 0;
			this->btnLoadCSV->Text = L"Wczytaj Plik CSV";
			this->btnLoadCSV->UseVisualStyleBackColor = false;
			this->btnLoadCSV->Click += gcnew System::EventHandler(this, &Form1::btnLoadCSV_Click);
			// 
			// textBoxFilePath
			// 
			this->textBoxFilePath->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBoxFilePath->Location = System::Drawing::Point(37, 55);
			this->textBoxFilePath->Name = L"textBoxFilePath";
			this->textBoxFilePath->ReadOnly = true;
			this->textBoxFilePath->Size = System::Drawing::Size(300, 22);
			this->textBoxFilePath->TabIndex = 1;
			// 
			// openFileDialogCSV
			// 
			this->openFileDialogCSV->FileName = L"Aluminium.csv";
			this->openFileDialogCSV->Filter = L"Pliki CSV (*.csv)|*.csv|Wszystkie pliki (*.*)|*.*";
			// 
			// btnRunSimulation
			// 
			this->btnRunSimulation->BackColor = System::Drawing::Color::Gainsboro;
			this->btnRunSimulation->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnRunSimulation->ForeColor = System::Drawing::Color::Black;
			this->btnRunSimulation->Location = System::Drawing::Point(57, 115);
			this->btnRunSimulation->Name = L"btnRunSimulation";
			this->btnRunSimulation->Size = System::Drawing::Size(240, 56);
			this->btnRunSimulation->TabIndex = 2;
			this->btnRunSimulation->Text = L"Uruchom Symulację";
			this->btnRunSimulation->UseVisualStyleBackColor = false;
			this->btnRunSimulation->Click += gcnew System::EventHandler(this, &Form1::btnRunSimulation_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(21, 220);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(155, 24);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Wyniki Symulacji:";
			this->label2->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
			// 
			// dataGridViewResults
			// 
			this->dataGridViewResults->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridViewResults->Location = System::Drawing::Point(14, 264);
			this->dataGridViewResults->Name = L"dataGridViewResults";
			this->dataGridViewResults->Size = System::Drawing::Size(1032, 200);
			this->dataGridViewResults->TabIndex = 6;
			// 
			// nudSimulationDays
			// 
			this->nudSimulationDays->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->nudSimulationDays->Location = System::Drawing::Point(904, 195);
			this->nudSimulationDays->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200000, 0, 0, 0 });
			this->nudSimulationDays->Name = L"nudSimulationDays";
			this->nudSimulationDays->Size = System::Drawing::Size(102, 22);
			this->nudSimulationDays->TabIndex = 7;
			this->nudSimulationDays->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 365, 0, 0, 0 });
			this->nudSimulationDays->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown1_ValueChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(901, 179);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(129, 16);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Liczba dni symulacji:";
			this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click_1);
			// 
			// numRsiPeriod
			// 
			this->numRsiPeriod->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numRsiPeriod->Location = System::Drawing::Point(512, 33);
			this->numRsiPeriod->Name = L"numRsiPeriod";
			this->numRsiPeriod->Size = System::Drawing::Size(103, 22);
			this->numRsiPeriod->TabIndex = 9;
			this->numRsiPeriod->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 14, 0, 0, 0 });
			// 
			// numRsiOversold
			// 
			this->numRsiOversold->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numRsiOversold->Location = System::Drawing::Point(512, 73);
			this->numRsiOversold->Name = L"numRsiOversold";
			this->numRsiOversold->Size = System::Drawing::Size(103, 22);
			this->numRsiOversold->TabIndex = 10;
			this->numRsiOversold->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
			// 
			// numRsiOverbought
			// 
			this->numRsiOverbought->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->numRsiOverbought->Location = System::Drawing::Point(512, 112);
			this->numRsiOverbought->Name = L"numRsiOverbought";
			this->numRsiOverbought->Size = System::Drawing::Size(103, 22);
			this->numRsiOverbought->TabIndex = 11;
			this->numRsiOverbought->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 70, 0, 0, 0 });
			this->numRsiOverbought->ValueChanged += gcnew System::EventHandler(this, &Form1::numRsiOverbought_ValueChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(509, 14);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(71, 16);
			this->label4->TabIndex = 12;
			this->label4->Text = L"Okres RSI:";
			this->label4->Click += gcnew System::EventHandler(this, &Form1::label4_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(509, 55);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(115, 16);
			this->label1->TabIndex = 13;
			this->label1->Text = L"RSI Wyprzedanie:";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(509, 98);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(106, 16);
			this->label5->TabIndex = 14;
			this->label5->Text = L"RSI Wykupienie:";
			this->label5->Click += gcnew System::EventHandler(this, &Form1::label5_Click);
			// 
			// MA1
			// 
			this->MA1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->MA1->Location = System::Drawing::Point(512, 154);
			this->MA1->Name = L"MA1";
			this->MA1->Size = System::Drawing::Size(103, 22);
			this->MA1->TabIndex = 15;
			this->MA1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			// 
			// MA2
			// 
			this->MA2->Location = System::Drawing::Point(512, 198);
			this->MA2->Name = L"MA2";
			this->MA2->Size = System::Drawing::Size(103, 20);
			this->MA2->TabIndex = 16;
			this->MA2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			// 
			// stochKPeriod
			// 
			this->stochKPeriod->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->stochKPeriod->Location = System::Drawing::Point(695, 33);
			this->stochKPeriod->Name = L"stochKPeriod";
			this->stochKPeriod->Size = System::Drawing::Size(102, 22);
			this->stochKPeriod->TabIndex = 17;
			this->stochKPeriod->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9, 0, 0, 0 });
			// 
			// stochDPeriod
			// 
			this->stochDPeriod->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->stochDPeriod->Location = System::Drawing::Point(695, 73);
			this->stochDPeriod->Name = L"stochDPeriod";
			this->stochDPeriod->Size = System::Drawing::Size(102, 22);
			this->stochDPeriod->TabIndex = 18;
			this->stochDPeriod->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 6, 0, 0, 0 });
			// 
			// macdFastPeriod
			// 
			this->macdFastPeriod->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->macdFastPeriod->Location = System::Drawing::Point(695, 112);
			this->macdFastPeriod->Name = L"macdFastPeriod";
			this->macdFastPeriod->Size = System::Drawing::Size(104, 22);
			this->macdFastPeriod->TabIndex = 19;
			this->macdFastPeriod->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 12, 0, 0, 0 });
			// 
			// macdSlowPeriod
			// 
			this->macdSlowPeriod->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->macdSlowPeriod->Location = System::Drawing::Point(695, 154);
			this->macdSlowPeriod->Name = L"macdSlowPeriod";
			this->macdSlowPeriod->Size = System::Drawing::Size(104, 22);
			this->macdSlowPeriod->TabIndex = 20;
			this->macdSlowPeriod->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 26, 0, 0, 0 });
			// 
			// macdSignalPeriod
			// 
			this->macdSignalPeriod->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->macdSignalPeriod->Location = System::Drawing::Point(695, 195);
			this->macdSignalPeriod->Name = L"macdSignalPeriod";
			this->macdSignalPeriod->Size = System::Drawing::Size(102, 22);
			this->macdSignalPeriod->TabIndex = 21;
			this->macdSignalPeriod->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9, 0, 0, 0 });
			// 
			// stochRsiRsiPeriod
			// 
			this->stochRsiRsiPeriod->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->stochRsiRsiPeriod->Location = System::Drawing::Point(904, 33);
			this->stochRsiRsiPeriod->Name = L"stochRsiRsiPeriod";
			this->stochRsiRsiPeriod->Size = System::Drawing::Size(102, 22);
			this->stochRsiRsiPeriod->TabIndex = 22;
			this->stochRsiRsiPeriod->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 14, 0, 0, 0 });
			this->stochRsiRsiPeriod->ValueChanged += gcnew System::EventHandler(this, &Form1::stochRsiRsiPeriod_ValueChanged);
			// 
			// StochRsiKPeriod
			// 
			this->StochRsiKPeriod->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->StochRsiKPeriod->Location = System::Drawing::Point(904, 73);
			this->StochRsiKPeriod->Name = L"StochRsiKPeriod";
			this->StochRsiKPeriod->Size = System::Drawing::Size(102, 22);
			this->StochRsiKPeriod->TabIndex = 23;
			this->StochRsiKPeriod->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 14, 0, 0, 0 });
			// 
			// stochRsiDPeriod
			// 
			this->stochRsiDPeriod->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->stochRsiDPeriod->Location = System::Drawing::Point(904, 112);
			this->stochRsiDPeriod->Name = L"stochRsiDPeriod";
			this->stochRsiDPeriod->Size = System::Drawing::Size(102, 22);
			this->stochRsiDPeriod->TabIndex = 24;
			this->stochRsiDPeriod->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
			// 
			// initialCapital
			// 
			this->initialCapital->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->initialCapital->Location = System::Drawing::Point(904, 154);
			this->initialCapital->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { -727379968, 232, 0, 0 });
			this->initialCapital->Name = L"initialCapital";
			this->initialCapital->Size = System::Drawing::Size(102, 22);
			this->initialCapital->TabIndex = 25;
			this->initialCapital->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(509, 137);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(69, 16);
			this->label6->TabIndex = 26;
			this->label6->Text = L"Okres MA:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(509, 179);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(69, 16);
			this->label7->TabIndex = 27;
			this->label7->Text = L"Okres MA:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(692, 14);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(105, 16);
			this->label8->TabIndex = 28;
			this->label8->Text = L"STOCH K okres:";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(692, 55);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(107, 16);
			this->label9->TabIndex = 29;
			this->label9->Text = L"STOCH D okres:";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(692, 98);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(191, 16);
			this->label10->TabIndex = 30;
			this->label10->Text = L"Okres szybkiej średniej MACD:";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(692, 135);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(180, 16);
			this->label11->TabIndex = 31;
			this->label11->Text = L"Okres wolnej średniej MACD:";
			this->label11->Click += gcnew System::EventHandler(this, &Form1::label11_Click);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(692, 179);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(141, 16);
			this->label12->TabIndex = 32;
			this->label12->Text = L"Okres sygnału MACD:";
			this->label12->Click += gcnew System::EventHandler(this, &Form1::label12_Click);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->Location = System::Drawing::Point(901, 14);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(118, 16);
			this->label13->TabIndex = 33;
			this->label13->Text = L"Okres STOCHRSI:";
			this->label13->Click += gcnew System::EventHandler(this, &Form1::label13_Click);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label14->Location = System::Drawing::Point(901, 55);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(129, 16);
			this->label14->TabIndex = 34;
			this->label14->Text = L"Okres K STOCHRSI:";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->Location = System::Drawing::Point(901, 96);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(131, 16);
			this->label15->TabIndex = 35;
			this->label15->Text = L"Okres D STOCHRSI:";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->Location = System::Drawing::Point(901, 137);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(128, 16);
			this->label16->TabIndex = 36;
			this->label16->Text = L"Kapitał początkowy:";
			this->label16->Click += gcnew System::EventHandler(this, &Form1::label16_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::LightSteelBlue;
			this->ClientSize = System::Drawing::Size(1058, 476);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->initialCapital);
			this->Controls->Add(this->stochRsiDPeriod);
			this->Controls->Add(this->StochRsiKPeriod);
			this->Controls->Add(this->stochRsiRsiPeriod);
			this->Controls->Add(this->macdSignalPeriod);
			this->Controls->Add(this->macdSlowPeriod);
			this->Controls->Add(this->macdFastPeriod);
			this->Controls->Add(this->stochDPeriod);
			this->Controls->Add(this->stochKPeriod);
			this->Controls->Add(this->MA2);
			this->Controls->Add(this->MA1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->numRsiOverbought);
			this->Controls->Add(this->numRsiOversold);
			this->Controls->Add(this->numRsiPeriod);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->nudSimulationDays);
			this->Controls->Add(this->dataGridViewResults);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->btnRunSimulation);
			this->Controls->Add(this->textBoxFilePath);
			this->Controls->Add(this->btnLoadCSV);
			this->Location = System::Drawing::Point(630, 136);
			this->Name = L"Form1";
			this->Text = L"Aplikacja";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewResults))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudSimulationDays))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numRsiPeriod))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numRsiOversold))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numRsiOverbought))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MA1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MA2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->stochKPeriod))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->stochDPeriod))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->macdFastPeriod))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->macdSlowPeriod))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->macdSignalPeriod))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->stochRsiRsiPeriod))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->StochRsiKPeriod))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->stochRsiDPeriod))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->initialCapital))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		// Obsługa kliknięcia przycisku "Wczytaj Plik CSV"
		System::Void btnLoadCSV_Click(System::Object^ sender, System::EventArgs^ e) {
			if (openFileDialogCSV->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				this->textBoxFilePath->Text = openFileDialogCSV->FileName;

			}
		}
		
		System::Void btnRunSimulation_Click(System::Object^ sender, System::EventArgs^ e) {
			if (String::IsNullOrEmpty(this->textBoxFilePath->Text)) {
				MessageBox::Show(L"Proszę wybrać plik CSV.", L"Błąd", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			std::string filePath = marshal_as<std::string>(this->textBoxFilePath->Text);

			Settings settings;
			settings.csvFilePath = filePath;

			settings.rsiPeriod = static_cast<int>(this->numRsiPeriod->Value);
			settings.rsiOversold = static_cast<double>(this->numRsiOversold->Value);
			settings.rsiOverbought = static_cast<double>(this->numRsiOverbought->Value);
			settings.simulationDays = static_cast<int>(nudSimulationDays->Value);
			settings.maPeriod1 = static_cast<int>(MA1->Value);
			settings.maPeriod2 = static_cast<int>(MA2->Value);
			settings.stochKPeriod = static_cast<int>(stochKPeriod->Value);
			settings.stochDPeriod = static_cast<int>(stochDPeriod->Value);
			settings.macdFastPeriod = static_cast<int>(macdFastPeriod->Value);
			settings.macdSlowPeriod = static_cast<int>(macdSlowPeriod->Value);
			settings.macdSignalPeriod = static_cast<int>(macdSignalPeriod->Value);
			settings.stochRsiRsiPeriod = static_cast<int>(stochRsiRsiPeriod->Value);
			settings.StochRsiKPeriod = static_cast<int>(StochRsiKPeriod->Value);
			settings.stochRsiDPeriod = static_cast<int>(stochRsiDPeriod->Value);
			settings.initialCapital = static_cast<int>(initialCapital->Value);
			
			

			AppLogic logic;
			std::string consoleOutput; 

		
			std::vector<PerformanceReport> reports = logic.runSimulation(settings, consoleOutput);
			System::String^ numReportsMsg = L"Liczba wygenerowanych raportów: " + reports.size().ToString();
			MessageBox::Show(numReportsMsg, "Status Symulacji", MessageBoxButtons::OK, MessageBoxIcon::Information);
			// Wyświetl wyniki w DataGridView
			// Wyczyść poprzednie rezultaty
			this->dataGridViewResults->Rows->Clear(); 
			this->dataGridViewResults->Columns->Clear(); 

			// Add columns to DataGridView
			this->dataGridViewResults->Columns->Add("IndicatorName", L"Wskaźnik/Strategia");
			this->dataGridViewResults->Columns->Add("InitialCapital", L"Kapitał początkowy");
			this->dataGridViewResults->Columns->Add("FinalCapital", L"Kapitał końcowy");
			this->dataGridViewResults->Columns->Add("TotalProfitPoints", "Zysk (pkt)");
			this->dataGridViewResults->Columns->Add("PercentageGain", "Zysk (%)");
			this->dataGridViewResults->Columns->Add("TotalTrades", "Liczba transakcji");
			this->dataGridViewResults->Columns->Add("WinningTrades", "Zyskownych transakcji");
			this->dataGridViewResults->Columns->Add("WinRate", "Procent zyskownych (%)");

		
			this->dataGridViewResults->Columns[0]->Width = 200;
			this->dataGridViewResults->Columns[1]->Width = 120;
			this->dataGridViewResults->Columns[2]->Width = 120;
			this->dataGridViewResults->Columns[3]->Width = 100;
			this->dataGridViewResults->Columns[4]->Width = 80;
			this->dataGridViewResults->Columns[5]->Width = 100;
			this->dataGridViewResults->Columns[6]->Width = 150;
			this->dataGridViewResults->Columns[7]->Width = 120;
			
			// Wypełnij DataGridView danymi z raportów
			for each (const auto & report in reports) {
				double winRate = (report.totalTrades > 0) ? (static_cast<double>(report.winningTrades) / report.totalTrades * 100.0) : 0.0;

				this->dataGridViewResults->Rows->Add(
					marshal_as<String^>(report.indicatorName),
					report.initialCapital.ToString("F2"),
					report.finalCapital.ToString("F2"),
					report.totalProfitPoints.ToString("F2"),
					report.percentageGain.ToString("F2"),
					report.totalTrades.ToString(),
					report.winningTrades.ToString(),
					winRate.ToString("F1")
				);
			}
			
			// Domyślne sortowanie DataGridView według kolumny 'PercentageGain' w kolejności malejącej 
			if (this->dataGridViewResults->Columns->Contains("PercentageGain")) {
				this->dataGridViewResults->Sort(this->dataGridViewResults->Columns["PercentageGain"], System::ComponentModel::ListSortDirection::Descending);
			}
			// Wyświetl output z konsoli w MessageBoxie
			System::String^ consoleOutputManaged = marshal_as<System::String^>(consoleOutput); // Konwersja na String^
			if (!String::IsNullOrEmpty(consoleOutputManaged->Trim())) { // Teraz .Trim() jest wywoływane na zmiennej
				MessageBox::Show(consoleOutputManaged, "Informacje z Logiki", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
		}
	private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void numRsiOverbought_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label3_Click_1(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label16_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void stochRsiRsiPeriod_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label11_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label13_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label12_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}