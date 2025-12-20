#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Tabla Hash
// Nodo para lista enlazada en caso de colisiones
struct HashNode
{
	std::string key; // Nombre original
	int value;       // El ID numérico asignado
	HashNode* next;  // Puntero al siguiente nodo
	HashNode(std::string k, int v) : key(k), value(v), next(nullptr) {}
};

class TablaHash
{
	private:
		static const int size = 10007;
		HashNode* tabla[size];        

		// Función Hash clasica
		// Convierte "abc" en un número entero
		unsigned int hashFunction(const std::string& str)
	       	{
			unsigned int hash = 5381;
			for (char c : str)
		       	{
				hash = ((hash << 5) + hash) + c;
			}
			return hash % size;
		}

	public:
		// Constructor: inicio a nullptr
		TablaHash() {for (int i = 0; i < size; ++i) tabla[i] = nullptr;}
		
		// Destructor: limpieza de memoria
		~TablaHash() 
		{
			for (int i = 0; i < size; ++i)
		       	{
				HashNode* entry = tabla[i];
				while (entry != nullptr)
			       	{
					HashNode* prev = entry;
					entry = entry->next;
					delete prev;
				}
			}
		}

		// Insertar: Guarda una clave si no existe.
		// Retorna el ID existente si estaba o el nuevo si no.
		// Recibe un puntero a un contador para asignar nuevos IDs automáticamente.
		int insertar(const std::string& key, int& counter)
	       	{
			unsigned int indice = hashFunction(key);
			HashNode* entry = tabla[indice];

			// Busca si ya existe 
			while (entry != nullptr)
		       	{
				if (entry->key == key) {return entry->value;}
				entry = entry->next;
			}

			// Si no existe, crea un nuevo nodo al principio de la lista
			HashNode* newNode = new HashNode(key, counter);
			newNode->next = tabla[indice]; 
			tabla[indice] = newNode;       
			return counter++; // Devolvemos el ID actual y luego incrementamos el contador
		}
};

// Como ahora mapeamos strings a ints podemos usar vectores simples
using Grafo = std::vector<std::vector<int>>;
using TablaMemo = std::vector<long long>;

long long caminos(int current, int target, const Grafo& grafo, TablaMemo& memo)
{
	if (current == target) {return 1;}

	// Programacion dinamica: Si memo[current] no es -1, ya lo calculamos
	if (memo[current] != -1) {return memo[current];}

	long long total = 0;
	for (int vecino : grafo[current]) {total += caminos(vecino, target, grafo, memo);}
	return memo[current] = total;
}

void solucion() 
{
	std::ifstream file("datosAOC11.txt");
	if (!file.is_open()) return;

	TablaHash mapa;
	int ids = 0; // Generador de IDs 

	// Estructuras temporales para guardar las conexiones antes de crear el grafo final
	std::vector<std::pair<int, int>> edges;

	std::string line;
	while (std::getline(file, line)) 
	{
		if (line.empty()) {continue;}
		std::stringstream ss(line);
		std::string origen, destino;

		ss >> origen;
		if (origen.back() == ':') {origen.pop_back();}

		// Usamos nuestro mapa para obtener el ID numérico
		int u = mapa.insertar(origen, ids);

		while (ss >> destino) 
		{
			int v = mapa.insertar(destino, ids);
			edges.push_back({u, v});
		}
	}

	// Ahora sabemos cuántos nodos únicos hay (ids), creamos el grafo
	Grafo grafo(ids);
	for (auto& edge : edges) {grafo[edge.first].push_back(edge.second);}

	// Preparamos la búsqueda
	// Necesitamos los IDs de "you" y "out".
	// Si no existen en el input, insertar los creará, pero no tendrán conexiones.
	int inicio = mapa.insertar("you", ids);
	int fin = mapa.insertar("out", ids);

	// Tabla de memoización iniciada a -1 
	TablaMemo memo(ids + 1, -1);

	long long resultado = caminos(inicio, fin, grafo, memo);

	std::cout << "Total de caminos: " << resultado << std::endl;
}

int main() 
{
	solucion();
	return 0;
}
