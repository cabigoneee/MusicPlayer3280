#pragma once

#include "MP.h"
#include "sqlite3.h"
#include "httpclient.h"
#include "httpserver.h"
#include <string>

namespace testCLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		bool playing = 0;
		bool mute = 0;
		bool streamMode = 0;
		int playingSongIndex;
		int soundTrackBarIndex;
		BackgroundWorker m_oWorker;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::TextBox^  textBox1;







	private: System::Windows::Forms::TextBox^  textBox2;

	private: System::Windows::Forms::Label^  label5;











	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::Button^  button12;

	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column6;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column7;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column8;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column11;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column9;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column10;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column12;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column13;























	public:
		float currentTime = 0;
		MyForm(void)
		{
			InitMusicPlayer();
			InitializeComponent();
			//m_oWorker = new BackgroundWorker();
			//
			//TODO: Add the constructor code here
			//

			//OpenFile("C:/Users/User/Desktop/08_piece_of_cake.wav");
			//SelectMusic("C:/Users/User/Desktop/08_piece_of_cake.wav");
			//playing = 1;

			soundTrackBarIndex = trackBar2->Value;
			/*
			dataGridView1->Rows->Add("piece of cake", "shiho x rika", "idolm@ster", "4:20", "offline", "C:/Users/User/Desktop/08_piece_of_cake.wav");
			dataGridView1->Rows->Add("sweet sweet soul", "serika x akane x tamaki", "idolm@ster", "4:53", "offline", "C:/Users/User/Desktop/Sweet_Sweet_Soul.wav");
			dataGridView1->Rows->Add("no curry no life", "anna x rio x kana", "idolm@ster", "3:59", "offline", "C:/Users/User/Desktop/NO_CURRY_NO_LIFE.wav");
			*/
			sqlite3 *db;
			int rc = sqlite3_open("songDB1.db", &db);
			char *error;

			if (rc)
			{
				sqlite3_close(db);

				wchar_t buf[100];
				swprintf_s(buf, 100, L"Error opening SQLite3 database\n");
				OutputDebugString(buf);
			}
			else
			{
				wchar_t buf[100];
				swprintf_s(buf, 100, L"Opened songDB.db.\n");
				OutputDebugString(buf);
			}
			/*
			// Execute SQL
			cout << "Inserting a value into MyTable ..." << endl;
			const char *sqlInsert = "INSERT INTO Song VALUES(NULL, 'Piece of Cake', 'shino', 'idol', '4:59', 'offline', 'C:/Users/User/Desktop/08_piece_of_cake.wav', NULL);";
			rc = sqlite3_exec(db, sqlInsert, NULL, NULL, &error);
			if (rc)
			{
			wchar_t buf[100];
			swprintf_s(buf, 100, L"%s\n", sqlite3_errmsg(db));
			OutputDebugString(buf);
			}
			else
			{
			wchar_t buf[100];
			swprintf_s(buf, 100, L"Inserted data\n");
			OutputDebugString(buf);
			}
			*/


			// Display MyTable
			cout << "Retrieving values in MyTable ..." << endl;
			//const char *sqlSelect = "SELECT * FROM song;";
			string para1 = "SELECT ";
			string parameter = "*";
			string para2 = " FROM song;";
			string fullPara = para1 + parameter + para2;
			const char *sqlSelect = fullPara.c_str();
			char **results = NULL;
			int rows, columns;
			sqlite3_get_table(db, sqlSelect, &results, &rows, &columns, &error);
			if (rc)
			{
				cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
				sqlite3_free(error);
			}
			else
			{
				// Display Table
				for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
				{
					string songBuffer[12];
					int index = 0;
					int rowIndex = 0;
					if (rowCtr != 0) {
						rowIndex = dataGridView1->Rows->Add();
						wchar_t buf[100];
						//swprintf_s(buf, 100, L"%s ", results[cellPosition]);
						swprintf_s(buf, 100, L"row Index: %d\n ", rowIndex);
						OutputDebugString(buf);
					}
					for (int colCtr = 0; colCtr < columns; ++colCtr)
					{
						// Determine Cell Position
						int cellPosition = (rowCtr * columns) + colCtr;

						songBuffer[index] = results[cellPosition];

						wchar_t buf[100];
						//swprintf_s(buf, 100, L"%s ", results[cellPosition]);
						swprintf_s(buf, 100, L"%s ", songBuffer[index].c_str());
						OutputDebugString(buf);

						if (index >= 1 && index <= 12 && rowCtr != 0) {
							System::String^ strNew = gcnew String(songBuffer[index].c_str());
							if (index == 5) {
								dataGridView1->Rows[rowIndex]->Cells[index - 1]->Value = "Local";
							}
							else {
								dataGridView1->Rows[rowIndex]->Cells[index - 1]->Value = strNew;
							}
						}

						index++;

					}

					wchar_t buf[100];
					swprintf_s(buf, 100, L"\n");
					OutputDebugString(buf);

					//Songs newSong(stoi(songBuffer[0]), songBuffer[1], songBuffer[2], songBuffer[3], songBuffer[4], songBuffer[5], songBuffer[6], songBuffer[7]);


				}
			}
			sqlite3_free_table(results);

			// Close Database
			//cout << "Closing MyDb.db ..." << endl;
			sqlite3_close(db);
			//cout << "Closed MyDb.db" << endl << endl;

			//streaming as host automatically when the application startes
			int hostSetup = startDaemon();
			if (hostSetup == 0) {
				//success
				wchar_t buf[100];
				swprintf_s(buf, 100, L"Host setup successfully\n");
				OutputDebugString(buf);
			}
			else {
				wchar_t buf[100];
				swprintf_s(buf, 100, L"Failed to setup host for streaming\n");
				OutputDebugString(buf);
			}

		}



	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::TrackBar^  trackBar2;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column11 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column9 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column10 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column12 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column13 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"PMingLiU", 20));
			this->label1->Location = System::Drawing::Point(155, 54);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(109, 27);
			this->label1->TabIndex = 0;
			this->label1->Text = L"songTitle";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"PMingLiU", 16));
			this->label2->Location = System::Drawing::Point(156, 84);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(102, 22);
			this->label2->TabIndex = 1;
			this->label2->Text = L"song Artist";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(150, 150);
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::Control;
			this->button1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.BackgroundImage")));
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->Location = System::Drawing::Point(549, 41);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(62, 62);
			this->button1->TabIndex = 3;
			this->button1->TabStop = false;
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::Previous_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::SystemColors::Control;
			this->button2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.BackgroundImage")));
			this->button2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button2->Location = System::Drawing::Point(617, 41);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(62, 62);
			this->button2->TabIndex = 4;
			this->button2->TabStop = false;
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::Play_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::SystemColors::Control;
			this->button3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button3.BackgroundImage")));
			this->button3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button3->Location = System::Drawing::Point(685, 41);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(62, 62);
			this->button3->TabIndex = 5;
			this->button3->TabStop = false;
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::Next_Click);
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(489, 114);
			this->trackBar1->Maximum = 100;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(315, 45);
			this->trackBar1->TabIndex = 6;
			this->trackBar1->TabStop = false;
			this->trackBar1->TickStyle = System::Windows::Forms::TickStyle::None;
			// 
			// button4
			// 
			this->button4->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button4.BackgroundImage")));
			this->button4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button4->Location = System::Drawing::Point(1105, 12);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(30, 30);
			this->button4->TabIndex = 7;
			this->button4->TabStop = false;
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::Volume_Click);
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(1136, 12);
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(140, 45);
			this->trackBar2->TabIndex = 8;
			this->trackBar2->TabStop = false;
			this->trackBar2->Value = 10;
			this->trackBar2->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::Volume_Select);
			// 
			// button5
			// 
			this->button5->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button5.BackgroundImage")));
			this->button5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button5->Location = System::Drawing::Point(503, 61);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(40, 40);
			this->button5->TabIndex = 9;
			this->button5->TabStop = false;
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::Backward_Click);
			// 
			// button6
			// 
			this->button6->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button6.BackgroundImage")));
			this->button6->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button6->Location = System::Drawing::Point(753, 61);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(40, 40);
			this->button6->TabIndex = 10;
			this->button6->TabStop = false;
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::Forward_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->AllowUserToResizeRows = false;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(13) {
				this->Column1,
					this->Column2, this->Column3, this->Column4, this->Column5, this->Column6, this->Column7, this->Column8, this->Column11, this->Column9,
					this->Column10, this->Column12, this->Column13
			});
			this->dataGridView1->Location = System::Drawing::Point(53, 201);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dataGridView1->Size = System::Drawing::Size(850, 230);
			this->dataGridView1->TabIndex = 11;
			this->dataGridView1->TabStop = false;
			this->dataGridView1->CellDoubleClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::Table_Select);
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"Title";
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			this->Column1->Width = 300;
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Artist";
			this->Column2->Name = L"Column2";
			this->Column2->ReadOnly = true;
			this->Column2->Width = 150;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"Album";
			this->Column3->Name = L"Column3";
			this->Column3->ReadOnly = true;
			this->Column3->Width = 150;
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"Duration";
			this->Column4->Name = L"Column4";
			this->Column4->ReadOnly = true;
			// 
			// Column5
			// 
			this->Column5->HeaderText = L"Online/Offline";
			this->Column5->Name = L"Column5";
			this->Column5->ReadOnly = true;
			this->Column5->Width = 150;
			// 
			// Column6
			// 
			this->Column6->HeaderText = L"Song Path";
			this->Column6->Name = L"Column6";
			this->Column6->ReadOnly = true;
			this->Column6->Width = 150;
			// 
			// Column7
			// 
			this->Column7->HeaderText = L"Lyrics Path";
			this->Column7->Name = L"Column7";
			this->Column7->ReadOnly = true;
			this->Column7->Width = 50;
			// 
			// Column8
			// 
			this->Column8->HeaderText = L"Image Path";
			this->Column8->Name = L"Column8";
			this->Column8->ReadOnly = true;
			// 
			// Column11
			// 
			this->Column11->HeaderText = L"Checksum";
			this->Column11->Name = L"Column11";
			this->Column11->ReadOnly = true;
			// 
			// Column9
			// 
			this->Column9->HeaderText = L"Remote IP1";
			this->Column9->Name = L"Column9";
			this->Column9->ReadOnly = true;
			this->Column9->Width = 120;
			// 
			// Column10
			// 
			this->Column10->HeaderText = L"Port1";
			this->Column10->Name = L"Column10";
			this->Column10->ReadOnly = true;
			this->Column10->Width = 50;
			// 
			// Column12
			// 
			this->Column12->HeaderText = L"Remote IP2";
			this->Column12->Name = L"Column12";
			this->Column12->ReadOnly = true;
			this->Column12->Width = 120;
			// 
			// Column13
			// 
			this->Column13->HeaderText = L"Port2";
			this->Column13->Name = L"Column13";
			this->Column13->ReadOnly = true;
			this->Column13->Width = 50;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(442, 114);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(51, 12);
			this->label3->TabIndex = 12;
			this->label3->Text = L"TimeNow";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(810, 114);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(62, 12);
			this->label4->TabIndex = 13;
			this->label4->Text = L"SongLength";
			// 
			// button7
			// 
			this->button7->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button7.BackgroundImage")));
			this->button7->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button7->Location = System::Drawing::Point(1242, 48);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(30, 30);
			this->button7->TabIndex = 14;
			this->button7->TabStop = false;
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Visible = false;
			// 
			// button8
			// 
			this->button8->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button8.BackgroundImage")));
			this->button8->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button8->Location = System::Drawing::Point(1206, 48);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(30, 30);
			this->button8->TabIndex = 15;
			this->button8->TabStop = false;
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Visible = false;
			// 
			// button9
			// 
			this->button9->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button9.BackgroundImage")));
			this->button9->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button9->Location = System::Drawing::Point(1170, 48);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(30, 30);
			this->button9->TabIndex = 16;
			this->button9->TabStop = false;
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Visible = false;
			// 
			// button10
			// 
			this->button10->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button10.BackgroundImage")));
			this->button10->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button10->Location = System::Drawing::Point(1136, 48);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(30, 30);
			this->button10->TabIndex = 17;
			this->button10->TabStop = false;
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Visible = false;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(926, 114);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(346, 317);
			this->textBox1->TabIndex = 18;
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox1->WordWrap = false;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(218, 173);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(211, 22);
			this->textBox2->TabIndex = 19;
			this->textBox2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::Enter_Press);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"PMingLiU", 15));
			this->label5->Location = System::Drawing::Point(149, 173);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(63, 20);
			this->label5->TabIndex = 21;
			this->label5->Text = L"Search:";
			// 
			// button11
			// 
			this->button11->BackColor = System::Drawing::Color::Yellow;
			this->button11->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button11->Location = System::Drawing::Point(926, 12);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(75, 23);
			this->button11->TabIndex = 22;
			this->button11->Text = L"Go Stream";
			this->button11->UseVisualStyleBackColor = false;
			this->button11->Click += gcnew System::EventHandler(this, &MyForm::Change_Stream_Mode_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(928, 57);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(25, 12);
			this->label6->TabIndex = 23;
			this->label6->Text = L"PC1";
			this->label6->Visible = false;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(928, 84);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(25, 12);
			this->label7->TabIndex = 24;
			this->label7->Text = L"PC2";
			this->label7->Visible = false;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(966, 38);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(55, 12);
			this->label8->TabIndex = 25;
			this->label8->Text = L"IP Address";
			this->label8->Visible = false;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(1049, 38);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(24, 12);
			this->label9->TabIndex = 26;
			this->label9->Text = L"Port";
			this->label9->Visible = false;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(959, 53);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(85, 22);
			this->textBox3->TabIndex = 27;
			this->textBox3->Text = L"localhost";
			this->textBox3->Visible = false;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(959, 81);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(85, 22);
			this->textBox4->TabIndex = 29;
			this->textBox4->Text = L"localhost";
			this->textBox4->Visible = false;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(1051, 53);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(29, 22);
			this->textBox5->TabIndex = 28;
			this->textBox5->Text = L"8080";
			this->textBox5->Visible = false;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(1051, 81);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(29, 22);
			this->textBox6->TabIndex = 30;
			this->textBox6->Text = L"8080";
			this->textBox6->Visible = false;
			// 
			// button12
			// 
			this->button12->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button12.BackgroundImage")));
			this->button12->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button12->Location = System::Drawing::Point(1086, 61);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(30, 30);
			this->button12->TabIndex = 31;
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Visible = false;
			this->button12->Click += gcnew System::EventHandler(this, &MyForm::Connect_Click);
			// 
			// button13
			// 
			this->button13->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button13.BackgroundImage")));
			this->button13->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button13->Location = System::Drawing::Point(1242, 81);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(30, 30);
			this->button13->TabIndex = 33;
			this->button13->TabStop = false;
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Visible = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(1284, 461);
			this->Controls->Add(this->button13);
			this->Controls->Add(this->button12);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->button11);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button10);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->trackBar2);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Play_Click(System::Object^  sender, System::EventArgs^  e) {
		System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
		if (playing) {
			playing = 0;
			currentTime = GetCurrentPlaybackTime();

			wchar_t buf[100];
			swprintf_s(buf, 100, L"stopped, Current Time Now %f\n", currentTime);
			OutputDebugString(buf);

			button2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button9.BackgroundImage")));

			PauseMusic();
			//ClosePlayer();			
		}
		else {
			currentTime = GetCurrentPlaybackTime();

			wchar_t buf[100];
			swprintf_s(buf, 100, L"playing, Current Time Now %f\n", currentTime);
			OutputDebugString(buf);

			button2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button10.BackgroundImage")));

			//when play button is clicked, check if resume the same song or play new song
			System::String^ selectedSong;
			selectedSong = dataGridView1->Rows[dataGridView1->SelectedCells[0]->RowIndex]->Cells[0]->Value->ToString();

			System::String^ currentSong;
			currentSong = label1->Text;

			if (String::Compare(selectedSong, currentSong) == 0) {
				//same
				RestartMusic();
			}
			else {
				//not same
				//update info first before playing the song
				updateSongInfo();

				System::String^ selectedSongPath;
				selectedSongPath = dataGridView1->Rows[dataGridView1->SelectedCells[0]->RowIndex]->Cells[5]->Value->ToString();
				string songPath;
				MarshalString(selectedSongPath, songPath);

				playingSongIndex = dataGridView1->SelectedCells[0]->RowIndex;
				SelectMusic(songPath.c_str()); // convert string to char*
			}
			playing = 1;
		}
	}
	private: System::Void Forward_Click(System::Object^  sender, System::EventArgs^  e) {
		SkipSecond(10000);
		currentTime = GetCurrentPlaybackTime();

		wchar_t buf[100];
		swprintf_s(buf, 100, L"10s rewind, Current Time Now %f\n", currentTime);
		OutputDebugString(buf);
	}
	private: System::Void Backward_Click(System::Object^  sender, System::EventArgs^  e) {
		SkipSecond(-10000);
		currentTime = GetCurrentPlaybackTime();

		wchar_t buf[100];
		swprintf_s(buf, 100, L"10s forward, Current Time Now %f\n", currentTime);
		OutputDebugString(buf);
	}
	private: System::Void Volume_Click(System::Object^  sender, System::EventArgs^  e) {
		System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
		if (mute) {
			trackBar2->Value = soundTrackBarIndex;
			mute = 0;
			button4->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button7.BackgroundImage")));
		}
		else {
			trackBar2->Value = 0;
			mute = 1;
			button4->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button8.BackgroundImage")));
		}

		int soundValue = trackBar2->Value * 6553;
		unsigned short value = (unsigned short)soundValue;

		SetVolume(value, value);

	}
			 //converting String^ to char*
			 void MarshalString(String ^ s, string& os) {
				 using namespace Runtime::InteropServices;
				 const char* chars =
					 (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
				 os = chars;
				 Marshal::FreeHGlobal(IntPtr((void*)chars));
			 }

	private: System::Void Table_Select(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {

		System::String^ selectedSongPath;
		selectedSongPath = dataGridView1->Rows[dataGridView1->SelectedCells[0]->RowIndex]->Cells[5]->Value->ToString();
		string songPath;
		MarshalString(selectedSongPath, songPath);
		wchar_t buf[100];
		swprintf_s(buf, 100, L"selected row: \n", dataGridView1->SelectedCells[0]->RowIndex);
		OutputDebugString(buf);
		swprintf_s(buf, 100, L"selected column: \n", dataGridView1->SelectedCells[0]->ColumnIndex);
		OutputDebugString(buf);
		swprintf_s(buf, 100, L"selected song path: \n", songPath);
		OutputDebugString(buf);
		swprintf_s(buf, 100, L"dfjaldkjfalkjdflkajsldkfj: \n", selectedSongPath);
		OutputDebugString(buf);

		playingSongIndex = dataGridView1->SelectedCells[0]->RowIndex;
		SelectMusic(songPath.c_str()); // convert string to char*
		playing = 1;

		System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
		button2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button10.BackgroundImage")));

		//update info first before playing the song
		updateSongInfo();
	}

	private: System::Void Next_Click(System::Object^  sender, System::EventArgs^  e) {
		playingSongIndex++;

		System::String^ selectedSongPath = dataGridView1->Rows[playingSongIndex]->Cells[5]->Value->ToString();
		string songPath;
		MarshalString(selectedSongPath, songPath);

		SelectMusic(songPath.c_str()); // convert string to char*
		playing = 1;

		System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
		button2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button10.BackgroundImage")));

		dataGridView1->CurrentCell = dataGridView1->Rows[playingSongIndex]->Cells[0];

		updateSongInfo();
	}

	private: System::Void Previous_Click(System::Object^  sender, System::EventArgs^  e) {
		playingSongIndex--;

		System::String^ selectedSongPath = dataGridView1->Rows[playingSongIndex]->Cells[5]->Value->ToString();
		string songPath;
		MarshalString(selectedSongPath, songPath);

		SelectMusic(songPath.c_str()); // convert string to char*
		playing = 1;

		System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
		button2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button10.BackgroundImage")));

		dataGridView1->CurrentCell = dataGridView1->Rows[playingSongIndex]->Cells[0];

		updateSongInfo();
	}

	private: void updateSongInfo() {
		System::String^ selectedSongTitle;
		selectedSongTitle = dataGridView1->Rows[dataGridView1->SelectedCells[0]->RowIndex]->Cells[0]->Value->ToString();
		label1->Text = selectedSongTitle;

		System::String^ selectedSongArtist;
		selectedSongArtist = dataGridView1->Rows[dataGridView1->SelectedCells[0]->RowIndex]->Cells[1]->Value->ToString();
		label2->Text = selectedSongArtist;

		//update song length
		int selectedSongDuration = GetTotalDuration() / 1000;
		int minute = selectedSongDuration / 60;
		int second = selectedSongDuration % 60;
		string divider = ":";
		if (second < 10) {
			divider = ":0";
		}
		string songDuration = std::to_string(minute) + divider + std::to_string(second);//int to ^str
		System::String^ strNew = gcnew String(songDuration.c_str());

		label4->Text = strNew;

		//update image 
		System::String^ selectedImagePath;
		selectedImagePath = dataGridView1->Rows[dataGridView1->SelectedCells[0]->RowIndex]->Cells[7]->Value->ToString();
		/*
		if (String::Compare(selectedImagePath, "null") == 0) {
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button13.BackgroundImage")));
		}
		else {
			pictureBox1->BackgroundImage = Image::FromFile(selectedImagePath);
		}
		*/
		try
		{
			pictureBox1->BackgroundImage = Image::FromFile(selectedImagePath);
		}
		catch (Exception^ e)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button13.BackgroundImage")));
		}

		//update lyrics table
		textBox1->Visible = false;
		textBox1->Text = "";
		String^ selectedLyricsPath;
		selectedLyricsPath = dataGridView1->Rows[dataGridView1->SelectedCells[0]->RowIndex]->Cells[6]->Value->ToString();
		try
		{
			wchar_t buf[100];
			swprintf_s(buf, 100, L"trying to open file: %s\n ", selectedLyricsPath);
			OutputDebugString(buf);
			StreamReader^ dine = gcnew StreamReader(selectedLyricsPath, System::Text::Encoding::UTF8);
			//textBox1->Text = "Hello";

			String^ str;
			int count = 0;
			while ((str = dine->ReadLine()) != nullptr)
			{
				count++;
				textBox1->AppendText(str);
				textBox1->AppendText("\n");
			}
			textBox1->Select(0, 1);
			textBox1->ScrollToCaret();
			textBox1->Focus();
			textBox1->DeselectAll();
			textBox1->Visible = true;
		}
		catch (Exception^ e)
		{
			if (dynamic_cast<FileNotFoundException^>(e)) {
				wchar_t buf[100];
				swprintf_s(buf, 100, L"file not found: %s\n ", selectedLyricsPath);
				OutputDebugString(buf);
				textBox1->AppendText("No Lyrics File, plz input file path in db\n");
				textBox1->Visible = true;
			}
			else {
				wchar_t buf[100];
				swprintf_s(buf, 100, L"error reading file: %s\n ", selectedLyricsPath);
				OutputDebugString(buf);
				textBox1->AppendText("error reading file:\n");
				textBox1->AppendText(selectedLyricsPath);
				textBox1->Visible = true;
			}
		}

		bgTimer();
	}

	private: void bgTimer() {
		//a background worker that keeps track of song progress bar



	}

	private: System::Void Volume_Select(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		soundTrackBarIndex = trackBar2->Value;
		int soundValue = trackBar2->Value * 6553;

		/*
		std::string hex = "0123456789ABCDEF";
		std::string res;
		while (soundValue > 0)
		{
		res = hex[soundValue % 16] + res;
		soundValue /= 16;
		}
		string value = "0x" + std::to_string(soundValue);
		*/
		unsigned short value = (unsigned short)soundValue;

		SetVolume(value, value);

		wchar_t buf[100];
		swprintf_s(buf, 100, L"trackBar: %hu\n", value);
		OutputDebugString(buf);
	}

	private: System::Void Enter_Press(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (e->KeyCode == Keys::Enter) {
			wchar_t buf[100];
			swprintf_s(buf, 100, L"search button clicked!!\n");
			OutputDebugString(buf);

			System::String^ searchedParameter;
			searchedParameter = textBox2->Text;
			string parameter;
			MarshalString(searchedParameter, parameter);

			sqlite3 *db;
			int rc = sqlite3_open("songDB.db", &db);
			char *error;

			if (rc)
			{
				sqlite3_close(db);

				swprintf_s(buf, 100, L"Error opening SQLite3 database\n");
				OutputDebugString(buf);
			}
			else
			{
				swprintf_s(buf, 100, L"Search Bar: Opened songDB.db.\n");
				OutputDebugString(buf);
			}

			swprintf_s(buf, 100, L"search parameter: %s\n ", parameter.c_str());
			OutputDebugString(buf);
			string fullPara;
			if (parameter.empty() == true) {
				//string is empty
				fullPara = "SELECT * FROM song";
			}
			else {
				string para1 = "SELECT * FROM song WHERE";
				fullPara = para1;
				string column[11] = { "Title", "Artist", "Album", "Duration", "Location", "songPath", "lyricsPath", "imagePath", "remoteIP", "port", "checksum" };
				for (int i = 0; i < 11; i++) {
					string likePara = "'%" + parameter + "%'";
					fullPara = fullPara + " " + column[i] + " LIKE " + likePara;
					if (i < 10) {
						fullPara = fullPara + " OR";
					}
				}
			}


			//swprintf_s(buf, 100, L"%s ", results[cellPosition]);
			const char *sqlSelect = fullPara.c_str();
			char **results = NULL;
			int rows, columns;
			wchar_t buff[1000];
			swprintf_s(buff, 1000, L"search Path: %s\n ", sqlSelect);
			OutputDebugString(buff);
			sqlite3_get_table(db, sqlSelect, &results, &rows, &columns, &error);
			if (rc)
			{
				cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
				sqlite3_free(error);
			}
			else
			{
				dataGridView1->Rows->Clear();
				// Display Table
				for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
				{
					string songBuffer[12];
					int index = 0;
					int rowIndex = 0;
					if (rowCtr != 0) {
						rowIndex = dataGridView1->Rows->Add();
						wchar_t buf[100];
						//swprintf_s(buf, 100, L"%s ", results[cellPosition]);
						swprintf_s(buf, 100, L"row Index: %d\n ", rowIndex);
						OutputDebugString(buf);
					}
					for (int colCtr = 0; colCtr < columns; ++colCtr)
					{
						// Determine Cell Position
						int cellPosition = (rowCtr * columns) + colCtr;

						songBuffer[index] = results[cellPosition];

						wchar_t buf[100];
						//swprintf_s(buf, 100, L"%s ", results[cellPosition]);
						swprintf_s(buf, 100, L"%s ", songBuffer[index].c_str());
						OutputDebugString(buf);

						if (index >= 1 && index <= 12 && rowCtr != 0) {
							System::String^ strNew = gcnew String(songBuffer[index].c_str());
							if (index == 5) {
								dataGridView1->Rows[rowIndex]->Cells[index - 1]->Value = "Local";
							}
							else {
								dataGridView1->Rows[rowIndex]->Cells[index - 1]->Value = strNew;
							}
						}

						index++;

					}

					wchar_t buf[100];
					swprintf_s(buf, 100, L"\n");
					OutputDebugString(buf);

					//Songs newSong(stoi(songBuffer[0]), songBuffer[1], songBuffer[2], songBuffer[3], songBuffer[4], songBuffer[5], songBuffer[6], songBuffer[7]);


				}
			}
			sqlite3_free_table(results);

			// Close Database
			//cout << "Closing MyDb.db ..." << endl;
			sqlite3_close(db);
		}
	}
	private: System::Void Change_Stream_Mode_Click(System::Object^  sender, System::EventArgs^  e) {
		if (streamMode) {
			//stream mode to local mode
			label6->Visible = false;
			label7->Visible = false;
			label8->Visible = false;
			label9->Visible = false;
			textBox3->Visible = false;
			textBox4->Visible = false;
			textBox5->Visible = false;
			textBox6->Visible = false;
			button12->Visible = false;
			button11->Text = "Go Stream";

			streamMode = false;
		}
		else {
			//local mode to stream mode
			label6->Visible = true;
			label7->Visible = true;
			label8->Visible = true;
			label9->Visible = true;
			textBox3->Visible = true;
			textBox4->Visible = true;
			textBox5->Visible = true;
			textBox6->Visible = true;
			button12->Visible = true;
			button11->Text = "Go Local";

			streamMode = true;
		}
	}
	private: System::Void Connect_Click(System::Object^  sender, System::EventArgs^  e) {

		textBox1->Text = "";
		textBox1->Visible = true;
		textBox1->AppendText("input received! Now test connection\n");

		System::String^ IP_PC1;
		IP_PC1 = textBox3->Text;
		string IPPC1;
		MarshalString(IP_PC1, IPPC1);

		System::String^ port_PC1;
		port_PC1 = textBox5->Text;
		string portPC1;
		MarshalString(port_PC1, portPC1);

		System::String^ IP_PC2;
		IP_PC2 = textBox4->Text;
		string IPPC2;
		MarshalString(IP_PC2, IPPC2);

		System::String^ port_PC2;
		port_PC2 = textBox6->Text;
		string portPC2;
		MarshalString(port_PC2, portPC2);

		wchar_t buf[100];
		swprintf_s(buf, 100, L"PC1's IP: %s:%s\n ", IPPC1.c_str(), portPC1.c_str());
		OutputDebugString(buf);
		swprintf_s(buf, 100, L"PC2's IP: %s:%s\n ", IPPC2.c_str(), portPC2.c_str());
		OutputDebugString(buf);

		int connection1 = test_connection(IPPC1.c_str(), stoi(portPC1));
		int connection2 = test_connection(IPPC2.c_str(), stoi(portPC2));

		if (connection1 == 0 && connection2 == 0) {
			//both success
			textBox1->AppendText("Connection Success\n!");
			swprintf_s(buf, 100, L"Connection Completed!\n");
			OutputDebugString(buf);

			UpdateDatabase(IPPC1.c_str(), stoi(portPC1), IPPC2.c_str(), stoi(portPC1));
		}
		else if (connection1 == 0 && connection2 != 0) {
			textBox1->AppendText("Fail to connect to PC2.\n");
			swprintf_s(buf, 100, L"Failed to connect to PC2\n");
			OutputDebugString(buf);
		}
		else if (connection1 != 0 && connection2 == 0) {
			textBox1->AppendText("Fail to connect to PC1.\n");
			swprintf_s(buf, 100, L"Failed to connect to PC1\n");
			OutputDebugString(buf);
		}
		else {
			textBox1->AppendText("Fail to connect both.\n");
			swprintf_s(buf, 100, L"Failed to connect to both PC1 and PC2\n");
			OutputDebugString(buf);
		}

		

	}

	private: void UpdateDatabase(const char* IP1, int port1, const char* IP2, int port2) {

		//get local song's checksum
		int localRows = dataGridView1->Rows->Count;
		wchar_t buf[100];
		swprintf_s(buf, 100, L"Number of Local Row Counts: %d\n", localRows);
		OutputDebugString(buf);

		string localChecksum[10]; //hardcode there is only 10 songs in local
		for (int i = 0; i < localRows; i++) {

			System::String^ checksumStr = dataGridView1->Rows[i]->Cells[8]->Value->ToString();
			string checksum;
			MarshalString(checksumStr, checksum);

			localChecksum[i] = checksum;
			swprintf_s(buf, 100, L"Local Checksum: %d -> %s\n", i, localChecksum[i].c_str());
			OutputDebugString(buf);
		}

		//get from PC1
		textBox1->AppendText("trying to download song database from remote PC1......\n");
		int response = get_db(IP1, port1, "temp1.db");
		Sleep(5000);
		if (response == 1) {
			textBox1->AppendText("Fail to get database\n");
		}
		else {
			textBox1->AppendText("Database downloaded successfully\n");
			sqlite3 *db;
			int rc = sqlite3_open("temp1.db", &db);
			char *error;

			if (rc)
			{
				sqlite3_close(db);

				wchar_t buf[100];
				swprintf_s(buf, 100, L"Error opening SQLite3 database\n");
				OutputDebugString(buf);
			}
			else
			{
				wchar_t buf[100];
				swprintf_s(buf, 100, L"Opened songDB.db.\n");
				OutputDebugString(buf);
			}
			/*
			// Execute SQL
			cout << "Inserting a value into MyTable ..." << endl;
			const char *sqlInsert = "INSERT INTO Song VALUES(NULL, 'Piece of Cake', 'shino', 'idol', '4:59', 'offline', 'C:/Users/User/Desktop/08_piece_of_cake.wav', NULL);";
			rc = sqlite3_exec(db, sqlInsert, NULL, NULL, &error);
			if (rc)
			{
			wchar_t buf[100];
			swprintf_s(buf, 100, L"%s\n", sqlite3_errmsg(db));
			OutputDebugString(buf);
			}
			else
			{
			wchar_t buf[100];
			swprintf_s(buf, 100, L"Inserted data\n");
			OutputDebugString(buf);
			}
			*/


			// Display MyTable
			cout << "Retrieving values in MyTable ..." << endl;
			//const char *sqlSelect = "SELECT * FROM song;";
			string para1 = "SELECT ";
			string parameter = "*";
			string para2 = " FROM song;";
			string fullPara = para1 + parameter + para2;
			const char *sqlSelect = fullPara.c_str();
			char **results = NULL;
			int rows, columns;
			sqlite3_get_table(db, sqlSelect, &results, &rows, &columns, &error);
			if (rc)
			{
				cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
				sqlite3_free(error);
			}
			else
			{
				// Display Table
				for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
				{
					string songBuffer[12];
					int index = 0;
					int rowIndex = 0;
					if (rowCtr != 0) {
						rowIndex = dataGridView1->Rows->Add();
						wchar_t buf[100];
						//swprintf_s(buf, 100, L"%s ", results[cellPosition]);
						swprintf_s(buf, 100, L"row Index: %d\n ", rowIndex);
						OutputDebugString(buf);
					}
					for (int colCtr = 0; colCtr < columns; ++colCtr)
					{
						// Determine Cell Position
						int cellPosition = (rowCtr * columns) + colCtr;

						songBuffer[index] = results[cellPosition];

						if (index >= 1 && index <= 12 && rowCtr != 0) {
							System::String^ strNew = gcnew String(songBuffer[index].c_str());
							if (index == 5) {
								dataGridView1->Rows[rowIndex]->Cells[index - 1]->Value = "Stream";
							}
							else {
								dataGridView1->Rows[rowIndex]->Cells[index - 1]->Value = strNew;
							}
						}

						wchar_t buf[100];
						//swprintf_s(buf, 100, L"%s ", results[cellPosition]);
						swprintf_s(buf, 100, L"%s ", songBuffer[index].c_str());
						OutputDebugString(buf);
						index++;

					}

					wchar_t buf[100];
					swprintf_s(buf, 100, L"\n");
					OutputDebugString(buf);

					//Songs newSong(stoi(songBuffer[0]), songBuffer[1], songBuffer[2], songBuffer[3], songBuffer[4], songBuffer[5], songBuffer[6], songBuffer[7]);

					//check if local exists
					if (rowCtr != 0) {
						System::String^ checksumStr = dataGridView1->Rows[rowIndex]->Cells[8]->Value->ToString();
						bool same = false;
						for (int i = 0; i < localRows; i++) {
							wchar_t buf[100];
							string checksum = localChecksum[i];
							System::String^ localChecksumStr = gcnew String(checksum.c_str());
							swprintf_s(buf, 100, L"checking localchecksum str: %d -> %s\n ", i, checksum.c_str());
							OutputDebugString(buf);
							if (String::Compare(checksumStr, localChecksumStr) == 0) {
								same = true;
							}
						}
						if (same) {
							dataGridView1->Rows->Remove(dataGridView1->Rows[rowIndex]);
							swprintf_s(buf, 100, L"deleted Row: %d -> %s\n ", rowIndex);
							OutputDebugString(buf);
							index--;
						}
					}
				}
			}
			sqlite3_free_table(results);

			// Close Database
			//cout << "Closing MyDb.db ..." << endl;
			sqlite3_close(db);
		}

		//get PC2 

		//merge song datum where it has two remote sources
		int totalRows = dataGridView1->Rows->Count;
		swprintf_s(buf, 100, L"Total Rows: %d \n", totalRows);
		OutputDebugString(buf);
		string remote1Checksum[10]; //hardcode there is only 10 songs in local
		for (int i = 0; i < totalRows - localRows; i++) {

			System::String^ checksumStr = dataGridView1->Rows[i + localRows]->Cells[8]->Value->ToString();
			string checksum;
			MarshalString(checksumStr, checksum);

			remote1Checksum[i] = checksum;
			swprintf_s(buf, 100, L"Remote Checksum: %d -> %s\n", i + localRows, remote1Checksum[i].c_str());
			OutputDebugString(buf);
		}

		textBox1->AppendText("trying to download song database from remote PC2......\n");
		response = get_db(IP2, port2, "temp2.db");
		Sleep(5000);
		if (response == 1) {
			textBox1->AppendText("Fail to get database\n");
		}
		else {
			textBox1->AppendText("Database downloaded successfully\n");
			sqlite3 *db;
			int rc = sqlite3_open("temp1.db", &db);
			char *error;

			if (rc)
			{
				sqlite3_close(db);

				wchar_t buf[100];
				swprintf_s(buf, 100, L"Error opening SQLite3 database\n");
				OutputDebugString(buf);
			}
			else
			{
				wchar_t buf[100];
				swprintf_s(buf, 100, L"Opened songDB.db.\n");
				OutputDebugString(buf);
			}
			/*
			// Execute SQL
			cout << "Inserting a value into MyTable ..." << endl;
			const char *sqlInsert = "INSERT INTO Song VALUES(NULL, 'Piece of Cake', 'shino', 'idol', '4:59', 'offline', 'C:/Users/User/Desktop/08_piece_of_cake.wav', NULL);";
			rc = sqlite3_exec(db, sqlInsert, NULL, NULL, &error);
			if (rc)
			{
			wchar_t buf[100];
			swprintf_s(buf, 100, L"%s\n", sqlite3_errmsg(db));
			OutputDebugString(buf);
			}
			else
			{
			wchar_t buf[100];
			swprintf_s(buf, 100, L"Inserted data\n");
			OutputDebugString(buf);
			}
			*/


			// Display MyTable
			cout << "Retrieving values in MyTable ..." << endl;
			//const char *sqlSelect = "SELECT * FROM song;";
			string para1 = "SELECT ";
			string parameter = "*";
			string para2 = " FROM song;";
			string fullPara = para1 + parameter + para2;
			const char *sqlSelect = fullPara.c_str();
			char **results = NULL;
			int rows, columns;
			sqlite3_get_table(db, sqlSelect, &results, &rows, &columns, &error);
			if (rc)
			{
				cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
				sqlite3_free(error);
			}
			else
			{
				// Display Table
				for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
				{
					string songBuffer[12];
					int index = 0;
					int rowIndex = 0;
					if (rowCtr != 0) {
						rowIndex = dataGridView1->Rows->Add();
						wchar_t buf[100];
						//swprintf_s(buf, 100, L"%s ", results[cellPosition]);
						swprintf_s(buf, 100, L"row Index: %d\n ", rowIndex);
						OutputDebugString(buf);
					}
					for (int colCtr = 0; colCtr < columns; ++colCtr)
					{
						// Determine Cell Position
						int cellPosition = (rowCtr * columns) + colCtr;

						songBuffer[index] = results[cellPosition];

						if (index >= 1 && index <= 12 && rowCtr != 0) {
							System::String^ strNew = gcnew String(songBuffer[index].c_str());
							if (index == 5) {
								dataGridView1->Rows[rowIndex]->Cells[index - 1]->Value = "Stream";
							}
							else {
								dataGridView1->Rows[rowIndex]->Cells[index - 1]->Value = strNew;
							}
						}

						wchar_t buf[100];
						//swprintf_s(buf, 100, L"%s ", results[cellPosition]);
						swprintf_s(buf, 100, L"%s ", songBuffer[index].c_str());
						OutputDebugString(buf);
						index++;

					}

					wchar_t buf[100];
					swprintf_s(buf, 100, L"\n");
					OutputDebugString(buf);

					//Songs newSong(stoi(songBuffer[0]), songBuffer[1], songBuffer[2], songBuffer[3], songBuffer[4], songBuffer[5], songBuffer[6], songBuffer[7]);

					//check if local exists
					bool localDeleted = false;
					if (rowCtr != 0) {
						System::String^ checksumStr = dataGridView1->Rows[rowIndex]->Cells[8]->Value->ToString();
						bool same = false;
						for (int i = 0; i < localRows; i++) {
							wchar_t buf[100];
							string checksum = localChecksum[i];
							System::String^ localChecksumStr = gcnew String(checksum.c_str());
							swprintf_s(buf, 100, L"checking localchecksum str: %d -> %s\n ", i, checksum.c_str());
							OutputDebugString(buf);
							if (String::Compare(checksumStr, localChecksumStr) == 0) {
								same = true;
							}
						}
						if (same) {
							dataGridView1->Rows->Remove(dataGridView1->Rows[rowIndex]);
							swprintf_s(buf, 100, L"deleted Row: %d -> %s\n ", rowIndex);
							OutputDebugString(buf);
							index--;
							localDeleted = true;
						}
					}

					//merge duplicated song
					if (!localDeleted) {
						for (int i = 0; i < totalRows - localRows; i++) {
							System::String^ checksumStr = dataGridView1->Rows[rowIndex]->Cells[8]->Value->ToString();
							string checksum = remote1Checksum[i];
							System::String^ remoteChecksumStr = gcnew String(checksum.c_str());
							swprintf_s(buf, 100, L"checking remotechecksum str: %d -> %s\n ", i, checksum.c_str());
							OutputDebugString(buf);
							if (String::Compare(checksumStr, remoteChecksumStr) == 0) {
								dataGridView1->Rows[i + localRows]->Cells[11]->Value = dataGridView1->Rows[rowIndex]->Cells[9]->Value->ToString();
								dataGridView1->Rows[i + localRows]->Cells[12]->Value = dataGridView1->Rows[rowIndex]->Cells[10]->Value->ToString();
								dataGridView1->Rows->Remove(dataGridView1->Rows[rowIndex]);
								swprintf_s(buf, 100, L"Checksums of these two rows are the same: %d & %d\n ", i + localRows, rowIndex);
								OutputDebugString(buf);
								break;
							}
						}
					}				

				}
			}
			sqlite3_free_table(results);

			// Close Database
			//cout << "Closing MyDb.db ..." << endl;
			sqlite3_close(db);


			
			//dataGridView1->Rows[3]->Cells[11]->Value = dataGridView1->Rows[5]->Cells[9]->Value->ToString();
			//dataGridView1->Rows[3]->Cells[12]->Value = dataGridView1->Rows[5]->Cells[10]->Value->ToString();
			//dataGridView1->Rows->Remove(dataGridView1->Rows[5]);

		}

		textBox1->AppendText("Updating Song Table......\n");
		textBox1->AppendText("Streaming Setup Completed !! \n");
	}
};
}
