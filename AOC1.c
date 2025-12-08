#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void solve()
{
    std::ifstream file("datosAOC1.txt");
    
    if (!file.is_open())
    {
        std::cerr << "No se pudo abrir 'datosAOC1.txt'.\n";
        return;
    }

    int dial_pos = 50;  //El problema indica que el dial empieza en 50.     
    int zeros = 0;  //Contador de paradas en 0
    char direction;
    int pasos;

    //Lectura del archivo que primero obtiene el caracter de la direccion
    //y luego el numero entero omitiendo espacios
    while (file >> direction >> pasos)
    {
        //Opcion giro a derecha
        if (direction == 'R')
       	{
            dial_pos = (dial_pos + pasos) % 100;
        } 
	//Opcion giro a izquierda
        else if (direction == 'L')
       	{
	    //Si el resultado es negativo devuelve un resto negativo.
            //Se ajustar para que el ciclo sea entre 0-99.
            dial_pos = (dial_pos - pasos);
            dial_pos = (dial_pos % 100); 
            if (dial_pos < 0) 
	    {
                dial_pos += 100;
            }
        }

        if (dial_pos == 0) 
	{
            zeros++;
        }
    }

    std::cout << "Password: " << zeros << std::endl;
}

int main()
{
    solve();
    return 0;
}
