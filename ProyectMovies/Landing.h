#pragma once
#include "Peliculas.h"
#include "Salas.h"
#include "AsignacionPeliculasSalas.h"
#include "CompraBoletos.h"
#include "Clientes.h"
#include "Usuarios.h"
#include "ClaseUsuarios.h"

namespace ProyectMovies {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class Landing : public System::Windows::Forms::Form
    {
    private:
        // Instancias de formularios (ahora recibidas desde Login)
        Peliculas^ peliculas;
        Salas^ salas;
        AsignacionPeliculasSalas^ asignacionPeliculasSalas;
        CompraBoletos^ compraBoletos;
        Clientes^ clientes;
        Usuarios^ usuarios;

        // Datos del usuario actual
        User^ usuarioActual;
        System::Windows::Forms::Form^ ownerForm;

    public:
        /// <summary>
        /// Constructor modificado para recibir instancias de formularios
        /// </summary>
        Landing(User^ usuario, Peliculas^ pelis, Salas^ sal,
            AsignacionPeliculasSalas^ asign, CompraBoletos^ compra,
            Clientes^ cli, Usuarios^ users, System::Windows::Forms::Form^ owner)
        {
            usuarioActual = usuario;
            ownerForm = owner;

            // Asignar los formularios recibidos
            peliculas = pelis;
            salas = sal;
            asignacionPeliculasSalas = asign;
            compraBoletos = compra;
            clientes = cli;
            usuarios = users;

            InitializeComponent();
            ConfigurarVistaSegunRol();
        }

    protected:
        ~Landing()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;

        // Controles de la interfaz
        System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanelButtons;
        System::Windows::Forms::Panel^ panel1;
        System::Windows::Forms::PictureBox^ PictureLogo;
        System::Windows::Forms::Button^ btnPeliculas;
        System::Windows::Forms::Button^ btnSalas;
        System::Windows::Forms::Button^ btnAsignacionPeliculasSalas;
        System::Windows::Forms::Button^ btnCompraBoletos;
        System::Windows::Forms::Button^ btnClientes;
        System::Windows::Forms::Button^ btnUsuarios;
        System::Windows::Forms::Button^ btnCambiarUsuario;
        System::Windows::Forms::Label^ txtTitulo;
        System::Windows::Forms::Panel^ panelContenido;

        void ConfigurarVistaSegunRol()
        {
            if (usuarioActual->UserRole == Role::User)
            {
                // Ocultar botones de administración para usuarios normales
                btnPeliculas->Visible = false;
                btnSalas->Visible = false;
                btnAsignacionPeliculasSalas->Visible = false;
                btnUsuarios->Visible = false;

                // Reorganizar botones visibles
                btnCompraBoletos->Location = Point(3, 198);
                btnClientes->Location = Point(3, 274);
                btnCambiarUsuario->Location = Point(3, 350);
            }
            else
            {
                // Posiciones originales para admin
                btnCompraBoletos->Location = Point(3, 405);
                btnClientes->Location = Point(3, 461);
                btnCambiarUsuario->Location = Point(3, 573);
            }

            // Mostrar siempre el botón de cambiar usuario
            btnCambiarUsuario->Visible = true;
            btnCambiarUsuario->Text = "Cerrar sesión"; // Texto más claro

            // Personalizar mensaje de bienvenida
            txtTitulo->Text = String::Format("BIENVENIDO/A {0} {1}",
                usuarioActual->UserRole == Role::Admin ? "ADMIN" : "",
                usuarioActual->Nombre);
        }

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Landing::typeid));
            this->panelContenido = (gcnew System::Windows::Forms::Panel());
            this->flowLayoutPanelButtons = (gcnew System::Windows::Forms::FlowLayoutPanel());
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->PictureLogo = (gcnew System::Windows::Forms::PictureBox());
            this->btnPeliculas = (gcnew System::Windows::Forms::Button());
            this->btnSalas = (gcnew System::Windows::Forms::Button());
            this->btnAsignacionPeliculasSalas = (gcnew System::Windows::Forms::Button());
            this->btnCompraBoletos = (gcnew System::Windows::Forms::Button());
            this->btnClientes = (gcnew System::Windows::Forms::Button());
            this->btnUsuarios = (gcnew System::Windows::Forms::Button());
            this->btnCambiarUsuario = (gcnew System::Windows::Forms::Button());
            this->txtTitulo = (gcnew System::Windows::Forms::Label());
            this->flowLayoutPanelButtons->SuspendLayout();
            this->panel1->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureLogo))->BeginInit();
            this->SuspendLayout();
            // 
            // panelContenido
            // 
            this->panelContenido->Dock = System::Windows::Forms::DockStyle::Fill;
            this->panelContenido->Location = System::Drawing::Point(224, 0);
            this->panelContenido->Name = L"panelContenido";
            this->panelContenido->Size = System::Drawing::Size(1281, 965);
            this->panelContenido->TabIndex = 3;
            // 
            // flowLayoutPanelButtons
            // 
            this->flowLayoutPanelButtons->BackColor = System::Drawing::Color::LightSeaGreen;
            this->flowLayoutPanelButtons->Controls->Add(this->panel1);
            this->flowLayoutPanelButtons->Controls->Add(this->btnPeliculas);
            this->flowLayoutPanelButtons->Controls->Add(this->btnSalas);
            this->flowLayoutPanelButtons->Controls->Add(this->btnAsignacionPeliculasSalas);
            this->flowLayoutPanelButtons->Controls->Add(this->btnCompraBoletos);
            this->flowLayoutPanelButtons->Controls->Add(this->btnClientes);
            this->flowLayoutPanelButtons->Controls->Add(this->btnUsuarios);
            this->flowLayoutPanelButtons->Controls->Add(this->btnCambiarUsuario);
            this->flowLayoutPanelButtons->Dock = System::Windows::Forms::DockStyle::Left;
            this->flowLayoutPanelButtons->Location = System::Drawing::Point(0, 0);
            this->flowLayoutPanelButtons->Name = L"flowLayoutPanelButtons";
            this->flowLayoutPanelButtons->Size = System::Drawing::Size(224, 965);
            this->flowLayoutPanelButtons->TabIndex = 1;
            // 
            // panel1
            // 
            this->panel1->Controls->Add(this->PictureLogo);
            this->panel1->Location = System::Drawing::Point(3, 3);
            this->panel1->Name = L"panel1";
            this->panel1->Size = System::Drawing::Size(217, 240);
            this->panel1->TabIndex = 5;
            // 
            // PictureLogo
            // 
            this->PictureLogo->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PictureLogo.Image")));
            this->PictureLogo->Location = System::Drawing::Point(-3, -3);
            this->PictureLogo->Name = L"PictureLogo";
            this->PictureLogo->Size = System::Drawing::Size(220, 243);
            this->PictureLogo->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
            this->PictureLogo->TabIndex = 4;
            this->PictureLogo->TabStop = false;
            // 
            // btnPeliculas
            // 
            this->btnPeliculas->FlatAppearance->BorderSize = 0;
            this->btnPeliculas->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnPeliculas->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btnPeliculas->Location = System::Drawing::Point(3, 249);
            this->btnPeliculas->Name = L"btnPeliculas";
            this->btnPeliculas->Size = System::Drawing::Size(217, 62);
            this->btnPeliculas->TabIndex = 2;
            this->btnPeliculas->Text = L"Peliculas";
            this->btnPeliculas->UseVisualStyleBackColor = true;
            this->btnPeliculas->Click += gcnew System::EventHandler(this, &Landing::btnPeliculas_Click);
            // 
            // btnSalas
            // 
            this->btnSalas->FlatAppearance->BorderSize = 0;
            this->btnSalas->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnSalas->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btnSalas->Location = System::Drawing::Point(3, 344);
            this->btnSalas->Margin = System::Windows::Forms::Padding(3, 30, 3, 3);
            this->btnSalas->Name = L"btnSalas";
            this->btnSalas->Size = System::Drawing::Size(217, 62);
            this->btnSalas->TabIndex = 6;
            this->btnSalas->Text = L"Salas";
            this->btnSalas->UseVisualStyleBackColor = true;
            this->btnSalas->Click += gcnew System::EventHandler(this, &Landing::btnSalas_Click);
            // 
            // btnAsignacionPeliculasSalas
            // 
            this->btnAsignacionPeliculasSalas->FlatAppearance->BorderSize = 0;
            this->btnAsignacionPeliculasSalas->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnAsignacionPeliculasSalas->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular,
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->btnAsignacionPeliculasSalas->Location = System::Drawing::Point(3, 439);
            this->btnAsignacionPeliculasSalas->Margin = System::Windows::Forms::Padding(3, 30, 3, 3);
            this->btnAsignacionPeliculasSalas->Name = L"btnAsignacionPeliculasSalas";
            this->btnAsignacionPeliculasSalas->Size = System::Drawing::Size(217, 108);
            this->btnAsignacionPeliculasSalas->TabIndex = 7;
            this->btnAsignacionPeliculasSalas->Text = L"Asignacion de peliculas a salas";
            this->btnAsignacionPeliculasSalas->UseVisualStyleBackColor = true;
            this->btnAsignacionPeliculasSalas->Click += gcnew System::EventHandler(this, &Landing::btnAsignacionPeliculasSalas_Click);
            // 
            // btnCompraBoletos
            // 
            this->btnCompraBoletos->FlatAppearance->BorderSize = 0;
            this->btnCompraBoletos->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnCompraBoletos->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btnCompraBoletos->Location = System::Drawing::Point(3, 580);
            this->btnCompraBoletos->Margin = System::Windows::Forms::Padding(3, 30, 3, 3);
            this->btnCompraBoletos->Name = L"btnCompraBoletos";
            this->btnCompraBoletos->Size = System::Drawing::Size(217, 62);
            this->btnCompraBoletos->TabIndex = 8;
            this->btnCompraBoletos->Text = L"Compra boletos";
            this->btnCompraBoletos->UseVisualStyleBackColor = true;
            this->btnCompraBoletos->Click += gcnew System::EventHandler(this, &Landing::btnCompraBoletos_Click);
            // 
            // btnClientes
            // 
            this->btnClientes->FlatAppearance->BorderSize = 0;
            this->btnClientes->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnClientes->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btnClientes->Location = System::Drawing::Point(3, 675);
            this->btnClientes->Margin = System::Windows::Forms::Padding(3, 30, 3, 3);
            this->btnClientes->Name = L"btnClientes";
            this->btnClientes->Size = System::Drawing::Size(217, 62);
            this->btnClientes->TabIndex = 9;
            this->btnClientes->Text = L"Clientes";
            this->btnClientes->UseVisualStyleBackColor = true;
            this->btnClientes->Click += gcnew System::EventHandler(this, &Landing::btnClientes_Click);
            // 
            // btnUsuarios
            // 
            this->btnUsuarios->FlatAppearance->BorderSize = 0;
            this->btnUsuarios->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnUsuarios->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btnUsuarios->Location = System::Drawing::Point(3, 770);
            this->btnUsuarios->Margin = System::Windows::Forms::Padding(3, 30, 3, 3);
            this->btnUsuarios->Name = L"btnUsuarios";
            this->btnUsuarios->Size = System::Drawing::Size(217, 62);
            this->btnUsuarios->TabIndex = 10;
            this->btnUsuarios->Text = L"Usuarios";
            this->btnUsuarios->UseVisualStyleBackColor = true;
            this->btnUsuarios->Click += gcnew System::EventHandler(this, &Landing::btnUsuarios_Click);
            // 
            // btnCambiarUsuario
            // 
            this->btnCambiarUsuario->FlatAppearance->BorderSize = 0;
            this->btnCambiarUsuario->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnCambiarUsuario->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btnCambiarUsuario->Location = System::Drawing::Point(3, 865);
            this->btnCambiarUsuario->Margin = System::Windows::Forms::Padding(3, 30, 3, 3);
            this->btnCambiarUsuario->Name = L"btnCambiarUsuario";
            this->btnCambiarUsuario->Size = System::Drawing::Size(217, 62);
            this->btnCambiarUsuario->TabIndex = 11;
            this->btnCambiarUsuario->Text = L"Cerrar sesión";
            this->btnCambiarUsuario->UseVisualStyleBackColor = true;
            this->btnCambiarUsuario->Click += gcnew System::EventHandler(this, &Landing::btnCambiarUsuario_Click);
            // 
            // txtTitulo
            // 
            this->txtTitulo->AutoSize = true;
            this->txtTitulo->Font = (gcnew System::Drawing::Font(L"Segoe UI", 27.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->txtTitulo->Location = System::Drawing::Point(424, 243);
            this->txtTitulo->Name = L"txtTitulo";
            this->txtTitulo->Size = System::Drawing::Size(290, 50);
            this->txtTitulo->TabIndex = 2;
            this->txtTitulo->Text = L"BIENVENIDO/A";
            // 
            // Landing
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1505, 965);
            this->Controls->Add(this->panelContenido);
            this->Controls->Add(this->txtTitulo);
            this->Controls->Add(this->flowLayoutPanelButtons);
            this->Name = L"Landing";
            this->Text = L"Landing";
            this->flowLayoutPanelButtons->ResumeLayout(false);
            this->panel1->ResumeLayout(false);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureLogo))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private:
        System::Void btnPeliculas_Click(System::Object^ sender, System::EventArgs^ e) {
            AbrirFormulario(peliculas);
        }

        System::Void btnSalas_Click(System::Object^ sender, System::EventArgs^ e) {
            AbrirFormulario(salas);
        }

        System::Void btnAsignacionPeliculasSalas_Click(System::Object^ sender, System::EventArgs^ e) {
            // Actualizar listas antes de abrir (de la versión vieja)
            asignacionPeliculasSalas->ActualizarListas(
                peliculas->ObtenerPeliculasExistentes(),
                salas->ObtenerSalasExistentes()
            );
            AbrirFormulario(asignacionPeliculasSalas);
        }

        System::Void btnCompraBoletos_Click(System::Object^ sender, System::EventArgs^ e) {
            // Actualizar listas antes de abrir (de la versión vieja)
            compraBoletos->ActualizarListas(
                asignacionPeliculasSalas->ObtenerAsignacionesExistentes(),
                clientes->ObtenerClientesExistentes()
            );
            AbrirFormulario(compraBoletos);
        }

        System::Void btnClientes_Click(System::Object^ sender, System::EventArgs^ e) {
            AbrirFormulario(clientes);
        }

        System::Void btnUsuarios_Click(System::Object^ sender, System::EventArgs^ e) {
            if (usuarioActual->UserRole == Role::Admin) {
                AbrirFormulario(usuarios);
            }
            else {
                MessageBox::Show("Acceso restringido a administradores", "Permiso denegado",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }

        System::Void btnCambiarUsuario_Click(System::Object^ sender, System::EventArgs^ e) {
            // Cerrar este formulario para volver al Login
            this->Close();
        }

        void AbrirFormulario(System::Windows::Forms::Form^ formHijo)
        {
            if (this->panelContenido->Controls->Count > 0)
                this->panelContenido->Controls[0]->Hide();

            formHijo->TopLevel = false;
            formHijo->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            formHijo->Dock = DockStyle::Fill;
            this->panelContenido->Controls->Clear();
            this->panelContenido->Controls->Add(formHijo);
            formHijo->Show();
        }
    };
}