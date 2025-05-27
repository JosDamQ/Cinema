#pragma once
#include "ClaseUsuarios.h"

namespace ProyectMovies {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class Usuarios : public System::Windows::Forms::Form
    {
    private:
        System::Collections::Generic::List<User^>^ usuarios;
        int ultimoCodigo;
        int userSeleccionado;

    private: System::Windows::Forms::Button^ btnCargaDatos;

        enum class ModoFormulario {
            Ninguno,
            Agregar,
            Editar
        };

        ModoFormulario estadoActual = ModoFormulario::Ninguno;

    public:
        Usuarios(System::Collections::Generic::List<User^>^ usersList)
        {
            InitializeComponent();
            CargarRoles();

            usuarios = usersList;
            ultimoCodigo = 0;
            for each (User ^ user in usuarios)
            {
                if (user != nullptr && user->Codigo > ultimoCodigo)
                    ultimoCodigo = user->Codigo;
            }

            userSeleccionado = -1;

            MostrarUsuarios();
            ActualizarEstadoFormulario();
            ResetearFormulario();
        }

        void AgregarUsuario(
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
            User^ nuevoUsuario = gcnew User(
                ultimoCodigo,
                username,
                password,
                nombre,
                apellido,
                dpi,
                telefono,
                email,
                direccion,
                role
            );
            usuarios->Add(nuevoUsuario);
            MostrarUsuarios();
        }

        void MostrarUsuarios()
        {
            tblUsuarios->Rows->Clear();
            for each (User ^ user in usuarios)
            {
                if (user != nullptr) {
                    tblUsuarios->Rows->Add(
                        user->Codigo,
                        user->Username,
                        user->Password,
                        user->Nombre,
                        user->Apellido,
                        user->DPI,
                        user->Telefono,
                        user->Email,
                        user->Direccion,
                        user->UserRole.ToString()
                    );
                }
            }
        }

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
            cboRol->SelectedIndex = -1;
        }

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

    protected:
        ~Usuarios()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Label^ lblName;
        System::Windows::Forms::TextBox^ txtUsuario;
        System::Windows::Forms::Label^ lblPassword;
        System::Windows::Forms::TextBox^ txtPassword;
        System::Windows::Forms::Label^ lblRol;
        System::Windows::Forms::Label^ lblNombre;
        System::Windows::Forms::TextBox^ txtNombre;
        System::Windows::Forms::Label^ lblApellido;
        System::Windows::Forms::TextBox^ txtApellido;
        System::Windows::Forms::Label^ lblTelefono;
        System::Windows::Forms::TextBox^ txtTelefono;
        System::Windows::Forms::Label^ lblCUI;
        System::Windows::Forms::TextBox^ txtCUI;
        System::Windows::Forms::Label^ lblEmail;
        System::Windows::Forms::TextBox^ txtEmail;
        System::Windows::Forms::Label^ lblDireccion;
        System::Windows::Forms::TextBox^ txtDireccion;
        System::Windows::Forms::ComboBox^ cboRol;
        System::Windows::Forms::DataGridView^ tblUsuarios;
        System::Windows::Forms::DataGridViewTextBoxColumn^ colCodigo;
        System::Windows::Forms::DataGridViewTextBoxColumn^ colUsuario;
        System::Windows::Forms::DataGridViewTextBoxColumn^ colPassword;
        System::Windows::Forms::DataGridViewTextBoxColumn^ colNombre;
        System::Windows::Forms::DataGridViewTextBoxColumn^ colApellido;
        System::Windows::Forms::DataGridViewTextBoxColumn^ colCUI;
        System::Windows::Forms::DataGridViewTextBoxColumn^ colTelefono;
        System::Windows::Forms::DataGridViewTextBoxColumn^ colEmail;
        System::Windows::Forms::DataGridViewTextBoxColumn^ colDireccion;
        System::Windows::Forms::DataGridViewTextBoxColumn^ colRol;
        System::Windows::Forms::Button^ btnAgregar;
        System::Windows::Forms::Button^ btnEditar;
        System::Windows::Forms::Button^ btnEliminar;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void CargarRoles() {
            this->cboRol->Items->Add(Role::Admin.ToString());
            this->cboRol->Items->Add(Role::User.ToString());
            this->cboRol->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
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
            this->btnCargaDatos = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tblUsuarios))->BeginInit();
            this->SuspendLayout();
            // 
            // lblName
            // 
            this->lblName->AutoSize = true;
            this->lblName->Location = System::Drawing::Point(21, 21);
            this->lblName->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->lblName->Name = L"lblName";
            this->lblName->Size = System::Drawing::Size(43, 13);
            this->lblName->TabIndex = 0;
            this->lblName->Text = L"Usuario";
            // 
            // txtUsuario
            // 
            this->txtUsuario->Location = System::Drawing::Point(61, 20);
            this->txtUsuario->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
            this->txtUsuario->Name = L"txtUsuario";
            this->txtUsuario->Size = System::Drawing::Size(93, 20);
            this->txtUsuario->TabIndex = 1;
            // 
            // lblPassword
            // 
            this->lblPassword->AutoSize = true;
            this->lblPassword->Location = System::Drawing::Point(157, 21);
            this->lblPassword->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->lblPassword->Name = L"lblPassword";
            this->lblPassword->Size = System::Drawing::Size(53, 13);
            this->lblPassword->TabIndex = 2;
            this->lblPassword->Text = L"Password";
            // 
            // txtPassword
            // 
            this->txtPassword->Location = System::Drawing::Point(207, 20);
            this->txtPassword->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
            this->txtPassword->Name = L"txtPassword";
            this->txtPassword->Size = System::Drawing::Size(90, 20);
            this->txtPassword->TabIndex = 3;
            this->txtPassword->TextChanged += gcnew System::EventHandler(this, &Usuarios::textBox1_TextChanged);
            // 
            // lblRol
            // 
            this->lblRol->AutoSize = true;
            this->lblRol->Location = System::Drawing::Point(534, 55);
            this->lblRol->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->lblRol->Name = L"lblRol";
            this->lblRol->Size = System::Drawing::Size(23, 13);
            this->lblRol->TabIndex = 5;
            this->lblRol->Text = L"Rol";
            // 
            // lblNombre
            // 
            this->lblNombre->AutoSize = true;
            this->lblNombre->Location = System::Drawing::Point(308, 21);
            this->lblNombre->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->lblNombre->Name = L"lblNombre";
            this->lblNombre->Size = System::Drawing::Size(44, 13);
            this->lblNombre->TabIndex = 6;
            this->lblNombre->Text = L"Nombre";
            this->lblNombre->Click += gcnew System::EventHandler(this, &Usuarios::label2_Click);
            // 
            // txtNombre
            // 
            this->txtNombre->Location = System::Drawing::Point(349, 20);
            this->txtNombre->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
            this->txtNombre->Name = L"txtNombre";
            this->txtNombre->Size = System::Drawing::Size(97, 20);
            this->txtNombre->TabIndex = 7;
            // 
            // lblApellido
            // 
            this->lblApellido->AutoSize = true;
            this->lblApellido->Location = System::Drawing::Point(456, 21);
            this->lblApellido->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->lblApellido->Name = L"lblApellido";
            this->lblApellido->Size = System::Drawing::Size(44, 13);
            this->lblApellido->TabIndex = 8;
            this->lblApellido->Text = L"Apellido";
            this->lblApellido->Click += gcnew System::EventHandler(this, &Usuarios::lblApellido_Click);
            // 
            // txtApellido
            // 
            this->txtApellido->Location = System::Drawing::Point(503, 18);
            this->txtApellido->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
            this->txtApellido->Name = L"txtApellido";
            this->txtApellido->Size = System::Drawing::Size(83, 20);
            this->txtApellido->TabIndex = 9;
            // 
            // lblTelefono
            // 
            this->lblTelefono->AutoSize = true;
            this->lblTelefono->Location = System::Drawing::Point(603, 21);
            this->lblTelefono->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->lblTelefono->Name = L"lblTelefono";
            this->lblTelefono->Size = System::Drawing::Size(49, 13);
            this->lblTelefono->TabIndex = 10;
            this->lblTelefono->Text = L"Teléfono";
            // 
            // txtTelefono
            // 
            this->txtTelefono->Location = System::Drawing::Point(665, 18);
            this->txtTelefono->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
            this->txtTelefono->Name = L"txtTelefono";
            this->txtTelefono->Size = System::Drawing::Size(90, 20);
            this->txtTelefono->TabIndex = 11;
            // 
            // lblCUI
            // 
            this->lblCUI->AutoSize = true;
            this->lblCUI->Location = System::Drawing::Point(23, 55);
            this->lblCUI->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->lblCUI->Name = L"lblCUI";
            this->lblCUI->Size = System::Drawing::Size(78, 13);
            this->lblCUI->TabIndex = 12;
            this->lblCUI->Text = L"CUI/Pasaporte";
            // 
            // txtCUI
            // 
            this->txtCUI->Location = System::Drawing::Point(103, 53);
            this->txtCUI->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
            this->txtCUI->Name = L"txtCUI";
            this->txtCUI->Size = System::Drawing::Size(100, 20);
            this->txtCUI->TabIndex = 13;
            // 
            // lblEmail
            // 
            this->lblEmail->AutoSize = true;
            this->lblEmail->Location = System::Drawing::Point(220, 55);
            this->lblEmail->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->lblEmail->Name = L"lblEmail";
            this->lblEmail->Size = System::Drawing::Size(32, 13);
            this->lblEmail->TabIndex = 14;
            this->lblEmail->Text = L"Email";
            // 
            // txtEmail
            // 
            this->txtEmail->Location = System::Drawing::Point(256, 53);
            this->txtEmail->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
            this->txtEmail->Name = L"txtEmail";
            this->txtEmail->Size = System::Drawing::Size(97, 20);
            this->txtEmail->TabIndex = 15;
            // 
            // lblDireccion
            // 
            this->lblDireccion->AutoSize = true;
            this->lblDireccion->Location = System::Drawing::Point(369, 55);
            this->lblDireccion->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->lblDireccion->Name = L"lblDireccion";
            this->lblDireccion->Size = System::Drawing::Size(52, 13);
            this->lblDireccion->TabIndex = 16;
            this->lblDireccion->Text = L"Dirección";
            // 
            // txtDireccion
            // 
            this->txtDireccion->Location = System::Drawing::Point(423, 53);
            this->txtDireccion->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
            this->txtDireccion->Name = L"txtDireccion";
            this->txtDireccion->Size = System::Drawing::Size(86, 20);
            this->txtDireccion->TabIndex = 17;
            // 
            // cboRol
            // 
            this->cboRol->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cboRol->FormattingEnabled = true;
            this->cboRol->Location = System::Drawing::Point(560, 53);
            this->cboRol->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
            this->cboRol->Name = L"cboRol";
            this->cboRol->Size = System::Drawing::Size(82, 21);
            this->cboRol->TabIndex = 18;
            // 
            // tblUsuarios
            // 
            this->tblUsuarios->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->tblUsuarios->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(10) {
                this->colCodigo,
                    this->colUsuario, this->colPassword, this->colNombre, this->colApellido, this->colCUI, this->colTelefono, this->colEmail, this->colDireccion,
                    this->colRol
            });
            this->tblUsuarios->Location = System::Drawing::Point(32, 141);
            this->tblUsuarios->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
            this->tblUsuarios->Name = L"tblUsuarios";
            this->tblUsuarios->RowTemplate->Height = 28;
            this->tblUsuarios->Size = System::Drawing::Size(737, 282);
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
            this->colTelefono->HeaderText = L"Teléfono";
            this->colTelefono->Name = L"colTelefono";
            // 
            // colEmail
            // 
            this->colEmail->HeaderText = L"Email";
            this->colEmail->Name = L"colEmail";
            // 
            // colDireccion
            // 
            this->colDireccion->HeaderText = L"Dirección";
            this->colDireccion->Name = L"colDireccion";
            // 
            // colRol
            // 
            this->colRol->HeaderText = L"Rol";
            this->colRol->Name = L"colRol";
            // 
            // btnAgregar
            // 
            this->btnAgregar->Location = System::Drawing::Point(197, 104);
            this->btnAgregar->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
            this->btnAgregar->Name = L"btnAgregar";
            this->btnAgregar->Size = System::Drawing::Size(65, 24);
            this->btnAgregar->TabIndex = 20;
            this->btnAgregar->Text = L"Agregar";
            this->btnAgregar->UseVisualStyleBackColor = true;
            this->btnAgregar->Click += gcnew System::EventHandler(this, &Usuarios::btnAgregar_Click);
            // 
            // btnEditar
            // 
            this->btnEditar->Location = System::Drawing::Point(387, 104);
            this->btnEditar->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
            this->btnEditar->Name = L"btnEditar";
            this->btnEditar->Size = System::Drawing::Size(65, 24);
            this->btnEditar->TabIndex = 21;
            this->btnEditar->Text = L"Editar";
            this->btnEditar->UseVisualStyleBackColor = true;
            this->btnEditar->Click += gcnew System::EventHandler(this, &Usuarios::btnEditar_Click);
            // 
            // btnEliminar
            // 
            this->btnEliminar->Location = System::Drawing::Point(293, 104);
            this->btnEliminar->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
            this->btnEliminar->Name = L"btnEliminar";
            this->btnEliminar->Size = System::Drawing::Size(65, 24);
            this->btnEliminar->TabIndex = 22;
            this->btnEliminar->Text = L"Eliminar";
            this->btnEliminar->UseVisualStyleBackColor = true;
            this->btnEliminar->Click += gcnew System::EventHandler(this, &Usuarios::btnEliminar_Click);
            // 
            // btnCargaDatos
            // 
            this->btnCargaDatos->Location = System::Drawing::Point(560, 99);
            this->btnCargaDatos->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
            this->btnCargaDatos->Name = L"btnCargaDatos";
            this->btnCargaDatos->Size = System::Drawing::Size(75, 33);
            this->btnCargaDatos->TabIndex = 24;
            this->btnCargaDatos->Text = L"Carga de datos";
            this->btnCargaDatos->UseVisualStyleBackColor = true;
            // 
            // Usuarios
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(801, 460);
            this->Controls->Add(this->btnCargaDatos);
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
            this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
            this->Name = L"Usuarios";
            this->Text = L"Usuarios";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tblUsuarios))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private:
        System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
        }

        System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
        }

        System::Void lblApellido_Click(System::Object^ sender, System::EventArgs^ e) {
        }

        System::Void tblUsuarios_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
        {
            if (e->RowIndex >= 0 && e->RowIndex < tblUsuarios->Rows->Count) {
                DataGridViewRow^ fila = tblUsuarios->Rows[e->RowIndex];

                if (!fila->IsNewRow) {
                    int codigo = Convert::ToInt32(fila->Cells["colCodigo"]->Value);
                    userSeleccionado = -1;

                    for (int i = 0; i < usuarios->Count; i++)
                    {
                        if (usuarios[i] != nullptr && usuarios[i]->Codigo == codigo)
                        {
                            userSeleccionado = i;
                            break;
                        }
                    }

                    if (userSeleccionado != -1)
                    {
                        txtUsuario->Text = usuarios[userSeleccionado]->Username;
                        txtPassword->Text = usuarios[userSeleccionado]->Password;
                        txtNombre->Text = usuarios[userSeleccionado]->Nombre;
                        txtApellido->Text = usuarios[userSeleccionado]->Apellido;
                        txtCUI->Text = usuarios[userSeleccionado]->DPI;
                        txtTelefono->Text = usuarios[userSeleccionado]->Telefono;
                        txtEmail->Text = usuarios[userSeleccionado]->Email;
                        txtDireccion->Text = usuarios[userSeleccionado]->Direccion;
                        cboRol->SelectedItem = usuarios[userSeleccionado]->UserRole.ToString();
                    }
                }
            }
        }

        System::Void btnAgregar_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (estadoActual == ModoFormulario::Ninguno) {
                estadoActual = ModoFormulario::Agregar;
                ActualizarEstadoFormulario();
                ResetearFormulario();
            }
            else if (estadoActual == ModoFormulario::Agregar) {
                if (String::IsNullOrEmpty(txtUsuario->Text) ||
                    String::IsNullOrEmpty(txtPassword->Text) ||
                    String::IsNullOrEmpty(txtNombre->Text) ||
                    String::IsNullOrEmpty(txtApellido->Text) ||
                    String::IsNullOrEmpty(txtCUI->Text) ||
                    String::IsNullOrEmpty(txtTelefono->Text) ||
                    String::IsNullOrEmpty(txtEmail->Text) ||
                    String::IsNullOrEmpty(txtDireccion->Text) ||
                    cboRol->SelectedIndex == -1)
                {
                    MessageBox::Show("Por favor complete todos los campos", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }

                AgregarUsuario(
                    txtUsuario->Text,
                    txtPassword->Text,
                    txtNombre->Text,
                    txtApellido->Text,
                    txtCUI->Text,
                    txtTelefono->Text,
                    txtEmail->Text,
                    txtDireccion->Text,
                    (Role)Enum::Parse(Role::typeid, cboRol->SelectedItem->ToString())
                );

                estadoActual = ModoFormulario::Ninguno;
                ActualizarEstadoFormulario();
                ResetearFormulario();
            }
        }

        System::Void btnEliminar_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (estadoActual == ModoFormulario::Agregar || estadoActual == ModoFormulario::Editar) {
                estadoActual = ModoFormulario::Ninguno;
                ActualizarEstadoFormulario();
                ResetearFormulario();
                tblUsuarios->ClearSelection();
                userSeleccionado = -1;
                return;
            }

            if (userSeleccionado >= 0 && userSeleccionado < usuarios->Count && usuarios[userSeleccionado] != nullptr) {
                System::Windows::Forms::DialogResult result = MessageBox::Show(
                    "¿Estás seguro de que deseas eliminar este usuario?",
                    "Confirmar eliminación",
                    MessageBoxButtons::YesNo,
                    MessageBoxIcon::Warning
                );

                if (result == System::Windows::Forms::DialogResult::Yes) {
                    usuarios->RemoveAt(userSeleccionado);
                    MostrarUsuarios();
                    ResetearFormulario();
                    tblUsuarios->ClearSelection();
                    userSeleccionado = -1;
                }
            }
            else {
                MessageBox::Show("Seleccione un usuario válido para eliminar.");
            }
        }

        System::Void btnEditar_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (estadoActual == ModoFormulario::Ninguno) {
                if (userSeleccionado < 0 || userSeleccionado >= usuarios->Count || usuarios[userSeleccionado] == nullptr) {
                    MessageBox::Show("Seleccione un usuario válido para editar");
                    return;
                }
                estadoActual = ModoFormulario::Editar;
                ActualizarEstadoFormulario();
            }
            else if (estadoActual == ModoFormulario::Editar) {
                if (String::IsNullOrEmpty(txtUsuario->Text) ||
                    String::IsNullOrEmpty(txtPassword->Text) ||
                    String::IsNullOrEmpty(txtNombre->Text) ||
                    String::IsNullOrEmpty(txtApellido->Text) ||
                    String::IsNullOrEmpty(txtCUI->Text) ||
                    String::IsNullOrEmpty(txtTelefono->Text) ||
                    String::IsNullOrEmpty(txtEmail->Text) ||
                    String::IsNullOrEmpty(txtDireccion->Text) ||
                    cboRol->SelectedIndex == -1)
                {
                    MessageBox::Show("Por favor complete todos los campos", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }

                if (userSeleccionado >= 0 && userSeleccionado < usuarios->Count && usuarios[userSeleccionado] != nullptr) {
                    usuarios[userSeleccionado]->Username = txtUsuario->Text;
                    usuarios[userSeleccionado]->Password = txtPassword->Text;
                    usuarios[userSeleccionado]->Nombre = txtNombre->Text;
                    usuarios[userSeleccionado]->Apellido = txtApellido->Text;
                    usuarios[userSeleccionado]->DPI = txtCUI->Text;
                    usuarios[userSeleccionado]->Telefono = txtTelefono->Text;
                    usuarios[userSeleccionado]->Email = txtEmail->Text;
                    usuarios[userSeleccionado]->Direccion = txtDireccion->Text;
                    usuarios[userSeleccionado]->UserRole = (Role)Enum::Parse(Role::typeid, cboRol->SelectedItem->ToString());

                    MostrarUsuarios();
                    estadoActual = ModoFormulario::Ninguno;
                    ActualizarEstadoFormulario();
                    ResetearFormulario();
                }
            }
        }
    };
}