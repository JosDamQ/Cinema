#pragma once
using namespace System;
#include "ClaseAsignacionPeliculasSalas.h";
#include "ClaseClientes.h";


namespace ProyectMovies {
	public ref class ComprasBoletos
	{
	private:
		int codigo;
		AsignacionPeliculaSala^ asignacion;
		Cliente^ cliente;
		DateTime fechaCompra;
		int filaAsiento;
		int columnaAsiento;
		//int totalBoletos;

	public:
		ComprasBoletos(int codigo, AsignacionPeliculaSala^ asignacion, Cliente^ cliente, DateTime fechaCompra, int fila, int columna)
		{
			this->codigo = codigo;
			this->asignacion = asignacion;
			this->cliente = cliente;
			this->fechaCompra = fechaCompra;
			this->filaAsiento = fila;
			this->columnaAsiento = columna;
		}
		property int Codigo
		{
			int get() { return codigo; }
			void set(int value) { codigo = value; }
		}
		property Cliente^ ClienteCompra
		{
			Cliente^ get() { return cliente; }
			void set(Cliente^ value) { cliente = value; }
		}
		property AsignacionPeliculaSala^ AsignacionCompra
		{
			AsignacionPeliculaSala^ get() { return asignacion; }
			void set(AsignacionPeliculaSala^ value) { asignacion = value; }
		}
		property DateTime FechaCompra
		{
			DateTime get() { return fechaCompra; }
			void set(DateTime value) { fechaCompra = value; }
		}
		property int FilaAsiento
		{
			int get() { return filaAsiento; }
			void set(int value) { filaAsiento = value; }
		}
		property int ColumnaAsiento
		{
			int get() { return columnaAsiento; }
			void set(int value) { columnaAsiento = value; }
		}
	};
}
