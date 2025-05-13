#pragma once

namespace ProyectMovies {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Salas
	/// </summary>
	public ref class Salas : public System::Windows::Forms::Form
	{
	public:
		Salas(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Salas()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colCodigo;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colNombre;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colCapacidad;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colUbicacion;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colNombreEncargado;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colTelefonoEncargado;
	private: System::Windows::Forms::Label^ lblcodigo;
	private: System::Windows::Forms::TextBox^ txtCodigo;
	private: System::Windows::Forms::TextBox^ txtNombre;

	private: System::Windows::Forms::Label^ lblNombre;
	private: System::Windows::Forms::TextBox^ txtUbicacion;
	private: System::Windows::Forms::Label^ lblUbicacion;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ComboBox^ cboCapacidad;
	private: System::Windows::Forms::ComboBox^ cboNombreEncargado;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ txtTelefonoEncargado;

	private: System::Windows::Forms::Label^ lblTelefonoEncargado;






	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->colCodigo = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colNombre = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colCapacidad = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colUbicacion = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colNombreEncargado = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colTelefonoEncargado = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->lblcodigo = (gcnew System::Windows::Forms::Label());
			this->txtCodigo = (gcnew System::Windows::Forms::TextBox());
			this->txtNombre = (gcnew System::Windows::Forms::TextBox());
			this->lblNombre = (gcnew System::Windows::Forms::Label());
			this->txtUbicacion = (gcnew System::Windows::Forms::TextBox());
			this->lblUbicacion = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->cboCapacidad = (gcnew System::Windows::Forms::ComboBox());
			this->cboNombreEncargado = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->txtTelefonoEncargado = (gcnew System::Windows::Forms::TextBox());
			this->lblTelefonoEncargado = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {
				this->colCodigo,
					this->colNombre, this->colCapacidad, this->colUbicacion, this->colNombreEncargado, this->colTelefonoEncargado
			});
			this->dataGridView1->Location = System::Drawing::Point(20, 130);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(643, 217);
			this->dataGridView1->TabIndex = 1;
			// 
			// colCodigo
			// 
			this->colCodigo->HeaderText = L"Código";
			this->colCodigo->Name = L"colCodigo";
			// 
			// colNombre
			// 
			this->colNombre->HeaderText = L"Nombre";
			this->colNombre->Name = L"colNombre";
			// 
			// colCapacidad
			// 
			this->colCapacidad->HeaderText = L"Capacidad";
			this->colCapacidad->Name = L"colCapacidad";
			// 
			// colUbicacion
			// 
			this->colUbicacion->HeaderText = L"Ubicacíon";
			this->colUbicacion->Name = L"colUbicacion";
			// 
			// colNombreEncargado
			// 
			this->colNombreEncargado->HeaderText = L"Nombre del encargado";
			this->colNombreEncargado->Name = L"colNombreEncargado";
			// 
			// colTelefonoEncargado
			// 
			this->colTelefonoEncargado->HeaderText = L"Teléfono del encargado";
			this->colTelefonoEncargado->Name = L"colTelefonoEncargado";
			// 
			// lblcodigo
			// 
			this->lblcodigo->AutoSize = true;
			this->lblcodigo->Location = System::Drawing::Point(26, 21);
			this->lblcodigo->Name = L"lblcodigo";
			this->lblcodigo->Size = System::Drawing::Size(40, 13);
			this->lblcodigo->TabIndex = 2;
			this->lblcodigo->Text = L"Código";
			this->lblcodigo->Click += gcnew System::EventHandler(this, &Salas::label2_Click);
			// 
			// txtCodigo
			// 
			this->txtCodigo->Location = System::Drawing::Point(72, 18);
			this->txtCodigo->Name = L"txtCodigo";
			this->txtCodigo->Size = System::Drawing::Size(100, 20);
			this->txtCodigo->TabIndex = 3;
			// 
			// txtNombre
			// 
			this->txtNombre->Location = System::Drawing::Point(235, 21);
			this->txtNombre->Name = L"txtNombre";
			this->txtNombre->Size = System::Drawing::Size(100, 20);
			this->txtNombre->TabIndex = 5;
			// 
			// lblNombre
			// 
			this->lblNombre->AutoSize = true;
			this->lblNombre->Location = System::Drawing::Point(189, 24);
			this->lblNombre->Name = L"lblNombre";
			this->lblNombre->Size = System::Drawing::Size(44, 13);
			this->lblNombre->TabIndex = 4;
			this->lblNombre->Text = L"Nombre";
			// 
			// txtUbicacion
			// 
			this->txtUbicacion->Location = System::Drawing::Point(584, 24);
			this->txtUbicacion->Name = L"txtUbicacion";
			this->txtUbicacion->Size = System::Drawing::Size(100, 20);
			this->txtUbicacion->TabIndex = 7;
			// 
			// lblUbicacion
			// 
			this->lblUbicacion->AutoSize = true;
			this->lblUbicacion->Location = System::Drawing::Point(521, 27);
			this->lblUbicacion->Name = L"lblUbicacion";
			this->lblUbicacion->Size = System::Drawing::Size(57, 13);
			this->lblUbicacion->TabIndex = 6;
			this->lblUbicacion->Text = L"Ubicacíon";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(341, 25);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(58, 13);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Capacidad";
			// 
			// cboCapacidad
			// 
			this->cboCapacidad->FormattingEnabled = true;
			this->cboCapacidad->Location = System::Drawing::Point(396, 22);
			this->cboCapacidad->Name = L"cboCapacidad";
			this->cboCapacidad->Size = System::Drawing::Size(121, 21);
			this->cboCapacidad->TabIndex = 9;
			// 
			// cboNombreEncargado
			// 
			this->cboNombreEncargado->FormattingEnabled = true;
			this->cboNombreEncargado->Location = System::Drawing::Point(138, 60);
			this->cboNombreEncargado->Name = L"cboNombreEncargado";
			this->cboNombreEncargado->Size = System::Drawing::Size(121, 21);
			this->cboNombreEncargado->TabIndex = 11;
			this->cboNombreEncargado->SelectedIndexChanged += gcnew System::EventHandler(this, &Salas::cboNombreEncargado_SelectedIndexChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(17, 63);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(115, 13);
			this->label3->TabIndex = 10;
			this->label3->Text = L"Nombre del encargado";
			this->label3->Click += gcnew System::EventHandler(this, &Salas::label3_Click);
			// 
			// txtTelefonoEncargado
			// 
			this->txtTelefonoEncargado->Location = System::Drawing::Point(396, 59);
			this->txtTelefonoEncargado->Name = L"txtTelefonoEncargado";
			this->txtTelefonoEncargado->Size = System::Drawing::Size(100, 20);
			this->txtTelefonoEncargado->TabIndex = 13;
			this->txtTelefonoEncargado->TextChanged += gcnew System::EventHandler(this, &Salas::txtTelefonoEncargado_TextChanged);
			// 
			// lblTelefonoEncargado
			// 
			this->lblTelefonoEncargado->AutoSize = true;
			this->lblTelefonoEncargado->Location = System::Drawing::Point(274, 66);
			this->lblTelefonoEncargado->Name = L"lblTelefonoEncargado";
			this->lblTelefonoEncargado->Size = System::Drawing::Size(120, 13);
			this->lblTelefonoEncargado->TabIndex = 12;
			this->lblTelefonoEncargado->Text = L"Telefono del encargado";
			this->lblTelefonoEncargado->Click += gcnew System::EventHandler(this, &Salas::label4_Click);
			// 
			// Salas
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(786, 443);
			this->Controls->Add(this->txtTelefonoEncargado);
			this->Controls->Add(this->lblTelefonoEncargado);
			this->Controls->Add(this->cboNombreEncargado);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->cboCapacidad);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->txtUbicacion);
			this->Controls->Add(this->lblUbicacion);
			this->Controls->Add(this->txtNombre);
			this->Controls->Add(this->lblNombre);
			this->Controls->Add(this->txtCodigo);
			this->Controls->Add(this->lblcodigo);
			this->Controls->Add(this->dataGridView1);
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"Salas";
			this->Text = L"Salas";
			this->Load += gcnew System::EventHandler(this, &Salas::Salas_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Salas_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void cboNombreEncargado_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void txtTelefonoEncargado_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
