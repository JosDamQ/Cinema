#pragma once
#include "ClaseUsuarios.h";

using namespace System;

namespace ProyectMovies {

	public ref class Cliente
	{
	private:
		int codigo;
		String^ nombre;
		String^ apellido;
		String^ dpi;
		DateTime^ fechaNacimiento;
		String^ telefono;
		String^ email;


	public:
		// Constructor
		Cliente(int codigo, String^ nombre, String^ apellido, String^ dpi, DateTime^ fechaNacimiento, String^ telefono, String^ email)
		{
			this->codigo = codigo;
			this->nombre = nombre;
			this->apellido = apellido;
			this->dpi = dpi;
			this->fechaNacimiento = fechaNacimiento;
			this->telefono = telefono;
			this->email = email;
		}
		// Getters y Setters
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
		property String^ Apellido
		{
			String^ get() { return apellido; }
			void set(String^ value) { apellido = value; }
		}
		property String^ DPI
		{
			String^ get() { return dpi; }
			void set(String^ value) { dpi = value; }
		}
		property DateTime^ FechaNacimiento
		{
			DateTime^ get() { return fechaNacimiento; }
			void set(DateTime^ value) { fechaNacimiento = value; }
		}
		property String^ Telefono
		{
			String^ get() { return telefono; }
			void set(String^ value) { telefono = value; }
		}
		property String^ Email
		{
			String^ get() { return email; }
			void set(String^ value) { email = value; }
		}
	};
}
