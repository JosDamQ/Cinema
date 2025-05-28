#pragma once
#include "ClaseSalas.h"
#include "GeneradorReporte.h"
// Coloca estos includes al inicio
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

	public ref class Salas : public System::Windows::Forms::Form
	{
	private:
		array<Sala^>^ salas;
		int ultimoCodigo;
		int salaSeleccionada;
	private: System::Windows::Forms::Button^ btnHTML;
	private: System::Windows::Forms::Button^ btnCargaDatos;

		enum class ModoFormulario
		{
			Ninguno,
			Agregar,
			Editar
		};

		ModoFormulario estadoActual = ModoFormulario::Ninguno;

	public:
		Salas(void)
		{
			InitializeComponent();
			CargarCapacidades();
			salas = gcnew array<Sala^>(50);
			ultimoCodigo = 0;
			salaSeleccionada = -1;

			ActualizarEstadoFormulario();
			ResetearFormulario();
		}

		void AgregarSala
		(
			String^ nombre,
			CapacidadSala capacidad,
			String^ ubicacion,
			String^ encargado,
			String^ telefonoEncargado
		)
		{
			ultimoCodigo++;
			Sala^ nuevaSala = gcnew Sala(ultimoCodigo, nombre, capacidad, ubicacion, encargado, telefonoEncargado);
			//MessageBox::Show(nuevaSala->ObtenerInfoMatrizAsientos(), "Tamaño de la Matriz");
			salas[ultimoCodigo - 1] = nuevaSala;
			MostrarSalas();
		}

		void MostrarSalas()
		{
			tblSalas->Rows->Clear();
			for (int i = 0; i < ultimoCodigo; i++) {
				if (salas[i] != nullptr) {
					tblSalas->Rows->Add(
						salas[i]->Codigo,
						salas[i]->Nombre,
						salas[i]->Capacidad.ToString(),
						salas[i]->Ubicacion,
						salas[i]->Encargado,
						salas[i]->TelefonoEncargado
					);
				}
			}
		}

		void ResetearFormulario()
		{
			txtName->Clear();
			cboCapacidad->SelectedIndex = -1;
			txtUbicacion->Clear();
			txtEncargado->Clear();
			txtTelefonoEncargado->Clear();
		}

		void ActualizarEstadoFormulario() {
			bool habilitar = estadoActual != ModoFormulario::Ninguno;

			txtName->Enabled = habilitar;
			cboCapacidad->Enabled = habilitar;
			txtUbicacion->Enabled = habilitar;
			txtEncargado->Enabled = habilitar;
			txtTelefonoEncargado->Enabled = habilitar;

			if (estadoActual == ModoFormulario::Agregar) {
				btnAgregar->Text = "Confirmar";
				btnEliminar->Text = "Cancelar";
				btnEditar->Enabled = false;
				btnHTML->Enabled = false;
				btnCargaDatos->Enabled = false;
			}
			else if (estadoActual == ModoFormulario::Editar) {
				btnEditar->Text = "Confirmar";
				btnEliminar->Text = "Cancelar";
				btnAgregar->Enabled = false;
				btnHTML->Enabled = false;
				btnCargaDatos->Enabled = false;
			}
			else {
				btnAgregar->Text = "Agregar";
				btnEliminar->Text = "Eliminar";
				btnEditar->Text = "Editar";
				btnAgregar->Enabled = true;
				btnEliminar->Enabled = true;
				btnEditar->Enabled = true;
				btnHTML->Enabled = true;
				btnCargaDatos->Enabled = true;
			}
		}

		//cargar combobox
		array<Sala^>^ ObtenerSalasExistentes()
		{
			return salas;
		}
		private:
			void GenerarReporteHTML()
			{
				if (tblSalas->Rows->Count == 0) {
					MessageBox::Show("No hay salas para generar el reporte.",
						"Información", MessageBoxButtons::OK, MessageBoxIcon::Information);
					return;
				}

				// Preparar los datos para el reporte
				array<String^>^ encabezados = gcnew array<String^> {
					"Código", "Nombre", "Capacidad", "Ubicación", "Encargado", "Teléfono Encargado"
				};

				// Crear lista de datos basada en el DataGridView
				System::Collections::Generic::List<array<String^>^>^ datosLista = gcnew System::Collections::Generic::List<array<String^>^>();

				for each (DataGridViewRow ^ fila in tblSalas->Rows)
				{
					if (!fila->IsNewRow)
					{
						array<String^>^ filaDatos = gcnew array<String^> {
							fila->Cells["colCodigo"]->Value == nullptr ? "" : fila->Cells["colCodigo"]->Value->ToString(),
								fila->Cells["colNombre"]->Value == nullptr ? "" : fila->Cells["colNombre"]->Value->ToString(),
								fila->Cells["colCapacidad"]->Value == nullptr ? "" : fila->Cells["colCapacidad"]->Value->ToString(),
								fila->Cells["colUbicacion"]->Value == nullptr ? "" : fila->Cells["colUbicacion"]->Value->ToString(),
								fila->Cells["colEncargado"]->Value == nullptr ? "" : fila->Cells["colEncargado"]->Value->ToString(),
								fila->Cells["colTelefonoEncargado"]->Value == nullptr ? "" : fila->Cells["colTelefonoEncargado"]->Value->ToString()
						};
						datosLista->Add(filaDatos);
					}
				}

				// Convertir la lista a array para el reporte
				array<array<String^>^>^ datos = datosLista->ToArray();

				// Generar el reporte usando la clase general
				GeneradorReporte::GenerarReporte(
					"Reporte de Salas",
					"Listado de Salas Registradas",
					"Sistema de Gestión de Salas - ProyectMovies",
					encabezados,
					datos,
					"ReporteSalas");
			}
		

	protected:
		~Salas()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lblNombre;
	private: System::Windows::Forms::TextBox^ txtName;
	private: System::Windows::Forms::Label^ lblCapacidad;
	private: System::Windows::Forms::ComboBox^ cboCapacidad;
	private: System::Windows::Forms::Label^ lblUbicacion;
	private: System::Windows::Forms::TextBox^ txtUbicacion;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ txtEncargado;
	private: System::Windows::Forms::Label^ lblTelefonoEncargado;
	private: System::Windows::Forms::TextBox^ txtTelefonoEncargado;
	private: System::Windows::Forms::DataGridView^ tblSalas;

	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colCodigo;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colNombre;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colCapacidad;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colUbicacion;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colEncargado;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colTelefonoEncargado;
	private: System::Windows::Forms::Button^ btnAgregar;
	private: System::Windows::Forms::Button^ btnEliminar;
	private: System::Windows::Forms::Button^ btnEditar;



	protected:

	private:
		System::ComponentModel::Container ^components;
		//System::Collections::Generic::Dictionary<String^, CapacidadSala>^ capacidadesMap;


#pragma region Windows Form Designer generated code
		void CargarCapacidades()
		{
			this->cboCapacidad->Items->Add(CapacidadSala::Capacidad_40.ToString());
			this->cboCapacidad->Items->Add(CapacidadSala::Capacidad_56.ToString());
			//capacidadesMap = gcnew System::Collections::Generic::Dictionary<String^, CapacidadSala>();

			//capacidadesMap->Add("40", CapacidadSala::Capacidad_40);
			//capacidadesMap->Add("56", CapacidadSala::Capacidad_56);

			//for each (String ^ clave in capacidadesMap->Keys) {
			//	this->cboCapacidad->Items->Add(clave); // Solo muestra "40" y "56"
			//}
		}

		void InitializeComponent(void)
		{
			this->lblNombre = (gcnew System::Windows::Forms::Label());
			this->txtName = (gcnew System::Windows::Forms::TextBox());
			this->lblCapacidad = (gcnew System::Windows::Forms::Label());
			this->cboCapacidad = (gcnew System::Windows::Forms::ComboBox());
			this->lblUbicacion = (gcnew System::Windows::Forms::Label());
			this->txtUbicacion = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtEncargado = (gcnew System::Windows::Forms::TextBox());
			this->lblTelefonoEncargado = (gcnew System::Windows::Forms::Label());
			this->txtTelefonoEncargado = (gcnew System::Windows::Forms::TextBox());
			this->tblSalas = (gcnew System::Windows::Forms::DataGridView());
			this->colCodigo = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colNombre = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colCapacidad = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colUbicacion = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colEncargado = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colTelefonoEncargado = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->btnAgregar = (gcnew System::Windows::Forms::Button());
			this->btnEliminar = (gcnew System::Windows::Forms::Button());
			this->btnEditar = (gcnew System::Windows::Forms::Button());
			this->btnHTML = (gcnew System::Windows::Forms::Button());
			this->btnCargaDatos = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tblSalas))->BeginInit();
			this->SuspendLayout();
			// 
			// lblNombre
			// 
			this->lblNombre->AutoSize = true;
			this->lblNombre->Location = System::Drawing::Point(61, 42);
			this->lblNombre->Name = L"lblNombre";
			this->lblNombre->Size = System::Drawing::Size(65, 20);
			this->lblNombre->TabIndex = 0;
			this->lblNombre->Text = L"Nombre";
			// 
			// txtName
			// 
			this->txtName->Location = System::Drawing::Point(132, 39);
			this->txtName->Name = L"txtName";
			this->txtName->Size = System::Drawing::Size(100, 26);
			this->txtName->TabIndex = 1;
			// 
			// lblCapacidad
			// 
			this->lblCapacidad->AutoSize = true;
			this->lblCapacidad->Location = System::Drawing::Point(285, 42);
			this->lblCapacidad->Name = L"lblCapacidad";
			this->lblCapacidad->Size = System::Drawing::Size(85, 20);
			this->lblCapacidad->TabIndex = 2;
			this->lblCapacidad->Text = L"Capacidad";
			// 
			// cboCapacidad
			// 
			this->cboCapacidad->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cboCapacidad->FormattingEnabled = true;
			this->cboCapacidad->Location = System::Drawing::Point(376, 37);
			this->cboCapacidad->Name = L"cboCapacidad";
			this->cboCapacidad->Size = System::Drawing::Size(121, 28);
			this->cboCapacidad->TabIndex = 3;
			// 
			// lblUbicacion
			// 
			this->lblUbicacion->AutoSize = true;
			this->lblUbicacion->Location = System::Drawing::Point(553, 42);
			this->lblUbicacion->Name = L"lblUbicacion";
			this->lblUbicacion->Size = System::Drawing::Size(79, 20);
			this->lblUbicacion->TabIndex = 4;
			this->lblUbicacion->Text = L"Ubicacion";
			// 
			// txtUbicacion
			// 
			this->txtUbicacion->Location = System::Drawing::Point(638, 37);
			this->txtUbicacion->Name = L"txtUbicacion";
			this->txtUbicacion->Size = System::Drawing::Size(100, 26);
			this->txtUbicacion->TabIndex = 5;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(145, 105);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(87, 20);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Encargado";
			// 
			// txtEncargado
			// 
			this->txtEncargado->Location = System::Drawing::Point(250, 102);
			this->txtEncargado->Name = L"txtEncargado";
			this->txtEncargado->Size = System::Drawing::Size(100, 26);
			this->txtEncargado->TabIndex = 7;
			// 
			// lblTelefonoEncargado
			// 
			this->lblTelefonoEncargado->AutoSize = true;
			this->lblTelefonoEncargado->Location = System::Drawing::Point(463, 105);
			this->lblTelefonoEncargado->Name = L"lblTelefonoEncargado";
			this->lblTelefonoEncargado->Size = System::Drawing::Size(153, 20);
			this->lblTelefonoEncargado->TabIndex = 8;
			this->lblTelefonoEncargado->Text = L"Telefono Encargado";
			// 
			// txtTelefonoEncargado
			// 
			this->txtTelefonoEncargado->Location = System::Drawing::Point(622, 102);
			this->txtTelefonoEncargado->Name = L"txtTelefonoEncargado";
			this->txtTelefonoEncargado->Size = System::Drawing::Size(100, 26);
			this->txtTelefonoEncargado->TabIndex = 9;
			// 
			// tblSalas
			// 
			this->tblSalas->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->tblSalas->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {
				this->colCodigo, this->colNombre,
					this->colCapacidad, this->colUbicacion, this->colEncargado, this->colTelefonoEncargado
			});
			this->tblSalas->Location = System::Drawing::Point(50, 251);
			this->tblSalas->Name = L"tblSalas";
			this->tblSalas->RowTemplate->Height = 28;
			this->tblSalas->Size = System::Drawing::Size(893, 280);
			this->tblSalas->TabIndex = 10;
			this->tblSalas->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Salas::tblSalas_CellClick);
			// 
			// colCodigo
			// 
			this->colCodigo->HeaderText = L"Codigo";
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
			this->colUbicacion->HeaderText = L"Ubicacion";
			this->colUbicacion->Name = L"colUbicacion";
			// 
			// colEncargado
			// 
			this->colEncargado->HeaderText = L"Encargado";
			this->colEncargado->Name = L"colEncargado";
			// 
			// colTelefonoEncargado
			// 
			this->colTelefonoEncargado->HeaderText = L"Telefono Encargado";
			this->colTelefonoEncargado->Name = L"colTelefonoEncargado";
			// 
			// btnAgregar
			// 
			this->btnAgregar->Location = System::Drawing::Point(250, 185);
			this->btnAgregar->Name = L"btnAgregar";
			this->btnAgregar->Size = System::Drawing::Size(84, 35);
			this->btnAgregar->TabIndex = 11;
			this->btnAgregar->Text = L"Agregar";
			this->btnAgregar->UseVisualStyleBackColor = true;
			this->btnAgregar->Click += gcnew System::EventHandler(this, &Salas::btnAgregar_Click);
			// 
			// btnEliminar
			// 
			this->btnEliminar->Location = System::Drawing::Point(365, 185);
			this->btnEliminar->Name = L"btnEliminar";
			this->btnEliminar->Size = System::Drawing::Size(84, 35);
			this->btnEliminar->TabIndex = 12;
			this->btnEliminar->Text = L"Eliminar";
			this->btnEliminar->UseVisualStyleBackColor = true;
			this->btnEliminar->Click += gcnew System::EventHandler(this, &Salas::btnEliminar_Click);
			// 
			// btnEditar
			// 
			this->btnEditar->Location = System::Drawing::Point(477, 185);
			this->btnEditar->Name = L"btnEditar";
			this->btnEditar->Size = System::Drawing::Size(84, 35);
			this->btnEditar->TabIndex = 13;
			this->btnEditar->Text = L"Editar";
			this->btnEditar->UseVisualStyleBackColor = true;
			this->btnEditar->Click += gcnew System::EventHandler(this, &Salas::btnEditar_Click);
			// 
			// btnHTML
			// 
			this->btnHTML->Location = System::Drawing::Point(592, 185);
			this->btnHTML->Name = L"btnHTML";
			this->btnHTML->Size = System::Drawing::Size(84, 35);
			this->btnHTML->TabIndex = 14;
			this->btnHTML->Text = L"HTML";
			this->btnHTML->UseVisualStyleBackColor = true;
			this->btnHTML->Click += gcnew System::EventHandler(this, &Salas::btnHTML_Click);;
			// 
			// btnCargaDatos
			// 
			this->btnCargaDatos->Location = System::Drawing::Point(702, 172);
			this->btnCargaDatos->Name = L"btnCargaDatos";
			this->btnCargaDatos->Size = System::Drawing::Size(94, 60);
			this->btnCargaDatos->TabIndex = 15;
			this->btnCargaDatos->Text = L"Carga de datos";
			this->btnCargaDatos->UseVisualStyleBackColor = true;
			this->btnCargaDatos->Click += gcnew System::EventHandler(this, &Salas::btnCargaDatos_Click);
			// 
			// Salas
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1179, 681);
			this->Controls->Add(this->btnCargaDatos);
			this->Controls->Add(this->btnHTML);
			this->Controls->Add(this->btnEditar);
			this->Controls->Add(this->btnEliminar);
			this->Controls->Add(this->btnAgregar);
			this->Controls->Add(this->tblSalas);
			this->Controls->Add(this->txtTelefonoEncargado);
			this->Controls->Add(this->lblTelefonoEncargado);
			this->Controls->Add(this->txtEncargado);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->txtUbicacion);
			this->Controls->Add(this->lblUbicacion);
			this->Controls->Add(this->cboCapacidad);
			this->Controls->Add(this->lblCapacidad);
			this->Controls->Add(this->txtName);
			this->Controls->Add(this->lblNombre);
			this->Name = L"Salas";
			this->Text = L"Salas";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tblSalas))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: System::Void tblSalas_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
			if (e->RowIndex >= 0 && e->RowIndex < tblSalas->Rows->Count) {
				DataGridViewRow^ fila = tblSalas->Rows[e->RowIndex];

				if (!fila->IsNewRow) {
					salaSeleccionada = e->RowIndex;
					txtName->Text = fila->Cells["colNombre"]->Value->ToString();
					cboCapacidad->SelectedItem = fila->Cells["colCapacidad"]->Value;
					txtUbicacion->Text = fila->Cells["colUbicacion"]->Value->ToString();
					txtEncargado->Text = fila->Cells["colEncargado"]->Value->ToString();
					txtTelefonoEncargado->Text = fila->Cells["colTelefonoEncargado"]->Value->ToString();
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
				if (txtName->Text->Trim() == "" ||
					cboCapacidad->SelectedIndex == -1 ||
					txtUbicacion->Text->Trim() == "" ||
					txtEncargado->Text->Trim() == "" ||
					txtTelefonoEncargado->Text->Trim() == "") {

					MessageBox::Show("Por favor complete todos los campos antes de agregar la sala.", "Campos incompletos", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					return;
				}

				String^ nombre = txtName->Text;
				CapacidadSala capacidad = (CapacidadSala)Enum::Parse(CapacidadSala::typeid, cboCapacidad->SelectedItem->ToString());
				//String^ claveSeleccionada = cboCapacidad->SelectedItem->ToString();
				//CapacidadSala capacidad = capacidadesMap[claveSeleccionada];
				String^ ubicacion = txtUbicacion->Text;
				String^ encargado = txtEncargado->Text;
				String^ telefonoEncargado = txtTelefonoEncargado->Text;

				AgregarSala(nombre, capacidad, ubicacion, encargado, telefonoEncargado);

				estadoActual = ModoFormulario::Ninguno;
				ActualizarEstadoFormulario();
				ResetearFormulario();
				tblSalas->ClearSelection();
			}
		}

		private: System::Void btnEliminar_Click(System::Object^ sender, System::EventArgs^ e) {
			if (estadoActual == ModoFormulario::Agregar) {
				estadoActual = ModoFormulario::Ninguno;
				ActualizarEstadoFormulario();
				ResetearFormulario();
				tblSalas->ClearSelection();
				salaSeleccionada = -1; // Resetear la selección
				return;
			}

			if (estadoActual == ModoFormulario::Editar) {
				estadoActual = ModoFormulario::Ninguno;
				ActualizarEstadoFormulario();
				ResetearFormulario();
				tblSalas->ClearSelection();
				salaSeleccionada = -1; // Resetear la selección
				return;
			}

			if (salaSeleccionada >= 0 && salaSeleccionada < ultimoCodigo) {
				System::Windows::Forms::DialogResult result = System::Windows::Forms::MessageBox::Show(
					"¿Estás seguro de que deseas eliminar este usuario?",
					"Confirmar eliminación",
					System::Windows::Forms::MessageBoxButtons::YesNo,
					System::Windows::Forms::MessageBoxIcon::Warning
				);

				if (result == System::Windows::Forms::DialogResult::Yes) {
					salas[salaSeleccionada] = nullptr;
					MostrarSalas();
				}
				ResetearFormulario();
				tblSalas->ClearSelection();

				salaSeleccionada = -1; // Resetear la selección
			}
			else {
				System::Windows::Forms::MessageBox::Show("Seleccione una sala para eliminar.");
			}
		}

		private: System::Void btnEditar_Click(System::Object^ sender, System::EventArgs^ e) {
			if (estadoActual == ModoFormulario::Ninguno) {
				if (salaSeleccionada < 0 || salaSeleccionada >= ultimoCodigo || salas[salaSeleccionada] == nullptr) {
					MessageBox::Show("Seleccione una sala para editar.");
					return;
				}

				estadoActual = ModoFormulario::Editar;
				ActualizarEstadoFormulario();
			}
			else if (estadoActual == ModoFormulario::Editar) {
				if (txtName->Text->Trim() == "" ||
					cboCapacidad->SelectedIndex == -1 ||
					txtUbicacion->Text->Trim() == "" ||
					txtEncargado->Text->Trim() == "" ||
					txtTelefonoEncargado->Text->Trim() == "") {

					MessageBox::Show("Por favor complete todos los campos antes de editar la sala.", "Campos incompletos", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					return;
				}

				String^ nombre = txtName->Text;
				CapacidadSala capacidad = (CapacidadSala)Enum::Parse(CapacidadSala::typeid, cboCapacidad->SelectedItem->ToString());
				//String^ claveSeleccionada = cboCapacidad->SelectedItem->ToString();
				//CapacidadSala capacidad = capacidadesMap[claveSeleccionada];
				String^ ubicacion = txtUbicacion->Text;
				String^ encargado = txtEncargado->Text;
				String^ telefonoEncargado = txtTelefonoEncargado->Text;

				salas[salaSeleccionada]->Nombre = nombre;
				salas[salaSeleccionada]->Capacidad = capacidad;
				salas[salaSeleccionada]->Ubicacion = ubicacion;
				salas[salaSeleccionada]->Encargado = encargado;
				salas[salaSeleccionada]->TelefonoEncargado = telefonoEncargado;

				MostrarSalas();

				estadoActual = ModoFormulario::Ninguno;
				ActualizarEstadoFormulario();
				ResetearFormulario();
				tblSalas->ClearSelection();
				salaSeleccionada = -1; // Resetear la selección
			}
		}
	private: System::Void btnHTML_Click(System::Object^ sender, System::EventArgs^ e) {
		if (ultimoCodigo == 0) {
			MessageBox::Show("No hay salas para generar el reporte.",
				"Información", MessageBoxButtons::OK, MessageBoxIcon::Information);
			return;
		}

		GenerarReporteHTML();
	}

	private: System::Void btnCargaDatos_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
		openFileDialog->Filter = "Archivos CSV (*.csv)|*.csv";
		openFileDialog->Title = "Seleccionar archivo CSV de salas";

		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ filePath = openFileDialog->FileName;
			try {
				StreamReader^ sr = gcnew StreamReader(filePath, Encoding::UTF8);
				String^ line;
				bool isFirstLine = true;
				int lineNumber = 0;
				int salasCargadas = 0;

				while ((line = sr->ReadLine()) != nullptr) {
					lineNumber++;
					if (isFirstLine) {
						isFirstLine = false;
						continue;
					}

					array<String^>^ campos = line->Split(';');

					// Validación básica de campos
					if (campos->Length < 5) {
						MessageBox::Show(String::Format("Línea {0}: Formato incorrecto. Se esperaban al menos 5 campos, se encontraron {1}",
							lineNumber, campos->Length),
							"Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Warning);
						continue;
					}

					try {
						// Procesar campos básicos
						String^ nombre = campos[0]->Trim();
						String^ ubicacion = campos[2]->Trim();
						String^ encargado = campos[3]->Trim();
						String^ telefonoEncargado = campos[4]->Trim();

						// Procesar capacidad con manejo de errores
						CapacidadSala capacidad;
						if (!Enum::TryParse<CapacidadSala>("Capacidad_" + campos[1]->Trim(), true, capacidad)) {
							MessageBox::Show(String::Format("Línea {0}: Capacidad '{1}' no válida. Se usará 'Capacidad_40' por defecto",
								lineNumber, campos[1]),
								"Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Warning);
							capacidad = CapacidadSala::Capacidad_40;
						}

						// Agregar sala
						AgregarSala(nombre, capacidad, ubicacion, encargado, telefonoEncargado);
						salasCargadas++;
					}
					catch (Exception^ ex) {
						MessageBox::Show(String::Format("Error en línea {0}: {1}", lineNumber, ex->Message),
							"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}
				sr->Close();
				MessageBox::Show(String::Format("Se cargaron {0} salas exitosamente.", salasCargadas),
					"Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				MostrarSalas();
			}
			catch (Exception^ ex) {
				MessageBox::Show("Error al cargar el archivo: " + ex->Message,
					"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}

	};
}
