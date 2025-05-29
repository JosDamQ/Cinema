/*
	Josue Garcia 9490-24-4256
	Fabian 
*/

#pragma once
#include "ClaseCompraBoletos.h"
#include "ClaseAsignacionPeliculasSalas.h"
#include "ClaseClientes.h"
#include "GeneradorReporte.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <fstream>
#undef ServiceProvider

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

		int asientoFilaSeleccionado = -1;
		int asientoColumnaSeleccionado = -1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colCodigo;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colPelicula;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colIdioma;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colFormato;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colSala;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colCliente;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colFechaFuncion;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colHoraFuncion;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colAsiento;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colTotal;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colFechaCompra;
	private: System::Windows::Forms::Button^ btnHTML;
	private: System::Windows::Forms::Button^ btnCargaDatos;
	private: System::Windows::Forms::Button^ btnDescargaDatos;











		   enum class ModoFormulario {
			   Ninguno,
			   Agregar,
		   };
		   ModoFormulario estadoActual = ModoFormulario::Ninguno;


	public:
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
		void AgregarCompraBoleto(AsignacionPeliculaSala^ asignacion, Cliente^ cliente, DateTime fechaCompra, int fila, int columna) {
			if (asientoFilaSeleccionado == -1) {
				MessageBox::Show("Seleccione un asiento.");
				return;
			}

			// Ocupar el asiento en la sala
			asignacion->SalaAsignada->OcuparAsiento(asientoFilaSeleccionado, asientoColumnaSeleccionado);

			// Resto de la lógica de agregar compra...
			ultimoCodigo++;
			ComprasBoletos^ nuevaCompra = gcnew ComprasBoletos(ultimoCodigo, asignacion, cliente, fechaCompra, fila, columna);
			comprasBoletos[ultimoCodigo - 1] = nuevaCompra;
			MostrarComprasBoletos();
		}

		void AgregarCompraBoletoCargaData(AsignacionPeliculaSala^ asignacion, Cliente^ cliente, DateTime fechaCompra, int fila, int columna) {
			/*if (asientoFilaSeleccionado == -1) {
				MessageBox::Show("Seleccione un asiento.");
				return;
			}*/

			// Ocupar el asiento en la sala
			//asignacion->SalaAsignada->OcuparAsiento(asientoFilaSeleccionado, asientoColumnaSeleccionado);

			// Resto de la lógica de agregar compra...
			ultimoCodigo++;
			ComprasBoletos^ nuevaCompra = gcnew ComprasBoletos(ultimoCodigo, asignacion, cliente, fechaCompra, fila, columna);
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
						comprasBoletos[i]->AsignacionCompra->PeliculaAsignada->IdiomaPelicula.ToString(),
						comprasBoletos[i]->AsignacionCompra->PeliculaAsignada->FormatoPelicula.ToString(),
						comprasBoletos[i]->AsignacionCompra->SalaAsignada->Nombre,
						comprasBoletos[i]->ClienteCompra->Nombre,
						comprasBoletos[i]->AsignacionCompra->ObtenerResumenAsignacion(),
						comprasBoletos[i]->AsignacionCompra->FechaEstreno.ToString("dd/MM/yyyy") + " " + comprasBoletos[i]->AsignacionCompra->HoraFuncion,
						String::Format("Fila {0}, Columna {1}",
							comprasBoletos[i]->FilaAsiento + 1,
							comprasBoletos[i]->ColumnaAsiento + 1),
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
				btnHTML->Enabled = false;
				btnCargaDatos->Enabled = false;
				btnDescargaDatos->Enabled = false;
			}
			else {
				btnAgregar->Text = "Agregar";
				btnEliminar->Text = "Eliminar";
				btnAgregar->Enabled = true;
				btnEliminar->Enabled = true;
				btnHTML->Enabled = true;
				btnCargaDatos->Enabled = true;
				btnDescargaDatos->Enabled = true;
			}
		}

	private:
		void GenerarReporteHTML()
		{
			if (compraSeleccionada == -1) {
				MessageBox::Show("Por favor seleccione una compra para generar el reporte.",
					"Información", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return;
			}

			// Obtener la compra seleccionada
			ComprasBoletos^ compra = comprasBoletos[compraSeleccionada];
			if (compra == nullptr) {
				MessageBox::Show("La compra seleccionada no es válida.",
					"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			// Preparar los datos para el reporte
			array<String^>^ encabezados = gcnew array<String^>{
				"Código", "Película", "Idioma", "Formato",
					"Sala", "Cliente", "Función", "Hora",
					"Asiento", "Total", "Fecha Compra"
			};

			// Crear array con solo la compra seleccionada
			array<array<String^>^>^ datos = gcnew array<array<String^>^>(1);
			datos[0] = gcnew array<String^>{
				compra->Codigo.ToString(),
					compra->AsignacionCompra->PeliculaAsignada->Nombre,
					compra->AsignacionCompra->PeliculaAsignada->IdiomaPelicula.ToString(),
					compra->AsignacionCompra->PeliculaAsignada->FormatoPelicula.ToString(),
					compra->AsignacionCompra->SalaAsignada->Nombre,
					compra->ClienteCompra->Nombre + " " + compra->ClienteCompra->Apellido,
					compra->AsignacionCompra->FechaEstreno.ToString("dd/MM/yyyy"),
					compra->AsignacionCompra->HoraFuncion,
					String::Format("Fila {0}, Columna {1}", compra->FilaAsiento + 1, compra->ColumnaAsiento + 1),
					compra->AsignacionCompra->PeliculaAsignada->Precio,
					compra->FechaCompra.ToString("dd/MM/yyyy")
			};

			// Generar el reporte usando la clase general
			GeneradorReporte::GenerarReporte(
				"Reporte de Compra de Boletos",
				"Detalle de Compra Seleccionada",
				"Sistema de Gestión de Compras - ProyectMovies",
				encabezados,
				datos,
				"ReporteCompraBoletos");
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










	private: System::Windows::Forms::Label^ lblFecha;
	private: System::Windows::Forms::DateTimePicker^ dateFecha;

		   // Asientos
	private: System::Windows::Forms::Panel^ panelAsientos;
	private: System::Windows::Forms::Label^ lblAsientos;


	protected:

	protected:

	private:
		System::ComponentModel::Container^ components;

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

		void CompactarArrayCompras() {
			int indiceDestino = 0;
			for (int i = 0; i < comprasBoletos->Length; i++) {
				if (comprasBoletos[i] != nullptr) {
					if (i != indiceDestino) {
						comprasBoletos[indiceDestino] = comprasBoletos[i];
						comprasBoletos[i] = nullptr;
					}
					indiceDestino++;
				}
			}
		}

		void ActualizarUltimoCodigo() {
			ultimoCodigo = 0;
			for (int i = 0; i < comprasBoletos->Length; i++) {
				if (comprasBoletos[i] != nullptr) {
					ultimoCodigo++;
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

		void MostrarAsientos(Sala^ sala) {
			if (panelAsientos == nullptr) {
				panelAsientos = gcnew Panel();
				panelAsientos->Location = System::Drawing::Point(1334, 40);
				panelAsientos->Size = System::Drawing::Size(933, 741);
				this->Controls->Add(panelAsientos);
			}

			panelAsientos->Controls->Clear();

			int filas = (sala->Capacidad == CapacidadSala::Capacidad_40) ? 5 : 7;
			int columnas = 8;
			int anchoBoton = 40;
			int altoBoton = 40;
			int espacio = 5;

			for (int fila = 0; fila < filas; fila++) {
				for (int columna = 0; columna < columnas; columna++) {
					Button^ btnAsiento = gcnew Button();
					btnAsiento->Width = anchoBoton;
					btnAsiento->Height = altoBoton;
					btnAsiento->Left = columna * (anchoBoton + espacio);
					btnAsiento->Top = fila * (altoBoton + espacio);
					btnAsiento->Text = String::Format("{0}-{1}", fila + 1, columna + 1);
					btnAsiento->Tag = gcnew Tuple<int, int>(fila, columna);

					bool disponible = sala->Asientos[fila][columna];

					if (disponible) {
						btnAsiento->BackColor = Color::Green;
						btnAsiento->Click += gcnew EventHandler(this, &CompraBoletos::Asiento_Click);
					}
					else {
						btnAsiento->BackColor = Color::Red;
						btnAsiento->Enabled = false;
					}

					panelAsientos->Controls->Add(btnAsiento);
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
			this->colIdioma = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colFormato = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
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
			this->panelAsientos = (gcnew System::Windows::Forms::Panel());
			this->btnHTML = (gcnew System::Windows::Forms::Button());
			this->btnCargaDatos = (gcnew System::Windows::Forms::Button());
			this->btnDescargaDatos = (gcnew System::Windows::Forms::Button());
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
			this->cboFuncion->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cboFuncion->FormattingEnabled = true;
			this->cboFuncion->Location = System::Drawing::Point(176, 65);
			this->cboFuncion->Name = L"cboFuncion";
			this->cboFuncion->Size = System::Drawing::Size(1103, 28);
			this->cboFuncion->TabIndex = 1;
			this->cboFuncion->SelectedIndexChanged += gcnew System::EventHandler(this, &CompraBoletos::cboFuncion_SelectedIndexChanged);
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
			this->cboCliente->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
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
			this->tblCompras->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(11) {
				this->colCodigo,
					this->colPelicula, this->colIdioma, this->colFormato, this->colSala, this->colCliente, this->colFechaFuncion, this->colHoraFuncion,
					this->colAsiento, this->colTotal, this->colFechaCompra
			});
			this->tblCompras->Location = System::Drawing::Point(12, 279);
			this->tblCompras->Name = L"tblCompras";
			this->tblCompras->RowHeadersWidth = 62;
			this->tblCompras->RowTemplate->Height = 28;
			this->tblCompras->Size = System::Drawing::Size(1193, 409);
			this->tblCompras->TabIndex = 6;
			this->tblCompras->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &CompraBoletos::tblCompras_CellClick);
			this->tblCompras->AllowUserToAddRows = false;
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
			// colIdioma
			// 
			this->colIdioma->HeaderText = L"Idioma";
			this->colIdioma->Name = L"colIdioma";
			// 
			// colFormato
			// 
			this->colFormato->HeaderText = L"Formato";
			this->colFormato->Name = L"colFormato";
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
			this->btnAgregar->Location = System::Drawing::Point(197, 196);
			this->btnAgregar->Name = L"btnAgregar";
			this->btnAgregar->Size = System::Drawing::Size(112, 43);
			this->btnAgregar->TabIndex = 9;
			this->btnAgregar->Text = L"Agregar";
			this->btnAgregar->UseVisualStyleBackColor = true;
			this->btnAgregar->Click += gcnew System::EventHandler(this, &CompraBoletos::btnAgregar_Click);
			// 
			// btnEliminar
			// 
			this->btnEliminar->Location = System::Drawing::Point(379, 196);
			this->btnEliminar->Name = L"btnEliminar";
			this->btnEliminar->Size = System::Drawing::Size(112, 43);
			this->btnEliminar->TabIndex = 10;
			this->btnEliminar->Text = L"Eliminar";
			this->btnEliminar->UseVisualStyleBackColor = true;
			this->btnEliminar->Click += gcnew System::EventHandler(this, &CompraBoletos::btnEliminar_Click);
			// 
			// panelAsientos
			// 
			this->panelAsientos->BackColor = System::Drawing::Color::LightGray;
			this->panelAsientos->Location = System::Drawing::Point(1334, 40);
			this->panelAsientos->Name = L"panelAsientos";
			this->panelAsientos->Size = System::Drawing::Size(933, 741);
			this->panelAsientos->TabIndex = 11;
			// 
			// btnHTML
			// 
			this->btnHTML->Location = System::Drawing::Point(558, 196);
			this->btnHTML->Name = L"btnHTML";
			this->btnHTML->Size = System::Drawing::Size(112, 43);
			this->btnHTML->TabIndex = 12;
			this->btnHTML->Text = L"HTML";
			this->btnHTML->UseVisualStyleBackColor = true;
			this->btnHTML->Click += gcnew System::EventHandler(this, &CompraBoletos::btnHTML_Click);
			// 
			// btnCargaDatos
			// 
			this->btnCargaDatos->Location = System::Drawing::Point(734, 189);
			this->btnCargaDatos->Name = L"btnCargaDatos";
			this->btnCargaDatos->Size = System::Drawing::Size(110, 56);
			this->btnCargaDatos->TabIndex = 13;
			this->btnCargaDatos->Text = L"Carga de Datos";
			this->btnCargaDatos->UseVisualStyleBackColor = true;
			this->btnCargaDatos->Click += gcnew System::EventHandler(this, &CompraBoletos::btnCargaDatos_Click);
			// 
			// btnDescargaDatos
			// 
			this->btnDescargaDatos->Location = System::Drawing::Point(881, 189);
			this->btnDescargaDatos->Name = L"btnDescargaDatos";
			this->btnDescargaDatos->Size = System::Drawing::Size(110, 56);
			this->btnDescargaDatos->TabIndex = 14;
			this->btnDescargaDatos->Text = L"Descarga de Datos";
			this->btnDescargaDatos->UseVisualStyleBackColor = true;
			this->btnDescargaDatos->Click += gcnew System::EventHandler(this, &CompraBoletos::btnExportarCSV_Click);
			// 
			// CompraBoletos
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1684, 1031);
			this->Controls->Add(this->btnDescargaDatos);
			this->Controls->Add(this->btnCargaDatos);
			this->Controls->Add(this->btnHTML);
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
			this->Controls->Add(this->panelAsientos);
			this->Name = L"CompraBoletos";
			this->Text = L"CompraBoletos";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tblCompras))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void tblCompras_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
		if (e->RowIndex >= 0 && e->RowIndex < tblCompras->Rows->Count) {
			DataGridViewRow^ fila = tblCompras->Rows[e->RowIndex];

			if (!fila->IsNewRow) {
				compraSeleccionada = e->RowIndex;

				// Obtener el código de la compra seleccionada
				int codigoCompra = Convert::ToInt32(fila->Cells["colCodigo"]->Value);

				// Buscar la compra en el array de comprasBoletos
				ComprasBoletos^ compraSeleccionadaObj = nullptr;
				for (int i = 0; i < ultimoCodigo; i++) {
					if (comprasBoletos[i] != nullptr && comprasBoletos[i]->Codigo == codigoCompra) {
						compraSeleccionadaObj = comprasBoletos[i];
						break;
					}
				}

				if (compraSeleccionadaObj != nullptr) {
					for (int i = 0; i < cboFuncion->Items->Count; i++) {
						AsignacionPeliculaSala^ asignacion = dynamic_cast<AsignacionPeliculaSala^>(cboFuncion->Items[i]);
						if (asignacion != nullptr && asignacion == compraSeleccionadaObj->AsignacionCompra) {
							cboFuncion->SelectedIndex = i;
							break;
						}
					}

					// Seleccionar el cliente correspondiente en el ComboBox
					for (int i = 0; i < cboCliente->Items->Count; i++) {
						Cliente^ cliente = dynamic_cast<Cliente^>(cboCliente->Items[i]);
						if (cliente != nullptr && cliente == compraSeleccionadaObj->ClienteCompra) {
							cboCliente->SelectedIndex = i;
							break;
						}
					}

					// Establecer la fecha de compra
					dateFecha->Value = compraSeleccionadaObj->FechaCompra;
				}
			}
		}
	}
	private: System::Void btnAgregar_Click(System::Object^ sender, System::EventArgs^ e) {
		if (estadoActual == ModoFormulario::Ninguno) {
			estadoActual = ModoFormulario::Agregar;
			ActualizarEstadoFormulario();
			ResetearFormulario();
		}
		else if (estadoActual == ModoFormulario::Agregar) {
			// Validar campos obligatorios
			if (cboFuncion->SelectedIndex == -1 || cboCliente->SelectedIndex == -1 || dateFecha->Value == DateTime::MinValue) {
				MessageBox::Show("Por favor, complete todos los campos.");
				return;
			}

			// Validar que se haya seleccionado un asiento
			if (asientoFilaSeleccionado == -1 || asientoColumnaSeleccionado == -1) {
				MessageBox::Show("Por favor, seleccione un asiento.");
				return;
			}

			AsignacionPeliculaSala^ asignacionSeleccionada = dynamic_cast<AsignacionPeliculaSala^>(cboFuncion->SelectedItem);
			Cliente^ clienteSeleccionado = dynamic_cast<Cliente^>(cboCliente->SelectedItem);
			DateTime fechaCompra = dateFecha->Value;

			// Obtener el botón del asiento seleccionado
			int totalColumnas = 8;
			int controlIndex = asientoFilaSeleccionado * totalColumnas + asientoColumnaSeleccionado;

			if (controlIndex >= 0 && controlIndex < panelAsientos->Controls->Count) {
				Button^ btnAsientoSeleccionado = dynamic_cast<Button^>(panelAsientos->Controls[controlIndex]);

				if (btnAsientoSeleccionado != nullptr && btnAsientoSeleccionado->Enabled) {
					// Ocupar el asiento en la sala
					asignacionSeleccionada->SalaAsignada->OcuparAsiento(asientoFilaSeleccionado, asientoColumnaSeleccionado);

					// Actualizar visualmente el asiento
					btnAsientoSeleccionado->BackColor = Color::Red;
					btnAsientoSeleccionado->Enabled = false;

					// Agregar la compra
					AgregarCompraBoleto(asignacionSeleccionada, clienteSeleccionado, fechaCompra, asientoFilaSeleccionado, asientoColumnaSeleccionado);

					// Resetear el formulario
					estadoActual = ModoFormulario::Ninguno;
					ActualizarEstadoFormulario();
					ResetearFormulario();
					tblCompras->ClearSelection();

					// Resetear la selección de asientos
					asientoFilaSeleccionado = -1;
					asientoColumnaSeleccionado = -1;

					panelAsientos->Controls->Clear();
				}
				else {
					MessageBox::Show("El asiento seleccionado no está disponible.");
				}
			}
			else {
				MessageBox::Show("Asiento inválido seleccionado.");
			}
		}
	}
	private: System::Void cboFuncion_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (cboFuncion->SelectedIndex != -1) {
			// Obtener la asignación seleccionada
			AsignacionPeliculaSala^ asignacion = dynamic_cast<AsignacionPeliculaSala^>(cboFuncion->SelectedItem);

			if (asignacion != nullptr && asignacion->SalaAsignada != nullptr) {
				// Mostrar los asientos de la sala correspondiente
				MostrarAsientos(asignacion->SalaAsignada);
			}
		}
	}
	private: System::Void Asiento_Click(System::Object^ sender, System::EventArgs^ e) {
		Button^ btnAsiento = dynamic_cast<Button^>(sender);
		if (btnAsiento != nullptr) {
			// Resetear color del asiento previo (si hay uno seleccionado)
			if (asientoFilaSeleccionado != -1) {
				Button^ btnAnterior = dynamic_cast<Button^>(panelAsientos->Controls[
					asientoFilaSeleccionado * 8 + asientoColumnaSeleccionado
				]);
				if (btnAnterior != nullptr) {
					btnAnterior->BackColor = Color::Green;
				}
			}

			// Seleccionar nuevo asiento
			Tuple<int, int>^ posicion = dynamic_cast<Tuple<int, int>^>(btnAsiento->Tag);
			asientoFilaSeleccionado = posicion->Item1;
			asientoColumnaSeleccionado = posicion->Item2;

			btnAsiento->BackColor = Color::Blue; // Asiento seleccionado
		}
	}
	private: System::Void btnEliminar_Click(System::Object^ sender, System::EventArgs^ e) {
		if (estadoActual == ModoFormulario::Agregar) {
			estadoActual = ModoFormulario::Ninguno;
			ActualizarEstadoFormulario();
			ResetearFormulario();
			tblCompras->ClearSelection();
			compraSeleccionada = -1;
			panelAsientos->Controls->Clear();
			return;
		}

		if (compraSeleccionada >= 0 && compraSeleccionada < comprasBoletos->Length && comprasBoletos[compraSeleccionada] != nullptr) {
			System::Windows::Forms::DialogResult result = MessageBox::Show(
				"¿Estás seguro de eliminar esta compra?",
				"Confirmar eliminación",
				MessageBoxButtons::YesNo,
				MessageBoxIcon::Warning
			);

			if (result == System::Windows::Forms::DialogResult::Yes) {
				ComprasBoletos^ compraAEliminar = comprasBoletos[compraSeleccionada];

				// Liberar asiento
				if (compraAEliminar->AsignacionCompra != nullptr &&
					compraAEliminar->AsignacionCompra->SalaAsignada != nullptr) {
					compraAEliminar->AsignacionCompra->SalaAsignada->LiberarAsiento(
						compraAEliminar->FilaAsiento,
						compraAEliminar->ColumnaAsiento
					);
				}

				// Eliminar compra y compactar array
				comprasBoletos[compraSeleccionada] = nullptr;

				// Compactar el array eliminando nulls
				CompactarArrayCompras();

				// Actualizar último código
				ActualizarUltimoCodigo();

				MostrarComprasBoletos();

				// Actualizar visualización si es necesario
				if (cboFuncion->SelectedIndex != -1) {
					AsignacionPeliculaSala^ asignacion = dynamic_cast<AsignacionPeliculaSala^>(cboFuncion->SelectedItem);
					if (asignacion != nullptr) {
						MostrarAsientos(asignacion->SalaAsignada);
					}
				}
			}

			ResetearFormulario();
			tblCompras->ClearSelection();
			compraSeleccionada = -1;
			panelAsientos->Controls->Clear();
		}
		else {
			MessageBox::Show("Seleccione una compra para eliminar.");
		}
	}
	private: System::Void btnHTML_Click(System::Object^ sender, System::EventArgs^ e) {
		if (compraSeleccionada == -1) {
			MessageBox::Show("Por favor seleccione una compra para generar el reporte.",
				"Información", MessageBoxButtons::OK, MessageBoxIcon::Information);
			return;
		}

		GenerarReporteHTML();
	}

	private: System::Void btnCargaDatos_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
		openFileDialog->Filter = "Archivos CSV (*.csv)|*.csv";
		openFileDialog->Title = "Seleccionar archivo CSV de compras";

		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ filePath = openFileDialog->FileName;
			try {
				StreamReader^ sr = gcnew StreamReader(filePath, Encoding::UTF8);
				String^ line;
				bool isFirstLine = true;
				int lineNumber = 0;
				int comprasCargadas = 0;

				while ((line = sr->ReadLine()) != nullptr) {
					lineNumber++;
					if (isFirstLine) {
						isFirstLine = false;
						continue;
					}

					array<String^>^ campos = line->Split(';');

					// Validación básica de campos (AsignaciónID;ClienteID;Fecha;Fila;Columna)
					if (campos->Length < 5) {
						MessageBox::Show(String::Format("Línea {0}: Formato incorrecto. Se esperaban 5 campos, se encontraron {1}",
							lineNumber, campos->Length),
							"Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Warning);
						continue;
					}

					try {
						// Buscar asignación por ID
						int asignacionId = Convert::ToInt32(campos[0]->Trim());
						AsignacionPeliculaSala^ asignacion = nullptr;
						for each(AsignacionPeliculaSala ^ a in listaAsignaciones) {
							if (a != nullptr && a->Codigo == asignacionId) {
								asignacion = a;
								break;
							}
						}

						if (asignacion == nullptr) {
							MessageBox::Show(String::Format("Línea {0}: Asignación con ID {1} no encontrada", lineNumber, asignacionId),
								"Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Warning);
							continue;
						}

						// Buscar cliente por ID
						int clienteId = Convert::ToInt32(campos[1]->Trim());
						Cliente^ cliente = nullptr;
						for each(Cliente ^ c in listaClientes) {
							if (c != nullptr && c->Codigo == clienteId) {
								cliente = c;
								break;
							}
						}

						if (cliente == nullptr) {
							MessageBox::Show(String::Format("Línea {0}: Cliente con ID {1} no encontrado", lineNumber, clienteId),
								"Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Warning);
							continue;
						}

						// Procesar fecha
						DateTime fechaCompra;
						if (!DateTime::TryParse(campos[2]->Trim(), fechaCompra)) {
							MessageBox::Show(String::Format("Línea {0}: Formato de fecha inválido", lineNumber),
								"Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Warning);
							continue;
						}

						// Procesar asiento
						int fila = Convert::ToInt32(campos[3]->Trim());
						int columna = Convert::ToInt32(campos[4]->Trim());

						// Validar disponibilidad de asiento (opcional)
						if (!asignacion->SalaAsignada->Asientos[fila][columna]) {
							MessageBox::Show(String::Format("Línea {0}: Asiento [{1},{2}] ya está ocupado", lineNumber, fila, columna),
								"Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Warning);
							continue;
						}

						// Crear la compra y ocupar el asiento
						AgregarCompraBoletoCargaData(asignacion, cliente, fechaCompra, fila, columna);
						asignacion->SalaAsignada->OcuparAsiento(fila, columna);
						comprasCargadas++;
						MostrarComprasBoletos();
					}
					catch (Exception^ ex) {
						MessageBox::Show(String::Format("Error en línea {0}: {1}", lineNumber, ex->Message),
							"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}
				sr->Close();
				MessageBox::Show(String::Format("Se cargaron {0} compras exitosamente.", comprasCargadas),
					"Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				MostrarComprasBoletos();
			}
			catch (Exception^ ex) {
				MessageBox::Show("Error al cargar el archivo: " + ex->Message,
					"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			MostrarComprasBoletos();
		}
		MostrarComprasBoletos();
	};
	/*private: System::Void btnExportarCSV_Click(System::Object^ sender, System::EventArgs^ e) {
		SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
		saveFileDialog->Filter = "Archivos CSV (*.csv)|*.csv";
		saveFileDialog->Title = "Exportar compras a CSV";
		saveFileDialog->FileName = "ComprasBoletos_" + DateTime::Now.ToString("yyyyMMdd") + ".csv";

		if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ filePath = saveFileDialog->FileName;
			try {
				StreamWriter^ sw = gcnew StreamWriter(filePath, false, Encoding::UTF8);

				// Escribir encabezados
				sw->WriteLine("AsignacionID;ClienteID;FechaCompra;FilaAsiento;ColumnaAsiento");

				// Escribir datos
				for each(ComprasBoletos ^ compra in comprasBoletos) {
					if (compra != nullptr) {
						String^ linea = String::Format("{0};{1};{2};{3};{4}",
							compra->AsignacionCompra->Codigo,
							compra->ClienteCompra->Codigo,
							compra->FechaCompra.ToString("dd/MM/yyyy"),
							compra->FilaAsiento,
							compra->ColumnaAsiento);

						sw->WriteLine(linea);
					}
				}

				sw->Close();
				MessageBox::Show("Compras exportadas exitosamente a: " + filePath,
					"Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (Exception^ ex) {
				MessageBox::Show("Error al exportar: " + ex->Message,
					"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}*/

	private: System::Void btnExportarCSV_Click(System::Object^ sender, System::EventArgs^ e) {
		// Validar si hay datos para exportar
		bool tieneDatos = false;
		for each (ComprasBoletos ^ compra in comprasBoletos) {
			if (compra != nullptr) {
				tieneDatos = true;
				break;
			}
		}

		if (!tieneDatos) {
			MessageBox::Show("No hay datos de compras para exportar.",
				"Advertencia",
				MessageBoxButtons::OK,
				MessageBoxIcon::Warning);
			return;
		}

		SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
		saveFileDialog->Filter = "Archivos CSV (*.csv)|*.csv";
		saveFileDialog->Title = "Exportar compras a CSV";
		saveFileDialog->FileName = "ComprasBoletos_" + DateTime::Now.ToString("yyyyMMdd") + ".csv";

		if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ filePath = saveFileDialog->FileName;
			try {
				StreamWriter^ sw = gcnew StreamWriter(filePath, false, Encoding::UTF8);

				// Escribir encabezados
				sw->WriteLine("AsignacionID;ClienteID;FechaCompra;FilaAsiento;ColumnaAsiento");

				// Escribir datos
				for each (ComprasBoletos ^ compra in comprasBoletos) {
					if (compra != nullptr) {
						String^ linea = String::Format("{0};{1};{2};{3};{4};{5};{6}",
							compra->AsignacionCompra->Codigo,
							compra->AsignacionCompra->PeliculaAsignada->Nombre,
							compra->ClienteCompra->Codigo,
							compra->ClienteCompra->Nombre,
							compra->FechaCompra.ToString("dd/MM/yyyy"),
							compra->FilaAsiento,
							compra->ColumnaAsiento);

						sw->WriteLine(linea);
					}
				}

				sw->Close();
				MessageBox::Show("Compras exportadas exitosamente a: " + filePath,
					"Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (Exception^ ex) {
				MessageBox::Show("Error al exportar: " + ex->Message,
					"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}
	};
}