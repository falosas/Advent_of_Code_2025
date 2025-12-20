#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Estructura para coordenadas
struct Punto
{
	int r;
	int c;
};

// Matriz de memorizacion
// memo[r][c] guardará el número de lineas temporales que se generan
// si un rayo golpea un divisor en esa posición.
// -1 indica que aún no lo hemos calculado.
std::vector<std::vector<long long>> memo;
int filas, cols;

// Busqueda de inicio: devuelve las coordenadas de 'S', o {-1, -1} si no existe.
Punto buscar_S(const std::vector<std::string>& mapa) 
{
	for (int r = 0; r < filas; ++r) 
	{
		for (int c = 0; c < cols; ++c) 
		{
			if (mapa[r][c] == 'S') 
			{
				return {r, c};
			}
		}
	}
	return {-1, -1};
}

// Función Recursiva con memorizacion 
// Recibe la posición desde donde el rayo empieza a caer (después de una division o inicio)
long long lineas(const std::vector<std::string>& mapa, int start_r, int start_c) 
{
	// Verificación de si el split nos manda fuera lateralmente
	if (start_c < 0 || start_c >= cols) return 0;

	// El rayo baja hasta encontrar algo
	int r = start_r;
	int c = start_c;

	while (r < filas)
	{
		char celda = mapa[r][c];
		if (celda == '^') 
		{
			// Choque
			// Consulta memorizacion divisor resuelto
			if (memo[r][c] != -1) 
			{
				return memo[r][c];
			}

			// Si no, calculamos recursivamente
			long long total_lineas = 0;

			// Camino izquierdo: empieza a caer desde la siguiente fila, columna izquierda
			// (r + 1 porque el rayo reaparece y cae inmediatamente)
			total_lineas += lineas(mapa, r + 1, c - 1);

			// Camino derecho: empieza a caer desde la siguiente fila, columna derecha
			total_lineas += lineas(mapa, r + 1, c + 1);

			// Guarda en memoria y retorna
			memo[r][c] = total_lineas;
			return total_lineas;
		}
		// Sigue cayendo
		r++;
	}
	// Caso base: si el bucle termina, salimos del mapa por abajo.
	// Cuenta como 1 línea temporal válida completada.
	return 1;
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

	if (mapa.empty()) return 0;

	filas = mapa.size();
	cols = mapa[0].size();

	// Inicializamos la tabla de memoización con -1
	memo.assign(filas, std::vector<long long>(cols, -1));

	//Llamada a funcion de busqueda del comienzo
	Punto inicio = buscar_S(mapa);

	// Llamada inicial: El rayo empieza a caer desde la fila siguiente a S
	long long total = lineas(mapa, inicio.r + 1, inicio.c);

	std::cout << "Total de lineas temporales: " << total << std::endl;

	return 0;
}
