#include "Login.h";
using namespace ProyectMovies;

int main() 
{
	Login^ login = gcnew Login();

	Application::Run(login);
	return 0;
}