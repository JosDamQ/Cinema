#include "Login.h"

[STAThread]  // <-- Este atributo es crucial
int main()
{
    System::Windows::Forms::Application::EnableVisualStyles();
    System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);

    ProyectMovies::Login^ loginForm = gcnew ProyectMovies::Login();
    System::Windows::Forms::Application::Run(loginForm);

    return 0;
}