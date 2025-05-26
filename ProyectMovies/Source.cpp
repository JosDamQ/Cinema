#include "Login.h"

int main()
{
    System::Windows::Forms::Application::EnableVisualStyles();
    System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);

    ProyectMovies::Login^ loginForm = gcnew ProyectMovies::Login();
    System::Windows::Forms::Application::Run(loginForm);

    return 0;
}