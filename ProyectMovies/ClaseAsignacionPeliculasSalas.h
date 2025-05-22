#pragma once
using namespace System;
#include "ClasePelicula.h"
#include "ClaseSalas.h"

namespace ProyectMovies {
	public ref class AsignacionPeliculaSala
	{
	private:
		int codigo;
		Pelicula^ pelicula;
		Sala^ sala;
		DateTime fechaHoraEstreno;

	public:
		AsignacionPeliculaSala(int codigo, Pelicula^ pelicula, Sala^ sala, DateTime fechaHoraEstreno)
		{
			this->codigo = codigo;
			this->pelicula = pelicula;
			this->sala = sala;
			this->fechaHoraEstreno = fechaHoraEstreno;
		}

		//Propiedades
		property int Codigo {
			int get() { return codigo; }
			void set(int value) { codigo = value; }
		}

		property Pelicula^ PeliculaAsignada {
			Pelicula^ get() { return pelicula; }
			void set(Pelicula^ value) { pelicula = value; }
		}

		property Sala^ SalaAsignada {
			Sala^ get() { return sala; }
			void set(Sala^ value) { sala = value; }
		}

		property DateTime FechaEstreno {
			DateTime get() { return fechaHoraEstreno; }
			void set(DateTime value) { fechaHoraEstreno = value; }
		}

		// M�todo para mostrar resumen de asignaci�n
		String^ ObtenerResumenAsignacion() {
			return String::Format("Asignaci�n #{0}: '{1}' en Sala '{2}' - {3}",
				codigo,
				pelicula->Nombre,
				sala->Nombre,
				fechaHoraEstreno.ToString("dd/MM/yyyy hh:mm tt")
			);
		}
	};

}
