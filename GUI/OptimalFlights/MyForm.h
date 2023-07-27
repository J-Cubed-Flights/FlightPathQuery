#pragma once
#include <string>
#include <chrono>
#include <thread> 
#include <cliext/vector>
#include <msclr\marshal_cppstd.h>

#include "../../src/directedgraph.h"

namespace OptimalFlights {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// This form is used to run the optimal flight path finder
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
		DirectedGraph* graph;
		cliext::vector<String ^>^ strs;
		String^ dHeap_path;
		String^ dHeap_time;
		String^ f_path;
		String^ f_time;
		String^ d_path;
		String^ d_time;
		String^ folderLocation;
		bool dHeapRunning;
		bool fRunning;
		bool dRunning;
		DateTime startTime;
		ReaderWriterLock^ rwl;
	private: System::ComponentModel::BackgroundWorker^ bkgdFloyd;

	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ chooseDataFolderToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ resetToolStripMenuItem;


	private: System::Windows::Forms::ToolStripTextBox^ toolStripTextBox1;

	private: System::Windows::Forms::FolderBrowserDialog^ fbd;
	private: System::ComponentModel::BackgroundWorker^ bkgdCodeLoader;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ dHeapTime;
	private: System::ComponentModel::BackgroundWorker^ bkgdDjik;
	private: System::ComponentModel::BackgroundWorker^ bkgdDjikHeap;




	public:
		MyForm(void)
		{
			folderLocation = "../../data";
			strs = gcnew cliext::vector<String^>();
			graph = new DirectedGraph();
			rwl = gcnew ReaderWriterLock();

			fRunning = false;
			dRunning = false;
			dHeapRunning = false;

			dHeap_path = nullptr;
			dHeap_time = nullptr;

			f_path = nullptr;
			f_time = nullptr;			

			d_path = nullptr;
			d_time = nullptr;
			InitializeComponent();
		}
	private:
		void cleanPaths() {
			if (dHeap_path) {
				delete dHeap_path;
				dHeap_path = nullptr;
			}
			if (dHeap_time) {
				delete dHeap_time;
				dHeap_time = nullptr;
			}
			if (f_path) {
				delete f_path;
				f_path = nullptr;
			}
			if (f_time) {
				delete f_time;
				f_time = nullptr;
			}
			if (d_path) {
				delete d_path;
				d_path = nullptr;
			}
			if (d_time) {
				delete d_time;
				d_time = nullptr;
			}
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (strs) {
				for (int i = 0; i < strs->size(); i++) {
					delete strs[i];
				}
				delete strs;
			}
			cleanPaths();
			if (components)
			{
				delete components;
			}
			if (graph != nullptr) {
				delete graph;
				graph = nullptr;
			}
			if (rwl) {
				delete rwl;
			}
		}
	//TODO: Add DirectedGraph as a member variable here.
	private: System::Windows::Forms::Button^ searchButton;
	private: System::Windows::Forms::TextBox^ start;
	private: System::Windows::Forms::TextBox^ end;
	private: System::Windows::Forms::Label^ startText;
	private: System::Windows::Forms::Label^ destText;
	private: System::Windows::Forms::ListBox^ resultList;
	private: System::Windows::Forms::Label^ DjikstraText;
	private: System::Windows::Forms::Label^ dTime;


	private: System::Windows::Forms::Label^ floydText;
	private: System::Windows::Forms::Label^ fTime;

	private: System::Windows::Forms::Label^ resultText;

	private: System::Windows::Forms::Label^ elapsedtimeText;
	private: System::Windows::Forms::Button^ clearButton;
	private: System::Windows::Forms::ListBox^ airportList;

	private: System::Windows::Forms::Label^ airportTitle;
	private: System::Windows::Forms::Label^ invalidCodeLabel;
private: System::Windows::Forms::Timer^ timerRuntime;



	private: System::ComponentModel::IContainer^ components;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->searchButton = (gcnew System::Windows::Forms::Button());
			this->start = (gcnew System::Windows::Forms::TextBox());
			this->end = (gcnew System::Windows::Forms::TextBox());
			this->startText = (gcnew System::Windows::Forms::Label());
			this->destText = (gcnew System::Windows::Forms::Label());
			this->resultList = (gcnew System::Windows::Forms::ListBox());
			this->DjikstraText = (gcnew System::Windows::Forms::Label());
			this->dTime = (gcnew System::Windows::Forms::Label());
			this->floydText = (gcnew System::Windows::Forms::Label());
			this->fTime = (gcnew System::Windows::Forms::Label());
			this->resultText = (gcnew System::Windows::Forms::Label());
			this->elapsedtimeText = (gcnew System::Windows::Forms::Label());
			this->clearButton = (gcnew System::Windows::Forms::Button());
			this->airportList = (gcnew System::Windows::Forms::ListBox());
			this->airportTitle = (gcnew System::Windows::Forms::Label());
			this->invalidCodeLabel = (gcnew System::Windows::Forms::Label());
			this->timerRuntime = (gcnew System::Windows::Forms::Timer(this->components));
			this->bkgdDjikHeap = (gcnew System::ComponentModel::BackgroundWorker());
			this->bkgdFloyd = (gcnew System::ComponentModel::BackgroundWorker());
			this->bkgdCodeLoader = (gcnew System::ComponentModel::BackgroundWorker());
			this->fbd = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->chooseDataFolderToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->resetToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->dHeapTime = (gcnew System::Windows::Forms::Label());
			this->bkgdDjik = (gcnew System::ComponentModel::BackgroundWorker());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// searchButton
			// 
			this->searchButton->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->searchButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->searchButton->Enabled = false;
			this->searchButton->Location = System::Drawing::Point(385, 42);
			this->searchButton->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->searchButton->Name = L"searchButton";
			this->searchButton->Size = System::Drawing::Size(97, 56);
			this->searchButton->TabIndex = 0;
			this->searchButton->Text = L"Search";
			this->searchButton->UseVisualStyleBackColor = false;
			this->searchButton->Click += gcnew System::EventHandler(this, &MyForm::searchButton_Click);
			// 
			// start
			// 
			this->start->Location = System::Drawing::Point(24, 71);
			this->start->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->start->Name = L"start";
			this->start->Size = System::Drawing::Size(158, 27);
			this->start->TabIndex = 1;
			this->start->TextChanged += gcnew System::EventHandler(this, &MyForm::start_TextChanged);
			// 
			// end
			// 
			this->end->Location = System::Drawing::Point(194, 71);
			this->end->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->end->Name = L"end";
			this->end->Size = System::Drawing::Size(158, 27);
			this->end->TabIndex = 2;
			this->end->TextChanged += gcnew System::EventHandler(this, &MyForm::end_TextChanged);
			// 
			// startText
			// 
			this->startText->AutoSize = true;
			this->startText->Location = System::Drawing::Point(59, 42);
			this->startText->Name = L"startText";
			this->startText->Size = System::Drawing::Size(79, 20);
			this->startText->TabIndex = 3;
			this->startText->Text = L"Start point";
			// 
			// destText
			// 
			this->destText->AutoSize = true;
			this->destText->Location = System::Drawing::Point(234, 42);
			this->destText->Name = L"destText";
			this->destText->Size = System::Drawing::Size(85, 20);
			this->destText->TabIndex = 4;
			this->destText->Text = L"Destination";
			// 
			// resultList
			// 
			this->resultList->FormattingEnabled = true;
			this->resultList->HorizontalScrollbar = true;
			this->resultList->ItemHeight = 20;
			this->resultList->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"Results appear here" });
			this->resultList->Location = System::Drawing::Point(12, 204);
			this->resultList->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->resultList->Name = L"resultList";
			this->resultList->Size = System::Drawing::Size(545, 364);
			this->resultList->TabIndex = 5;
			// 
			// DjikstraText
			// 
			this->DjikstraText->AutoSize = true;
			this->DjikstraText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->DjikstraText->Location = System::Drawing::Point(564, 91);
			this->DjikstraText->Name = L"DjikstraText";
			this->DjikstraText->Size = System::Drawing::Size(174, 25);
			this->DjikstraText->TabIndex = 6;
			this->DjikstraText->Text = L"Djikstra (MinHeap)";
			// 
			// dTime
			// 
			this->dTime->AutoSize = true;
			this->dTime->Location = System::Drawing::Point(744, 61);
			this->dTime->Name = L"dTime";
			this->dTime->Size = System::Drawing::Size(63, 20);
			this->dTime->TabIndex = 9;
			this->dTime->Text = L"---------";
			// 
			// floydText
			// 
			this->floydText->AutoSize = true;
			this->floydText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->floydText->Location = System::Drawing::Point(596, 124);
			this->floydText->Name = L"floydText";
			this->floydText->Size = System::Drawing::Size(142, 25);
			this->floydText->TabIndex = 10;
			this->floydText->Text = L"Floyd Warshall";
			// 
			// fTime
			// 
			this->fTime->AutoSize = true;
			this->fTime->Location = System::Drawing::Point(744, 128);
			this->fTime->Name = L"fTime";
			this->fTime->Size = System::Drawing::Size(63, 20);
			this->fTime->TabIndex = 11;
			this->fTime->Text = L"---------";
			// 
			// resultText
			// 
			this->resultText->AutoSize = true;
			this->resultText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F));
			this->resultText->Location = System::Drawing::Point(12, 173);
			this->resultText->Name = L"resultText";
			this->resultText->Size = System::Drawing::Size(75, 22);
			this->resultText->TabIndex = 12;
			this->resultText->Text = L"Results:";
			// 
			// elapsedtimeText
			// 
			this->elapsedtimeText->AutoSize = true;
			this->elapsedtimeText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->elapsedtimeText->Location = System::Drawing::Point(644, 11);
			this->elapsedtimeText->Name = L"elapsedtimeText";
			this->elapsedtimeText->Size = System::Drawing::Size(176, 29);
			this->elapsedtimeText->TabIndex = 13;
			this->elapsedtimeText->Text = L"Elapsed Time";
			// 
			// clearButton
			// 
			this->clearButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->clearButton->Enabled = false;
			this->clearButton->Location = System::Drawing::Point(385, 106);
			this->clearButton->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->clearButton->Name = L"clearButton";
			this->clearButton->Size = System::Drawing::Size(97, 56);
			this->clearButton->TabIndex = 14;
			this->clearButton->Text = L"Clear";
			this->clearButton->UseVisualStyleBackColor = true;
			this->clearButton->Click += gcnew System::EventHandler(this, &MyForm::clearButton_Click);
			// 
			// airportList
			// 
			this->airportList->FormattingEnabled = true;
			this->airportList->ItemHeight = 20;
			this->airportList->Location = System::Drawing::Point(572, 204);
			this->airportList->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->airportList->Name = L"airportList";
			this->airportList->Size = System::Drawing::Size(317, 364);
			this->airportList->TabIndex = 15;
			// 
			// airportTitle
			// 
			this->airportTitle->AutoSize = true;
			this->airportTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F));
			this->airportTitle->Location = System::Drawing::Point(568, 173);
			this->airportTitle->Name = L"airportTitle";
			this->airportTitle->Size = System::Drawing::Size(125, 22);
			this->airportTitle->TabIndex = 16;
			this->airportTitle->Text = L"Airport Codes:";
			// 
			// invalidCodeLabel
			// 
			this->invalidCodeLabel->AutoSize = true;
			this->invalidCodeLabel->ForeColor = System::Drawing::Color::Red;
			this->invalidCodeLabel->Location = System::Drawing::Point(89, 106);
			this->invalidCodeLabel->Name = L"invalidCodeLabel";
			this->invalidCodeLabel->Size = System::Drawing::Size(217, 20);
			this->invalidCodeLabel->TabIndex = 17;
			this->invalidCodeLabel->Text = L"Please input valid airport codes";
			this->invalidCodeLabel->Visible = false;
			// 
			// timerRuntime
			// 
			this->timerRuntime->Tick += gcnew System::EventHandler(this, &MyForm::timer_Tick);
			// 
			// bkgdDjikHeap
			// 
			this->bkgdDjikHeap->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::bkgdDjikHeap_DoWork);
			// 
			// bkgdFloyd
			// 
			this->bkgdFloyd->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::bkgdFloyd_DoWork);
			// 
			// bkgdCodeLoader
			// 
			this->bkgdCodeLoader->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::bkgdCodeLoader_DoWork);
			this->bkgdCodeLoader->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::bkgdCodeLoader_RunWorkerCompleted);
			// 
			// fbd
			// 
			this->fbd->RootFolder = System::Environment::SpecialFolder::UserProfile;
			this->fbd->ShowNewFolderButton = false;
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::Control;
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->optionsToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(902, 28);
			this->menuStrip1->TabIndex = 18;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->chooseDataFolderToolStripMenuItem1,
					this->resetToolStripMenuItem
			});
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(75, 24);
			this->optionsToolStripMenuItem->Text = L"Options";
			// 
			// chooseDataFolderToolStripMenuItem1
			// 
			this->chooseDataFolderToolStripMenuItem1->Name = L"chooseDataFolderToolStripMenuItem1";
			this->chooseDataFolderToolStripMenuItem1->Size = System::Drawing::Size(223, 26);
			this->chooseDataFolderToolStripMenuItem1->Text = L"Choose Data Folder";
			this->chooseDataFolderToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::chooseDataFolderToolStripMenuItem1_Click);
			// 
			// resetToolStripMenuItem
			// 
			this->resetToolStripMenuItem->Name = L"resetToolStripMenuItem";
			this->resetToolStripMenuItem->Size = System::Drawing::Size(223, 26);
			this->resetToolStripMenuItem->Text = L"Reset";
			this->resetToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::resetToolStripMenuItem_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->label1->Location = System::Drawing::Point(563, 56);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(175, 25);
			this->label1->TabIndex = 19;
			this->label1->Text = L"Djikstra (Standard)";
			// 
			// dHeapTime
			// 
			this->dHeapTime->AutoSize = true;
			this->dHeapTime->Location = System::Drawing::Point(744, 95);
			this->dHeapTime->Name = L"dHeapTime";
			this->dHeapTime->Size = System::Drawing::Size(63, 20);
			this->dHeapTime->TabIndex = 20;
			this->dHeapTime->Text = L"---------";
			// 
			// bkgdDjik
			// 
			this->bkgdDjik->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::bkgdDjik_DoWork);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(902, 591);
			this->Controls->Add(this->dHeapTime);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->invalidCodeLabel);
			this->Controls->Add(this->airportTitle);
			this->Controls->Add(this->airportList);
			this->Controls->Add(this->clearButton);
			this->Controls->Add(this->elapsedtimeText);
			this->Controls->Add(this->resultText);
			this->Controls->Add(this->fTime);
			this->Controls->Add(this->floydText);
			this->Controls->Add(this->dTime);
			this->Controls->Add(this->DjikstraText);
			this->Controls->Add(this->resultList);
			this->Controls->Add(this->destText);
			this->Controls->Add(this->startText);
			this->Controls->Add(this->end);
			this->Controls->Add(this->start);
			this->Controls->Add(this->searchButton);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->Name = L"MyForm";
			this->Text = L"Optimal Flight Search";
			this->Load += gcnew System::EventHandler(this, &MyForm::formLoad);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: void timerStart() {
		startTime = DateTime::Now;
		dRunning = true;
		dHeapRunning = true;
		fRunning = true;
		timerRuntime->Start();
	}
	private: void displayDjikstra() {
		rwl->AcquireWriterLock(1);
		resultList->Items->Add(L"Djikstra's Algorithm Path (Standard):");
		resultList->Items->Add(d_path);
		resultList->Items->Add("");
		rwl->ReleaseWriterLock();
	}
	private: void displayDjikstraMinHeap() {
		rwl->AcquireWriterLock(1);
		resultList->Items->Add(L"Djikstra's Algorithm Path (MinHeap):");
		resultList->Items->Add(dHeap_path);
		resultList->Items->Add("");
		rwl->ReleaseWriterLock();
	}
	private: void displayFloyd() {
		rwl->AcquireWriterLock(1);
		resultList->Items->Add(L"Floyd Warshall Algorithm Path:");
		resultList->Items->Add(f_path);
		resultList->Items->Add("");
		rwl->ReleaseWriterLock();
	}
	private: void displayDjikstraTime() {
		dTime->Text = d_time;
	}
	private: void displayDjikstraMinHeapTime() {
		dHeapTime->Text = dHeap_time;
	}
	private: void displayFloydTime() {
		fTime->Text = f_time;
	}
	private: void loadList() {
		vector<std::string> names = graph->getAirportNames();
		airportList->Items->Clear();
		for (std::string s : names) {
			String^ str = gcnew String(s.c_str());
			strs->push_back(str);
			airportList->Items->Add(str);
		}
		if (names.size() == 0) {
			airportList->Items->Add("Files not found at " + folderLocation);
		}
	}
	private: System::Void formLoad(System::Object^ sender, System::EventArgs^ e) {
		airportList->Items->Add("loading...");
		bkgdCodeLoader->RunWorkerAsync();
	}
	private: System::Void end_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		if (this->invalidCodeLabel->Visible) {
			this->invalidCodeLabel->Visible = false;
		}
	}
	private: System::Void start_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		if (this->invalidCodeLabel->Visible) {
			this->invalidCodeLabel->Visible = false;
		}
	}

	private: System::Void searchButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (start->Text->Length != 3 || end->Text->Length != 3) {
			this->invalidCodeLabel->Visible = true;
			return;
		}
		//Notify user that it is loading.
		searchButton->Enabled = false;
		clearButton->Enabled = false;
		resultList->Items->Clear();
		cleanPaths();
		resultList->Items->Add(L"Calculating shortest path from " + start->Text + L" to " + end->Text + L", please wait");
		
		
		//***
		//Start the BackgroundWorkers
		timerStart();
		bkgdDjikHeap->RunWorkerAsync();
		bkgdFloyd->RunWorkerAsync();
		bkgdDjik->RunWorkerAsync();
		/***/
	}
	private: System::Void clearButton_Click(System::Object^ sender, System::EventArgs^ e) {
		dHeapTime->Text = L"---------";
		fTime->Text = L"---------";
		dTime->Text = L"---------";
		resultList->Items->Clear();
		cleanPaths();
		resultList->Items->Add(L"Results appear here");
		start->Clear();
		end->Clear();
	}
private: System::Void timer_Tick(System::Object^ sender, System::EventArgs^ e) {
	TimeSpan cur = DateTime::Now.Subtract(startTime);
	String^ strTime;
	if (cur.TotalSeconds > 60) {
		 strTime = System::Convert::ToString(Math::Floor(cur.TotalMinutes)) + " m " + System::Convert::ToString(Math::Round(cur.TotalSeconds - Math::Floor(cur.TotalMinutes) * 60, 0)) + "s";
	} else {
		strTime = System::Convert::ToString(Math::Round(cur.TotalSeconds, 2)) + " s";
	}
	bool updated = false;
	if (dHeapRunning) {
		dHeapTime->Text = strTime;
		updated = true;
	}
	if (fRunning) {
		fTime->Text = strTime;
		updated = true;
	}
	if (dRunning) {
		dTime->Text = strTime;
		updated = true;
	}
	if (!updated) {
		timerRuntime->Stop();
		resultList->Items->RemoveAt(0);
		searchButton->Enabled = true;
		clearButton->Enabled = true;
	}
}
private: System::Void bkgdFloyd_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
	//Convert to std strings
	msclr::interop::marshal_context context;
	std::string origin = context.marshal_as<std::string>(start->Text);
	std::string dest = context.marshal_as<std::string>(end->Text);

	//Time how long it takes to get the path.
	DateTime startTime = DateTime::Now;
	FlightPath result = graph->floydPath(origin, dest);
	TimeSpan cur = DateTime::Now.Subtract(startTime);
	String^ strTime;

	// tell the timer that Floyd is done running
	fRunning = false;

	//parse and generate time to be output
	if (cur.TotalMilliseconds > 1000) {
		strTime = System::Convert::ToString(Math::Round(cur.TotalSeconds, 3)) + " s";
	}
	else {
		strTime = System::Convert::ToString(Math::Round(cur.TotalMilliseconds, 3)) + " ms";
	}

	Sleep(100);
	f_time = strTime;
	
	//push results into the list
	fTime->Invoke(gcnew Action(this, &MyForm::displayFloydTime));

	//Add results to list
	f_path = gcnew String(result.toString().c_str());

	resultList->Invoke(gcnew Action(this, &MyForm::displayFloyd));
	
}
private: System::Void bkgdDjikHeap_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {

	//Convert to std strings
	msclr::interop::marshal_context context;
	std::string origin = context.marshal_as<std::string>(start->Text);
	std::string dest = context.marshal_as<std::string>(end->Text);

	//Time how long it takes to get the path.
	DateTime startTime = DateTime::Now;
	FlightPath result = graph->djikstraMinHeapPath(origin, dest);
	TimeSpan cur = DateTime::Now.Subtract(startTime);
	String^ strTime;

	// tell the timer that Djikstra MinHeap is done running
	dHeapRunning = false;

	//parse and generate time to be output
	if (cur.TotalMilliseconds > 1000) {
		strTime = System::Convert::ToString(Math::Round(cur.TotalSeconds, 3)) + " s";
	}
	else {
		strTime = System::Convert::ToString(Math::Round(cur.TotalMilliseconds, 3)) + " ms";
	}

	Sleep(100);
	dHeap_time = strTime;

	//push results into the list
	dTime->Invoke(gcnew Action(this, &MyForm::displayDjikstraMinHeapTime));

	dHeap_path = gcnew String(result.toString().c_str());
	
	resultList->Invoke(gcnew Action(this, &MyForm::displayDjikstraMinHeap));

}
private: System::Void bkgdDjik_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
	//Convert to std strings
	msclr::interop::marshal_context context;
	std::string origin = context.marshal_as<std::string>(start->Text);
	std::string dest = context.marshal_as<std::string>(end->Text);

	//Time how long it takes to get the path.
	DateTime startTime = DateTime::Now;
	FlightPath result = graph->djikstraVectorPath(origin, dest);
	TimeSpan cur = DateTime::Now.Subtract(startTime);
	String^ strTime;

	// tell the timer that Djikstra Standard is done running
	dRunning = false;

	//parse and generate time to be output
	if (cur.TotalMilliseconds > 1000) {
		strTime = System::Convert::ToString(Math::Round(cur.TotalSeconds, 3)) + " s";
	}
	else {
		strTime = System::Convert::ToString(Math::Round(cur.TotalMilliseconds, 3)) + " ms";
	}

	Sleep(100);
	d_time = strTime;
	dTime->Invoke(gcnew Action(this, &MyForm::displayDjikstraTime));
	//push results into the list

	d_path = gcnew String(result.toString().c_str());

	resultList->Invoke(gcnew Action(this, &MyForm::displayDjikstra));
}

private: System::Void bkgdCodeLoader_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
	msclr::interop::marshal_context context;
	std::string folder = context.marshal_as<std::string>(folderLocation);
	graph->parseData(folder + "/airports.csv", folder + "/transport_data_2015_january.csv");
	
	if (graph->size() == 0) {
		graph->parseData("data/airports.csv", "data/transport_data_2015_january.csv");
	}
	airportList->Invoke(gcnew Action(this, &MyForm::loadList));
}


//Signal to find folder to update data
private: System::Void chooseDataFolderToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
	fbd->ShowDialog();
	folderLocation = fbd->SelectedPath;
	while (!searchButton->Enabled) {
		Thread::Sleep(500);
	}
	airportList->Items->Clear();
	airportList->Items->Add("loading...");
	searchButton->Enabled = false;
	clearButton->Enabled = false;
	System::Drawing::SystemColors::ControlDark;
	graph->clear();
	bkgdCodeLoader->RunWorkerAsync();
}
//Signal to reset Floyd Warshall
private: System::Void resetToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	graph->reset();
}
private: System::Void bkgdCodeLoader_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e) {
	searchButton->Enabled = true;
	clearButton->Enabled = true;
}

};
}
