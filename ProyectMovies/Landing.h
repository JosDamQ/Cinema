#pragma once
#include "Peliculas.h"
#include "Salas.h"
#include "AsignacionPeliculasSalas.h"
#include "CompraBoletos.h"
#include "Clientes.h"
#include "Usuarios.h"


namespace ProyectMovies {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Resumen de Landing
	/// </summary>
	public ref class Landing : public System::Windows::Forms::Form
	{
	public:
		Landing(void)
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
		~Landing()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanelButtons;
	protected:






	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::PictureBox^ PictureLogo;
	private: System::Windows::Forms::Button^ btnPeliculas;
	private: System::Windows::Forms::Button^ btnSalas;
	private: System::Windows::Forms::Button^ btnAsignacionPeliculasSalas;
	private: System::Windows::Forms::Button^ btnCompraBoletos;
	private: System::Windows::Forms::Button^ btnClientes;
	private: System::Windows::Forms::Button^ btnUsuarios;
	private: System::Windows::Forms::Label^ txtTitulo;




	protected:

	protected:

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Landing::typeid));
			this->flowLayoutPanelButtons = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->PictureLogo = (gcnew System::Windows::Forms::PictureBox());
			this->btnPeliculas = (gcnew System::Windows::Forms::Button());
			this->btnSalas = (gcnew System::Windows::Forms::Button());
			this->btnAsignacionPeliculasSalas = (gcnew System::Windows::Forms::Button());
			this->btnCompraBoletos = (gcnew System::Windows::Forms::Button());
			this->btnClientes = (gcnew System::Windows::Forms::Button());
			this->btnUsuarios = (gcnew System::Windows::Forms::Button());
			this->txtTitulo = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanelButtons->SuspendLayout();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureLogo))->BeginInit();
			this->SuspendLayout();
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
			this->flowLayoutPanelButtons->Dock = System::Windows::Forms::DockStyle::Left;
			this->flowLayoutPanelButtons->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanelButtons->Name = L"flowLayoutPanelButtons";
			this->flowLayoutPanelButtons->Size = System::Drawing::Size(224, 851);
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
			this->btnPeliculas->Dock = System::Windows::Forms::DockStyle::Top;
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
			this->btnSalas->Dock = System::Windows::Forms::DockStyle::Top;
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
			this->btnAsignacionPeliculasSalas->Dock = System::Windows::Forms::DockStyle::Top;
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
			this->btnCompraBoletos->Dock = System::Windows::Forms::DockStyle::Top;
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
			this->btnClientes->Dock = System::Windows::Forms::DockStyle::Top;
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
			this->btnUsuarios->Dock = System::Windows::Forms::DockStyle::Top;
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
			// txtTitulo
			// 
			this->txtTitulo->AutoSize = true;
			this->txtTitulo->Font = (gcnew System::Drawing::Font(L"Segoe UI", 27.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtTitulo->Location = System::Drawing::Point(424, 243);
			this->txtTitulo->Name = L"txtTitulo";
			this->txtTitulo->Size = System::Drawing::Size(436, 74);
			this->txtTitulo->TabIndex = 2;
			this->txtTitulo->Text = L"BIENVENIDO/A";
			// 
			// Landing
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1275, 851);
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
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	//Logica para ir a vista peliculas
	private: System::Void btnPeliculas_Click(System::Object^ sender, System::EventArgs^ e) {
		ProyectMovies::Peliculas^ formularioPeliculas = gcnew ProyectMovies::Peliculas();
		formularioPeliculas->Show(); // Usa ShowDialog() si quieres que sea modal
	}

	//Logica para ir a la vista de salas
	private: System::Void btnSalas_Click(System::Object^ sender, System::EventArgs^ e) {
		ProyectMovies::Salas^ formularioSalas = gcnew ProyectMovies::Salas();
		formularioSalas->Show(); // Usa ShowDialog() si quieres que sea modal
	}

	//Logica para ir a la vista de asignacion de peliculas a salas
	private: System::Void btnAsignacionPeliculasSalas_Click(System::Object^ sender, System::EventArgs^ e) {
		ProyectMovies::AsignacionPeliculasSalas^ formularioAsignacion = gcnew ProyectMovies::AsignacionPeliculasSalas();
		formularioAsignacion->Show(); // Usa ShowDialog() si quieres que sea modal
	}

	//Logica para ir a la vista de compra de boletos
	private: System::Void btnCompraBoletos_Click(System::Object^ sender, System::EventArgs^ e) {
		ProyectMovies::CompraBoletos^ formularioCompraBoletos = gcnew ProyectMovies::CompraBoletos();
		formularioCompraBoletos->Show(); // Usa ShowDialog() si quieres que sea modal
	}

	//Logica para ir a la vista de clientes
	private: System::Void btnClientes_Click(System::Object^ sender, System::EventArgs^ e) {
		ProyectMovies::Clientes^ formularioClientes = gcnew ProyectMovies::Clientes();
		formularioClientes->Show(); // Usa ShowDialog() si quieres que sea modal
	}

	//Logica para ir a la vista de usuarios
	private: System::Void btnUsuarios_Click(System::Object^ sender, System::EventArgs^ e) {
		ProyectMovies::Usuarios^ formularioUsuarios = gcnew ProyectMovies::Usuarios();
		formularioUsuarios->Show(); // Usa ShowDialog() si quieres que sea modal
	}

};
}
