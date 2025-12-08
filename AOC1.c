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

    int dial_pos = 50;       
    int zeros = 0;  
    char direction;
    int pasos;

    while (file >> direction >> pasos)
    {
        
        if (direction == 'R')
       	{
            dial_pos = (dial_pos + pasos) % 100;
        } 
        else if (direction == 'L')
       	{
            dial_pos = (dial_pos - pasos);
            dial_pos = (dial_pos % 100); 
            if (dial_pos < 0) 
	    {
                dial_pos += 100;
            }
        }

        if (dial_pos == 0) {
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
