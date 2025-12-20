#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void solve(const std::string& ruta_archivo)
{
	std::ifstream file(ruta_archivo);
	if (!file.is_open())
	{
		std::cerr << "No se pudo abrir '" <<  ruta_archivo << "'.\n";
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

int main(int argc, char* argv[])
{
	// argc siempre es al menos 1.
	// Si argc es menor que 2, es que el usuario olvidó poner el archivo.
	if (argc < 2)
	{
		std::cerr << "Uso correcto: " << argv[0] << " <ruta_del_archivo>\n";
		return 1; // Error
	}
	solve(argv[1]);
	return 0;
}
