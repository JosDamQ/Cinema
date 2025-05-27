#pragma once
#include "ClaseClientes.h"
#include "GeneradorReporte.h"
// Coloca estos includes al inicio
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <fstream>


// Evita conflictos con ServiceProvider de Windows
#undef ServiceProvider

namespace ProyectMovies {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Text;

	public ref class Clientes : public System::Windows::Forms::Form
	{
	private:
		// para traer a los externos
		//array<User^>^ listaUsuarios;
		array <Cliente^>^ clientes;
		int ultimoCodigo;
		int clienteSeleccionado;
	private: System::Windows::Forms::Button^ btnHTML;
	private: System::Windows::Forms::Button^ btnCargaDatos;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colCodigo;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colNombre;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colApellido;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colCUI;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colFechaNacimiento;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colTelefono;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colEmail;

		   enum class ModoFormulario {
			   Ninguno,
			   Agregar,
			   Editar
		   };

		   ModoFormulario estadoActual = ModoFormulario::Ninguno;
	private:
		void GenerarReporteHTML()
		{
			if (tblClientes->Rows->Count == 0) {
				MessageBox::Show("No hay clientes para generar el reporte.",
					"Información", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return;
			}

			// Preparar los datos para el reporte
			array<String^>^ encabezados = gcnew array<String^> {
				"Código", "Nombre", "Apellido", "DPI", "Fecha Nacimiento", "Teléfono", "Email"
			};

			// Crear lista de datos basada en el DataGridView
			System::Collections::Generic::List<array<String^>^>^ datosLista = gcnew System::Collections::Generic::List<array<String^>^>();

			for each (DataGridViewRow ^ fila in tblClientes->Rows)
			{
				if (!fila->IsNewRow)
				{
					array<String^>^ filaDatos = gcnew array<String^> {
						fila->Cells["colCodigo"]->Value == nullptr ? "" : fila->Cells["colCodigo"]->Value->ToString(),
							fila->Cells["colNombre"]->Value == nullptr ? "" : fila->Cells["colNombre"]->Value->ToString(),
							fila->Cells["colApellido"]->Value == nullptr ? "" : fila->Cells["colApellido"]->Value->ToString(),
							fila->Cells["colCUI"]->Value == nullptr ? "" : fila->Cells["colCUI"]->Value->ToString(),
							fila->Cells["colFechaNacimiento"]->Value == nullptr ? "" : fila->Cells["colFechaNacimiento"]->Value->ToString(),
							fila->Cells["colTelefono"]->Value == nullptr ? "" : fila->Cells["colTelefono"]->Value->ToString(),
							fila->Cells["colEmail"]->Value == nullptr ? "" : fila->Cells["colEmail"]->Value->ToString()
					};
					datosLista->Add(filaDatos);
				}
			}

			// Convertir la lista a array para el reporte
			array<array<String^>^>^ datos = datosLista->ToArray();

			// Generar el reporte usando la clase general
			GeneradorReporte::GenerarReporte(
				"Reporte de Clientes",
				"Listado de Clientes Registrados",
				"Sistema de Gestión de Clientes - ProyectMovies",
				encabezados,
				datos,
				"ReporteClientes");
		}

	public:
		Clientes(void)
		{
			InitializeComponent();
			clientes = gcnew array<Cliente^>(50);
			ultimoCodigo = 0;
			clienteSeleccionado = -1;

			ActualizarEstadoFormulario();
			ResetearFormulario();
		}

		//Funcion de agregar
		void AgregarCliente
		(
			String^ nombre,
			String^ apellido,
			String^ dpi,
			DateTime^ fechaNacimiento,
			String^ telefono,
			String^ email
		)
		{
			ultimoCodigo++;
			Cliente^ nuevoCliente = gcnew Cliente(ultimoCodigo, nombre, apellido, dpi, fechaNacimiento, telefono, email);
			clientes[ultimoCodigo - 1] = nuevoCliente;
			MostrarClientes();
		}

		// Funcion de mostrar
		void MostrarClientes()
		{
			tblClientes->Rows->Clear();
			for (int i = 0; i < ultimoCodigo; i++) {
				if (clientes[i] != nullptr) {
					tblClientes->Rows->Add(
						clientes[i]->Codigo,
						clientes[i]->Nombre,
						clientes[i]->Apellido,
						clientes[i]->DPI,
						clientes[i]->FechaNacimiento/*->ToString("dd/MM/yyyy")*/,
						clientes[i]->Telefono,
						clientes[i]->Email
					);
				}
			}
		}

		//Resetear el formulario
		void ResetearFormulario()
		{
			txtNombre->Clear();
			txtApellido->Clear();
			txtCUI->Clear();
			dateFechaNacimiento->ResetText();
			txtTelefono->Clear();
			txtEmail->Clear();
		}

		//Estado formulario
		void ActualizarEstadoFormulario()
		{
			bool habilitar = estadoActual != ModoFormulario::Ninguno;

			txtNombre->Enabled = habilitar;
			txtApellido->Enabled = habilitar;
			txtCUI->Enabled = habilitar;
			dateFechaNacimiento->Enabled = habilitar;
			txtTelefono->Enabled = habilitar;
			txtEmail->Enabled = habilitar;

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

		// Cargar comboBox
		array<Cliente^>^ ObtenerClientesExistentes()
		{
			return clientes;
		}

	protected:
		~Clientes()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lblNombre;
	private: System::Windows::Forms::TextBox^ txtNombre;
	private: System::Windows::Forms::Label^ lblApellido;
	private: System::Windows::Forms::TextBox^ txtApellido;
	private: System::Windows::Forms::Label^ lblCUI;
	private: System::Windows::Forms::TextBox^ txtCUI;
	private: System::Windows::Forms::DateTimePicker^ dateFechaNacimiento;
	private: System::Windows::Forms::Label^ txtFechaNacimiento;
	private: System::Windows::Forms::Label^ lblTelefono;
	private: System::Windows::Forms::TextBox^ txtTelefono;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ txtEmail;


	private: System::Windows::Forms::DataGridView^ tblClientes;









	private: System::Windows::Forms::Button^ btnAgregar;
	private: System::Windows::Forms::Button^ btnEliminar;
	private: System::Windows::Forms::Button^ btnEditar;


	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		// Para comboBox externo
		/*void CargarUsuariosComboBox() {
			cboUsuarios->Items->Clear();
			cboUsuarios->DisplayMember = "Username";

			for (int i = 0; i < listaUsuarios->Length; i++) {
				if (listaUsuarios[i] != nullptr) {
					cboUsuarios->Items->Add(listaUsuarios[i]);
				}
			}
		}*/

		void InitializeComponent(void)
		{
			this->lblNombre = (gcnew System::Windows::Forms::Label());
			this->txtNombre = (gcnew System::Windows::Forms::TextBox());
			this->lblApellido = (gcnew System::Windows::Forms::Label());
			this->txtApellido = (gcnew System::Windows::Forms::TextBox());
			this->lblCUI = (gcnew System::Windows::Forms::Label());
			this->txtCUI = (gcnew System::Windows::Forms::TextBox());
			this->dateFechaNacimiento = (gcnew System::Windows::Forms::DateTimePicker());
			this->txtFechaNacimiento = (gcnew System::Windows::Forms::Label());
			this->lblTelefono = (gcnew System::Windows::Forms::Label());
			this->txtTelefono = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtEmail = (gcnew System::Windows::Forms::TextBox());
			this->tblClientes = (gcnew System::Windows::Forms::DataGridView());
			this->btnAgregar = (gcnew System::Windows::Forms::Button());
			this->btnEliminar = (gcnew System::Windows::Forms::Button());
			this->btnEditar = (gcnew System::Windows::Forms::Button());
			this->btnHTML = (gcnew System::Windows::Forms::Button());
			this->btnCargaDatos = (gcnew System::Windows::Forms::Button());
			this->colCodigo = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colNombre = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colApellido = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colCUI = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colFechaNacimiento = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colTelefono = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colEmail = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tblClientes))->BeginInit();
			this->SuspendLayout();
			// 
			// lblNombre
			// 
			this->lblNombre->AutoSize = true;
			this->lblNombre->Location = System::Drawing::Point(60, 48);
			this->lblNombre->Name = L"lblNombre";
			this->lblNombre->Size = System::Drawing::Size(65, 20);
			this->lblNombre->TabIndex = 0;
			this->lblNombre->Text = L"Nombre";
			// 
			// txtNombre
			// 
			this->txtNombre->Location = System::Drawing::Point(131, 45);
			this->txtNombre->Name = L"txtNombre";
			this->txtNombre->Size = System::Drawing::Size(100, 26);
			this->txtNombre->TabIndex = 1;
			// 
			// lblApellido
			// 
			this->lblApellido->AutoSize = true;
			this->lblApellido->Location = System::Drawing::Point(289, 48);
			this->lblApellido->Name = L"lblApellido";
			this->lblApellido->Size = System::Drawing::Size(65, 20);
			this->lblApellido->TabIndex = 2;
			this->lblApellido->Text = L"Apellido";
			// 
			// txtApellido
			// 
			this->txtApellido->Location = System::Drawing::Point(360, 45);
			this->txtApellido->Name = L"txtApellido";
			this->txtApellido->Size = System::Drawing::Size(100, 26);
			this->txtApellido->TabIndex = 3;
			// 
			// lblCUI
			// 
			this->lblCUI->AutoSize = true;
			this->lblCUI->Location = System::Drawing::Point(503, 45);
			this->lblCUI->Name = L"lblCUI";
			this->lblCUI->Size = System::Drawing::Size(114, 20);
			this->lblCUI->TabIndex = 4;
			this->lblCUI->Text = L"CUI/Pasaporte";
			// 
			// txtCUI
			// 
			this->txtCUI->Location = System::Drawing::Point(623, 42);
			this->txtCUI->Name = L"txtCUI";
			this->txtCUI->Size = System::Drawing::Size(100, 26);
			this->txtCUI->TabIndex = 5;
			// 
			// dateFechaNacimiento
			// 
			this->dateFechaNacimiento->Location = System::Drawing::Point(911, 43);
			this->dateFechaNacimiento->Name = L"dateFechaNacimiento";
			this->dateFechaNacimiento->Size = System::Drawing::Size(285, 26);
			this->dateFechaNacimiento->TabIndex = 6;
			this->dateFechaNacimiento->Value = System::DateTime(2025, 5, 12, 12, 6, 4, 0);
			// 
			// txtFechaNacimiento
			// 
			this->txtFechaNacimiento->AutoSize = true;
			this->txtFechaNacimiento->Location = System::Drawing::Point(768, 45);
			this->txtFechaNacimiento->Name = L"txtFechaNacimiento";
			this->txtFechaNacimiento->Size = System::Drawing::Size(137, 20);
			this->txtFechaNacimiento->TabIndex = 7;
			this->txtFechaNacimiento->Text = L"Fecha Nacimiento";
			// 
			// lblTelefono
			// 
			this->lblTelefono->AutoSize = true;
			this->lblTelefono->Location = System::Drawing::Point(247, 137);
			this->lblTelefono->Name = L"lblTelefono";
			this->lblTelefono->Size = System::Drawing::Size(71, 20);
			this->lblTelefono->TabIndex = 8;
			this->lblTelefono->Text = L"Telefono";
			// 
			// txtTelefono
			// 
			this->txtTelefono->Location = System::Drawing::Point(340, 134);
			this->txtTelefono->Name = L"txtTelefono";
			this->txtTelefono->Size = System::Drawing::Size(100, 26);
			this->txtTelefono->TabIndex = 9;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(546, 137);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(48, 20);
			this->label1->TabIndex = 10;
			this->label1->Text = L"Email";
			// 
			// txtEmail
			// 
			this->txtEmail->Location = System::Drawing::Point(613, 131);
			this->txtEmail->Name = L"txtEmail";
			this->txtEmail->Size = System::Drawing::Size(100, 26);
			this->txtEmail->TabIndex = 11;
			// 
			// tblClientes
			// 
			this->tblClientes->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->tblClientes->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(7) {
				this->colCodigo,
					this->colNombre, this->colApellido, this->colCUI, this->colFechaNacimiento, this->colTelefono, this->colEmail
			});
			this->tblClientes->Location = System::Drawing::Point(154, 272);
			this->tblClientes->Name = L"tblClientes";
			this->tblClientes->RowTemplate->Height = 28;
			this->tblClientes->Size = System::Drawing::Size(985, 329);
			this->tblClientes->TabIndex = 14;
			this->tblClientes->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Clientes::tblClientes_CellClick);
			// 
			// btnAgregar
			// 
			this->btnAgregar->Location = System::Drawing::Point(340, 213);
			this->btnAgregar->Name = L"btnAgregar";
			this->btnAgregar->Size = System::Drawing::Size(85, 31);
			this->btnAgregar->TabIndex = 15;
			this->btnAgregar->Text = L"Agregar";
			this->btnAgregar->UseVisualStyleBackColor = true;
			this->btnAgregar->Click += gcnew System::EventHandler(this, &Clientes::btnAgregar_Click);
			// 
			// btnEliminar
			// 
			this->btnEliminar->Location = System::Drawing::Point(469, 213);
			this->btnEliminar->Name = L"btnEliminar";
			this->btnEliminar->Size = System::Drawing::Size(85, 31);
			this->btnEliminar->TabIndex = 16;
			this->btnEliminar->Text = L"Eliminar";
			this->btnEliminar->UseVisualStyleBackColor = true;
			this->btnEliminar->Click += gcnew System::EventHandler(this, &Clientes::btnEliminar_Click);
			// 
			// btnEditar
			// 
			this->btnEditar->Location = System::Drawing::Point(601, 213);
			this->btnEditar->Name = L"btnEditar";
			this->btnEditar->Size = System::Drawing::Size(85, 31);
			this->btnEditar->TabIndex = 17;
			this->btnEditar->Text = L"Editar";
			this->btnEditar->UseVisualStyleBackColor = true;
			this->btnEditar->Click += gcnew System::EventHandler(this, &Clientes::btnEditar_Click);
			// 
			// btnHTML
			// 
			this->btnHTML->Location = System::Drawing::Point(726, 213);
			this->btnHTML->Name = L"btnHTML";
			this->btnHTML->Size = System::Drawing::Size(85, 31);
			this->btnHTML->TabIndex = 18;
			this->btnHTML->Text = L"HTML";
			this->btnHTML->UseVisualStyleBackColor = true;
			this->btnHTML->Click += gcnew System::EventHandler(this, &Clientes::btnHTML_Click);
			// 
			// btnCargaDatos
			// 
			this->btnCargaDatos->Location = System::Drawing::Point(847, 202);
			this->btnCargaDatos->Name = L"btnCargaDatos";
			this->btnCargaDatos->Size = System::Drawing::Size(96, 53);
			this->btnCargaDatos->TabIndex = 19;
			this->btnCargaDatos->Text = L"Carga de datos";
			this->btnCargaDatos->UseVisualStyleBackColor = true;
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
			// colApellido
			// 
			this->colApellido->HeaderText = L"Apellido";
			this->colApellido->Name = L"colApellido";
			// 
			// colCUI
			// 
			this->colCUI->HeaderText = L"CUI/Pasaporte";
			this->colCUI->Name = L"colCUI";
			// 
			// colFechaNacimiento
			// 
			this->colFechaNacimiento->HeaderText = L"Fecha de nacimiento";
			this->colFechaNacimiento->Name = L"colFechaNacimiento";
			// 
			// colTelefono
			// 
			this->colTelefono->HeaderText = L"Telefono";
			this->colTelefono->Name = L"colTelefono";
			// 
			// colEmail
			// 
			this->colEmail->HeaderText = L"Email";
			this->colEmail->Name = L"colEmail";
			// 
			// Clientes
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1249, 779);
			this->Controls->Add(this->btnCargaDatos);
			this->Controls->Add(this->btnHTML);
			this->Controls->Add(this->btnEditar);
			this->Controls->Add(this->btnEliminar);
			this->Controls->Add(this->btnAgregar);
			this->Controls->Add(this->tblClientes);
			this->Controls->Add(this->txtEmail);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->txtTelefono);
			this->Controls->Add(this->lblTelefono);
			this->Controls->Add(this->txtFechaNacimiento);
			this->Controls->Add(this->dateFechaNacimiento);
			this->Controls->Add(this->txtCUI);
			this->Controls->Add(this->lblCUI);
			this->Controls->Add(this->txtApellido);
			this->Controls->Add(this->lblApellido);
			this->Controls->Add(this->txtNombre);
			this->Controls->Add(this->lblNombre);
			this->Name = L"Clientes";
			this->Text = L"Clientes";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tblClientes))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		//Eventos
	private: System::Void tblClientes_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
		if (e->RowIndex >= 0 && e->RowIndex < tblClientes->Rows->Count) {
			DataGridViewRow^ fila = tblClientes->Rows[e->RowIndex];

			if (!fila->IsNewRow) {
				clienteSeleccionado = e->RowIndex;
				txtNombre->Text = fila->Cells["colNombre"]->Value->ToString();
				txtApellido->Text = fila->Cells["colApellido"]->Value->ToString();
				txtCUI->Text = fila->Cells["colCUI"]->Value->ToString();
				//dateFechaNacimiento->Value = DateTime::Parse(fila->Cells["colFechaNacimiento"]->Value->ToString());
				Object^ valorFecha = fila->Cells["colFechaNacimiento"]->Value;
				if (valorFecha != nullptr && !String::IsNullOrWhiteSpace(valorFecha->ToString())) {
					DateTime fecha;
					if (DateTime::TryParse(valorFecha->ToString(), fecha)) {
						dateFechaNacimiento->Value = fecha;
					}
					else {
						// Opcional: manejar formato inválido
						MessageBox::Show("Formato de fecha inválido en la fila seleccionada.");
					}
				}
				else {
					// Opcional: asignar una fecha por defecto si está vacío
					dateFechaNacimiento->Value = DateTime::Now;
				}
				txtTelefono->Text = fila->Cells["colTelefono"]->Value->ToString();
				txtEmail->Text = fila->Cells["colEmail"]->Value->ToString();
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
			if (txtNombre->Text->Trim() == "" ||
				txtApellido->Text->Trim() == "" ||
				txtCUI->Text->Trim() == "" ||
				dateFechaNacimiento->Value == DateTime::MinValue ||
				txtTelefono->Text->Trim() == "" ||
				txtEmail->Text->Trim() == "") {

				MessageBox::Show("Por favor complete todos los campos antes de agregar el usuario.", "Campos incompletos", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			String^ nombre = txtNombre->Text;
			String^ apellido = txtApellido->Text;
			String^ dpi = txtCUI->Text;
			DateTime^ fechaNacimiento = dateFechaNacimiento->Value;
			String^ telefono = txtTelefono->Text;
			String^ email = txtEmail->Text;

			AgregarCliente(nombre, apellido, dpi, fechaNacimiento, telefono, email);

			estadoActual = ModoFormulario::Ninguno;
			ActualizarEstadoFormulario();
			ResetearFormulario();
			tblClientes->ClearSelection();
		}
	}

	private: System::Void btnEliminar_Click(System::Object^ sender, System::EventArgs^ e) {
		if (estadoActual == ModoFormulario::Agregar) {
			estadoActual = ModoFormulario::Ninguno;
			ActualizarEstadoFormulario();
			ResetearFormulario();
			tblClientes->ClearSelection();
			clienteSeleccionado = -1; // Resetear la selección
			return;
		}

		if (estadoActual == ModoFormulario::Editar) {
			estadoActual = ModoFormulario::Ninguno;
			ActualizarEstadoFormulario();
			ResetearFormulario();
			tblClientes->ClearSelection();
			clienteSeleccionado = -1; // Resetear la selección
			return;
		}

		if (clienteSeleccionado >= 0 && clienteSeleccionado < ultimoCodigo) {
			System::Windows::Forms::DialogResult result = System::Windows::Forms::MessageBox::Show(
				"¿Estás seguro de que deseas eliminar este cliente?",
				"Confirmar eliminación",
				System::Windows::Forms::MessageBoxButtons::YesNo,
				System::Windows::Forms::MessageBoxIcon::Warning
			);

			if (result == System::Windows::Forms::DialogResult::Yes) {
				clientes[clienteSeleccionado] = nullptr;
				MostrarClientes();
			}
			ResetearFormulario();
			tblClientes->ClearSelection();

			clienteSeleccionado = -1; // Resetear la selección
		}
		else {
			System::Windows::Forms::MessageBox::Show("Seleccione un cliente para eliminar.");
		}
	}

	private: System::Void btnEditar_Click(System::Object^ sender, System::EventArgs^ e) {
		if (estadoActual == ModoFormulario::Ninguno) {
			if (clienteSeleccionado < 0 || clienteSeleccionado >= ultimoCodigo || clientes[clienteSeleccionado] == nullptr) {
				System::Windows::Forms::MessageBox::Show("Seleccione un cliente para editar.");
				return;
			}

			estadoActual = ModoFormulario::Editar;
			ActualizarEstadoFormulario();
		}
		else if (estadoActual == ModoFormulario::Editar) {
			if (txtNombre->Text->Trim() == "" ||
				txtApellido->Text->Trim() == "" ||
				txtCUI->Text->Trim() == "" ||
				dateFechaNacimiento->Value == DateTime::MinValue ||
				txtTelefono->Text->Trim() == "" ||
				txtEmail->Text->Trim() == "") {
				MessageBox::Show("Por favor complete todos los campos antes de editar el cliente.", "Campos incompletos", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			String^ nombre = txtNombre->Text;
			String^ apellido = txtApellido->Text;
			String^ dpi = txtCUI->Text;
			DateTime^ fechaNacimiento = dateFechaNacimiento->Value;
			String^ telefono = txtTelefono->Text;
			String^ email = txtEmail->Text;
			clientes[clienteSeleccionado]->Nombre = nombre;
			clientes[clienteSeleccionado]->Apellido = apellido;
			clientes[clienteSeleccionado]->DPI = dpi;
			clientes[clienteSeleccionado]->FechaNacimiento = fechaNacimiento;
			clientes[clienteSeleccionado]->Telefono = telefono;
			clientes[clienteSeleccionado]->Email = email;

			MostrarClientes();

			estadoActual = ModoFormulario::Ninguno;
			ActualizarEstadoFormulario();
			ResetearFormulario();
			tblClientes->ClearSelection();
			clienteSeleccionado = -1; // Resetear la selección
		}
	}
	private: System::Void btnHTML_Click(System::Object^ sender, System::EventArgs^ e) {
		if (ultimoCodigo == 0) {
			MessageBox::Show("No hay clientes para generar el reporte.",
				"Información", MessageBoxButtons::OK, MessageBoxIcon::Information);
			return;
		}

		GenerarReporteHTML();
	}

	};
}