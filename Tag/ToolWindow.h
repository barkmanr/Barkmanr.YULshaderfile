#pragma once

namespace Tag {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class ToolWindow : public System::Windows::Forms::Form
	{
	public:
		//static bool RenderRedChannel;
		//static bool RenderGreenChannel;
		//static bool RenderBlueChannel;

		static int RenderValueY;
		static int RenderValueU;
		static int RenderValueV;
		static bool Invert;

	private: System::Windows::Forms::TrackBar^ TY;
	private: System::Windows::Forms::TrackBar^ TU;
	private: System::Windows::Forms::TrackBar^ TV;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ labelY;
	private: System::Windows::Forms::Label^ labelU;
	private: System::Windows::Forms::CheckBox^ Inverter;
	private: System::Windows::Forms::Label^ labelV;
	public:

	public:


		ToolWindow(void)
		{
			InitializeComponent();
			//RenderRedChannel = checkBoxRedChannel->Checked;
			//RenderGreenChannel = checkBoxGreenChannel->Checked;
			//RenderBlueChannel = checkBoxBlueChannel->Checked;
			RenderValueY = TY->Value;
			RenderValueU = TU->Value;
			RenderValueV = TV->Value;
			labelY->Text = TY->Value.ToString() + "%";
			labelU->Text = TU->Value.ToString() + "%";
			labelV->Text = TV->Value.ToString() + "%";
			Invert = Inverter->Checked;
		}

	protected:
		~ToolWindow()
		{
			if (components)
			{
				delete components;
			}
		}




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
			this->TY = (gcnew System::Windows::Forms::TrackBar());
			this->TU = (gcnew System::Windows::Forms::TrackBar());
			this->TV = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->labelY = (gcnew System::Windows::Forms::Label());
			this->labelU = (gcnew System::Windows::Forms::Label());
			this->labelV = (gcnew System::Windows::Forms::Label());
			this->Inverter = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TU))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TV))->BeginInit();
			this->SuspendLayout();
			// 
			// TY
			// 
			this->TY->Location = System::Drawing::Point(61, 37);
			this->TY->Maximum = 200;
			this->TY->Name = L"TY";
			this->TY->Size = System::Drawing::Size(613, 45);
			this->TY->TabIndex = 12;
			this->TY->Value = 100;
			this->TY->Scroll += gcnew System::EventHandler(this, &ToolWindow::TY_Scroll);
			this->TY->ValueChanged += gcnew System::EventHandler(this, &ToolWindow::TY_ValueChanged);
			// 
			// TU
			// 
			this->TU->Location = System::Drawing::Point(61, 88);
			this->TU->Maximum = 200;
			this->TU->Name = L"TU";
			this->TU->Size = System::Drawing::Size(613, 45);
			this->TU->TabIndex = 13;
			this->TU->Value = 100;
			this->TU->ValueChanged += gcnew System::EventHandler(this, &ToolWindow::TU_ValueChanged);
			// 
			// TV
			// 
			this->TV->Location = System::Drawing::Point(61, 139);
			this->TV->Maximum = 200;
			this->TV->Name = L"TV";
			this->TV->Size = System::Drawing::Size(613, 45);
			this->TV->TabIndex = 14;
			this->TV->Value = 100;
			this->TV->ValueChanged += gcnew System::EventHandler(this, &ToolWindow::TV_ValueChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(14, 37);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(14, 13);
			this->label1->TabIndex = 15;
			this->label1->Text = L"Y";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(14, 88);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(15, 13);
			this->label2->TabIndex = 16;
			this->label2->Text = L"U";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(17, 139);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(14, 13);
			this->label3->TabIndex = 17;
			this->label3->Text = L"V";
			// 
			// labelY
			// 
			this->labelY->AutoSize = true;
			this->labelY->Location = System::Drawing::Point(697, 37);
			this->labelY->Name = L"labelY";
			this->labelY->Size = System::Drawing::Size(35, 13);
			this->labelY->TabIndex = 18;
			this->labelY->Text = L"label4";
			// 
			// labelU
			// 
			this->labelU->AutoSize = true;
			this->labelU->Location = System::Drawing::Point(697, 88);
			this->labelU->Name = L"labelU";
			this->labelU->Size = System::Drawing::Size(35, 13);
			this->labelU->TabIndex = 19;
			this->labelU->Text = L"label4";
			// 
			// labelV
			// 
			this->labelV->AutoSize = true;
			this->labelV->Location = System::Drawing::Point(697, 149);
			this->labelV->Name = L"labelV";
			this->labelV->Size = System::Drawing::Size(35, 13);
			this->labelV->TabIndex = 20;
			this->labelV->Text = L"label4";
			// 
			// Inverter
			// 
			this->Inverter->AutoSize = true;
			this->Inverter->Location = System::Drawing::Point(20, 190);
			this->Inverter->Name = L"Inverter";
			this->Inverter->Size = System::Drawing::Size(85, 17);
			this->Inverter->TabIndex = 21;
			this->Inverter->Text = L"Invert Colors";
			this->Inverter->UseVisualStyleBackColor = true;
			this->Inverter->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::Inverter_CheckedChanged);
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(776, 247);
			this->Controls->Add(this->Inverter);
			this->Controls->Add(this->labelV);
			this->Controls->Add(this->labelU);
			this->Controls->Add(this->labelY);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->TV);
			this->Controls->Add(this->TU);
			this->Controls->Add(this->TY);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->Load += gcnew System::EventHandler(this, &ToolWindow::ToolWindow_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TU))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TV))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void checkBoxRedChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		//RenderRedChannel = checkBoxRedChannel->Checked;
	}

	private: System::Void checkBoxGreenChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		//RenderGreenChannel = checkBoxGreenChannel->Checked;
	}

	private: System::Void checkBoxBlueChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		//RenderBlueChannel = checkBoxBlueChannel->Checked;
	}

private: System::Void ToolWindow_Load(System::Object^ sender, System::EventArgs^ e) 
{
}

private: System::Void TY_Scroll(System::Object^ sender, System::EventArgs^ e) 
{
}
private: System::Void TY_ValueChanged(System::Object^ sender, System::EventArgs^ e) 
{
	RenderValueY = TY->Value;
	labelY->Text = TY->Value.ToString() + "%";
}
private: System::Void TU_ValueChanged(System::Object^ sender, System::EventArgs^ e) 
{
	RenderValueU = TU->Value;
	labelU->Text = TU->Value.ToString() + "%";
}

private: System::Void TV_ValueChanged(System::Object^ sender, System::EventArgs^ e) 
{
	RenderValueV = TV->Value;
	labelV->Text = TV->Value.ToString() + "%";
}

private: System::Void Inverter_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
{
	Invert = Inverter->Checked;
}
};

}
