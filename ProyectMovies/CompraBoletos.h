#pragma once
#include "ClaseCompraBoletos.h"
#include "ClaseAsignacionPeliculasSalas.h"
#include "ClaseClientes.h"

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
		/*void AgregarCompraBoleto
		(
			AsignacionPeliculaSala^ asignacion,
			Cliente^ cliente,
			DateTime fechaCompra
		)
		{
			ultimoCodigo++;
			ComprasBoletos^ nuevaCompra = gcnew ComprasBoletos(ultimoCodigo, asignacion, cliente, fechaCompra);
			comprasBoletos[ultimoCodigo - 1] = nuevaCompra;
			MostrarComprasBoletos();
		}*/
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
			}
			else {
				btnAgregar->Text = "Agregar";
				btnEliminar->Text = "Eliminar";
				btnAgregar->Enabled = true;
				btnEliminar->Enabled = true;
			}
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
		System::ComponentModel::Container ^components;

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
			this->lblFecha = (gcnew System::Windows::Forms::Label());
			this->dateFecha = (gcnew System::Windows::Forms::DateTimePicker());
			this->btnAgregar = (gcnew System::Windows::Forms::Button());
			this->btnEliminar = (gcnew System::Windows::Forms::Button());
			this->panelAsientos = (gcnew System::Windows::Forms::Panel());
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
			this->btnAgregar->Location = System::Drawing::Point(482, 181);
			this->btnAgregar->Name = L"btnAgregar";
			this->btnAgregar->Size = System::Drawing::Size(112, 43);
			this->btnAgregar->TabIndex = 9;
			this->btnAgregar->Text = L"Agregar";
			this->btnAgregar->UseVisualStyleBackColor = true;
			this->btnAgregar->Click += gcnew System::EventHandler(this, &CompraBoletos::btnAgregar_Click);
			// 
			// btnEliminar
			// 
			this->btnEliminar->Location = System::Drawing::Point(632, 181);
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
			// CompraBoletos
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1684, 1031);
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
                // Cargar los datos en los controles
                // Seleccionar la función correspondiente en el ComboBox
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
                
                // Cambiar al modo de edición (si lo implementas)
                // estadoActual = ModoFormulario::Editar;
                // ActualizarEstadoFormulario();
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

};
}
