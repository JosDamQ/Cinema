#pragma once

#include "ClaseUsuarios.h"
#include "Usuarios.h"
#include "Landing.h"
#include "Peliculas.h"
#include "Salas.h"
#include "AsignacionPeliculasSalas.h"
#include "CompraBoletos.h"
#include "Clientes.h"

namespace ProyectMovies {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class Login : public System::Windows::Forms::Form
    {
    private:
        // Instancias de los formularios
        Peliculas^ peliculas;
        Salas^ salas;
        AsignacionPeliculasSalas^ asignacionPeliculasSalas;
        CompraBoletos^ compraBoletos;
        Clientes^ clientes;
        Usuarios^ usuarios;
        System::Collections::Generic::List<User^>^ users;

    public:
        // Método para obtener la lista de usuarios
        System::Collections::Generic::List<User^>^ GetUsersList()
        {
            return users;
        }

        Login(void)
        {
            InitializeComponent();
            CreateDefaultUsers();

            // Inicializar formularios pasando la lista de usuarios
            usuarios = gcnew Usuarios(GetUsersList());
            peliculas = gcnew Peliculas();
            salas = gcnew Salas();
            asignacionPeliculasSalas = gcnew AsignacionPeliculasSalas();
            compraBoletos = gcnew CompraBoletos();
            clientes = gcnew Clientes();
        }

    protected:
        ~Login()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;

        // Controles del formulario
        System::Windows::Forms::Label^ lblLogin;
        System::Windows::Forms::Label^ lblUsuario;
        System::Windows::Forms::TextBox^ txtUsuario;
        System::Windows::Forms::Label^ lblContrasena;
        System::Windows::Forms::TextBox^ txtContrasena;
        System::Windows::Forms::Button^ btnIngresar;
        System::Windows::Forms::Label^ lblMensaje;

        void CreateDefaultUsers()
        {
            users = gcnew System::Collections::Generic::List<User^>();

            // Usuario administrador por defecto
            users->Add(gcnew User(
                1,
                "admin",
                "admin123",
                "Administrador",
                "Sistema",
                "1234567890101",
                "12345678",
                "admin@proyectmovies.com",
                "Dirección Admin",
                Role::Admin
            ));

            // Usuario normal de ejemplo
            users->Add(gcnew User(
                2,
                "usuario",
                "user123",
                "Usuario",
                "Normal",
                "9876543210101",
                "87654321",
                "user@proyectmovies.com",
                "Dirección User",
                Role::User
            ));
        }

        bool ValidateUser(String^ username, String^ password)
        {
            for each (User ^ user in users)
            {
                if (user->Username->Equals(username) && user->Password->Equals(password))
                {
                    return true;
                }
            }
            return false;
        }

        User^ GetUser(String^ username)
        {
            for each (User ^ user in users)
            {
                if (user->Username->Equals(username))
                {
                    return user;
                }
            }
            return nullptr;
        }

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->lblLogin = (gcnew System::Windows::Forms::Label());
            this->lblUsuario = (gcnew System::Windows::Forms::Label());
            this->txtUsuario = (gcnew System::Windows::Forms::TextBox());
            this->lblContrasena = (gcnew System::Windows::Forms::Label());
            this->txtContrasena = (gcnew System::Windows::Forms::TextBox());
            this->btnIngresar = (gcnew System::Windows::Forms::Button());
            this->lblMensaje = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // lblLogin
            // 
            this->lblLogin->AutoSize = true;
            this->lblLogin->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->lblLogin->Location = System::Drawing::Point(120, 30);
            this->lblLogin->Name = L"lblLogin";
            this->lblLogin->Size = System::Drawing::Size(160, 24);
            this->lblLogin->TabIndex = 0;
            this->lblLogin->Text = L"INICIO DE SESIÓN";
            // 
            // lblUsuario
            // 
            this->lblUsuario->AutoSize = true;
            this->lblUsuario->Location = System::Drawing::Point(50, 80);
            this->lblUsuario->Name = L"lblUsuario";
            this->lblUsuario->Size = System::Drawing::Size(46, 13);
            this->lblUsuario->TabIndex = 1;
            this->lblUsuario->Text = L"Usuario:";
            // 
            // txtUsuario
            // 
            this->txtUsuario->Location = System::Drawing::Point(50, 100);
            this->txtUsuario->Name = L"txtUsuario";
            this->txtUsuario->Size = System::Drawing::Size(200, 20);
            this->txtUsuario->TabIndex = 2;
            // 
            // lblContrasena
            // 
            this->lblContrasena->AutoSize = true;
            this->lblContrasena->Location = System::Drawing::Point(50, 130);
            this->lblContrasena->Name = L"lblContrasena";
            this->lblContrasena->Size = System::Drawing::Size(64, 13);
            this->lblContrasena->TabIndex = 3;
            this->lblContrasena->Text = L"Contraseña:";
            // 
            // txtContrasena
            // 
            this->txtContrasena->Location = System::Drawing::Point(50, 150);
            this->txtContrasena->Name = L"txtContrasena";
            this->txtContrasena->PasswordChar = '*';
            this->txtContrasena->Size = System::Drawing::Size(200, 20);
            this->txtContrasena->TabIndex = 4;
            // 
            // btnIngresar
            // 
            this->btnIngresar->Location = System::Drawing::Point(100, 190);
            this->btnIngresar->Name = L"btnIngresar";
            this->btnIngresar->Size = System::Drawing::Size(100, 30);
            this->btnIngresar->TabIndex = 5;
            this->btnIngresar->Text = L"Ingresar";
            this->btnIngresar->UseVisualStyleBackColor = true;
            this->btnIngresar->Click += gcnew System::EventHandler(this, &Login::btnIngresar_Click);
            // 
            // lblMensaje
            // 
            this->lblMensaje->AutoSize = true;
            this->lblMensaje->ForeColor = System::Drawing::Color::Red;
            this->lblMensaje->Location = System::Drawing::Point(50, 230);
            this->lblMensaje->Name = L"lblMensaje";
            this->lblMensaje->Size = System::Drawing::Size(0, 13);
            this->lblMensaje->TabIndex = 6;
            // 
            // Login
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(300, 280);
            this->Controls->Add(this->lblMensaje);
            this->Controls->Add(this->btnIngresar);
            this->Controls->Add(this->txtContrasena);
            this->Controls->Add(this->lblContrasena);
            this->Controls->Add(this->txtUsuario);
            this->Controls->Add(this->lblUsuario);
            this->Controls->Add(this->lblLogin);
            this->Name = L"Login";
            this->Text = L"Inicio de Sesión";
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private: System::Void btnIngresar_Click(System::Object^ sender, System::EventArgs^ e)
    {
        String^ username = txtUsuario->Text;
        String^ password = txtContrasena->Text;

        if (String::IsNullOrEmpty(username) || String::IsNullOrEmpty(password))
        {
            lblMensaje->Text = "Por favor ingrese usuario y contraseña";
            return;
        }

        if (ValidateUser(username, password))
        {
            User^ loggedUser = GetUser(username);
            lblMensaje->ForeColor = Color::Green;
            lblMensaje->Text = String::Format("Bienvenido {0}", loggedUser->Nombre);

            // Ocultar el Login en lugar de cerrarlo
            this->Hide();

            // Crear y mostrar el Landing (pasando this como owner para poder volver)
            Landing^ landingForm = gcnew Landing(loggedUser, peliculas, salas,
                asignacionPeliculasSalas, compraBoletos, clientes, usuarios, this);
            landingForm->ShowDialog();

            // Cuando se cierre el Landing, mostrar el Login nuevamente
            this->Show();
            txtUsuario->Text = "";
            txtContrasena->Text = "";
            txtUsuario->Focus();
        }
        else
        {
            lblMensaje->ForeColor = Color::Red;
            lblMensaje->Text = "Usuario o contraseña incorrectos";
        }
    }
    };
}