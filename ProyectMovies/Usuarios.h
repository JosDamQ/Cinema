#pragma once
#include "ClaseUsuarios.h"

namespace ProyectMovies {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Usuarios
	/// </summary>
	public ref class Usuarios : public System::Windows::Forms::Form
	{
	private: 
		array<User^>^ usuarios;
		int ultimoCodigo;
		int userSeleccionado;

		enum class ModoFormulario {
			Ninguno,
			Agregar,
			Editar
		};

		ModoFormulario estadoActual = ModoFormulario::Ninguno;

	public:
		Usuarios(void)
		{
			InitializeComponent();
			CargarRoles();
			usuarios = gcnew array<User^>(50);
			ultimoCodigo = 0;
			userSeleccionado = -1;

			ActualizarEstadoFormulario();
			ResetearFormulario();
		}

		// Funcion de agregar
		void AgregarUsuario
		(
			String^ username,
			String^ password,
			String^ nombre,
			String^ apellido,
			String^ dpi,
			String^ telefono,
			String^ email,
			String^ direccion,
			Role role
		)
		{
			ultimoCodigo++;
			User^ nuevoUsuario = gcnew User(ultimoCodigo, username, password, nombre, apellido, dpi, telefono, email, direccion, role);
			usuarios[ultimoCodigo - 1] = nuevoUsuario;
			MostrarUsuarios();
		}

		// Funcion de mostrar
		void MostrarUsuarios()
		{
			tblUsuarios->Rows->Clear();
			for (int i = 0; i < ultimoCodigo; i++) {
				if (usuarios[i] != nullptr) {
					tblUsuarios->Rows->Add(
						usuarios[i]->Codigo,
						usuarios[i]->Username,
						usuarios[i]->Password,
						usuarios[i]->Nombre,
						usuarios[i]->Apellido,
						usuarios[i]->DPI,
						usuarios[i]->Telefono,
						usuarios[i]->Email,
						usuarios[i]->Direccion,
						usuarios[i]->UserRole.ToString()
					);
				}
			}
		}

		// Resetear el formulario
		void ResetearFormulario()
		{
			txtUsuario->Clear();
			txtPassword->Clear();
			txtNombre->Clear();
			txtApellido->Clear();
			txtCUI->Clear();
			txtTelefono->Clear();
			txtEmail->Clear();
			txtDireccion->Clear();
			cboRol->SelectedIndex = -1; // Resetear el combo box a Admin
		}

		//Estado formulario
		void ActualizarEstadoFormulario() {
			bool habilitar = estadoActual != ModoFormulario::Ninguno;

			txtUsuario->Enabled = habilitar;
			txtPassword->Enabled = habilitar;
			txtNombre->Enabled = habilitar;
			txtApellido->Enabled = habilitar;
			txtCUI->Enabled = habilitar;
			txtTelefono->Enabled = habilitar;
			txtEmail->Enabled = habilitar;
			txtDireccion->Enabled = habilitar;
			cboRol->Enabled = habilitar;

			if (estadoActual == ModoFormulario::Agregar) {
				btnAgregar->Text = "Confirmar";
				btnEliminar->Text = "Cancelar";
				btnEditar->Enabled = false;
			}
			else if (estadoActual == ModoFormulario::Editar) {
				btnEditar->Text = "Confirmar";
				btnEliminar->Text = "Cancelar";
				btnAgregar->Enabled = false;
			}
			else {
				btnAgregar->Text = "Agregar";
				btnEliminar->Text = "Eliminar";
				btnEditar->Text = "Editar";
				btnAgregar->Enabled = true;
				btnEliminar->Enabled = true;
				btnEditar->Enabled = true;
			}
		}
		
		// Para mostrar los usuarios en combo box externo
		/*array<User^>^ ObtenerUsuariosRegistrados() {
			return usuarios;
		}*/

	protected:
		~Usuarios()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ lblName;
	private: System::Windows::Forms::TextBox^ txtUsuario;
	private: System::Windows::Forms::Label^ lblPassword;
	private: System::Windows::Forms::TextBox^ txtPassword;
	private: System::Windows::Forms::Label^ lblRol;

	private: System::Windows::Forms::Label^ lblNombre;
	private: System::Windows::Forms::TextBox^ txtNombre;
	private: System::Windows::Forms::Label^ lblApellido;
	private: System::Windows::Forms::TextBox^ txtApellido;
	private: System::Windows::Forms::Label^ lblTelefono;
	private: System::Windows::Forms::TextBox^ txtTelefono;
	private: System::Windows::Forms::Label^ lblCUI;
	private: System::Windows::Forms::TextBox^ txtCUI;
	private: System::Windows::Forms::Label^ lblEmail;
	private: System::Windows::Forms::TextBox^ txtEmail;
	private: System::Windows::Forms::Label^ lblDireccion;
	private: System::Windows::Forms::TextBox^ txtDireccion;
	private: System::Windows::Forms::ComboBox^ cboRol;
	private: System::Windows::Forms::DataGridView^ tblUsuarios;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colCodigo;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colUsuario;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colPassword;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colNombre;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colApellido;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colCUI;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colTelefono;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colEmail;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colDireccion;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colRol;
	private: System::Windows::Forms::Button^ btnAgregar;
	private: System::Windows::Forms::Button^ btnEditar;
	private: System::Windows::Forms::Button^ btnEliminar;

	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void CargarRoles() {
			this->cboRol->Items->Add(Role::Admin.ToString());
			this->cboRol->Items->Add(Role::User.ToString());
		}
		void InitializeComponent(void)
		{
			this->lblName = (gcnew System::Windows::Forms::Label());
			this->txtUsuario = (gcnew System::Windows::Forms::TextBox());
			this->lblPassword = (gcnew System::Windows::Forms::Label());
			this->txtPassword = (gcnew System::Windows::Forms::TextBox());
			this->lblRol = (gcnew System::Windows::Forms::Label());
			this->lblNombre = (gcnew System::Windows::Forms::Label());
			this->txtNombre = (gcnew System::Windows::Forms::TextBox());
			this->lblApellido = (gcnew System::Windows::Forms::Label());
			this->txtApellido = (gcnew System::Windows::Forms::TextBox());
			this->lblTelefono = (gcnew System::Windows::Forms::Label());
			this->txtTelefono = (gcnew System::Windows::Forms::TextBox());
			this->lblCUI = (gcnew System::Windows::Forms::Label());
			this->txtCUI = (gcnew System::Windows::Forms::TextBox());
			this->lblEmail = (gcnew System::Windows::Forms::Label());
			this->txtEmail = (gcnew System::Windows::Forms::TextBox());
			this->lblDireccion = (gcnew System::Windows::Forms::Label());
			this->txtDireccion = (gcnew System::Windows::Forms::TextBox());
			this->cboRol = (gcnew System::Windows::Forms::ComboBox());
			this->tblUsuarios = (gcnew System::Windows::Forms::DataGridView());
			this->colCodigo = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colUsuario = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colPassword = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colNombre = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colApellido = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colCUI = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colTelefono = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colEmail = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colDireccion = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colRol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->btnAgregar = (gcnew System::Windows::Forms::Button());
			this->btnEditar = (gcnew System::Windows::Forms::Button());
			this->btnEliminar = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tblUsuarios))->BeginInit();
			this->SuspendLayout();
			// 
			// lblName
			// 
			this->lblName->AutoSize = true;
			this->lblName->Location = System::Drawing::Point(31, 33);
			this->lblName->Name = L"lblName";
			this->lblName->Size = System::Drawing::Size(64, 20);
			this->lblName->TabIndex = 0;
			this->lblName->Text = L"Usuario";
			// 
			// txtUsuario
			// 
			this->txtUsuario->Location = System::Drawing::Point(92, 30);
			this->txtUsuario->Name = L"txtUsuario";
			this->txtUsuario->Size = System::Drawing::Size(137, 26);
			this->txtUsuario->TabIndex = 1;
			// 
			// lblPassword
			// 
			this->lblPassword->AutoSize = true;
			this->lblPassword->Location = System::Drawing::Point(235, 33);
			this->lblPassword->Name = L"lblPassword";
			this->lblPassword->Size = System::Drawing::Size(78, 20);
			this->lblPassword->TabIndex = 2;
			this->lblPassword->Text = L"Password";
			// 
			// txtPassword
			// 
			this->txtPassword->Location = System::Drawing::Point(311, 30);
			this->txtPassword->Name = L"txtPassword";
			this->txtPassword->Size = System::Drawing::Size(133, 26);
			this->txtPassword->TabIndex = 3;
			this->txtPassword->TextChanged += gcnew System::EventHandler(this, &Usuarios::textBox1_TextChanged);
			// 
			// lblRol
			// 
			this->lblRol->AutoSize = true;
			this->lblRol->Location = System::Drawing::Point(801, 85);
			this->lblRol->Name = L"lblRol";
			this->lblRol->Size = System::Drawing::Size(33, 20);
			this->lblRol->TabIndex = 5;
			this->lblRol->Text = L"Rol";
			// 
			// lblNombre
			// 
			this->lblNombre->AutoSize = true;
			this->lblNombre->Location = System::Drawing::Point(462, 33);
			this->lblNombre->Name = L"lblNombre";
			this->lblNombre->Size = System::Drawing::Size(65, 20);
			this->lblNombre->TabIndex = 6;
			this->lblNombre->Text = L"Nombre";
			this->lblNombre->Click += gcnew System::EventHandler(this, &Usuarios::label2_Click);
			// 
			// txtNombre
			// 
			this->txtNombre->Location = System::Drawing::Point(524, 30);
			this->txtNombre->Name = L"txtNombre";
			this->txtNombre->Size = System::Drawing::Size(143, 26);
			this->txtNombre->TabIndex = 7;
			// 
			// lblApellido
			// 
			this->lblApellido->AutoSize = true;
			this->lblApellido->Location = System::Drawing::Point(684, 33);
			this->lblApellido->Name = L"lblApellido";
			this->lblApellido->Size = System::Drawing::Size(65, 20);
			this->lblApellido->TabIndex = 8;
			this->lblApellido->Text = L"Apellido";
			this->lblApellido->Click += gcnew System::EventHandler(this, &Usuarios::lblApellido_Click);
			// 
			// txtApellido
			// 
			this->txtApellido->Location = System::Drawing::Point(755, 27);
			this->txtApellido->Name = L"txtApellido";
			this->txtApellido->Size = System::Drawing::Size(122, 26);
			this->txtApellido->TabIndex = 9;
			// 
			// lblTelefono
			// 
			this->lblTelefono->AutoSize = true;
			this->lblTelefono->Location = System::Drawing::Point(905, 33);
			this->lblTelefono->Name = L"lblTelefono";
			this->lblTelefono->Size = System::Drawing::Size(86, 20);
			this->lblTelefono->TabIndex = 10;
			this->lblTelefono->Text = L"lblTelefono";
			// 
			// txtTelefono
			// 
			this->txtTelefono->Location = System::Drawing::Point(997, 27);
			this->txtTelefono->Name = L"txtTelefono";
			this->txtTelefono->Size = System::Drawing::Size(133, 26);
			this->txtTelefono->TabIndex = 11;
			// 
			// lblCUI
			// 
			this->lblCUI->AutoSize = true;
			this->lblCUI->Location = System::Drawing::Point(35, 85);
			this->lblCUI->Name = L"lblCUI";
			this->lblCUI->Size = System::Drawing::Size(114, 20);
			this->lblCUI->TabIndex = 12;
			this->lblCUI->Text = L"CUI/Pasaporte";
			// 
			// txtCUI
			// 
			this->txtCUI->Location = System::Drawing::Point(155, 82);
			this->txtCUI->Name = L"txtCUI";
			this->txtCUI->Size = System::Drawing::Size(148, 26);
			this->txtCUI->TabIndex = 13;
			// 
			// lblEmail
			// 
			this->lblEmail->AutoSize = true;
			this->lblEmail->Location = System::Drawing::Point(330, 85);
			this->lblEmail->Name = L"lblEmail";
			this->lblEmail->Size = System::Drawing::Size(48, 20);
			this->lblEmail->TabIndex = 14;
			this->lblEmail->Text = L"Email";
			// 
			// txtEmail
			// 
			this->txtEmail->Location = System::Drawing::Point(384, 82);
			this->txtEmail->Name = L"txtEmail";
			this->txtEmail->Size = System::Drawing::Size(143, 26);
			this->txtEmail->TabIndex = 15;
			// 
			// lblDireccion
			// 
			this->lblDireccion->AutoSize = true;
			this->lblDireccion->Location = System::Drawing::Point(554, 85);
			this->lblDireccion->Name = L"lblDireccion";
			this->lblDireccion->Size = System::Drawing::Size(75, 20);
			this->lblDireccion->TabIndex = 16;
			this->lblDireccion->Text = L"Direccion";
			// 
			// txtDireccion
			// 
			this->txtDireccion->Location = System::Drawing::Point(635, 82);
			this->txtDireccion->Name = L"txtDireccion";
			this->txtDireccion->Size = System::Drawing::Size(127, 26);
			this->txtDireccion->TabIndex = 17;
			// 
			// cboRol
			// 
			this->cboRol->FormattingEnabled = true;
			this->cboRol->Location = System::Drawing::Point(840, 82);
			this->cboRol->Name = L"cboRol";
			this->cboRol->Size = System::Drawing::Size(121, 28);
			this->cboRol->TabIndex = 18;
			//Esto es para que no se pueda escribir en el combobox
			this->cboRol->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			// 
			// tblUsuarios
			// 
			this->tblUsuarios->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->tblUsuarios->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(10) {
				this->colCodigo,
					this->colUsuario, this->colPassword, this->colNombre, this->colApellido, this->colCUI, this->colTelefono, this->colEmail, this->colDireccion,
					this->colRol
			});
			this->tblUsuarios->Location = System::Drawing::Point(48, 217);
			this->tblUsuarios->Name = L"tblUsuarios";
			this->tblUsuarios->RowTemplate->Height = 28;
			this->tblUsuarios->Size = System::Drawing::Size(1106, 434);
			this->tblUsuarios->TabIndex = 19;
			this->tblUsuarios->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Usuarios::tblUsuarios_CellClick);
			// 
			// colCodigo
			// 
			this->colCodigo->HeaderText = L"Codigo";
			this->colCodigo->Name = L"colCodigo";
			// 
			// colUsuario
			// 
			this->colUsuario->HeaderText = L"Usuario";
			this->colUsuario->Name = L"colUsuario";
			// 
			// colPassword
			// 
			this->colPassword->HeaderText = L"Password";
			this->colPassword->Name = L"colPassword";
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
			this->colCUI->MaxInputLength = 32787;
			this->colCUI->Name = L"colCUI";
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
			// colDireccion
			// 
			this->colDireccion->HeaderText = L"Direccion";
			this->colDireccion->Name = L"colDireccion";
			// 
			// colRol
			// 
			this->colRol->HeaderText = L"Rol";
			this->colRol->Name = L"colRol";
			// 
			// btnAgregar
			// 
			this->btnAgregar->Location = System::Drawing::Point(346, 160);
			this->btnAgregar->Name = L"btnAgregar";
			this->btnAgregar->Size = System::Drawing::Size(98, 37);
			this->btnAgregar->TabIndex = 20;
			this->btnAgregar->Text = L"Agregar";
			this->btnAgregar->UseVisualStyleBackColor = true;
			this->btnAgregar->Click += gcnew System::EventHandler(this, &Usuarios::btnAgregar_Click);
			// 
			// btnEditar
			// 
			this->btnEditar->Location = System::Drawing::Point(675, 160);
			this->btnEditar->Name = L"btnEditar";
			this->btnEditar->Size = System::Drawing::Size(98, 37);
			this->btnEditar->TabIndex = 21;
			this->btnEditar->Text = L"Editar";
			this->btnEditar->UseVisualStyleBackColor = true;
			this->btnEditar->Click += gcnew System::EventHandler(this, &Usuarios::btnEditar_Click);
			// 
			// btnEliminar
			// 
			this->btnEliminar->Location = System::Drawing::Point(505, 160);
			this->btnEliminar->Name = L"btnEliminar";
			this->btnEliminar->Size = System::Drawing::Size(98, 37);
			this->btnEliminar->TabIndex = 22;
			this->btnEliminar->Text = L"Eliminar";
			this->btnEliminar->UseVisualStyleBackColor = true;
			this->btnEliminar->Click += gcnew System::EventHandler(this, &Usuarios::btnEliminar_Click);
			// 
			// Usuarios
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1201, 707);
			this->Controls->Add(this->btnEliminar);
			this->Controls->Add(this->btnEditar);
			this->Controls->Add(this->btnAgregar);
			this->Controls->Add(this->tblUsuarios);
			this->Controls->Add(this->cboRol);
			this->Controls->Add(this->txtDireccion);
			this->Controls->Add(this->lblDireccion);
			this->Controls->Add(this->txtEmail);
			this->Controls->Add(this->lblEmail);
			this->Controls->Add(this->txtCUI);
			this->Controls->Add(this->lblCUI);
			this->Controls->Add(this->txtTelefono);
			this->Controls->Add(this->lblTelefono);
			this->Controls->Add(this->txtApellido);
			this->Controls->Add(this->lblApellido);
			this->Controls->Add(this->txtNombre);
			this->Controls->Add(this->lblNombre);
			this->Controls->Add(this->lblRol);
			this->Controls->Add(this->txtPassword);
			this->Controls->Add(this->lblPassword);
			this->Controls->Add(this->txtUsuario);
			this->Controls->Add(this->lblName);
			this->Name = L"Usuarios";
			this->Text = L"Usuarios";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tblUsuarios))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void lblApellido_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void tblUsuarios_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e){
		if (e->RowIndex >= 0 && e->RowIndex < tblUsuarios->Rows->Count) {
			DataGridViewRow^ fila = tblUsuarios->Rows[e->RowIndex];

			if (!fila->IsNewRow) {
				txtUsuario->Text = fila->Cells["colUsuario"]->Value->ToString();
				txtPassword->Text = fila->Cells["colPassword"]->Value->ToString();
				txtNombre->Text = fila->Cells["colNombre"]->Value->ToString();
				txtApellido->Text = fila->Cells["colApellido"]->Value->ToString();
				txtCUI->Text = fila->Cells["colCUI"]->Value->ToString();
				txtTelefono->Text = fila->Cells["colTelefono"]->Value->ToString();
				txtEmail->Text = fila->Cells["colEmail"]->Value->ToString();
				txtDireccion->Text = fila->Cells["colDireccion"]->Value->ToString();
				cboRol->SelectedItem = fila->Cells["colRol"]->Value;
				userSeleccionado = e->RowIndex; // Guardar el índice de la fila seleccionada
			}
		}
	}
	private: System::Void btnAgregar_Click(System::Object^ sender, System::EventArgs^ e){
		if (estadoActual == ModoFormulario::Ninguno) {
			estadoActual = ModoFormulario::Agregar;
			ActualizarEstadoFormulario();
			ResetearFormulario();
		}
		else if (estadoActual == ModoFormulario::Agregar) {
			if (txtUsuario->Text->Trim() == "" ||
				txtPassword->Text->Trim() == "" ||
				txtNombre->Text->Trim() == "" ||
				txtApellido->Text->Trim() == "" ||
				txtCUI->Text->Trim() == "" ||
				txtTelefono->Text->Trim() == "" ||
				txtEmail->Text->Trim() == "" ||
				txtDireccion->Text->Trim() == "" ||
				cboRol->SelectedIndex == -1) {

				MessageBox::Show("Por favor complete todos los campos antes de agregar el usuario.", "Campos incompletos", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			String^ username = txtUsuario->Text;
			String^ password = txtPassword->Text;
			String^ nombre = txtNombre->Text;
			String^ apellido = txtApellido->Text;
			String^ dpi = txtCUI->Text;
			String^ telefono = txtTelefono->Text;
			String^ email = txtEmail->Text;
			String^ direccion = txtDireccion->Text;
			Role role = (Role)Enum::Parse(Role::typeid, cboRol->SelectedItem->ToString());

			AgregarUsuario(username, password, nombre, apellido, dpi, telefono, email, direccion, role);

			estadoActual = ModoFormulario::Ninguno;
			ActualizarEstadoFormulario();
			ResetearFormulario();
			tblUsuarios->ClearSelection();
		}
	}
	private: System::Void btnEliminar_Click(System::Object^ sender, System::EventArgs^ e) {
		if (estadoActual == ModoFormulario::Agregar) {
			estadoActual = ModoFormulario::Ninguno;
			ActualizarEstadoFormulario();
			ResetearFormulario();
			tblUsuarios->ClearSelection();
			userSeleccionado = -1; // Resetear la selección
			return;
		}

		if (estadoActual == ModoFormulario::Editar) {
			estadoActual = ModoFormulario::Ninguno;
			ActualizarEstadoFormulario();
			ResetearFormulario();
			tblUsuarios->ClearSelection();
			userSeleccionado = -1; // Resetear la selección
			return;
		}
		
		if (userSeleccionado >= 0 && userSeleccionado < ultimoCodigo) {
			System::Windows::Forms::DialogResult result = System::Windows::Forms::MessageBox::Show(
				"¿Estás seguro de que deseas eliminar este usuario?",
				"Confirmar eliminación",
				System::Windows::Forms::MessageBoxButtons::YesNo,
				System::Windows::Forms::MessageBoxIcon::Warning
			);

			if (result == System::Windows::Forms::DialogResult::Yes) {
				usuarios[userSeleccionado] = nullptr;
				MostrarUsuarios();
			}
			ResetearFormulario();
			tblUsuarios->ClearSelection();

			userSeleccionado = -1; // Resetear la selección
		}
		else {
			System::Windows::Forms::MessageBox::Show("Seleccione un usuario para eliminar.");
		}
	}
	private: System::Void btnEditar_Click(System::Object^ sender, System::EventArgs^ e) {
		if (estadoActual == ModoFormulario::Ninguno) {
			if (userSeleccionado < 0 || userSeleccionado >= ultimoCodigo || usuarios[userSeleccionado] == nullptr) {
				MessageBox::Show("Seleccione un usuario para editar.");
				return;
			}

			estadoActual = ModoFormulario::Editar;
			ActualizarEstadoFormulario();
		}
		else if (estadoActual == ModoFormulario::Editar) {
			if (txtUsuario->Text->Trim() == "" ||
				txtPassword->Text->Trim() == "" ||
				txtNombre->Text->Trim() == "" ||
				txtApellido->Text->Trim() == "" ||
				txtCUI->Text->Trim() == "" ||
				txtTelefono->Text->Trim() == "" ||
				txtEmail->Text->Trim() == "" ||
				txtDireccion->Text->Trim() == "" ||
				cboRol->SelectedIndex == -1) {

				MessageBox::Show("Por favor complete todos los campos antes de confirmar la edición.", "Campos incompletos", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			String^ username = txtUsuario->Text;
			String^ password = txtPassword->Text;
			String^ nombre = txtNombre->Text;
			String^ apellido = txtApellido->Text;
			String^ dpi = txtCUI->Text;
			String^ telefono = txtTelefono->Text;
			String^ email = txtEmail->Text;
			String^ direccion = txtDireccion->Text;
			Role role = (Role)Enum::Parse(Role::typeid, cboRol->SelectedItem->ToString());
			usuarios[userSeleccionado]->Username = username;
			usuarios[userSeleccionado]->Password = password;
			usuarios[userSeleccionado]->Nombre = nombre;
			usuarios[userSeleccionado]->Apellido = apellido;
			usuarios[userSeleccionado]->DPI = dpi;
			usuarios[userSeleccionado]->Telefono = telefono;
			usuarios[userSeleccionado]->Email = email;
			usuarios[userSeleccionado]->Direccion = direccion;
			usuarios[userSeleccionado]->UserRole = role;

			MostrarUsuarios();

			estadoActual = ModoFormulario::Ninguno;
			ActualizarEstadoFormulario();
			ResetearFormulario();
			tblUsuarios->ClearSelection();
			userSeleccionado = -1; // Resetear la selección
		}

	}
};
}
