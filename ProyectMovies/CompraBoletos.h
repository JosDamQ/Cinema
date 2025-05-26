#pragma once
#include "ClaseCompraBoletos.h"
#include "ClaseAsignacionPeliculasSalas.h"
#include "ClaseClientes.h"

namespace ProyectMovies {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class CompraBoletos : public System::Windows::Forms::Form
	{
	private:
		array<AsignacionPeliculaSala^>^ listaAsignaciones;
		array<Cliente^>^ listaClientes;
		array<ComprasBoletos^>^ comprasBoletos;
		int ultimoCodigo;
		int compraSeleccionada;
		enum class ModoFormulario {
			Ninguno,
			Agregar,
			//Editar
		};
		ModoFormulario estadoActual = ModoFormulario::Ninguno;


	public:
		/*CompraBoletos(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}*/
		CompraBoletos(array<AsignacionPeliculaSala^>^ asignacionesExistentes, array<Cliente^>^ clientesExistentes)
		{
			InitializeComponent();
			this->listaAsignaciones = asignacionesExistentes;
			this->listaClientes = clientesExistentes;
			CargarAsignacionesComboBox();
			CargarClientesComboBox();

			comprasBoletos = gcnew array<ComprasBoletos^>(50);
			ultimoCodigo = 0;
			compraSeleccionada = -1;
			ActualizarEstadoFormulario();
			ResetearFormulario();
		}

		// Coso del comboBoc
		void ActualizarListas(array<AsignacionPeliculaSala^>^ asignacionesActualizadas, array<Cliente^>^ clientesActualizados) {
			this->listaAsignaciones = asignacionesActualizadas;
			this->listaClientes = clientesActualizados;
			CargarAsignacionesComboBox();
			CargarClientesComboBox();
		}

		//Funcion agregar
		void AgregarCompraBoleto
		(
			AsignacionPeliculaSala^ asignacion,
			Cliente^ cliente,
			DateTime fechaCompra
		)
		{
			ultimoCodigo++;
			ComprasBoletos^ nuevaCompra = gcnew ComprasBoletos(ultimoCodigo, asignacion, cliente, fechaCompra);
			comprasBoletos[ultimoCodigo - 1] = nuevaCompra;
			MostrarComprasBoletos();
		}

		//Funcion de mostrar
		void MostrarComprasBoletos()
		{
			tblCompras->Rows->Clear();
			for (int i = 0; i < ultimoCodigo; i++) {
				if (comprasBoletos[i] != nullptr) {
					tblCompras->Rows->Add(
						comprasBoletos[i]->Codigo,
						comprasBoletos[i]->AsignacionCompra->PeliculaAsignada->Nombre,
						comprasBoletos[i]->AsignacionCompra->SalaAsignada->Nombre,
						comprasBoletos[i]->ClienteCompra->Nombre,
						comprasBoletos[i]->AsignacionCompra->ObtenerResumenAsignacion(),
						comprasBoletos[i]->AsignacionCompra->FechaEstreno.ToString("dd/MM/yyyy") + " " + comprasBoletos[i]->AsignacionCompra->HoraFuncion,
						"", //Asiento,
						comprasBoletos[i]->AsignacionCompra->PeliculaAsignada->Precio,
						comprasBoletos[i]->FechaCompra.ToString("dd/MM/yyyy")
					);
				}
			}
		}

		void ResetearFormulario()
		{
			cboFuncion->SelectedIndex = -1;
			cboCliente->SelectedIndex = -1;
			dateFecha->ResetText();
		}

		void ActualizarEstadoFormulario()
		{
			bool habilitar = estadoActual != ModoFormulario::Ninguno;

			cboFuncion->Enabled = habilitar;
			cboCliente->Enabled = habilitar;
			dateFecha->Enabled = habilitar;

			if (estadoActual == ModoFormulario::Agregar) {
				btnAgregar->Text = "Confirmar";
				btnEliminar->Text = "Cancelar";
			}
			else {
				btnAgregar->Text = "Agregar";
				btnEliminar->Text = "Eliminar";
				btnAgregar->Enabled = true;
				btnEliminar->Enabled = true;
			}
		}


	protected:

		~CompraBoletos()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lblFuncion;
	private: System::Windows::Forms::ComboBox^ cboFuncion;
	private: System::Windows::Forms::Label^ lblCliente;
	private: System::Windows::Forms::ComboBox^ cboCliente;

	private: System::Windows::Forms::Label^ lblTotal;
	private: System::Windows::Forms::DataGridView^ tblCompras;
	private: System::Windows::Forms::Button^ btnAgregar;
	private: System::Windows::Forms::Button^ btnEliminar;

	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colCodigo;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colPelicula;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colSala;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colCliente;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colFechaFuncion;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colHoraFuncion;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colAsiento;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colTotal;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colFechaCompra;
	private: System::Windows::Forms::Label^ lblFecha;
	private: System::Windows::Forms::DateTimePicker^ dateFecha;




	protected:

	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		
		void CargarAsignacionesComboBox() {
			this->cboFuncion->Items->Clear();
			this->cboFuncion->DisplayMember = "ResumenAsignacion";
			for (int i = 0; i < listaAsignaciones->Length; i++) {
				if (listaAsignaciones[i] != nullptr) {
					cboFuncion->Items->Add(listaAsignaciones[i]);
				}
			}
		}

		void CargarClientesComboBox() {
			this->cboCliente->Items->Clear();
			this->cboCliente->DisplayMember = "Nombre";
			for (int i = 0; i < listaClientes->Length; i++) {
				if (listaClientes[i] != nullptr) {
					cboCliente->Items->Add(listaClientes[i]);
				}
			}
		}


		void InitializeComponent(void)
		{
			this->lblFuncion = (gcnew System::Windows::Forms::Label());
			this->cboFuncion = (gcnew System::Windows::Forms::ComboBox());
			this->lblCliente = (gcnew System::Windows::Forms::Label());
			this->cboCliente = (gcnew System::Windows::Forms::ComboBox());
			this->lblTotal = (gcnew System::Windows::Forms::Label());
			this->tblCompras = (gcnew System::Windows::Forms::DataGridView());
			this->colCodigo = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colPelicula = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colSala = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colCliente = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colFechaFuncion = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colHoraFuncion = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colAsiento = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colTotal = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colFechaCompra = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->lblFecha = (gcnew System::Windows::Forms::Label());
			this->dateFecha = (gcnew System::Windows::Forms::DateTimePicker());
			this->btnAgregar = (gcnew System::Windows::Forms::Button());
			this->btnEliminar = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tblCompras))->BeginInit();
			this->SuspendLayout();
			// 
			// lblFuncion
			// 
			this->lblFuncion->AutoSize = true;
			this->lblFuncion->Location = System::Drawing::Point(91, 68);
			this->lblFuncion->Name = L"lblFuncion";
			this->lblFuncion->Size = System::Drawing::Size(66, 20);
			this->lblFuncion->TabIndex = 0;
			this->lblFuncion->Text = L"Funcion";
			// 
			// cboFuncion
			// 
			this->cboFuncion->FormattingEnabled = true;
			this->cboFuncion->Location = System::Drawing::Point(176, 65);
			this->cboFuncion->Name = L"cboFuncion";
			this->cboFuncion->Size = System::Drawing::Size(1103, 28);
			this->cboFuncion->TabIndex = 1;
			// 
			// lblCliente
			// 
			this->lblCliente->AutoSize = true;
			this->lblCliente->Location = System::Drawing::Point(323, 145);
			this->lblCliente->Name = L"lblCliente";
			this->lblCliente->Size = System::Drawing::Size(58, 20);
			this->lblCliente->TabIndex = 2;
			this->lblCliente->Text = L"Cliente";
			// 
			// cboCliente
			// 
			this->cboCliente->FormattingEnabled = true;
			this->cboCliente->Location = System::Drawing::Point(398, 142);
			this->cboCliente->Name = L"cboCliente";
			this->cboCliente->Size = System::Drawing::Size(158, 28);
			this->cboCliente->TabIndex = 3;
			// 
			// lblTotal
			// 
			this->lblTotal->AutoSize = true;
			this->lblTotal->Location = System::Drawing::Point(730, 71);
			this->lblTotal->Name = L"lblTotal";
			this->lblTotal->Size = System::Drawing::Size(0, 20);
			this->lblTotal->TabIndex = 5;
			// 
			// tblCompras
			// 
			this->tblCompras->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->tblCompras->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(9) {
				this->colCodigo,
					this->colPelicula, this->colSala, this->colCliente, this->colFechaFuncion, this->colHoraFuncion, this->colAsiento, this->colTotal,
					this->colFechaCompra
			});
			this->tblCompras->Location = System::Drawing::Point(51, 279);
			this->tblCompras->Name = L"tblCompras";
			this->tblCompras->RowHeadersWidth = 62;
			this->tblCompras->RowTemplate->Height = 28;
			this->tblCompras->Size = System::Drawing::Size(1193, 409);
			this->tblCompras->TabIndex = 6;
			// 
			// colCodigo
			// 
			this->colCodigo->HeaderText = L"Codigo";
			this->colCodigo->MinimumWidth = 8;
			this->colCodigo->Name = L"colCodigo";
			this->colCodigo->Width = 150;
			// 
			// colPelicula
			// 
			this->colPelicula->HeaderText = L"Pelicula";
			this->colPelicula->MinimumWidth = 8;
			this->colPelicula->Name = L"colPelicula";
			this->colPelicula->Width = 150;
			// 
			// colSala
			// 
			this->colSala->HeaderText = L"Sala";
			this->colSala->MinimumWidth = 8;
			this->colSala->Name = L"colSala";
			this->colSala->Width = 150;
			// 
			// colCliente
			// 
			this->colCliente->HeaderText = L"Cliente";
			this->colCliente->MinimumWidth = 8;
			this->colCliente->Name = L"colCliente";
			this->colCliente->Width = 150;
			// 
			// colFechaFuncion
			// 
			this->colFechaFuncion->HeaderText = L"Funcion";
			this->colFechaFuncion->MinimumWidth = 8;
			this->colFechaFuncion->Name = L"colFechaFuncion";
			this->colFechaFuncion->Width = 150;
			// 
			// colHoraFuncion
			// 
			this->colHoraFuncion->HeaderText = L"HoraFuncion";
			this->colHoraFuncion->MinimumWidth = 8;
			this->colHoraFuncion->Name = L"colHoraFuncion";
			this->colHoraFuncion->Width = 150;
			// 
			// colAsiento
			// 
			this->colAsiento->HeaderText = L"Asiento";
			this->colAsiento->MinimumWidth = 8;
			this->colAsiento->Name = L"colAsiento";
			this->colAsiento->Width = 150;
			// 
			// colTotal
			// 
			this->colTotal->HeaderText = L"Total";
			this->colTotal->MinimumWidth = 8;
			this->colTotal->Name = L"colTotal";
			this->colTotal->Width = 150;
			// 
			// colFechaCompra
			// 
			this->colFechaCompra->HeaderText = L"Fecha de compra";
			this->colFechaCompra->MinimumWidth = 8;
			this->colFechaCompra->Name = L"colFechaCompra";
			this->colFechaCompra->Width = 150;
			// 
			// lblFecha
			// 
			this->lblFecha->AutoSize = true;
			this->lblFecha->Location = System::Drawing::Point(605, 142);
			this->lblFecha->Name = L"lblFecha";
			this->lblFecha->Size = System::Drawing::Size(54, 20);
			this->lblFecha->TabIndex = 7;
			this->lblFecha->Text = L"Fecha";
			this->lblFecha->Click += gcnew System::EventHandler(this, &CompraBoletos::label1_Click);
			// 
			// dateFecha
			// 
			this->dateFecha->Location = System::Drawing::Point(682, 137);
			this->dateFecha->Name = L"dateFecha";
			this->dateFecha->Size = System::Drawing::Size(309, 26);
			this->dateFecha->TabIndex = 8;
			// 
			// btnAgregar
			// 
			this->btnAgregar->Location = System::Drawing::Point(482, 181);
			this->btnAgregar->Name = L"btnAgregar";
			this->btnAgregar->Size = System::Drawing::Size(112, 43);
			this->btnAgregar->TabIndex = 9;
			this->btnAgregar->Text = L"Agregar";
			this->btnAgregar->UseVisualStyleBackColor = true;
			// 
			// btnEliminar
			// 
			this->btnEliminar->Location = System::Drawing::Point(632, 181);
			this->btnEliminar->Name = L"btnEliminar";
			this->btnEliminar->Size = System::Drawing::Size(112, 43);
			this->btnEliminar->TabIndex = 10;
			this->btnEliminar->Text = L"Eliminar";
			this->btnEliminar->UseVisualStyleBackColor = true;
			// 
			// CompraBoletos
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(2284, 1046);
			this->Controls->Add(this->btnEliminar);
			this->Controls->Add(this->btnAgregar);
			this->Controls->Add(this->dateFecha);
			this->Controls->Add(this->lblFecha);
			this->Controls->Add(this->tblCompras);
			this->Controls->Add(this->lblTotal);
			this->Controls->Add(this->cboCliente);
			this->Controls->Add(this->lblCliente);
			this->Controls->Add(this->cboFuncion);
			this->Controls->Add(this->lblFuncion);
			this->Name = L"CompraBoletos";
			this->Text = L"CompraBoletos";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tblCompras))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
