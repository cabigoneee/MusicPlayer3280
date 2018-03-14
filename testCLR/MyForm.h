#pragma once

#include "MP.h"
#include "sqlite3.h"
#include <string>

namespace testCLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:  
		bool playing = 0;
		bool mute = 0;
		int playingSongIndex;
		int soundTrackBarIndex;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column6;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Button^  button10;
	public:
		float currentTime = 0;
		MyForm(void)
		{
			InitMusicPlayer();
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			//OpenFile("C:/Users/User/Desktop/08_piece_of_cake.wav");
			//SelectMusic("C:/Users/User/Desktop/08_piece_of_cake.wav");
			//playing = 1;

			soundTrackBarIndex = trackBar2->Value;
			
			dataGridView1->Rows->Add("piece of cake", "shiho x rika", "idolm@ster", "4:20", "offline", "C:/Users/User/Desktop/08_piece_of_cake.wav");
			dataGridView1->Rows->Add("sweet sweet soul", "serika x akane x tamaki", "idolm@ster", "4:53", "offline", "C:/Users/User/Desktop/Sweet_Sweet_Soul.wav");
			dataGridView1->Rows->Add("no curry no life", "anna x rio x kana", "idolm@ster", "3:59", "offline", "C:/Users/User/Desktop/NO_CURRY_NO_LIFE.wav");
			dataGridView1->Rows->Add("no curry no life", "anna x rio x kana lkdsjflk asjdlfjalskdjflkasjdfl", "idolm@ster", "3:59", "offline", "C:/Users/User/Desktop/NO_CURRY_NO_LIFE.wav");
			dataGridView1->Rows->Add("no curry no life", "anna x rio x kana", "idolm@ster", "3:59", "offline", "C:/Users/User/Desktop/NO_CURRY_NO_LIFE.wav");
			dataGridView1->Rows->Add("no curry no life", "anna x rio x kana", "idolm@ster", "3:59", "offline", "C:/Users/User/Desktop/NO_CURRY_NO_LIFE.wav");
			dataGridView1->Rows->Add("no curry no life", "anna x rio x kana", "idolm@ster", "3:59", "offline", "C:/Users/User/Desktop/NO_CURRY_NO_LIFE.wav");
			dataGridView1->Rows->Add("no curry no life", "anna x rio x kana", "idolm@ster", "3:59", "offline", "C:/Users/User/Desktop/NO_CURRY_NO_LIFE.wav");
			dataGridView1->Rows->Add("no curry no life", "anna x rio x kana", "idolm@ster", "3:59", "offline", "C:/Users/User/Desktop/NO_CURRY_NO_LIFE.wav");
			dataGridView1->Rows->Add("no curry no life", "anna x rio x kana", "idolm@ster", "3:59", "offline", "C:/Users/User/Desktop/NO_CURRY_NO_LIFE.wav");
			dataGridView1->Rows->Add("no curry no life", "anna x rio x kana", "idolm@ster", "3:59", "offline", "C:/Users/User/Desktop/NO_CURRY_NO_LIFE.wav"); 
			dataGridView1->Rows->Add("no curry no life", "anna x rio x kana", "idolm@ster", "3:59", "offline", "C:/Users/User/Desktop/NO_CURRY_NO_LIFE.wav"); 
			dataGridView1->Rows->Add("no curry no life", "anna x rio x kana", "idolm@ster", "3:59", "offline", "C:/Users/User/Desktop/NO_CURRY_NO_LIFE.wav"); 
			dataGridView1->Rows->Add("no curry no life", "anna x rio x kana", "idolm@ster", "3:59", "offline", "C:/Users/User/Desktop/NO_CURRY_NO_LIFE.wav"); 
			dataGridView1->Rows->Add("no curry no life", "anna x rio x kana", "idolm@ster", "3:59", "offline", "C:/Users/User/Desktop/NO_CURRY_NO_LIFE.wav"); 
			dataGridView1->Rows->Add("no curry no life", "anna x rio x kana", "idolm@ster", "3:59", "offline", "C:/Users/User/Desktop/NO_CURRY_NO_LIFE.wav"); 
			dataGridView1->Rows->Add("no curry no life", "anna x rio x kana", "idolm@ster", "3:59", "offline", "C:/Users/User/Desktop/NO_CURRY_NO_LIFE.wav"); 
			dataGridView1->Rows->Add("no curry no life", "anna x rio x kana", "idolm@ster", "3:59", "offline", "C:/Users/User/Desktop/NO_CURRY_NO_LIFE.wav");
		
			sqlite3 *db;
			int rc = sqlite3_open("MyDb.db", &db);

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
				swprintf_s(buf, 100, L"Error opening SQLite3 database\n");
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
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
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
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(315, 45);
			this->trackBar1->TabIndex = 6;
			this->trackBar1->TabStop = false;
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
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {
				this->Column1,
					this->Column2, this->Column3, this->Column4, this->Column5, this->Column6
			});
			this->dataGridView1->Location = System::Drawing::Point(53, 201);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->dataGridView1->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dataGridView1->Size = System::Drawing::Size(850, 230);
			this->dataGridView1->TabIndex = 11;
			this->dataGridView1->TabStop = false;
			this->dataGridView1->CellDoubleClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::Table_Select);
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"Name";
			this->Column1->Name = L"Column1";
			this->Column1->Width = 130;
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Artist";
			this->Column2->Name = L"Column2";
			this->Column2->Width = 130;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"Album";
			this->Column3->Name = L"Column3";
			this->Column3->Width = 130;
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"Length";
			this->Column4->Name = L"Column4";
			this->Column4->Width = 130;
			// 
			// Column5
			// 
			this->Column5->HeaderText = L"Online/Offline";
			this->Column5->Name = L"Column5";
			this->Column5->Width = 130;
			// 
			// Column6
			// 
			this->Column6->HeaderText = L"Path";
			this->Column6->Name = L"Column6";
			this->Column6->Width = 200;
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
			this->button7->Location = System::Drawing::Point(1069, 12);
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
			this->button8->Location = System::Drawing::Point(1033, 12);
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
			this->button9->Location = System::Drawing::Point(997, 12);
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
			this->button10->Location = System::Drawing::Point(961, 12);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(30, 30);
			this->button10->TabIndex = 17;
			this->button10->TabStop = false;
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Visible = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(1284, 461);
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


			RestartMusic();
			//Playback(currentTime);
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

		int selectedSongDuration = GetTotalDuration() / 1000;
		int minute = selectedSongDuration / 60;
		int second = selectedSongDuration % 60;
		//int to string^
		string songDuration = std::to_string(minute) + ":" + std::to_string(second);
		System::String^ strNew = gcnew String(songDuration.c_str());

		label4->Text = strNew;
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
};
}
