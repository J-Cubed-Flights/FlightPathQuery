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
		String^ d_path;
		String^ d_time;
		String^ f_path;
		String^ f_time;
		String^ folderLocation;
		DateTime dStartTime;
		DateTime fwStartTime;
		ReaderWriterLock^ rwl;
	private: System::ComponentModel::BackgroundWorker^ bkgdWorkerFloyd;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ chooseDataFolderToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ resetToolStripMenuItem;


	private: System::Windows::Forms::ToolStripTextBox^ toolStripTextBox1;

	private: System::Windows::Forms::FolderBrowserDialog^ fbd;
	private: System::ComponentModel::BackgroundWorker^ bkgdCodeLoader;
	private: System::ComponentModel::BackgroundWorker^ bkgdWorkerDjik;


	public:
		MyForm(void)
		{
			folderLocation = "../../data";
			strs = gcnew cliext::vector<String^>();
			graph = new DirectedGraph();
			rwl = gcnew ReaderWriterLock();
			d_path = nullptr;
			f_path = nullptr;
			d_time = nullptr;
			f_time = nullptr;			
			InitializeComponent();
		}
	private:
		void cleanPaths() {
			if (d_path) {
				delete d_path;
				d_path = nullptr;
			}
			if (d_time) {
				delete d_time;
				d_time = nullptr;
			}
			if (f_path) {
				delete f_path;
				f_path = nullptr;
			}
			if (f_time) {
				delete f_time;
				f_time = nullptr;
			}
			if (rwl) {
				delete rwl;
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
	private: System::Windows::Forms::Timer^ timerDjikstra;
	private: System::Windows::Forms::Timer^ timerFloyd;

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
			this->timerDjikstra = (gcnew System::Windows::Forms::Timer(this->components));
			this->timerFloyd = (gcnew System::Windows::Forms::Timer(this->components));
			this->bkgdWorkerDjik = (gcnew System::ComponentModel::BackgroundWorker());
			this->bkgdWorkerFloyd = (gcnew System::ComponentModel::BackgroundWorker());
			this->bkgdCodeLoader = (gcnew System::ComponentModel::BackgroundWorker());
			this->fbd = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->chooseDataFolderToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->resetToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// searchButton
			// 
			this->searchButton->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->searchButton->Cursor = System::Windows::Forms::Cursors::Hand;
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
			this->resultList->Location = System::Drawing::Point(13, 181);
			this->resultList->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->resultList->Name = L"resultList";
			this->resultList->Size = System::Drawing::Size(545, 364);
			this->resultList->TabIndex = 5;
			// 
			// DjikstraText
			// 
			this->DjikstraText->AutoSize = true;
			this->DjikstraText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->DjikstraText->Location = System::Drawing::Point(655, 71);
			this->DjikstraText->Name = L"DjikstraText";
			this->DjikstraText->Size = System::Drawing::Size(76, 25);
			this->DjikstraText->TabIndex = 6;
			this->DjikstraText->Text = L"Djikstra";
			// 
			// dTime
			// 
			this->dTime->AutoSize = true;
			this->dTime->Location = System::Drawing::Point(777, 80);
			this->dTime->Name = L"dTime";
			this->dTime->Size = System::Drawing::Size(63, 20);
			this->dTime->TabIndex = 9;
			this->dTime->Text = L"---------";
			// 
			// floydText
			// 
			this->floydText->AutoSize = true;
			this->floydText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->floydText->Location = System::Drawing::Point(599, 115);
			this->floydText->Name = L"floydText";
			this->floydText->Size = System::Drawing::Size(142, 25);
			this->floydText->TabIndex = 10;
			this->floydText->Text = L"Floyd Warshall";
			// 
			// fTime
			// 
			this->fTime->AutoSize = true;
			this->fTime->Location = System::Drawing::Point(777, 124);
			this->fTime->Name = L"fTime";
			this->fTime->Size = System::Drawing::Size(63, 20);
			this->fTime->TabIndex = 11;
			this->fTime->Text = L"---------";
			// 
			// resultText
			// 
			this->resultText->AutoSize = true;
			this->resultText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F));
			this->resultText->Location = System::Drawing::Point(12, 150);
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
			this->airportList->Location = System::Drawing::Point(573, 181);
			this->airportList->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->airportList->Name = L"airportList";
			this->airportList->Size = System::Drawing::Size(317, 364);
			this->airportList->TabIndex = 15;
			// 
			// airportTitle
			// 
			this->airportTitle->AutoSize = true;
			this->airportTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F));
			this->airportTitle->Location = System::Drawing::Point(569, 150);
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
			// timerDjikstra
			// 
			this->timerDjikstra->Tick += gcnew System::EventHandler(this, &MyForm::timerDjikstra_Tick);
			// 
			// timerFloyd
			// 
			this->timerFloyd->Tick += gcnew System::EventHandler(this, &MyForm::timerFloyd_Tick);
			// 
			// bkgdWorkerDjik
			// 
			this->bkgdWorkerDjik->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::bkgdWorkerDjik_DoWork);
			this->bkgdWorkerDjik->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::bkgdWorkerDjik_RunWorkerCompleted);
			// 
			// bkgdWorkerFloyd
			// 
			this->bkgdWorkerFloyd->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::bkgdWorkerFloyd_DoWork);
			this->bkgdWorkerFloyd->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::bkgdWorkerFloyd_RunWorkerCompleted);
			// 
			// bkgdCodeLoader
			// 
			this->bkgdCodeLoader->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::bkgdCodeLoader_DoWork);
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
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(902, 565);
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
	private: void dTimerStart() {
		dStartTime = DateTime::Now;
		timerDjikstra->Start();
	}
	private: void fwTimerStart() {
		fwStartTime = DateTime::Now;
		timerFloyd->Start();
	}
	private: void displayDjikstra() {
		rwl->AcquireWriterLock(1);
		resultList->Items->Add(L"Djikstra's Algorithm Path:");
		resultList->Items->Add(d_path);
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
		resultList->Items->Clear();
		cleanPaths();
		resultList->Items->Add(L"Calculating shortest path from " + start->Text + L" to " + end->Text + L", please wait");
		this->searchButton->BackColor = System::Drawing::SystemColors::ControlDark;
		this->clearButton->BackColor = System::Drawing::SystemColors::ControlDark;
		//***
		//Start the BackgroundWorkers
		dTimerStart();
		fwTimerStart();
		bkgdWorkerDjik->RunWorkerAsync();
		bkgdWorkerFloyd->RunWorkerAsync();
		/***/

		/*** Single Thread
		computeDjikstra();
		computeFloydWarshall();
		/***/

		//remove the first row, and revert button color.
	}
	private: System::Void clearButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (timerDjikstra->Enabled || timerFloyd->Enabled) {
			return;
		}
		dTime->Text = L"---------";
		fTime->Text = L"---------";
		resultList->Items->Clear();
		cleanPaths();
		resultList->Items->Add(L"Results appear here");
		start->Clear();
		end->Clear();
	}
private: System::Void timerDjikstra_Tick(System::Object^ sender, System::EventArgs^ e) {
	TimeSpan cur = DateTime::Now.Subtract(dStartTime);
	if (cur.TotalSeconds > 60) {
		dTime->Text = System::Convert::ToString(Math::Floor(cur.TotalMinutes)) + "m " + System::Convert::ToString(Math::Round(cur.TotalSeconds - Math::Floor(cur.TotalMinutes) * 60, 0)) + "s";
	} else {
		dTime->Text = System::Convert::ToString(Math::Round(cur.TotalSeconds, 2)) + "s";
	}
}
private: System::Void timerFloyd_Tick(System::Object^ sender, System::EventArgs^ e) {
	TimeSpan cur = DateTime::Now.Subtract(fwStartTime);
	if (cur.TotalSeconds > 60) {
		fTime->Text = System::Convert::ToString(Math::Floor(cur.TotalMinutes)) + "m " + System::Convert::ToString(Math::Round(cur.TotalSeconds - Math::Floor(cur.TotalMinutes) * 60, 0)) + "s";
	} else {
		fTime->Text = System::Convert::ToString(Math::Round(cur.TotalSeconds, 2)) + "s";
	}
}
private: System::Void bkgdWorkerFloyd_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
	//Convert to std strings
	msclr::interop::marshal_context context;
	std::string origin = context.marshal_as<std::string>(start->Text);
	std::string dest = context.marshal_as<std::string>(end->Text);

	std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
	std::chrono::duration<double> elapsed_seconds;
	startTime = std::chrono::system_clock::now();
	FlightPath result = graph->floydPath(origin, dest);
	endTime = std::chrono::system_clock::now();
	elapsed_seconds = endTime - startTime;

	timerFloyd->Stop();
	f_time = elapsed_seconds.count().ToString() + L"s";
	if (fTime->InvokeRequired) {
		fTime->Invoke(gcnew Action(this, &MyForm::displayFloydTime));
	}
	else {
		displayFloydTime();
	}

	//Add results to list
	f_path = gcnew String(result.toString().c_str());

	if (resultList->InvokeRequired) {
		resultList->Invoke(gcnew Action(this, &MyForm::displayFloyd));
	}
	else {
		displayFloyd();
	}
	
}
private: System::Void bkgdWorkerDjik_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {

	//Convert to std strings
	msclr::interop::marshal_context context;
	std::string origin = context.marshal_as<std::string>(start->Text);
	std::string dest = context.marshal_as<std::string>(end->Text);

	std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
	std::chrono::duration<double> elapsed_seconds;
	startTime = std::chrono::system_clock::now();
	//TODO insert function here when finished
	FlightPath result;// = graph->djikstraPath(origin, dest);
	endTime = std::chrono::system_clock::now();
	elapsed_seconds = endTime - startTime;
	timerDjikstra->Stop();
	d_time = elapsed_seconds.count().ToString() + L"s";
	if (dTime->InvokeRequired) {
		dTime->Invoke(gcnew Action(this, &MyForm::displayDjikstraTime));
	}
	else {
		displayDjikstraTime();
	}
	//push results into the list

	d_path = gcnew String(result.toString().c_str());
	
	if (resultList->InvokeRequired) {
		resultList->Invoke(gcnew Action(this, &MyForm::displayDjikstra));
	}
	else {
		displayDjikstra();
	}

}
private: System::Void bkgdWorkerFloyd_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e) {
	rwl->AcquireReaderLock(1);
	if (resultList->Items->Count >= 7) {
		this->searchButton->BackColor = System::Drawing::SystemColors::ControlLightLight;
		this->clearButton->BackColor = System::Drawing::SystemColors::ControlLightLight;
		resultList->Items->RemoveAt(0);
	}
	rwl->ReleaseReaderLock();
}
private: System::Void bkgdWorkerDjik_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e) {
	rwl->AcquireReaderLock(1);
	if (resultList->Items->Count >= 7) {
		this->searchButton->BackColor = System::Drawing::SystemColors::ControlLightLight;
		this->clearButton->BackColor = System::Drawing::SystemColors::ControlLightLight;
		resultList->Items->RemoveAt(0);
	}
	rwl->ReleaseReaderLock();
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
	while (bkgdCodeLoader->IsBusy) {
		Thread::Sleep(500);
	}
	airportList->Items->Clear();
	airportList->Items->Add("loading...");
	graph->clear();
	bkgdCodeLoader->RunWorkerAsync();
}
//Signal to reset Floyd Warshall
private: System::Void resetToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	graph->reset();
}
};
}
