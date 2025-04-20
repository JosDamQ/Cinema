//#include "Login.h";
#include "Landing.h";
using namespace ProyectMovies;

int main() 
{
	//Login^ login = gcnew Login();
	Landing^ landing = gcnew Landing();

	//Application::Run(login);
	Application::Run(landing);
	return 0;
}