#pragma once

namespace ProyectMovies {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de AsignacionPeliculasSalas
	/// </summary>
	public ref class AsignacionPeliculasSalas : public System::Windows::Forms::Form
	{
	public:
		AsignacionPeliculasSalas(void)
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
		~AsignacionPeliculasSalas()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(95, 55);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(399, 30);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Vista asignacion de peliculas a salas";
			// 
			// AsignacionPeliculasSalas
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(976, 663);
			this->Controls->Add(this->label1);
			this->Name = L"AsignacionPeliculasSalas";
			this->Text = L"AsignacionPeliculasSalas";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
