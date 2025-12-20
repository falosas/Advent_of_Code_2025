#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>

// Estructura para guardar coordenadas (fila, columna)
struct Punto 
{
	int r;
	int c;
};

long long rayos(const std::vector<std::string>& mapa)
{
	int filas = mapa.size();
	int cols = mapa[0].size();
	long long divisiones = 0;

	// Buscamos la 'S'
	Punto inicio = {0, 0};
	for (int r = 0; r < filas; r++) 
	{
		for (int c = 0; c < cols; c++)
		{
			if (mapa[r][c] == 'S'){inicio = {r, c};}
		}
	}

	// Preparación para buscar en anchura
	std::queue<Punto> cola;
	cola.push(inicio);

	// Matriz para recordar dónde ha empezado un rayo (para evita bucles infinitos y fusiones)
	std::vector<std::vector<bool>> visitado(filas, std::vector<bool>(cols, false));
	visitado[inicio.r][inicio.c] = true;

	// Matriz para marcar qué divisores hemos golpeado
	std::vector<std::vector<bool>> choque(filas, std::vector<bool>(cols, false));

	while (!cola.empty())
	{
		Punto actual = cola.front();
		cola.pop();

		// El rayo empieza a caer desde la siguiente casilla hacia abajo
		int r = actual.r + 1;
		int c = actual.c;

		// El rayo baja hasta chocar o salir del mapa
		while (r < filas)
		{
			char celda = mapa[r][c];

			if (celda == '^') 
			{
				// Choque
				// Si es la primera vez que golpeamos este divisor, sumamos 1
				if (!choque[r][c])
				{
					choque[r][c] = true;
					divisiones++;
				}

				// Generar nuevo rayo a la izquierda (si está dentro del mapa)
				if (c - 1 >= 0) 
				{
					if (!visitado[r][c - 1]) 
					{
						visitado[r][c - 1] = true;
						cola.push({r, c - 1});
					}
				}

				// Generar nuevo rayo a la derecha (si está dentro del mapa)
				if (c + 1 < cols) 
				{
					if (!visitado[r][c + 1])
					{
						visitado[r][c + 1] = true;
						cola.push({r, c + 1});
					}
				}
				// El rayo actual muere aquí
				break; 
			}
			// Si no chocamos, seguimos bajando
			r++;
		}
	}
	return divisiones;
}

int main(int argc, char* argv[]) 
{
	// Comprobamos si el usuario introdujo la ruta del archivo
	if (argc < 2)
	{
		std::cout << "Uso correcto: " << argv[0] << " <ruta_del_archivo>" << std::endl;
		return 1;
	}

	// Abrimos el archivo
	std::ifstream file(argv[1]);
	if (!file.is_open())
	{
		std::cout << "No se pudo abrir " << argv[1]  << std::endl;
		return 1;
	}
	std::vector<std::string> mapa;
	std::string line;

	while (std::getline(file, line))
	{
		if (!line.empty()) mapa.push_back(line);
	}
	file.close();

	std::cout << "Veces que el rayo se divide: " << rayos(mapa) << std::endl;

	return 0;
}
