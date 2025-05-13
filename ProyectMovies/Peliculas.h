#pragma once

namespace ProyectMovies {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Peliculas
	/// </summary>
	public ref class Peliculas : public System::Windows::Forms::Form
	//public ref class Peliculas : public System::Windows::Forms::UserControl
	{
	public:
		Peliculas(void)
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
		~Peliculas()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::DataGridView^ tblPelicula;

	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colCodigo;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colNombre;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colGenero;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colClasificacion;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colIdioma;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colFormato;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colPrecio;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colEstado;
	private: System::Windows::Forms::TextBox^ txtNombre;
	private: System::Windows::Forms::Label^ lblNombre;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ txtPrecio;
	private: System::Windows::Forms::ComboBox^ cdoGenero;
	private: System::Windows::Forms::Label^ lblGenero;
	private: System::Windows::Forms::Label^ lblClasificacion;
	private: System::Windows::Forms::ComboBox^ cdoClasificacion;
	private: System::Windows::Forms::Label^ lblFormato;
	private: System::Windows::Forms::ComboBox^ cdoFormato;
	private: System::Windows::Forms::Label^ lblIdioma;
	private: System::Windows::Forms::ComboBox^ cdoIdioma;
	private: System::Windows::Forms::Label^ lblEstado;
	private: System::Windows::Forms::ComboBox^ cdoEstado;








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
			this->tblPelicula = (gcnew System::Windows::Forms::DataGridView());
			this->colCodigo = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colNombre = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colGenero = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colClasificacion = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colIdioma = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colFormato = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colPrecio = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colEstado = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->txtNombre = (gcnew System::Windows::Forms::TextBox());
			this->lblNombre = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtPrecio = (gcnew System::Windows::Forms::TextBox());
			this->cdoGenero = (gcnew System::Windows::Forms::ComboBox());
			this->lblGenero = (gcnew System::Windows::Forms::Label());
			this->lblClasificacion = (gcnew System::Windows::Forms::Label());
			this->cdoClasificacion = (gcnew System::Windows::Forms::ComboBox());
			this->lblFormato = (gcnew System::Windows::Forms::Label());
			this->cdoFormato = (gcnew System::Windows::Forms::ComboBox());
			this->lblIdioma = (gcnew System::Windows::Forms::Label());
			this->cdoIdioma = (gcnew System::Windows::Forms::ComboBox());
			this->lblEstado = (gcnew System::Windows::Forms::Label());
			this->cdoEstado = (gcnew System::Windows::Forms::ComboBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tblPelicula))->BeginInit();
			this->SuspendLayout();
			// 
			// tblPelicula
			// 
			this->tblPelicula->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->tblPelicula->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(8) {
				this->colCodigo,
					this->colNombre, this->colGenero, this->colClasificacion, this->colIdioma, this->colFormato, this->colPrecio, this->colEstado
			});
			this->tblPelicula->Location = System::Drawing::Point(27, 185);
			this->tblPelicula->Name = L"tblPelicula";
			this->tblPelicula->RowHeadersWidth = 51;
			this->tblPelicula->RowTemplate->Height = 24;
			this->tblPelicula->Size = System::Drawing::Size(1054, 262);
			this->tblPelicula->TabIndex = 1;
			// 
			// colCodigo
			// 
			this->colCodigo->HeaderText = L"Codigo";
			this->colCodigo->MinimumWidth = 6;
			this->colCodigo->Name = L"colCodigo";
			this->colCodigo->Width = 125;
			// 
			// colNombre
			// 
			this->colNombre->HeaderText = L"Nombre";
			this->colNombre->MinimumWidth = 6;
			this->colNombre->Name = L"colNombre";
			this->colNombre->Width = 125;
			// 
			// colGenero
			// 
			this->colGenero->HeaderText = L"Genero";
			this->colGenero->MinimumWidth = 6;
			this->colGenero->Name = L"colGenero";
			this->colGenero->Width = 125;
			// 
			// colClasificacion
			// 
			this->colClasificacion->HeaderText = L"Clasificacion";
			this->colClasificacion->MinimumWidth = 6;
			this->colClasificacion->Name = L"colClasificacion";
			this->colClasificacion->Width = 125;
			// 
			// colIdioma
			// 
			this->colIdioma->HeaderText = L"Idioma";
			this->colIdioma->MinimumWidth = 6;
			this->colIdioma->Name = L"colIdioma";
			this->colIdioma->Width = 125;
			// 
			// colFormato
			// 
			this->colFormato->HeaderText = L"Formato";
			this->colFormato->MinimumWidth = 6;
			this->colFormato->Name = L"colFormato";
			this->colFormato->Width = 125;
			// 
			// colPrecio
			// 
			this->colPrecio->HeaderText = L"Precio";
			this->colPrecio->MinimumWidth = 6;
			this->colPrecio->Name = L"colPrecio";
			this->colPrecio->Width = 125;
			// 
			// colEstado
			// 
			this->colEstado->HeaderText = L"Estado";
			this->colEstado->MinimumWidth = 6;
			this->colEstado->Name = L"colEstado";
			this->colEstado->Width = 125;
			// 
			// txtNombre
			// 
			this->txtNombre->Location = System::Drawing::Point(86, 22);
			this->txtNombre->Multiline = true;
			this->txtNombre->Name = L"txtNombre";
			this->txtNombre->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->txtNombre->Size = System::Drawing::Size(100, 22);
			this->txtNombre->TabIndex = 2;
			// 
			// lblNombre
			// 
			this->lblNombre->AutoSize = true;
			this->lblNombre->Location = System::Drawing::Point(24, 25);
			this->lblNombre->Name = L"lblNombre";
			this->lblNombre->Size = System::Drawing::Size(56, 16);
			this->lblNombre->TabIndex = 3;
			this->lblNombre->Text = L"Nombre";
			this->lblNombre->Click += gcnew System::EventHandler(this, &Peliculas::label1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(480, 82);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(46, 16);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Precio";
			// 
			// txtPrecio
			// 
			this->txtPrecio->Location = System::Drawing::Point(542, 79);
			this->txtPrecio->Multiline = true;
			this->txtPrecio->Name = L"txtPrecio";
			this->txtPrecio->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->txtPrecio->Size = System::Drawing::Size(100, 22);
			this->txtPrecio->TabIndex = 4;
			// 
			// cdoGenero
			// 
			this->cdoGenero->FormattingEnabled = true;
			this->cdoGenero->Location = System::Drawing::Point(279, 20);
			this->cdoGenero->Name = L"cdoGenero";
			this->cdoGenero->Size = System::Drawing::Size(121, 24);
			this->cdoGenero->TabIndex = 6;
			// 
			// lblGenero
			// 
			this->lblGenero->AutoSize = true;
			this->lblGenero->Location = System::Drawing::Point(221, 25);
			this->lblGenero->Name = L"lblGenero";
			this->lblGenero->Size = System::Drawing::Size(52, 16);
			this->lblGenero->TabIndex = 7;
			this->lblGenero->Text = L"Genero";
			// 
			// lblClasificacion
			// 
			this->lblClasificacion->AutoSize = true;
			this->lblClasificacion->Location = System::Drawing::Point(432, 27);
			this->lblClasificacion->Name = L"lblClasificacion";
			this->lblClasificacion->Size = System::Drawing::Size(83, 16);
			this->lblClasificacion->TabIndex = 9;
			this->lblClasificacion->Text = L"Clasificacion";
			// 
			// cdoClasificacion
			// 
			this->cdoClasificacion->FormattingEnabled = true;
			this->cdoClasificacion->Location = System::Drawing::Point(521, 25);
			this->cdoClasificacion->Name = L"cdoClasificacion";
			this->cdoClasificacion->Size = System::Drawing::Size(121, 24);
			this->cdoClasificacion->TabIndex = 8;
			// 
			// lblFormato
			// 
			this->lblFormato->AutoSize = true;
			this->lblFormato->Location = System::Drawing::Point(23, 81);
			this->lblFormato->Name = L"lblFormato";
			this->lblFormato->Size = System::Drawing::Size(57, 16);
			this->lblFormato->TabIndex = 11;
			this->lblFormato->Text = L"Formato";
			// 
			// cdoFormato
			// 
			this->cdoFormato->FormattingEnabled = true;
			this->cdoFormato->Location = System::Drawing::Point(86, 79);
			this->cdoFormato->Name = L"cdoFormato";
			this->cdoFormato->Size = System::Drawing::Size(121, 24);
			this->cdoFormato->TabIndex = 10;
			// 
			// lblIdioma
			// 
			this->lblIdioma->AutoSize = true;
			this->lblIdioma->Location = System::Drawing::Point(227, 83);
			this->lblIdioma->Name = L"lblIdioma";
			this->lblIdioma->Size = System::Drawing::Size(48, 16);
			this->lblIdioma->TabIndex = 13;
			this->lblIdioma->Text = L"Idioma";
			// 
			// cdoIdioma
			// 
			this->cdoIdioma->FormattingEnabled = true;
			this->cdoIdioma->Location = System::Drawing::Point(316, 81);
			this->cdoIdioma->Name = L"cdoIdioma";
			this->cdoIdioma->Size = System::Drawing::Size(121, 24);
			this->cdoIdioma->TabIndex = 12;
			// 
			// lblEstado
			// 
			this->lblEstado->AutoSize = true;
			this->lblEstado->Location = System::Drawing::Point(28, 125);
			this->lblEstado->Name = L"lblEstado";
			this->lblEstado->Size = System::Drawing::Size(50, 16);
			this->lblEstado->TabIndex = 15;
			this->lblEstado->Text = L"Estado";
			// 
			// cdoEstado
			// 
			this->cdoEstado->FormattingEnabled = true;
			this->cdoEstado->Location = System::Drawing::Point(117, 123);
			this->cdoEstado->Name = L"cdoEstado";
			this->cdoEstado->Size = System::Drawing::Size(121, 24);
			this->cdoEstado->TabIndex = 14;
			// 
			// Peliculas
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1227, 490);
			this->Controls->Add(this->lblEstado);
			this->Controls->Add(this->cdoEstado);
			this->Controls->Add(this->lblIdioma);
			this->Controls->Add(this->cdoIdioma);
			this->Controls->Add(this->lblFormato);
			this->Controls->Add(this->cdoFormato);
			this->Controls->Add(this->lblClasificacion);
			this->Controls->Add(this->cdoClasificacion);
			this->Controls->Add(this->lblGenero);
			this->Controls->Add(this->cdoGenero);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->txtPrecio);
			this->Controls->Add(this->lblNombre);
			this->Controls->Add(this->txtNombre);
			this->Controls->Add(this->tblPelicula);
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"Peliculas";
			this->Text = L"Peliculas";
			this->Load += gcnew System::EventHandler(this, &Peliculas::Peliculas_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tblPelicula))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void Peliculas_Load(System::Object^ sender, System::EventArgs^ e) {
}
};
}
