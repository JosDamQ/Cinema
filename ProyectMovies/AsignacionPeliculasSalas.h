#pragma once
#include "ClaseAsignacionPeliculasSalas.h"
#include "ClasePelicula.h"
#include "ClaseSalas.h"

namespace ProyectMovies {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class AsignacionPeliculasSalas : public System::Windows::Forms::Form
	{
	private: 
		//Trear datos externos
		array<Pelicula^>^ listaPeliculas;
		array<Sala^>^ listaSalas;
		array<AsignacionPeliculaSala^>^ asignacionesPeliculasSalas;
		int ultimoCodigo;
		int asignacionSeleccionada;
	private: System::Windows::Forms::Label^ lblHora;
	private: System::Windows::Forms::TextBox^ txtHora;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colFechaHoraAsignacion;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colCapacidad;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colSala;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colIdioma;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colFormato;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colPelicula;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colCodigo;
	private: System::Windows::Forms::DataGridView^ tblAsignacionPeliculas;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colHora;

		enum class ModoFormulario {
			Ninguno,
			Agregar,
			Editar
		};

		ModoFormulario estadoActual = ModoFormulario::Ninguno;

	public:
		//Metodo combobox
		AsignacionPeliculasSalas(array<Pelicula^>^ peliculasExistentes, array<Sala^>^ salasExistentes) {
			InitializeComponent();
			this->listaPeliculas = peliculasExistentes;
			this->listaSalas = salasExistentes;
			CargarPeliculasComboBox();
			CargarSalasComboBox();

			asignacionesPeliculasSalas = gcnew array<AsignacionPeliculaSala^>(50);
			ultimoCodigo = 0;
			asignacionSeleccionada = -1;

			ActualizarEstadoFormulario();
			ResetearFormulario();
		}

		// Coso del comboBox
		void ActualizarListas(array<Pelicula^>^ peliculasActualizadas, array<Sala^>^ salasActualizadas) {
			this->listaPeliculas = peliculasActualizadas;
			this->listaSalas = salasActualizadas;
			CargarPeliculasComboBox();
			CargarSalasComboBox();
		}

		//Funcion de agregar
		void AgregarAsignacion
		(
			Pelicula^ pelicula,
			Sala^ sala,
			DateTime fechaHoraEstreno,
			String^ horaFuncion
		)
		{
			ultimoCodigo++;
			AsignacionPeliculaSala^ nuevaAsignacion = gcnew AsignacionPeliculaSala(ultimoCodigo, pelicula, sala, fechaHoraEstreno, horaFuncion);
			asignacionesPeliculasSalas[ultimoCodigo - 1] = nuevaAsignacion;
			MostrarAsignacion();
		}

		//Funcion de mostrar
		void MostrarAsignacion()
		{
			tblAsignacionPeliculas->Rows->Clear();
			for (int i = 0; i < ultimoCodigo; i++) {
				if (asignacionesPeliculasSalas[i] != nullptr) {
					tblAsignacionPeliculas->Rows -> Add(
						asignacionesPeliculasSalas[i]->Codigo,
						asignacionesPeliculasSalas[i]->PeliculaAsignada->Nombre,
						asignacionesPeliculasSalas[i]->PeliculaAsignada->FormatoPelicula.ToString(),
						asignacionesPeliculasSalas[i]->PeliculaAsignada->IdiomaPelicula.ToString(),
						asignacionesPeliculasSalas[i]->SalaAsignada->Nombre,
						asignacionesPeliculasSalas[i]->SalaAsignada->Capacidad.ToString(),
						asignacionesPeliculasSalas[i]->FechaEstreno.ToShortDateString(),
						asignacionesPeliculasSalas[i]->HoraFuncion
					);
				}
			}
		}

		//Resetear el formulario
		void ResetearFormulario()
		{
			cboPeliculas->SelectedIndex = -1;
			cboSala->SelectedIndex = -1;
			dateFechaAsignacion->ResetText();
			txtHora->Clear();
		}

		//Estado formulario
		void ActualizarEstadoFormulario()
		{
			bool habilitar = estadoActual != ModoFormulario::Ninguno;

			cboPeliculas->Enabled = habilitar;
			cboSala->Enabled = habilitar;
			dateFechaAsignacion->Enabled = habilitar;
			txtHora->Enabled = habilitar;

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

	protected:
		~AsignacionPeliculasSalas()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lblPelicula;
	protected:

	private: System::Windows::Forms::ComboBox^ cboPeliculas;
	private: System::Windows::Forms::Label^ lblSala;

	private: System::Windows::Forms::ComboBox^ cboSala;
	private: System::Windows::Forms::DateTimePicker^ dateFechaAsignacion;
	private: System::Windows::Forms::Label^ lblFechaHoraAsignacion;


	private: System::Windows::Forms::Button^ btnAgregar;
	private: System::Windows::Forms::Button^ btnEliminar;
	private: System::Windows::Forms::Button^ btnEditar;










	protected:

	protected:

	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		// para comboBox externo
		void CargarPeliculasComboBox() {
			this->cboPeliculas->Items->Clear();
			this->cboPeliculas->DisplayMember = "Nombre";
			for (int i = 0; i < listaPeliculas->Length; i++) {
				if (listaPeliculas[i] != nullptr) {
					cboPeliculas->Items->Add(listaPeliculas[i]);
				}
			}
		}

		void CargarSalasComboBox() {
			this->cboSala->Items->Clear();
			this->cboSala->DisplayMember = "Nombre";
			for (int i = 0; i < listaSalas->Length; i++) {
				if (listaSalas[i] != nullptr) {
					cboSala->Items->Add(listaSalas[i]);
				}
			}
		}


		void InitializeComponent(void)
		{
			this->lblPelicula = (gcnew System::Windows::Forms::Label());
			this->cboPeliculas = (gcnew System::Windows::Forms::ComboBox());
			this->lblSala = (gcnew System::Windows::Forms::Label());
			this->cboSala = (gcnew System::Windows::Forms::ComboBox());
			this->dateFechaAsignacion = (gcnew System::Windows::Forms::DateTimePicker());
			this->lblFechaHoraAsignacion = (gcnew System::Windows::Forms::Label());
			this->btnAgregar = (gcnew System::Windows::Forms::Button());
			this->btnEliminar = (gcnew System::Windows::Forms::Button());
			this->btnEditar = (gcnew System::Windows::Forms::Button());
			this->lblHora = (gcnew System::Windows::Forms::Label());
			this->txtHora = (gcnew System::Windows::Forms::TextBox());
			this->colFechaHoraAsignacion = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colCapacidad = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colSala = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colIdioma = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colFormato = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colPelicula = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colCodigo = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->tblAsignacionPeliculas = (gcnew System::Windows::Forms::DataGridView());
			this->colHora = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tblAsignacionPeliculas))->BeginInit();
			this->SuspendLayout();
			// 
			// lblPelicula
			// 
			this->lblPelicula->AutoSize = true;
			this->lblPelicula->Location = System::Drawing::Point(31, 38);
			this->lblPelicula->Name = L"lblPelicula";
			this->lblPelicula->Size = System::Drawing::Size(63, 20);
			this->lblPelicula->TabIndex = 0;
			this->lblPelicula->Text = L"Pelicula";
			// 
			// cboPeliculas
			// 
			this->cboPeliculas->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cboPeliculas->FormattingEnabled = true;
			this->cboPeliculas->Location = System::Drawing::Point(100, 35);
			this->cboPeliculas->Name = L"cboPeliculas";
			this->cboPeliculas->Size = System::Drawing::Size(121, 28);
			this->cboPeliculas->TabIndex = 1;
			// 
			// lblSala
			// 
			this->lblSala->AutoSize = true;
			this->lblSala->Location = System::Drawing::Point(251, 38);
			this->lblSala->Name = L"lblSala";
			this->lblSala->Size = System::Drawing::Size(41, 20);
			this->lblSala->TabIndex = 2;
			this->lblSala->Text = L"Sala";
			// 
			// cboSala
			// 
			this->cboSala->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cboSala->FormattingEnabled = true;
			this->cboSala->Location = System::Drawing::Point(298, 35);
			this->cboSala->Name = L"cboSala";
			this->cboSala->Size = System::Drawing::Size(121, 28);
			this->cboSala->TabIndex = 3;
			// 
			// dateFechaAsignacion
			// 
			this->dateFechaAsignacion->Location = System::Drawing::Point(645, 38);
			this->dateFechaAsignacion->Name = L"dateFechaAsignacion";
			this->dateFechaAsignacion->Size = System::Drawing::Size(296, 26);
			this->dateFechaAsignacion->TabIndex = 4;
			// 
			// lblFechaHoraAsignacion
			// 
			this->lblFechaHoraAsignacion->AutoSize = true;
			this->lblFechaHoraAsignacion->Location = System::Drawing::Point(449, 38);
			this->lblFechaHoraAsignacion->Name = L"lblFechaHoraAsignacion";
			this->lblFechaHoraAsignacion->Size = System::Drawing::Size(181, 20);
			this->lblFechaHoraAsignacion->TabIndex = 5;
			this->lblFechaHoraAsignacion->Text = L"Fecha y hora asignacion";
			// 
			// btnAgregar
			// 
			this->btnAgregar->Location = System::Drawing::Point(255, 122);
			this->btnAgregar->Name = L"btnAgregar";
			this->btnAgregar->Size = System::Drawing::Size(88, 31);
			this->btnAgregar->TabIndex = 6;
			this->btnAgregar->Text = L"Agregar";
			this->btnAgregar->UseVisualStyleBackColor = true;
			this->btnAgregar->Click += gcnew System::EventHandler(this, &AsignacionPeliculasSalas::btnAgregar_Click);
			// 
			// btnEliminar
			// 
			this->btnEliminar->Location = System::Drawing::Point(392, 122);
			this->btnEliminar->Name = L"btnEliminar";
			this->btnEliminar->Size = System::Drawing::Size(88, 31);
			this->btnEliminar->TabIndex = 7;
			this->btnEliminar->Text = L"Eliminar";
			this->btnEliminar->UseVisualStyleBackColor = true;
			this->btnEliminar->Click += gcnew System::EventHandler(this, &AsignacionPeliculasSalas::btnEliminar_Click);
			// 
			// btnEditar
			// 
			this->btnEditar->Location = System::Drawing::Point(523, 122);
			this->btnEditar->Name = L"btnEditar";
			this->btnEditar->Size = System::Drawing::Size(88, 31);
			this->btnEditar->TabIndex = 8;
			this->btnEditar->Text = L"Editar";
			this->btnEditar->UseVisualStyleBackColor = true;
			this->btnEditar->Click += gcnew System::EventHandler(this, &AsignacionPeliculasSalas::btnEditar_Click);
			// 
			// lblHora
			// 
			this->lblHora->AutoSize = true;
			this->lblHora->Location = System::Drawing::Point(995, 43);
			this->lblHora->Name = L"lblHora";
			this->lblHora->Size = System::Drawing::Size(44, 20);
			this->lblHora->TabIndex = 10;
			this->lblHora->Text = L"Hora";
			// 
			// txtHora
			// 
			this->txtHora->Location = System::Drawing::Point(1049, 43);
			this->txtHora->Name = L"txtHora";
			this->txtHora->Size = System::Drawing::Size(145, 26);
			this->txtHora->TabIndex = 11;
			// 
			// colFechaHoraAsignacion
			// 
			this->colFechaHoraAsignacion->HeaderText = L"Fecha y Hora estreno";
			this->colFechaHoraAsignacion->MinimumWidth = 8;
			this->colFechaHoraAsignacion->Name = L"colFechaHoraAsignacion";
			this->colFechaHoraAsignacion->Width = 150;
			// 
			// colCapacidad
			// 
			this->colCapacidad->HeaderText = L"Capacidad";
			this->colCapacidad->MinimumWidth = 8;
			this->colCapacidad->Name = L"colCapacidad";
			this->colCapacidad->Width = 150;
			// 
			// colSala
			// 
			this->colSala->HeaderText = L"Sala";
			this->colSala->MinimumWidth = 8;
			this->colSala->Name = L"colSala";
			this->colSala->Width = 150;
			// 
			// colIdioma
			// 
			this->colIdioma->HeaderText = L"Idioma";
			this->colIdioma->MinimumWidth = 8;
			this->colIdioma->Name = L"colIdioma";
			this->colIdioma->Width = 150;
			// 
			// colFormato
			// 
			this->colFormato->HeaderText = L"Formato";
			this->colFormato->MinimumWidth = 8;
			this->colFormato->Name = L"colFormato";
			this->colFormato->Width = 150;
			// 
			// colPelicula
			// 
			this->colPelicula->HeaderText = L"Pelicula";
			this->colPelicula->MinimumWidth = 8;
			this->colPelicula->Name = L"colPelicula";
			this->colPelicula->Width = 150;
			// 
			// colCodigo
			// 
			this->colCodigo->HeaderText = L"Codigo";
			this->colCodigo->MinimumWidth = 8;
			this->colCodigo->Name = L"colCodigo";
			this->colCodigo->Width = 150;
			// 
			// tblAsignacionPeliculas
			// 
			this->tblAsignacionPeliculas->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->tblAsignacionPeliculas->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(8) {
				this->colCodigo,
					this->colPelicula, this->colFormato, this->colIdioma, this->colSala, this->colCapacidad, this->colFechaHoraAsignacion, this->colHora
			});
			this->tblAsignacionPeliculas->Location = System::Drawing::Point(12, 201);
			this->tblAsignacionPeliculas->Name = L"tblAsignacionPeliculas";
			this->tblAsignacionPeliculas->RowHeadersWidth = 62;
			this->tblAsignacionPeliculas->RowTemplate->Height = 28;
			this->tblAsignacionPeliculas->Size = System::Drawing::Size(1238, 364);
			this->tblAsignacionPeliculas->TabIndex = 9;
			this->tblAsignacionPeliculas->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &AsignacionPeliculasSalas::tblAsignacionPeliculas_CellClick);
			// 
			// colHora
			// 
			this->colHora->HeaderText = L"HoraFuncion";
			this->colHora->MinimumWidth = 8;
			this->colHora->Name = L"colHora";
			this->colHora->Width = 150;
			// 
			// AsignacionPeliculasSalas
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1359, 663);
			this->Controls->Add(this->txtHora);
			this->Controls->Add(this->lblHora);
			this->Controls->Add(this->tblAsignacionPeliculas);
			this->Controls->Add(this->btnEditar);
			this->Controls->Add(this->btnEliminar);
			this->Controls->Add(this->btnAgregar);
			this->Controls->Add(this->lblFechaHoraAsignacion);
			this->Controls->Add(this->dateFechaAsignacion);
			this->Controls->Add(this->cboSala);
			this->Controls->Add(this->lblSala);
			this->Controls->Add(this->cboPeliculas);
			this->Controls->Add(this->lblPelicula);
			this->Name = L"AsignacionPeliculasSalas";
			this->Text = L"AsignacionPeliculasSalas";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tblAsignacionPeliculas))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		//Eventos
		private: System::Void tblAsignacionPeliculas_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
			if (e->RowIndex >= 0 && e->RowIndex < tblAsignacionPeliculas->Rows->Count) {
				DataGridViewRow^ fila = tblAsignacionPeliculas->Rows[e->RowIndex];

				if (!fila->IsNewRow) {
					asignacionSeleccionada = e->RowIndex;

					//cboPeliculas->SelectedItem = fila->Cells["colPelicula"]->Value;
					//cboSala->SelectedItem = fila->Cells["colSala"]->Value;
					
					String^ nombrePelicula = safe_cast<String^>(fila->Cells["colPelicula"]->Value);
					for each (Pelicula ^ p in cboPeliculas->Items) {
						if (p->Nombre->Equals(nombrePelicula)) {
							cboPeliculas->SelectedItem = p;
							break;
						}
					}

					String^ nombreSala = safe_cast<String^>(fila->Cells["colSala"]->Value);
					for each (Sala ^ s in cboSala->Items) {
						if (s->Nombre->Equals(nombreSala)) {
							cboSala->SelectedItem = s;
							break;
						}
					}
					//Fecha
					Object^ valorFecha = fila->Cells["colFechaHoraAsignacion"]->Value;
					if (valorFecha != nullptr && !String::IsNullOrWhiteSpace(valorFecha->ToString())) {
						DateTime fecha;
						if (DateTime::TryParse(valorFecha->ToString(), fecha)) {
							dateFechaAsignacion->Value = fecha;
						}
						else {
							// Opcional: manejar formato inválido
							MessageBox::Show("Formato de fecha inválido en la fila seleccionada.");
						}
					}
					else {
						// Opcional: asignar fecha por si esta nulo
						dateFechaAsignacion->Value = DateTime::Now;
					}

					//Hora
					Object^ valorHora = fila->Cells["colHora"]->Value->ToString();
					if (valorHora != nullptr && !String::IsNullOrWhiteSpace(valorHora->ToString())) {
						txtHora->Text = valorHora->ToString();
					}
					/*else {
						// Opcional: asignar hora por si esta nulo
						txtHora->Text = "";
					}*/

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
				if (cboPeliculas->SelectedIndex == -1 ||
					cboSala->SelectedIndex == -1 ||
					txtHora->Text->Trim() == "" ||
					dateFechaAsignacion->Value == DateTime::MinValue) {

					MessageBox::Show("Por favor, complete todos los campos.");
					return;
				}

				Pelicula^ peliculaSeleccionada = dynamic_cast<Pelicula^>(cboPeliculas->SelectedItem);
				Sala^ salaSeleccionada = dynamic_cast<Sala^>(cboSala->SelectedItem);
				DateTime fechaHoraEstreno = dateFechaAsignacion->Value;
				String^ horaFuncion = txtHora->Text;

				AgregarAsignacion(peliculaSeleccionada, salaSeleccionada, fechaHoraEstreno, horaFuncion);

				estadoActual = ModoFormulario::Ninguno;
				ActualizarEstadoFormulario();
				ResetearFormulario();
				tblAsignacionPeliculas->ClearSelection();
			}
		}
		private: System::Void btnEliminar_Click(System::Object^ sender, System::EventArgs^ e) {
			if (estadoActual == ModoFormulario::Agregar) {
				estadoActual = ModoFormulario::Ninguno;
				ActualizarEstadoFormulario();
				ResetearFormulario();
				tblAsignacionPeliculas->ClearSelection();
				asignacionSeleccionada = -1; // Resetear la selección
				return;
			}
			
			if (estadoActual == ModoFormulario::Editar) {
				estadoActual = ModoFormulario::Ninguno;
				ActualizarEstadoFormulario();
				ResetearFormulario();
				tblAsignacionPeliculas->ClearSelection();
				asignacionSeleccionada = -1; // Resetear la selección
				return;
			}

			if (asignacionSeleccionada >= 0 && asignacionSeleccionada < ultimoCodigo) {
				System::Windows::Forms::DialogResult result = System::Windows::Forms::MessageBox::Show(
					"¿Estás seguro de que deseas eliminar esta asignación?",
					"Confirmar eliminación",
					System::Windows::Forms::MessageBoxButtons::YesNo,
					System::Windows::Forms::MessageBoxIcon::Warning
				);

				if (result == System::Windows::Forms::DialogResult::Yes) {
					asignacionesPeliculasSalas[asignacionSeleccionada] = nullptr;
					MostrarAsignacion();
				}
				ResetearFormulario();
				tblAsignacionPeliculas->ClearSelection();

				asignacionSeleccionada = -1; // Resetear la selección
			}
			else {
				System::Windows::Forms::MessageBox::Show("Seleccione una asignación para eliminar.");
			}
		}
		private: System::Void btnEditar_Click(System::Object^ sender, System::EventArgs^ e) {
			if (estadoActual == ModoFormulario::Ninguno) {
				if (asignacionSeleccionada < 0 || asignacionSeleccionada >= ultimoCodigo || asignacionesPeliculasSalas[asignacionSeleccionada] == nullptr) {
					MessageBox::Show("Seleccione una asignación para editar.");
					return;
				}

				estadoActual = ModoFormulario::Editar;
				ActualizarEstadoFormulario();
			}

			else if (estadoActual == ModoFormulario::Editar) {
				if (cboPeliculas->SelectedIndex == -1 ||
					cboSala->SelectedIndex == -1 ||
					txtHora->Text->Trim() == "" ||
					dateFechaAsignacion->Value == DateTime::MinValue) {
					MessageBox::Show("Por favor, complete todos los campos.");
					return;
				}
				
				Pelicula^ peliculaSeleccionada = dynamic_cast<Pelicula^>(cboPeliculas->SelectedItem);
				Sala^ salaSeleccionada = dynamic_cast<Sala^>(cboSala->SelectedItem);
				DateTime fechaHoraEstreno = dateFechaAsignacion->Value;
				String^ horaFuncion = txtHora->Text;

				asignacionesPeliculasSalas[asignacionSeleccionada]->PeliculaAsignada = peliculaSeleccionada;
				asignacionesPeliculasSalas[asignacionSeleccionada]->SalaAsignada = salaSeleccionada;
				asignacionesPeliculasSalas[asignacionSeleccionada]->FechaEstreno = fechaHoraEstreno;
				asignacionesPeliculasSalas[asignacionSeleccionada]->HoraFuncion = horaFuncion;

				MostrarAsignacion();

				estadoActual = ModoFormulario::Ninguno;
				ActualizarEstadoFormulario();
				ResetearFormulario();
				tblAsignacionPeliculas->ClearSelection();
				asignacionSeleccionada = -1; // Resetear la selección
			}
		}
	};
}
