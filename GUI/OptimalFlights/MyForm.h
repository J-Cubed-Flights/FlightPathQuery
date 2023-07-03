#pragma once
#include <string>

namespace OptimalFlights {

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
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
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
	//TODO: Add DirectedGraph as a member variable here.
	private: System::Windows::Forms::Button^ searchButton;
	private: System::Windows::Forms::TextBox^ start;
	private: System::Windows::Forms::TextBox^ end;

	private: System::Windows::Forms::Label^ startText;
	private: System::Windows::Forms::Label^ destText;
	private: System::Windows::Forms::ListBox^ resultList;





	private: System::Windows::Forms::Label^ DjikstraText;
	private: System::Windows::Forms::Label^ dTime;



	private: System::Windows::Forms::Label^ bfsText;
	private: System::Windows::Forms::Label^ bTime;
	private: System::Windows::Forms::Label^ resultText;

	private: System::Windows::Forms::Label^ elapsedtimeText;
	private: System::Windows::Forms::Button^ clearButton;
	private: System::Windows::Forms::ListBox^ airportList;

	private: System::Windows::Forms::Label^ airportTitle;


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
			this->searchButton = (gcnew System::Windows::Forms::Button());
			this->start = (gcnew System::Windows::Forms::TextBox());
			this->end = (gcnew System::Windows::Forms::TextBox());
			this->startText = (gcnew System::Windows::Forms::Label());
			this->destText = (gcnew System::Windows::Forms::Label());
			this->resultList = (gcnew System::Windows::Forms::ListBox());
			this->DjikstraText = (gcnew System::Windows::Forms::Label());
			this->dTime = (gcnew System::Windows::Forms::Label());
			this->bfsText = (gcnew System::Windows::Forms::Label());
			this->bTime = (gcnew System::Windows::Forms::Label());
			this->resultText = (gcnew System::Windows::Forms::Label());
			this->elapsedtimeText = (gcnew System::Windows::Forms::Label());
			this->clearButton = (gcnew System::Windows::Forms::Button());
			this->airportList = (gcnew System::Windows::Forms::ListBox());
			this->airportTitle = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// searchButton
			// 
			this->searchButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->searchButton->Location = System::Drawing::Point(385, 34);
			this->searchButton->Name = L"searchButton";
			this->searchButton->Size = System::Drawing::Size(97, 45);
			this->searchButton->TabIndex = 0;
			this->searchButton->Text = L"Search";
			this->searchButton->UseVisualStyleBackColor = true;
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
			this->DjikstraText->Location = System::Drawing::Point(544, 57);
			this->DjikstraText->Name = L"DjikstraText";
			this->DjikstraText->Size = System::Drawing::Size(76, 25);
			this->DjikstraText->TabIndex = 6;
			this->DjikstraText->Text = L"Djikstra";
			// 
			// dTime
			// 
			this->dTime->AutoSize = true;
			this->dTime->Location = System::Drawing::Point(638, 64);
			this->dTime->Name = L"dTime";
			this->dTime->Size = System::Drawing::Size(43, 16);
			this->dTime->TabIndex = 9;
			this->dTime->Text = L"---------";
			// 
			// bfsText
			// 
			this->bfsText->AutoSize = true;
			this->bfsText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->bfsText->Location = System::Drawing::Point(554, 92);
			this->bfsText->Name = L"bfsText";
			this->bfsText->Size = System::Drawing::Size(51, 25);
			this->bfsText->TabIndex = 10;
			this->bfsText->Text = L"BFS";
			// 
			// bTime
			// 
			this->bTime->AutoSize = true;
			this->bTime->Location = System::Drawing::Point(636, 99);
			this->bTime->Name = L"bTime";
			this->bTime->Size = System::Drawing::Size(43, 16);
			this->bTime->TabIndex = 11;
			this->bTime->Text = L"---------";
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
			this->elapsedtimeText->Location = System::Drawing::Point(533, 9);
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
			this->airportList->Size = System::Drawing::Size(158, 292);
			this->airportList->TabIndex = 15;
			// 
			// airportTitle
			// 
			this->airportTitle->AutoSize = true;
			this->airportTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F));
			this->airportTitle->Location = System::Drawing::Point(555, 120);
			this->airportTitle->Name = L"airportTitle";
			this->airportTitle->Size = System::Drawing::Size(182, 22);
			this->airportTitle->TabIndex = 16;
			this->airportTitle->Text = L"Airport Abbreviations:";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(743, 452);
			this->Controls->Add(this->airportTitle);
			this->Controls->Add(this->airportList);
			this->Controls->Add(this->clearButton);
			this->Controls->Add(this->elapsedtimeText);
			this->Controls->Add(this->resultText);
			this->Controls->Add(this->bTime);
			this->Controls->Add(this->bfsText);
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
	private: System::Void formLoad(System::Object^ sender, System::EventArgs^ e) {
		//TODO: Replace this code with function adding all the airport ID's to the list.
		for (int i = 100; i < 179; i++) {
			airportList->Items->Add(i);
		}
	}
	private: System::Void end_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		if (resultList->Items->Count == 1 && resultList->Items[0]->ToString()->Length == 40) {
			resultList->Items->Clear();
			resultList->Items->Add(L"Results appear here");
		}
	}
	private: System::Void start_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		if (resultList->Items->Count == 1 && resultList->Items[0]->ToString()->Length == 40) {
			resultList->Items->Clear();
			resultList->Items->Add(L"Results appear here");
		}
	}
	private: System::Void searchButton_Click(System::Object^ sender, System::EventArgs^ e) {
		resultList->Items->Clear();
		if (start->Text->Length != 3 || end->Text->Length != 3) {
			resultList->Items->Add(L"Please input valid airport abbreviations");
			return;
		}
		resultList->Items->Add(start->Text + L" " + end->Text);
		//TODO: Add results here...
		dTime->Text = L"0.000ms";
		bTime->Text = L"0.000ms";
	}
	private: System::Void clearButton_Click(System::Object^ sender, System::EventArgs^ e) {
		dTime->Text = L"---------";
		bTime->Text = L"---------";
		resultList->Items->Clear();
		resultList->Items->Add(L"Results appear here");
		start->Clear();
		end->Clear();
	}
};
}
