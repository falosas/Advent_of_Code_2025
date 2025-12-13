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
	
	while (std::getline(file, line) && !line.empty()) 
	{
		size_t dash_pos = line.find('-');
		if (dash_pos != std::string::npos) 
		{
			long long start = std::stoll(line.substr(0, dash_pos));
			long long end = std::stoll(line.substr(dash_pos + 1));
			ranges.push_back({start, end});
		}
	}
	
	// Cierre temprano ya que no nos interesan los ID.
	file.close();
	
	//Calculo de volumen
	std::vector<Range> optimized_ranges = merge_ranges(ranges);
	long long total_volume = 0;
	for (size_t i = 0; i < optimized_ranges.size(); i++) 
	{
		Range r = optimized_ranges[i];
		total_volume += (r.end - r.start + 1);
	}
	
	std::cout << "IDs cubiertos por los rangos: " << total_volume << std::endl;
	return 0;
}
