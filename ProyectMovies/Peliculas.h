#pragma once
#include "ClasePelicula.h"
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

    public ref class Peliculas : public System::Windows::Forms::Form
    {
    private:
        array<Pelicula^>^ peliculas;
        int ultimoCodigo;
        int peliculaSeleccionada;
    private: System::Windows::Forms::Button^ btnHTML;
    private: System::Windows::Forms::Button^ btnCargaDatos;

        enum class ModoFormulario {
            Ninguno,
            Agregar,
            Editar
        };

        ModoFormulario estadoActual = ModoFormulario::Ninguno;

    public:
        Peliculas(void)
        {
            InitializeComponent();
            CargarCombos();
            peliculas = gcnew array<Pelicula^>(50);
            ultimoCodigo = 0;
            peliculaSeleccionada = -1;

            ActualizarEstadoFormulario();
            ResetearFormulario();
        }

        // Funcion para cargar los combobox
        void CargarCombos()
        {
            // Cargar géneros
            this->cdoGenero->Items->Add(Genero::Accion.ToString());
            this->cdoGenero->Items->Add(Genero::Aventura.ToString());
            this->cdoGenero->Items->Add(Genero::Ficcion.ToString());
            this->cdoGenero->Items->Add(Genero::Comedia.ToString());
            this->cdoGenero->Items->Add(Genero::Drama.ToString());
            this->cdoGenero->Items->Add(Genero::Documental.ToString());

            // Cargar clasificaciones
            this->cdoClasificacion->Items->Add(Clasificacion::A14.ToString());
            this->cdoClasificacion->Items->Add(Clasificacion::A18.ToString());
            this->cdoClasificacion->Items->Add(Clasificacion::PA.ToString());

            // Cargar idiomas
            this->cdoIdioma->Items->Add(Idioma::Doblada.ToString());
            this->cdoIdioma->Items->Add(Idioma::Subtitulada.ToString());

            // Cargar formatos
            this->cdoFormato->Items->Add(Formato::Formato2D.ToString());
            this->cdoFormato->Items->Add(Formato::Formato3D.ToString());
            this->cdoFormato->Items->Add(Formato::Digital.ToString());

            // Cargar estados
            this->cdoEstado->Items->Add(Estado::Activo.ToString());
            this->cdoEstado->Items->Add(Estado::Inactivo.ToString());

            // Configurar para que no se pueda escribir en los combos
            this->cdoGenero->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cdoClasificacion->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cdoIdioma->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cdoFormato->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cdoEstado->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
        }

        // Funcion de agregar
        void AgregarPelicula(
            String^ nombre,
            Genero genero,
            Clasificacion clasificacion,
            Idioma idioma,
            Formato formato,
            String^ precio,
            Estado estado
        )
        {
			ultimoCodigo++;
            Pelicula^ nuevaPelicula = gcnew Pelicula(
                ultimoCodigo, nombre, genero, clasificacion, idioma, formato, precio, estado
            );
            peliculas[ultimoCodigo - 1] = nuevaPelicula;
            //ultimoCodigo++;
            MostrarPeliculas();
        }

        // Funcion de mostrar
        void MostrarPeliculas()
        {
            tblPelicula->Rows->Clear();
            for (int i = 0; i < ultimoCodigo; i++) {
                if (peliculas[i] != nullptr) {
                    Pelicula^ p = peliculas[i];
                    tblPelicula->Rows->Add(
                        //i + 1, // Código autoincremental
						/*peliculas[i]->Codigo,
                        peliculas[i]->Nombre,
                        peliculas[i]->GeneroPelicula.ToString(),
                        peliculas[i]->ClasificacionPelicula.ToString(),
                        peliculas[i]->IdiomaPelicula.ToString(),
                        peliculas[i]->FormatoPelicula.ToString(),
                        peliculas[i]->Precio,
                        peliculas[i]->EstadoPelicula.ToString()*/
                        p->Codigo,
                        p->Nombre,
                        p->GeneroPelicula.ToString(),
                        p->ClasificacionPelicula.ToString(),
                        p->IdiomaPelicula.ToString(),
                        p->FormatoPelicula.ToString(),
                        p->Precio,
                        p->EstadoPelicula.ToString()
                    );
                }
            }
        }

        // Resetear el formulario
        void ResetearFormulario()
        {
            txtNombre->Clear();
            txtPrecio->Clear();
            cdoGenero->SelectedIndex = -1;
            cdoClasificacion->SelectedIndex = -1;
            cdoIdioma->SelectedIndex = -1;
            cdoFormato->SelectedIndex = -1;
            cdoEstado->SelectedIndex = -1;
        }

        //Estado formulario
        void ActualizarEstadoFormulario() {
            bool habilitar = estadoActual != ModoFormulario::Ninguno;

            txtNombre->Enabled = habilitar;
            txtPrecio->Enabled = habilitar;
            cdoGenero->Enabled = habilitar;
            cdoClasificacion->Enabled = habilitar;
            cdoIdioma->Enabled = habilitar;
            cdoFormato->Enabled = habilitar;
            cdoEstado->Enabled = habilitar;

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
        

		//Cargar comboBox
        /*array<Pelicula^>^ ObtenerPeliculasExistentes()
        {
			return peliculas;
        }*/
        array<Pelicula^>^ ObtenerPeliculasExistentes()
        {
            int cantidadActivas = 0;
            for (int i = 0; i < peliculas->Length; i++) {
                if (peliculas[i] != nullptr && peliculas[i]->EstadoPelicula == Estado::Activo) {
                    cantidadActivas++;
                }
            }

            array<Pelicula^>^ activas = gcnew array<Pelicula^>(cantidadActivas);
            int idx = 0;
            for (int i = 0; i < peliculas->Length; i++) {
                if (peliculas[i] != nullptr && peliculas[i]->EstadoPelicula == Estado::Activo) {
                    activas[idx++] = peliculas[i];
                }
            }

            return activas;
        }
        private:
            void GenerarReporteHTML()
            {
                if (tblPelicula->Rows->Count == 0) {
                    MessageBox::Show("No hay películas para generar el reporte.",
                        "Información", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    return;
                }

                // Preparar los datos para el reporte
                array<String^>^ encabezados = gcnew array<String^> {
                    "Código", "Nombre", "Género", "Clasificación", "Idioma", "Formato", "Precio", "Estado"
                };

                // Crear lista de datos basada en el DataGridView
                System::Collections::Generic::List<array<String^>^>^ datosLista = gcnew System::Collections::Generic::List<array<String^>^>();

                for each (DataGridViewRow ^ fila in tblPelicula->Rows)
                {
                    if (!fila->IsNewRow)
                    {
                        array<String^>^ filaDatos = gcnew array<String^> {
                            fila->Cells["colCodigo"]->Value == nullptr ? "" : fila->Cells["colCodigo"]->Value->ToString(),
                                fila->Cells["colNombre"]->Value == nullptr ? "" : fila->Cells["colNombre"]->Value->ToString(),
                                fila->Cells["colGenero"]->Value == nullptr ? "" : fila->Cells["colGenero"]->Value->ToString(),
                                fila->Cells["colClasificacion"]->Value == nullptr ? "" : fila->Cells["colClasificacion"]->Value->ToString(),
                                fila->Cells["colIdioma"]->Value == nullptr ? "" : fila->Cells["colIdioma"]->Value->ToString(),
                                fila->Cells["colFormato"]->Value == nullptr ? "" : fila->Cells["colFormato"]->Value->ToString(),
                                fila->Cells["colPrecio"]->Value == nullptr ? "" : fila->Cells["colPrecio"]->Value->ToString(),
                                fila->Cells["colEstado"]->Value == nullptr ? "" : fila->Cells["colEstado"]->Value->ToString()
                        };
                        datosLista->Add(filaDatos);
                    }
                }

                // Convertir la lista a array para el reporte
                array<array<String^>^>^ datos = datosLista->ToArray();

                // Generar el reporte usando la clase general
                GeneradorReporte::GenerarReporte(
                    "Reporte de Películas",
                    "Listado de Películas Registradas",
                    "Sistema de Gestión de Películas - ProyectMovies",
                    encabezados,
                    datos,
                    "ReportePeliculas");
            }




    protected:
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
    private: System::Windows::Forms::Button^ btnAgregar;
    private: System::Windows::Forms::Button^ btnEditar;
    private: System::Windows::Forms::Button^ btnEliminar;

    private:
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
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
            this->btnAgregar = (gcnew System::Windows::Forms::Button());
            this->btnEditar = (gcnew System::Windows::Forms::Button());
            this->btnEliminar = (gcnew System::Windows::Forms::Button());
            this->btnHTML = (gcnew System::Windows::Forms::Button());
            this->btnCargaDatos = (gcnew System::Windows::Forms::Button());
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
            this->tblPelicula->Location = System::Drawing::Point(30, 231);
            this->tblPelicula->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->tblPelicula->Name = L"tblPelicula";
            this->tblPelicula->RowHeadersWidth = 51;
            this->tblPelicula->RowTemplate->Height = 24;
            this->tblPelicula->Size = System::Drawing::Size(1186, 328);
            this->tblPelicula->TabIndex = 1;
            this->tblPelicula->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Peliculas::tblPelicula_CellClick);
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
            this->txtNombre->Location = System::Drawing::Point(97, 28);
            this->txtNombre->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->txtNombre->Name = L"txtNombre";
            this->txtNombre->Size = System::Drawing::Size(193, 26);
            this->txtNombre->TabIndex = 2;
            // 
            // lblNombre
            // 
            this->lblNombre->AutoSize = true;
            this->lblNombre->Location = System::Drawing::Point(27, 31);
            this->lblNombre->Name = L"lblNombre";
            this->lblNombre->Size = System::Drawing::Size(65, 20);
            this->lblNombre->TabIndex = 3;
            this->lblNombre->Text = L"Nombre";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(540, 102);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(53, 20);
            this->label1->TabIndex = 5;
            this->label1->Text = L"Precio";
            // 
            // txtPrecio
            // 
            this->txtPrecio->Location = System::Drawing::Point(610, 99);
            this->txtPrecio->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->txtPrecio->Name = L"txtPrecio";
            this->txtPrecio->Size = System::Drawing::Size(112, 26);
            this->txtPrecio->TabIndex = 4;
            // 
            // cdoGenero
            // 
            this->cdoGenero->FormattingEnabled = true;
            this->cdoGenero->Location = System::Drawing::Point(362, 25);
            this->cdoGenero->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->cdoGenero->Name = L"cdoGenero";
            this->cdoGenero->Size = System::Drawing::Size(168, 28);
            this->cdoGenero->TabIndex = 6;
            // 
            // lblGenero
            // 
            this->lblGenero->AutoSize = true;
            this->lblGenero->Location = System::Drawing::Point(297, 31);
            this->lblGenero->Name = L"lblGenero";
            this->lblGenero->Size = System::Drawing::Size(63, 20);
            this->lblGenero->TabIndex = 7;
            this->lblGenero->Text = L"Genero";
            // 
            // lblClasificacion
            // 
            this->lblClasificacion->AutoSize = true;
            this->lblClasificacion->Location = System::Drawing::Point(534, 34);
            this->lblClasificacion->Name = L"lblClasificacion";
            this->lblClasificacion->Size = System::Drawing::Size(97, 20);
            this->lblClasificacion->TabIndex = 9;
            this->lblClasificacion->Text = L"Clasificacion";
            // 
            // cdoClasificacion
            // 
            this->cdoClasificacion->FormattingEnabled = true;
            this->cdoClasificacion->Location = System::Drawing::Point(634, 31);
            this->cdoClasificacion->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->cdoClasificacion->Name = L"cdoClasificacion";
            this->cdoClasificacion->Size = System::Drawing::Size(168, 28);
            this->cdoClasificacion->TabIndex = 8;
            // 
            // lblFormato
            // 
            this->lblFormato->AutoSize = true;
            this->lblFormato->Location = System::Drawing::Point(26, 101);
            this->lblFormato->Name = L"lblFormato";
            this->lblFormato->Size = System::Drawing::Size(69, 20);
            this->lblFormato->TabIndex = 11;
            this->lblFormato->Text = L"Formato";
            // 
            // cdoFormato
            // 
            this->cdoFormato->FormattingEnabled = true;
            this->cdoFormato->Location = System::Drawing::Point(97, 99);
            this->cdoFormato->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->cdoFormato->Name = L"cdoFormato";
            this->cdoFormato->Size = System::Drawing::Size(168, 28);
            this->cdoFormato->TabIndex = 10;
            // 
            // lblIdioma
            // 
            this->lblIdioma->AutoSize = true;
            this->lblIdioma->Location = System::Drawing::Point(272, 106);
            this->lblIdioma->Name = L"lblIdioma";
            this->lblIdioma->Size = System::Drawing::Size(57, 20);
            this->lblIdioma->TabIndex = 13;
            this->lblIdioma->Text = L"Idioma";
            // 
            // cdoIdioma
            // 
            this->cdoIdioma->FormattingEnabled = true;
            this->cdoIdioma->Location = System::Drawing::Point(356, 101);
            this->cdoIdioma->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->cdoIdioma->Name = L"cdoIdioma";
            this->cdoIdioma->Size = System::Drawing::Size(168, 28);
            this->cdoIdioma->TabIndex = 12;
            // 
            // lblEstado
            // 
            this->lblEstado->AutoSize = true;
            this->lblEstado->Location = System::Drawing::Point(32, 156);
            this->lblEstado->Name = L"lblEstado";
            this->lblEstado->Size = System::Drawing::Size(60, 20);
            this->lblEstado->TabIndex = 15;
            this->lblEstado->Text = L"Estado";
            // 
            // cdoEstado
            // 
            this->cdoEstado->FormattingEnabled = true;
            this->cdoEstado->Location = System::Drawing::Point(132, 154);
            this->cdoEstado->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->cdoEstado->Name = L"cdoEstado";
            this->cdoEstado->Size = System::Drawing::Size(168, 28);
            this->cdoEstado->TabIndex = 14;
            // 
            // btnAgregar
            // 
            this->btnAgregar->Location = System::Drawing::Point(382, 156);
            this->btnAgregar->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->btnAgregar->Name = L"btnAgregar";
            this->btnAgregar->Size = System::Drawing::Size(110, 46);
            this->btnAgregar->TabIndex = 20;
            this->btnAgregar->Text = L"Agregar";
            this->btnAgregar->UseVisualStyleBackColor = true;
            this->btnAgregar->Click += gcnew System::EventHandler(this, &Peliculas::btnAgregar_Click);
            // 
            // btnEditar
            // 
            this->btnEditar->Location = System::Drawing::Point(717, 156);
            this->btnEditar->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->btnEditar->Name = L"btnEditar";
            this->btnEditar->Size = System::Drawing::Size(110, 46);
            this->btnEditar->TabIndex = 21;
            this->btnEditar->Text = L"Editar";
            this->btnEditar->UseVisualStyleBackColor = true;
            this->btnEditar->Click += gcnew System::EventHandler(this, &Peliculas::btnEditar_Click);
            // 
            // btnEliminar
            // 
            this->btnEliminar->Location = System::Drawing::Point(544, 156);
            this->btnEliminar->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->btnEliminar->Name = L"btnEliminar";
            this->btnEliminar->Size = System::Drawing::Size(110, 46);
            this->btnEliminar->TabIndex = 22;
            this->btnEliminar->Text = L"Eliminar";
            this->btnEliminar->UseVisualStyleBackColor = true;
            this->btnEliminar->Click += gcnew System::EventHandler(this, &Peliculas::btnEliminar_Click);
            // 
            // btnHTML
            // 
            this->btnHTML->Location = System::Drawing::Point(892, 156);
            this->btnHTML->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->btnHTML->Name = L"btnHTML";
            this->btnHTML->Size = System::Drawing::Size(110, 46);
            this->btnHTML->TabIndex = 23;
            this->btnHTML->Text = L"HTML";
            this->btnHTML->UseVisualStyleBackColor = true;
            this->btnHTML->Click += gcnew System::EventHandler(this, &Peliculas::btnHTML_Click);
            // 
            // btnCargaDatos
            // 
            this->btnCargaDatos->Location = System::Drawing::Point(1042, 149);
            this->btnCargaDatos->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->btnCargaDatos->Name = L"btnCargaDatos";
            this->btnCargaDatos->Size = System::Drawing::Size(119, 60);
            this->btnCargaDatos->TabIndex = 24;
            this->btnCargaDatos->Text = L"Carga de datos";
            this->btnCargaDatos->UseVisualStyleBackColor = true;
            // 
            // Peliculas
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1380, 612);
            this->Controls->Add(this->btnCargaDatos);
            this->Controls->Add(this->btnHTML);
            this->Controls->Add(this->btnEliminar);
            this->Controls->Add(this->btnEditar);
            this->Controls->Add(this->btnAgregar);
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
            this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->Name = L"Peliculas";
            this->Text = L"Peliculas";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tblPelicula))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void Peliculas_Load(System::Object^ sender, System::EventArgs^ e) {
    }

    private: System::Void tblPelicula_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
        if (e->RowIndex >= 0 && e->RowIndex < tblPelicula->Rows->Count) {
            DataGridViewRow^ fila = tblPelicula->Rows[e->RowIndex];

            if (!fila->IsNewRow) {
                txtNombre->Text = fila->Cells["colNombre"]->Value->ToString();
                txtPrecio->Text = fila->Cells["colPrecio"]->Value->ToString();

                // Configurar los combobox con los valores de la fila seleccionada
                cdoGenero->SelectedItem = fila->Cells["colGenero"]->Value;
                cdoClasificacion->SelectedItem = fila->Cells["colClasificacion"]->Value;
                cdoIdioma->SelectedItem = fila->Cells["colIdioma"]->Value;
                cdoFormato->SelectedItem = fila->Cells["colFormato"]->Value;
                cdoEstado->SelectedItem = fila->Cells["colEstado"]->Value;

                //peliculaSeleccionada = e->RowIndex;

                // Cambio Update
                peliculaSeleccionada = Convert::ToInt32(fila->Cells["colCodigo"]->Value);
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
            // Validar campos
            if (txtNombre->Text->Trim() == "" ||
                txtPrecio->Text->Trim() == "" ||
                cdoGenero->SelectedIndex == -1 ||
                cdoClasificacion->SelectedIndex == -1 ||
                cdoIdioma->SelectedIndex == -1 ||
                cdoFormato->SelectedIndex == -1 ||
                cdoEstado->SelectedIndex == -1) {

                MessageBox::Show("Por favor complete todos los campos antes de agregar la película.",
                    "Campos incompletos",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return;
            }

            // Validar que el precio no esté vacío
            if (String::IsNullOrEmpty(txtPrecio->Text)) {
                MessageBox::Show("Por favor ingrese un precio válido.",
                    "Precio inválido",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return;
            }

            String^ nombre = txtNombre->Text;
            Genero genero = (Genero)Enum::Parse(Genero::typeid, cdoGenero->SelectedItem->ToString());
            Clasificacion clasificacion = (Clasificacion)Enum::Parse(Clasificacion::typeid, cdoClasificacion->SelectedItem->ToString());
            Idioma idioma = (Idioma)Enum::Parse(Idioma::typeid, cdoIdioma->SelectedItem->ToString());
            Formato formato = (Formato)Enum::Parse(Formato::typeid, cdoFormato->SelectedItem->ToString());
            String^ precio = txtPrecio->Text;
            Estado estado = (Estado)Enum::Parse(Estado::typeid, cdoEstado->SelectedItem->ToString());

            AgregarPelicula(nombre, genero, clasificacion, idioma, formato, precio, estado);

            estadoActual = ModoFormulario::Ninguno;
            ActualizarEstadoFormulario();
            ResetearFormulario();
            tblPelicula->ClearSelection();
        }
    }

    private: System::Void btnEliminar_Click(System::Object^ sender, System::EventArgs^ e) {
        if (estadoActual == ModoFormulario::Agregar) {
            estadoActual = ModoFormulario::Ninguno;
            ActualizarEstadoFormulario();
            ResetearFormulario();
            tblPelicula->ClearSelection();
            peliculaSeleccionada = -1;
            return;
        }

        if (estadoActual == ModoFormulario::Editar) {
            estadoActual = ModoFormulario::Ninguno;
            ActualizarEstadoFormulario();
            ResetearFormulario();
            tblPelicula->ClearSelection();
            peliculaSeleccionada = -1;
            return;
        }

        if (peliculaSeleccionada >= 0 && peliculaSeleccionada < ultimoCodigo) {
            System::Windows::Forms::DialogResult result = System::Windows::Forms::MessageBox::Show(
                "¿Estás seguro de que deseas eliminar esta película?",
                "Confirmar eliminación",
                System::Windows::Forms::MessageBoxButtons::YesNo,
                System::Windows::Forms::MessageBoxIcon::Warning
            );

            if (result == System::Windows::Forms::DialogResult::Yes) {
                // Mover todas las películas posteriores una posición hacia atrás
                /*for (int i = peliculaSeleccionada; i < ultimoCodigo - 1; i++) {
                    peliculas[i] = peliculas[i + 1];
                }
                peliculas[ultimoCodigo - 1] = nullptr;
                ultimoCodigo--;
                MostrarPeliculas();*/
                peliculas[peliculaSeleccionada] = nullptr;
                MostrarPeliculas();
            }
            /*ResetearFormulario();
            tblPelicula->ClearSelection();
            peliculaSeleccionada = -1;*/

			ResetearFormulario();
			tblPelicula->ClearSelection();
            peliculaSeleccionada = -1; // Resetear la selección
        }
        else {
            System::Windows::Forms::MessageBox::Show("Seleccione una película para eliminar.");
        }
    }

    private: System::Void btnEditar_Click(System::Object^ sender, System::EventArgs^ e) {
        if (estadoActual == ModoFormulario::Ninguno) {
            bool encontrada = false;
            for (int i = 0; i < ultimoCodigo; i++) {
                if (peliculas[i] != nullptr && peliculas[i]->Codigo == peliculaSeleccionada) {
                    encontrada = true;
                    break;
                }
            }
            if (!encontrada) {
                MessageBox::Show("Seleccione una película para editar.");
                return;
            }
            /*if (peliculaSeleccionada < 0 || peliculaSeleccionada >= ultimoCodigo || peliculas[peliculaSeleccionada] == nullptr) {
                MessageBox::Show("Seleccione una película para editar.");
                return;
            }*/

            estadoActual = ModoFormulario::Editar;
            ActualizarEstadoFormulario();
        }
        else if (estadoActual == ModoFormulario::Editar) {
            // Validar campos
            if (txtNombre->Text->Trim() == "" ||
                txtPrecio->Text->Trim() == "" ||
                cdoGenero->SelectedIndex == -1 ||
                cdoClasificacion->SelectedIndex == -1 ||
                cdoIdioma->SelectedIndex == -1 ||
                cdoFormato->SelectedIndex == -1 ||
                cdoEstado->SelectedIndex == -1) {

                MessageBox::Show("Por favor complete todos los campos antes de confirmar la edición.",
                    "Campos incompletos",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return;
            }

            // Validar que el precio no esté vacío
            if (String::IsNullOrEmpty(txtPrecio->Text)) {
                MessageBox::Show("Por favor ingrese un precio válido.",
                    "Precio inválido",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return;
            }

            String^ nombre = txtNombre->Text;
            Genero genero = (Genero)Enum::Parse(Genero::typeid, cdoGenero->SelectedItem->ToString());
            Clasificacion clasificacion = (Clasificacion)Enum::Parse(Clasificacion::typeid, cdoClasificacion->SelectedItem->ToString());
            Idioma idioma = (Idioma)Enum::Parse(Idioma::typeid, cdoIdioma->SelectedItem->ToString());
            Formato formato = (Formato)Enum::Parse(Formato::typeid, cdoFormato->SelectedItem->ToString());
            String^ precio = txtPrecio->Text;
            Estado estado = (Estado)Enum::Parse(Estado::typeid, cdoEstado->SelectedItem->ToString());

            for (int i = 0; i < ultimoCodigo; i++) {
                if (peliculas[i] != nullptr && peliculas[i]->Codigo == peliculaSeleccionada) {
                    peliculas[i]->Nombre = nombre;
                    peliculas[i]->GeneroPelicula = genero;
                    peliculas[i]->ClasificacionPelicula = clasificacion;
                    peliculas[i]->IdiomaPelicula = idioma;
                    peliculas[i]->FormatoPelicula = formato;
                    peliculas[i]->Precio = precio;
                    peliculas[i]->EstadoPelicula = estado;
                    break;
                }
            }

            //// Actualizar la película seleccionada
            //peliculas[peliculaSeleccionada]->Nombre = nombre;
            //peliculas[peliculaSeleccionada]->GeneroPelicula = genero;
            //peliculas[peliculaSeleccionada]->ClasificacionPelicula = clasificacion;
            //peliculas[peliculaSeleccionada]->IdiomaPelicula = idioma;
            //peliculas[peliculaSeleccionada]->FormatoPelicula = formato;
            //peliculas[peliculaSeleccionada]->Precio = precio;
            //peliculas[peliculaSeleccionada]->EstadoPelicula = estado;

            MostrarPeliculas();

            estadoActual = ModoFormulario::Ninguno;
            ActualizarEstadoFormulario();
            ResetearFormulario();
            tblPelicula->ClearSelection();
            peliculaSeleccionada = -1;
        }
    }
    private: System::Void btnHTML_Click(System::Object^ sender, System::EventArgs^ e) {
        if (ultimoCodigo == 0) {
            MessageBox::Show("No hay películas para generar el reporte.",
                "Información", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }

        GenerarReporteHTML();
    }
    };
}