// GeneradorReporte.h
#pragma once

// Incluir esto al inicio para evitar conflictos con Windows
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef ServiceProvider  // Deshacer la definición de Windows

#include <fstream>
#include <string>

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;

namespace ProyectMovies {

    public ref class GeneradorReporte
    {
    public:
        // Versión sin parámetro predeterminado
        static bool GenerarReporte(
            String^ titulo,
            String^ encabezado,
            String^ piePagina,
            array<String^>^ encabezadosColumnas,
            array<array<String^>^>^ datosTabla)
        {
            return GenerarReporte(titulo, encabezado, piePagina,
                encabezadosColumnas, datosTabla,
                "Reporte");
        }

        // Versión con nombre de archivo personalizado
        static bool GenerarReporte(
            String^ titulo,
            String^ encabezado,
            String^ piePagina,
            array<String^>^ encabezadosColumnas,
            array<array<String^>^>^ datosTabla,
            String^ nombreArchivo)
        {
            // Configurar el diálogo para guardar archivo
            SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
            saveFileDialog->Filter = "Archivos HTML (*.html)|*.html|Todos los archivos (*.*)|*.*";
            saveFileDialog->FilterIndex = 1;
            saveFileDialog->RestoreDirectory = true;
            saveFileDialog->FileName = nombreArchivo + "_" + DateTime::Now.ToString("yyyyMMdd_HHmmss") + ".html";
            saveFileDialog->Title = "Guardar reporte";

            // Mostrar el diálogo
            if (saveFileDialog->ShowDialog() == DialogResult::OK)
            {
                try
                {
                    // Generar el contenido HTML
                    String^ htmlContent = GenerarHTML(
                        titulo,
                        encabezado,
                        piePagina,
                        encabezadosColumnas,
                        datosTabla);

                    // Guardar el archivo
                    File::WriteAllText(saveFileDialog->FileName, htmlContent);

                    // Mostrar mensaje de éxito
                    MessageBox::Show(
                        "Reporte generado exitosamente en:\n" + saveFileDialog->FileName,
                        "Éxito",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Information);

                    // Opcional: abrir el reporte en el navegador
                    System::Diagnostics::Process::Start(saveFileDialog->FileName);

                    return true;
                }
                catch (Exception^ e)
                {
                    MessageBox::Show(
                        "Error al generar el reporte:\n" + e->Message,
                        "Error",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Error);
                    return false;
                }
            }

            return false;
        }

    private:
        // Método privado para generar el contenido HTML
        static String^ GenerarHTML(
            String^ titulo,
            String^ encabezado,
            String^ piePagina,
            array<String^>^ encabezadosColumnas,
            array<array<String^>^>^ datosTabla)
        {
            // Cargar la plantilla HTML
            String^ plantillaPath = "TemplateReporte.html";
            String^ htmlTemplate = File::ReadAllText(plantillaPath);

            // Generar encabezados de columnas
            StringBuilder^ headersBuilder = gcnew StringBuilder();
            for each (String ^ header in encabezadosColumnas)
            {
                headersBuilder->AppendFormat("<th>{0}</th>", header);
            }

            // Generar filas de datos
            StringBuilder^ dataBuilder = gcnew StringBuilder();
            for each (array<String^> ^ fila in datosTabla)
            {
                if (fila != nullptr)
                {
                    dataBuilder->Append("<tr>");
                    for each (String ^ celda in fila)
                    {
                        dataBuilder->AppendFormat("<td>{0}</td>", celda);
                    }
                    dataBuilder->Append("</tr>");
                }
            }

            // Reemplazar placeholders en la plantilla
            htmlTemplate = htmlTemplate->Replace("%%TITLE%%", titulo);
            htmlTemplate = htmlTemplate->Replace("%%HEADER%%", encabezado);
            htmlTemplate = htmlTemplate->Replace("%%FOOTER%%", piePagina);
            htmlTemplate = htmlTemplate->Replace("%%DATE%%", DateTime::Now.ToString("dd/MM/yyyy HH:mm:ss"));
            htmlTemplate = htmlTemplate->Replace("%%COLUMNHEADERS%%", headersBuilder->ToString());
            htmlTemplate = htmlTemplate->Replace("%%TABLEDATA%%", dataBuilder->ToString());

            return htmlTemplate;
        }
    };
}