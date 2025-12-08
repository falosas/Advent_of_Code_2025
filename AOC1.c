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
    int amount;

    while (file >> direction >> amount)
    {
        
        if (direction == 'R')
       	{
            dial_pos = (dial_pos + amount) % 100;
        } 
        else if (direction == 'L')
       	{
            dial_pos = (dial_pos - amount);
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

    std::cout << "Contraseña (veces en 0): " << zeros << std::endl;
}

int main()
{
    solve();
    return 0;
}
