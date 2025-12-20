#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdio> 

// Estructura de datos
struct Punto 
{
	long long x, y, z;
	int id;
};

struct Arista
{
	int u, v; //ID puntos
	long long dist_sq;  // Distancia al cuadrado

	// Sobrecarga para ordenar
	bool operator<(const Arista& otro) const {return dist_sq < otro.dist_sq;}
};

long long distsq(const Punto& a, const Punto& b) 
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
	if (padre[i] == i) {return i;}
	// Compresión de camino: actualizamos el padre directamente a la raíz
	return padre[i] = encontrar_raiz(padre[i], padre);
}

// Union de conjuntos diferentes
void unir(int i, int j, std::vector<int>& padre, std::vector<int>& tamano) 
{
	int raiz_i = encontrar_raiz(i, padre);
	int raiz_j = encontrar_raiz(j, padre);

	if (raiz_i != raiz_j) 
	{
		// Optimización: Unir el árbol pequeño al grande
		if (tamano[raiz_i] < tamano[raiz_j]) {std::swap(raiz_i, raiz_j);}
		padre[raiz_j] = raiz_i; // El padre de j ahora es i
		tamano[raiz_i] += tamano[raiz_j]; // El tamaño de i crece
	}
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

		// Usamos sscanf para leer formato "X,Y,Z"
		if (sscanf(line.c_str(), "%lld,%lld,%lld", &p.x, &p.y, &p.z) == 3) 
		{
			puntos.push_back(p);
		}
	}
	file.close();

	int N = puntos.size();
	if (N < 2) return 0;

	// Genera todas las aristas posibles 
	std::vector<Arista> aristas;
	aristas.reserve(N * (N - 1) / 2); // Reservar memoria para evitar reallocaciones

	for (int i = 0; i < N; ++i) 
	{
		for (int j = i + 1; j < N; ++j)
		{
			long long d = distsq(puntos[i], puntos[j]);
			aristas.push_back({i, j, d});
		}
	}

	// Ordenamos aristas de menor a mayor distancia
	std::sort(aristas.begin(), aristas.end());
	std::vector<int> padre(N);
	std::vector<int> tamano(N, 1); 
	for (int i = 0; i < N; i++) padre[i] = i; 

	// Procesamos las 1000 conexiones más cortas
	int limite = std::min((int)aristas.size(), 1000);

	for (int i = 0; i < limite; ++i)
	{
		unir(aristas[i].u, aristas[i].v, padre, tamano);
	}

	// Recopilamos resultados
	std::vector<long long> tamanos_finales;
	std::vector<bool> procesado(N, false);

	for (int i = 0; i < N; ++i) 
	{
		// Solo nos interesan las raíces de los grupos para no contar duplicados
		int raiz = encontrar_raiz(i, padre);
		if (!procesado[raiz])
		{
			tamanos_finales.push_back(tamano[raiz]);
			procesado[raiz] = true;
		}
	}

	// Ordenar para buscar los 3 más grandes
	std::sort(tamanos_finales.rbegin(), tamanos_finales.rend());

	long long resultado = 1;
	int a_multiplicar = std::min((int)tamanos_finales.size(), 3);

	for (int i = 0; i < a_multiplicar; ++i) {resultado *= tamanos_finales[i];}

	std::cout << "Resultado final: " << resultado << std::endl;

	return 0;
}
