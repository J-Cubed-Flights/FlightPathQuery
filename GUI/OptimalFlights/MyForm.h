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
		cliext::vector<String^>^ path_strs;
		DateTime dStartTime;
		DateTime fwStartTime;

		void cleanPaths() {
			if (path_strs->size() != 0) {
				for (int i = 0; i < path_strs->size(); i++) {
					delete path_strs[i];
				}
				path_strs->clear();
			}
		}
	public:
		MyForm(void)
		{
			strs = gcnew cliext::vector<String^>();
			path_strs = gcnew cliext::vector<String^>();
			graph = new DirectedGraph();
			parseData(*graph, "../../data/airports.csv", "../../data/transport_data_2015_january.csv");
			if (graph->size() == 0) {
				parseData(*graph, "data/airports.csv", "data/transport_data_2015_january.csv");
			}
			InitializeComponent();
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
			if (path_strs) {
				cleanPaths();
				delete path_strs;
			}
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



	protected:


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
			this->SuspendLayout();
			// 
			// searchButton
			// 
			this->searchButton->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->searchButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->searchButton->Location = System::Drawing::Point(385, 34);
			this->searchButton->Name = L"searchButton";
			this->searchButton->Size = System::Drawing::Size(97, 45);
			this->searchButton->TabIndex = 0;
			this->searchButton->Text = L"Search";
			this->searchButton->UseVisualStyleBackColor = false;
			this->searchButton->Click += gcnew System::EventHandler(this, &MyForm::searchButton_Click);
			// 
			// start
			// 
			this->start->Location = System::Drawing::Point(24, 57);
			this->start->Name = L"start";
			this->start->Size = System::Drawing::Size(158, 22);
			this->start->TabIndex = 1;
			this->start->TextChanged += gcnew System::EventHandler(this, &MyForm::start_TextChanged);
			// 
			// end
			// 
			this->end->Location = System::Drawing::Point(194, 57);
			this->end->Name = L"end";
			this->end->Size = System::Drawing::Size(158, 22);
			this->end->TabIndex = 2;
			this->end->TextChanged += gcnew System::EventHandler(this, &MyForm::end_TextChanged);
			// 
			// startText
			// 
			this->startText->AutoSize = true;
			this->startText->Location = System::Drawing::Point(59, 34);
			this->startText->Name = L"startText";
			this->startText->Size = System::Drawing::Size(66, 16);
			this->startText->TabIndex = 3;
			this->startText->Text = L"Start point";
			// 
			// destText
			// 
			this->destText->AutoSize = true;
			this->destText->Location = System::Drawing::Point(234, 34);
			this->destText->Name = L"destText";
			this->destText->Size = System::Drawing::Size(74, 16);
			this->destText->TabIndex = 4;
			this->destText->Text = L"Destination";
			// 
			// resultList
			// 
			this->resultList->FormattingEnabled = true;
			this->resultList->HorizontalScrollbar = true;
			this->resultList->ItemHeight = 16;
			this->resultList->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"Results appear here" });
			this->resultList->Location = System::Drawing::Point(13, 145);
			this->resultList->Name = L"resultList";
			this->resultList->Size = System::Drawing::Size(545, 292);
			this->resultList->TabIndex = 5;
			// 
			// DjikstraText
			// 
			this->DjikstraText->AutoSize = true;
			this->DjikstraText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->DjikstraText->Location = System::Drawing::Point(655, 57);
			this->DjikstraText->Name = L"DjikstraText";
			this->DjikstraText->Size = System::Drawing::Size(76, 25);
			this->DjikstraText->TabIndex = 6;
			this->DjikstraText->Text = L"Djikstra";
			// 
			// dTime
			// 
			this->dTime->AutoSize = true;
			this->dTime->Location = System::Drawing::Point(777, 64);
			this->dTime->Name = L"dTime";
			this->dTime->Size = System::Drawing::Size(43, 16);
			this->dTime->TabIndex = 9;
			this->dTime->Text = L"---------";
			// 
			// floydText
			// 
			this->floydText->AutoSize = true;
			this->floydText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->floydText->Location = System::Drawing::Point(599, 92);
			this->floydText->Name = L"floydText";
			this->floydText->Size = System::Drawing::Size(142, 25);
			this->floydText->TabIndex = 10;
			this->floydText->Text = L"Floyd Warshall";
			// 
			// fTime
			// 
			this->fTime->AutoSize = true;
			this->fTime->Location = System::Drawing::Point(777, 99);
			this->fTime->Name = L"fTime";
			this->fTime->Size = System::Drawing::Size(43, 16);
			this->fTime->TabIndex = 11;
			this->fTime->Text = L"---------";
			// 
			// resultText
			// 
			this->resultText->AutoSize = true;
			this->resultText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F));
			this->resultText->Location = System::Drawing::Point(12, 120);
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
			this->elapsedtimeText->Location = System::Drawing::Point(644, 9);
			this->elapsedtimeText->Name = L"elapsedtimeText";
			this->elapsedtimeText->Size = System::Drawing::Size(176, 29);
			this->elapsedtimeText->TabIndex = 13;
			this->elapsedtimeText->Text = L"Elapsed Time";
			// 
			// clearButton
			// 
			this->clearButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->clearButton->Location = System::Drawing::Point(385, 85);
			this->clearButton->Name = L"clearButton";
			this->clearButton->Size = System::Drawing::Size(97, 45);
			this->clearButton->TabIndex = 14;
			this->clearButton->Text = L"Clear";
			this->clearButton->UseVisualStyleBackColor = true;
			this->clearButton->Click += gcnew System::EventHandler(this, &MyForm::clearButton_Click);
			// 
			// airportList
			// 
			this->airportList->FormattingEnabled = true;
			this->airportList->ItemHeight = 16;
			this->airportList->Location = System::Drawing::Point(573, 145);
			this->airportList->Name = L"airportList";
			this->airportList->Size = System::Drawing::Size(317, 292);
			this->airportList->TabIndex = 15;
			// 
			// airportTitle
			// 
			this->airportTitle->AutoSize = true;
			this->airportTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F));
			this->airportTitle->Location = System::Drawing::Point(569, 120);
			this->airportTitle->Name = L"airportTitle";
			this->airportTitle->Size = System::Drawing::Size(125, 22);
			this->airportTitle->TabIndex = 16;
			this->airportTitle->Text = L"Airport Codes:";
			// 
			// invalidCodeLabel
			// 
			this->invalidCodeLabel->AutoSize = true;
			this->invalidCodeLabel->ForeColor = System::Drawing::Color::Red;
			this->invalidCodeLabel->Location = System::Drawing::Point(89, 85);
			this->invalidCodeLabel->Name = L"invalidCodeLabel";
			this->invalidCodeLabel->Size = System::Drawing::Size(195, 16);
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
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(902, 452);
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
			this->Name = L"MyForm";
			this->Text = L"Optimal Flight Search";
			this->Load += gcnew System::EventHandler(this, &MyForm::formLoad);
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
	public: void computeDjikstra(System::Object^ state) {
		//Convert to std strings
		msclr::interop::marshal_context context;
		std::string origin = context.marshal_as<std::string>(start->Text);
		std::string dest = context.marshal_as<std::string>(end->Text);

		dTimerStart();
		std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
		std::chrono::duration<double> elapsed_seconds;
		startTime = std::chrono::system_clock::now();
		//TODO insert function here when finished
		FlightPath result;// = graph->djikstraPath(origin, dest);
		endTime = std::chrono::system_clock::now();
		elapsed_seconds = endTime - startTime;

		//push results into the list

		String^ path = gcnew String(result.toString().c_str());
		path_strs->push_back(path);
		//fix System.InvalidOperationException: 'Cross-thread operation not valid: Control 'resultList' accessed from a thread other than the thread it was created on
		resultList->Items->Add(L"Djikstra's Algorithm Path:");
		resultList->Items->Add(path);

		timerDjikstra->Stop();
		dTime->Text = elapsed_seconds.count().ToString() + L"s";
	}
	public: void computeFloydWarshall(System::Object^ state) {
		//Convert to std strings
		msclr::interop::marshal_context context;
		std::string origin = context.marshal_as<std::string>(start->Text);
		std::string dest = context.marshal_as<std::string>(end->Text);


		fwTimerStart();
		std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
		std::chrono::duration<double> elapsed_seconds;
		startTime = std::chrono::system_clock::now();
		FlightPath result = graph->floydPath(origin, dest);
		endTime = std::chrono::system_clock::now();
		elapsed_seconds = endTime - startTime;

		//push results into the list

		String^ path = gcnew String(result.toString().c_str());
		path_strs->push_back(path);

		resultList->Items->Add(L"Floyd Warshall Algorithm Path:");
		resultList->Items->Add(path);

		timerFloyd->Stop();
		fTime->Text = elapsed_seconds.count().ToString() + L"s";
	}
	private: void computeFloydWarshall() {
		Object^ temp = gcnew Object();
		computeFloydWarshall(temp);
		delete temp;
	}
	private: void computeDjikstra() {
		Object^ temp = gcnew Object();
		computeDjikstra(temp);
		delete temp;
	}
	private: System::Void formLoad(System::Object^ sender, System::EventArgs^ e) {
		vector<std::string> names = graph->getAirportNames();
		for (std::string s : names) {
			String^ str = gcnew String(s.c_str());
			strs->push_back(str);
			airportList->Items->Add(str);
		}
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
		//***
		//Make Djikstra thread 
		System::Threading::ParameterizedThreadStart^ dStarter = gcnew System::Threading::ParameterizedThreadStart(this, &MyForm::computeDjikstra);
		System::Threading::Thread^ dThread = gcnew System::Threading::Thread(dStarter);

		//Make a Floyd Warshall thread
		System::Threading::ParameterizedThreadStart^ fwStarter = gcnew System::Threading::ParameterizedThreadStart(this, &MyForm::computeFloydWarshall);
		System::Threading::Thread^ fwThread = gcnew System::Threading::Thread(fwStarter);

		//Start the threads
		dThread->Start(this);
		fwThread->Start(this);
		
		//join threads
		fwThread->Join();
		dThread->Join();
		delete fwStarter;
		delete dStarter;
		delete fwThread;
		delete dThread;
		/***/

		/*** Single Thread
		computeDjikstra();
		computeFloydWarshall();
		/***/

		//remove the first row, and revert button color.
		this->searchButton->BackColor = System::Drawing::SystemColors::ControlLightLight;
		resultList->Items->RemoveAt(0);
	}
	private: System::Void clearButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (timerDjikstra->Enabled) {
			timerDjikstra->Stop();
		}
		if (timerFloyd->Enabled) {
			timerFloyd->Stop();
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
	dTime->Text = System::Convert::ToString(cur.TotalSeconds) + "s";
}
private: System::Void timerFloyd_Tick(System::Object^ sender, System::EventArgs^ e) {
	TimeSpan cur = DateTime::Now.Subtract(fwStartTime);
	fTime->Text = System::Convert::ToString(cur.TotalSeconds) + "s";
}
};
}
