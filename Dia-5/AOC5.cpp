#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

// Estructura básica para el rango
struct Range 
{
       long long start;
       long long end;
       // Sobrecarga del operador para ordenar automáticamente
       bool operator<(const Range& other) const {return start < other.start;}
};

// Funcion 1: Fusionar Rangos
// Recibe los rangos y devuelve una lista
std::vector<Range> merge_ranges(std::vector<Range>& ranges)
{
	if (ranges.empty()) {return {};}
       	std::sort(ranges.begin(), ranges.end()); // Ordenamos los rangos de menor a mayor inicio
	std::vector<Range> merged;
	merged.push_back(ranges[0]); // Añadimos el primero como base
	
	for (size_t i = 1; i < ranges.size(); i++)
       	{
		int last_index = merged.size() - 1; // Obtenemos referencia al último rango añadido
		Range current_range = ranges[i];
		
		// Comprobamos solapamiento:
		if (current_range.start <= merged[last_index].end)
	       	{
			// Los fusionamos extendiendo el final del último
			if (current_range.end > merged[last_index].end)
		       	{
				merged[last_index].end = current_range.end;
			}
		}
		
		// No hay solapamiento, añadimos el rango nuevo a la lista
		else {merged.push_back(current_range);}
	}
	
	return merged;
}

// Funcion 2: Búsqueda Binaria
// Busca si 'id' está dentro de alguno de los rangos ordenados y fusionados.
bool fresh(const std::vector<Range>& ranges, long long id)
{
	int left = 0;
	int right = ranges.size() - 1;
	
	while (left <= right)
       	{
		int mid = left + (right - left) / 2;
		// El ID está en el rango del medio
		if (id >= ranges[mid].start && id <= ranges[mid].end) {return true;}
		
		// El ID es menor que el inicio del rango -> Buscamos a la izquierda
		if (id < ranges[mid].start) {right = mid - 1;}
	       
	       	// El ID es mayor que el final del rango -> Buscamos a la derecha
		else {left = mid + 1;}
	}
	
	return false; // No se encontró en ningún rango
}

int main()
{
	std::ifstream file("datosAOC5.txt");
	if (!file.is_open()) 
	{
		std::cout << "No se pudo abrir datosAOC5.txt" << std::endl;
		return 1;
	}
       
	std::vector<Range> ranges;
	std::string line;
	long long fresh_count = 0;
	
	while (std::getline(file, line) && !line.empty()) 
       	{
		size_t dash_pos = line.find('-');
		if (dash_pos != std::string::npos)
	       	{
			// Leemos rangos
			long long start = std::stoll(line.substr(0, dash_pos));
			long long end = std::stoll(line.substr(dash_pos + 1));
			ranges.push_back({start, end});
		}
	}
	
	std::vector<Range> optimized_ranges = merge_ranges(ranges);
	
	// Liberamos RAM
	ranges.clear();
	ranges.shrink_to_fit(); // Truco para forzar al S.O. a recuperar la memoria
	
	//Lectura de valores y comprobacion simultanea
	long long current_id;
	while (file >> current_id)
       	{
		if (fresh(optimized_ranges, current_id)) {fresh_count++;}
	}

	file.close();
	std::cout << "Total ingredientes frescos: " << fresh_count << std::endl;
	return 0;
}
