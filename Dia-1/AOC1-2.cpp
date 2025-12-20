#include <iostream>
#include <fstream>
#include <string>

void solve(const std::string& ruta_archivo)
{
	std::ifstream file(ruta_archivo);
	if (!file.is_open())
	{
		std::cerr << "No se pudo abrir '" << ruta_archivo << "'.\n";
		return;
	}
	//Usamos un numero enorme para usar solo numeros positivos
	long long pos = 1000000000000LL + 50; 
	long long zeros = 0;
	char dir;
	long long pasos;

	while (file >> dir >> pasos)
	{
		long long old_pos = pos;

		if (dir == 'R') 
		{
			pos += pasos;
			//Cuenta cuántos múltiplos de 100 hay en (old, new]
			zeros += (pos / 100) - (old_pos / 100);
		} 
		else if (dir == 'L')
		{
			pos -= pasos;
			//Cuenta multiplos entre variables
			//Restamos 1 para evitar que haga cuentas extra en el total
			//si partimos del 0 y lo incluimos en el nuevo por si vuelve
			//a pararse en 0.
			zeros += ((old_pos - 1) / 100) - ((pos - 1) / 100);
		}
	}

	std::cout << "Password: " << zeros << std::endl;
}

int main(int argc, char* argv[]) 
{
	// argc siempre es al menos 1 (el nombre del programa).
	// Si argc es menor que 2, es que el usuario olvidó poner el archivo.
	if (argc < 2)
       	{
		std::cerr << "Uso correcto: " << argv[0] << " <ruta_del_archivo>\n";
		return 1; // Retornar 1 indica error al sistema operativo
	}
		solve(argv[1]);
return 0;
}
