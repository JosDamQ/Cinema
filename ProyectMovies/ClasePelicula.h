#pragma once
using namespace System;

namespace ProyectMovies {

	public enum class Genero {
		Accion,
		Aventura,
		Ficcion,
		Comedia,
		Drama,
		Documental
	};

	public enum class Clasificacion {
		A14,
		A18,
		PA
	};

	public enum class Idioma {
		Doblada,
		Subtitulada
	};

	public enum class Formato {
		Formato2D,
		Formato3D,
		Digital
	};

	public enum class Estado {
		Activo,
		Inactivo
	};

	public ref class Pelicula {

	private:
		String^ nombre;
		Genero genero;
		Clasificacion clasificacion;
		Idioma idioma;
		Formato formato;
		String^ precio;
		Estado estado;

	public:
		// Constructor
		Pelicula(String^ nombre, Genero genero, Clasificacion clasificacion, Idioma idioma, Formato formato, String^ precio, Estado estado) {
			this->nombre = nombre;
			this->genero = genero;
			this->clasificacion = clasificacion;
			this->idioma = idioma;
			this->formato = formato;
			this->precio = precio;
			this->estado = estado;
		}

		// Propiedades
		property String^ Nombre {
			String^ get() { return nombre; }
			void set(String^ value) { nombre = value; }
		}

		property Genero GeneroPelicula {
			Genero get() { return genero; }
			void set(Genero value) { genero = value; }
		}

		property Clasificacion ClasificacionPelicula {
			Clasificacion get() { return clasificacion; }
			void set(Clasificacion value) { clasificacion = value; }
		}

		property Idioma IdiomaPelicula {
			Idioma get() { return idioma; }
			void set(Idioma value) { idioma = value; }
		}

		property Formato FormatoPelicula {
			Formato get() { return formato; }
			void set(Formato value) { formato = value; }
		}

		property String^ Precio {
			String^ get() { return precio; }
			void set(String^ value) { precio = value; }
		}

		property Estado EstadoPelicula {
			Estado get() { return estado; }
			void set(Estado value) { estado = value; }
		}
	};
}
#pragma once
