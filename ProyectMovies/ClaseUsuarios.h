#pragma once

using namespace System;

namespace ProyectMovies {

	public enum class Role {
		Admin,
		User
	};

	public ref class User
	{
	private:
		int codigo;
		String^ username;
		String^ password;
		String^ nombre;
		String^ apellido;
		String^ dpi;
		String^ telefono;
		String^ email;
		String^ direccion;
		Role role;

	public:
		// Constructor
		User(int codigo, String^ username, String^ password, String^ nombre, String^ apellido, String^ dpiParam, String^ telefono, String^ email, String^ direccion, Role role)
		{
			this->codigo = codigo;
			this->username = username;
			this->password = password;
			this->nombre = nombre;
			this->apellido = apellido;
			this->dpi = dpiParam;
			this->telefono = telefono;
			this->email = email;
			this->direccion = direccion;
			this->role = role;
		}

		// Getters y Setters
		property int Codigo
		{
			int get() { return codigo; }
			void set(int value) { codigo = value; }
		}

		property String^ Username
		{
			String^ get() { return username; }
			void set(String^ value) { username = value; }
		}

		property String^ Password
		{
			String^ get() { return password; }
			void set(String^ value) { password = value; }
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

		property String^ Direccion
		{
			String^ get() { return direccion; }
			void set(String^ value) { direccion = value; }
		}

		property Role UserRole
		{
			Role get() { return role; }
			void set(Role value) { role = value; }
		}
	};
}
