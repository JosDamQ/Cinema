#pragma once
#include <array>

using namespace System;

namespace ProyectMovies {

	public enum class CapacidadSala {
		Capacidad_40 = 40,
		Capacidad_56 = 56
	};

	public ref class Sala
	{
	private:
		int codigo;
		String^ nombre;
		CapacidadSala capacidad;
		String^ ubicacion;
		String^ encargado;
		String^ telefonoEncargado;
		array<array<bool>^>^ asientos;

		void InicializarAsientos() {
			int filas = 0;
			if (capacidad == CapacidadSala::Capacidad_40)
			{
				filas = 5;
			}
			else if (capacidad == CapacidadSala::Capacidad_56)
			{
				filas = 7;
			}
			int columnas = 8;

			asientos = gcnew array<array<bool>^>(filas);
			for (int i = 0; i < filas; i++) {
				asientos[i] = gcnew array<bool>(columnas);
				for (int j = 0; j < columnas; j++) {
					asientos[i][j] = true;  // Todos disponibles al inicio
				}
			}
		}

	public:
		// Constructor
		Sala(int codigo, String^ nombre, CapacidadSala capacidad, String^ ubicacion, String^ encargado, String^ telefonoEncargado)
		{
			this->codigo = codigo;
			this->nombre = nombre;
			this->capacidad = capacidad;
			this->ubicacion = ubicacion;
			this->encargado = encargado;
			this->telefonoEncargado = telefonoEncargado;

			InicializarAsientos();
		}
		property int Codigo
		{
			int get() { return codigo; }
			void set(int value) { codigo = value; }
		}
		property String^ Nombre
		{
			String^ get() { return nombre; }
			void set(String^ value) { nombre = value; }
		}
		property CapacidadSala Capacidad
		{
			CapacidadSala get() { return capacidad; }
			void set(CapacidadSala value) { capacidad = value; }
		}
		property String^ Ubicacion
		{
			String^ get() { return ubicacion; }
			void set(String^ value) { ubicacion = value; }
		}
		property String^ Encargado
		{
			String^ get() { return encargado; }
			void set(String^ value) { encargado = value; }
		}
		property String^ TelefonoEncargado
		{
			String^ get() { return telefonoEncargado; }
			void set(String^ value) { telefonoEncargado = value; }
		}

		//property array<array<bool>^>^ Asientos {
		//	array<array<bool>^>^ get() { return asientos; }
		//}

		bool OcuparAsiento(int fila, int columna) {
			if (fila >= 0 && fila < asientos->Length && columna >= 0 && columna < asientos[0]->Length) {
				if (asientos[fila][columna]) {
					asientos[fila][columna] = false;
					return true; // Asiento ocupado
				}
			}
			return false; // Asiento ya ocupado o coordenadas inválidas
		}

		// Aqui podria ir el liberar todos los asientos
		void RestaurarAsientos() {
			for (int i = 0; i < asientos->Length; i++) {
				for (int j = 0; j < asientos[i]->Length; j++) {
					asientos[i][j] = true; // Marcar todos los asientos como disponibles
				}
			}
		}

		String^ ObtenerInfoMatrizAsientos() {
			int filas = asientos->Length;
			int columnas = asientos[0]->Length;
			return String::Format("Filas: {0}, Columnas: {1}", filas, columnas);
		}

	};
}
