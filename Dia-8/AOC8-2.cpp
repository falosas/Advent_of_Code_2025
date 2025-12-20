#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdio>

// Estructuras de datos 
struct Punto 
{
	long long x, y, z;
	int id;
};

struct Arista
{
	int u, v; // ID puntos              
	long long dist_sq;  // Distancia al cuadrado

	// Sobrecarga para ordenar
	bool operator<(const Arista& otro) const {return dist_sq < otro.dist_sq;}
};

long long distanciasq(const Punto& a, const Punto& b)
{
	long long dx = a.x - b.x;
	long long dy = a.y - b.y;
	long long dz = a.z - b.z;
	return (dx*dx) + (dy*dy) + (dz*dz);
}

// Encuentra la raíz del conjunto al que pertenece 'i'
// Usa recursividad y compresión de caminos
int encontrar_raiz(int i, std::vector<int>& padre)
{
	if (padre[i] == i) return i;
	// Compresión de camino: actualizamos el padre directamente a la raíz
	return padre[i] = encontrar_raiz(padre[i], padre);
}

// Modificamos esta función para que devuelva 'true' si hubo unión real
bool unir(int i, int j, std::vector<int>& padre, std::vector<int>& tamano)
{
	int raiz_i = encontrar_raiz(i, padre);
	int raiz_j = encontrar_raiz(j, padre);

	if (raiz_i != raiz_j)
	{
		// Optimización: Unir el árbol pequeño al grande
		if (tamano[raiz_i] < tamano[raiz_j]) {std::swap(raiz_i, raiz_j);}
		padre[raiz_j] = raiz_i; // El padre de j ahora es i
		tamano[raiz_i] += tamano[raiz_j]; // El tamaño de i crece
		return true; //Los conectamos
	}
	return false; //Ya estaban conectados
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

	std::vector<Punto> puntos;
	std::string line;
	int id_counter = 0;

	while (std::getline(file, line))
	{
		if (line.empty()) continue;
		Punto p;
		p.id = id_counter++;
		if (sscanf(line.c_str(), "%lld,%lld,%lld", &p.x, &p.y, &p.z) == 3)
		{
			puntos.push_back(p);
		}
	}
	file.close();

	int N = puntos.size();
	if (N < 2) return 0;

	// Genera todas las aristas
	std::vector<Arista> aristas;
	aristas.reserve(N * (N - 1) / 2);

	for (int i = 0; i < N; ++i)
	{
		for (int j = i + 1; j < N; ++j) 
		{
			long long d = distanciasq(puntos[i], puntos[j]);
			aristas.push_back({i, j, d});
		}
	}

	// Ordenamos ascendentemente
	std::sort(aristas.begin(), aristas.end());
	std::vector<int> padre(N);
	std::vector<int> tamano(N, 1); 
	for (int i = 0; i < N; i++) padre[i] = i;

	int activos = N; 

	// Procesamos aristas hasta que todo sea un solo circuito
	for (const auto& arista : aristas)
	{
		// Intentamos unir
		if (unir(arista.u, arista.v, padre, tamano)) 
		{
			// Si la unión fue exitosa, reducimos el contador de islas
			activos--;
			// Condicion de parada: Solo queda 1 gran componente
			if (activos == 1) 
			{
				long long x1 = puntos[arista.u].x;
				long long x2 = puntos[arista.v].x;
				long long resultado = x1 * x2;

				std::cout << "Ultima conexion realizada entre nodos: " << arista.u << " y "
					<< arista.v << std::endl;
				std::cout << "Resultado (Producto de X): " << resultado << std::endl;
				return 0; 
			}
		}
	}

	return 0;
}
